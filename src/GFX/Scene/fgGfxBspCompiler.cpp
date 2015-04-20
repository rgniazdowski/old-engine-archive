/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
// compiler.cpp: implementation of the Compiler class.
//
//////////////////////////////////////////////////////////////////////

#include "fgGfxBspCompiler.h"
#include "GFX/fgGfxStdInc.h"
#include "fgGfxBspTypes.h"

using namespace fg;

//---------------------------------------------------------------------------------------

fgBool gfx::CBspCompiler::compile(fgBool usethreads) {
    m_usethreads = usethreads;
    //Start();
    //ThreadMain();
    m_bspTree.clear();
    m_portalProcesor.clear();
    m_pvsProcesor.clear();
#if 0
    if(p_brush->_flags & BRSH_TERRAIN) {
        m_bspTree.SetType(CBspTree::BSP_TERRAIN);
    }

    m_bspTree.process(p_brush->_polys);

    if(!(p_brush->_flags & BRSH_TERRAIN)) {
        m_portalProcesor.process(m_bspTree);
        m_pvsProcesor.process(m_bspTree, m_portalProcesor);
    }
#endif
    return 1;
}

//---------------------------------------------------------------------------------------

void gfx::CBspCompiler::render(unsigned int mode, fgBool is3D) {
    switch(mode) {
        case RB_BSP:
            renderBSP(is3D);
            break;
        case RB_PORTALS:
            renderPortals(is3D);
            break;
        case RB_PORTALSBSP:
            if(is3D) {
                renderBSP(is3D);
                renderPortals(is3D);
            } else {
                renderBSP(is3D);
                renderPortals(is3D);
            }
            break;
    }
}

//---------------------------------------------------------------------------------------

static fgBool Local_IsLeafVisFromLeaf(CVector<gfx::CBspLeaf*>& leafs,
                                      int l1,
                                      int l2,
                                      unsigned char* ppvs) {
    if(l1 < 0 || l2 < 0)return 1;
    unsigned char* pPvs1 = &ppvs[leafs[l1]->m_pvsIdx];
    return (pPvs1[l2 >> 3] & (1 << (l2 & 7))) != 0;
}

//---------------------------------------------------------------------------------------

void gfx::CBspCompiler::renderBSP(fgBool is3D) {
    Vector3f camPos; //p_dlg->gl_3d._cam._wpos;
    int curLeaf = m_bspTree.getCurrentLeaf(camPos);
    fgBool bvisible = FG_FALSE;
    //int nVisPOlys = 0;
    CVector<CPolygon*> visibles;
    visibles.reserve(64);

    //FG_LOG_DEBUG("Current Leaf=%d", curLeaf);
    if(!is3D) {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(0);
    }
    //    glColor4ubv(CLR_WHITE);
    glDisable(GL_BLEND);

    // from this leaf check the pvs and render all visible leafs
    CVector<CBspLeaf*>::iterator end = m_bspTree.m_leafs.end();
    for(CVector<CBspLeaf*>::iterator it = m_bspTree.m_leafs.begin(); it != end; it++) {
        CBspLeaf* pNode = *it;
        bvisible = FG_TRUE;
        if(curLeaf != -1) // if we are in interior of the BSP
        {
            if(pNode->m_pvsIdx >= 0 && pNode->m_leafIdx != curLeaf) {
                if(!Local_IsLeafVisFromLeaf(m_bspTree.m_leafs, pNode->m_leafIdx, curLeaf, m_pvsProcesor.m_pvs)) {
                    bvisible = FG_FALSE;
                }
            }

            if(CBspTree::BSP_TERRAIN == m_bspTree.m_bspType) {
                //if(!bvisible || p_dlg->gl_3d._cam.IsCulled(&pNode->_bbox._min, &pNode->_bbox._max)) {
                if(!bvisible) {
                    bvisible = FG_FALSE;
                } else {
                    bvisible = FG_TRUE;
                }
            }
        }
        if(FG_FALSE == bvisible && is3D)
            continue;

        int nCount;
        CPolygon* pPolyh = pNode->getPolygons(nCount);
        for(int i = 0; i < nCount; i++, pPolyh++) {
            if(!bvisible) {
                //                glColor4ubv(CLR_GREY);

                if(is3D) {
                    //p_dlg->gl_3d.DrawPolyVertexes(*pPolyh);
                } else {
                    if((pPolyh)->n.y < .9 && (pPolyh)->n.y>-.9) {
                        //    p_dlg->gl_2d.DrawPolyLines(*pPolyh);
                    }
                }
            } else {
                visibles.push_back(pPolyh);
            }
        }
    }
    {
        CVector<CPolygon*>::iterator end = visibles.end();
        for(CVector<CPolygon*>::iterator it = visibles.begin(); it != end; it++) {
            CPolygon* polygon = *it;
            if(!polygon) {
                continue;
            }
            //glColor4ubv(CLR_WHITE);
            if(is3D) {
                //p_dlg->gl_3d.DrawPolyVertexes(**ppp);

            } else {
                if(polygon->n.y < 0.9f && polygon->n.y>-0.9f) {

                }
                //p_dlg->gl_2d.DrawPolyLines(**ppp);
            }

        }
    }

    //glColor4ubv(CLR_WHITE);
    //TextOut(ST_OUT2, "Vis =%d of %d (%02.2f%%)", visibles.size(), bsp_tree._polys.size(),
    //        (REAL)visibles.size()*100.0 / (REAL)bsp_tree._polys.size());
}

//---------------------------------------------------------------------------------------

void gfx::CBspCompiler::renderPortals(fgBool is3D) {
    ////glDisable(GL_TEXTURE_2D);
    //glColor4ubv(CLR_WHITE);
    ////glEnable(GL_BLEND);
    ////glDisable(GL_DEPTH_TEST);
    ////glDepthMask(0);
    ////glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //int ii = 0;
    CVector<CPortal>::iterator end = m_portalProcesor.m_portals.end();
    CVector<CPortal>::iterator begin = m_portalProcesor.m_portals.begin();
    for(CVector<CPortal>::iterator pPrt = begin; pPrt != end; pPrt++) {
        if(is3D) {
            if(pPrt->m_flags & CPortal::DUPLICATED) {
                //glColor4ubv(CLR_PORTALS1);
            } else {
                //glColor4ubv(CLR_PORTALS);
            }
            //glBegin(GL_POLYGON);
            //FORxEACH(CVector<Vector3f>, pPrt->m_vertexes, pv) {
            //    glVertex3f(pv->x, pv->y, pv->z);
            //}
            //glEnd();
        }

        //glColor4ubv(CLR_PORTALSLINE);
        //glBegin(GL_LINE_LOOP);
        //FORxEACH(CVector<Vector3f>, pPrt->m_vertexes, pv) {
        //    glVertex3f(pv->x, pv->y, pv->z);
        //}
        //glEnd();
    }
    //glColor4ubv(CLR_WHITE);
    ////glDisable(GL_BLEND);
    ////glDepthMask(1);
    ////glEnable(GL_DEPTH_TEST);
    ////if(is3D)
    ////    glEnable(GL_TEXTURE_2D);
}

void gfx::CBspCompiler::clear() {
    m_portalProcesor.clear();
    m_pvsProcesor.clear();
    m_bspTree.clear();
}
