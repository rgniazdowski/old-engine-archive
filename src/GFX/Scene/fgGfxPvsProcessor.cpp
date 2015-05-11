/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxPvsProcessor.h"
#include "fgGfxPortalProcessor.h"
#include "fgGfxBspTree.h"
#include "fgGfxBspNode.h"
#include "fgGfxPortal.h"
#include "Util/fgTime.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CPvsProcessor::CPvsProcessor() : m_numLeafs(0), m_pvs(0), m_numPvs(0) { }
//------------------------------------------------------------------------------

gfx::CPvsProcessor::~CPvsProcessor() {
    clear();
}
//------------------------------------------------------------------------------

void gfx::CPvsProcessor::clear(void) {
    if(m_pvs)
        delete[] m_pvs;
    m_pvs = 0;
    m_numPvs = 0;
    CVector<SPortalData*>::iterator end = m_portVs.end();
    for(CVector<SPortalData*>::iterator pp = m_portVs.begin(); pp != end; pp++) {
        if(!(*pp))
            continue;
        delete[] (*pp);
    }
    m_portVs.clear();
    dw_deltatime = timesys::ticks();

}
//------------------------------------------------------------------------------

int AllocBitsRoundByLong(int nSetCount) {
    int rval = (nSetCount + 7) / 8; // bytes
    rval = (rval * 3 + 3) & 0xFFFFFFFC; // round by mod4
    return rval;
}
//------------------------------------------------------------------------------

void gfx::CPvsProcessor::process(CBspTree& tree, CPortalProcessor& portalprc) {
    FG_LOG_DEBUG("GFX: Calculating PVS. Please Wait...");

    m_pBspTree = &tree;
    m_pPortProc = &portalprc;
    clear();
    m_numLeafs = tree.m_leafs.size();
    dw_deltatime = timesys::ticks();

    if(portalprc.hasPortals()) {
        CVector<CPortal>& rPortals = portalprc.getPortals();
        InitalPortalVis(rPortals);
        gatherLeafsVis();
    }
    dw_deltatime = timesys::ticks() - dw_deltatime;
    FG_LOG_DEBUG("GFX: PVS Time: %d ms", dw_deltatime);
}
//------------------------------------------------------------------------------

fgBool CompletteOnBack(gfx::Planef& pA, gfx::CPortal& rP) {
    int count = rP.m_vertexes.size();
    CVector<Vector3f>::iterator end = rP.m_vertexes.end();
    CVector<Vector3f>::iterator begin = rP.m_vertexes.begin();
    for(CVector<Vector3f>::iterator pvx = begin; pvx != end; pvx++) {
        if(pA.classify(*pvx) == gfx::Planef::POSITIVE)
            break;
        --count;
    }
    return (fgBool)(0 == count);
}
//------------------------------------------------------------------------------

fgBool CompletteOnFront(gfx::Planef& pA, gfx::CPortal& rP) {
    int count = rP.m_vertexes.size();

    CVector<Vector3f>::iterator end = rP.m_vertexes.end();
    CVector<Vector3f>::iterator begin = rP.m_vertexes.begin();
    for(CVector<Vector3f>::iterator pvx = begin; pvx != end; pvx++) {
        if(pA.classify(*pvx) == gfx::Planef::NEGATIVE)
            break;
        --count;
    }
    return (fgBool)(0 == count);
}
//------------------------------------------------------------------------------

fgBool gfx::CPvsProcessor::InitalPortalVis(CVector<CPortal>& rPortals) {
    fgBool bRetVal = FG_TRUE;
    unsigned char* pVis = new unsigned char[rPortals.size()];
    int nCount = 0;
    int nTotal = rPortals.size();

    //ASSERT(pVis);

    for(CVector<CPortal>::iterator portItA = rPortals.begin(); portItA != rPortals.end(); portItA++) {
        CPortal& prtA = *portItA;
        SPortalData* pD = new SPortalData(m_numLeafs);
        //_portVs << pD; // this prtA pvs
        m_portVs.push_back(pD);
        ::memset(pVis, 0, rPortals.size()); // reset the array for this prtA

        FG_LOG_DEBUG("Processing PVS for Portal : %d", nCount);
        for(CVector<CPortal>::iterator portItB = rPortals.begin(); portItB != rPortals.end(); portItB++) {
            CPortal& prtB = *portItB;
            if(portItB == portItA)
                continue;
            if(prtA.m_idxThis + 1 == prtB.m_idxThis) // portal sees iu'ts duplicate
            {
                pVis[prtB.m_idxThis] = 1; // portal vis flag
                continue;
            }
            if(CompletteOnBack(prtA, prtB)) // complette on back we dont see this
                continue; // so leave his byte on 0
            if(CompletteOnFront(prtB, prtA)) // are we complette on front
                continue;

            pVis[prtB.m_idxThis] = 1; // portal vis flag
        }
        pD->possibleVisCount = 0;
        performPVS(prtA, rPortals, pVis);
        R_PortalFlood(prtA, pVis, prtA.m_sideLIdx[1]); // flod in neghbour leaf
        ++nCount;
    }
    delete []pVis;
    return bRetVal;
}
//------------------------------------------------------------------------------

