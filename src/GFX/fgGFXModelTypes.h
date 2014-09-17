/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MODEL_TYPES_H_
#define _FG_GFX_MODEL_TYPES_H_

#include "fgGFXTypes.h"
#include "fgGFXMaterial.h"

// This needs fixing ! ! ! - but dont want to fuck with this any longer
// -- -- Need more generic class/struct for holding 3D data
// can also hold aos/soa in one struct (as a union)
/* Something like:
struct static3DData {
	union {
		struct soa {
			fgVector<fgGFXfloat>	vertices;  //3
			fgVector<fgGFXfloat>	normals;   //3
			fgVector<fgGFXfloat>	uvs;       //2
			fgVector<fgGFXuint>		indices;
		};
		struct aos {
			fgVector<fgVertex3>	vertices;
			fgVector<fgGFXuint>	indices;
		};
	};
	*getVertices*()
	***
};
*/
/*
Assuming the container has at least one element in it, you 
need to get the address of the initial element of the 
container, which you can get via:

(the address of the element at index 0)
	&something[0] or &something.front()

(the address of the element pointed to by the iterator returned by begin()).
	&*something.begin() 


*/

inline void fgGfxComputeNormal(const fgVector3f & v1, const fgVector3f & v2, const fgVector3f & v3, fgVector3f & normal)
{
	//glm::vec3 const & a = Triangle.Position[0];
	//glm::vec3 const & b = Triangle.Position[1];
	//glm::vec3 const & c = Triangle.Position[2];
	normal = glm::normalize(glm::cross(v3 - v1, v2 - v1));
} 

/*
 *
 */
struct fgGfxMeshBase
{
	virtual ~fgGfxMeshBase() { };
	virtual void clear(void) = 0;
	virtual fgBool isSoA(void) const = 0;
	virtual size_t getSize(void) = 0;
	virtual fgGFXuint getNumVertices(void) const = 0;
	virtual fgGFXuint getNumNormals(void) const = 0;
	virtual fgGFXuint getNumUVs(void) const = 0;
	virtual fgGFXuint getNumIndices(void) const = 0;
};

/*
 *
 */
struct fgGfxMeshSoA : fgGfxMeshBase
{
	fgVector<fgGFXfloat>	vertices;  //3
	fgVector<fgGFXfloat>	normals;   //3
	fgVector<fgGFXfloat>	uvs;       //2
	fgVector<fgGFXuint>		indices;

	fgGfxMeshSoA() {}
	// #FIXME #SERIOUSLY
	fgGfxMeshSoA(tinyobj::mesh_t & mesh)
	{
		int n = mesh.positions.size();
		vertices.reserve(n);
		for(int i=0;i<n;i++) {
			vertices.push_back(mesh.positions[i]);
		}
		n = mesh.normals.size();
		normals.reserve(n);
		for(int i=0;i<n;i++) {
			normals.push_back(mesh.normals[i]);
		}
		if(normals.empty()) {
			n = mesh.positions.size();
			for(int i=0;i<n/9;i+=9) {
				fgVector3f normal;
				fgVector3f v1(mesh.positions[i+0], mesh.positions[i+1], mesh.positions[i+2]);
				fgVector3f v2(mesh.positions[i+3], mesh.positions[i+4], mesh.positions[i+5]);
				fgVector3f v3(mesh.positions[i+6], mesh.positions[i+7], mesh.positions[i+8]);
				fgGfxComputeNormal(v1, v2, v3, normal);
				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);
			}
		}
		n = mesh.texcoords.size();
		uvs.reserve(n);
		for(int i=0;i<n;i++) {
			uvs.push_back(mesh.texcoords[i]);
		}
		n = mesh.indices.size();
		indices.reserve(n);
		for(int i=0;i<n;i++) {
			indices.push_back(mesh.indices[i]);
		}
	}

	virtual ~fgGfxMeshSoA() 
	{
		clear();
	}

	//
	virtual void clear(void)
	{
		vertices.clear_optimised();
		normals.clear_optimised();
		uvs.clear_optimised();
		indices.clear_optimised();
	}

	// 
	virtual fgBool isSoA(void) const {
		return FG_TRUE;
	}	

	//
	virtual size_t getSize(void) {
		size_t size = 0;
		size += sizeof(vertices) + sizeof(normals) + sizeof(uvs) + sizeof(indices);
		size += sizeof(fgGFXfloat) * vertices.size();
		size += sizeof(fgGFXfloat) * normals.size();
		size += sizeof(fgGFXfloat) * uvs.size();
		size += sizeof(fgGFXuint) * indices.size();
		return size;
	}

	virtual fgGFXuint getNumVertices(void) const {
		return (fgGFXuint)vertices.size();
	}

	virtual fgGFXuint getNumNormals(void) const {
		return (fgGFXuint)normals.size();
	}

	virtual fgGFXuint getNumUVs(void) const {
		return (fgGFXuint)uvs.size();
	}

	virtual fgGFXuint getNumIndices(void) const {
		return (fgGFXuint)indices.size();
	}
};

/*
 *
 */
struct fgGfxMeshAoS : fgGfxMeshBase
{
	fgVector<fgVertex3>	vertices;
	fgVector<fgGFXuint>	indices;

	fgGfxMeshAoS() { }

