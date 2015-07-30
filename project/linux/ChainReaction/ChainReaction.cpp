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

#include "ChainReaction.h"
#include "CLevelFile.h"
#include "CLevelGenerator.h"

#include "fgVector.h"
#include "fgPluginResource.h"
#include "fgEngineMain.h"
#include "fgColors.h"
#include "fgLog.h"

#include "Util/fgTime.h"
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

    fg::CLevelFile* level = new fg::CLevelFile();
    level->load("ChainReaction/level_hex2.cr");
    unsigned short xSize, ySize;
    unsigned short xAreaMin, yAreaMin;
    unsigned short xAreaMax, yAreaMax;
    unsigned short xAreaSize, yAreaSize;
    level->getSize(xSize, ySize);
    level->getAreaSize(xAreaSize, yAreaSize);
    level->getAreaMin(xAreaMin, yAreaMin);
    level->getAreaMax(xAreaMax, yAreaMax);
    FG_LOG_DEBUG("ChainReaction: Level: size[%dx%d]", xSize, ySize);
    FG_LOG_DEBUG("ChainReaction: Level: area size[%dx%d]", xAreaSize, yAreaSize);
    FG_LOG_DEBUG("ChainReaction: Level: area min[%dx%d]", xAreaMin, yAreaMin);
    FG_LOG_DEBUG("ChainReaction: Level: area max[%dx%d]", xAreaMax, yAreaMax);
    pChainReactionMgr->getLevelVis()->getLevelDataHolder()->setLevelFile(level);
    pChainReactionMgr->refreshLevelMaterials();
    pChainReactionMgr->getLevelVis()->setScale(20.0f);
    pChainReactionMgr->getLevelVis()->restart();

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
    delete pChainReactionMgr->getLevelVis()->getLevelFile();
    pChainReactionMgr->getLevelVis()->getLevelDataHolder()->setLevelFile(NULL);
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
m_levelSolver(NULL),
m_levelDataHolder(NULL),
m_updateCallback(NULL),
m_preRenderCallback(NULL),
m_renderCallback(NULL),
m_touchCallback(NULL),
m_mouseCallback(NULL),
m_drag() {
    this->setEngineMain(pEngineMain);
    m_managerType = FG_MANAGER_CHAIN_REACTION;
    m_drag.invalidate();
    //memset(m_materials, 0, sizeof(m_materials));
    for(unsigned int i = 0; i < VColor::NUM_COLORS; i++) {
        m_materials[0][i] = NULL;
        m_materials[1][i] = NULL;
    }
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
    if(m_levelSolver) {
        delete m_levelSolver;
        m_levelSolver = NULL;
    }
    if(m_levelDataHolder) {
        delete m_levelDataHolder;
        m_levelDataHolder = NULL;
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
    unsigned int n = VColor::NUM_COLORS;
    for(unsigned int j = 0; j < 2; j++) {
        for(unsigned int i = 0; i < n; i++) {
            if(m_materials[j][i] != NULL) {
                delete m_materials[j][i];
            }
            m_materials[j][i] = NULL;
        }
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
    if(m_levelVis)
        delete m_levelVis;
    if(m_levelSolver)
        delete m_levelSolver;
    if(m_levelDataHolder)
        delete m_levelDataHolder;
    m_levelDataHolder = new CLevelDataHolder(m_grid);
    m_levelSolver = new CLevelSolver(m_levelDataHolder);
    m_levelVis = new CLevelVisualization(m_levelSolver);
    m_levelVis->setSceneManager(m_pEngineMain->getGfxMain()->get3DScene());

    unsigned int n = VColor::NUM_COLORS;
    for(unsigned int j = 0; j < 2; j++) {
        for(unsigned int i = 0; i < n; i++) {
            if(m_materials[j][i] != NULL) {
                delete m_materials[j][i];
            }
            m_materials[j][i] = NULL;
        }
    }
    // #FIXME
    const char *texNames[2] = {"quadWhite.jpg", "hexWhite.jpg"};
    const char *colorNames[VColor::NUM_COLORS];
    colorNames[VColor::INVALID_COLOR] = NULL;
    colorNames[VColor::BLACK] = "Black";
    colorNames[VColor::WHITE] = "White";
    colorNames[VColor::GRAY] = "Gray";
    colorNames[VColor::RED] = "Red";
    colorNames[VColor::GREEN] = "Green";
    colorNames[VColor::BLUE] = "Blue";
    colorNames[VColor::CYAN] = "Cyan";
    colorNames[VColor::YELLOW] = "Yellow";
    colorNames[VColor::MAGENTA] = "Magenta";

    // 0 - quad / 1 - hexagon
    for(unsigned int j = 0; j < 2; j++) {
        for(unsigned int i = VColor::BLACK; i < n; i++) {
            float blackOffset = 0.0f;
            if(i == VColor::BLACK)
                blackOffset = 0.15f;
            m_materials[j][i] = new gfx::SMaterial();
            m_materials[j][i]->diffuseTexName = texNames[j];
            m_materials[j][i]->diffuseTex = (gfx::CTextureResource*)m_pEngineMain->getResourceManager()->request(m_materials[j][i]->diffuseTexName);
            m_materials[j][i]->shaderName = "sPlainEasy";
            m_materials[j][i]->diffuse = colors::getColor(colorNames[i]) + blackOffset;
            m_materials[j][i]->customColor = m_materials[j][i]->diffuse;
            m_materials[j][i]->setFrontFace(gfx::FrontFace::FACE_CCW);
            m_materials[j][i]->blendMode = gfx::BlendMode::BLEND_ADDITIVE;
        }
    }
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CChainReaction::refreshLevelMaterials(void) {
    if(!m_levelVis)
        return;
    if(!m_levelVis->getLevelFile())
        return;
    const CLevelFile::LevelType levelType = m_levelVis->getLevelType();
    SBlockData::BlockType blockType = CLevelDataHolder::getBlockTypeFromLevelType(levelType);
    // 0 - quads / 1 - hexagons
    if(blockType != SBlockData::QUAD && blockType != SBlockData::HEXAGON)
        return;
    const unsigned int index = (unsigned int)blockType;
    const unsigned int n = VColor::NUM_COLORS;
    for(unsigned int i = (unsigned int)VColor::BLACK; i < n; i++) {
        if(m_materials[index][i])
            m_levelVis->setMaterial(m_materials[index][i], (VColor)i);
    }
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
    if(released) {
        // reset the rotation - deactivate the drag flag for the node
        fgBool doReset = FG_TRUE;
        if(m_drag.pNode && m_drag.pBlockData) {

            if(m_drag.pBlockData->rotDir == NO_ROTATION)
                doReset = FG_FALSE;

            if(doReset) {
                // need to check for finished rotation
                if(m_drag.pBlockData->isRotationFinished()) {
                    unsigned short x = 0, y = 0;
                    m_drag.pBlockData->getCoveredNeighbourCoord(x, y);
                    SBlockData* pNewBlock = m_levelDataHolder->moveBlockToNewPlace(m_drag.pBlockData, x, y);
                    if(!pNewBlock) {
                        m_levelSolver->getOrphanBlocks().push_back(m_drag.pBlockData);
                        m_levelSolver->setChainReaction();
                        m_levelSolver->setStepOn(FG_TRUE);
                    } else {
                        m_levelSolver->setUserDisturbance(pNewBlock);
                        m_levelSolver->setChainReaction(); // now should animate
                        m_levelSolver->setStepOn(FG_TRUE);
                    }
                    m_drag.pNode = NULL;
                    m_drag.pBlockData = NULL;
                } else {
                    float rotation = m_drag.pBlockData->rotation;
                    m_drag.pBlockData->rotate(OPPOSITE_ROTATION, rotation);
                    m_drag.pBlockData->rotation = 0.0f;
                    m_drag.pBlockData->isDragged = FG_FALSE;
                    m_drag.pBlockData->rotDir = NO_ROTATION;
                }
            }
        }
    }

    if(!pressed || released || m_levelSolver->isChainReaction()) {
        // nothing to do - this is mouse motion without keys pressed
        return;
    }

    if(m_drag.pNode && m_drag.pBlockData) {
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
        if(m_drag.pBlockData->rotDir == NO_ROTATION || 1) {
            // no current rotation - detect
            Vec3f posDiff = m_drag.current - nodePos;
            float lenDiff = 0.0f;
            RotationDirection propRotDir = NO_ROTATION;
            RotationDirection curRotDir = propRotDir;
            //if(posDiff.x > 0.0f && posDiff.y > 0.0f) {}
            // check the relative mouse position ?
            const char *dirStr = NULL;
            if(swipeDir == event::SSwipe::LEFT) {
                // X bigger (more minus) -> LEFT
                propRotDir = DOWN_LEFT;
                dirStr = "LEFT\0";
            } else if(swipeDir == event::SSwipe::RIGHT) {
                // X bigger -> RIGHT
                propRotDir = UP_RIGHT;
                dirStr = "RIGHT\0";
            } else if(swipeDir == event::SSwipe::UP) {
                // Y bigger (more minus) -> UP
                propRotDir = UP_LEFT;
                dirStr = "UP\0";
            } else if(swipeDir == event::SSwipe::DOWN) {
                // Y bigger -> DOWN
                propRotDir = DOWN_RIGHT;
                dirStr = "DOWN\0";
            }

            curRotDir = m_drag.pBlockData->rotDir;
            if(curRotDir == NO_ROTATION) {
                m_drag.pBlockData->rotDir = propRotDir;
                curRotDir = propRotDir;
            }
            if(propRotDir != NO_ROTATION &&
               (propRotDir == curRotDir || m_drag.pBlockData->isOppositeRotation(propRotDir))) {
                float rSteps = 1.0f;
                switch(m_drag.pBlockData->rotDir) {
                    case LEFT:
                        lenDiff = m_drag.current.x - (nodePos.x + scale / 2.0f);
                        rSteps = (float)math::abs(steps.x) * 2.3f;
                        break;
                    case RIGHT:
                        lenDiff = m_drag.current.x - (nodePos.x - scale / 2.0f);
                        rSteps = (float)math::abs(steps.x) * 2.3f; // #FIXME - X res fubar
                        break;
                    case UP:
                        lenDiff = m_drag.current.y - (nodePos.y - scale / 2.0f);
                        rSteps = (float)math::abs(steps.y);
                        break;
                    case DOWN:
                        lenDiff = m_drag.current.y - (nodePos.y + scale / 2.0f);
                        rSteps = (float)math::abs(steps.y);
                        break;
                }
                // some direction is determined
                // now need to determine the difference
                //float angle = math::acos((scale - math::abs(lenDiff)) / scale);
                //float reverse = 1.0f;
                float rotationStep = 0.3f;
                m_drag.pBlockData->rotate(propRotDir, rotationStep * rSteps);
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
    //gfx::CSceneNode* pLastPicked = m_pSceneMgr->getLastPickedNode();
    fgBool isPickerDown = m_pSceneMgr->isPickSelectionPickerActive();
    //
    // Remember that updateStep is called at the end of the update loop step
    // (via event manager) - first called are the event callbacks for mouse,
    // touch or keyboard events.
    //
    if(isPickerDown) {

    }
    float zoomOut = 250.0f;
    float zoomIn = 120.0f;
    m_drag.zoomProp = (zoomOut - zoomIn) / zoomOut;
    if(pPicked && isPickerDown && !m_drag.pNode && !m_levelSolver->isChainReaction()) {
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
            m_drag.pBlockData = (SBlockData *)pCellData;
            m_drag.quadCoord.x = m_drag.pBlockData->pCellHolder->pos.x;
            m_drag.quadCoord.y = m_drag.pBlockData->pCellHolder->pos.y;
            FG_LOG_DEBUG("ChainReaction: Will drag node[%s][%dx%d]", nameStr, m_drag.quadCoord.x, m_drag.quadCoord.y);
            m_levelVis->setDraggedNode(m_drag.pNode);
            m_levelVis->setDraggedCoord(m_drag.quadCoord);
            // mouse / touch handler manages the rotation
            // Vec3f dragPosCenter = pDraggedNode->getPosition3f();
            pCamera->setCenter(m_drag.begin * m_drag.zoomProp);
            pCamera->setEye(Vec3f(m_drag.begin.x * m_drag.zoomProp,
                                  m_drag.begin.y * m_drag.zoomProp,
                                  zoomIn));
            m_drag.isValid = FG_TRUE;
            const float scale = m_levelVis->getScale();
            m_drag.pNode->setScale(scale + 0.05f, scale + 0.05f, 1.5f);
        } else {
            m_drag.pBlockData = NULL;
        }
    } else if(!isPickerDown) {
        if(m_drag.pNode) {
            const float scale = m_levelVis->getScale();
            m_drag.pNode->setScale(scale, scale, 1.0f);
            m_drag.pBlockData->isDragged = FG_FALSE;
        }
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

void CChainReaction::preRenderStep(void) {
    if(!m_pSceneMgr) {
        return;
    }
    // this will animate the quads (if the chain reaction flag is set)
    m_levelVis->preRender();
}
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
    fg::CEngineMain* pEngineMain = info->pEngineMain;
    fg::gfx::CCameraAnimation* pCamera = pEngineMain->getGfxMain()->get3DSceneCamera();
    fg::event::CInputHandler* pInputHandler = pEngineMain->getInputHandler();
    fg::gfx::CSceneNode* pRoot = pEngineMain->getGfxMain()->get3DScene()->getActiveRootNode();
    fg::gfx::CSceneNode::ChildrenVec& children = pRoot->getChildren();
    unsigned int n = pRoot->getChildrenCount();
    float direction = 0.0f;
    fgBool isDown = FG_FALSE;
    fg::RotationDirection rotDir;
    if(pInputHandler->isKeyDown(fg::event::FG_KEY_LEFT)) {
        direction = -1.0f;
        isDown = FG_TRUE;
        rotDir = fg::LEFT;
    } else if(pInputHandler->isKeyDown(fg::event::FG_KEY_RIGHT)) {
        direction = 1.0f;
        isDown = FG_TRUE;
        rotDir = fg::RIGHT;
    } else if(pInputHandler->isKeyDown(fg::event::FG_KEY_UP)) {
        isDown = FG_TRUE;
        rotDir = fg::UP;
    } else if(pInputHandler->isKeyDown(fg::event::FG_KEY_DOWN)) {
        isDown = FG_TRUE;
        rotDir = fg::DOWN;
    }
    static int restart = 0;
    if(!restart && pInputHandler->isKeyDown(fg::event::FG_KEY_R)) {
        restart++;
        pChainReaction->getLevelVis()->restart();
    }
    if(pInputHandler->isKeyUp(fg::event::FG_KEY_R)) {
        restart = 0;
    }

    static int stepOn = 0;
    if(!stepOn && pInputHandler->isKeyDown(fg::event::FG_KEY_SPACE)) {
        stepOn++;
        pChainReaction->getLevelSolver()->setStepOn(FG_TRUE);
    }
    if(pInputHandler->isKeyUp(fg::event::FG_KEY_SPACE)) {
        stepOn = 0;
        //pChainReaction->getLevelVis()->setStepping(FG_TRUE);
    }

    if(isDown) {
        if(pChainReaction->m_drag.pBlockData) {
            pChainReaction->m_drag.pBlockData->rotate(rotDir, 0.1f);
        }
    }
    pChainReaction->getLevelVis()->setSpeed(2.0f);
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
pBlockData(NULL),
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
    pBlockData = NULL;
    pNode = NULL;
}
//------------------------------------------------------------------------------
