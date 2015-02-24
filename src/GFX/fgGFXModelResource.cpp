/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXModelResource.h"
#include "fgTinyObj.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceErrorCodes.h"
#include "Util/fgPath.h"

using namespace fg;

/**
 * 
 */
gfx::CModelResource::CModelResource() :
CResource(),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_isMultitextured(FG_FALSE),
m_isTextured(FG_FALSE),
m_hasMaterial(FG_FALSE),
m_isInterleaved(FG_TRUE) {
    memset(m_numData, 0, sizeof (m_numData));
    base_type::m_resType = resource::MODEL3D;
}

/**
 * 
 * @param path
 */
gfx::CModelResource::CModelResource(const char *path) :
CResource(path),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_isMultitextured(FG_FALSE),
m_isTextured(FG_FALSE),
m_hasMaterial(FG_FALSE),
m_isInterleaved(FG_TRUE) {
    base_type::m_resType = resource::MODEL3D;
}

/**
 * 
 * @param path
 */
gfx::CModelResource::CModelResource(std::string& path) :
CResource(path),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_isMultitextured(FG_FALSE),
m_isTextured(FG_FALSE),
m_hasMaterial(FG_FALSE),
m_isInterleaved(FG_TRUE) {
    base_type::m_resType = resource::MODEL3D;
}

/**
 * Clears the class data, this actually does not free allocated memory,
 * just resets base class attributes
 */
void gfx::CModelResource::clear(void) {
    base_type::clear();
    m_materialOverride = NULL;
    m_modelType = MODEL_INVALID;
    m_isTextured = FG_FALSE;
    m_isMultitextured = FG_FALSE;
    m_hasMaterial = FG_FALSE;
    m_isInterleaved = FG_TRUE;
    memset(m_numData, 0, sizeof (m_numData));
}

/**
 * 
 * @param path
 * @return 
 */
