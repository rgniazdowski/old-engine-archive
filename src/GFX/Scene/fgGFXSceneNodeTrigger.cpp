/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSceneNodeTrigger.cpp
 * Author: vigilant
 * 
 * Created on February 18, 2015, 10:34 PM
 */

#include "fgGFXSceneNodeTrigger.h"

using namespace fg;

/**
 * 
 */
gfx::CSceneNodeTrigger::CSceneNodeTrigger() : CSceneNode(SCENE_NODE_TRIGGER), m_callbacks() {
    m_callbacks.reserve(2);
}

/**
 * 
 * @param orig
 */
gfx::CSceneNodeTrigger::CSceneNodeTrigger(const CSceneNodeTrigger& orig) : base_type(orig) {
    if(this != &orig) {
        unsigned int n = orig.m_callbacks.size();
        for(unsigned int i = 0; i < n; i++) {
            this->m_callbacks.push_back(orig.m_callbacks[i]);
            if(this->m_callbacks.back().pCallback) {
                this->m_callbacks.back().pCallback->upRef();
            }
        }
    }
}

/**
 * 
 */
gfx::CSceneNodeTrigger::~CSceneNodeTrigger() {
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n; i++) {
        TriggerInfo &info = m_callbacks[i];
        if(info.pCallback) {
            if(!info.pCallback->downRef()) {
                delete info.pCallback;
            }
            info.pCallback = NULL;
        }
    }
    m_callbacks.clear_optimised();
    CallbacksVec swapvec;
    m_callbacks.swap(swapvec);
}

/**
 * 
 * @param position
 */
void gfx::CSceneNodeTrigger::setPosition(const Vec3f& position) {
    base_type::setPosition(position);
    //m_aabb.center = position;
    //m_aabb.extent;
    m_aabb.min = position - m_aabb.extent;
    m_aabb.max = position + m_aabb.extent;
    m_aabb.refresh();

}

/**
 * 
 * @param x
 * @param y
 * @param z
 */
void gfx::CSceneNodeTrigger::setPosition(float x, float y, float z) {
    const Vector3f pos(x, y, z);
    base_type::setPosition(pos);
    m_aabb.min = pos - m_aabb.extent;
    m_aabb.max = pos + m_aabb.extent;
    m_aabb.refresh();
}

/**
 * 
 * @param translation
 */
void gfx::CSceneNodeTrigger::translate(const Vec3f& translation) {
    //m_modelMat = math::translate(m_modelMat, translation);
    m_modelMat[3].x += translation.x;
    m_modelMat[3].y += translation.y;
    m_modelMat[3].z += translation.z;
    m_aabb.min += translation;
    m_aabb.max += translation;
    m_aabb.refresh();
}

/**
 * 
 * @param x
 * @param y
 * @param z
 */
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

/**
 * 
 * @param scale
 */
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

void gfx::CSceneNodeTrigger::setCollisionBodyType(const physics::CCollisionBody::BodyType bodyType) {
    // Scene Node Trigger does not need a collision body
    // At least not the base version of node trigger
    if(getCollisionBody()) {
        removeCollisionBody();
    }
}

/**
 * 
 * @param pCallback
 * @param activationType
 */
void gfx::CSceneNodeTrigger::addCallback(CSceneCallback *pCallback,
                                         TriggerActivation activationType) {
    if(!pCallback)
        return;
    fgBool status = checkCallback(pCallback);
    if(!status) {
        pCallback->upRef();
        m_callbacks.push_back(TriggerInfo(pCallback, activationType));
    }
}

/**
 * 
 * @param pCallback
 */
void gfx::CSceneNodeTrigger::removeCallback(CSceneCallback *pCallback) {
    fgBool status = FG_FALSE;
    if(!pCallback) {
        return;
    }
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n && !status; i++) {
        TriggerInfo &info = m_callbacks[i];
        if(info.pCallback == pCallback) {
            pCallback->downRef();
            m_callbacks[i] = m_callbacks[n - 1];
            m_callbacks[n - 1].pCallback = NULL;
            m_callbacks.resize(n - 1);
            status = FG_TRUE;
        }
    }
}

/**
 * 
 * @param pCallback
 */
fgBool gfx::CSceneNodeTrigger::checkCallback(CSceneCallback *pCallback) {
    fgBool status = FG_FALSE;
    if(!pCallback) {
        return status;
    }
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n && !status; i++) {
        TriggerInfo &info = m_callbacks[i];
        if(info.pCallback == pCallback) {
            status = FG_TRUE;
        }
    }
    return status;
}

/**
 * 
 * @param activationType
 * @param pNodeB
 */
void gfx::CSceneNodeTrigger::trigger(TriggerActivation activationType,
                                     CSceneNode* pNodeB) {

    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n; i++) {
        TriggerInfo &info = m_callbacks[i];
        if(info.activation == activationType) {
            info.Call(this, pNodeB);
        }
    }
}
