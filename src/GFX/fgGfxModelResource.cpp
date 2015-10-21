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
#include "fgGfxSkinnedMesh.h"

#include "Animation/fgGfxArmature.h"
#include "Animation/fgGfxBoneAnimation.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceErrorCodes.h"
#include "Util/fgStrings.h"
#include "Util/fgPath.h"
#include "fgTinyObj.h"

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

gfx::CModelResource::SModelSkinning::SModelSkinning() :
animations(),
pArmature(NULL) { }
//------------------------------------------------------------------------------

gfx::CModelResource::SModelSkinning::SModelSkinning(const SModelSkinning& orig) {
    if(orig.pArmature) {
        pArmature = new anim::CArmature(*orig.pArmature);
    }
    const unsigned int n = orig.animations.size();
    if(!n)
        return;
    animations.reserve(n);
    for(unsigned int i = 0; i < n; i++) {
        if(orig.animations[i]->getType() == anim::Type::BONE) {
            anim::CAnimation* pAnimation = new anim::CBoneAnimation(*(static_cast<anim::CBoneAnimation*>(orig.animations[i])));
            animations.push_back(pAnimation);
        }
    }
}
//------------------------------------------------------------------------------

gfx::CModelResource::SModelSkinning::~SModelSkinning() {
    destroy();
}
//------------------------------------------------------------------------------

void gfx::CModelResource::SModelSkinning::deleteAnimations(void) {
    const unsigned int n = animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(animations[i])
            delete animations[i];
        animations[i] = NULL;
    }
    animations.clear();
}
//------------------------------------------------------------------------------

