/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxBspGeometry.h"
#include "fgGfxBspCompiler.h"

using namespace fg;

//------------------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getBack(void) {
    if(m_nodeIdx[0] >= 0)
        return m_pBsp->m_nodes[m_nodeIdx[0]];
    return 0;
}

//------------------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getFront(void) {
    if(m_nodeIdx[1] >= 0)
        return m_pBsp->m_nodes[m_nodeIdx[1]];
    return 0;
}

//------------------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getParent(void) {
    if(m_idxParent >= 0)
        return m_pBsp->m_nodes[m_idxParent];
    return 0;
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::process(CVector<CPolygon>& polys) {
    CVector<CPolygon> loco;
    clear();

    FG_LOG_DEBUG("GFX: Building BSP Tree...");
    unsigned int n = polys.size();
    loco.reserve(n);
    for(unsigned int i = 0; i < n; i++) {
        polys[i].m_flags &= ~SPLITTER_POLY;
        loco.push_back(polys[i]);
    }
    _pInPolys = &polys; // hold a pointer to input data set

    makeRoot(); // sdd default root node
    FG_LOG_DEBUG("GFX: Preparing BSP...");

    updateNodeBB(getRoot(), polys);
    //V3 center = Root()->_bbox.GetCenter();
    m_balance = 6;

    dw_deltatime = timesys::ticks();
    buildPlaneArray(loco);
    CBspNode* pNode = m_nodes[0];
    pNode->m_planeIdx = 0;
    n_thrcount = 0;
    n_threadsup = 0;
    if(BSP_TERRAIN == m_bspType) {
        R_TerrainCompile(0, loco);
    } else {
        R_Compile(0, loco);

    }
    dw_deltatime = timesys::ticks() - dw_deltatime;
    FG_LOG_DEBUG("GFX: BSP Time: %d ms", dw_deltatime);
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::R_TerrainCompile(int nodeIdx, CVector<CPolygon>& polys) {
    static unsigned int Deepth = 0;
    CVector<CPolygon> frontPolys;
    CVector<CPolygon> backPolys;
    CBspNode* pNode = m_nodes[nodeIdx];
    Deepth++;

    findSplitterPlane(polys, pNode);
    partitionTerrain(pNode, polys, frontPolys, backPolys);

    if(frontPolys.size()) {
        if(0 == backPolys.size()) {
            CBspNode* fn = createNode(NODE_LEAF);

            { // lock
                pNode->m_nodeIdx[N_FRONT] = m_nodes.size();
                fn->m_polyIdx = m_polygons.size();
                fn->m_nPolys = frontPolys.size() + backPolys.size();
                fn->m_idxParent = pNode->m_idxNodeThis;
                addNode(fn);

                unsigned int n = frontPolys.size();
                m_polygons.resize(m_polygons.size() + n + backPolys.size());
                for(unsigned int i = 0; i < n; i++) {
                    m_polygons.push_back(frontPolys[i]);
                }
                // WHY? this is inside of if(backPolys.size()==0) what the hell?
                n = backPolys.size();
                for(unsigned int i = 0; i < n; i++) {
                    m_polygons.push_back(backPolys[i]);
                }
            }
            updateNodeBB(fn, frontPolys);
            frontPolys.clear();
        } else // continue
        {
            CBspNode* fn = createNode(0);
            { // lock
                pNode->m_nodeIdx[N_FRONT] = m_nodes.size();
                fn->m_idxParent = pNode->m_idxNodeThis;
                addNode(fn);
            }
            R_TerrainCompile(pNode->m_nodeIdx[N_FRONT], frontPolys);
        }
    }
    if(backPolys.size()) // make a solid leaf
    {
        CBspNode* bn = createNode(0);
        { // lock
            pNode->m_nodeIdx[N_BACK] = m_nodes.size();
            bn->m_idxParent = pNode->m_idxNodeThis;
            addNode(bn);
        }
        R_TerrainCompile(pNode->m_nodeIdx[N_BACK], backPolys);
    } else // continue
    {
        CBspNode* bn = createNode(NODE_LEAF | NODE_SOLID);
        { // lock
            pNode->m_nodeIdx[N_BACK] = m_nodes.size();
            bn->m_idxParent = pNode->m_idxNodeThis;
            addNode(bn);
        }
    }
}

//------------------------------------------------------------------------------------------

fgBool gfx::CBspTree::formConvex(CVector<CPolygon>& frontPolys) {
    CPolygon& fp = frontPolys[0];
    unsigned int n = frontPolys.size();
    for(unsigned int i = 1; i < n; i++) {
        if(CPolygon::ON_BACK == fp.classify(frontPolys[i])) {
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::R_Compile(int nodeIdx, CVector<CPolygon>& polys) { // #FIXME
    CVector<CPolygon> frontPolys;
    CVector<CPolygon> backPolys;
    CBspNode* pNode = m_nodes[nodeIdx];
    int splitters = partition(pNode, polys, frontPolys, backPolys);

    if(0 == splitters && backPolys.size()) {
        unsigned int n = backPolys.size();
        frontPolys.reserve(frontPolys.size() + n);
        for(unsigned int i = 0; i < n; i++) {
            frontPolys.push_back(backPolys[i]);
        }
        backPolys.clear();
    }

    if(frontPolys.size()) {
        if(splitters == 0) {
            CBspNode* fn = createNode(NODE_LEAF);
            { // lock
                pNode->m_nodeIdx[N_FRONT] = m_nodes.size();
                fn->m_polyIdx = m_polygons.size();
                fn->m_nPolys = frontPolys.size();
                fn->m_idxParent = pNode->m_idxNodeThis;
                addNode(fn);
                {
                    unsigned int frontN = frontPolys.size();
                    m_polygons.reserve(m_polygons.size() + frontN);
                    for(unsigned int i = 0; i < frontN; i++) {
                        m_polygons.push_back(frontPolys[i]);
                    }
                }
            }
            updateNodeBB(fn, frontPolys);
            frontPolys.clear();
        } else //  continue
        {
            CBspNode* fn = createNode(0);
            { // lock
                pNode->m_nodeIdx[N_FRONT] = m_nodes.size();
                fn->m_idxParent = pNode->m_idxNodeThis;
                addNode(fn);
            }
            updateNodeBB(fn, frontPolys);
            //Recurs_Or_Thread(pNode->m_nodeIdx[N_FRONT], frontPolys); // #FIXME
            R_Compile(pNode->m_nodeIdx[N_FRONT], frontPolys); // #FIXME
        }
    }

    if(backPolys.size()) // make a solid leaf
    {
        CBspNode* bn = createNode(0);
        { // lock
            pNode->m_nodeIdx[N_BACK] = m_nodes.size();
            bn->m_idxParent = pNode->m_idxNodeThis;
            addNode(bn);
        }
        updateNodeBB(bn, backPolys);
        //Recurs_Or_Thread(pNode->m_nodeIdx[N_BACK], backPolys); // #FIXME
        R_Compile(pNode->m_nodeIdx[N_BACK], backPolys); // #FIXME
    } else {
        CBspNode* bn = createNode(NODE_LEAF | NODE_SOLID);
        { // lock
            pNode->m_nodeIdx[N_BACK] = m_nodes.size();
            bn->m_idxParent = pNode->m_idxNodeThis;
            bn->m_bbox.max = Vector3f(0, 0, 0);
            bn->m_bbox.min = Vector3f(0, 0, 0);
            addNode(bn);
        }
    }
}

//------------------------------------------------------------------------------------------
// Select the best splitter

int gfx::CBspTree::getBestSplitter(CVector<CPolygon>& polys,
                                   CPolygon* pWantPoly) {
    int retval = -1;
    unsigned int splitCnt = 0;
    unsigned int bestscore = UINT_MAX - 1;
    unsigned int maxbacks = 0;
    unsigned int maxfronts = 0;
    unsigned int n = polys.size();
    unsigned int bpIt = n;

    for(unsigned int i = 0; i < n; i++) {
        //FOREACH(std::list<CPolygon>, polys, pPoly1) {
        unsigned int score = 0;
        unsigned int boths = 0;
        unsigned int planars = 0;
        unsigned int backs = 0;
        unsigned int fronts = 0;
        CPolygon& polySpliter = polys[i];

        if(!polySpliter.isSplitter()) {

            //FOREACH(std::list<CPolygon>, polys, pPoly2) {
            for(unsigned int j = 0; j < n; j++) {
                CPolygon::RelPos whereIs;
                CPolygon& poly = polys[j];

                //if(pPoly2 == pPoly1)
                if(j == i)
                    continue;
                whereIs = poly.classify(polySpliter);
                switch(whereIs) {
                    case CPolygon::ON_PLANE:
                        ++planars;
                        break;
                    case CPolygon::ON_FRONT:
                        ++fronts;
                        break;
                    case CPolygon::ON_BACK:
                        ++backs;
                        break;
                    case CPolygon::ON_SPLIT:
                        ++boths;
                        break;
                }
            }
            score = math::abs(fronts - backs)+(boths * m_balance);
            if(score < bestscore) {
                bestscore = score;
                bpIt = i;
            }
            splitCnt++;
            maxfronts = math::max(maxfronts, fronts);
            maxbacks = math::max(maxbacks, backs);
        }
    }
    if(bpIt != polys.size()) {
        // mark it as a splitter poly
        polys[bpIt].setSplitter();
        return polys[bpIt].m_planeIdx;
    }

    //FOREACH(std::list<CPolygon>, polys, pPoly1) {
    for(unsigned int i = 0; i < n; i++) {
        if(!polys[i].isSplitter()) {
            // mark it as a splitter poly
            polys[i].setSplitter();
            return polys[i].m_planeIdx;
        }
    }
    // all are on front so doesn't matter
    return polys[0].m_planeIdx;
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::buildPlaneArray(CVector<CPolygon>& polygons) {
    //ASSERT(m_planes.size() == 0);
    fgBool outerLoop = FG_FALSE;
    // init the splitting planes
    do {
        outerLoop = FG_FALSE;
        unsigned int n = polygons.size();
        for(unsigned int i = 0; i < n; i++) {
            CPolygon& poly = polygons[i];
            poly.recalculate();
            fgBool isnot0 = (math::abs(poly.n.x) > EPSILON ||
                             math::abs(poly.n.y) > EPSILON ||
                             math::abs(poly.n.z) > EPSILON);
            if(isnot0) {
                Planef plane(poly.n, poly.d);
                poly.m_planeIdx = -1;
                //CVector<CPlane>::iterator fp = _planes.find(plane);
                int fp = m_planes.find(plane);
                if(fp < 0) {
                    poly.m_planeIdx = m_planes.size();
                    m_planes.push_back(plane);
                } else {
                    poly.m_planeIdx = fp;
                }
                //ASSERT(pPoly->_planeIdx != -1);
            } else {
                // erase selected polygon
                polygons[i] = polygons[n - 1];
                polygons.resize(n - 1);
                outerLoop = FG_TRUE;
                i = n;
                continue;
            }
        }
    } while(outerLoop);
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::partitionTerrain(CBspNode* pNode,
                                     CVector<CPolygon>& polys,
                                     CVector<CPolygon>& frontPolys,
                                     CVector<CPolygon>& backPolys) {
    while(polys.size()) {
        CPolygon& curPoly = polys.back();
        CPolygon::RelPos whereIs = curPoly.classify(pNode->getPlane());
        switch(whereIs) {
            case CPolygon::ON_PLANE:
                if(math::isZero(math::dot(curPoly.n, pNode->getPlane().n) - 1.0f)) {
                    frontPolys.push_back(curPoly);
                } else {
                    backPolys.push_back(curPoly);
                }
                break;
            case CPolygon::ON_SPLIT:
            {
                CPolygon frontPoly;
                CPolygon backPoly;
                curPoly.split(pNode->getPlane(), frontPoly, backPoly);
                backPolys.push_back(backPoly);
                frontPolys.push_back(frontPoly);
            }
                break;
            case CPolygon::ON_FRONT:
                frontPolys.push_back(curPoly);
                break;
            case CPolygon::ON_BACK:
                backPolys.push_back(curPoly);
                break;
            default:
                break;
        }
        polys.pop_back();
    }
    updateNodeBB(pNode, frontPolys);
    updateNodeBB(pNode, backPolys);
}

//------------------------------------------------------------------------------------------

int gfx::CBspTree::partition(CBspNode* pNode,
                             CVector<CPolygon>& polys,
                             CVector<CPolygon>& frontPolys,
                             CVector<CPolygon>& backPolys) {
    pNode->m_planeIdx = getBestSplitter(polys);

    int splitters = polys.size();
    while(polys.size()) {
        CPolygon& curPoly = polys.back();
        if(curPoly.isSplitter())
            splitters--;

        CPolygon::RelPos whereIs = curPoly.classify(pNode->getPlane());
        switch(whereIs) {
            case CPolygon::ON_PLANE:
                if(math::isZero(math::dot(curPoly.n, pNode->getPlane().n) - 1.0f)) {
                    curPoly.setSplitter();
                    frontPolys.push_back(curPoly);
                } else
                    backPolys.push_back(curPoly);
                break;
            case CPolygon::ON_FRONT:
                frontPolys.push_back(curPoly);
                break;
            case CPolygon::ON_BACK:
                backPolys.push_back(curPoly);
                break;
            case CPolygon::ON_SPLIT:
            {
                CPolygon frontPoly;
                CPolygon backPoly;

                curPoly.split(pNode->getPlane(), frontPoly, backPoly);
                if(curPoly.isSplitter()) {
                    frontPoly.setSplitter();
                    backPoly.setSplitter();
                }
                backPolys.push_back(backPoly);
                frontPolys.push_back(frontPoly);
            }
                break;
            default:
                break;
        }
        polys.pop_back();
    }
    return splitters;

}

//------------------------------------------------------------------------------------------

gfx::Planef gfx::CBspTree::getOptimSpliterPlane(CVector<CPolygon>& polys, int moe) {
    AABoundingBox3Df allBox;
    Vector3f V1(100, 100, 100);
    AABoundingBox3Df oneBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    unsigned int n = polys.size();
    for(unsigned int i = 0; i < n; i++) {
        //FOREACH(std::list<CPolygon>, polys, pp) {
        polys[i].recalculate();
        allBox.merge(polys[i].m_bbox);
    }

    Vector3f allEx = allBox.getExtent();
    Vector3f oneEx = oneBox.getExtent();
    Vector3f ex = allBox.getExtent();
    Vector3f c = allBox.getCenter();

    float mx = math::max(ex.x, ex.y);
    mx = math::max(mx, ex.z);

    if(ex.x == mx) {
        ex.x = 1;
        ex.y = 0;
        ex.z = 0;
    } else if(ex.y == mx) {
        ex.x = 0;
        ex.y = 1;
        ex.z = 0;
    } else {
        ex.x = 0;
        ex.y = 0;
        ex.z = 1;
    }

    // make all of them on front to nail down the tree
    if(moe) {
        oneEx *= 8;
        if((allEx.x <= oneEx.x &&
            allEx.y <= oneEx.y &&
            allEx.z <= oneEx.z) || (int)polys.size() <= moe) {
            c = allBox.min; // one unit down
            c.x -= 1;
            c.y -= 1;
            c.z -= 1;
        }
    }
    return Planef(ex, c);
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::findSplitterPlane(CVector<CPolygon>& polys, CBspNode* pNode) {
    Planef plane = getOptimSpliterPlane(polys);
    pNode->m_planeIdx = m_planes.size();
    m_planes.push_back(plane);

}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::updateNodeBB(CBspNode* pNode, CVector<CPolygon>& polys) {
    unsigned int n = polys.size();
    //FOREACH(CVector<CPolygon>, polys, poly) {
    for(unsigned int i = 0; i < n; i++) {
        polys[i].recalculate();
        pNode->m_bbox.merge(polys[i].m_bbox);
        getRoot()->m_bbox.merge(polys[i].m_bbox);
    }
}

//------------------------------------------------------------------------------------------

void gfx::CBspTree::clear(void) {
    CVector<CBspNode*>::iterator end = m_nodes.end();
    for(CVector<CBspNode*>::iterator pp = m_nodes.begin(); pp != end; pp++) {
        if(!(*pp))
            continue;
        delete[] (*pp);
    }
    m_nodes.clear();
    m_planes.clear();
    m_polygons.clear();
    m_leafs.clear();
    dw_deltatime = timesys::ticks();
}

//------------------------------------------------------------------------------------------

fgBool gfx::CBspTree::R_SegmentIntersect(int nodeIdx,
                                         Vector3f& a,
                                         Vector3f& b,
                                         Vector3f& col) {
    CBspNode* pNode = m_nodes[nodeIdx];
    if(pNode->isLeaf()) {
        if(pNode->isSolid()) {
            return FG_TRUE;
        }
        return FG_FALSE;
    }

    Planef& plane = m_planes[pNode->m_planeIdx];
    float da = plane.distance(a);
    float db = plane.distance(b);

    if(da > -EPSILON && db > -EPSILON)
        return R_SegmentIntersect(pNode->m_nodeIdx[N_FRONT], a, b, col);
    else if(da < EPSILON && db < EPSILON)
        return R_SegmentIntersect(pNode->m_nodeIdx[N_BACK], a, b, col);

    int side = da >= 0;
    float dist = da / (da - db);
    Vector3f midPct = a + ((b - a) * dist);

    if(R_SegmentIntersect(pNode->m_nodeIdx[side], a, midPct, col)) {
        return FG_TRUE;
    } else if(R_SegmentIntersect(pNode->m_nodeIdx[!side], midPct, b, col)) {
        if(!m_hitTest) {
            m_hitTest = FG_TRUE;
            col = midPct;
        }
        return FG_TRUE;
    }
    return FG_FALSE;
}

//------------------------------------------------------------------------------------------

fgBool gfx::CBspTree::segmentIntersect(Vector3f& paa,
                                       Vector3f& pab,
                                       int node,
                                       Vector3f& col) {
    m_hitTest = FG_FALSE;
    R_SegmentIntersect(0, paa, pab, col);
    return m_hitTest;
}

//------------------------------------------------------------------------------------------

int gfx::CBspTree::getCurrentLeaf(Vector3f& pov, int nodeIdx) {
    float rdist;
    CBspNode* pNode = m_nodes[nodeIdx];
    while(!pNode->isLeaf()) {
        Planef& plane = m_planes[pNode->m_planeIdx];
        rdist = plane.distance(pov);
        if(rdist < 0) {
            nodeIdx = pNode->m_nodeIdx[0];
        } else {
            nodeIdx = pNode->m_nodeIdx[1];
        }
        pNode = m_nodes[nodeIdx];
    }
    return m_nodes[nodeIdx]->m_leafIdx;
}
