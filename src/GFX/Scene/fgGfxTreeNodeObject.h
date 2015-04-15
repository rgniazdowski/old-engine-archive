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
 * File:   fgGFXTreeNodeObject.h
 * Author: vigilant
 *
 * Created on April 14, 2015, 2:19 PM
 */

#ifndef FG_INC_GFX_TREE_NODE_OBJECT
    #define FG_INC_GFX_TREE_NODE_OBJECT
    #define FG_INC_GFX_TREE_NODE_OBJECT_BLOCK

namespace fg {
    namespace gfx {

        struct STreeNodeBase;

        /**
         *
         */
        class CTreeNodeObject {
        public:
            ///
            typedef CTreeNodeObject type;
            ///
            typedef CTreeNodeObject self_type;

        public:
            /**
             *
             */
            CTreeNodeObject() : m_pTreeNode(0) { }
            /**
             * 
             */
            virtual ~CTreeNodeObject() { }

        public:
            /**
             *
             * @param pTreeNode
             */
            inline void setTreeNode(STreeNodeBase* pTreeNode) {
                m_pTreeNode = pTreeNode;
            }
            /**
             *
             * @return
             */
            inline STreeNodeBase* getTreeNode(void) const {
                return m_pTreeNode;
            }

        protected:
            /// Pointer to the tree node in which this (3d/2d/abstract)
            /// object resides. This is for spatial partitioning
            STreeNodeBase* m_pTreeNode;
        };
    }
}

    #undef FG_INC_GFX_TREE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_TREE_NODE_OBJECT */