void gfx::CModelResource::SModelSkinning::destroy(void) {
    deleteAnimations();
    if(pArmature)
        delete pArmature;
    pArmature = NULL;
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::SModelSkinning::getAnimation(const std::string& name,
                                                                         strings::MatchMode mode) {
    if(name.empty())
        return NULL;
    return getAnimation(name.c_str(), mode);
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::SModelSkinning::getAnimation(const char* name,
                                                                         strings::MatchMode mode) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    anim::CAnimation* pResult = NULL;
    const unsigned int n = this->animations.size();
    for(unsigned int i = 0; i < n; i++) {
        anim::CAnimation* pAnimation = this->animations[i];
        if(!pAnimation)
            continue;
        if(strings::doesMatch(pAnimation->getNameStr(), name, mode)) {
            //if(pAnimation->getName().compare(name) == 0) {
            pResult = pAnimation;
            break;
        }
    }
    return pResult;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::SModelSkinning::loadFromFile(const char* path) {
    if(!path)
        return FG_FALSE;
    fgBool status = FG_TRUE;

    enum ReadingState
    {
        NONE,
        READ_ANIMATION_MAPPING,
        READ_BONE_MAPPING,
        READ_ANIMATION_BLENDING,
        READ_BLEND_PAIR
    } state;
    state = NONE;
    util::CFile file;
    status = file.open(path, util::CFile::Mode::READ);
    char lineBuf[512];
    CStringVector splits1, splits2;
    std::string line;
    if(status) {
        memset(lineBuf, 0, 512);
        splits1.reserve(4);
        splits2.reserve(8);
        line.reserve(513);

        this->skinningInfo.actionsMap.clear();
    }
    anim::SBlendingInfo::AnimationPair currentPair;
    anim::StandardActionType action[2] = {anim::ACTION_NONE, anim::ACTION_NONE};
    currentPair.first = NULL;
    currentPair.second = NULL;
    int currentIndex = -1;
    while(status && file.readString(lineBuf, 512)) {
        line.clear();
        splits1.clear();
        splits2.clear();
        line.append(strings::trim(lineBuf, " \n\r\t"));
        if(line.empty() || strings::startsWith(lineBuf, ";") || strings::startsWith(lineBuf, "//") ||
           strings::startsWith(lineBuf, "#")) {
            memset(lineBuf, 0, 512);
            continue;
        }

        if(state == NONE) {
            if(strings::startsWith(line, "begin ", FG_FALSE)) {
                std::string catName = line.substr(6);
                if(strings::startsWith(catName.c_str(), "AnimationMapping", FG_FALSE)) {
                    state = READ_ANIMATION_MAPPING;
                } else if(strings::startsWith(catName.c_str(), "BoneMapping", FG_FALSE)) {
                    state = READ_BONE_MAPPING;
                } else if(strings::startsWith(catName.c_str(), "AnimationBlending", FG_FALSE)) {
                    state = READ_ANIMATION_BLENDING;
                }
            }
        } else if(state == READ_ANIMATION_MAPPING && strings::startsWith(line, "map ", FG_FALSE)) {
            strings::split(line, '{', splits1);
            if(splits1.empty())
                continue;
            std::string animationName = strings::trim(splits1[0], " \t\"\'\\").substr(4);
            anim::StandardActionType actionType = anim::getActionTypeFromText(animationName.c_str());
            strings::split(splits1[1], ',', splits2);
            unsigned int _n = splits2.size();
            if(!_n)
                continue;
            for(unsigned int _i = 0; _i < _n; _i++) {
                std::string realAnimName = strings::trim(splits2[_i], " \t\"\'\\{}[]");
                this->skinningInfo.actionsMap[actionType] = realAnimName;
            }
        } else if(state == READ_BONE_MAPPING && strings::startsWith(line, "map ", FG_FALSE) && pArmature) {
            strings::split(line, '{', splits1);
            if(splits1.empty())
                continue;
            std::string boneName = strings::trim(splits1[0], " \t\"\'\\").substr(4);
            anim::BoneType boneType = anim::getBoneTypeFromText(boneName.c_str());
            strings::split(splits1[1], ',', splits2);
            unsigned int _n = splits2.size();
            if(!_n)
                continue;
            for(unsigned int _i = 0; _i < _n; _i++) {
                std::string realBoneName = strings::trim(splits2[_i], " \t\"\'\\{}[]");
                anim::SBone* pBone = this->pArmature->get(realBoneName);
                pBone->boneType = boneType;
                if(pBone) {
                    if(!this->skinningInfo.boneTypesMap[boneType].contains(pBone))
                        this->skinningInfo.boneTypesMap[boneType].push_back(pBone);
                }
            }
        } else if(state == READ_ANIMATION_BLENDING) {
            if(strings::startsWith(line, "begin_blend", FG_FALSE)) {
                strings::split(line, ' ', splits1);
                if(splits1.size() < 2) {
                    currentIndex = -1;
                    continue;
                }
                strings::split(splits1[1], '+', splits2);
                if(splits2.size() < 2) {
                    currentIndex = -1;
                    continue;
                }
                action[0] = anim::getActionTypeFromText(splits2[0]);
                action[1] = anim::getActionTypeFromText(splits2[1]);

                anim::CAnimation * animation[2];
                animation[0] = this->getAnimation(this->skinningInfo.actionsMap[action[0]].c_str(),
                                                  strings::MATCH_SUBSTR);
                animation[1] = this->getAnimation(this->skinningInfo.actionsMap[action[1]].c_str(),
                                                  strings::MATCH_SUBSTR);
                if(animation[0] && animation[1]) {
                    currentPair.first = animation[0];
                    currentPair.second = animation[1];
                } else {
                    action[0] = anim::ACTION_NONE;
                    action[1] = anim::ACTION_NONE;
                    currentIndex = -1;
                    continue;
                }
                state = READ_BLEND_PAIR; // next stage
                this->skinningInfo.armatureInfo.push_back(anim::SBlendingPair());
                currentIndex = this->skinningInfo.armatureInfo.size() - 1;
                this->skinningInfo.armatureInfo[currentIndex].animation = currentPair;
                this->skinningInfo.armatureInfo[currentIndex].weights.resize(this->pArmature->count());
            }
        } else if(state == READ_BLEND_PAIR) {
            if(currentIndex < 0) {
                state = READ_ANIMATION_BLENDING;
                action[0] = anim::ACTION_NONE;
                action[1] = anim::ACTION_NONE;
                continue;
            }
            if(strings::startsWith(line, "end_blend", FG_FALSE)) {
                state = READ_ANIMATION_BLENDING;
                action[0] = anim::ACTION_NONE;
                action[1] = anim::ACTION_NONE;
                continue;
            }
            // run+attack
            // HEAD,NECK,ARM_LEFT,ARM_RIGHT={0.0,1.0}
            strings::split(line, '=', splits1);
            anim::SSkinningInfo::BoneTypesMap& boneTypesMap = this->skinningInfo.boneTypesMap;
            CVector<anim::BoneType> boneTypes;
            // get list of bone categories
            strings::split(splits1[0], ',', splits2);
            boneTypes.reserve(splits2.size());
            for(unsigned int i = 0; i < splits2.size(); i++) {
                std::string stdBoneName = strings::trim(splits2[i], " \t\n\r[]{}();,.");
                anim::BoneType boneType = anim::getBoneTypeFromText(stdBoneName.c_str());
                if(boneType != anim::BoneType::BONE_INVALID) {
                    boneTypes.push_back(boneType);
                } else if(strings::isEqual(stdBoneName, "ALL", FG_FALSE)) {
                    boneTypes.clear();
                    anim::SSkinningInfo::BoneTypesMapItor itor = boneTypesMap.begin(),
                            end = boneTypesMap.end();
                    for(; itor != end; itor++)
                        boneTypes.push_back(itor->first);
                }
            }
            splits2.clear();
            // get list of weights / should be 2
            strings::split(splits1[1], ',', splits2);
            if(splits2.size() < 2) {

            }
            float weights[2] = {0.0f, 0.0f};
            for(unsigned int i = 0; i < 2; i++) {
                std::string weightStr = strings::trim(splits2[i], " \t\n\r[]{}();,");
                weights[i] = (float)std::atof(weightStr.c_str());
            }
            anim::SBlendingInfo& pairsInfoVec = this->skinningInfo.armatureInfo;
            // process all bones for every type
            for(unsigned int typeIdx = 0; typeIdx < boneTypes.size(); typeIdx++) {
                anim::BoneType boneType = boneTypes[typeIdx];
                unsigned int nSubBones = boneTypesMap[boneType].size();
                if(nSubBones == 0) {
                    // ?
                    continue;
                }

                for(unsigned int i = 0; i < nSubBones; i++) {
                    anim::SBone* pBone = boneTypesMap[boneType][i];
                    if(!pBone)
                        continue;
                    int boneIndex = pBone->index;
                    pairsInfoVec[currentIndex].weights[boneIndex].first = weights[0];
                    pairsInfoVec[currentIndex].weights[boneIndex].second = weights[1];
                }
            }
        }

        if(strings::isEqual("end", line)) {
            state = NONE;
        }

        memset(lineBuf, 0, 512);
    }
    if(status)
        file.close();
    return status;
}
//------------------------------------------------------------------------------

void gfx::CModelResource::SModelSkinning::translatePositionKeys(const std::string& targetName,
                                                                const Vector3f& translation) {

    if(targetName.empty())
        return;
    unsigned int nAnims = this->animations.size();
    for(unsigned int i = 0; i < nAnims; i++) {
        anim::CAnimation* pAnim = this->animations[i];
        if(!pAnim)
            continue;
        const unsigned int nChannels = pAnim->getChannels().size();
        for(unsigned int idChannel = 0; idChannel < nChannels; idChannel++) {
            anim::SAnimationChannel& refChannel = pAnim->getChannels()[idChannel];
            if(refChannel.targetName.compare(targetName) == 0) {
                // get Armature channel - ignore the rest
                // now pre-translate properly all translation keys
                const unsigned int nKeys = refChannel.positionKeys.size();
                for(unsigned int idxKey = 0; idxKey < nKeys; idxKey++) {
                    refChannel.positionKeys[idxKey].value += translation;
                    // so now the model should display properly
                }
                break; 
            }            
        } // for every channel
    } // for every animation
}
//------------------------------------------------------------------------------

gfx::CModelResource::CModelResource() :
base_type(),
m_skinning(),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    // Set default flags
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    setFlag(HIGH_QUALITY, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_FALSE);
    setFlag(PRE_TRANSLATION, FG_FALSE);

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
m_skinning(),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    // Set default flags
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    setFlag(HIGH_QUALITY, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_FALSE);
    setFlag(PRE_TRANSLATION, FG_FALSE);
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
m_skinning(),
m_materialOverride(NULL),
m_modelType(MODEL_INVALID),
m_modelFlags(NO_FLAGS) {
    m_modelFlags = NO_FLAGS;
    // Set default flags
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    setFlag(HIGH_QUALITY, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_FALSE);
    setFlag(PRE_TRANSLATION, FG_FALSE);
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
    // Set default flags
    setFlag(INTERLEAVED, FG_TRUE);
    setFlag(FIX_CENTER, FG_TRUE);
    setFlag(HIGH_QUALITY, FG_TRUE);
    setFlag(SAVE_DISPLACEMENT, FG_FALSE);
    setFlag(PRE_TRANSLATION, FG_FALSE);
    memset(m_numData, 0, sizeof (m_numData));
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::setModelTypeFromFilePath(std::string&path) {
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

            if(shape->mesh->isSkinnedMesh()) {
                SSkinnedMesh* pSkinned = shape->getSkinnedMesh();
                pSkinned->skinningInfo.boneTypesMap = m_skinning.skinningInfo.boneTypesMap;
                pSkinned->skinningInfo.armatureInfo = m_skinning.skinningInfo.armatureInfo;
                pSkinned->skinningInfo.actionsMap = m_skinning.skinningInfo.actionsMap;
            }
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
    if(m_skinning.pArmature) {
        m_skinning.pArmature->refreshInternals();
    }
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

gfx::SShape* gfx::CModelResource::getShape(const std::string& name) {
    if(name.empty())
        return NULL;
    return getShape(name.c_str());
}
//------------------------------------------------------------------------------

gfx::SShape* gfx::CModelResource::getShape(const char* name) {
    if(!name)
        return NULL;
    SShape* pShape = NULL;
    const unsigned int n = m_shapes.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_shapes[i]->name.compare(name) == 0) {
            pShape = m_shapes[i];
            break;
        }
    }
    return pShape;
}
//------------------------------------------------------------------------------

gfx::SShape* gfx::CModelResource::getShape(SMeshBase* pMesh) {
    if(!pMesh)
        return NULL;
    SShape* pShape = NULL;
    const unsigned int n = m_shapes.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_shapes[i]->mesh == pMesh) {
            pShape = m_shapes[i];
            break;
        }
    }
    return pShape;
}
//------------------------------------------------------------------------------

