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
 * File:   fgGfxPlaneGrid.cpp
 * Author: vigilant
 * 
 * Created on May 9, 2015, 6:58 PM
 */

#include "fgGfxPlaneGrid.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "fgGfxMVPMatrix.h"
#include "fgGfxPrimitives.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::SPlaneGridf::SPlaneGridf() : base_type(), cellSize(10.0f),
dimensions(100.0f, 100.0f), modelMat(), gridLines() {
    gridLines.reserve(64);
}
//------------------------------------------------------------------------------

gfx::SPlaneGridf::SPlaneGridf(float _cellSize, const Vector2f& _dimensions) :
base_type(),
cellSize(_cellSize),
dimensions(_dimensions), modelMat(), gridLines() {
    if(cellSize < 0.0f)
        cellSize *= -1.0f;
    gridLines.reserve(64);
}
//------------------------------------------------------------------------------

void gfx::SPlaneGridf::render(CShaderProgram* pProgram, CMVPMatrix* pMVP) {
    if(!pProgram || !pMVP)
        return;
    gridLines.clear_optimised();
    Vector3f oldNormal = Vec3f(0.0f, 1.0f, 0.0f);
    modelMat = math::translate(Matrix4f(), this->n * this->d);
    if(this->axis != Planef::Y) {
        Vector3f rotAxis;
        float rotAngle = 0.0f;
        if(this->n.y <= (-1.0f + std::numeric_limits<float>::epsilon())) {
            rotAxis = Vec3f(0.0f, 0.0f, 1.0f);
            rotAngle = M_PIF; // 180 degrees
        } else {
            rotAxis = math::cross(oldNormal, this->n);
            rotAngle = math::acos(math::dot(oldNormal, this->n));
        }
        modelMat = math::rotate(modelMat, rotAngle, rotAxis);
    }
    pMVP->calculate(modelMat);
    pProgram->setUniform(pMVP);
    CVertexData4v gridLines;
    Vector3f pos, corner;
    Color3f color;
    float step = cellSize;
    int rows = dimensions.y / step; // Z
    int cols = dimensions.x / step; // X
    float depth = rows * step;
    float width = cols * step;

    corner = Vec3f(-cols / 2 * step, 0.0f, -rows / 2 * step);
    for(int i = 0; i <= cols; i++) {
        color = Color3f(1.0f, 1.0f, 1.0f); // white
        pos.x = corner.x + i * step;
        pos.z = corner.z;
        gridLines.append(pos, Vec3f(), Vec2f(), color); // A
        pos.z += depth;
        gridLines.append(pos, Vec3f(), Vec2f(), color); // B
        if(i < cols) {
            color = Color3f(0.6f, 0.6f, 0.6f); // gray
            pos.x += step / 2.0f;
            pos.z = corner.z;
            gridLines.append(pos, Vec3f(), Vec2f(), color); // A
            pos.z += depth;
            gridLines.append(pos, Vec3f(), Vec2f(), color); // B
        }
    }

    for(int i = 0; i <= rows; i++) {
        color = Color3f(1.0f, 1.0f, 1.0f); // white
        pos.x = corner.x;
        pos.z = corner.z + i * step;
        gridLines.append(pos, Vec3f(), Vec2f(), color); // A
        pos.x += width;
        gridLines.append(pos, Vec3f(), Vec2f(), color); // B
        if(i < rows) {
            color = Color3f(0.6f, 0.6f, 0.6f); // gray
            pos.x = corner.x;
            pos.z += step / 2.0f;
            gridLines.append(pos, Vec3f(), Vec2f(), color); // A
            pos.x += width;
            gridLines.append(pos, Vec3f(), Vec2f(), color); // B
        }
    }
    primitives::drawVertexData(&gridLines,
                               ATTRIBUTE_POSITION_BIT | ATTRIBUTE_COLOR_BIT,
                               PrimitiveMode::LINES);
}
//------------------------------------------------------------------------------

void gfx::SPlaneGridf::snapTo(const Vector3f& inputPoint,
                              Vector3f& outputPoint,
                              float threshold,
                              fgBool snapHalf,
                              fgBool refreshMatrix) {

    if(threshold < 0.0f)
        threshold *= -1.0f;
    if(refreshMatrix) {
        determineAxis();
        Vector3f oldNormal = Vec3f(0.0f, 1.0f, 0.0f);
        modelMat = math::translate(Matrix4f(), this->n * this->d);
        if(this->axis != Planef::Y) {
            Vector3f rotAxis;
            float rotAngle = 0.0f;
            if(this->n.y <= (-1.0f + std::numeric_limits<float>::epsilon())) {
                rotAxis = Vec3f(0.0f, 0.0f, 1.0f);
                rotAngle = M_PIF; // 180 degrees
            } else {
                rotAxis = math::cross(oldNormal, this->n);
                rotAngle = math::acos(math::dot(oldNormal, this->n));
            }
            modelMat = math::rotate(modelMat, rotAngle, rotAxis);
        }
    }
    const float cell = (snapHalf ? cellSize / 2.0f : cellSize);

    // grid cell size - snap when d < .33f * gridCellSize
    // need to transform point to original state - invert the modelMat -
    // created by rotation / translation based on the groundPlane
    const Matrix4f invMat = math::inverse(modelMat);
    Vector4f flatPos = invMat * Vector4f(inputPoint, 1.0f);

    const int cols = (int)flatPos.x / cell;
    const int rows = (int)flatPos.z / cell;
    const float xil = (float)cols * cell;
    const float zil = (float)rows * cell;
    float diffX = (flatPos.x - xil) / cell;
    float signX = 1.0f;
    if(diffX < 0.0f) {
        diffX *= -1.0f;
        signX = -1.0f;
    }
    if(diffX < threshold)
        flatPos.x = xil;
    if(diffX > 1.0f - threshold)
        flatPos.x = xil + cell * signX;

    float diffZ = (flatPos.z - zil) / cell;
    float signZ = 1.0f;
    if(diffZ < 0.0f) {
        diffZ *= -1.0f;
        signZ = -1.0f;
    }
    if(diffZ < threshold)
        flatPos.z = zil;
    if(diffZ > 1.0f - threshold)
        flatPos.z = zil + cell * signZ;
    flatPos = modelMat * flatPos;
    outputPoint.x = flatPos.x;
    outputPoint.y = flatPos.y;
    outputPoint.z = flatPos.z;
}
//------------------------------------------------------------------------------
