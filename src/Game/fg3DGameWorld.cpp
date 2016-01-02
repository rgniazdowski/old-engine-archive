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
 * File:   fg3DGameWorld.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 8:00 PM
 */

#include "fg3DGameWorld.h"
#include "Physics/fgPhysical.h"
#include "fgGameEntityType.h"
#include "Util/fgStrings.h"
#if defined(FG_USING_BULLET)
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "fgDebugConfig.h"
#endif

using namespace fg;
//------------------------------------------------------------------------------

game::CGameWorld3D::CGameWorld3D() :
base_type(this),
scene_type() {
    this->setLayerName("game::CGameWorld3D");
    this->setLayerID(12); // ?
    scene_type::setDefaultNodeObjectType(GAME_ENTITY);
    //scene_type::addFromModel()
}
//------------------------------------------------------------------------------

game::CGameWorld3D::CGameWorld3D(const CGameWorld3D& orig) : self_type() {
    // #FIXME
}
//------------------------------------------------------------------------------

game::CGameWorld3D::~CGameWorld3D() {
    self_type::destroy();
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld3D::initialize(void) {
    fgBool status = base_type::initialize();
    status = (fgBool)(scene_type::initialize() && status);

    return status;
}
//------------------------------------------------------------------------------

fgBool game::CGameWorld3D::destroy(void) {
    fgBool status = scene_type::destroy();
    status = (fgBool)(base_type::destroy() && status);

    return status;
}
//------------------------------------------------------------------------------

void game::CGameWorld3D::render(void) {
    scene_type::render();

    // now the default debug shader and MVP are reset
    // just call drawDebugWorld on physics world
#if defined(FG_DEBUG) && defined(FG_USING_BULLET)
    if(base_type::getDynamicsWorld())
        base_type::getDynamicsWorld()->debugDrawWorld();
#endif /* FG_DEBUG */
}
//------------------------------------------------------------------------------

void game::CGameWorld3D::update(float delta) {
    // after sorting calls need to copy model matrix from rigid body to proper
    // game entity node (the ones that have Physical trait).
    // this will happen after update stage from GameWorld (physical & intelligent)
    /// // // // // // // //
    // game world update function - intelligent & physical world
    base_type::update(delta);
    // update function of scene_type calls internal event manager callbacks
    scene_type::update(delta);

    // this copying below should be done at the same rate as sortCalls procedure
    // --- need to fix fps for this: <= 60.0 fps
    // and after successful sortCalls()/preRender()
    // now need to copy matrices from rigid bodies
    // linear traverse - only active nodes (any visibility)
    m_traverse.rewind();
    while(m_traverse.next(getActiveRootNode())) {
        gfx::CSceneNode* pSceneNode = m_traverse.current;
        if(!pSceneNode)
            continue;
        if(pSceneNode->getNodeType() == gfx::SCENE_NODE_ROOT) {
            continue; // skip root nodes
        }
        if(!pSceneNode->isActive()) {
            continue; // skip not active node
        }
        physics::traits::CPhysical* pPhysical = NULL;
        if(pSceneNode->queryTrait(fg::traits::PHYSICAL, (void**)&pPhysical)) {
            if(pPhysical->isRagdoll()) {
                continue;
            }
            if(!pPhysical->getCollisionBody())
                continue; // skip
            physics::CCollisionBody* pBody = pPhysical->getCollisionBody();
            if(!pBody->isActive())
                continue; // skip inactive ??
            if(pBody->isStaticObject())
                continue; // skip static
            // quick copy
            // cant just copy matrix
            // node's model matrix is relative to the parents matrix
            Matrix4f matrix;
            pBody->getWorldTransform(matrix);
            if(pSceneNode->getParent())
                matrix = math::inverse(pSceneNode->getParent()->getFinalModelMatrix()) * matrix;
            // reset the scaling factor?           
            // set the proper (local) model matrix for this node
            pSceneNode->setModelMatrix(matrix);
#if defined(FG_USING_BULLET)
            // #TODO - maybe should use dual quaternions? so just rotation and
            // translation, scaling in separate vector 4+4+3 -> 11 floats
            getDynamicsWorld()->updateSingleAabb(pBody);
#endif
        }
    }
}
//------------------------------------------------------------------------------
