/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgBuildConfig.h"
#include "fgDebugConfig.h"
#include "fgLog.h"

#include "ChainReaction.h"
#include "CLevelFile.h"

#include "fgPluginResource.h"
#include "fgEngineMain.h"

#include "Event/fgCallback.h"
#include "Event/fgEventManager.h"
#include "GameLogic/fgGameMain.h"
#include "GameLogic/fgGrid.h"
#include "GFX/Scene/fgGfx3DScene.h"
#include "GFX/fgGfxMain.h"

#include "Math/fgMathLib.h"

extern "C" {
    fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
    fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
}
//------------------------------------------------------------------------------

fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pEngineMain) {
        return FG_FALSE;
    }

    fg::CChainReaction* pChainReactionMgr = new fg::CChainReaction(info->pEngineMain, info);
    if(!pChainReactionMgr) {
        return FG_FALSE;
    }

    info->pPluginData = (void *)pChainReactionMgr;

    if(!pChainReactionMgr->initialize()) {
        info->pPluginData = NULL;
        delete pChainReactionMgr;
        pChainReactionMgr = NULL;
        return FG_FALSE;
    }

    FG_LOG_DEBUG("ChainReaction: Initialized successfully!");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pEngineMain) {
        return FG_FALSE;
    }

    if(!info->pPluginData) {
        return FG_FALSE;
    }

    fg::CChainReaction* pChainReactionMgr = (fg::CChainReaction*) info->pPluginData;
    delete pChainReactionMgr;
    pChainReactionMgr = NULL;
    info->pPluginData = NULL;

    FG_LOG_DEBUG("ChainReaction: Plugin closed successfully!");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

using namespace fg;

//------------------------------------------------------------------------------

CChainReaction::CChainReaction(CEngineMain* pEngineMain,
                               CPluginResource::SInternalInfo* pPluginInfo) :
m_pPluginInfo(pPluginInfo),
m_pEngineMain(pEngineMain),
m_pGfxMain(NULL),
m_pSceneMgr(NULL),
m_pGameMain(NULL),
m_grid(NULL),
m_levelVis(NULL),
m_updateCallback(NULL),
m_preRenderCallback(NULL),
m_renderCallback(NULL),
m_touchCallback(NULL),
m_mouseCallback(NULL),
m_materialBlack(NULL),
m_materialWhite(NULL),
m_drag() {
    this->setEngineMain(pEngineMain);
    m_managerType = FG_MANAGER_CHAIN_REACTION;
    m_drag.invalidate();
}
//------------------------------------------------------------------------------

CChainReaction::~CChainReaction() {
    destroy();
}
//------------------------------------------------------------------------------

