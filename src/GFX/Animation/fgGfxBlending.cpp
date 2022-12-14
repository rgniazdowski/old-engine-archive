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
 * File:   fgGfxBlending.cpp
 * Author: vigilant
 * 
 * Created on September 16, 2015, 6:02 PM
 */

#include "fgGfxBlending.h"
#include "fgGfxBlendingInfo.h"

using namespace fg;
//------------------------------------------------------------------------------

int gfx::anim::blendAnimations(const CVector<anim::SAnimationInfo>& anims,
                               Type animType,
                               const SBlendingInfo& blendInfo,
                               SAnimationFrameInfo* pResult) {
    if(!pResult)
        return -1;
    if(anims.empty())
        return -1;
    int blendCount = 0;
    const unsigned int nAnims = anims.size();
    if(anims.size() == 1) {
        //*pResult = anims[0];
        return blendCount;
    }
    const unsigned int nPairs = blendInfo.size();
    if((animType == Type::BONE || animType == Type::NODE) && !blendInfo.empty()) {
        // if(blendInfo.empty()) {
        //     pResult->clear();
        //     // no info on how to blend
        //     return blendCount;
        // }
        // Blending bone animations requires blending info - always
        // Check if blending pairs (compatible animations) are inside of the animation list.
        for(unsigned int pairIdx = 0; pairIdx < nPairs; pairIdx++) {
            SBlendingPair const& pairInfo = blendInfo[pairIdx];
            SBlendingInfo::AnimationPair const& pair = pairInfo.animation;
            if(pairInfo.weights.empty())
                continue; // ignore empty pair info
            const anim::SAnimationInfo * foundAnims[2] = {NULL, NULL};
            int nFound = 0;
            // now check if these animations are inside
            for(unsigned int animIdx = 0; animIdx < nAnims; animIdx++) {
                const anim::SAnimationInfo& animInfo = anims[animIdx];
                if(animInfo.pAnimation == pair.first) {
                    nFound++;
                    foundAnims[0] = &anims[animIdx];
                } else if(animInfo.pAnimation == pair.second) {
                    foundAnims[1] = &anims[animIdx];
                    nFound++;
                }
                if(nFound == 2)
                    break;
            } // for each anim info
            if(nFound < 2)
                continue;
            // could also found two the same animations
            // could happen...
            if(foundAnims[0] == NULL || foundAnims[1] == NULL) {
                if(foundAnims[0])
                    *pResult = foundAnims[0]->curFrame;
                else if(foundAnims[1])
                    *pResult = foundAnims[1]->curFrame;
                // #FIXME
                // no merge / just copy
                break;
            }
            // found corresponding animations
            // now can merge properly
            SBlendingInfo::WeightsVec const& weights = pairInfo.weights;
            SAnimationFrameInfo::DualQuatsVec& result = pResult->dualQuaternions;
            SAnimationFrameInfo::DualQuatsVec const& first = foundAnims[0]->curFrame.dualQuaternions;
            SAnimationFrameInfo::DualQuatsVec const& second = foundAnims[1]->curFrame.dualQuaternions;
            const unsigned int nCount[2] = {(unsigned int)first.size(),
                                            (unsigned int)second.size()};
            const unsigned int maxCount = math::max(nCount[0], nCount[1]);
            result.resize(maxCount);
            for(unsigned int dqIdx = 0; dqIdx < maxCount; dqIdx++) {
                if(dqIdx >= nCount[0] || dqIdx >= nCount[1])
                    break;
                result[dqIdx].q0 = first[dqIdx].q0 * weights[dqIdx].first +
                        second[dqIdx].q0 * weights[dqIdx].second;

                result[dqIdx].qe = first[dqIdx].qe * weights[dqIdx].first +
                        second[dqIdx].qe * weights[dqIdx].second;
            }
            blendCount++;
            // this is not final version of bone animation merging
            // need to find a way to merge 3 animations
            // merging walk + jump + attack =
            // walk + attack -> walk + jump
            // need to remember types of the merged animations
            break;
        } // for each pair
        //if(!blendCount) {
          //  *pResult = anims[0].curFrame; // Fallback
            //return blendCount;
        //}
    }// if anim type bone
    else if(animType == Type::NODE) {
        // this should not require blending info
        const anim::SAnimationInfo * foundAnims[2] = {NULL, NULL};
        unsigned int nFound = 0;
        for(unsigned int animIdx = 0; animIdx < nAnims; animIdx++) {
            const anim::SAnimationInfo& animInfo = anims[animIdx];
            fgBool foundNow = FG_FALSE;
            if(animInfo.pAnimation && animInfo.pAnimation->getType() == animType) {
                if(nFound < 2) {
                    foundAnims[nFound] = &anims[animIdx];
                } else {
                    foundAnims[0] = &anims[animIdx];
                }
                nFound++;
                foundNow = FG_TRUE;
            }
            if(!foundNow || nFound < 2)
                continue;

            SAnimationFrameInfo::DualQuatsVec& result = pResult->dualQuaternions;
            SAnimationFrameInfo::DualQuatsVec const* first = NULL, *second = NULL;
            if(nFound == 2) {
                first = &foundAnims[0]->curFrame.dualQuaternions;
                second = &foundAnims[1]->curFrame.dualQuaternions;
            } else {
                first = &pResult->dualQuaternions;
                second = &foundAnims[0]->curFrame.dualQuaternions;
            }
            const unsigned int nCount[2] = {(unsigned int)first->size(),
                                            (unsigned int)second->size()};
            const unsigned int maxCount = math::max(nCount[0], nCount[1]);
            result.resize(maxCount);
            for(unsigned int dqIdx = 0; dqIdx < maxCount; dqIdx++) {
                if(dqIdx >= nCount[0] || dqIdx >= nCount[1])
                    break;
                result[dqIdx].q0 = (*first)[dqIdx].q0 * 0.5f +
                        (*second)[dqIdx].q0 * 0.5f;

                result[dqIdx].qe = (*first)[dqIdx].qe * 0.5f +
                        (*second)[dqIdx].qe * 0.5f;

            } // for each anim info
            blendCount++;
        }
    }
    return blendCount;
}
//------------------------------------------------------------------------------
