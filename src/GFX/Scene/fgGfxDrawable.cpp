/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "GFX/fgGfxDrawCall.h"
#include "fgGfxDrawable.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::traits::CDrawable::CDrawable() : m_drawCall(NULL) { }
//------------------------------------------------------------------------------

gfx::traits::CDrawable::~CDrawable() {
    if(m_drawCall) {
        delete m_drawCall;
        m_drawCall = NULL;
    }
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator ==(const self_type& a) const {
    if(!this->m_drawCall) {
        return false;
    } else if(!a.getDrawCall()) {
        return false;
    }
    return (*this->m_drawCall == *a.getDrawCall());
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator !=(const self_type& a) const {
    if(!this->m_drawCall) {
        return true;
    } else if(!a.getDrawCall()) {
        return true;
    }
    return (*this->m_drawCall != *a.getDrawCall());
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator <(const self_type& a) const {
    if(!this->m_drawCall) {
        return true;
    } else if(!a.getDrawCall()) {
        return false;
    }
    return (*this->m_drawCall < *a.getDrawCall());
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator >(const self_type& a) const {
    if(!this->m_drawCall) {
        return false;
    } else if(!a.getDrawCall()) {
        return true;
    }
    return (*this->m_drawCall > *a.getDrawCall());
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator <=(const self_type& a) const {
    if(!this->m_drawCall) {
        return true;
    } else if(!a.getDrawCall()) {
        return false;
    }
    return (*this->m_drawCall <= *a.getDrawCall());
}
//------------------------------------------------------------------------------

bool gfx::traits::CDrawable::operator >=(const self_type& a) const {
    if(!this->m_drawCall) {
        return false;
    } else if(!a.getDrawCall()) {
        return true;
    }
    return (*this->m_drawCall >= *a.getDrawCall());
}
//------------------------------------------------------------------------------
