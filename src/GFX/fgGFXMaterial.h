/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MATERIAL_H_
#define _FG_GFX_MATERIAL_H_

#include "fgCommon.h"
#include "fgGFXTypes.h"
#include <string>

#include "Resource/fgResource.h"
#include "Resource/fgResourceManager.h"
#include "Math/fgMathLib.h"

// Base structure describing material in graphics rendering
struct fgGfxMaterial
{
public:
	std::string name;

	fgColor3f ambient;
	fgColor3f diffuse;
	fgColor3f specular;
	fgColor3f transmittance;
	fgColor3f emission;
		
	// The shininess parameter of the material
	float shininess;
	// Index of refraction parameter
	float ior;
	// The dissolve parameter of the material
	float dissolve;           // 1 == opaque; 0 == fully transparent
	// Illumination model (see http://www.fileformat.info/format/material/)
	int illuminationModel;

	// Name of the ambient texture
	std::string ambientTexName;
	// Name of the diffuse texture
	std::string diffuseTexName;
	// Name of the specular texture
	std::string specularTexName;
	// Name of the normal texture
	std::string normalTexName;

	//std::map<std::string, std::string> unknown_parameter; // #FIXME
	// Handle for the ambient texture
	FG_RHANDLE ambientTexHandle;
	// Handle for the diffuse texture
	FG_RHANDLE diffuseTexHandle;
	// Handle for the specular texture
	FG_RHANDLE specularTexHandle;
	// Handle for the normal texture
	FG_RHANDLE normalTexHandle;

    std::map<std::string, std::string> unknownParam;

	fgGfxMaterial()
	{
	}

	size_t getSize(void) 
	{
		size_t size = name.length() + sizeof(std::string);
		size += sizeof(fgColor3f) * 5;
		size += sizeof(float) * 3 + sizeof(int);
		size += sizeof(std::string) * 4;
		size += ambientTexName.length() + diffuseTexName.length() + specularTexName.length() + normalTexName.length();
		size += sizeof(FG_RHANDLE) * 4;
		return size;
	}

	fgGfxMaterial(const fgGfxMaterial & material)
	{
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

	// #FIXME #SERIOUSLY
#if 0
	fgGfxMaterial(tinyobj::material_t & material)
	{
		name = material.name;
		for(int i=0;i<3;i++)
			ambient[i] = material.ambient[i];
		for(int i=0;i<3;i++)
			diffuse[i] = material.diffuse[i];
		for(int i=0;i<3;i++)
			specular[i] = material.specular[i];
		for(int i=0;i<3;i++)
			transmittance[i] = material.transmittance[i];
		for(int i=0;i<3;i++)
			emission[i] = material.emission[i];
		shininess = material.shininess;
		ior = material.ior;
		dissolve = material.dissolve;
		illuminationModel = material.illum;
		ambientTexName = material.ambient_texname;
		diffuseTexName = material.diffuse_texname;
		specularTexName = material.specular_texname;
		normalTexName = material.normal_texname;
	}
#endif
	~fgGfxMaterial()
	{
		clear();
	}

	void clear(void)
	{
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
	}
};

#endif /* _FG_GFX_MATERIAL_H_ */
