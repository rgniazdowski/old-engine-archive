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
 * File:   fgGFXSceneNodeObject.h
 * Author: vigilant
 *
 * Created on November 12, 2014, 6:08 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_OBJECT
    #define FG_INC_GFX_SCENE_NODE_OBJECT
    #define FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK

    #include "fgGfxSceneNode.h"    

namespace fg {
    namespace gfx {

        class CModelResource;
        struct SMeshBase;
        struct SShape;
        struct SSkinnedMesh;

        /**
         * 
         */
        class CSceneNodeObject : public CSceneNode {
        public:
            ///
            typedef CSceneNode base_type;
            ///
            typedef CSceneNodeObject self_type;
            ///
            typedef CSceneNodeObject type;

        public:
            /**
             * 
             */
            CSceneNodeObject(CModelResource *pModel = NULL, CSceneNode *pParent = NULL);
            /**
             * 
             * @param orig
             */
            CSceneNodeObject(const CSceneNodeObject& orig);
            /**
             * 
             */
            virtual ~CSceneNodeObject();

        public:
            /**
             * 
             * @param pModel
             */
            virtual void setModel(CModelResource *pModel);
            /**
             * 
             * @return 
             */
            CModelResource *getModel(void) const {
                return m_pModel;
            }

            using animated_type::setAnimation;
            /**
             * 
             * @param name
             * @param slot
             * @return
             */
            virtual fgBool setAnimation(const char* name, unsigned int slot);

        protected:
            /**
             * 
             */
            virtual void updateAABB(void);

            /**
             * 
             */
            virtual void refreshGfxInternals(void);

        public:
            /**
             *
             */
            virtual void removeAnimations(void);
            /**
             *
             */
            virtual void playAnimations(void);
            /**
             *
             */
            virtual void stopAnimations(void);
            /**
             *
             */
            virtual void pauseAnimations(fgBool toggle = FG_TRUE);
            /**
             *
             */
            virtual void resumeAnimations(void);
            /**
             *
             */
            virtual void rewindAnimations(void);

        private:
            /// Pointer to the external model on which this object is based
            CModelResource *m_pModel;
        }; // class CSceneNodeObject

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_OBJECT */
