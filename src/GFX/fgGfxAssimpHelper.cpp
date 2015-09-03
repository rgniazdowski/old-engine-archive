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
 * File:   fgAssimpHelper.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 11:39 AM
 */

#include "fgGfxAssimpHelper.h"

using namespace fg;

//------------------------------------------------------------------------------
#if defined(FG_USING_ASSIMP)

void gfx::assimp_helper::setupMaterial(struct SMaterial* pNewMaterial,
                                       struct aiMaterial* pMaterial) {
    if(!pMaterial || !pNewMaterial)
        return;

    unsigned int texIndex = 0;
    aiString texPath;
    if(AI_SUCCESS == pMaterial->GetTexture(aiTextureType_AMBIENT, texIndex, &texPath)) {
        pNewMaterial->ambientTexName.append(texPath.C_Str());
    }

    if(AI_SUCCESS == pMaterial->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath)) {
        pNewMaterial->diffuseTexName.append(texPath.C_Str());
    }

    if(AI_SUCCESS == pMaterial->GetTexture(aiTextureType_SPECULAR, texIndex, &texPath)) {
        pNewMaterial->specularTexName.append(texPath.C_Str());
    }

    if(AI_SUCCESS == pMaterial->GetTexture(aiTextureType_NORMALS, texIndex, &texPath)) {
        pNewMaterial->normalTexName.append(texPath.C_Str());
    }
    aiColor4D tmpColor;
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, tmpColor)) {
        pNewMaterial->ambient.r = tmpColor.r;
        pNewMaterial->ambient.g = tmpColor.g;
        pNewMaterial->ambient.b = tmpColor.b;
        pNewMaterial->ambient.a = tmpColor.a;
    }
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, tmpColor)) {
        pNewMaterial->diffuse.r = tmpColor.r;
        pNewMaterial->diffuse.g = tmpColor.g;
        pNewMaterial->diffuse.b = tmpColor.b;
        pNewMaterial->diffuse.a = tmpColor.a;
    }
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, tmpColor)) {
        pNewMaterial->specular.r = tmpColor.r;
        pNewMaterial->specular.g = tmpColor.g;
        pNewMaterial->specular.b = tmpColor.b;
        pNewMaterial->specular.a = tmpColor.a;
    }
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, tmpColor)) {
        pNewMaterial->emission.r = tmpColor.r;
        pNewMaterial->emission.g = tmpColor.g;
        pNewMaterial->emission.b = tmpColor.b;
        pNewMaterial->emission.a = tmpColor.a;
    }
    unsigned int pMax = 1;
    float shininess = 1.0f, strength = 1.0f;
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_SHININESS, &shininess, &pMax)) {
        pNewMaterial->shininess = shininess;
    }
    pMax = 1;
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, &strength, &pMax)) {
        pNewMaterial->shininess *= strength;
    }
    int twoSided = 0;
    if(AI_SUCCESS == pMaterial->Get(AI_MATKEY_TWOSIDED, &twoSided, &pMax)) {
        if(twoSided)
            pNewMaterial->setCullFace(FG_FALSE);
    }
}

//------------------------------------------------------------------------------

void gfx::assimp_helper::copyMatrix4x4(Matrix4f& dest, const aiMatrix4x4& source) {
    dest[0].x = source.a1;
    dest[0].y = source.b1;
    dest[0].z = source.c1;
    dest[0].w = source.d1;

    dest[1].x = source.a2;
    dest[1].y = source.b2;
    dest[1].z = source.c2;
    dest[1].w = source.d2;

    dest[2].x = source.a3;
    dest[2].y = source.b3;
    dest[2].z = source.c3;
    dest[2].w = source.d3;

    dest[3].x = source.a4;
    dest[3].y = source.b4;
    dest[3].z = source.c4;
    dest[3].w = source.d4;

}
//------------------------------------------------------------------------------

void gfx::assimp_helper::copyMatrix4x4(aiMatrix4x4& dest, const Matrix4f& source) {
    dest.a1 = source[0].x;
    dest.b1 = source[0].y;
    dest.c1 = source[0].z;
    dest.d1 = source[0].w;

    dest.a2 = source[1].x;
    dest.b2 = source[1].y;
    dest.c2 = source[1].z;
    dest.d2 = source[1].w;

    dest.a3 = source[2].x;
    dest.b3 = source[2].y;
    dest.c3 = source[2].z;
    dest.d3 = source[2].w;

    dest.a4 = source[3].x;
    dest.b4 = source[3].y;
    dest.c4 = source[3].z;
    dest.d4 = source[3].w;
}
//------------------------------------------------------------------------------

void gfx::assimp_helper::copyMatrix3x3(Matrix3f& dest, const aiMatrix3x3& source) {
    dest[0].x = source.a1;
    dest[0].y = source.b1;
    dest[0].z = source.c1;

    dest[1].x = source.a2;
    dest[1].y = source.b2;
    dest[1].z = source.c2;

    dest[2].x = source.a3;
    dest[2].y = source.b3;
    dest[2].z = source.c3;
}
//------------------------------------------------------------------------------

void gfx::assimp_helper::copyMatrix3x3(aiMatrix3x3& dest, const Matrix3f& source) {
    dest.a1 = source[0].x;
    dest.b1 = source[0].y;
    dest.c1 = source[0].z;

    dest.a2 = source[1].x;
    dest.b2 = source[1].y;
    dest.c2 = source[1].z;

    dest.a3 = source[2].x;
    dest.b3 = source[2].y;
    dest.c3 = source[2].z;
}
//------------------------------------------------------------------------------

void gfx::assimp_helper::decompose(const aiMatrix4x4& source,
                                   Vector3f& scale,
                                   Quaternionf& rotation,
                                   Vector3f& position) {
    aiQuaternion sourceRot;
    aiVector3D sourcePosition, sourceScale;

    source.Decompose(sourceScale, sourceRot, sourcePosition);
    copyVector(scale, sourceScale);
    copyQuat(rotation, sourceRot);
    copyVector(position, sourcePosition);
}
//------------------------------------------------------------------------------
#endif
