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

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::SAnimationChannel() {
    positionKeys.reserve(2);
    scalingKeys.reserve(2);
    rotationKeys.reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::SAnimationChannel(const SAnimationChannel& orig) {
    targetName.append(orig.targetName);
    positionKeys.append(orig.positionKeys);
    scalingKeys.append(orig.scalingKeys);
    rotationKeys.append(orig.rotationKeys);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel::~SAnimationChannel() {
    targetName.clear();
    positionKeys.clear();
    scalingKeys.clear();
    rotationKeys.clear();
}
//------------------------------------------------------------------------------

const Vector3f& gfx::anim::SAnimationChannel::getPosition(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = positionKeys.size();
    while(FG_TRUE) {
        if(index + 1 >= count)
            break;
        if(positionKeys[index + 1].elapsed > currentTime)
            break;
        index++;
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
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(positionKeys[index+1].elapsed > currentTime) {
            mixIndex = index+1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = positionKeys[index+1].elapsed - positionKeys[index].elapsed;
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

Vector3f gfx::anim::SAnimationChannel::getPositionInterpolated(float currentTime) {
    Vector3f result;
    getPositionInterpolated(result, currentTime);
    return result;
}
//------------------------------------------------------------------------------

const Vector3f& gfx::anim::SAnimationChannel::getScale(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = scalingKeys.size();
    while(FG_TRUE) {
        if(index + 1 >= count)
            break;
        if(scalingKeys[index + 1].elapsed > currentTime)
            break;
        index++;
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
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(scalingKeys[index+1].elapsed > currentTime) {
            mixIndex = index+1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = scalingKeys[index+1].elapsed - scalingKeys[index].elapsed;
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

Vector3f gfx::anim::SAnimationChannel::getScaleInterpolated(float currentTime) {
    Vector3f result;
    getScaleInterpolated(result, currentTime);
    return result;
}
//------------------------------------------------------------------------------

const Quaternionf& gfx::anim::SAnimationChannel::getRotation(float currentTime) {
    unsigned int index = 0;
    const unsigned int count = rotationKeys.size();
    while(FG_TRUE) {
        if(index + 1 >= count)
            break;
        if(rotationKeys[index + 1].elapsed > currentTime)
            break;
        index++;
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
        if(index + 1 >= count) {
            // this key is the last one - no interpolation
            mixIndex = index;
            break;
        }
        if(rotationKeys[index+1].elapsed > currentTime) {
            mixIndex = index+1;
            // the next key lies in the future, need to mix it with proper proportion
            const float keyDiff = rotationKeys[index+1].elapsed - rotationKeys[index].elapsed;
            const float currentDiff = currentTime - rotationKeys[index].elapsed;
            mixFactor = currentDiff / keyDiff;
            break;
        }
        index++;
    }
    if(mixIndex == index) {
        result = rotationKeys[index].value;
    } else {
        result = math::mix(rotationKeys[index].value,
                           rotationKeys[mixIndex].value,
                           mixFactor);
    }
}
//------------------------------------------------------------------------------

Quaternionf gfx::anim::SAnimationChannel::getRotationInterpolated(float currentTime) {
    Quaternionf result;
    getRotationInterpolated(result, currentTime);
    return result;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getMatrix(Matrix4f& result, float currentTime) {
    const Vector3f& position = getPosition(currentTime);
    const Quaternionf& rotation = getRotation(currentTime);
    const Vector3f& scale = getScale(currentTime);
    // translate - rotate - scale

    result = math::translate(Matrix4f(), position);
    //result = math::rotate(result, rotation);
    result *= math::toMat4(rotation);
    result = math::scale(result, scale);
}
//------------------------------------------------------------------------------

Matrix4f gfx::anim::SAnimationChannel::getMatrix(float currentTime) {
    Matrix4f result;
    getMatrix(result, currentTime);
    return result;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationChannel::getMatrixInterpolated(Matrix4f& result,
                                                         float currentTime) {
    Vector3f position, scale;
    Quaternionf rotation;
    getInterpolated(position, rotation, scale, currentTime);
    // translate - rotate - scale
    result = math::translate(Matrix4f(), position);
    result *= math::toMat4(rotation);
    result = math::scale(result, scale);
}
//------------------------------------------------------------------------------

Matrix4f gfx::anim::SAnimationChannel::getMatrixInterpolated(float currentTime) {
    Matrix4f result;
    getMatrixInterpolated(result, currentTime);
    return result;
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
}
//------------------------------------------------------------------------------