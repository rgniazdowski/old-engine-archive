/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXModelResource.h"
#include "tiny_obj_loader.h"
#include "Resource/fgResourceErrorCodes.h"

/*
 *
 */
fgGfxModelResource::fgGfxModelResource() :
	m_materialOverride(NULL),
	m_modelType(FG_GFX_MODEL_RES_INVALID),
	m_isMultitextured(FG_FALSE),
	m_isTextured(FG_FALSE),
	m_hasMaterial(FG_FALSE),
	m_isInterleaved(FG_TRUE)
{
	memset(m_numData, 0, sizeof(m_numData));
	m_resType = FG_RESOURCE_TEXTURE;
}

/*
 *
 */
fgGfxModelResource::fgGfxModelResource(const char *path) :
	m_materialOverride(NULL),
	m_modelType(FG_GFX_MODEL_RES_INVALID),
	m_isMultitextured(FG_FALSE),
	m_isTextured(FG_FALSE),
	m_hasMaterial(FG_FALSE),
	m_isInterleaved(FG_TRUE),
	fgResource(path)
{
	m_resType = FG_RESOURCE_TEXTURE;
}

/*
 *
 */
fgGfxModelResource::fgGfxModelResource(std::string& path) : 
	m_materialOverride(NULL),
	m_modelType(FG_GFX_MODEL_RES_INVALID),
	m_isMultitextured(FG_FALSE),
	m_isTextured(FG_FALSE),
	m_hasMaterial(FG_FALSE),
	m_isInterleaved(FG_TRUE),
	fgResource(path)
{
	m_resType = FG_RESOURCE_TEXTURE;
}

/*
 * Clears the class data, this actually does not free allocated memory,
 * just resets base class attributes
 */
void fgGfxModelResource::clear(void)
{
	fgResource::clear();
	m_materialOverride = NULL;
	m_modelType = FG_GFX_MODEL_RES_INVALID;
	m_isTextured = FG_FALSE;
	m_isMultitextured = FG_FALSE;
	m_hasMaterial = FG_FALSE;
	m_isInterleaved = FG_TRUE;
	memset(m_numData, 0, sizeof(m_numData));
}

