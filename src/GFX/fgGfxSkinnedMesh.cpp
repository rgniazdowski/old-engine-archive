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
#include "Animation/fgGfxAnimationInfo.h"

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
    boneBoxes.reserve(4);
    boneEdges.reserve(4);
}
//------------------------------------------------------------------------------

gfx::SSkinnedMesh::~SSkinnedMesh() {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
    boneBoxes.clear();
    boneEdges.clear();
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::clearSkinningInfo(void) {
    bones.clear();
    blendWeights.clear();
    blendIndices.clear();
    boneBoxes.clear();
    boneEdges.clear();
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

static void getVertexPos(const void* data,
                         unsigned int stride,
                         unsigned int index,
                         Vector3f& result) {
    if(!data || !stride)
        return;
    // need to reset    
    typedef float value_type;
    typedef unsigned int size_type;

    uintptr_t offset = (uintptr_t)data;
    const size_type innerMax = 3;
    const size_type i = index;
    const void *cur = (const void *)(offset + i * stride);
    value_type *values = (value_type *)cur;
    for(size_type j = 0; j < innerMax; j++) {
        value_type checkVal = *(values + j); // offset + sizeof(value_type)*j
        result[j] = checkVal;
    }
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::merge(int index, const Vector3f& value) {
    float vLen = math::length(value);
    // max: 0(x/0), 2(y/1), 4(z/2)
    // min: 1(x/0), 3(y/1), 5(z/2)
    for(unsigned int p = 0, i = 0; p <= 4; p += 2, i++) {
        // max
        if(value[i] > points[p].value[i]) {
            points[p].value = value;
            points[p].index = index;
            points[p].length = vLen;
        }
    }
    for(unsigned int p = 1, i = 0; p <= 5; p += 2, i++) {
        // min
        if(value[i] < points[p].value[i]) {
            points[p].value = value;
            points[p].index = index;
            points[p].length = vLen;
        }
    }
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::invalidate(void) {
    const float fmax = std::numeric_limits<float>::max();

    for(unsigned int i = 0; i < 6; i++) {
        if(i % 2 == 0) {
            // even - positive
            this->points[i].value.x = fmax / 2.0f * (-1.0f);
            this->points[i].value.y = fmax / 2.0f * (-1.0f);
            this->points[i].value.z = fmax / 2.0f * (-1.0f);
        } else {
            // odd - negative
            this->points[i].value.x = fmax;
            this->points[i].value.y = fmax;
            this->points[i].value.z = fmax;
        }
        this->points[i].index = -1;
        this->points[i].length = 0.0f;
    }
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::transform(SSkinnedMesh* pMesh,
                                             const MatrixVec& matrices,
                                             Vector3f& outputMin,
                                             Vector3f& outputMax) {

    // this will basically do the same thing as GPU/CPU skinning
    // but just for six edge points;
    Vec3f output[6];
    AABB3Df aabb;
    aabb.invalidate();
    transform(pMesh, matrices, output);
    for(unsigned int p = 0; p < 6; p++) {
        aabb.merge(output[p]);
    }
    outputMax = aabb.max;
    outputMin = aabb.min;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::transform(SSkinnedMesh* pMesh,
                                             const DualQuatsVec& dquats,
                                             Vector3f& outputMin,
                                             Vector3f& outputMax) {

    // this will basically do the same thing as GPU/CPU skinning
    // but just for six edge points;
    Vec3f output[6];
    AABB3Df aabb;
    aabb.invalidate();
    transform(pMesh, dquats, output);
    for(unsigned int p = 0; p < 6; p++) {
        aabb.merge(output[p]);
    }
    outputMax = aabb.max;
    outputMin = aabb.min;
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::transform(SSkinnedMesh* pMesh,
                                             const MatrixVec& matrices,
                                             Vector3f* output) {

    // this will basically do the same thing as GPU/CPU skinning
    // but just for six edge points;
    static int jjj = 0;
    jjj++;
    int boneIdx = -1, vertexIdx = 0;
    float weight = 0.0f;
    for(unsigned int p = 0; p < 6; p++) {
        vertexIdx = points[p].index;
        if(vertexIdx < 0)
            continue;
        output[p] = Vec3f();
        const Vec3f& value = points[p].value;
        for(unsigned int i = 0; i < 4; i++) {
            boneIdx = pMesh->blendIndices[vertexIdx][i];
            weight = pMesh->blendWeights[vertexIdx][i];
            if(i > 0 && boneIdx == 0) {
                break;
            }
            output[p] += Vec3f(matrices[boneIdx] * Vec4f(value, 1.0f)) * weight;
        }
    }
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::SEdgeInfo::transform(SSkinnedMesh* pMesh,
                                             const DualQuatsVec& dquats,
                                             Vector3f* output) {

    // this will basically do the same thing as GPU/CPU skinning
    // but just for six edge points;
    DualQuaternionf blendQuat;
    Quaternionf q0;
    int boneIdx = -1, vertexIdx = 0;
    float weight = 0.0f;
    for(unsigned int p = 0; p < 6; p++) {
        vertexIdx = points[p].index;
        if(vertexIdx < 0)
            continue;
        output[p] = Vec3f();
        const Vec3f& value = points[p].value;
        for(unsigned int i = 0; i < 4; i++) {
            boneIdx = pMesh->blendIndices[vertexIdx][i];
            weight = pMesh->blendWeights[vertexIdx][i];
            if(i > 0 && boneIdx == 0) {
                break;
            }
            if(i == 0) {
                q0 = dquats[boneIdx].q0;
                blendQuat = dquats[boneIdx] * weight;
                continue;
            }
            if(math::dot(dquats[boneIdx].q0, q0) < 0.0f) {
                weight *= -1.0f;
            }
            blendQuat += dquats[boneIdx] * weight;
        }
        blendQuat.normalize();
        output[p] = blendQuat.transform(value);
    }
}
//------------------------------------------------------------------------------

void gfx::SSkinnedMesh::refreshSkinningInfo(SMeshBase* pMeshSuper) {
    if(!pMeshSuper)
        return;
    blendWeights.clear();
    blendIndices.clear();
    CVector<unsigned char> countVec;
    const unsigned int nVertices = pMeshSuper->size();
    blendWeights.reserve(nVertices);
    blendIndices.reserve(nVertices);
    countVec.reserve(nVertices);
    blendWeights.resize(nVertices);
    blendIndices.resize(nVertices);
    countVec.resize(nVertices);

    const unsigned int nBones = bones.size();
    boneBoxes.resize(nBones);
    boneEdges.resize(nBones);
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        anim::SBone* pBone = bones[boneIdx];
        if(!pBone)
            continue;
        boneBoxes[boneIdx].invalidate();
        boneEdges[boneIdx].invalidate();
        const unsigned int nWeights = pBone->weights.size();
        for(unsigned int j = 0; j < nWeights; j++) {
            anim::SVertexWeight& weight = pBone->weights[j];
            if(this->meshIndex != (unsigned int)weight.meshIdx)
                continue;
            unsigned int subIdx = (unsigned int)countVec[weight.vertexIdx];
            if(subIdx == 0) {
                blendWeights[weight.vertexIdx] = Vec4f();
                blendIndices[weight.vertexIdx] = Vec4f();
            }
            countVec[weight.vertexIdx]++;
            if(subIdx <= 3) {
                blendWeights[weight.vertexIdx][subIdx] = weight.weight;
                blendIndices[weight.vertexIdx][subIdx] = boneIdx; //pBone->index;
                Vector3f point(0.0f, 0.0f, 0.0f);
                getVertexPos(pMeshSuper->front(), pMeshSuper->stride(),
                             weight.vertexIdx, point);
                boneBoxes[boneIdx].merge(point);
                boneEdges[boneIdx].merge(weight.vertexIdx, point);
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

void gfx::SSkinnedMesh::calculate(anim::SAnimationInfo& animationInfo,
                                  float delta) {
    anim::CAnimation* pAnimation = animationInfo.pAnimation;
    if(!pAnimation)
        return;
    if(pAnimation->getType() != anim::Type::BONE)
        return;
    //if(!isAnimationCompatible(pAnimation))
    //    return;
    anim::CBoneAnimation* pBoneAnimation = NULL;
    pBoneAnimation = static_cast<anim::CBoneAnimation*>(pAnimation);
    pBoneAnimation->calculate(animationInfo, this->bones, delta);
}
//------------------------------------------------------------------------------

fgBool gfx::SSkinnedMesh::isAnimationCompatible(const anim::CAnimation* pAnimation) const {
    if(!pAnimation)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    if(pAnimation->getType() != anim::Type::BONE)
        return FG_FALSE; // only bone animation type compatible with mesh
    const unsigned int nBones = this->bones.size();
    for(unsigned int boneId = 0; boneId < nBones; boneId++) {
        // now if animations does not have channel with this bone - it's not compatible
        if(!pAnimation->hasChannel(this->bones[boneId]->name)) {
            status = FG_FALSE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

unsigned int gfx::SSkinnedMesh::matchBones(const AABoundingBox3Df& aabb,
                                           BonesVec& matchedBones,
                                           float fuzzyEdge) const {
    unsigned int nFound = 0;
    CVector<unsigned int> matchedIdxs;
    nFound = matchBones(aabb, matchedIdxs, fuzzyEdge);
    if(nFound) {
        matchedBones.clear();
        matchedBones.reserve(nFound);
        matchedBones.resize(nFound);
    }
    for(unsigned int i = 0; i < nFound; i++) {
        matchedBones[i] = bones[matchedIdxs[i]];
    }
    return nFound;
}
//------------------------------------------------------------------------------

unsigned int gfx::SSkinnedMesh::matchBones(const AABoundingBox3Df& aabb,
                                           CVector<unsigned int>& matchedBones,
                                           float fuzzyEdge) const {
    const unsigned int nBones = boneBoxes.size();
    if(!nBones)
        return 0;
    //--------------------------------
    // Mode I:
    // ratio = boneBox / aabbBox;
    // ratio <= limit;
    //--------------------------------
    // Mode II:
    // ratio = boneBox / aabbBox;
    // ratio >= limit;
    //--------------------------------
    // Mode III:
    // ratio = fuzzBox / aabbBox;
    // ratio <= limit;
    //--------------------------------
    // Mode IV:
    // ratio = fuzzBox / aabbBox;
    // ratio >= limit;
    //--------------------------------
    // Mode V:
    // ratio = fuzzBox / boneBox;
    // ratio <= limit;
    //--------------------------------
    // Mode VI:
    // ratio = fuzzBox / boneBox;
    // ratio >= limit;
    //--------------------------------
    fgBool shouldFuzzy = (fgBool)!!(fuzzyEdge > FG_EPSILON && fuzzyEdge <= 1.0f);
    matchedBones.clear();
    for(unsigned int i = 0; i < nBones; i++) {
        const AABoundingBox3Df& boneBox = boneBoxes[i];
        //printf("Testing bone[%d][%s]: min:(%.2f;%.2f;%.2f) max:(%.2f;%.2f;%.2f)\n",
        //       i, bones[i]->name.c_str(),
        //       box.min.x, box.min.y, box.min.z,
        //       box.max.x, box.max.y, box.max.z);
        if(aabb.test(boneBox)) {
            matchedBones.push_back(i);
        } else if(shouldFuzzy) {
            AABoundingBox3Df fuzz;
            fuzz.intersect(aabb, boneBox);
            if(!fuzz.isValid())
                continue;
            const float ratio[3] = {fuzz.width() / boneBox.width(),
                                    fuzz.height() / boneBox.height(),
                                    fuzz.depth() / boneBox.depth()};
            fgBool passed = FG_FALSE;
            for(unsigned int r = 0; r < 3; r++) {
                if(ratio[r] <= fuzzyEdge && ratio[r] <= 1.0f) {
                    passed = FG_TRUE;
                    break;
                }
            }
            if(passed) {
                /*
                printf("FUZZBOX: min:(%.2f;%.2f;%.2f) max:(%.2f;%.2f;%.2f) w:%.2f|h:%.2f|d:%.2f\n",
                       fuzz.min.x, fuzz.min.y, fuzz.min.z,
                       fuzz.max.x, fuzz.max.y, fuzz.max.z,
                       fuzz.width(), fuzz.height(), fuzz.depth());
                printf("Matched[%s] -> volume fuzz: %.2f | volume aabbquery: %.2f | ratio: %.2f|%.2f|%.2f\n",
                       bones[i]->name.c_str(), fuzz.getVolume(), aabb.getVolume(), ratio[0], ratio[1], ratio[2]);
                 */
                matchedBones.push_back(i);
            }
        }
    }
    return matchedBones.size();
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
    return base_type::VBO_ARRAY_SIZE + 1; // default for AoS / 5
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
    return base_type::VBO_ARRAY_SIZE + 1; // default for AoS / 3
}
//------------------------------------------------------------------------------
