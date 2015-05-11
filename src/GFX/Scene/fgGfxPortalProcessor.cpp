/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

//#include "fgGfxBspTypes.h"
#include "fgGfxPortalProcessor.h"
#include "fgGfxBspNode.h"
#include "fgGfxBspTree.h"
#include "fgGfxPortal.h"
#include "GFX/fgGfxPolygon.h"
#include "fgLog.h"

#include <set>
#include <algorithm>

using namespace fg;

//------------------------------------------------------------------------------

fgBool R_SearchLeaf(CVector<gfx::CBspNode*>& nodes,
                    gfx::CBspNode* pStartNode,
                    gfx::CBspNode* p2Find) {
    if(!pStartNode || nodes.empty()) {
        return FG_FALSE;
    }
    if(pStartNode->isLeaf()) {
        return (pStartNode == p2Find);
    }

    if(pStartNode->m_nodeIdx[N_BACK] >= 0 && R_SearchLeaf(nodes, nodes[pStartNode->m_nodeIdx[N_BACK]], p2Find))
        return FG_TRUE;
    if(pStartNode->m_nodeIdx[N_FRONT] >= 0 && R_SearchLeaf(nodes, nodes[pStartNode->m_nodeIdx[N_FRONT]], p2Find))
        return FG_TRUE;
    return FG_FALSE;
}
//------------------------------------------------------------------------------

gfx::CBspNode* R_FindCommonParent(CVector<gfx::CBspNode*>& nodes,
                                  gfx::CBspNode* pNotGo,
                                  gfx::CBspNode* pUpNode,
                                  gfx::CBspNode* pSec) {
    gfx::CBspNode* p2Go;

    if(pNotGo == pUpNode->getFront())
        p2Go = pUpNode->getBack();
    else
        p2Go = pUpNode->getFront();

    if(R_SearchLeaf(nodes, p2Go, pSec))
        return pUpNode;
    if(pUpNode->m_idxNodeThis == 0) {
        if(R_SearchLeaf(nodes, pUpNode, pSec))
            return pUpNode;
    }
    return R_FindCommonParent(nodes, pUpNode, nodes[pUpNode->m_idxParent], pSec);
}
//------------------------------------------------------------------------------

gfx::CBspNode* FindCommonParent(CVector<gfx::CBspNode*>& nodes,
                                gfx::CBspNode* pLa,
                                gfx::CBspNode* pLb) {
    return R_FindCommonParent(nodes, pLa, nodes[pLa->m_idxParent], pLb);
}
//------------------------------------------------------------------------------

gfx::CBspLeaf* gfx::CPortalProcessor::getLeaf(int idx) {
    CBspNode* pL = m_pTree->getLeaf(idx);
    //ASSERT(pL->m_flags & NODE_LEAF);
    return (CBspLeaf*)pL;
}
//------------------------------------------------------------------------------

