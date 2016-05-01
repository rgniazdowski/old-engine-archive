/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxProjection.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

void gfx::CProjection::setPerspective(float fovY, float aspect, float zNear, float zFar) {
    float properFOV;
#if defined(GLM_FORCE_RADIANS)
    properFOV = math::radians(fovY);
#else
    properFOV = fovY;
#endif
    m_projMatrix = math::perspective(properFOV, aspect, zNear, zFar);
}
//------------------------------------------------------------------------------

void gfx::CProjection::setOrtho(float left, float right, float bottom, float top, float zNear, float zFar) {
    m_projMatrix = math::ortho(left, right, bottom, top, zNear, zFar);
}
//------------------------------------------------------------------------------
