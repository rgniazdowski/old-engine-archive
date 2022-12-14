/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGfxAnimationChannel.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 3:49 PM
 */

#include "fgGfxAnimationChannel.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::SAnimationChannel() :
targetName(),
positionKeys(),
rotationKeys(),
scalingKeys(),
matrixKeys(),
dualQuatKeys(),
m_stateFlags(NO_FLAGS) {
    positionKeys.reserve(2);
    scalingKeys.reserve(2);
    rotationKeys.reserve(2);
    matrixKeys.reserve(2);
    dualQuatKeys.reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::SAnimationChannel(const SAnimationChannel& orig) {
    m_stateFlags = NO_FLAGS;
    this->setBakeDQs(orig.shouldBakeDQs());
    this->setBakeMatrices(orig.shouldBakeMatrices());
    targetName.append(orig.targetName);
    positionKeys.append(orig.positionKeys);
    scalingKeys.append(orig.scalingKeys);
    rotationKeys.append(orig.rotationKeys);
    matrixKeys.append(orig.matrixKeys);
    dualQuatKeys.append(orig.dualQuatKeys);
    setFlag(KEYS_FASTER_LOOKUP, orig.isFasterLookup());
    if(matrixKeys.size() || dualQuatKeys.size()) {
        setFlag(BAKED, FG_TRUE);
        setFlag(KEYS_FASTER_LOOKUP, FG_TRUE);
    }
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::~SAnimationChannel() {
    targetName.clear();
    positionKeys.clear();
    scalingKeys.clear();
    rotationKeys.clear();
    matrixKeys.clear();
    dualQuatKeys.clear();
    m_stateFlags = NO_FLAGS;
}
//------------------------------------------------------------------------------

const Vector3f& gfx::anim::SAnimationChannel::getPosition(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = positionKeys.size();
    if(!isFasterLookup()) {
        while(FG_TRUE) {
            if(index + 1 >= count)
                break;
            if(positionKeys[index + 1].elapsed > currentTime)
                break;
            index++;
        }
    } else {
        // if is baked then can just use currentTime for index
        index = (unsigned int)currentTime;
        if(index >= count)
            index = count - 1;
    }
    return positionKeys[index].value;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getPositionInterpolated(Vector3f& result,
                                                           float currentTime) {
    unsigned int index = 0;
    unsigned int mixIndex = 0;
    float mixFactor = 1.0f;
    const unsigned int count = positionKeys.size();
    while(FG_TRUE) {
        if(isFasterLookup()) {
            // if is baked - force index
            index = (unsigned int)currentTime;
        }
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(positionKeys[index + 1].elapsed > currentTime) {
            mixIndex = index + 1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = positionKeys[mixIndex].elapsed - positionKeys[index].elapsed;
            const float currentDiff = currentTime - positionKeys[index].elapsed;
            mixFactor = currentDiff / keyDiff;
            break;
        }
        index++;
    }
    if(mixIndex == index) {
        result = positionKeys[index].value;
    } else {
        result = math::mix(positionKeys[index].value,
                           positionKeys[mixIndex].value,
                           mixFactor);
    }
}
//------------------------------------------------------------------------------

const Vector3f& gfx::anim::SAnimationChannel::getScale(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = scalingKeys.size();
    if(!isFasterLookup()) {
        while(FG_TRUE) {
            if(index + 1 >= count)
                break;
            if(scalingKeys[index + 1].elapsed > currentTime)
                break;
            index++;
        }
    } else {
        index = (unsigned int)currentTime;
        if(index >= count)
            index = count - 1;
    }
    return scalingKeys[index].value;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getScaleInterpolated(Vector3f& result,
                                                        float currentTime) {
    unsigned int index = 0;
    unsigned int mixIndex = 0;
    float mixFactor = 1.0f;
    const unsigned int count = scalingKeys.size();
    while(FG_TRUE) {
        if(isFasterLookup()) {
            index = (unsigned int)currentTime;
        }
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(scalingKeys[index + 1].elapsed > currentTime) {
            mixIndex = index + 1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = scalingKeys[mixIndex].elapsed - scalingKeys[index].elapsed;
            const float currentDiff = currentTime - scalingKeys[index].elapsed;
            mixFactor = currentDiff / keyDiff;
            break;
        }
        index++;
    }
    if(mixIndex == index) {
        result = scalingKeys[index].value;
    } else {
        result = math::mix(scalingKeys[index].value,
                           scalingKeys[mixIndex].value,
                           mixFactor);
    }
}
//------------------------------------------------------------------------------

const Quaternionf& gfx::anim::SAnimationChannel::getRotation(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = rotationKeys.size();
    if(!isFasterLookup()) {
        while(FG_TRUE) {
            if(index + 1 >= count)
                break;
            if(rotationKeys[index + 1].elapsed > currentTime)
                break;
            index++;
        }
    } else {
        index = (unsigned int)currentTime;
        if(index >= count)
            index = count - 1;
    }
    return rotationKeys[index].value;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getRotationInterpolated(Quaternionf& result,
                                                           float currentTime) {
    unsigned int index = 0;
    unsigned int mixIndex = 0;
    float mixFactor = 1.0f;
    const unsigned int count = rotationKeys.size();
    while(FG_TRUE) {
        if(isFasterLookup()) {
            index = (unsigned int)currentTime;
        }
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(rotationKeys[index + 1].elapsed > currentTime) {
            mixIndex = index + 1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = rotationKeys[mixIndex].elapsed - rotationKeys[index].elapsed;
            const float currentDiff = currentTime - rotationKeys[index].elapsed;
            mixFactor = currentDiff / keyDiff;
            break;
        }
        index++;
    }
    if(mixIndex == index) {
        result = rotationKeys[index].value;
    } else {
        result = math::slerp(rotationKeys[index].value,
                             rotationKeys[mixIndex].value,
                             mixFactor);
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getMatrix(Matrix4f& result, float currentTime) {
    if(!isBaked() || matrixKeys.empty()) {
        const Vector3f& position = getPosition(currentTime);
        const Quaternionf& rotation = getRotation(currentTime);
        const Vector3f& scale = getScale(currentTime);
        // translate - rotate - scale

        result = math::translate(Matrix4f(), position);
        result *= math::toMat4(rotation);
        result = math::scale(result, scale);
    } else {
        const unsigned int count = matrixKeys.size();
        if((unsigned int)currentTime < count) {
            result = matrixKeys[(unsigned int)currentTime].value;
        }
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getMatrixInterpolated(Matrix4f& result,
                                                         float currentTime) {
    Vector3f position, scale;
    Quaternionf rotation;
    //getInterpolated(position, rotation, scale, currentTime);
    getPositionInterpolated(position, currentTime);
    getRotationInterpolated(rotation, currentTime);
    getScaleInterpolated(scale, currentTime);
    // translate - rotate - scale
    result = math::translate(Matrix4f(), position);
    result *= math::toMat4(rotation);
    result = math::scale(result, scale);    
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getDualQuaternion(DualQuaternionf& result,
                                                     float currentTime) {
    if(!isBaked() || dualQuatKeys.empty()) {
        result.initializeFrom(getRotation(currentTime), getPosition(currentTime));
    } else {
        const unsigned int count = dualQuatKeys.size();
        unsigned int index = (unsigned int)currentTime;
        if(index >= count)
            index = count - 1;
        result = dualQuatKeys[index].value;
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getDualQuaternionInterpolated(DualQuaternionf& result,
                                                                 float currentTime) {
    if(isBaked() && !dualQuatKeys.empty()) {
        float mixFactor = 1.0f;
        const unsigned int count = dualQuatKeys.size();
        unsigned int index = (unsigned int)currentTime, mixIndex = 0;
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
        } else /* if(dualQuatKeys[index + 1].elapsed > currentTime) */ {
            mixIndex = index + 1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = dualQuatKeys[mixIndex].elapsed - dualQuatKeys[index].elapsed;
            const float currentDiff = currentTime - dualQuatKeys[index].elapsed;
            mixFactor = currentDiff / keyDiff;
        }
        if(mixIndex == index) {
            result = dualQuatKeys[index].value;
        } else {
            result = DualQuaternionf(math::slerp(dualQuatKeys[index].value.q0,
                                                 dualQuatKeys[mixIndex].value.q0,
                                                 mixFactor),
                                     math::slerp(dualQuatKeys[index].value.qe,
                                                 dualQuatKeys[mixIndex].value.qe,
                                                 mixFactor));
        }
    } else {
        Quatf rot;
        Vec3f pos;
        getRotationInterpolated(rot, currentTime);
        getPositionInterpolated(pos, currentTime);
        result.initializeFrom(rot, pos);
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::get(Vector3f& outPosition,
                                       Quaternionf& outRotation,
                                       Vector3f& outScale,
                                       float currentTime) {
    outPosition = getPosition(currentTime);
    outRotation = getRotation(currentTime);
    outScale = getScale(currentTime);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getInterpolated(Vector3f& outPosition,
                                                   Quaternionf& outRotation,
                                                   Vector3f& outScale,
                                                   float currentTime) {
    getPositionInterpolated(outPosition, currentTime);
    getRotationInterpolated(outRotation, currentTime);
    getScaleInterpolated(outScale, currentTime);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::clearKeys(void) {
    positionKeys.clear();
    rotationKeys.clear();
    scalingKeys.clear();
    matrixKeys.clear();
    dualQuatKeys.clear();
    setFlag(BAKED, FG_FALSE);
    setFlag(KEYS_FASTER_LOOKUP, FG_FALSE);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::bake(fgBool force) {
    if(isBaked() && !force)
        return;
    if(positionKeys.size()) {
        unsigned int nKeys = positionKeys.size();
        float diff = positionKeys[nKeys - 1].elapsed - positionKeys[0].elapsed;
        // now the difference is in ticks
        // it should be the same as the number of position keys
        if((unsigned int)diff >= nKeys) {
            // search for holes and interpolate
            SVectorKeyf posKey;
            for(unsigned int i = 0; i < nKeys; i++) {
                if(i == nKeys - 1) {
                    break; // last key
                }
                float subKeyDiff = positionKeys[i + 1].elapsed - positionKeys[i].elapsed;
                const Vec3f aValue = positionKeys[i].value;
                const Vec3f bValue = positionKeys[i + 1].value;
                if(subKeyDiff > 1.0f) {
                    // the difference is more than 1.0f
                    unsigned int nDiff = (unsigned int)subKeyDiff;
                    PositionKeys::iterator itor = positionKeys.begin() + i;
                    for(unsigned int j = 0; j < nDiff - 1; j++) {
                        float mixFactor = ((float)j + 1.0f) / (subKeyDiff);
                        posKey.elapsed = positionKeys[i].elapsed + (float)j + 1.0f;
                        posKey.value = math::mix(aValue,
                                                 bValue,
                                                 mixFactor);
                        itor = positionKeys.begin() + i + j + 1;
                        positionKeys.insert(itor, posKey);
                        nKeys++;
                    }
                }
            }
        }
    }

    if(rotationKeys.size()) {
        unsigned int nKeys = rotationKeys.size();
        float diff = rotationKeys[nKeys - 1].elapsed - rotationKeys[0].elapsed;
        // now the difference is in ticks
        // it should be the same as the number of position keys
        if((unsigned int)diff >= nKeys) {
            // search for holes and interpolate
            SQuatKeyf rotKey;
            for(unsigned int i = 0; i < nKeys; i++) {
                if(i == nKeys - 1) {
                    break; // last key
                }
                float subKeyDiff = rotationKeys[i + 1].elapsed - rotationKeys[i].elapsed;
                const Quatf aValue = rotationKeys[i].value;
                const Quatf bValue = rotationKeys[i + 1].value;
                if(subKeyDiff > 1.0f) {
                    // the difference is more than 1.0f
                    unsigned int nDiff = (unsigned int)subKeyDiff;
                    RotationKeys::iterator itor = rotationKeys.begin() + i;
                    for(unsigned int j = 0; j < nDiff - 1; j++) {
                        float mixFactor = ((float)j + 1.0f) / (subKeyDiff);
                        rotKey.elapsed = rotationKeys[i].elapsed + (float)j + 1.0f;
                        rotKey.value = math::slerp(aValue,
                                                   bValue,
                                                   mixFactor);
                        itor = rotationKeys.begin() + i + j + 1;
                        rotationKeys.insert(itor, rotKey);
                        nKeys++;
                    }
                }
            }
        }
    }

    if(scalingKeys.size()) {
        unsigned int nKeys = scalingKeys.size();
        float diff = scalingKeys[nKeys - 1].elapsed - scalingKeys[0].elapsed;
        // now the difference is in ticks
        // it should be the same as the number of position keys
        if((unsigned int)diff >= nKeys) {
            // search for holes and interpolate
            SVectorKeyf scaleKey;
            for(unsigned int i = 0; i < nKeys; i++) {
                if(i == nKeys - 1) {
                    break; // last key
                }
                float subKeyDiff = scalingKeys[i + 1].elapsed - scalingKeys[i].elapsed;
                const Vec3f aValue = scalingKeys[i].value;
                const Vec3f bValue = scalingKeys[i + 1].value;
                if(subKeyDiff > 1.0f) {
                    // the difference is more than 1.0f
                    unsigned int nDiff = (unsigned int)subKeyDiff;
                    ScalingKeys::iterator itor = scalingKeys.begin() + i;
                    for(unsigned int j = 0; j < nDiff - 1; j++) {
                        float mixFactor = ((float)j + 1.0f) / (subKeyDiff);
                        scaleKey.elapsed = scalingKeys[i].elapsed + (float)j + 1.0f;
                        scaleKey.value = math::mix(aValue,
                                                   bValue,
                                                   mixFactor);
                        itor = scalingKeys.begin() + i + j + 1;
                        scalingKeys.insert(itor, scaleKey);
                        nKeys++;
                    }
                }
            }
        }
    }
    setFlag(KEYS_FASTER_LOOKUP, FG_TRUE);
    if(shouldBakeMatrices() || shouldBakeDQs()) {
        unsigned int nMaxKey = math::max(positionKeys.size(), scalingKeys.size());
        nMaxKey = math::max(nMaxKey, (unsigned int)rotationKeys.size());
        if(shouldBakeMatrices())
            matrixKeys.reserve(nMaxKey);
        if(shouldBakeDQs())
            dualQuatKeys.reserve(nMaxKey);
        matrixKeys.clear();
        dualQuatKeys.clear();
        Matrix4f outMat;
        DualQuaternionf outDQ;
        for(unsigned int i = 0; i < nMaxKey; i++) {
            // can use getMatrix here - isBaked is set to FALSE
            if(shouldBakeMatrices()) {
                getMatrix(outMat, (float)i);
                matrixKeys.push_back(SMatrixKeyf((float)i, outMat));
            }
            if(shouldBakeDQs()) {
                getDualQuaternion(outDQ, (float)i);
                dualQuatKeys.push_back(SDualQuatKeyf((float)i, outDQ));
            }
        }
        setFlag(BAKED, FG_TRUE);
    }
}
//------------------------------------------------------------------------------
