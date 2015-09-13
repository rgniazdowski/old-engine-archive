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
 * File:   fgGfxUniformUpdater.cpp
 * Author: vigilant
 * 
 * Created on September 13, 2015, 10:51 PM
 */

#include "fgGfxUniformUpdater.h"
#include "fgGfxShaderProgram.h"
#include "GFX/fgGfxMVPMatrix.h"
#include "GFX/fgGfxMaterial.h"
#include "GFX/fgGfxLight.h"
#include "Util/fgMemory.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CUniformUpdater::CUniformUpdater() :
m_uniformValues(),
m_uniformUpdateList() {
    m_uniformValues.resize(shaders::NUM_UNIFORM_TYPES + 1);
    const unsigned int n = m_uniformValues.size();
    for(unsigned int i = 0; i < n; i++) {
        m_uniformValues[i].type = (shaders::UniformType)i;
    }
    m_uniformUpdateList.reserve(4);
}
//------------------------------------------------------------------------------

gfx::CUniformUpdater::CUniformUpdater(const CUniformUpdater& orig) { }
//------------------------------------------------------------------------------

gfx::CUniformUpdater::~CUniformUpdater() {
    m_uniformUpdateList.clear();
    m_uniformValues.clear();
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::disable(shaders::UniformType uniformType) {
    int index = m_uniformUpdateList.find(uniformType);
    if(index >= 0) {
        m_uniformValues.at(index).release();
    }
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::enable(shaders::UniformType uniformType) {
    int index = m_uniformUpdateList.find(uniformType);
    if(index < 0) {
        m_uniformUpdateList.push_back(uniformType);
    }
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(CMVPMatrix* matrix,
                                  unsigned int index) {
    if(matrix)
        m_uniformValues[shaders::UNIFORM_MVP_MATRIX].copy(matrix->getRefModelViewProjMatrix(), index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(CMVMatrix* matrix,
                                  unsigned int index) {
    if(matrix)
        m_uniformValues[shaders::UNIFORM_MODEL_VIEW_MATRIX].copy(matrix->getRefMVMatrix(), index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Matrix4f& matrix,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(math::value_ptr(matrix), 16, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Matrix3f& matrix,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(math::value_ptr(matrix), 9, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Matrix2f& matrix,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(math::value_ptr(matrix), 4, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const SDirectionalLight& light,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(light, index);
}

//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const SMaterial& material,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(material, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  fgGFXfloat v0,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(&v0, 1, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Vector4f& vector,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(vector, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Vector3f& vector,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(vector, index);
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::update(shaders::UniformType uniformType,
                                  const Vector2f& vector,
                                  unsigned int index) {
    m_uniformValues[uniformType].copy(vector, index);
}
//------------------------------------------------------------------------------

gfx::CUniformUpdater::SUniformValue::SUniformValue() :
type(shaders::UNIFORM_INVALID),
data(NULL),
size(0),
count(0),
stride(0) { }
//------------------------------------------------------------------------------

gfx::CUniformUpdater::SUniformValue::SUniformValue(shaders::UniformType uniformType) :
type(uniformType),
data(NULL),
size(0),
count(0),
stride(0) { }
//------------------------------------------------------------------------------

gfx::CUniformUpdater::SUniformValue::SUniformValue(const SUniformValue& orig) {
    this->type = orig.type;
    this->count = orig.count;
    this->stride = orig.stride;
    resize(orig.size);
    memcpy(this->data, orig.data, this->size);
}
//------------------------------------------------------------------------------

gfx::CUniformUpdater::SUniformValue::~SUniformValue() {
    memset(data, 0, size);
    if(data)
        fgFree(data);
    data = NULL;
    size = 0;
    count = 0;
    stride = 0;
    type = shaders::UNIFORM_INVALID;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::release(void) {
    if(data)
        fgFree(data);
    data = NULL;
    count = 0;
    size = 0;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::resize(unsigned int bytes) {
    if(bytes > this->size) {
        this->data = fgRealloc<void>(this->data, bytes);
        this->size = bytes;
    }
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Matrix4f& matrix, unsigned int index) {
    const unsigned int required = 16 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, math::value_ptr(matrix), required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Matrix3f& matrix, unsigned int index) {
    const unsigned int required = 9 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, math::value_ptr(matrix), required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Matrix2f& matrix, unsigned int index) {
    const unsigned int required = 4 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, math::value_ptr(matrix), required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Vector4f& vector, unsigned int index) {
    const unsigned int required = 4 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, &vector, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Vector3f& vector, unsigned int index) {
    const unsigned int required = 3 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, &vector, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const Vector2f& vector, unsigned int index) {
    const unsigned int required = 2 * sizeof (float);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, &vector, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const float* inData,
                                               unsigned int count,
                                               unsigned int index) {
    if(!inData || !count)
        return;
    const unsigned int required = count * sizeof (float);
    if(this->stride == 0) {
        this->stride = required;
    }
    unsigned int offset = index * this->stride;
    if(this->data == NULL || this->count == 0 || this->size == 0) {
        this->resize(offset + required);
        this->count = index + 1;
    } else if(this->count <= index) {
        // need to resize
        this->resize(index * this->stride + required);
        this->count = index + 1;
        offset = index * this->stride;
    }
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void *)address, inData, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const SDirectionalLight& dirLight,
                                               unsigned int index) {
    const unsigned int required = sizeof (SDirectionalLight);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, &dirLight, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::SUniformValue::copy(const SMaterial& material,
                                               unsigned int index) {
    const unsigned int required = sizeof (SMaterial);
    if(!this->stride)
        this->stride = required;
    unsigned int offset = index * this->stride;
    if(offset + required > this->size)
        this->resize(offset + required);
    uintptr_t address = ((uintptr_t)this->data) + offset;
    memcpy((void*)address, &material, required);
    if(this->count <= index)
        this->count = index + 1;
}
//------------------------------------------------------------------------------

void gfx::CUniformUpdater::updateUniforms(CShaderProgram* pProgram) {
    if(!pProgram)
        return;
    const unsigned int n = m_uniformUpdateList.size();
    for(unsigned int i = 0; i < n; i++) {
        unsigned int idx = (int)m_uniformUpdateList[i];
        SUniformValue const& value = m_uniformValues[idx];
        if(value.data == NULL || value.size == 0)
            continue;
        if(value.type == shaders::UNIFORM_MATERIAL) {
            pProgram->setUniform(*((SMaterial*)value.data));
        } else if(value.type == shaders::UNIFORM_DIRECTIONAL_LIGHT) {
            pProgram->setUniform(*((SDirectionalLight*)value.data));
        } else if(value.type == shaders::UNIFORM_DIFFUSE_TEXTURE ||
                  value.type == shaders::UNIFORM_NORMAL_MAP ||
                  value.type == shaders::UNIFORM_BUMP_MAP) {
            pProgram->setUniform(value.type, *((fgGFXint *)value.data));
        } else if(value.type != shaders::UNIFORM_INVALID) {
            // this won't work for integer types
            pProgram->setUniform(value.type, value.size / sizeof (float), (const fgGFXfloat *)value.data);
        }
    }
}
//------------------------------------------------------------------------------
