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

        struct SSkinnedMesh {
            typedef SSkinnedMesh self_type;
            typedef SSkinnedMesh type;

            typedef Vector4f blend_vec_element_type;

            typedef CVector<Vector4f> BlendVec;
            typedef BlendVec::iterator BlendVecItor;
            typedef BlendVec::const_iterator BlendVecConstItor;

            typedef CVector<anim::SBone*> BonesVec;
            typedef BonesVec::iterator BonesVecItor;
            typedef BonesVec::const_iterator BonesVecConstItor;

        protected:
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        public:
            ///
            BonesVec bones;
            ///
            BlendVec blendWeights;
            ///
            BlendVec blendIndices;

            /**
             *
             */
            SSkinnedMesh();

            /**
             * 
             */
            virtual ~SSkinnedMesh();

            /**
             *
             * @return
             */
            virtual SMeshSoA* getMeshSoA(void) = 0;
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void) = 0;
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void) = 0;

            /**
             *
             */
            void clearSkinningInfo(void);

            /**
             *
             */
            virtual void refreshSkinningInfo() = 0;

            /**
             * Helper function for calculating current animation frame
             * @param pAnimation    Animation object to use (must be bone subtype)
             * @param frameInfo     Reference to special frame info structure
             * @param elapsed       Elapsed time (since app init) - not animation time
             */
            void calculate(anim::CAnimation* pAnimation,
                           anim::SAnimationFrameInfo& frameInfo,
                           float elapsed = 0.0f);

        protected:
            /**
             *
             */
            void clear(SMeshBase* pMeshSuper);

            /**
             *
             */
            void refreshSkinningInfo(SMeshBase* pMeshSuper);
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean refreshAttributes(const SMeshBase* pMeshSuper, SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean setupAttributes(const SMeshBase* pMeshSuper, SAttributeData* pDataArray) const;

            /**
             *
             * @return
             */
            fgGFXboolean genBuffers(SMeshBase* pMeshSuper);

        }; // struct SSkinnedMesh

        /**
         *
         */
        struct SSkinnedMeshSoA : public SMeshSoA, public SSkinnedMesh {
        public:
            typedef SSkinnedMeshSoA self_type;
            typedef SSkinnedMeshSoA type;
            typedef SMeshSoA base_type;
            typedef SSkinnedMesh skinned_base_type;

            /**
             *
             */
            SSkinnedMeshSoA();
            /**
             *
             */
            virtual ~SSkinnedMeshSoA();
            /**
             *
             * @return
             */
            virtual fgBool isSkinnedMesh(void) const {
                return FG_TRUE;
            }
            
            /**
             *
             * @return
             */
            virtual SMeshSoA* getMeshSoA(void);
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void);
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void);

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
            virtual void refreshSkinningInfo(void);

        protected:
            /**
             *
             * @return
             */
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            /**
             * 
             * @return
             */
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        }; // SSkinnedMeshSoA

        /**
         *
         */
        struct SSkinnedMeshAoS : public SMeshAoS, public SSkinnedMesh {
        public:
            typedef SSkinnedMeshAoS self_type;
            typedef SSkinnedMeshAoS type;
            typedef SMeshAoS base_type;
            typedef SSkinnedMesh skinned_base_type;

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
             * @return
             */
            virtual fgBool isSkinnedMesh(void) const {
                return FG_TRUE;
            }

            /**
             *
             * @return
             */
            virtual SMeshSoA* getMeshSoA(void);
            /**
             *
             * @return
             */
            virtual SMeshAoS* getMeshAoS(void);
            /**
             *
             * @return
             */
            virtual SMeshBase* getMeshBase(void);

            /**
             *
             */
            virtual void clear(void);

            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean refreshAttributes(SAttributeData* pDataArray) const;
            /**
             *
             * @param pDataArray
             * @return
             */
            fgGFXboolean setupAttributes(SAttributeData* pDataArray) const;

            /**
             *
             * @return
             */
            fgGFXboolean genBuffers(void);

            /**
             *
             */
            virtual void refreshSkinningInfo(void);

        protected:
            virtual unsigned short internal_getBlendWeightsVboArrayIdx(void) const;
            virtual unsigned short internal_getBlendIndicesVboArrayIdx(void) const;

        }; // SSkinnedMeshAoS

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SKINNED_MESH_BLOCK
#endif	/* FG_INC_GFX_SKINNED_MESH */