void gfx::CPortalProcessor::clear(void) {
    m_portals.clear();
    dw_deltatime = timesys::ticks();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// build the new leafs tha will hold additional flags. we do not copy the

fgBool IsTouchesBox(const gfx::AABoundingBox3Df& a, const gfx::AABoundingBox3Df& other) {
    if(a.max.x <= other.min.x) return FG_FALSE;
    if(a.min.x >= other.max.x) return FG_FALSE;
    if(a.max.y <= other.min.y) return FG_FALSE;
    if(a.min.y >= other.max.y) return FG_FALSE;
    if(a.max.z <= other.min.z) return FG_FALSE;
    if(a.min.z >= other.max.z) return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CPortalProcessor::process(CBspTree& tree) {
    int cleafIdx1 = 0;
    CVector<CPortal> portals;
    CVector<::std::pair<int, int> > uniques;
    FG_LOG_DEBUG("Generating Portals. Please Wait...");

    m_pTree = &tree;
    clear();
    dw_deltatime = timesys::ticks();

    CVector<CBspLeaf*>::iterator end = tree.m_leafs.end();
    CVector<CBspLeaf*>::iterator begin = tree.m_leafs.begin();
    for(CVector<CBspLeaf*>::iterator pp1 = begin; pp1 != end; pp1++) {
        FG_LOG_DEBUG("GFX: Processing Portals for Leaf : %d", cleafIdx1);
        for(CVector<CBspLeaf*>::iterator pp2 = begin; pp2 != end; pp2++) {
            if(pp1 == pp2)
                continue;
            CBspLeaf* pl1 = *pp1;
            CBspLeaf* pl2 = *pp2;

            ::std::pair<int, int> p(pl1->m_leafIdx, pl2->m_leafIdx);
            if(find(uniques.begin(), uniques.end(), p) != uniques.end())
                continue;

            AABoundingBox3Df b1 = pl1->m_bbox;
            AABoundingBox3Df b2 = pl2->m_bbox;
            b1.min -= 8.0f; //b1.Expand(4);
            b1.max += 8.0f; //b1.Expand(4);
            if(IsTouchesBox(b1, b2)) {
                CBspNode* pNode = FindCommonParent(tree.m_nodes, pl1, pl2);
                CPortal portal(this);

                calculateInitialPortal(portal, pNode);

                clipWithLeafSides(pl1, portal);
                clipWithLeafSides(pl2, portal);

                portal.addSideLeafIdx(pl1->m_leafIdx);
                portal.addSideLeafIdx(pl2->m_leafIdx);
                if(validatePortal(portal)) {
                    //portals << portal;
                    portals.push_back(portal);
                }
                p.first = pl1->m_leafIdx;
                p.second = pl2->m_leafIdx;
                uniques.push_back(p);

                p.first = pl2->m_leafIdx;
                p.second = pl1->m_leafIdx;
                uniques.push_back(p);
            }
        }
        ++cleafIdx1;
    }
    duplicatePortals(portals, m_portals);
    dw_deltatime = timesys::ticks() - dw_deltatime;
    FG_LOG_DEBUG("GFX: Portal Time: %d ms", dw_deltatime);
}
//------------------------------------------------------------------------------

fgBool gfx::CPortalProcessor::validatePortal(CPortal& portal) {
    Vector3f points[2];
    Vector3f center = portal.getCenter();
    points[0] = center - portal.n * 8.0f;
    points[1] = center + portal.n * 8.0f;
    int nleal1 = m_pTree->getCurrentLeaf(points[0]);
    int nleal2 = m_pTree->getCurrentLeaf(points[1]);

    if((nleal1 == portal.m_sideLIdx[0] && nleal2 == portal.m_sideLIdx[1]) ||
       (nleal1 == portal.m_sideLIdx[1] && nleal2 == portal.m_sideLIdx[0])) {

        if(nleal1 == portal.m_sideLIdx[0])
            return FG_TRUE;

        int temp = portal.m_sideLIdx[0];
        portal.m_sideLIdx[0] = portal.m_sideLIdx[1];
        portal.m_sideLIdx[1] = temp;
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

static Vector3f GetMajorAxes(Vector3f& normal) {
    Vector3f rv;
    if(math::abs(normal.y) > math::abs(normal.z)) {
        if(math::abs(normal.z) < math::abs(normal.x)) {
            rv.z = 1.f;
        } else {
            rv.x = 1.f;
        }
    } else {
        if(math::abs(normal.y) <= math::abs(normal.x)) {
            rv.y = 1;
        } else {
            rv.x = 1;
        }
    }
    return rv;
}
//------------------------------------------------------------------------------

fgBool gfx::CPortalProcessor::calculateInitialPortal(CPortal& portal, CBspNode* pNode) {
    Planef& plane = pNode->getPlane();
    Vector3f& normal = plane.n;
    AABoundingBox3Df bb = m_pTree->getRoot()->m_bbox; //pNode->_bbox;// bbox
    Vector3f bbCenter = bb.getCenter(); // bbox center
    float d2plan = -plane.distance(bbCenter); // dist to plane
    Vector3f portOrig = bbCenter + (normal * d2plan); // plane center id bb center projeccted on plane
    Vector3f ax = GetMajorAxes(plane.n); // get to see what wax we are using for rotation cp
    ax = math::normalize(ax);

    // build a polygon from plane
    Vector3f bbEx = (bb.max - bbCenter); // bbox extends
    Vector3f uDr = math::cross(ax, normal); // to corner vectors;
    Vector3f vDr = math::cross(uDr, normal);

    uDr *= math::max((math::max(bbEx.x, bbEx.y)), bbEx.z); //bbEx.getmax();
    vDr *= math::max((math::max(bbEx.x, bbEx.y)), bbEx.z); //bbEx.getmax();
    float vdp = math::dot(normal, ax);

    // enlarge the bogus polygon
    if(!math::isZero(vdp, 0.001f)) {
        uDr *= 8.0f;
        vDr *= 8.0f;
    }

    Vector3f corners[4]; // the 4 corners
    corners[0] = portOrig + (uDr - vDr);
    corners[1] = portOrig + (uDr + vDr);
    corners[2] = portOrig - (uDr - vDr); // switch this to be able to rotate it
    corners[3] = portOrig - (uDr + vDr);

    // populate the portal structure
    portal.m_planeIdx = pNode->m_planeIdx;
    portal.m_flags = CPortal::INITIAL;
    portal.m_vertexes.clear();
    for(int i = 0; i < 4; i++) {
        //portal._vxes << corners[i];
        portal.m_vertexes.push_back(corners[i]);
    }

    // see if bnew generated portal rely on the same plane it was generated (due)
    // 2 floating point errors
    //GCalcNormal(&portal, portal.m_vertexes[0], portal.m_vertexes[1], portal.m_vertexes[2]);
    //This will calculate portal normal
    //portal.set(portal.m_vertexes[0], portal.m_vertexes[1], portal.m_vertexes[2]);
    portal.calcNormal();
    if(0 == portal.m_vertexes.size())
        return FG_FALSE;

    // cut initial portal with BSP bounding box
    cutPortalWithNodeBox(portal, m_pTree->getRoot()->m_bbox, 0);
    if(portal.m_vertexes.size() == 0)
        return FG_TRUE;

    CBspNode * pNodeP = pNode; //->Parent();
    AABoundingBox3Df lb = pNodeP->m_bbox;
    lb.min -= 128.0f; //lb.Expand(128);
    lb.max += 128.0f;
    cutPortalWithNodeBox(portal, pNodeP->m_bbox);

    portal.n = normal;
    portal.d = plane.d;
    return portal.m_vertexes.size() >= 3;
}
//------------------------------------------------------------------------------

void gfx::CPortalProcessor::clipWithLeafSides(CBspLeaf* pLeaf, CPortal& portal) {
    ::std::set<int> sides;
    CPortal ap((const CPortal&)portal), bp;
    for(int i = pLeaf->m_polyIdx; i < pLeaf->m_polyIdx + pLeaf->m_nPolys; i++) {
        SPolygon& poly = m_pTree->m_polygons[i];
        if(sides.find(poly.planeIdx) == sides.end()) {
            sides.insert(poly.planeIdx);
            portal.split(poly, ap, bp);
            portal.clear();
            portal = ap;
        }
    }
}
//------------------------------------------------------------------------------

/*
BackLeaf->Portal->FrontLeaf    P->[0][1]
|  - front leaf  - back leaf
Leaf->[portals] these portals has back leaf this 'Leaf'

Duplication rplaces any portal makeing it 2 way portal
[Lo]->P->[l1]
  
 */
fgBool gfx::CPortalProcessor::duplicatePortals(CVector<CPortal>& portalsI,
                                               CVector<CPortal>& portalsO) {

    Vector3f nodeC0; // portal side leafs bbox centers
    Vector3f nodeC1;
    portalsO.clear();

AG:
    CVector<CPortal>::iterator end = portalsI.end();
    for(CVector<CPortal>::iterator pPrt = portalsI.begin(); pPrt != end; pPrt++) {
        if(pPrt->m_vertexes.size() < 3) {

            portalsI.erase(pPrt);
            goto AG;
        }
        //ASSERT(pPrt->m_sideLIdx.size() == 2); // indexes in node structure
        CPortal dupP = (*pPrt);
        dupP.reverse();
        dupP.setFlag(CPortal::DUPLICATED);
        int temp = dupP.m_sideLIdx[0];
        dupP.m_sideLIdx[0] = dupP.m_sideLIdx[1];
        dupP.m_sideLIdx[1] = temp;
        /*
        int iLf0 = pPrt->_sideLIdx[0];             // see wich leaf is back and wich is front
        int iLf1 = pPrt->_sideLIdx[1];
        nodeC0   = GetLeaf(iLf0)->_bbox.GetCenter();
        nodeC1   = GetLeaf(iLf1)->_bbox.GetCenter();
        int side1;
        int side0 = pPrt->GetSide(nodeC0);
        side1 = -side0;
        if(0 == side0)                          // it may end up on portal plane
        {                                       // so take the other one
        side1 = pPrt->GetSide(nodeC1);
        //ASSERT(side1 != 0);
        if(0==side1)
        {
        continue;
        }
        side0 = -side1;
        }
        // make [0]P[1]
        if(side0 > 0) // if leaf [0] id on front switch the order
        {
        SWITCHI(dupP._sideLIdx[0] , dupP._sideLIdx[1]);
        SWITCHI(pPrt->_sideLIdx[0] , pPrt->_sideLIdx[1]);
        }
         */
        //
        // _portIdxes
        //
        pPrt->getBackLeaf()->addPortalIdx(portalsO.size());
        addPortal(*pPrt);

        pPrt->getFrontLeaf()->addPortalIdx(portalsO.size());
        addPortal(dupP);
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CPortalProcessor::cutPortalWithNodeBox(CPortal& portal,
                                                 AABoundingBox3Df& box,
                                                 fgBool reverse) {
    Planef cutPlanes[6];
    if(reverse) {
        cutPlanes[0] = Planef(Vector3f(0.0f, -1.0f, 0.0f), box.max);
        cutPlanes[1] = Planef(Vector3f(0.0f, 1.0f, 0.0f), box.min);
        cutPlanes[2] = Planef(Vector3f(-1.0f, 0.0f, 0.0f), box.max);
        cutPlanes[3] = Planef(Vector3f(1.0f, 0.0f, 0.0f), box.min);
        cutPlanes[4] = Planef(Vector3f(0.0f, 0.0f, -1.0f), box.max);
        cutPlanes[5] = Planef(Vector3f(0.0f, 0.0f, 1.0f), box.min);
    } else {
        cutPlanes[0] = Planef(Vector3f(0.0f, 1.0f, 0.0f), box.max);
        cutPlanes[1] = Planef(Vector3f(0.0f, -1.0f, 0.0f), box.min);
        cutPlanes[2] = Planef(Vector3f(1.0f, 0.0f, 0.0f), box.max);
        cutPlanes[3] = Planef(Vector3f(-1.0f, 0.0f, 0.0f), box.min);
        cutPlanes[4] = Planef(Vector3f(0.0f, 0.0f, 1.0f), box.max);
        cutPlanes[5] = Planef(Vector3f(0.0f, 0.0f, -1.0f), box.min);
    }

    CPortal rp = portal;
    CPortal a(this);
    CPortal b(this);
    for(int i = 0; i < 6 && rp.m_vertexes.size() > 2; i++) {
        rp.split(cutPlanes[i], a, b);
        rp = b;
        b.clear();
        a.clear();
    }
    portal.clear();
    portal = rp;
}
//------------------------------------------------------------------------------

gfx::Planef& gfx::CPortalProcessor::getPlane(int idx) {
    return m_pTree->getPlane(idx);
}
//------------------------------------------------------------------------------

gfx::Planef const& gfx::CPortalProcessor::getPlane(int idx) const {
    return m_pTree->getPlane(idx);
}
//------------------------------------------------------------------------------

void gfx::CPortalProcessor::addPortal(CPortal& portal) {
    portal.m_idxThis = m_portals.size();
    m_portals.push_back(portal);
}
//------------------------------------------------------------------------------
