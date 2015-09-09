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
#include "Animation/fgGfxAnimation.h"
#include "Animation/fgGfxBoneAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

/******************************************************************************
 * SKINNED MESH BASE FUNCTIONS
 ******************************************************************************/

gfx::SSkinnedMesh::SSkinnedMesh() :
bones(),
blendWeights(),
blendIndices() {
    bones.reserve(4);
    blendWeights.reserve(8);
    blendIndices.reserve(8);
}
//------------------------------------------------------------------------------

gfx::SSkinnedMesh::~SSkinnedMesh() {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::clearSkinningInfo(void) {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMesh::internal_getBlendWeightsVboArrayIdx(void) const {
    return 2; // default for AoS
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMesh::internal_getBlendIndicesVboArrayIdx(void) const {
    return 3; // default for AoS
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::clear(SMeshBase* pMeshSuper) {
    if(!pMeshSuper)
        return;
    pMeshSuper->clear();
    clearSkinningInfo();
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::refreshSkinningInfo(SMeshBase* pMeshSuper) {
    if(!pMeshSuper)
        return;
    blendWeights.clear();
    blendIndices.clear();
    CVector<unsigned char> countVec;
    const unsigned int vCount = pMeshSuper->size();
    blendWeights.reserve(vCount);
    blendIndices.reserve(vCount);
    countVec.reserve(vCount);
    blendWeights.resize(vCount);
    blendIndices.resize(vCount);
    countVec.resize(vCount);

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
                blendIndices[weight.vertexIdx][subIdx] = i; //pBone->index;
            }
        }
    }
    countVec.clear();
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMesh::refreshAttributes(const SMeshBase* pMeshSuper,
                                                  SAttributeData* pDataArray) const {
    if(!pMeshSuper) {
        return FG_GFX_FALSE;
    }    
    const unsigned short BLEND_WEIGHTS_VBO_ARRAY_IDX = internal_getBlendWeightsVboArrayIdx();
    const unsigned short BLEND_INDICES_VBO_ARRAY_IDX = internal_getBlendIndicesVboArrayIdx();
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)&blendWeights.front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = pMeshSuper->hasVBO();
    // Blend weights info
    index = FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = pMeshSuper->getPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id;
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
        pDataArray[index].buffer = pMeshSuper->getPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMesh::setupAttributes(const SMeshBase* pMeshSuper,
                                                SAttributeData* pDataArray) const {
    if(!pMeshSuper) {
        return FG_GFX_FALSE;
    }    
    const unsigned short BLEND_WEIGHTS_VBO_ARRAY_IDX = internal_getBlendWeightsVboArrayIdx();
    const unsigned short BLEND_INDICES_VBO_ARRAY_IDX = internal_getBlendIndicesVboArrayIdx();
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)&blendWeights.front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = pMeshSuper->hasVBO();
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
        pDataArray[index].buffer = pMeshSuper->getPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id;
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
        pDataArray[index].buffer = pMeshSuper->getPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMesh::genBuffers(SMeshBase* pMeshSuper) {
    if(!pMeshSuper)
        return FG_GFX_FALSE;    

    const unsigned short BLEND_WEIGHTS_VBO_ARRAY_IDX = internal_getBlendWeightsVboArrayIdx();
    const unsigned short BLEND_INDICES_VBO_ARRAY_IDX = internal_getBlendIndicesVboArrayIdx();
    int &count = pMeshSuper->getRefVBOCount();
    // originally is 2 for AoS, 4 for SoA,
    // need additional 2 buffers for blend weights/idx (4/6)
    count += 2;
    if(pMeshSuper->getNumIndices() < 1) {
        // cannot change the indexes...
    }
    const char* baseTypeStr = "AoS\0";
    if(pMeshSuper->isSoA())
        baseTypeStr = "SoA\0";
    FG_LOG_DEBUG("GFX: SKINNED MESH %s: generating %d additional buffers - static draw", baseTypeStr, 2);
    // calling genBuffers with higher count does generate only additional
    // buffers - the previous buffers (in array) remain unchanged!
    context::genBuffers(count, pMeshSuper->getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(pMeshSuper->getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);

    context::bufferData(pMeshSuper->getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX],
                        sizeof (blend_vec_element_type) * blendWeights.size(),
                        (const fgGFXvoid *)&blendWeights.front());

    context::bindBuffer(pMeshSuper->getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);

    context::bufferData(pMeshSuper->getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX],
                        sizeof (blend_vec_element_type) * blendIndices.size(),
                        (const fgGFXvoid *)(&blendIndices.front()));


    FG_LOG_DEBUG("GFX: SKINNED MESH %s: buffer id[blend_weights][%d], data[%p], stride[%d], size[%d]",
                 baseTypeStr,
                 (int)pMeshSuper->getRefPtrVBO()[BLEND_WEIGHTS_VBO_ARRAY_IDX].id,
                 (const fgGFXvoid *)&blendWeights.front(),
                 sizeof (blend_vec_element_type),
                 blendWeights.size());


    FG_LOG_DEBUG("GFX: SKINNED MESH %s: buffer id[blend_indices][%d], data[%p], stride[%d], size[%d]",
                 baseTypeStr,
                 (int)pMeshSuper->getRefPtrVBO()[BLEND_INDICES_VBO_ARRAY_IDX].id,
                 (const fgGFXvoid *)(&blendIndices.front()),
                 sizeof (blend_vec_element_type),
                 blendIndices.size());

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::calculate(anim::CAnimation* pAnimation,
                                  anim::SAnimationFrameInfo& frameInfo,
                                  float elapsed) {
    if(!pAnimation) {
        return;
    }
    if(pAnimation->getType() != anim::Type::BONE) {
        return;
    }
    anim::CBoneAnimation* pBoneAnimation = NULL;
    pBoneAnimation = static_cast<anim::CBoneAnimation*>(pAnimation);
    pBoneAnimation->calculate(frameInfo, this->bones, elapsed);
}
//------------------------------------------------------------------------------

/******************************************************************************
 * SKINNED MESH SOA FUNCTIONS - STRUCTURE OF ARRAYS
 ******************************************************************************/

gfx::SSkinnedMeshSoA::SSkinnedMeshSoA() :
base_type(),
skinned_base_type() { }
//------------------------------------------------------------------------------

gfx::SSkinnedMeshSoA::~SSkinnedMeshSoA() { }
//------------------------------------------------------------------------------

gfx::SMeshSoA* gfx::SSkinnedMeshSoA::getMeshSoA(void) {
    return this;
}
//------------------------------------------------------------------------------

gfx::SMeshAoS* gfx::SSkinnedMeshSoA::getMeshAoS(void) {
    return NULL; // this is not AoS
}
//------------------------------------------------------------------------------

gfx::SMeshBase* gfx::SSkinnedMeshSoA::getMeshBase(void) {
    return this;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshSoA::clear(void) {
    skinned_base_type::clear(this);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshSoA::refreshAttributes(SAttributeData* pDataArray) const {
    if(!base_type::refreshAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::refreshAttributes(this, pDataArray);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshSoA::setupAttributes(SAttributeData* pDataArray) const {
    if(!base_type::setupAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::setupAttributes(this, pDataArray);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshSoA::genBuffers(void) {
    if(!base_type::genBuffers()) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::genBuffers(this);
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshSoA::refreshSkinningInfo(void) {
    skinned_base_type::refreshSkinningInfo(this);
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMeshSoA::internal_getBlendWeightsVboArrayIdx(void) const {
    return base_type::VBO_ARRAY_SIZE; // default for AoS / 4
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMeshSoA::internal_getBlendIndicesVboArrayIdx(void) const {
    return base_type::VBO_ARRAY_SIZE+1; // default for AoS / 5
}
//------------------------------------------------------------------------------

/******************************************************************************
 * SKINNED MESH AOS FUNCTIONS - ARRAY OF STRUCTURES
 ******************************************************************************/

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS() :
base_type(),
skinned_base_type() { }
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS(VertexType vertexType) :
base_type(vertexType),
skinned_base_type() { }
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::SSkinnedMeshAoS(AttributeMask attribMask) :
base_type(attribMask),
skinned_base_type() { }
//------------------------------------------------------------------------------

gfx::SSkinnedMeshAoS::~SSkinnedMeshAoS() { }
//------------------------------------------------------------------------------

gfx::SMeshSoA* gfx::SSkinnedMeshAoS::getMeshSoA(void) {
    return NULL;
}
//------------------------------------------------------------------------------

gfx::SMeshAoS* gfx::SSkinnedMeshAoS::getMeshAoS(void) {
    return this;
}
//------------------------------------------------------------------------------

gfx::SMeshBase* gfx::SSkinnedMeshAoS::getMeshBase(void) {
    return this;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshAoS::clear(void) {
    skinned_base_type::clear(this);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::refreshAttributes(SAttributeData* pDataArray) const {
    if(!base_type::refreshAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::refreshAttributes(this, pDataArray);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::setupAttributes(SAttributeData* pDataArray) const {
    if(!base_type::setupAttributes(pDataArray)) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::setupAttributes(this, pDataArray);
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SSkinnedMeshAoS::genBuffers(void) {
    if(!base_type::genBuffers()) {
        return FG_GFX_FALSE;
    }
    return skinned_base_type::genBuffers(this);
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMeshAoS::refreshSkinningInfo(void) {
    skinned_base_type::refreshSkinningInfo(this);
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMeshAoS::internal_getBlendWeightsVboArrayIdx(void) const {
    return base_type::VBO_ARRAY_SIZE; // default for AoS / 2
}
//------------------------------------------------------------------------------

unsigned short gfx::SSkinnedMeshAoS::internal_getBlendIndicesVboArrayIdx(void) const {
    return base_type::VBO_ARRAY_SIZE+1; // default for AoS / 3
}
//------------------------------------------------------------------------------