void CChainReaction::clear(void) {
    m_managerType = FG_MANAGER_CHAIN_REACTION;
    m_init = FG_FALSE;
    m_grid = NULL;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::destroy(void) {
    m_init = FG_FALSE;
    unregisterCallbacks();
    if(m_levelVis) {
        delete m_levelVis;
        m_levelVis = NULL;
    }
    if(m_grid) {
        delete m_grid;
        m_grid = NULL;
    }
    if(m_updateCallback) {
        delete m_updateCallback;
        m_updateCallback = NULL;
    }
    if(m_preRenderCallback) {
        delete m_preRenderCallback;
        m_preRenderCallback = NULL;
    }
    if(m_renderCallback) {
        delete m_renderCallback;
        m_renderCallback = NULL;
    }
    if(m_touchCallback) {
        delete m_touchCallback;
        m_touchCallback = NULL;
    }
    if(m_mouseCallback) {
        delete m_mouseCallback;
        m_mouseCallback = NULL;
    }
    if(m_materialBlack) {
        delete m_materialBlack;
        m_materialBlack = NULL;
    }
    if(m_materialWhite) {
        delete m_materialWhite;
        m_materialWhite = NULL;
    }
    m_pEngineMain = NULL;
    m_pGfxMain = NULL;
    m_pGameMain = NULL;
    m_pSceneMgr = NULL;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::initialize(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return FG_FALSE;
    }
    if(!m_init) {
        registerCallbacks();
    }
    if(m_grid)
        delete m_grid;
    m_grid = new game::CGrid(game::CGrid::TWO_DIMENSIONAL);
    m_grid->setMaxSize(48, 48);
    m_grid->reserve(48, 48);
    m_levelVis = new CLevelVis(m_grid);
    m_levelVis->setSceneManager(m_pEngineMain->getGfxMain()->get3DScene());

    if(m_materialWhite)
        delete m_materialWhite;
    if(m_materialBlack)
        delete m_materialBlack;
    m_materialWhite = new gfx::SMaterial();
    m_materialBlack = new gfx::SMaterial();

    m_materialBlack->diffuseTexName = "qWhite.jpg"; // qBlack.jpg ?
    m_materialBlack->diffuseTex = (gfx::CTextureResource*)m_pEngineMain->getResourceManager()->request(m_materialBlack->diffuseTexName);
    m_materialBlack->shaderName = "sPlainEasy";
    m_materialBlack->diffuse = Color4f(0.15f, 0.15f, 0.15f, 1.0f);
    m_materialBlack->customColor = Color4f(0.15f, 0.15f, 0.15f, 1.0f);
    m_materialBlack->setFrontFace(gfx::FrontFace::FACE_CCW);
    //m_materialBlack->setDepthTest(FG_FALSE);
    //m_materialBlack->setCullFace(FG_FALSE);
    //m_materialBlack->blendMode = gfx::BlendMode::BLEND_ADDITIVE;

    m_materialWhite->diffuseTexName = "qWhite.jpg";
    m_materialWhite->diffuseTex = (gfx::CTextureResource*)m_pEngineMain->getResourceManager()->request(m_materialWhite->diffuseTexName);
    m_materialWhite->shaderName = "sPlainEasy";
    m_materialWhite->diffuse = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    m_materialWhite->customColor = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
    m_materialWhite->setFrontFace(gfx::FrontFace::FACE_CCW);
    //m_materialWhite->setDepthTest(FG_FALSE);
    //m_materialWhite->setCullFace(FG_FALSE);
    //m_materialWhite->blendMode = gfx::BlendMode::BLEND_ADDITIVE;

    m_levelVis->setMaterialBlack(m_materialBlack);
    m_levelVis->setMaterialWhite(m_materialWhite);

    //    m_pEngineMain->getGfxMain()->get3DSceneCamera()->setEye(Vector3f(0.0f, 0.0f, -200.0f));
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CChainReaction::setEngineMain(::fg::CEngineMain* pEngineMain) {
    m_pEngineMain = pEngineMain;
    if(m_pEngineMain) {
        if(m_levelVis) {
            m_levelVis->setSceneManager(m_pEngineMain->getGfxMain()->get3DScene());
        }
        m_pGfxMain = m_pEngineMain->getGfxMain();
        m_pSceneMgr = m_pEngineMain->getGfxMain()->get3DScene();
        m_pGameMain = m_pEngineMain->getGameMain();
    }
}
//------------------------------------------------------------------------------

void CChainReaction::registerCallbacks(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return;
    }

    if(!m_updateCallback)
        m_updateCallback = new event::CPlainFunctionCallback(&self_type::updateHandler,
                                                             (void*)m_pPluginInfo);

    if(!m_preRenderCallback)
        m_preRenderCallback = new event::CPlainFunctionCallback(&self_type::preRenderHandler,
                                                                (void*)m_pPluginInfo);

    if(!m_renderCallback)
        m_renderCallback = new event::CPlainFunctionCallback(&self_type::renderHandler,
                                                             (void*)m_pPluginInfo);

    if(!m_touchCallback)
        m_touchCallback = new event::CMethodCallback<CChainReaction>(this, &self_type::touchHandler);

    if(!m_mouseCallback)
        m_mouseCallback = new event::CMethodCallback<CChainReaction>(this, &self_type::mouseHandler);

    m_pEngineMain->addCallback(event::UPDATE_SHOT, m_updateCallback);
    m_pEngineMain->addCallback(event::PRERENDER_SHOT, m_preRenderCallback);
    m_pEngineMain->addCallback(event::RENDER_SHOT, m_renderCallback);

    m_pEngineMain->addCallback(event::TOUCH_MOTION, m_touchCallback);
    m_pEngineMain->addCallback(event::TOUCH_PRESSED, m_touchCallback);
    m_pEngineMain->addCallback(event::TOUCH_RELEASED, m_touchCallback);
    m_pEngineMain->addCallback(event::TOUCH_TAP_FINISHED, m_touchCallback);

    m_pEngineMain->addCallback(event::MOUSE_MOTION, m_mouseCallback);
    m_pEngineMain->addCallback(event::MOUSE_PRESSED, m_mouseCallback);
    m_pEngineMain->addCallback(event::MOUSE_RELEASED, m_mouseCallback);
    m_pEngineMain->addCallback(event::MOUSE_TAP_FINISHED, m_mouseCallback);

    m_pEngineMain->addCallback(event::SWIPE_X, m_mouseCallback);
    m_pEngineMain->addCallback(event::SWIPE_Y, m_mouseCallback);
}
//------------------------------------------------------------------------------

void CChainReaction::unregisterCallbacks(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return;
    }

    m_pEngineMain->removeCallback(event::UPDATE_SHOT, m_updateCallback);
    m_pEngineMain->removeCallback(event::PRERENDER_SHOT, m_preRenderCallback);
    m_pEngineMain->removeCallback(event::RENDER_SHOT, m_renderCallback);

    m_pEngineMain->removeCallback(event::TOUCH_MOTION, m_touchCallback);
    m_pEngineMain->removeCallback(event::TOUCH_PRESSED, m_touchCallback);
    m_pEngineMain->removeCallback(event::TOUCH_RELEASED, m_touchCallback);
    m_pEngineMain->removeCallback(event::TOUCH_TAP_FINISHED, m_touchCallback);

    m_pEngineMain->removeCallback(event::MOUSE_MOTION, m_mouseCallback);
    m_pEngineMain->removeCallback(event::MOUSE_PRESSED, m_mouseCallback);
    m_pEngineMain->removeCallback(event::MOUSE_RELEASED, m_mouseCallback);
    m_pEngineMain->removeCallback(event::MOUSE_TAP_FINISHED, m_mouseCallback);

    m_pEngineMain->removeCallback(event::SWIPE_X, m_mouseCallback);
    m_pEngineMain->removeCallback(event::SWIPE_Y, m_mouseCallback);
}
//------------------------------------------------------------------------------