void gfx::CPvsProcessor::R_PortalFlood(CPortal& srcP, unsigned char* pVis, int nLeaf) {
    if(m_portVs[srcP.m_idxThis]->portArrPvs[nLeaf] == 1) // leaf vis bit
        return;
    m_portVs[srcP.m_idxThis]->portArrPvs.set(nLeaf);
    m_portVs[srcP.m_idxThis]->possibleVisCount++; // count how many portals this prtA can flood
    CBspLeaf* pToLeaf = m_pPortProc->getLeaf(nLeaf);
    CVector<int>& iporrts = pToLeaf->getPortalIdxes();

    for(CVector<int>::iterator pip = iporrts.begin(); pip != iporrts.end(); pip++) {
        if(0 == pVis[*pip]) // don't flood in this prtA
            continue;
        CPortal& prtA = m_pPortProc->getPortal(*pip);
        R_PortalFlood(srcP, pVis, prtA.m_sideLIdx[1]);
    }
}
//------------------------------------------------------------------------------

void gfx::CPvsProcessor::performPVS(CPortal& portA,
                                    CVector<CPortal>& rPortals,
                                    unsigned char* prevPvs) {
    for(CVector<CPortal>::iterator portItB = rPortals.begin(); portItB != rPortals.end(); portItB++) {
        CPortal& prtB = *portItB;
        if(prtB == portA)
            continue;
        if(prevPvs[prtB.m_idxThis] == 0)
            continue;
        if(!doesPortalSeesPortal(portA, prtB))
            prevPvs[prtB.m_idxThis] = 0;
    }
}
//------------------------------------------------------------------------------

void gfx::CPvsProcessor::gatherLeafsVis(void) {
    int dummy;
    if(m_pvs) {
        delete[] m_pvs;
    }
    m_pvs = 0;
    int nPerLeaf = AllocBitsRoundByLong(m_numLeafs);
    m_numPvs = m_numLeafs * nPerLeaf; // all leafs
    m_pvs = new unsigned char[m_numPvs];

    ::memset(m_pvs, 0, m_numPvs); // zerooo them
    unsigned char* pWalkPvsPtr = m_pvs; // head of all bytes
    CBitArray pPerLeafPvs(m_numLeafs);

    CVector<CBspLeaf*>::iterator begin = m_pBspTree->m_leafs.begin();
    CVector<CBspLeaf*>::iterator end = m_pBspTree->m_leafs.end();
    for(CVector<CBspLeaf*>::iterator ppLeaf = begin; ppLeaf != end; ppLeaf++) {
        CBspLeaf * pLeaf = (*ppLeaf);
        CVector<int>& pidxs = pLeaf->getPortalIdxes();

        pPerLeafPvs.reset();
        pLeaf->m_pvsIdx = pWalkPvsPtr - m_pvs;
        pPerLeafPvs.set((*ppLeaf)->m_leafIdx);

        for(CVector<int>::iterator pidx = pidxs.begin(); pidx != pidxs.end(); pidx++) {
            CPortal& portal = m_pPortProc->getPortal(*pidx);
            SPortalData* pD = m_portVs[portal.m_idxThis];
            pPerLeafPvs.merge(pD->portArrPvs);
        }
        //ASSERT(pPerLeafPvs.Size() == nPerLeaf);
        ::memcpy(pWalkPvsPtr, pPerLeafPvs.buffer(dummy), nPerLeaf);
        pWalkPvsPtr += nPerLeaf;
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CPvsProcessor::doesPortalSeesPortal(CPortal& a, CPortal& b) {
    //Vector3f dummy;
    Vector3f paa;
    Vector3f pab;

    typedef CVector<Vector3f>::iterator Vec3fItor;
    Vec3fItor vabegin = a.m_vertexes.begin();
    Vec3fItor vaend = a.m_vertexes.end();
    for(Vec3fItor pv = vabegin; pv != vaend; pv++) {
        paa += *pv;
    }
    Vec3fItor vbbegin = b.m_vertexes.begin();
    Vec3fItor vbend = b.m_vertexes.end();
    for(Vec3fItor pv = vbbegin; pv != vbend; pv++) {
        pab += *pv;
    }
    paa /= (float)a.m_vertexes.size();
    pab /= (float)b.m_vertexes.size();
    // test center to center
    Vector3f col;
    if(!m_pBspTree->segmentIntersect(paa, pab, 0, col)) {
        return FG_TRUE;
    }
    // test close to corner vertex to close to corner vertex
    for(Vec3fItor pva = vabegin; pva != vaend; pva++) {
        for(Vec3fItor pvb = vbbegin; pvb != vbend; pvb++) {
            Vector3f c2c1;
            Vector3f c2c2;

            //c2c1.interpolate(*pva, paa, .3);
            //interpolateVec3f(c2c1, *pva, paa, .3);
            c2c1 = math::mix(*pva, paa, 0.3f);
            //c2c2.interpolate(*pvb, pab, .3);
            //interpolateVec3f(c2c2, *pvb, pab, .3);
            c2c2 = math::mix(*pvb, pab, 0.3f);

            if(!m_pBspTree->segmentIntersect(c2c1, c2c2, 0, col)) {
                return FG_TRUE;
            }
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------
