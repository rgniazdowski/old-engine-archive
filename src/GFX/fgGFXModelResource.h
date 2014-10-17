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
    #define	FG_GFX_MODEL_RES_X			0x0F9

class fgGfxModelResource : public fgResource {
public:
    typedef fgVector<fgGfxShape *> modelShapes;
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
    // 
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

    // 
    fgBool setModelTypeFromFilePath(void) {
        if(getFilePath(m_quality).empty())
            return FG_FALSE;
        return setModelTypeFromFilePath(getFilePath(m_quality));
    }

    fgBool _loadOBJ(void);

public:
    //
    modelShapes & getRefShapes(void) {
        return m_shapes;
    }

    //
    fgGfxMaterial* getMainMaterial(void) const {
        return m_materialOverride;
    }

    //
    fgGFXuint getModelType(void) const {
        return m_modelType;
    }

    //
    fgBool isMultitextured(void) const {
        return m_isMultitextured;
    }

    //
    fgBool isTextured(void) const {
        return m_isTextured;
    }

    //
    fgBool hasMaterial(void) const {
        return m_hasMaterial;
    }

    //
    fgBool isInterleaved(void) const {
        return m_isInterleaved;
    }

    //
    void setInterleaved(fgBool toggle = FG_TRUE) {
        m_isInterleaved = toggle;
    }

    //
    fgGFXuint getNumVertices(void) const {
        return m_numVertices;
    }
    //
    fgGFXuint getNumNormals(void) const {
        return m_numNormals;
    }
    //
    fgGFXuint getNumUVs(void) const {
        return m_numUVs;
    }
    //
    fgGFXuint getNumIndices(void) const {
        return m_numIndices;
    }
    //
    fgGFXuint getNumTriangles(void) const {
        return m_numTriangles;
    }
    //
    fgGFXuint getNumPolygons(void) const {
        return m_numPolygons;
    }
    //
    fgGFXuint getNumShapes(void) const {
        return m_numShapes;
    }
    //
    fgGFXuint getNumMaterials(void) const {
        return m_numMaterials;
    }
    //
    const fgGFXuint* getNumData(void) const {
        return m_numData;
    }

protected:
    /// 
    fgGfxMaterial *m_materialOverride;
    /// 
    modelShapes m_shapes;
    /// 
    fgGFXuint m_modelType;
    /// 
    fgBool m_isMultitextured;
    /// 
    fgBool m_isTextured;
    /// 
    fgBool m_hasMaterial;
    /// 
    fgBool m_isInterleaved;

    union {

        struct {

            union {
                fgGFXuint m_numVertices;
                fgGFXuint m_numPoints;
            };
            fgGFXuint m_numNormals;
            fgGFXuint m_numUVs;
            fgGFXuint m_numIndices;
            fgGFXuint m_numTriangles;
            fgGFXuint m_numPolygons;
            fgGFXuint m_numShapes;
            fgGFXuint m_numMaterials;
        };
        fgGFXuint m_numData[8];
    };

};

#endif /* _FG_GFX_MODEL_RESOURCE_H_ */
