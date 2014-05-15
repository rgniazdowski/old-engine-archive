/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_GFX_MODEL_RESOURCE_H_
#define _FG_GFX_MODEL_RESOURCE_H_

#include <string>
#include <map>

#include "fgGFXTypes.h"
#include "../fgCommon.h"
#include "../fgResource.h"
#include "../Math/fgMathLib.h"

typedef struct
{
    std::string name;

	fgColor4f ambient;
    fgColor4f diffuse;
    fgColor4f specular;
    fgColor4f transmittance;
    fgColor4f emission;
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

	void clear(void)
	{
		// #TODO - here is the place to call resource manager and decrease reference count for the used textures
		// #TODO - ! remember to change the whole reference mechanism to be more automatic (if its even possible)
	}
} fgGfxMaterial;

typedef struct
{
	fgArrayVector<float>          vertices;
    fgArrayVector<float>          normals;
    fgArrayVector<float>          uvs;
    fgArrayVector<unsigned int>   indices;

	void clear(void)
	{
		vertices.clear_optimised();
		normals.clear_optimised();
		uvs.clear_optimised();
		indices.clear_optimised();
	}

} fgGfxMesh;

typedef struct
{
    std::string		name;
	fgGfxMaterial   material;
    fgGfxMesh		mesh;

	void clear(void)
	{
		mesh.clear();
		material.clear();
	}
} fgGfxShape;

class fgGfxModelResource : public fgResource
{
public:
	enum fgGfxModelResType {
		// Custom 3d model file format
		FG_GFX_MODEL_RES_CUSTOM,
		// 3DS - Autodesk 3ds Max 3D
		FG_GFX_MODEL_RES_3DS, 
		// OBJ - Wavefront Technologies
		FG_GFX_MODEL_RES_OBJ,
		// BLEND - Blender file database
		FG_GFX_MODEL_RES_BLEND,
		// DAE - COLLADA
		FG_GFX_MODEL_RES_DAE,
		// DXF - AutoCAD, Drawing Exchange Format - CAD data file format developed by Autodesk
		FG_GFX_MODEL_RES_DXF,
		// FBX - Autodesk exchange - exchange format, in particular for interoperability between Autodesk products and other Digital content creation (DCC) software packages
		FG_GFX_MODEL_RES_FBX,
		// LWO - Lightwave - LightWave high-end software file format
		FG_GFX_MODEL_RES_LWO,
		// OFF - Object File Format 
		FG_GFX_MODEL_RES_OFF,
		// X - DirectX 3D Model
		FG_GFX_MODEL_RES_X
	};
protected:
	fgArrayVector<fgGfxShape> m_shapes;
	bool	m_isMultitextured;
	bool	m_isTextured;
	bool	m_hasMaterial;
	unsigned int m_numPolygons;
	unsigned int m_numVertices;
	unsigned int m_numTriangles;
	unsigned int m_numNormals;
	unsigned int m_numIndices;
	unsigned int m_numUVs;
	unsigned int m_numShapes;
	unsigned int m_numMaterials;
	fgGfxMaterial m_materialOverride;
};
#endif