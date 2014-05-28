/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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
#include "../fgResourceManager.h"
#include "../Math/fgMathLib.h"

#include "fgGFXMaterial.h"

namespace FG_GFX {

	struct fgGfxMesh
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

	};

	struct fgGfxShape
	{
		std::string		name;
		fgGfxMaterial   material;
		fgGfxMesh		mesh;

		void clear(void)
		{
			mesh.clear();
			material.clear();
		}
	};

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
		fgGfxModelResType m_modelResourceType;
		std::string m_modelName;
		bool	m_isMultitextured;
		bool	m_isTextured;
		bool	m_hasMaterial;

		union {
			struct {
				union {
					unsigned int m_numVertices;
					unsigned int m_numPoints;
				};
				unsigned int m_numNormals;		
				unsigned int m_numUVs;
				unsigned int m_numIndices;
				unsigned int m_numTriangles;
				unsigned int m_numPolygons;
				unsigned int m_numShapes;
				unsigned int m_numMaterials;
			};
			unsigned int m_numData[8];
		};
		fgGfxMaterial m_materialOverride;
		fgArrayVector<fgGfxShape> m_shapes;
	};

};
#endif