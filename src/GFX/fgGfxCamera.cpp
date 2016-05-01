/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxCamera.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

float* gfx::CCamera::update(void) {
    m_viewMatrix = math::lookAt(m_eye, m_center, m_up);
    //m_frustum.set(m_eye, m_center, m_up); // #SRSLY?
    return getViewMatPtr();
}
//------------------------------------------------------------------------------
