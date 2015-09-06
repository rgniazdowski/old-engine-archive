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
 * File:   fgGfxSkinnedMesh.h
 * Author: vigilant
 *
 * Created on September 3, 2015, 9:16 PM
 */

#ifndef FG_INC_GFX_SKINNED_MESH
    #define FG_INC_GFX_SKINNED_MESH
    #define FG_INC_GFX_SKINNED_MESH_BLOCK

    #include "fgGfxMesh.h"
    #include "Animation/fgGfxBone.h"

namespace fg {
    namespace gfx {

        namespace anim {
            class CAnimation;
            struct SAnimationFrameInfo;
            struct SAnimationFrame;
        } // namespace anim

        /**
         *
         */
        struct SSkinnedMeshAoS : public SMeshAoS {
            typedef SSkinnedMeshAoS self_type;
            typedef SSkinnedMeshAoS type;
            typedef SMeshAoS base_type;

            typedef Vector4f blend_vec_element_type;

            typedef CVector<Vector4f> BlendVec;
            typedef BlendVec::iterator BlendVecItor;
            typedef BlendVec::const_iterator BlendVecConstItor;

            typedef CVector<anim::SBone*> BonesVec;
            typedef BonesVec::iterator BonesVecItor;
            typedef BonesVec::const_iterator BonesVecConstItor;

            static const unsigned short BLEND_WEIGHTS_VBO_ARRAY_IDX;
            static const unsigned short BLEND_INDICES_VBO_ARRAY_IDX;

            ///
            BonesVec bones;
            ///
            BlendVec blendWeights;
            ///
            BlendVec blendIndices;

            /**
             *
             */
            SSkinnedMeshAoS();
            /**
             *
             * @param vertexType
             */
            SSkinnedMeshAoS(VertexType vertexType);
            /**
             *
             * @param attribMask
             */
            SSkinnedMeshAoS(AttributeMask attribMask);
            /**
             * 
             */
            virtual ~SSkinnedMeshAoS();

            /**
             *
             */
            virtual void clear(void);

            /**
             *
             * @param pDataArray
             * @return
             */
            virtual fgGFXboolean refreshAttributes(SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            virtual fgGFXboolean setupAttributes(SAttributeData* pDataArray) const;

            /**
             *
             * @return
             */
            virtual fgGFXboolean genBuffers(void);
            /**
             *
             */
            void clearSkinningInfo(void);

            /**
             *
             */
            void refreshSkinningInfo(void);

            /**
             * Helper function for calculating current animation frame
             * @param pAnimation    Animation object to use (must be bone subtype)
             * @param frameInfo     Reference to special frame info structure
             * @param elapsed       Elapsed time (since app init) - not animation time
             */
            void calculate(anim::CAnimation* pAnimation,
                           anim::SAnimationFrameInfo& frameInfo,
                           float elapsed = 0.0f);

        }; // SSkinnedMeshAoS

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SKINNED_MESH_BLOCK
#endif	/* FG_INC_GFX_SKINNED_MESH */
