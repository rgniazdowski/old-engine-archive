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
 * File:   fgGFXLooseQuadtree.h
 * Author: vigilant
 *
 * Created on January 14, 2015, 9:58 PM
 */

#ifndef FG_INC_GFX_LOOSE_QUADTREE
    #define FG_INC_GFX_LOOSE_QUADTREE
    #define FG_INC_GFX_LOOSE_QUADTREE_BLOCK

    #include "fgGfxQuadtree.h"

namespace fg {
    namespace gfx {

        /**
         * 
         */
        class CLooseQuadtree : public CQuadtree {
        public:
            ///
            static const float DEFAULT_LOOSE_K;
             
        public:
            /**
             * 
             */
            CLooseQuadtree();
            /**
             * 
             * @param orig
             */
            CLooseQuadtree(const CLooseQuadtree& orig);
            /**
             * 
             */
            virtual ~CLooseQuadtree();

        public:
            /**
             * 
             * @param k
             */
            void setLooseK(const float k) {
                m_looseK = k;
                if(m_looseK < 1.0f)
                    m_looseK = 1.0f;
            }
            /**
             * 
             * @return 
             */
            float getLooseK(void) const {
                return m_looseK;
            }
            
            
        public:
            /**
             * 
             * @param sceneNode
             * @param treeNode
             * @return 
             */
            virtual int insert(traits::CSpatialObject* pObject, STreeNode* pTreeNode = NULL);
            
        private:
            ///
            float m_looseK;
        }; // class CLooseOctree
        
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_LOOSE_QUADTREE_BLOCK
#endif	/* FG_INC_GFX_LOOSE_QUADTREE */
