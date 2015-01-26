/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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
        class CSceneNodeObject : public fg::gfx::CSceneNode {
        public:
            typedef fg::gfx::CSceneNode base_type;

        private:
            fg::gfx::CModel *m_pModel;

        public:
            /**
             * 
             */
            CSceneNodeObject(fg::gfx::CModel *pModel = NULL, fg::gfx::CSceneNode *pParent = NULL);
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
            virtual void setModel(fg::gfx::CModel *pModel);
            /**
             * 
             * @return 
             */
            fg::gfx::CModel *getModel(void) const {
                return m_pModel;
            }
            /**
             * 
             */
            virtual inline void updateAABB(void) {
                // #FUBAR
                if(m_pModel) {
                    m_aabb.min = m_pModel->getRefAABB().min;
                    m_aabb.max = m_pModel->getRefAABB().max;
                    m_aabb.transform(m_modelMat);
                }
            }
            /**
             * 
             * @param modelMat
             */
            virtual inline void updateAABB(const Matrix4f& modelMat) {
                if(m_pModel) {
                    m_aabb.min = m_pModel->getRefAABB().min;
                    m_aabb.max = m_pModel->getRefAABB().max;
                    m_aabb.transform(modelMat);
                }
            }
        };
    };
};

    #undef FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_OBJECT */