	// #FIXME #SERIOUSLY
	fgGfxMeshAoS(tinyobj::mesh_t & mesh) 
	{
		// pos, norm, uv
		int npos = mesh.positions.size();
		int nnorm = mesh.normals.size();
		int nuvs = mesh.texcoords.size();
		int nind = mesh.indices.size();
		FG_LOG::PrintDebug("fgGfxMeshAoS(tinyobj::mesh_t & mesh): npos: %d, nnorm: %d, nuvs: %d, nind: %d",
			npos,
			nnorm,
			nuvs,
			nind);
		vertices.reserve(npos);
		for(int i=0,k=0;i<npos;i+=3,k+=2) {
			fgVertex3 vertex;
			for(int j=0;j<3;j++)
				vertex.position[j] = mesh.positions[i+j];
			
			for(int j=0;j<3 && i+j<nnorm;j++)
				vertex.normal[j] = mesh.normals[i+j];
			
			for(int j=0;j<2 && k+j<nuvs;j++)
				vertex.uv[j] = mesh.texcoords[k+j];
			//vertices.push_back(mesh.positions[i]);
			if(vertices.size() < 15) {
			printf("Vertex[%d] pos:  {%.2f, %.2f, %.2f}\n", vertices.size(), vertex.position[0], vertex.position[1], vertex.position[2]);
			printf("Vertex[%d] norm: {%.2f, %.2f, %.2f}\n", vertices.size(), vertex.normal[0], vertex.normal[1], vertex.normal[2]);
			printf("Vertex[%d] uv:   {%.2f, %.2f}\n", vertices.size(), vertex.uv[0], vertex.uv[1]);
			} 
			vertices.push_back(vertex);
		}
		if(nnorm == 0) {
			// FIXME - this is soooo fucked up ....
			for(int i=2;i<npos;i++) {
				fgGfxComputeNormal(vertices[i].position, vertices[i-1].position, vertices[i-2].position, vertices[i].normal);
			}
		}
		indices.reserve(nind);
		for(int i=0;i<nind;i++) {
			indices.push_back(mesh.indices[i]);
			if(i < 15)
				printf("Index[%d] %d\n", i, mesh.indices[i]);
		}
	}
	
	virtual ~fgGfxMeshAoS()
	{
		clear();
	}

	//
	virtual void clear(void)
	{
		vertices.clear_optimised();
		indices.clear_optimised();
	}

	//
	virtual fgBool isSoA(void) const {
		return FG_FALSE;
	}

	//
	virtual size_t getSize(void) {
		size_t size = 0;
		size += sizeof(vertices) + sizeof(indices);
		size += sizeof(fgVertex3) * vertices.size();
		size += sizeof(fgGFXuint) * indices.size();
		return size;
	}

	virtual fgGFXuint getNumVertices(void) const {
		return (fgGFXuint)vertices.size();
	}

	virtual fgGFXuint getNumNormals(void) const {
		return (fgGFXuint)vertices.size();
	}

	virtual fgGFXuint getNumUVs(void) const {
		return (fgGFXuint)vertices.size();
	}

	virtual fgGFXuint getNumIndices(void) const {
		return (fgGFXuint)indices.size();
	}
};

/*
 *
 */
struct fgGfxShape
{
	std::string		name;
	fgGfxMaterial*	material;
	fgGfxMeshBase*	mesh;

	fgGfxShape() : material(NULL), mesh(NULL) { }
	~fgGfxShape() { clear(); }

	//
	void clear(void)
	{
		if(material)
			delete material;
		material = NULL;

		if(mesh)
			delete mesh;
		mesh = NULL;
		name.clear();
	}

	//
	size_t getSize(void)
	{
		size_t size = 0;
		size += name.length();
		size += sizeof(fgGfxShape);
		if(material)
			size += material->getSize();
		if(mesh)
			size += mesh->getSize();
		return size;
	}
};

// Custom 3d model file format
//#define	FG_GFX_MODEL_RES_CUSTOM		0x0F0
// 3DS - Autodesk 3ds Max 3D
#define	FG_GFX_MODEL_RES_3DS_EXTENSION		"3ds"
// OBJ - Wavefront Technologies
#define	FG_GFX_MODEL_RES_OBJ_EXTENSION		"obj"
// BLEND - Blender file database
#define	FG_GFX_MODEL_RES_BLEND_EXTENSION	"blend"
// DAE - COLLADA
#define	FG_GFX_MODEL_RES_DAE_EXTENSION		"dae"
// DXF - AutoCAD, Drawing Exchange Format - CAD data file format developed by Autodesk
#define	FG_GFX_MODEL_RES_DXF_EXTENSION		"dxf"
// FBX - Autodesk exchange - exchange format, in particular for interoperability between Autodesk products and other Digital content creation (DCC) software packages
#define	FG_GFX_MODEL_RES_FBX_EXTENSION		"fbx"
// LWO - Lightwave - LightWave high-end software file format
#define	FG_GFX_MODEL_RES_LWO_EXTENSION		"lwo"
// OFF - Object File Format 
#define	FG_GFX_MODEL_RES_OFF_EXTENSION		"off"
// X - DirectX 3D Model
#define	FG_GFX_MODEL_RES_X_EXTENSION		"x"

#endif /* _FG_GFX_MODEL_TYPES_H_ */
