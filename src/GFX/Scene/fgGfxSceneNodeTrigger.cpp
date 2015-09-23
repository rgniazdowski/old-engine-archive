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
 * File:   fgGFXSceneNodeTrigger.cpp
 * Author: vigilant
 * 
 * Created on February 18, 2015, 10:34 PM
 */

#include "fgGfxSceneNodeTrigger.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::CSceneNodeTrigger() :
base_type(SCENE_NODE_TRIGGER),
triggerable_type() {
    this->setNodeTrait(triggerable_type::SELF_TRAIT);
    this->setNodeTypeMask(SCENE_NODE_TRIGGER);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::CSceneNodeTrigger(const CSceneNodeTrigger& orig) :
base_type(orig),
triggerable_type(orig) {
    this->setNodeTrait(triggerable_type::SELF_TRAIT);
    this->setNodeTypeMask(SCENE_NODE_TRIGGER);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::~CSceneNodeTrigger() { }
//------------------------------------------------------------------------------

fgBool gfx::CSceneNodeTrigger::queryTrait(const traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & traits::TRIGGERABLE) {
            *pObj = static_cast<traits::CTriggerable*>(this);
        }
    } else {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeTrigger::setPosition(const Vec3f& position) {
    base_type::setPosition(position);
    //m_aabb.center = position;
    //m_aabb.extent;
    m_aabb.min = position - m_aabb.extent;
    m_aabb.max = position + m_aabb.extent;
    m_aabb.refresh();

}
//------------------------------------------------------------------------------

void gfx::CSceneNodeTrigger::setPosition(float x, float y, float z) {
    const Vector3f pos(x, y, z);
    base_type::setPosition(pos);
    m_aabb.min = pos - m_aabb.extent;
    m_aabb.max = pos + m_aabb.extent;
    m_aabb.refresh();
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeTrigger::translate(const Vec3f& translation) {
    //m_modelMat = math::translate(m_modelMat, translation);
    m_modelMat[3].x += translation.x;
    m_modelMat[3].y += translation.y;
    m_modelMat[3].z += translation.z;
    m_aabb.min += translation;
    m_aabb.max += translation;
    m_aabb.refresh();
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeTrigger::translate(float x, float y, float z) {
    m_modelMat[3].x += x;
    m_modelMat[3].y += y;
    m_modelMat[3].z += z;
    m_aabb.min.x += x;
    m_aabb.min.y += y;
    m_aabb.min.z += z;
    m_aabb.max.x += x;
    m_aabb.max.y += y;
    m_aabb.max.z += z;
    m_aabb.refresh();
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeTrigger::setScale(const Vector3f& scale) {
    const Vector4f translation = m_modelMat[3];
    m_modelMat = math::scale(m_modelMat, scale / m_scale);
    m_aabb.extent *= scale / m_scale;
    m_aabb.min = m_aabb.center - m_aabb.extent;
    m_aabb.max = m_aabb.center + m_aabb.extent;
    m_aabb.refresh();
    m_aabb.radius = math::length(m_aabb.extent);
    m_scale = scale;
    m_modelMat[3].x = translation.x;
    m_modelMat[3].y = translation.y;
    m_modelMat[3].z = translation.z;

}
//------------------------------------------------------------------------------
