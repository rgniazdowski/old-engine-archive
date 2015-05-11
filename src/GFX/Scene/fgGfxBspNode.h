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
 * File:   fgGfxBspNode.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 11:56 AM
 */

#ifndef FG_INC_GFX_BSP_NODE
    #define FG_INC_GFX_BSP_NODE
    #define FG_INC_GFX_BSP_NODE_BLOCK

//------------------------------------------------------------------------------
    #define NODE_EMPTY      0x0
    #define NODE_SOLID      0x1
    #define NODE_LEAF       0x8
    #define N_FRONT         1
    #define N_BACK          0

    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif
    #ifndef FG_INC_GFX_PLANE
        #include "GFX/fgGfxPlane.h"
    #endif
    #ifndef FG_INC_GFX_AA_BOUNDING_BOX
        #include "GFX/fgGfxAABoundingBox.h"
    #endif

namespace fg {
    namespace gfx {

        struct SPolygon;
        class CBspTree;
        class CBspNode;
        class CBspLeaf;

        /**
         *
         */
        class CBspNode {
        public:
            ///
            typedef CBspNode self_type;
            ///
            typedef CBspNode type;

        public:
            /**
             *
             * @param pBsp
             * @param _nflags
             */
            CBspNode(CBspTree* pBsp, unsigned long int _nflags = 0);
            /**
             * 
             */
            virtual ~CBspNode();
            /**
             *
             * @return
             */
            CBspNode* getBack(void);
            /**
             *
             * @return
             */
            CBspNode* getFront(void);
            /**
             *
             * @return
             */
            CBspNode* getParent(void);
            /**
             *
             * @return
             */
            int getFrontIdx(void) const {
                return m_nodeIdx[N_FRONT];
            }
            /**
             *
             * @return
             */
            int getBackIdx(void) const {
                return m_nodeIdx[N_BACK];
            }
            /**
             *
             * @return
             */
            fgBool isEmptyLeaf(void) const {
                //BOOL IsEmptyLeaf() {return (_flags & NODE_LEAF) && !(_flags & NODE_SOLID);}
                return (fgBool)((m_flags & NODE_LEAF)) && !(m_flags & NODE_SOLID);
            }
            /**
             *
             * @return
             */
            fgBool isLeaf(void) const {
                //BOOL IsLeaf()  {return  (_flags & NODE_LEAF);}
                return (fgBool)(m_flags & NODE_LEAF);
            }
            /**
             *
             * @return
             */
            fgBool isSolid(void) const {
                //BOOL IsSolid() {return (_flags & NODE_SOLID);}
                return (fgBool)!!(m_flags & NODE_SOLID);
            }
            /**
             *
             * @return
             */
            fgBool isSpace(void) const {
                //BOOL IsSpace() {return !(_flags & NODE_SOLID) && (_flags & NODE_LEAF);}
                return (fgBool)(!(m_flags & NODE_SOLID) && ((m_flags & NODE_LEAF)));
            }
            /**
             *
             * @return
             */
            fgBool isNode(void) const {
                //BOOL IsNode() {return !(_flags & NODE_LEAF);}
                return (fgBool)(!(m_flags & NODE_LEAF));
            }
            /**
             *
             * @return
             */
            Planef& getPlane(void) const;
            /**
             *
             * @param count
             * @return
             */
            SPolygon* getPolygons(int& count);

        public:
            /**
             * 
             * @param pBsp
             */
            void setBsp(CBspTree* pBsp) {
                m_pBsp = pBsp;
            }

        public:
            ///
            int m_idxNodeThis;
            ///
            int m_idxParent;
            ///
            int m_nodeIdx[2];
            ///
            int m_planeIdx;
            ///
            int m_leafIdx;
            ///
            unsigned long int m_flags;
            ///
            int m_nPolys;
            ///
            int m_polyIdx;            
            ///
            AABoundingBox3Df m_bbox;
            ///
            CBspTree* m_pBsp;
        };

        //--------------------------------------------------------------------------------

        /**
         *
         */
        class CBspLeaf : public CBspNode {
        public:
            ///
            typedef CBspNode base_type;
            ///
            typedef CBspLeaf type;
            ///
            typedef CBspLeaf self_type;

        public:
            /**
             *
             * @param pBsp
             * @param _nflags
             */
            CBspLeaf(CBspTree* pBsp, unsigned long int _nflags = 0);
            /**
             *
             */
            virtual ~CBspLeaf();
            /**
             *
             * @param idx
             */
            void addPortalIdx(int idx) {
                m_portalIdxes.push_back(idx);
            };
            /**
             *
             * @return
             */
            CVector<int>& getPortalIdxes(void) {
                return m_portalIdxes;
            }
            /**
             *
             * @return
             */
            CVector<int> const& getPortalIdxes(void) const {
                return m_portalIdxes;
            }

        public:
            ///
            int m_pvsIdx;
            ///
            unsigned long int m_flags;
            ///
            CVector<int> m_portalIdxes;            
        };
    }
}
    #undef FG_INC_GFX_BSP_NODE_BLOCK
#endif	/* FG_INC_GFX_BSP_NODE */

