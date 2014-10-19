/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXMaterial.h"

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

/**
 * 
 */
fgGfxMaterial::fgGfxMaterial() { }

/**
 * 
 * @return 
 */
size_t fgGfxMaterial::getDataSize(void) {
    size_t size = sizeof (fgGfxMaterial);
    size += name.length() +
            ambientTexName.length() +
            diffuseTexName.length() +
            specularTexName.length() +
            normalTexName.length();
    size += unknownParam.size() * (sizeof (std::string) * 2);
    return size;
}

/**
 * 
 * @param material
 */
fgGfxMaterial::fgGfxMaterial(const fgGfxMaterial & material) {
    //*this = material;

    this->ambientTexHandle.copyFrom(material.ambientTexHandle);
    this->diffuseTexHandle.copyFrom(material.diffuseTexHandle);
    this->specularTexHandle.copyFrom(material.specularTexHandle);
    this->normalTexHandle.copyFrom(material.normalTexHandle);

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

    this->ambientTexName = material.ambientTexName;
    this->diffuseTexName = material.diffuseTexName;
    this->specularTexName = material.specularTexName;
    this->normalTexName = material.normalTexName;

    this->unknownParam = material.unknownParam;
}
