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
 * File:   fgGFXLoader.cpp
 * Author: vigilant
 * 
 * Created on January 6, 2015, 11:12 PM
 */

#include "fgGFXLoader.h"
#include "fgGFXPrimitives.h"
#include "Hardware/fgHardwareState.h"

using namespace fg;

/**
 * 
 */
gfx::CLoader::CLoader() :
m_pSplashTex(NULL),
m_pProgressTex(NULL),
m_pProgram(NULL),
m_pWindow(NULL),
m_mvp(),
m_mat(),
m_progress(0.0f) { }

/**
 * 
 * @param orig
 */
gfx::CLoader::CLoader(const CLoader& orig) {
    if(this != &orig) {
        this->m_pSplashTex = orig.m_pSplashTex;
        this->m_pProgressTex = orig.m_pProgressTex;
        this->m_pProgram = orig.m_pProgram;
        this->m_pWindow = orig.m_pWindow;
        this->m_mvp = orig.m_mvp;
        this->m_mat = orig.m_mat;
        this->m_progress = orig.m_progress;
    }
}

/**
 * 
 */
gfx::CLoader::~CLoader() {
    m_pSplashTex = NULL;
    m_pProgressTex = NULL;
    m_pProgram = NULL;
    m_pWindow = NULL;
    m_progress = 0.0f;
    m_mvp.identity();
}

/**
 * 
 * @param diff
 */
void gfx::CLoader::update(const float diff) {
    if(!m_pWindow || !m_pSplashTex || !context::isInit() || !m_pProgram)
        return;
    m_pWindow->clearColor();
    m_progress += diff;
    if(m_progress > 100.0f)
        m_progress = 100.0f;
    if(m_progress < 0.0f)
        m_progress = 0.0f;
    float ratio = m_progress / 100.0f;
    //float sw = m_pSplashTex->getWidth();
    //float sh = m_pSplashTex->getHeight();
    float ww = m_pWindow->getWidth();
    float wh = m_pWindow->getHeight();
    /// The splash screen will be shown centered, with proper proportion
    /// based on the screen dimensions
    /// Get the lower dimensions
    float mextent = (float)glm::min((int)ww, (int)wh)*0.9f;
    /// Bind the splash texture
    context::bindTexture(m_pSplashTex->getRefGfxID());
    // Centered on screen, aspect ratio 1:1 regardless of texture dimensions (for now)
    m_mat = math::translate(Matrix4f(),
                            Vec3f(ww / 2.0f,
                                  wh / 2.0f,
                                  0.0f));
    m_mat = math::rotate(m_mat, (float)ratio * M_PIF * (70.0f / (float)FG_RAND(100, 110)), Vec3f(0.0f, 0.0f, 1.0f));
    m_mat = math::scale(m_mat, Vec3f(mextent, mextent, 0.0f));
    m_mvp.calculate(m_mat);
    m_pProgram->setUniform(&m_mvp);
    CPrimitives::drawSquare2D();

    if(!m_pProgressTex || m_progress < FG_EPSILON) {
        m_pWindow->swapBuffers();
        FG_HardwareState->deviceYield(1);
        return;
    }
    float pw = ratio * ww;
    float ph = 0.07f * wh;
    /// Bind the progress texture
    context::bindTexture(m_pProgressTex->getRefGfxID());
    // Bottom-left of the screen
    m_mat = math::translate(Matrix4f(),
                            Vec3f(ww / 2.0f,
                                  wh - ph / 2.0f,
                                  0.0f));
    m_mat = math::scale(m_mat, Vec3f(pw, ph, 0.0f));
    m_mvp.calculate(m_mat);
    m_pProgram->setUniform(&m_mvp);
    CPrimitives::drawSquare2D();
    m_pWindow->swapBuffers();
    FG_HardwareState->deviceYield(1);
}
