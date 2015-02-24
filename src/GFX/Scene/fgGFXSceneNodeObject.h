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

    #ifndef FG_INC_GFX_SCENE_NODE
        #include "fgGFXSceneNode.h"
    #endif
    #ifndef FG_INC_GFX_DRAW_CALL
        #include "GFX/fgGFXDrawCall.h"
    #endif
    #ifndef FG_INC_GFX_MODEL_RESOURCE
        #include "GFX/fgGFXModelResource.h"
    #endif

namespace fg {
    namespace gfx {

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
            CSceneNodeObject(gfx::CModel *pModel = NULL, CSceneNode *pParent = NULL);
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
            virtual void setModel(gfx::CModel *pModel);
            /**
             * 
             * @return 
             */
            gfx::CModel *getModel(void) const {
                return m_pModel;
            }
            /**
             * 
             */
            virtual void updateAABB(void);

            ///
            virtual void refreshGfxInternals(void);

        private:
            /// Pointer to the external model
            CModel *m_pModel;
            
        };
    };
};

    #undef FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_OBJECT */
