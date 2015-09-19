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
 * File:   fgGfxTriggerable.cpp
 * Author: vigilant
 * 
 * Created on September 19, 2015, 10:53 AM
 */
#include "fgGfxSceneCallback.h"
#include "fgGfxSceneNode.h"
#include "fgGfxTriggerable.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::traits::CTriggerable::CTriggerable() { }
//------------------------------------------------------------------------------

gfx::traits::CTriggerable::CTriggerable(const CTriggerable& orig) {
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
//------------------------------------------------------------------------------

gfx::traits::CTriggerable::~CTriggerable() {
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n; i++) {
        STriggerInfo &info = m_callbacks[i];
        if(info.pCallback) {
            if(!info.pCallback->downRef()) {
                delete info.pCallback;
            }
            info.pCallback = NULL;
        }
    }
    m_callbacks.clear_optimised();
}
//------------------------------------------------------------------------------

gfx::traits::CTriggerable::STriggerInfo::STriggerInfo() :
pCallback(NULL),
activation(ON_COLLISION_BEGIN) { }
//------------------------------------------------------------------------------

gfx::traits::CTriggerable::STriggerInfo::STriggerInfo(CSceneCallback *callback,
                                                      TriggerActivation activationType) :
pCallback(callback),
activation(activationType) { }
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::STriggerInfo::Call(void) {
    if(pCallback) pCallback->Call();
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::STriggerInfo::Call(event::CArgumentList* argv) {
    if(pCallback) pCallback->Call(argv);
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::STriggerInfo::Call(void* pSystemData) {
    if(pCallback) pCallback->Call(pSystemData);
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::STriggerInfo::Call(CSceneNode* pNodeA) {
    if(pCallback) pCallback->Call(pNodeA);
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::STriggerInfo::Call(CSceneNode* pNodeA, CSceneNode* pNodeB) {
    if(pCallback) pCallback->Call(pNodeA, pNodeB);
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::addCallback(CSceneCallback* pCallback,
                                            TriggerActivation activationType) {
    if(!pCallback)
        return;
    fgBool status = checkCallback(pCallback);
    if(!status) {
        pCallback->upRef();
        m_callbacks.push_back(STriggerInfo(pCallback, activationType));
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::removeCallback(CSceneCallback* pCallback) {
    fgBool status = FG_FALSE;
    if(!pCallback) {
        return;
    }
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n && !status; i++) {
        STriggerInfo &info = m_callbacks[i];
        if(info.pCallback == pCallback) {
            pCallback->downRef();
            m_callbacks[i] = m_callbacks[n - 1];
            m_callbacks[n - 1].pCallback = NULL;
            m_callbacks.resize(n - 1);
            status = FG_TRUE;
        }
    }
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CTriggerable::checkCallback(CSceneCallback* pCallback) {
    fgBool status = FG_FALSE;
    if(!pCallback) {
        return status;
    }
    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n && !status; i++) {
        STriggerInfo &info = m_callbacks[i];
        if(info.pCallback == pCallback) {
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::traits::CTriggerable::trigger(TriggerActivation activationType,
                                        CSceneNode* pNodeA,
                                        CSceneNode* pNodeB) {

    unsigned int n = m_callbacks.size();
    for(unsigned int i = 0; i < n; i++) {
        STriggerInfo &info = m_callbacks[i];
        if(info.activation == activationType) {
            info.Call(pNodeA, pNodeB);
        }
    }
}
//------------------------------------------------------------------------------
