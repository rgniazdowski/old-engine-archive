/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxBspCompiler.h"

#include "GFX/fgGfxStdInc.h"
#include "GFX/fgGfxFrustum.h"
#include "GFX/fgGfxPrimitives.h"

#include "fgColors.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CBspCompiler::CBspCompiler() {
    int count = 64;
    m_visiblePolygons.reserve(count);
    for(int i = 0; i < count; i++) {
        m_visiblePolygons[i] = NULL;
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CBspCompiler::compile(CVector<SPolygon>& polygons, fgBool usethreads) {
    m_usethreads = usethreads;
    m_bspTree.clear();
    m_portalProcessor.clear();
    m_pvsProcessor.clear();
    m_bspTree.setType(CBspTree::BSP_LEAFY);
    if(polygons.empty()) {
        return FG_FALSE;
    }
    m_bspTree.process(polygons);
    if(m_bspTree.m_bspType != CBspTree::BSP_TERRAIN) {
        m_portalProcessor.process(m_bspTree);
        m_pvsProcessor.process(m_bspTree, m_portalProcessor);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

static fgBool Local_IsLeafVisFromLeaf(CVector<gfx::CBspLeaf*>& leafs,
                                      int l1,
                                      int l2,
                                      unsigned char* ppvs) {
    if(l1 < 0 || l2 < 0)return 1;
    unsigned char* pPvs1 = &ppvs[leafs[l1]->m_pvsIdx];
    return (pPvs1[l2 >> 3] & (1 << (l2 & 7))) != 0;
}

//------------------------------------------------------------------------------

void gfx::CBspCompiler::display(const Vector3f& camPos, CFrustum& frustum, fgBool is3D) {
    int curLeaf = m_bspTree.getCurrentLeaf(camPos);
    fgBool isVisible = FG_FALSE;
    //glDisable(GL_BLEND);
    m_visiblePolygons.clear();
    //printf("CURLEAF: %d | %.2f;%.2f;%.2f ", curLeaf, camPos.x, camPos.y, camPos.z);
    // from this leaf check the pvs and render all visible leafs
    CVector<CBspLeaf*>::iterator end = m_bspTree.m_leafs.end();
    for(CVector<CBspLeaf*>::iterator it = m_bspTree.m_leafs.begin(); it != end; it++) {
        CBspLeaf* pNode = *it;
        isVisible = FG_TRUE;
        // if we are in interior of the BSP
        if(curLeaf != -1) {
            if(pNode->m_pvsIdx >= 0 && pNode->m_leafIdx != curLeaf) {
                if(!Local_IsLeafVisFromLeaf(m_bspTree.m_leafs,
                                            pNode->m_leafIdx,
                                            curLeaf,
                                            m_pvsProcessor.m_pvs)) {
                    isVisible = FG_FALSE;
                }
            }

            if(CBspTree::BSP_TERRAIN == m_bspTree.m_bspType || 1) {
                if(!isVisible) {
                    isVisible = !!frustum.testVolume(pNode->m_bbox);
                } else {
                    isVisible = FG_TRUE;
                }
            }
        }
        if(FG_FALSE == isVisible && is3D) {
            continue;
        }
        int nCount;
        SPolygon* pPolyh = pNode->getPolygons(nCount);
        for(int i = 0; i < nCount; i++, pPolyh++) {
            if(!isVisible) {
                gfx::primitives::drawAABBLines(pPolyh->bbox, fg::colors::getColor("red"));
                if(is3D || 1) {
                    // gfx::CPrimitives::drawVertexData(pPolyh->m_vertexData, ATTRIBUTE_POSITION_BIT, gfx::PrimitiveMode::TRIANGLE_STRIP);
                    //p_dlg->gl_3d.DrawPolyVertexes(*pPolyh);
                } else {
                    if((pPolyh)->n.y < .9 && (pPolyh)->n.y>-.9) {
                        //    p_dlg->gl_2d.DrawPolyLines(*pPolyh);
                    }
                }
            } else {
                gfx::primitives::drawAABBLines(pPolyh->bbox, fg::colors::getColor("green"));
                m_visiblePolygons.push_back(pPolyh);
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CBspCompiler::render(void) {
    glDisable(GL_BLEND);
    CVector<SPolygon*>::iterator end = m_visiblePolygons.end();
    for(CVector<SPolygon*>::iterator it = m_visiblePolygons.begin(); it != end; it++) {
        SPolygon* polygon = *it;
        if(!polygon) {
            continue;
        }
        if(1) {            
            gfx::primitives::drawVertexData(polygon->getVertexData(),
                                            ATTRIBUTE_POSITION_BIT,
                                            gfx::PrimitiveMode::TRIANGLE_FAN);
        } else {
            if(polygon->n.y < 0.9f && polygon->n.y>-0.9f) {
                //p_dlg->gl_2d.DrawPolyLines(**ppp);
            }
        }
    }
    //printf("Visible polygons: %d\n", (int)m_visiblePolygons.size());
}
//------------------------------------------------------------------------------

void gfx::CBspCompiler::renderPortals(fgBool is3D) {
    CVector<CPortal>::iterator end = m_portalProcessor.m_portals.end();
    CVector<CPortal>::iterator begin = m_portalProcessor.m_portals.begin();
    for(CVector<CPortal>::iterator pPrt = begin; pPrt != end; pPrt++) {
        if(is3D) {
            if(pPrt->m_flags & CPortal::DUPLICATED) {
                //glColor4ubv(CLR_PORTALS1);
            } else {
                //glColor4ubv(CLR_PORTALS);
            }
            primitives::drawArray(pPrt->m_vertexes, PrimitiveMode::LINE_LOOP);
        }
        //glColor4ubv(CLR_PORTALSLINE);
        //glBegin(GL_LINE_LOOP);
        //FORxEACH(CVector<Vector3f>, pPrt->m_vertexes, pv) {
        //    glVertex3f(pv->x, pv->y, pv->z);
        //}
        //glEnd();
    }
}
//------------------------------------------------------------------------------

void gfx::CBspCompiler::clear(void) {
    m_portalProcessor.clear();
    m_pvsProcessor.clear();
    m_bspTree.clear();
    m_visiblePolygons.clear_optimised();
}
//------------------------------------------------------------------------------
