/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MODEL_RESOURCE_H_
    #define _FG_GFX_MODEL_RESOURCE_H_

    #include "fgTypes.h"
    #include "fgGFXModelTypes.h"
    #include "Resource/fgResource.h"

// invalid / not selected file format
    #define FG_GFX_MODEL_RES_INVALID	0x000
// Custom 3d model file format
    #define	FG_GFX_MODEL_RES_CUSTOM		0x0F0
// 3DS - Autodesk 3ds Max 3D
    #define	FG_GFX_MODEL_RES_3DS		0x0F1
// OBJ - Wavefront Technologies
    #define	FG_GFX_MODEL_RES_OBJ		0x0F2
// BLEND - Blender file database
    #define	FG_GFX_MODEL_RES_BLEND		0x0F3
// DAE - COLLADA
    #define	FG_GFX_MODEL_RES_DAE		0x0F4
// DXF - AutoCAD, Drawing Exchange Format - CAD data file format developed by Autodesk
    #define	FG_GFX_MODEL_RES_DXF		0x0F5
// FBX - Autodesk exchange - exchange format, in particular for interoperability between Autodesk products and other Digital content creation (DCC) software packages
    #define	FG_GFX_MODEL_RES_FBX		0x0F6
// LWO - Lightwave - LightWave high-end software file format
    #define	FG_GFX_MODEL_RES_LWO		0x0F7
// OFF - Object File Format 
    #define	FG_GFX_MODEL_RES_OFF		0x0F8
// X - DirectX 3D Model
    #define	FG_GFX_MODEL_RES_X		0x0F9

/*
 * Class definition for Model Resource
 * This resource loads various types of models
 * Provides functions also for generation of VBOs
 */
class fgGfxModelResource : public fgResource {
public:
    // Type definition for vector holding model shapes
    typedef fgVector<fgGfxShape *> modelShapes;
    // Type definition for special vector iterator
    typedef modelShapes::iterator modelShapesItor;

public:
    //
    fgGfxModelResource();
    //
    fgGfxModelResource(const char *path);
    //
    fgGfxModelResource(std::string& path);
    //
    virtual ~fgGfxModelResource() {
        destroy();
    }

    FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgGfxModelResource)
    
protected:
    // Clears the class data, this actually does not free allocated memory,
    // just resets base class attributes
    virtual void clear(void);
    
public:
    // Create function loads/interprets data from file in ROM and place it in RAM memory.
    virtual fgBool create(void);
    
    // Destroy all loaded data including additional metadata (called with deconstructor)
    virtual void destroy(void);
    
    // Reloads any data, recreates the resource (refresh)
    virtual fgBool recreate(void);
    
    // Dispose completely of the all loaded data, free all memory
    virtual void dispose(void);
    
    // Check if resource is disposed (not loaded yet or disposed after)
    virtual fgBool isDisposed(void) const;

protected:
    // Determine the model type identifier from the file extension
    fgBool setModelTypeFromFilePath(std::string &path) {
        const char *ext = fgPath::fileExt(path.c_str());
        if(!ext)
            return FG_FALSE;
        m_modelType = FG_GFX_MODEL_RES_INVALID;
        if(strcasecmp(ext, FG_GFX_MODEL_RES_3DS_EXTENSION) == 0) {
            m_modelType = FG_GFX_MODEL_RES_3DS;
        } else if(strcasecmp(ext, FG_GFX_MODEL_RES_OBJ_EXTENSION) == 0) {
            m_modelType = FG_GFX_MODEL_RES_OBJ;
        }
        return FG_TRUE;
    }

    // Determine the model type identifier from the file extension
    fgBool setModelTypeFromFilePath(void) {
        if(getFilePath(m_quality).empty())
            return FG_FALSE;
        return setModelTypeFromFilePath(getFilePath(m_quality));
    }

    // This helper function loads the proper .OBJ model file
    fgBool _loadOBJ(void);

public:
    // Returns the reference to the shapes' array
    modelShapes & getRefShapes(void) {
        return m_shapes;
    }

    // Generates the GFX buffers (VBO) from the model data
    fgBool genBuffers(void);
    
    // Deletes/releases the GFX buffers (VBO)
    fgBool deleteBuffers(void);
    
    // Returns the pointer to the main material (override)
    fgGfxMaterial* getMainMaterial(void) const {
        return m_materialOverride;
    }

    // Returns the specific model type identifier
    fgGFXuint getModelType(void) const {
        return m_modelType;
    }

    // Returns whether the model is mutli-textured
    fgBool isMultitextured(void) const {
        return m_isMultitextured;
    }

    // Returns whether model is textured
    fgBool isTextured(void) const {
        return m_isTextured;
    }

    // Returns whether the model has any kind of material
    fgBool hasMaterial(void) const {
        return m_hasMaterial;
    }

    // Returns whether the data in the model is interleaved
    fgBool isInterleaved(void) const {
        return m_isInterleaved;
    }

    // Set data to be interleaved (requires explicit reload of the data from file)
    void setInterleaved(fgBool toggle = FG_TRUE) {
        m_isInterleaved = toggle;
    }

    // Number of vertices
    fgGFXuint getNumVertices(void) const {
        return m_numVertices;
    }
    // Number of normals
    fgGFXuint getNumNormals(void) const {
        return m_numNormals;
    }
    // Number of UVs - texture coords
    fgGFXuint getNumUVs(void) const {
        return m_numUVs;
    }
    // Number of indices
    fgGFXuint getNumIndices(void) const {
        return m_numIndices;
    }
    // Number of triangles
    fgGFXuint getNumTriangles(void) const {
        return m_numTriangles;
    }
    // Number of all polygons in the model
    fgGFXuint getNumPolygons(void) const {
        return m_numPolygons;
    }
    // Number of shapes used in the model
    fgGFXuint getNumShapes(void) const {
        return m_numShapes;
    }
    // Get number of materials used by this model
    fgGFXuint getNumMaterials(void) const {
        return m_numMaterials;
    }
    // Return pointer to the array holding specific info
    const fgGFXuint* getNumData(void) const {
        return m_numData;
    }

protected:
    /// Global material override definition
    fgGfxMaterial *m_materialOverride;
    /// Array holding all basic shapes of the model
    modelShapes m_shapes;
    /// Identifier of the model type - based on the input data file extension
    fgGFXuint m_modelType;
    /// Is model multitextured?
    fgBool m_isMultitextured;
    /// Is model textured?
    fgBool m_isTextured;
    /// Does the model have any kind of material?
    fgBool m_hasMaterial;
    /// Is data interleaved (soa or aos?)
    fgBool m_isInterleaved;

    union {

        struct {

            union {
                /// Number of vertices in the model
                fgGFXuint m_numVertices;
                /// Number of points in the model
                fgGFXuint m_numPoints;
            };
            /// Number of all normal coords in the model
            fgGFXuint m_numNormals;
            /// Number of all texture coords (in all meshes/shapes)
            fgGFXuint m_numUVs;
            /// Number of indices
            fgGFXuint m_numIndices;
            /// Number of triangles in all meshes
            fgGFXuint m_numTriangles;
            /// Number of all polygons
            fgGFXuint m_numPolygons;
            /// Number of shapes in the model
            fgGFXuint m_numShapes;
            /// Number of used materials
            fgGFXuint m_numMaterials;
        };
        /// Special array containing all data (number of specific vertex data)
        fgGFXuint m_numData[8];
    };

};

typedef fgGfxModelResource fgGfxModel;

#endif /* _FG_GFX_MODEL_RESOURCE_H_ */