gfx::SMeshBase* gfx::CModelResource::getMesh(const std::string& name) {
    if(name.empty())
        return NULL;
    return getMesh(name.c_str());
}
//------------------------------------------------------------------------------

gfx::SMeshBase* gfx::CModelResource::getMesh(const char* name) {
    if(!name)
        return NULL;
    SMeshBase* pMesh = NULL;
    const unsigned int n = m_shapes.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_shapes[i]->name.compare(name) == 0) {
            pMesh = m_shapes[i]->mesh;
            break;
        }
    }
    return pMesh;
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
    defaultFlags |= aiProcess_JoinIdenticalVertices;
    // defaultFlags |= aiProcess_MakeLeftHanded; // only for DirectX
    defaultFlags |= aiProcess_Triangulate;
    defaultFlags |= aiProcess_GenUVCoords;
    defaultFlags |= aiProcess_RemoveComponent;
    defaultFlags |= aiProcess_RemoveRedundantMaterials;
    defaultFlags |= aiProcess_SortByPType;
    defaultFlags |= aiProcess_TransformUVCoords;
    defaultFlags |= aiProcess_FlipUVs;
    if(isHighQuality()) {
        defaultFlags |= aiProcess_CalcTangentSpace;
    }

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

    anim::CArmature* pArmature = NULL;
    aiNode* pNodeArmature = NULL;
    if(!isDropBones()) {
        // should load armature?
        // creating armature and bones from aiNode structure
        // It is required that for given model there is only one Armature structure
        // and there is a node named exactly 'Armature';
        pNodeArmature = pScene->mRootNode->FindNode("Armature");
    }
    if(pNodeArmature) {
        stack.push(pNodeArmature);
        pArmature = new anim::CArmature();
        m_skinning.pArmature = pArmature;
        // first child here
        anim::SBone* pBone = new anim::SBone();
        pBone->name.append("ArmatureRoot");
        assimp_helper::copyMatrix4x4(pBone->bindPoseMatrix, pScene->mRootNode->mTransformation);
        pArmature->add(pBone);
        //delete pBone;
    }
    // traverse the 'Armature' node
    while(!stack.empty()) {
        aiNode* pNode = stack.top();
        stack.pop();
        const fgBool isRoot = (fgBool)(pNode->mParent == NULL); // should be false
        // push children in reverse order
        if(pNode->mNumChildren) {
            for(int i = pNode->mNumChildren - 1; i >= 0; i--) {
                if(i >= 0)
                    stack.push(pNode->mChildren[i]);
            }
        }
        // skip node if it has meshes
        // bone nodes should not have mesh info
        if(isRoot || pNode->mNumMeshes > 0) {
            continue;
        }
        // first child here
        anim::SBone* pBone = new anim::SBone();
        pBone->name.append(pNode->mName.C_Str());
        if(pNode == pNodeArmature) {
            pBone->pParent = pArmature->get("ArmatureRoot");
        } else if(pNode->mParent) {
            // this node has parent
            pBone->pParent = pArmature->get(pNode->mParent->mName.C_Str());
            // parent index will be set upon addition
        }

        const char* pFatherName = NULL;
        if(pBone->pParent)
            pFatherName = pBone->pParent->name.c_str();

        printf("Adding bone '%s' | it has a father: '%s'\n", pBone->name.c_str(), pFatherName);
        assimp_helper::copyMatrix4x4(pBone->bindPoseMatrix, pNode->mTransformation);
        // add bone to the armature, parent idx/ptr and children vectors
        // will be updated automatically
        pArmature->add(pBone);
    }
    if(!isDropAnimations()) {
        // should load animations?
        unsigned int n = pScene->mNumAnimations;
        for(unsigned int i = 0; i < n; i++) {
            aiAnimation* pAiAnimation = pScene->mAnimations[i];
            // need to check whether or not this animation targets only bone nodes
            unsigned int nChannels = pAiAnimation->mNumChannels;
            for(unsigned int channelIdx = 0; channelIdx < nChannels && pArmature; channelIdx++) {
                const char* targetName = pAiAnimation->mChannels[channelIdx]->mNodeName.C_Str();
                if(!targetName) {
                    nChannels = 0;
                    break;
                }
                if(!pArmature->get(targetName)) {
                    // such bone does not exist
                    nChannels = 0;
                    break;
                }
            }
            if(!nChannels) // skip
                continue;
            anim::CAnimation* pAnimation = new anim::CBoneAnimation(pArmature);
            assimp_helper::copyAnimation(pAnimation, pAiAnimation);
            m_skinning.animations.push_back(pAnimation);
        }
    }

    // Traverse the structure from node, search for meshes and additional bone info
    stack.push(pScene->mRootNode);
    while(!stack.empty()) {
        aiQuaternion matRot;
        aiVector3D matPos, matScale;

        aiNode* pNode = stack.top();
        stack.pop();
        const fgBool isRoot = (fgBool)(pNode->mParent == NULL);
        for(unsigned int i = 0; i < pNode->mNumChildren; i++) {
            stack.push(pNode->mChildren[i]);
        }
        if(isRoot) {
            pNode->mTransformation.Decompose(matScale, matRot, matPos);
            printf("%p: %s [Root] [t:%.2f;%.2f;%.2f] [rot:%.2f;%.2f;%.2f;%.2f] [scale:%.2f;%.2f;%.2f]\n",
                   pNode, pNode->mName.C_Str(),
                   matPos.x, matPos.y, matPos.z,
                   matRot.w, matRot.x, matRot.y, matRot.z,
                   matScale.x, matScale.y, matScale.z);
            continue;
        }
        unsigned int n = 0;
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
        if(!pNode->mNumMeshes) {
            pNode->mTransformation.Decompose(matScale, matRot, matPos);
            printf("%s%p: %s [Bone] [t:%.2f;%.2f;%.2f] [rot:%.2f;%.2f;%.2f;%.2f] [scale:%.2f;%.2f;%.2f]\n",
                   spacing.c_str(), pNode, pNode->mName.C_Str(),
                   matPos.x, matPos.y, matPos.z,
                   matRot.w, matRot.x, matRot.y, matRot.z,
                   matScale.x, matScale.y, matScale.z);
            continue;
        }
        aiTransform = aiMatrix4x4();
        n = nodeTransVec.size();
        for(unsigned int i = 0; i < n; i++) {
            aiTransform *= nodeTransVec[i]->mTransformation;
        }
        nodeTransVec.clear();
        aiTransform.Decompose(matScale, matRot, matPos);

        // This may not be working properly for now. #FIXME        
        if(!isPreTranslation()) {
            // Zero the transformation: the mesh will now appear at center (local)
            // mesh still will be moved by armature offset if animated/rigged
            Vec4f offsetArmature;
            if(pArmature) {
                offsetArmature = pArmature->get("Armature")->bindPoseMatrix[3];
                pArmature->get("Armature")->bindPoseMatrix[3] = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
            }
            // ? basically it means that even with translation
            // one should not change the offset
            // just change the translation keys of all animations
            // this makes sense ?
            m_skinning.translatePositionKeys(std::string("Armature"), -Vec3f(offsetArmature));
            aiTransform.a4 = 0.0f;
            aiTransform.b4 = 0.0f;
            aiTransform.c4 = 0.0f;
        } else {
            aiTransform.a4 += m_preTranslation.x;
            aiTransform.b4 += m_preTranslation.y;
            aiTransform.c4 += m_preTranslation.z;
        }
        Matrix4f transformInv;
        assimp_helper::copyMatrix4x4(transformInv, aiMatrix4x4(aiTransform).Inverse());
        const aiMatrix3x3 aiTransformIT = aiMatrix3x3(aiTransform).Inverse().Transpose();
        Matrix3f transformIT;
        assimp_helper::copyMatrix3x3(transformIT, aiTransformIT);
        printf("%s%p: %s [t:%.2f;%.2f;%.2f] [rot:%.2f;%.2f;%.2f;%.2f] [scale:%.2f;%.2f;%.2f]\n",
               spacing.c_str(), pNode, pNode->mName.C_Str(),
               matPos.x, matPos.y, matPos.z,
               matRot.w, matRot.x, matRot.y, matRot.z,
               matScale.x, matScale.y, matScale.z);
        for(unsigned int i = 0; i < pNode->mNumMeshes; i++) {
            aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
            if(!pMesh) {
                continue;
            }
            SShape* pShape = new SShape();
            SSkinnedMesh* pSkinnedMesh = NULL;
            pShape->name.reserve(pNode->mName.length);
            pShape->name.append(pNode->mName.C_Str());
            m_shapes.push_back(pShape);

            VertexType vertexType = VERTEX_3;
            if(pMesh->HasTangentsAndBitangents() && isHighQuality()) {
                vertexType = VERTEX_5_HQ;
            }
            if(isInterleaved()) {
                if(shouldDropBones()) {
                    pShape->mesh = new SMeshAoS(vertexType); // mesh - array of structures
                } else {
                    pSkinnedMesh = new SSkinnedMeshAoS(vertexType);
                    pShape->mesh = pSkinnedMesh->getMeshBase();
                }
            } else {
                if(shouldDropBones()) {
                    pShape->mesh = new SMeshSoA(); // mesh - structure of arrays
                } else {
                    pSkinnedMesh = new SSkinnedMeshSoA(); // ? lame-o!
                    pShape->mesh = pSkinnedMesh->getMeshBase();
                }
            }
            if(pSkinnedMesh) {
                pSkinnedMesh->meshIndex = m_shapes.size() - 1;
            }

            if(!shouldDropBones()) {
                // update bone structure with offsets and weights
                n = pMesh->mNumBones;
                pSkinnedMesh->bones.reserve(n);
                for(unsigned int boneIdx = 0; boneIdx < n; boneIdx++) {
                    aiBone* pAiBone = pMesh->mBones[boneIdx];
                    anim::SBone* pOriginalBone = pArmature->get(pAiBone->mName.C_Str());
                    if(!pOriginalBone) {
                        // could not find the bone? this should not happen
                        continue;
                    }
                    assimp_helper::copyBone(pOriginalBone, pAiBone, pSkinnedMesh->meshIndex);
                    pSkinnedMesh->bones.push_back(pOriginalBone);
                }
            }

            for(unsigned int fn = 0; fn < pMesh->mNumFaces; fn++) {
                struct aiFace* pFace = &pMesh->mFaces[fn];
                for(unsigned int fidx = 0; fidx < pFace->mNumIndices; fidx++) {
                    pShape->mesh->appendIndice(pFace->mIndices[fidx]);
                }
            }
            // In most cases using only save displacement may cause artifacts
            // as the objects will be moved twice: once by the model matrix
            // transformation, the second time because of the transformation
            // of vertices. - should use with PreTranslation(false)
            if(isSaveDisplacement()) {
                // Save the displacement info (off-center transformation)
                assimp_helper::copyVector(pShape->mesh->displacement, matPos);
            }
            for(unsigned int vidx = 0; vidx < pMesh->mNumVertices; vidx++) {
                Vector3f pos, normal, tangent, bitangent;
                Vector2f uv;
                assimp_helper::copyVector(normal, pMesh->mNormals[vidx]);
                if(pMesh->HasTextureCoords(0)) {
                    assimp_helper::copyVector(uv, pMesh->mTextureCoords[0][vidx]);
                }
                // aiVector3D is a little problematic (make some transform functions?)
                aiVector3D transPos = pMesh->mVertices[vidx];
                transPos *= aiTransform;

                assimp_helper::copyVector(pos, transPos);
                if(pMesh->HasTangentsAndBitangents()) {
                    assimp_helper::copyVector(tangent, pMesh->mTangents[vidx]);
                    tangent = transformIT * tangent;
                    assimp_helper::copyVector(bitangent, pMesh->mBitangents[vidx]);
                    bitangent = transformIT * bitangent;
                }
                normal = transformIT * normal;
                pShape->mesh->append(pos, normal, uv, tangent, bitangent);
            }
            struct aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
            SMaterial* pNewMaterial = new SMaterial();
            // copy aiMaterial data to gfx::SMaterial
            assimp_helper::setupMaterial(pNewMaterial, pMaterial);
            pShape->material = pNewMaterial;
        } // for (mNumMeshes)
        if(pNode->mNumMeshes && pArmature) {
            for(unsigned int i = 0; i < pArmature->count(); i++) {
                anim::SBone *pBone = pArmature->getBones()[i];
                pBone->offset *= transformInv;
            }
        }
    } // while (stack not empty)    
    s_objImporter->FreeScene();
    // load additional skinning info file
    std::string& currentPath = this->getCurrentFilePath();
    std::string skinning_file;
    skinning_file = currentPath.substr(0, currentPath.size() - strlen(ext) - 1);
    skinning_file.append(".skin");
    if(!this->m_skinning.loadFromFile(skinning_file)) {
        FG_LOG_ERROR("GFX: Model: Failed to load additional skinning info file '%s' for model '%s'.",
                     skinning_file.c_str(), getNameStr());
    }
    // reset the ready flag
    this->m_isReady = FG_FALSE;
    refreshInternalData(); // recalculate internals
    setFlag(RIGGED, (fgBool)(pArmature != NULL));
    setFlag(ANIMATED, (fgBool)(m_skinning.animations.size() > 0));
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
    this->refreshSkinningInfo();
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
        // only dispose on recreate when modelType is not BuiltIn
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