fgBool CChainReaction::touchHandler(event::CArgumentList *argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent *pEvent = (event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::EventType type = pEvent->code;
    if(!m_pEngineMain)
        return FG_FALSE;

    event::STouch *touch = (event::STouch *)pEvent;
    if(type == event::TOUCH_MOTION) {
        //dragHandler(Vec2i(touch->x, touch->y),
        //Vec2i(touch->relX, touch->relY),
        //touch->pressed, FG_FALSE, touch->touchID);
    } else if(type == event::TOUCH_PRESSED) {
        dragHandler(event::SSwipe::INVALID,
                    Vec2i(touch->x, touch->y),
                    Vec2i(touch->x, touch->y),
                    Vec2i(0, 0),
                    FG_TRUE, FG_FALSE, touch->touchID);
    } else if(type == event::TOUCH_RELEASED) {
        dragHandler(event::SSwipe::INVALID,
                    Vec2i(touch->x, touch->y),
                    Vec2i(touch->x, touch->y),
                    Vec2i(0, 0),
                    FG_FALSE, FG_TRUE, touch->touchID);
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::mouseHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::EventType type = pEvent->code;
    if(!m_pEngineMain)
        return FG_FALSE;
    event::SMouse* mouse = (event::SMouse*)pEvent;

    if(type == event::MOUSE_MOTION) {
        /*dragHandler(Vec2i(mouse->x, mouse->y),
                    Vec2i(mouse->relX, mouse->relY),
                    mouse->pressed, FG_FALSE, mouse->buttonID);*/
    } else if(type == event::MOUSE_PRESSED) {
        dragHandler(event::SSwipe::INVALID,
                    Vec2i(mouse->x, mouse->y),
                    Vec2i(mouse->x, mouse->y),
                    Vec2i(0, 0),
                    FG_TRUE, FG_FALSE, mouse->buttonID);
    } else if(type == event::MOUSE_RELEASED) {
        dragHandler(event::SSwipe::INVALID,
                    Vec2i(mouse->x, mouse->y),
                    Vec2i(mouse->x, mouse->y),
                    Vec2i(0, 0),
                    FG_FALSE, FG_TRUE, mouse->buttonID);
    } else if(type == event::SWIPE_X || type == event::SWIPE_Y) {
        event::SSwipe* swipe = (event::SSwipe*)pEvent;

        dragHandler(swipe->swipeDirection,
                    Vec2i(swipe->xStart, swipe->yStart),
                    Vec2i(swipe->xEnd, swipe->yEnd),
                    Vec2i(swipe->swipeXSteps, swipe->swipeYSteps),
                    FG_TRUE, FG_FALSE, 0);
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CChainReaction::dragHandler(event::SSwipe::Direction swipeDir,
                                 const Vec2i& pos, const Vec2i& end,
                                 const Vec2i& steps, fgBool pressed,
                                 fgBool released, unsigned int id) {
    if(!m_pEngineMain)
        return;
    Vec3f translationAxis;
    Vec3f rotationAxis;
    if(released) {
        // reset the rotation - deactivate the drag flag for the node
        fgBool doReset = FG_TRUE;
        if(m_drag.pNode && m_drag.pQuadData) {

            switch(m_drag.pQuadData->rotDir) {
                case SQuadData::LEFT:
                    translationAxis.x = -QUAD_HALF_SIZE;
                    rotationAxis.y = -1.0f;
                    break;
                case SQuadData::RIGHT:
                    translationAxis.x = QUAD_HALF_SIZE;
                    rotationAxis.y = 1.0f;
                    break;
                case SQuadData::UP:
                    translationAxis.y = QUAD_HALF_SIZE;
                    rotationAxis.x = -1.0f;
                    break;
                case SQuadData::DOWN:
                    translationAxis.y = -QUAD_HALF_SIZE;
                    rotationAxis.x = 1.0f;
                    break;
                default:
                    doReset = FG_FALSE;
            }            
            if(doReset) {
                float rotation = m_drag.pQuadData->rotation;
                m_drag.pNode->translateMatrix(translationAxis);
                m_drag.pNode->rotate(-rotation, rotationAxis);
                m_drag.pNode->translateMatrix(-1.0f * translationAxis);

                m_drag.pQuadData->rotation = 0.0f;
                m_drag.pQuadData->isDragged = FG_FALSE;
                m_drag.pQuadData->rotDir = SQuadData::STATIC;
            }
        }
    }

    if(!pressed || released) {
        // nothing to do - this is mouse motion without keys pressed
        return;
    }

    if(m_drag.pNode && m_drag.pQuadData) {
        // now can rotate based on m_drag difference and length
        float scale = m_levelVis->getScale();
        Vec3f nodePos = m_drag.pNode->getPosition3f();
        // need to check whether or not the pointer is still over dragged node
        gfx::CSceneNode* pPicked = m_pSceneMgr->getCurrentPickedNode();
        if(m_drag.pNode != pPicked) {
            // nothing to do?
            //return;
        }
        // mouse/touch is hovering over the dragged node
        // need to detect drag direction and rotate accordingly
        if(m_drag.pQuadData->rotDir == SQuadData::STATIC || 1) {
            // no current rotation - detect
            Vec3f posDiff = m_drag.current - nodePos;
            float lenDiff = 0.0f;
            SQuadData::RotationDirection propRotDir = SQuadData::STATIC;
            SQuadData::RotationDirection curRotDir = propRotDir;
            //if(posDiff.x > 0.0f && posDiff.y > 0.0f) {}
            // check the relative mouse position ?
            const char *dirStr = NULL;
            if(swipeDir == event::SSwipe::LEFT) {
                // X bigger (more minus) -> LEFT
                propRotDir = SQuadData::LEFT;
                translationAxis.x = -QUAD_HALF_SIZE;
                rotationAxis.y = -1.0f;
                dirStr = "LEFT\0";
            } else if(swipeDir == event::SSwipe::RIGHT) {
                // X bigger -> RIGHT
                propRotDir = SQuadData::RIGHT;
                translationAxis.x = QUAD_HALF_SIZE;
                rotationAxis.y = 1.0f;
                dirStr = "RIGHT\0";
            } else if(swipeDir == event::SSwipe::UP) {
                // Y bigger (more minus) -> UP
                propRotDir = SQuadData::UP;
                translationAxis.y = QUAD_HALF_SIZE;
                rotationAxis.x = -1.0f;
                dirStr = "UP\0";
            } else if(swipeDir == event::SSwipe::DOWN) {
                // Y bigger -> DOWN
                propRotDir = SQuadData::DOWN;
                translationAxis.y = -QUAD_HALF_SIZE;
                rotationAxis.x = 1.0f;
                dirStr = "DOWN\0";
            }

            curRotDir = m_drag.pQuadData->rotDir;
            if(curRotDir == SQuadData::STATIC) {
                m_drag.pQuadData->rotDir = propRotDir;
                curRotDir = propRotDir;
            }
            if(propRotDir != SQuadData::STATIC &&
               (propRotDir == curRotDir || m_drag.pQuadData->isOppositeRotation(propRotDir))) {
                float rSteps = 1.0f;
                switch(m_drag.pQuadData->rotDir) {
                    case SQuadData::LEFT:
                        lenDiff = m_drag.current.x - (nodePos.x + scale / 2.0f);
                        rSteps = (float)math::abs(steps.x) * 2.3f;
                        break;
                    case SQuadData::RIGHT:
                        lenDiff = m_drag.current.x - (nodePos.x - scale / 2.0f);
                        rSteps = (float)math::abs(steps.x) * 2.3f; // #FIXME - X res fubar
                        break;
                    case SQuadData::UP:
                        lenDiff = m_drag.current.y - (nodePos.y - scale / 2.0f);
                        rSteps = (float)math::abs(steps.y);
                        break;
                    case SQuadData::DOWN:
                        lenDiff = m_drag.current.y - (nodePos.y + scale / 2.0f);
                        rSteps = (float)math::abs(steps.y);
                        break;
                }
                // some direction is determined
                // now need to determine the difference
                float angle = math::acos((scale - math::abs(lenDiff)) / scale);
                float reverse = 1.0f;
                float rotationStep = 0.1f;
                if(m_drag.pQuadData->isOppositeRotation(propRotDir))
                    reverse = -1.0f;
                m_drag.pNode->translateMatrix(reverse * translationAxis);
                //m_drag.pNode->rotate(m_drag.pQuadData->rotation * -1.0f, rotationAxis);
                //m_drag.pNode->rotate(angle, rotationAxis);
                m_drag.pNode->rotate(rotationStep * reverse * rSteps, reverse * rotationAxis);
                m_drag.pNode->translateMatrix(-1.0f * translationAxis * reverse);

                m_drag.pQuadData->rotation += rotationStep * reverse * rSteps;
            }
        }
    }
}
//------------------------------------------------------------------------------

void CChainReaction::updateStep(void) {
    if(!m_pSceneMgr) {
        return;
    }
    gfx::CSceneNode* pPicked = m_pSceneMgr->getCurrentPickedNode();
    gfx::CCameraAnimation* pCamera = m_pSceneMgr->getCamera();
    gfx::CSceneNode* pLastPicked = m_pSceneMgr->getLastPickedNode();
    fgBool isPickerDown = m_pSceneMgr->isPickSelectionPickerActive();

    if(isPickerDown) {

    }
    float zoomOut = 250.0f;
    float zoomIn = 100.0f;
    m_drag.zoomProp = (zoomOut - zoomIn) / zoomOut;
    if(pPicked && isPickerDown && !m_drag.pNode) {
        m_drag.begin = m_pSceneMgr->getGroundIntersectionPoint(1);
        //printf("BEGIN: %.2f %.2f %.2f | END: %.2f %.2f %.2f\n",
        //intP0.x, intP0.y, intP0.z,
        //intP1.x, intP1.y, intP0.z);
        m_drag.pNode = pPicked;
        const char* nameStr = m_drag.pNode->getNameStr();
        unsigned int x = 0, y = 0;
        // #FIXME
        std::sscanf(nameStr, "cr_node_%dx%d", &x, &y);
        void *pCellData = m_grid->getCellData((unsigned short)x, (unsigned short)y);
        if(pCellData) {
            m_drag.pQuadData = (SQuadData *)pCellData;
            m_drag.quadCoord.x = m_drag.pQuadData->pCellHolder->pos.x;
            m_drag.quadCoord.y = m_drag.pQuadData->pCellHolder->pos.y;
            m_levelVis->setDraggedNode(m_drag.pNode);
            m_levelVis->setDraggedCoord(m_drag.quadCoord);
            // mouse / touch handler manages the rotation
            // Vec3f dragPosCenter = pDraggedNode->getPosition3f();
            pCamera->setCenter(m_drag.begin * m_drag.zoomProp);
            pCamera->setEye(Vec3f(m_drag.begin.x * m_drag.zoomProp,
                                  m_drag.begin.y * m_drag.zoomProp,
                                  zoomIn));
            m_drag.isValid = FG_TRUE;
        } else {
            m_drag.pQuadData = NULL;
        }
    } else if(!isPickerDown) {
        m_levelVis->setDraggedNode(NULL);
        m_levelVis->setDraggedCoord(0, 0);
        pCamera->setCenter(Vec3f(0.0f, 0.0f, 0.0f));
        pCamera->setEye(Vec3f(0.0f, 0.0f, zoomOut)); // #FIXME

        m_drag.invalidate();
    }
    if(isPickerDown && m_drag.pNode) {

        m_drag.current = m_pSceneMgr->getGroundIntersectionPoint(1);
        m_drag.length = math::length(m_drag.current - m_drag.begin);
        //Vec3f intP1 = m_pSceneMgr->getGroundIntersectionPoint(1);
        //pCamera->setCenter(intP1 * 0.6f);
        //pCamera->setEye(Vec3f(intP1.x * 0.6f, intP1.y * 0.6f, 100.0f));
    }
}
//------------------------------------------------------------------------------

void CChainReaction::preRenderStep(void) { }
//------------------------------------------------------------------------------

void CChainReaction::renderStep(void) { }
//------------------------------------------------------------------------------

fgBool CChainReaction::updateHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;
    fg::CChainReaction* pChainReaction = (fg::CChainReaction*)info->pPluginData;
    if(pChainReaction) {
        pChainReaction->updateStep();
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::preRenderHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;
    fg::CChainReaction* pChainReaction = (fg::CChainReaction*)info->pPluginData;
    if(pChainReaction) {
        pChainReaction->preRenderStep();
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::renderHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;
    fg::CChainReaction* pChainReaction = (fg::CChainReaction*)info->pPluginData;
    if(pChainReaction) {
        pChainReaction->renderStep();
    } else {
        return FG_FALSE;
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

CChainReaction::SDragging::SDragging() :
begin(),
current(),
length(0.0f),
quadCoord(),
isValid(FG_FALSE),
zoomProp(1.0f),
pQuadData(NULL),
pNode(NULL) { }
//------------------------------------------------------------------------------

CChainReaction::SDragging::~SDragging() {

    invalidate();
}
//------------------------------------------------------------------------------

void CChainReaction::SDragging::invalidate(void) {
    begin = Vec3f();
    current = Vec3f();
    length = 0.0f;
    quadCoord = Vec2i();
    isValid = FG_FALSE;
    zoomProp = 1.0f;
    pQuadData = NULL;
    pNode = NULL;
}
//------------------------------------------------------------------------------
