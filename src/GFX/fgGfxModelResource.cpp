/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxModelResource.h"
#include "fgTinyObj.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceErrorCodes.h"
#include "Util/fgPath.h"

using namespace fg;

//------------------------------------------------------------------------------

#if defined(FG_USING_ASSIMP)
#include "assimp/Importer.hpp" // #FIXME IOSystem!
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "fgGfxAssimpHelper.h"
::Assimp::Importer* gfx::CModelResource::s_objImporter = NULL;
#endif
int gfx::CModelResource::s_cmrInstanceCount = 0;

//------------------------------------------------------------------------------

gfx::CModelResource::CModelResource() :
base_type(),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    memset(m_numData, 0, sizeof (m_numData));
    base_type::m_resType = resource::MODEL3D;
    s_cmrInstanceCount++;
#if defined(FG_USING_ASSIMP)
    if(!s_objImporter) {
        s_objImporter = new ::Assimp::Importer();
    }
#endif
}
//------------------------------------------------------------------------------

gfx::CModelResource::CModelResource(const char *path) :
base_type(path),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    base_type::m_resType = resource::MODEL3D;
    s_cmrInstanceCount++;
#if defined(FG_USING_ASSIMP)
    if(!s_objImporter) {
        s_objImporter = new ::Assimp::Importer();
    }
#endif
}
//------------------------------------------------------------------------------

gfx::CModelResource::CModelResource(std::string& path) :
base_type(path),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    m_modelFlags = NO_FLAGS;
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    base_type::m_resType = resource::MODEL3D;
    s_cmrInstanceCount++;
#if defined(FG_USING_ASSIMP)
    if(!s_objImporter) {
        s_objImporter = new ::Assimp::Importer();
    }
#endif
}
//------------------------------------------------------------------------------

gfx::CModelResource::~CModelResource() {
    s_cmrInstanceCount--;
    if(s_cmrInstanceCount == 0) {
#if defined(FG_USING_ASSIMP)
        if(s_objImporter) {
            delete s_objImporter;
            s_objImporter = NULL;
        }
#endif
    }
    if(s_cmrInstanceCount < 0) {
        // now this is highly unlikely!
        FG_LOG_DEBUG("CModelResource: For some reason instance count is below zero after destructor call.");
    }
    destroy();
}
//------------------------------------------------------------------------------

void gfx::CModelResource::clear(void) {
    base_type::clear();
    m_materialOverride = NULL;
    m_modelType = MODEL_INVALID;
    m_modelFlags = NO_FLAGS;
    base_type::m_resType = resource::MODEL3D;
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    memset(m_numData, 0, sizeof (m_numData));
}
//------------------------------------------------------------------------------

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
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_BLEND_EXTENSION) == 0) {
        m_modelType = MODEL_BLEND;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_DAE_EXTENSION) == 0) {
        m_modelType = MODEL_DAE;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_DXF_EXTENSION) == 0) {
        m_modelType = MODEL_DXF;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_FBX_EXTENSION) == 0) {
        m_modelType = MODEL_FBX;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_LWO_EXTENSION) == 0) {
        m_modelType = MODEL_LWO;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_OFF_EXTENSION) == 0) {
        m_modelType = MODEL_OFF;
    } else if(strcasecmp(ext, FG_GFX_MODEL_RES_X_EXTENSION) == 0) {
        m_modelType = MODEL_X;
    }
    return (fgBool)(m_modelType != MODEL_INVALID);
}
//------------------------------------------------------------------------------

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
    if(m_numMaterials) {
        setFlag(HAS_MATERIALS, FG_TRUE);
    }
    if(!m_materialOverride) {
        if(!m_numShapes) {
            m_materialOverride = new SMaterial();
        } else {
            m_materialOverride = new SMaterial(*this->m_shapes[0]->material);
        }
    }
    this->m_size += m_materialOverride->getDataSize();
    FG_LOG_DEBUG("GFX.Model: '%s': vertices[%d], normals[%d], indices[%d], uvs[%d], size(B)[%d]", getNameStr(),
                 m_numVertices, m_numNormals, m_numIndices, m_numUVs, m_size);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CModelResource::addShape(SShape *pShape) {
    if(!pShape)
        return;
    if(pShape->name.empty()) {
        pShape->name = "XShape1"; // #FIXME
    }
    m_shapes.push_back(pShape);
}
//------------------------------------------------------------------------------

