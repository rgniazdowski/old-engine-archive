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
 * File:   fgGfxSkinnedMesh.cpp
 * Author: vigilant
 * 
 * Created on September 3, 2015, 9:22 PM
 */

#include "fgGfxSkinnedMesh.h"

using namespace fg;
//------------------------------------------------------------------------------

const unsigned short gfx::SSkinnedMeshAoS::BLEND_WEIGHTS_VBO_ARRAY_IDX = 2;
const unsigned short gfx::SSkinnedMeshAoS::BLEND_INDICES_VBO_ARRAY_IDX = 3;

//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS() :
base_type(),
bones(),
blendWeights(),
blendIndices() {
    bones.reserve(4);
    blendWeights.reserve(8);
    blendIndices.reserve(8);
}
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS(VertexType vertexType) :
base_type(vertexType),
bones(),
blendWeights(),
blendIndices() {
    bones.reserve(4);
    blendWeights.reserve(8);
    blendIndices.reserve(8);
}
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS(AttributeMask attribMask) :
base_type(attribMask),
bones(),
blendWeights(),
blendIndices() {
    bones.reserve(4);
    blendWeights.reserve(8);
    blendIndices.reserve(8);
}
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::~SSkinnedMeshAoS() {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshAoS::clear(void) {
    base_type::clear();
    clearSkinningInfo();
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::refreshAttributes(SAttributeData* pDataArray) const {
    if(!this->vertices->refreshAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)&blendWeights.front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Blend weights info
    index = FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    pointer = (uintptr_t)((unsigned int*)&blendIndices.front());
    // Blend indices info
    index = FG_GFX_ATTRIB_BLEND_INDICES_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::setupAttributes(SAttributeData* pDataArray) const {
    if(!this->vertices->setupAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)&blendWeights.front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Blend weights info
    index = FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 4;
    pDataArray[index].type = ATTRIBUTE_BLEND_WEIGHTS;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (blend_vec_element_type);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    pointer = (uintptr_t)((unsigned int*)&blendIndices.front());
    // Blend indices info
    index = FG_GFX_ATTRIB_BLEND_INDICES_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 4;
    pDataArray[index].type = ATTRIBUTE_BLEND_INDICES;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (blend_vec_element_type);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::genBuffers(void) {

    if(!base_type::genBuffers())
        return FG_GFX_FALSE;

    int &count = getRefVBOCount();
    count = 4; // originally is 2, need additional 2 buffers for blend weights/idx
    if(getNumIndices() < 1) {
        // cannot change the indexes...
    }

    FG_LOG_DEBUG("GFX: SKINNED MESH AoS: generating %d additional buffers - static draw", 2);
    // calling genBuffers with higher count does generate only additional
    // buffers - the previous buffers (in array) remain unchanged!
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);

    context::bufferData(getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX],
                        sizeof (blend_vec_element_type) * blendWeights.size(),
                        (const fgGFXvoid *)&blendWeights.front());

    context::bindBuffer(getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);

    context::bufferData(getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX],
                        sizeof (blend_vec_element_type) * blendIndices.size(),
                        (const fgGFXvoid *)(&blendIndices.front()));


    FG_LOG_DEBUG("GFX: SKINNED MESH AoS: buffer id[blend_weights][%d], data[%p], stride[%d], size[%d]",
                 (int)getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id,
                 (const fgGFXvoid *)&blendWeights.front(),
                 sizeof (blend_vec_element_type),
                 blendWeights.size());


    FG_LOG_DEBUG("GFX: SKINNED MESH AoS: buffer id[blend_indices][%d], data[%p], stride[%d], size[%d]",
                 (int)getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id,
                 (const fgGFXvoid *)(&blendIndices.front()),
                 sizeof (blend_vec_element_type),
                 blendIndices.size());

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshAoS::clearSkinningInfo(void) {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshAoS::refreshSkinningInfo(void) {
    blendWeights.clear();
    blendIndices.clear();
    CVector<unsigned char> countVec;
    blendWeights.reserve(this->size());
    blendIndices.reserve(this->size());
    countVec.reserve(this->size());
    blendWeights.resize(this->size());
    blendIndices.resize(this->size());
    countVec.resize(this->size());
    // ?
    const unsigned int n = bones.size();
    for(unsigned int i = 0; i < n; i++) {
        anim::SBone* pBone = bones[i];
        if(!pBone)
            continue;
        const unsigned int nWeights = pBone->weights.size();
        for(unsigned int j = 0; j < nWeights; j++) {
            anim::SVertexWeight& weight = pBone->weights[j];
            unsigned int subIdx = (unsigned int)countVec[weight.vertexIdx];
            countVec[weight.vertexIdx]++;
            if(subIdx <= 3) {
                blendWeights[weight.vertexIdx][subIdx] = weight.weight;
                blendIndices[weight.vertexIdx][subIdx] = pBone->index;
            }
        }
    }
    countVec.clear();
}
//------------------------------------------------------------------------------
