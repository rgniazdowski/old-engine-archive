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

#ifndef FG_INC_GFX_SPATIAL_OBJECT
    #define FG_INC_GFX_SPATIAL_OBJECT
    #define FG_INC_GFX_SPATIAL_OBJECT_BLOCK

    #include "GFX/fgGfxBoundingVolume.h"
    #include "fgTraits.h"

namespace fg {
    namespace gfx {

        struct STreeNodeBase;

        namespace traits {

            /**
             *
             */
            class CSpatialObject {
            public:
                ///
                typedef CSpatialObject self_type;
                ///
                typedef CSpatialObject type;
                /// Bounding box type - axis-aligned
                typedef AABoundingBox3Df box_type;
            public:
                static const fg::traits::SceneNode SELF_TRAIT = fg::traits::SPATIAL;

            public:
                /**
                 *
                 */
                CSpatialObject() : m_pTreeNode(0) { }
                /**
                 *
                 */
                virtual ~CSpatialObject() { }

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
                //--------------------------------------------------------------
                /**
                 *
                 * @param aabb
                 */
                inline void setBoundingVolume(const AABoundingBox3Df& aabb) {
                    m_aabb.invalidate();
                    m_aabb.merge(aabb);
                }
                /**
                 *
                 * @param aabb
                 */
                inline void setBoundingVolume(const BoundingVolume3Df& aabb) {
                    m_aabb = aabb;
                }
                /**
                 *
                 * @return
                 */
                inline BoundingVolume3Df& getBoundingVolume(void) {
                    return m_aabb;
                }
                /**
                 *
                 * @return
                 */
                inline BoundingVolume3Df const& getBoundingVolume(void) const {
                    return m_aabb;
                }

            protected:
                /// Pointer to the tree node in which this (3d/2d/abstract)
                /// object resides. This is for spatial partitioning
                STreeNodeBase* m_pTreeNode;
                /// Bounding volume (aabb + sphere)
                BoundingVolume3Df m_aabb;
            }; // CSpatialObject

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SPATIAL_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SPATIAL_OBJECT */
