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
 * File:   fgGFXSkyBox.cpp
 * Author: vigilant
 * 
 * Created on January 26, 2015, 7:16 PM
 */

#include "GFX/fgGfxStdInc.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/fgGfxPrimitives.h"
#include "fgGfxSceneSkyBox.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CSceneSkyBox::CSceneSkyBox() :
CDrawable(DRAWABLE_SKYBOX),
m_skyBoxScale(1.0f),
m_pos(),
m_textureID(),
m_program(NULL),
m_MVP(NULL) { }
//------------------------------------------------------------------------------

gfx::CSceneSkyBox::CSceneSkyBox(const CSceneSkyBox& orig) {
    if(this != &orig) {
        this->m_pos = orig.m_pos;
        this->m_skyBoxScale = orig.m_skyBoxScale;
        this->m_textureID = orig.m_textureID;
        this->m_program = orig.m_program;
        this->m_MVP = orig.m_MVP;
        this->setDrawableType(DRAWABLE_SKYBOX);
    }
}
//------------------------------------------------------------------------------

gfx::CSceneSkyBox::~CSceneSkyBox() {
    m_program = NULL;
    m_MVP = NULL;
}
//------------------------------------------------------------------------------

void gfx::CSceneSkyBox::draw(void) {
    Matrix4f modelMat = math::translate(Matrix4f(), m_pos);
    modelMat = math::scale(modelMat, Vector3f(m_skyBoxScale, m_skyBoxScale, m_skyBoxScale));
    draw(modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneSkyBox::draw(const Vec2f& relPos) {
    Matrix4f modelMat = math::translate(Matrix4f(), m_pos);
    modelMat = math::translate(modelMat, Vector3f(relPos.x, relPos.y, 0.0f));
    modelMat = math::scale(modelMat, Vector3f(m_skyBoxScale, m_skyBoxScale, m_skyBoxScale));
    draw(modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneSkyBox::draw(const Vec3f& relPos) {
    Matrix4f modelMat = math::translate(Matrix4f(), m_pos);
    modelMat = math::translate(modelMat, relPos);
    modelMat = math::scale(modelMat, Vector3f(m_skyBoxScale, m_skyBoxScale, m_skyBoxScale));
    draw(modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneSkyBox::draw(const Matrix4f& modelMat) {
    const fgBool isTexture = (fgBool)context::isTexture(m_textureID);
    //if(!isTexture) {
    //fgBool test = (fgBool)glIsTexture(m_textureID.id);
    //printf("SKYBOX - NOT A TEXTURE ! %d || glIsTexture()=%d\n", m_textureID.id, (int)test);
    //}
    if(isTexture && m_MVP && m_program) {
        m_program->setUniform(shaders::UNIFORM_USE_TEXTURE, 1.0f);
        m_program->setUniform(shaders::UNIFORM_CUBE_TEXTURE, (fgGFXint)0);
        context::setBlend(FG_FALSE);
        context::bindTexture(m_textureID);
        m_MVP->calculate(modelMat);
        m_program->setUniform(m_MVP);
        context::frontFace(GL_CW); // #FUBAR
        primitives::drawSkyBoxOptimized();
        context::frontFace(GL_CCW);
    }
}
//------------------------------------------------------------------------------