gfx::SShape* gfx::CModelResource::addShape(SMeshBase *pMesh, const char *name) {
    if(!pMesh || !name) {
        return NULL;
    }
    if(!name[0]) {
        return NULL;
    }

    SShape *shape = new SShape();
    shape->name = name;
    shape->mesh = pMesh;
    m_shapes.push_back(shape);
    return shape;
}
//------------------------------------------------------------------------------

gfx::SShape* gfx::CModelResource::addShape(SMeshBase *pMesh, const std::string& name) {
    if(!pMesh || name.empty()) {
        return NULL;
    }

    SShape *shape = new SShape();
    shape->name = name;
    shape->mesh = pMesh;
    m_shapes.push_back(shape);
    return shape;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadWavefrontObj(void) {
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    std::string err;
    std::string mtl_basepath = path::dirName(getFilePath());
    err = fgTinyObj::LoadObj(this->m_shapes, getFilePathStr(this->m_quality), mtl_basepath.c_str(), isInterleaved());
    if(!err.empty()) {
        FG_LOG_ERROR("Error while loading model: '%s'", err.c_str());
        this->m_shapes.clear();
        return FG_FALSE;
    }
    this->m_isReady = FG_FALSE;
    refreshInternalData();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadFlexiObject(void) {
    return FG_FALSE; // TODO
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadAutodesk3ds(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadBlender(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadCollada(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadAutoCAD(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadAutodeskExchange(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadLightwaveObject(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadObjectFile(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::internal_loadDirectXModel(void) {
#if defined(FG_USING_ASSIMP)
    return internal_loadUsingAssimp();
#else
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    return FG_FALSE;
#endif
}
//------------------------------------------------------------------------------
#if defined(FG_USING_ASSIMP)

fgBool gfx::CModelResource::internal_loadUsingAssimp(void) {
    if(getFilePath(this->m_quality).empty()) {
        return FG_FALSE;
    }
    if(!s_objImporter)
        return FG_FALSE;
    const char *ext = path::fileExt(getCurrentFilePathStr());
    if(!ext)
        return FG_FALSE;

    if(s_objImporter->IsExtensionSupported(ext) == false) {
        FG_LOG_ERROR("GFX: '%s' model extension is not supported. Will not load '%s'.");
        return FG_FALSE;
    }
    // This functions uses assimp to load model representation;
    // Assimps' importer create a scene graph containing all the nodes in hierarchy.
    // In this loading procedure the scene graph will be ignored.
    // All models/meshes within the scene are saved as shapes of this model and
    // are pre-transformed based on nodes' transformation matrix.
    const ::aiScene* pScene = NULL;
    unsigned int defaultFlags = 0;

    setFlag(FIX_CENTER, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_TRUE);
    defaultFlags |= aiProcess_JoinIdenticalVertices;
    // defaultFlags |= aiProcess_MakeLeftHanded; // only for DirectX
    defaultFlags |= aiProcess_Triangulate;
    defaultFlags |= aiProcess_GenUVCoords;
    defaultFlags |= aiProcess_RemoveComponent;
    defaultFlags |= aiProcess_RemoveRedundantMaterials;
    defaultFlags |= aiProcess_SortByPType;
    defaultFlags |= aiProcess_TransformUVCoords;
    defaultFlags |= aiProcess_FlipUVs;

    //defaultFlags |= aiProcess_OptimizeGraph;
    // force generation of per vertex normals
    defaultFlags |= aiProcess_GenSmoothNormals;
    //defaultFlags |= aiProcess_CalcTangentSpace;
    // Remove not needed cameras and lights
    // tangents and bi-tangents are currently ignored #TODO
    s_objImporter->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
                                      aiComponent_CAMERAS |
                                      aiComponent_LIGHTS |
                                      aiComponent_COLORS |
                                      aiComponent_NORMALS |
                                      aiComponent_TANGENTS_AND_BITANGENTS);
    // Remove lines and points from the model - not used in rendering
    s_objImporter->SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE,
                                      aiPrimitiveType_LINE |
                                      aiPrimitiveType_POINT);
    // Set the smoothing angle limit
    s_objImporter->SetPropertyInteger(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80);

    pScene = s_objImporter->ReadFile(getCurrentFilePath(), defaultFlags);
    if(!pScene) {
        FG_LOG_ERROR("GFX: Failed to load model file: '%s': %s",
                     getCurrentFilePathStr(),
                     s_objImporter->GetErrorString());
        return FG_FALSE;
    }
    // DFS algorithm for searching through scene and generating gfx shapes
    CVector<aiNode*> nodeTransVec;
    nodeTransVec.reserve(16);
    std::stack<aiNode*> stack;
    aiMatrix4x4 aiTransform;

    stack.push(pScene->mRootNode);    
    while(!stack.empty()) {
        aiQuaternion quat;
        aiVector3D matPos, matScale;

        aiNode* pNode = stack.top();
        stack.pop();
        const fgBool isRoot = (fgBool)(pNode->mParent == NULL);
        for(unsigned int i = 0; i < pNode->mNumChildren; i++) {
            stack.push(pNode->mChildren[i]);
        }
        if(isRoot) {
            pNode->mTransformation.Decompose(matScale, quat, matPos);
            printf("%p: %s [Root] [t:%.2f;%.2f;%.2f] [rot:%.2f;%.2f;%.2f;%.2f] [scale:%.2f;%.2f;%.2f]\n",
                   pNode, pNode->mName.C_Str(),
                   matPos.x, matPos.y, matPos.z,
                   quat.w, quat.x, quat.y, quat.z,
                   matScale.x, matScale.y, matScale.z);
            continue;
        }
        std::string spacing;
        spacing.reserve(32);
        // need to generate modelMatrix and transform vertices accordingly
        aiNode* pSearchNode = pNode;
        while(pSearchNode) {
            nodeTransVec.push_back(pSearchNode);
            pSearchNode = pSearchNode->mParent;
            if(pSearchNode)
                spacing.append("  ");
        }
        nodeTransVec.reverse();
        aiTransform = aiMatrix4x4();
        unsigned int n = nodeTransVec.size();
        for(unsigned int i = 0; i < n; i++) {            
            aiTransform *= nodeTransVec[i]->mTransformation;
        }
        nodeTransVec.clear();
        aiTransform.Decompose(matScale, quat, matPos);

        printf("%s%p: %s [t:%.2f;%.2f;%.2f] [rot:%.2f;%.2f;%.2f;%.2f] [scale:%.2f;%.2f;%.2f]\n",
               spacing.c_str(), pNode, pNode->mName.C_Str(),
               matPos.x, matPos.y, matPos.z,
               quat.w, quat.x, quat.y, quat.z,
               matScale.x, matScale.y, matScale.z);
        if(!pNode->mNumMeshes) {
            printf("NO MESH AT NODE: %s\n", pNode->mName.C_Str());
        }
        for(unsigned int i = 0; i < pNode->mNumMeshes; i++) {
            aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
            if(!pMesh) {                
                continue;
            }
            SShape* pShape = new SShape();
            pShape->name.reserve(pNode->mName.length);
            pShape->name.append(pNode->mName.C_Str());
            m_shapes.push_back(pShape);

            if(isInterleaved()) {
                pShape->mesh = new SMeshAoS(); // mesh - array of structures
            } else {
                pShape->mesh = new SMeshSoA(); // mesh - structure of arrays
            }

            for(unsigned int fn = 0; fn < pMesh->mNumFaces; fn++) {
                struct aiFace* pFace = &pMesh->mFaces[fn];
                for(unsigned int fidx = 0; fidx < pFace->mNumIndices; fidx++) {
                    pShape->mesh->appendIndice(pFace->mIndices[fidx]);
                }
            }
            // Fix center and save displacement should be used together
            // In most cases using only save displacement may cause artifacts
            // as the objects will be moved twice: once by the model matrix
            // transformation, the second time because of the transformation
            // of vertices.
            // This may not be working properly for now. #FIXME
            if(isFixCenter()) {
                // Zero the transformation: the mesh will now appear at center (local)
                aiTransform.a4 = 0.0f;
                aiTransform.b4 = 0.0f;
                aiTransform.c4 = 0.0f;
            }
            if(isSaveDisplacement()) {
                // Save the displacement info (off-center transformation)
                assimp_helper::copyVector(pShape->mesh->displacement, matPos);
            }
            for(unsigned int vidx = 0; vidx < pMesh->mNumVertices; vidx++) {
                Vector3f pos, normal;
                Vector2f uv;
                assimp_helper::copyVector(normal, pMesh->mNormals[vidx]);
                if(pMesh->HasTextureCoords(0)) {
                    assimp_helper::copyVector(uv, pMesh->mTextureCoords[0][vidx]);
                }
                // aiVector3D is a little problematic (make some transform functions?)
                aiVector3D transPos = pMesh->mVertices[vidx];
                transPos *= aiTransform;
                assimp_helper::copyVector(pos, transPos);
                pShape->mesh->append(pos, normal, uv);
            }
            struct aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
            SMaterial* pNewMaterial = new SMaterial();
            // copy aiMaterial data to gfx::SMaterial
            assimp_helper::setupMaterial(pNewMaterial, pMaterial);
            pShape->material = pNewMaterial;

        } // for (mNumMeshes)
    } // while (stack not empty)

    s_objImporter->FreeScene();
    // reset the ready flag
    this->m_isReady = FG_FALSE;
    refreshInternalData(); // recalculate internals
    return FG_TRUE;
}
#endif
//------------------------------------------------------------------------------

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
            if(!internal_loadFlexiObject()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            break;

        case MODEL_3DS:
            FG_LOG_DEBUG("Preparing to load a 3DS file for model: '%s'", getNameStr());
            if(!internal_loadAutodesk3ds()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            break;

        case MODEL_OBJ:
            FG_LOG_DEBUG("Preparing to load an OBJ file for model: '%s'", getNameStr());
            if(!internal_loadWavefrontObj()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            // #FIXME - special tag type for Gfx Model Resource !
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded an OBJ model file: '%s'", getFilePathStr());
            break;

        case MODEL_BLEND:
            FG_LOG_DEBUG("Preparing to load a Blender file for model: '%s'", getNameStr());
            if(!internal_loadBlender()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded a Blender model file: '%s'", getFilePathStr());
            break;

        case MODEL_DAE:
            FG_LOG_DEBUG("Preparing to load a Collada file for model: '%s'", getNameStr());
            if(!internal_loadCollada()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded a Collada model file: '%s'", getFilePathStr());
            break;

        case MODEL_DXF:
            FG_LOG_DEBUG("Preparing to load an AutoCAD Exchange file for model: '%s'", getNameStr());
            if(!internal_loadAutoCAD()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded an AutoCAD Exchange model file: '%s'", getFilePathStr());
            break;

        case MODEL_FBX:
            FG_LOG_DEBUG("Preparing to load an Autodesk Exchange file for model: '%s'", getNameStr());
            if(!internal_loadAutodeskExchange()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded an Autodesk Exchange model file: '%s'", getFilePathStr());
            break;

        case MODEL_LWO:
            FG_LOG_DEBUG("Preparing to load a Lightwave object file for model: '%s'", getNameStr());
            if(!internal_loadLightwaveObject()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            break;

        case MODEL_OFF:
            FG_LOG_DEBUG("Preparing to load an OFF file for model: '%s'", getNameStr());
            if(!internal_loadObjectFile()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded an OFF model file: '%s'", getFilePathStr());
            break;

        case MODEL_X:
            FG_LOG_DEBUG("Preparing to load a DirectX file for model: '%s'", getNameStr());
            if(!internal_loadDirectXModel()) {
                return FG_FALSE;
            }
            this->m_isReady = FG_TRUE;
            FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Successfully loaded a DirectX model file: '%s'", getFilePathStr());
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
//------------------------------------------------------------------------------

void gfx::CModelResource::destroy(void) {
    dispose();
    clear();
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::recreate(void) {
    if(m_modelType != ModelType::MODEL_BUILTIN) {
        // only dispose on reacreate when modelType is not BuiltIn
        dispose();
    }
    return create();
}
//------------------------------------------------------------------------------

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
    setFlag(HAS_MATERIALS, FG_FALSE);
    base_type::m_isReady = FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::isDisposed(void) const {
    return (fgBool)(/*m_shapes.empty() &&*/!base_type::m_isReady && !base_type::m_size);
}
//------------------------------------------------------------------------------

void gfx::CModelResource::updateAABB(void) {
    if(m_shapes.empty()) {
        return;
    }
    int n = m_shapes.size();
    m_aabb.invalidate();
    for(int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh) {
            m_shapes[i]->updateAABB();
            if(isFixCenter())
                m_shapes[i]->mesh->fixCenter(isSaveDisplacement());
            m_aabb.merge(m_shapes[i]->mesh->aabb);
        }
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::genBuffers(void) {
    if(m_shapes.empty()) {
        return FG_FALSE;
    }
    int n = m_shapes.size();
    for(int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh) {
            if(!m_shapes[i]->mesh->hasVBO()) {
                m_shapes[i]->mesh->genBuffers();
            }
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------