void gfx::CModelResource::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 2)
        return;
    // This is important - always call setFlags for the base class
    base_type::setFlags(flags);
    fg::CStringVector flagsVec;
    strings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(flagsVec[i].c_str(), "interleaved", FG_FALSE) ||
           strings::isEqual(flagsVec[i].c_str(), "aos", FG_FALSE) ||
           strings::isEqual(flagsVec[i].c_str(), "meshaos", FG_FALSE)) {
            setInterleaved(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "notinterleaved", FG_FALSE) ||
                  strings::isEqual(flagsVec[i].c_str(), "soa", FG_FALSE) ||
                  strings::isEqual(flagsVec[i].c_str(), "meshsoa", FG_FALSE)) {
            setInterleaved(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "dropanimations", FG_FALSE)) {
            setDropAnimations(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "dropbones", FG_FALSE)) {
            setDropBones(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "mergemeshes", FG_FALSE)) {
            setMergeMeshes(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "nomergemeshes", FG_FALSE)) {
            setMergeMeshes(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "fixcenter", FG_FALSE)) {
            setFixCenter(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "nofixcenter", FG_FALSE)) {
            setFixCenter(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "savedisplacement", FG_FALSE)) {
            setSaveDisplacement(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "nosavedisplacement", FG_FALSE)) {
            setSaveDisplacement(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "pretranslation", FG_FALSE)) {
            setPreTranslation(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "nopretranslation", FG_FALSE)) {
            setPreTranslation(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "highquality", FG_FALSE) ||
                  strings::isEqual(flagsVec[i].c_str(), "generatetangents", FG_FALSE)) {
            setHighQuality(FG_TRUE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "nohighquality", FG_FALSE) ||
                  strings::isEqual(flagsVec[i].c_str(), "lowquality", FG_FALSE)) {
            setHighQuality(FG_FALSE);
        } else if(strings::isEqual(flagsVec[i].c_str(), "defaults", FG_FALSE)) {
            // Set default flags
            setFlag(INTERLEAVED, FG_TRUE);
            setFlag(FIX_CENTER, FG_TRUE);
            setFlag(HIGH_QUALITY, FG_TRUE);
            setFlag(SAVE_DISPLACEMENT, FG_FALSE);
            setFlag(PRE_TRANSLATION, FG_FALSE);
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CModelResource::updateAABB(void) {
    if(m_shapes.empty()) {
        return;
    }
    int n = m_shapes.size();
    m_aabb.invalidate();
    for(int i = 0; i < n; i++) {
        SMeshBase* pMesh = m_shapes[i]->mesh;
        if(pMesh) {
            pMesh->updateAABB();
            m_aabb.merge(pMesh->aabb);
        }
    }
    if(isFixCenter()) {
        const Vector3f offCenter = m_aabb.getCenter();
        //printf("%s: offCenter: %.2f %.2f %.2f\n",
        //       this->getNameStr(), offCenter.x, offCenter.y, offCenter.z);
        const Matrix4f offMatInv = math::inverse(math::translate(Matrix4f(), -offCenter));
        if(m_skinning.pArmature) {
            const unsigned int nBones = m_skinning.pArmature->getBones().size();
            for(unsigned int i = 0; i < nBones; i++) {
                anim::SBone* pBone = m_skinning.pArmature->getBones()[i];
                if(!pBone)
                    continue;
                pBone->offset *= offMatInv;
            }
        }
        m_aabb.min -= offCenter;
        m_aabb.max -= offCenter;
        for(int i = 0; i < n; i++) {
            SMeshBase* pMesh = m_shapes[i]->mesh;
            if(pMesh) {
                pMesh->translate(-offCenter);
                pMesh->aabb.min -= offCenter;
                pMesh->aabb.max -= offCenter;
            }
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

fgBool gfx::CModelResource::addAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return FG_FALSE;
    int index = m_skinning.animations.find(pAnimation);
    if(index >= 0)
        return FG_FALSE; // already exists
    if(pAnimation->getName().empty())
        return FG_FALSE; // name is required
    m_skinning.animations.push_back(pAnimation);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::hasAnimation(anim::CAnimation* pAnimation) const {
    if(!pAnimation)
        return FG_FALSE;
    int index = m_skinning.animations.find(pAnimation);
    return (fgBool)(index >= 0);
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::hasAnimation(const std::string& name) const {
    if(name.empty())
        return FG_FALSE;
    return hasAnimation(name.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::CModelResource::hasAnimation(const char* name) const {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool status = FG_FALSE;
    const unsigned int n = m_skinning.animations.size();
    for(unsigned int i = 0; i < n; i++) {
        anim::CAnimation* pAnimation = m_skinning.animations[i];
        if(!pAnimation)
            continue; // ?
        if(pAnimation->getName().compare(name) == 0) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::getAnimation(const std::string& name) {
    if(name.empty())
        return NULL;
    return m_skinning.getAnimation(name.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::getAnimation(const char* name) {
    return m_skinning.getAnimation(name);
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::getMatchingAnimation(const std::string& name) {
    if(name.empty())
        return NULL;
    return m_skinning.getAnimation(name.c_str(), strings::MATCH_CASE_INSENSITIVE | strings::MATCH_SUBSTR);
 }
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::CModelResource::getMatchingAnimation(const char* name) {
    return m_skinning.getAnimation(name, strings::MATCH_CASE_INSENSITIVE | strings::MATCH_SUBSTR);
 }
//------------------------------------------------------------------------------

void gfx::CModelResource::refreshSkinningInfo(void) {
    const unsigned int n = m_shapes.size();
    for(unsigned int i = 0; i < n; i++) {
        if(!m_shapes[i]->isSkinned())
            continue;
        m_shapes[i]->getSkinnedMesh()->refreshSkinningInfo();
    }
}
//------------------------------------------------------------------------------
