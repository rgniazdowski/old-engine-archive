/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGameWorld.cpp
 * Author: vigilant
 * 
 * Created on September 24, 2015, 4:59 PM
 */

#include "fgGameWorld.h"
#include "GFX/Scene/fgGfxSceneManager.h"
#include "Physics/fgPhysical.h"

#if defined(FG_USING_BULLET)
#include "GFX/fgGfxColor.h"
#include "LinearMath/btIDebugDraw.h"
#endif /* FG_USING_BULLET */

//------------------------------------------------------------------------------
namespace fg {
#if defined(FG_USING_BULLET)

    /**
     *
     */
    struct SPhysicsDebugDrawer : public btIDebugDraw
    {
        typedef btIDebugDraw base_type;
        typedef SPhysicsDebugDrawer self_type;
        ///
        static const unsigned int BT_LINE_BATCH_SIZE = 256;
        ///
        DefaultColors debugColors;
        ///
        CVector<Vector3f> positions;
        ///
        CVector<Color4f> colors;
        ///
        int debugMode;
        ///
        btVector3 currentColor;

        SPhysicsDebugDrawer() :
        debugColors(),
        positions(),
        colors(),
        debugMode(DBG_NoHelpText |
                  DBG_DrawConstraintLimits |
                  DBG_DrawConstraints),
        currentColor(-1, -1, -1) {
            positions.reserve(64);
            colors.reserve(64);
        }

        virtual ~SPhysicsDebugDrawer() {
            positions.clear();
            colors.clear();
        }

        virtual DefaultColors getDefaultColors() const {
            return debugColors;
        }

        virtual void setDefaultColors(const DefaultColors& colors) {
            debugColors = colors;
        }

        virtual void drawLine(const btVector3& from,
                              const btVector3& to,
                              const btVector3& color) {
            if(positions.size() >= BT_LINE_BATCH_SIZE) {
                flushLines();
                currentColor = color;
            }
            positions.push_back(Vec3f(from.getX(), from.getY(), from.getZ()));
            positions.push_back(Vec3f(to.getX(), to.getY(), to.getZ()));
            // colors are quite heavy - but this is special debug mode
            colors.push_back(Color4f(color.getX(), color.getY(), color.getZ(), 1.0f));
            colors.push_back(Color4f(color.getX(), color.getY(), color.getZ(), 1.0f));
        }

        virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
            drawLine(PointOnB, PointOnB + normalOnB, color);
        }

        virtual void reportErrorWarning(const char* warningString) { }

        virtual void draw3dText(const btVector3& location, const char* textString) { }

        virtual void setDebugMode(int _debugMode) {
            debugMode = _debugMode;
        }

        virtual int getDebugMode() const {
            return debugMode;
        }

        virtual void flushLines() {
            const unsigned int cnt = positions.size();
            if(!cnt)
                return;

            gfx::primitives::drawLines(positions, colors);

            positions.clear();
            colors.clear();
        }
    }; // struct SDebugDrawer

#else 

    struct SPhysicsDebugDrawer
    {
    }; // struct SPhysicsDebugDrawer
#endif
} // namespace fg

#if defined(FG_USING_BULLET)
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#endif
//------------------------------------------------------------------------------

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld(gfx::CSceneManager* pSceneMgr) :
base_type(),
physical_world(),
m_pSceneMgr(pSceneMgr),
m_sceneNodeInsertedCallback(NULL),
m_debugDrawer(NULL) {
    m_debugDrawer = new SPhysicsDebugDrawer();
}
//------------------------------------------------------------------------------

game::CGameWorld::CGameWorld(const CGameWorld& orig) : self_type(orig.m_pSceneMgr) {
    // #FIXME
}
//------------------------------------------------------------------------------

game::CGameWorld::~CGameWorld() { }
//------------------------------------------------------------------------------

fgBool game::CGameWorld::initialize(void) {
    fgBool status = base_type::initialize();
    status = (fgBool)(physical_world::initialize() && status);
    if(physical_world::getDynamicsWorld()) {
        physical_world::getDynamicsWorld()->setDebugDrawer(m_debugDrawer);
    }
    registerCallbacks();
    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld::destroy(void) {
    fgBool status = base_type::destroy();
    if(physical_world::getDynamicsWorld()) {
        physical_world::getDynamicsWorld()->setDebugDrawer(NULL);
    }
    status = (fgBool)(physical_world::destroy() && status);
    unregisterCallbacks();
    m_pSceneMgr = NULL;
    if(m_debugDrawer) {
        delete m_debugDrawer;
    }
    m_debugDrawer = NULL;
    return status;
}
//------------------------------------------------------------------------------

void game::CGameWorld::update(float delta) {
    base_type::update(delta); // intelligent world

    physical_world::update(delta); // #FIXME
}
//------------------------------------------------------------------------------

gfx::CSceneManager* game::CGameWorld::getSceneManager(void) const {
    return m_pSceneMgr;
}
//------------------------------------------------------------------------------

void game::CGameWorld::registerCallbacks(void) {
    if(!m_pSceneMgr)
        return;

    if(!m_sceneNodeInsertedCallback) {
        m_sceneNodeInsertedCallback =
                new event::CMethodCallback<self_type>(this,
                                                      &self_type::sceneNodeInsertedHandler);
    }

    m_pSceneMgr->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED,
                                                        m_sceneNodeInsertedCallback);

    //m_pSceneMgr->getInternalEventManager()->addCallback(event::SCENE_NODE_DESTROYED)
}
//------------------------------------------------------------------------------

void game::CGameWorld::unregisterCallbacks(void) {
    if(!m_pSceneMgr)
        return;

}
//------------------------------------------------------------------------------

fgBool game::CGameWorld::sceneNodeInsertedHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SSceneEvent* pEventStruct = (event::SSceneEvent*)argv->getValueByID(0);
    gfx::CSceneManager* pSceneManager = (gfx::CSceneManager*)argv->getValueByID(1);
    if(!pEventStruct)
        return FG_FALSE;
    event::EventType type = pEventStruct->code;
    if(type != event::SCENE_NODE_INSERTED)
        return FG_FALSE;
    if(!pSceneManager) {
        return FG_FALSE;
    }
    if(!pSceneManager->isManaged(pEventStruct->node.handleNodeA)) {
        return FG_FALSE;
    }
    if(!pEventStruct->node.pNodeA) {
        return FG_FALSE;
    }
    // Now this callback is for automated adding nodes with physical traits
    // to the physical world
    physics::traits::CPhysical* pPhysical = NULL;
    fgBool status = FG_FALSE;
    if(pEventStruct->node.pNodeA->queryTrait(fg::traits::PHYSICAL, (void**)&pPhysical)) {
        if(pPhysical->isRagdoll()) {
            physical_world::setupOwnerFor(pPhysical->getAbstractCollisionBody());
            status = FG_TRUE;
        } else if(pPhysical->hasCollisionBody()) {
            physical_world::add(pPhysical->getCollisionBody());
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------