// #FIXME #PLOX
fgBool fgGfxModelResource::_loadOBJ(void)
{
	if(getFilePath(m_quality).empty()) {
		return FG_FALSE;
	}
	// #FIXME - should not use tinyobj types here
	std::vector<tinyobj::shape_t> shapes;
	std::string mtl_basepath = fgPath::dirName(getFilePath());
	std::string err = tinyobj::LoadObj(shapes, getFilePathStr(m_quality), mtl_basepath.c_str());

	if(!err.empty()) {
		FG_LOG::PrintError("Error while loading model: %s", err.c_str());
		return FG_FALSE;
	}
	memset(m_numData, 0, sizeof(m_numData));
	m_isReady = FG_FALSE;
	m_size = 0;
	std::vector<tinyobj::shape_t>::iterator begin, end, itor;
	begin=shapes.begin(); end=shapes.end(); itor=begin;
	if(shapes.empty()) {
		FG_LOG::PrintError("There is no shapes in model file: '%s'", getFilePathStr());
	}
	int n = 0;
	for(;itor!=end;itor++) {
		m_numShapes++;
		tinyobj::shape_t & tinyshape = (*itor);
		m_shapes.push_back();
		n = m_shapes.size()-1;
		FG_LOG::PrintDebug("Model '%s': found shape '%s'", getNameStr(), tinyshape.name.c_str());
		m_shapes[n].name = tinyshape.name;
		m_shapes[n].material = new fgGfxMaterial(tinyshape.material);
		m_numMaterials++;
		if(m_isInterleaved)
			m_shapes[n].mesh = new fgGfxMeshAoS(tinyshape.mesh);
		else
			m_shapes[n].mesh = new fgGfxMeshSoA(tinyshape.mesh);
		m_numVertices += m_shapes[n].mesh->getNumVertices();
		m_numNormals += m_shapes[n].mesh->getNumNormals();
		m_numUVs += m_shapes[n].mesh->getNumUVs();
		m_numIndices += m_shapes[n].mesh->getNumIndices();
		tinyshape.mesh.indices.clear();
		tinyshape.mesh.normals.clear();
		tinyshape.mesh.positions.clear();
		tinyshape.mesh.texcoords.clear();
		tinyshape.name.clear();
		tinyshape.material.unknown_parameter.clear();
		m_size += m_shapes[n].getSize();
	}
	shapes.clear();
	if(!m_materialOverride)
		m_materialOverride = new fgGfxMaterial();
	m_size += m_materialOverride->getSize();
	FG_LOG::PrintDebug("Loaded OBJ file: total size in bytes: %d", m_size);
	FG_LOG::PrintDebug("Model '%s': vertices: %d, indices: %d, uvs: %d", getNameStr(), 
		m_numVertices, m_numIndices, m_numUVs);
	return FG_TRUE;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
fgBool fgGfxModelResource::create(void)
{
	if(m_isReady || !isDisposed()) {
		return FG_TRUE;
	}
	clearStatus();
	m_size = 0;
	if(getFilePath(m_quality).empty()) {
		FG_LOG::PrintError("%s(%d): file path is empty on create", fgPath::fileName(__FILE__), __LINE__-1); 
		// #TODO error handling / reporting
		return FG_FALSE;
	}
	setModelTypeFromFilePath();
	if(m_modelType == FG_GFX_MODEL_RES_INVALID) {
		FG_LOG::PrintError("%s(%d): model file type is invalid", fgPath::fileName(__FILE__), __LINE__-1); 
		// #TODO error handling / reporting
		return FG_FALSE;
	}
	switch(m_modelType)
	{
	case FG_GFX_MODEL_RES_CUSTOM:
		break;

	case FG_GFX_MODEL_RES_3DS:
		break;
		
	case FG_GFX_MODEL_RES_OBJ:
		FG_LOG::PrintDebug("Preparing to load an OBJ file for model: '%s'", getNameStr());
		if(!_loadOBJ()) {
			return FG_FALSE;
		}
		m_isReady = FG_TRUE;
		reportSuccess(FG_ERRNO_RESOURCE_OK, "Successfully loaded an OBJ model file: '%s'", getFilePathStr());
		break;

	case FG_GFX_MODEL_RES_BLEND:
		break;

	case FG_GFX_MODEL_RES_DAE:
		break;

	case FG_GFX_MODEL_RES_DXF:
		break;

	case FG_GFX_MODEL_RES_FBX:
		break;

	case FG_GFX_MODEL_RES_LWO:
		break;

	case FG_GFX_MODEL_RES_OFF:
		break;

	case FG_GFX_MODEL_RES_X:
		break;

	default:
		return FG_FALSE;
		break;
	};

	if(!m_size) return FG_FALSE;

	return FG_TRUE;
}

/*
 * Destroy all loaded data including additional metadata (called with deconstructor)
 */
void fgGfxModelResource::destroy(void)
{
	dispose();
	clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool fgGfxModelResource::recreate(void)
{
	dispose();
	return create();
}

/*
 * Dispose completely of the all loaded data, free all memory
 */
void fgGfxModelResource::dispose(void)
{
	int n = (int)m_shapes.size();
	for(int i=0;i<n;i++) {
		m_shapes[i].clear();
	}
	m_shapes.clear_optimised();
	if(m_materialOverride) {
		delete m_materialOverride;
	}
	m_materialOverride = NULL;
	m_hasMaterial = FG_FALSE;
	m_isReady = FG_FALSE;
}

/*
 * Check if resource is disposed (not loaded yet or disposed after)
 */
fgBool fgGfxModelResource::isDisposed(void) const
{
	return (fgBool)(m_shapes.empty());
}