fgBool gfx::CModelResource::setModelTypeFromFilePath(std::string &path) {
    if(m_modelType == MODEL_BUILTIN) {
        return FG_TRUE;
    }
    const char *ext = path::fileExt(path.c_str());
    if(!ext)
        return FG_FALSE;
    m_modelType = MODEL_INVALID;
    if(strcasecmp(ext, FG_GFX_MODEL_RES_3DS_EXTENSION) == 0) {
        m_modelType = MODEL_3DS;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_OBJ_EXTENSION) == 0) {
        m_modelType = MODEL_OBJ;
    }
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CModelResource::refreshInternalData(void) {
    memset(m_numData, 0, sizeof (m_numData));
    this->m_size = 0;
    ShapesVecItor begin, end, itor;
    begin = this->m_shapes.begin();
    end = this->m_shapes.end();
    itor = begin;
    if(this->m_shapes.empty()) {
        FG_LOG_ERROR("GFX.Model: There is no shapes in model file: '%s'", getFilePathStr());
        return FG_FALSE;
    }
    for(; itor != end; itor++) {
        m_numShapes++;
        SShape *shape = (*itor);
        FG_LOG_DEBUG("GFX.Model: '%s': found shape '%s'", getNameStr(), shape->name.c_str());
        FG_LOG_DEBUG("GFX.Model: shape '%s': vec[%d], norm[%d], uvs[%d]", shape->name.c_str(), shape->mesh->getNumVertices(), shape->mesh->getNumNormals(), shape->mesh->getNumUVs());
        if(shape->material) {
            m_numMaterials++;
#if 0
            if(base_type::m_pManager) {
                CResource *tex = NULL;
                // Ambient texture handle lookup
                tex = ((resource::CResourceManager *)base_type::m_pManager)->request(shape->material->ambientTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        shape->material->ambientTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Diffuse texture handle lookup
                tex = ((resource::CResourceManager *)base_type::m_pManager)->request(shape->material->diffuseTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        shape->material->diffuseTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Specular texture handle lookup
                tex = ((resource::CResourceManager *)base_type::m_pManager)->request(shape->material->specularTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        shape->material->specularTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Normal texture handle lookup
                tex = ((resource::CResourceManager *)base_type::m_pManager)->request(shape->material->normalTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        shape->material->normalTex = static_cast<CTextureResource *>(tex);
                    }
                }
            }
#endif
        }

        if(shape->mesh) {
            m_numVertices += shape->mesh->getNumVertices();
            m_numNormals += shape->mesh->getNumNormals();
            m_numUVs += shape->mesh->getNumUVs();
            m_numIndices += shape->mesh->getNumIndices();
            // #FIXME
            m_numTriangles += shape->mesh->getNumIndices() / 3;
        }
        this->m_size += shape->getDataSize();
    }
    if(!m_materialOverride) {
        if(!m_numShapes)
            m_materialOverride = new SMaterial();
        else
            m_materialOverride = new SMaterial(*this->m_shapes[0]->material);
    }
    this->m_size += m_materialOverride->getDataSize();
    FG_LOG_DEBUG("GFX.Model: '%s': vertices[%d], normals[%d], indices[%d], uvs[%d], size(B)[%d]", getNameStr(),
                 m_numVertices, m_numNormals, m_numIndices, m_numUVs, m_size);
    return FG_TRUE;
}

/**
 * 
 * @param shape
 */
void gfx::CModelResource::addShape(SShape *shape) {
    if(!shape)
        return;
    if(shape->name.empty()) {
        shape->name = "XShape1";
    }
    m_shapes.push_back(shape);
}

/**
 * 
 * @param mesh
 * @param name
 */
void gfx::CModelResource::addShape(SMeshBase *mesh, const char *name) {
    if(!mesh || !name) {
        return;
    }
    if(!name[0]) {
        return;
    }

    SShape *shape = new SShape();
    shape->name = name;
    shape->mesh = mesh;
    m_shapes.push_back(shape);
}

/**
 * 
 * @param mesh
 * @param name
 */
void gfx::CModelResource::addShape(SMeshBase *mesh, const std::string& name) {
    if(!mesh || name.empty()) {
        return;
    }

    SShape *shape = new SShape();
    shape->name = name;
    shape->mesh = mesh;
    m_shapes.push_back(shape);
}

/**
 * 
 * @return 
 */
fgBool gfx::CModelResource::loadWavefrontObj(void) {
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    std::string err;
    std::string mtl_basepath = fg::path::dirName(getFilePath());
    err = fgTinyObj::LoadObj(this->m_shapes, getFilePathStr(this->m_quality), mtl_basepath.c_str(), m_isInterleaved);
    if(!err.empty()) {
        FG_LOG_ERROR("Error while loading model: '%s'", err.c_str());
        this->m_shapes.clear();
        return FG_FALSE;
    }
    this->m_isReady = FG_FALSE;
    refreshInternalData();
    return FG_TRUE;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
fgBool gfx::CModelResource::create(void) {
    if(this->m_isReady || !isDisposed()) {
        return FG_TRUE;
    }
    this->m_size = 0;
    if(m_modelType != MODEL_BUILTIN) {
        if(getFilePath(this->m_quality).empty()) {
            FG_LOG_ERROR("%s(%d): file path is empty on create", fg::path::fileName(__FILE__), __LINE__ - 1);
            // #TODO error handling / reporting
            return FG_FALSE;
        }
        setModelTypeFromFilePath();
        if(m_modelType == MODEL_INVALID) {
            FG_LOG_ERROR("%s(%d): model file type is invalid", fg::path::fileName(__FILE__), __LINE__ - 1);
            // #TODO error handling / reporting
            return FG_FALSE;
        }
    }
    switch(m_modelType) {
        case MODEL_CUSTOM:
            break;

        case MODEL_3DS:
            break;

        case MODEL_OBJ:
            FG_LOG_DEBUG("Preparing to load an OBJ file for model: '%s'", getNameStr());
            if(!loadWavefrontObj()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            // #FIXME - special tag type for Gfx Model Resource !
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded an OBJ model file: '%s'", getFilePathStr());
            break;

        case MODEL_BLEND:
            break;

        case MODEL_DAE:
            break;

        case MODEL_DXF:
            break;

        case MODEL_FBX:
            break;

        case MODEL_LWO:
            break;

        case MODEL_OFF:
            break;

        case MODEL_X:
            break;

        case MODEL_BUILTIN:
            if(m_shapes.size()) {
                // It means that there is some shape in the array.
                // With this model type it is probably custom allocated
                refreshInternalData();
                this->m_isReady = FG_TRUE;
            }
            break;

        default:
            return FG_FALSE;
            break;
    };

    if(!this->m_size) return FG_FALSE;
    this->updateAABB();
    return FG_TRUE;
}

/*
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void gfx::CModelResource::destroy(void) {
    dispose();
    clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool gfx::CModelResource::recreate(void) {
    if(m_modelType != ModelType::MODEL_BUILTIN) {
        // only dispose on reacreate when modelType is not BuiltIn
        dispose();
    }
    return create();
}

/*
 * Dispose completely of the all loaded data, free all memory
 */
void gfx::CModelResource::dispose(void) {
    int n = (int)m_shapes.size();
    for(int i = 0; i < n; i++) {
        SShape *shape = m_shapes[i];
        m_shapes[i] = NULL;
        delete shape;
        shape = NULL;
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
fgBool gfx::CModelResource::isDisposed(void) const {
    return (fgBool)(/*m_shapes.empty() &&*/!m_isReady && !m_size);
}

/**
 * 
 */
void gfx::CModelResource::updateAABB(void) {
    if(m_shapes.empty()) {
        return;
    }
    int n = m_shapes.size();
    m_aabb.invalidate();
    for(int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh) {
            m_shapes[i]->updateAABB();
            m_shapes[i]->mesh->fixCenter(); 
            m_aabb.merge(m_shapes[i]->mesh->aabb);
        }
    }
}

/*
 *
 */
fgBool gfx::CModelResource::genBuffers(void) {
    if(m_shapes.empty()) {
        return FG_FALSE;
    }
    int n = m_shapes.size();
    for(int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh) {
            m_shapes[i]->mesh->genBuffers();
        }
    }
    return FG_TRUE;
}

/*
 *
 */
fgBool gfx::CModelResource::deleteBuffers(void) {
    if(m_shapes.empty()) {
        return FG_FALSE;
    }
    int n = m_shapes.size();
    for(int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh) {
            m_shapes[i]->mesh->deleteBuffers();
        }
    }
    return FG_TRUE;
}
