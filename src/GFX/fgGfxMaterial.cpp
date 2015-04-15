/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxMaterial.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"

/* #TODO P4 - stworzenie klasy Material w glownym podsystemie GFX - wazne: tablice wierzcholkow, 
 * kolorow/uv itp sa grupowane wedlug uzytego materialu
 *
 * zalozenie jest takie ze grupowanie w ten sposob pozwala przyspieszyc rendering - jesli mamy np.
 * 10 obiektow po 1000+ wierzcholkow to nie ma sensu 10 razy wywolywac i przekazywac listy wierzcholkow
 * do OpenGL - mozna stworzyc jedna tablice i przekazac ja tylko raz 
 * * - teoretycznie ma to przyspieszyc dzialanie i prawdopodobnie tak jest - jednak zostawiam to na pozniej
 *
 * * Jak to zaimplementowac pozniej? W jakis sposob material musi miec odnosnik do obiektow ktore go uzywaja
 * * lub vice versa - po zaladowaniu wszystkich obiektow sa one merge'owane w grupy (wg uzytego Materialu) i
 * * duze tablice danych (vert,tris,uv,norm,color)
 * *
 * * To ma sens przy scenach z duza iloscia obiektow - zostawiam na pozniej - P4
 */

using namespace fg;

gfx::SMaterial::SMaterial() : name(),
ambient(1.0f, 1.0f, 1.0f, 1.0f),
diffuse(1.0f, 1.0f, 1.0f, 1.0f),
specular(1.0f, 1.0f, 1.0f, 1.0f),
transmittance(1.0f, 1.0f, 1.0f, 1.0f),
emission(1.0f, 1.0f, 1.0f, 1.0f),
shininess(1.0f),
ior(1.0f),
dissolve(1.0f),
illuminationModel(0),
burn(1.0f),
ambientTexName(),
diffuseTexName(),
specularTexName(),
normalTexName(),
ambientTex(NULL),
diffuseTex(NULL),
specularTex(NULL),
normalTex(NULL),
shaderProgram(NULL),
shaderName(),
blendMode(BlendMode::BLEND_OFF),
stateFlags(FRONT_FACE_CCW | DEPTH_TEST | DEPTH_WRITE_MASK | CULL_FACE),
unknownParam() { }

size_t gfx::SMaterial::getDataSize(void) {
    size_t size = sizeof (SMaterial);
    size += name.length() +
            ambientTexName.length() +
            diffuseTexName.length() +
            specularTexName.length() +
            normalTexName.length() +
            shaderName.length();
    size += unknownParam.size() * (sizeof (std::string) * 2);
    return size;
}

gfx::SMaterial::SMaterial(const SMaterial & material) {
    this->ambientTex = material.ambientTex;
    this->diffuseTex = material.diffuseTex;
    this->specularTex = material.specularTex;
    this->normalTex = material.normalTex;

    this->name = material.name;
    this->ambient = material.ambient;
    this->diffuse = material.diffuse;
    this->specular = material.specular;
    this->transmittance = material.transmittance;
    this->emission = material.emission;
    this->shininess = material.shininess;
    this->ior = material.ior;
    this->dissolve = material.dissolve;
    this->illuminationModel = material.illuminationModel;
    this->burn = material.burn;
    this->blendMode = material.blendMode;
    this->shaderName = material.shaderName;
    this->shaderProgram = material.shaderProgram;

    this->stateFlags = material.stateFlags;

    this->ambientTexName = material.ambientTexName;
    this->diffuseTexName = material.diffuseTexName;
    this->specularTexName = material.specularTexName;
    this->normalTexName = material.normalTexName;

    this->unknownParam = material.unknownParam;
}

void gfx::SMaterial::clear(void) {
    // #TODO - here is the place to call resource manager and decrease reference count for the used textures
    //FG_ResourceManager->unlockResource(ambientTexHandle);
    //FG_ResourceManager->unlockResource(diffuseTexHandle);
    //FG_ResourceManager->unlockResource(specularTexHandle);
    //FG_ResourceManager->unlockResource(normalTexHandle);
    // #FIXME #PLOX
    ambientTexName.clear();
    diffuseTexName.clear();
    specularTexName.clear();
    normalTexName.clear();

    name.clear();
    shaderName.clear();
    shaderProgram = NULL;

    ambient = fgColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    diffuse = fgColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    specular = fgColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    transmittance = fgColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    emission = fgColor4f(0.0f, 0.0f, 0.0f, 1.0f);

    shininess = 0.0f;
    ior = 0.0f;
    dissolve = 0.0f;
    illuminationModel = 0;
    burn = 0.0f;

    blendMode = BlendMode::BLEND_OFF;

    //stateFlags = FRONT_FACE_CCW | DEPTH_TEST | DEPTH_WRITE_MASK | CULL_FACE;
    stateFlags = NONE;

    ambientTex = NULL;
    diffuseTex = NULL;
    specularTex = NULL;
    normalTex = NULL;

    unknownParam.clear();
}

unsigned int gfx::SMaterial::getSortingValue(const unsigned int maxValue) const {
    unsigned int sortingValue = 0;

    sortingValue += (unsigned int)stateFlags;
    sortingValue += (unsigned int)blendMode;
    if(ambientTex) {
        sortingValue += ambientTex->getRefHandle().getIndex() % 32;
    }
    if(diffuseTex) {
        sortingValue += diffuseTex->getRefHandle().getIndex() % 32;
    }
    if(specularTex) {
        sortingValue += specularTex->getRefHandle().getIndex() % 32;
    }
    if(normalTex) {
        sortingValue += normalTex->getRefHandle().getIndex() % 32;
    }
    sortingValue += (unsigned int)illuminationModel;
    sortingValue += name.length();

    //if(burn > 1.0f)
    //        burn = 1.0f; // ? ? ?
    sortingValue += (unsigned int)(burn * 10.0f);

    if(sortingValue > maxValue) {
        sortingValue = sortingValue % maxValue;
    }

    return sortingValue;
}
