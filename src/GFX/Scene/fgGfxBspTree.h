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
 * File:   fgGfxBspTree.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 12:46 PM
 */

#ifndef FG_INC_GFX_BSP_TREE
    #define FG_INC_GFX_BSP_TREE
    #define FG_INC_GFX_BSP_TREE_BLOCK

    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif
    #ifndef FG_INC_GFX_PLANE
        #include "GFX/fgGfxPlane.h"
    #endif

namespace fg {
    namespace gfx {

        class CPolygon;
        class CBspNode;
        class CBspLeaf;
        class CBspCompiler;

        /**
         *
         */
        class CBspTree {
        public:
            typedef CBspTree type;
            typedef CBspTree self_type;

        public:

            /**
             *
             */
            enum BspType {
                BSP_LEAFY = 0, BSP_TERRAIN
            };

        public:
            friend class CBspNode;
            friend class CBspCompiler;
            /**
             *
             * @param expected
             */
            CBspTree(int expected = 128);
            /**
             *
             */
            virtual ~CBspTree();
            /**
             *
             * @param bt
             */
            void SetType(BspType bt) {
                m_bspType = bt;
            }
            /**
             *
             */
            void clear(void);

            /**
             *
             * @param polys
             * @param busethreads
             */
            void process(CVector<CPolygon>& polys);

            ////////////////////////////////////////////////////////////////////
            /**
             *
             * @return
             */
            CVector<CPolygon>& getPolygons(void) {
                return m_polygons;
            };
            /**
             *
             * @return
             */
            CVector<CPolygon> const& getPolygons(void) const {
                return m_polygons;
            };
            /**
             *
             * @return
             */
            CBspNode* getRoot(void) {
                return m_nodes[0];
            }
            /**
             *
             * @return
             */
            const CBspNode* getRoot(void) const {
                return m_nodes[0];
            }
            /**
             *
             * @return
             */
            CVector<CBspNode*>& getNodes(void) {
                return m_nodes;
            }
            /**
             *
             * @return
             */
            CVector<CBspNode*> const& getNodes(void) const {
                return m_nodes;
            }
            /**
             *
             * @param idx
             * @return
             */
            CBspNode* GetNode(int idx) {
                //ASSERT(idx < (int)m_nodes.size());
                return m_nodes[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            const CBspNode* GetNode(int idx) const {
                //ASSERT(idx < (int)m_nodes.size());
                return m_nodes[idx];
            }
            /**
             *
             * @param iplane
             * @return
             */
            Planef& getPlane(int iplane) {
                //ASSERT(iplane < (int)m_planes.size());
                return m_planes[iplane];
            }
            /**
             *
             * @param iplane
             * @return
             */
            Planef const& getPlane(int iplane) const {
                //ASSERT(iplane < (int)m_planes.size());
                return m_planes[iplane];
            }
            /**
             *
             * @param idx
             * @return
             */
            CPolygon& getPolygon(int idx);
            /**
             *
             * @param idx
             * @return
             */
            CPolygon const& getPolygon(int idx) const;
            /**
             *
             * @param idx
             * @return
             */
            CBspLeaf* getLeaf(int idx) {
                //ASSERT(idx < m_leafs.size());
                return m_leafs[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            const CBspLeaf* getLeaf(int idx) const {
                //ASSERT(idx < m_leafs.size());
                return m_leafs[idx];
            }
            ////////////////////////////////////////////////////////////////////

            /**
             *
             * @param paa
             * @param pab
             * @param node
             * @param col
             * @return
             */
            fgBool segmentIntersect(Vector3f& paa, Vector3f& pab, int node, Vector3f& col);
            /**
             *
             * @param pov
             * @param nodeIdx
             * @return
             */
            int getCurrentLeaf(const Vector3f& pov, int nodeIdx = 0);
            /**
             *
             * @param nodeIdx
             * @param polys
             */
            void R_Compile(int nodeIdx, CVector<CPolygon>& polys);

        private:
            /**
             *
             * @param pNode
             * @param polys
             */
            void updateNodeBB(CBspNode* pNode, CVector<CPolygon>& polys);
            /**
             *
             */
            void makeRoot(void);
            /**
             *
             * @param polys
             */
            void buildPlaneArray(CVector<CPolygon>& polygons);

            /**
             *
             * @param nodeIdx
             * @param pols
             */
            void R_TerrainCompile(int nodeIdx, CVector<CPolygon>& polys);
            /**
             *
             * @param polys
             * @param pWantPoly
             * @return
             */
            int getBestSplitter(CVector<CPolygon>& polys,
                                CPolygon* pWantPoly = 0);
            /**
             *
             * @param pNode
             * @param polys
             * @param frontPolys
             * @param backPolys
             * @return
             */
            int partition(CBspNode* pNode,
                          CVector<CPolygon>& polys,
                          CVector<CPolygon>& frontPolys,
                          CVector<CPolygon>& backPolys);
            /**
             *
             * @param pNode
             * @param polys
             * @param frontPlys
             * @param backPolys
             */
            void partitionTerrain(CBspNode* pNode,
                                  CVector<CPolygon>& polys,
                                  CVector<CPolygon>& frontPlys,
                                  CVector<CPolygon>& backPolys);
            /**
             *
             * @param polys
             * @param pNode
             */
            void findSplitterPlane(CVector<CPolygon>& polys, CBspNode* pNode);
            /**
             *
             * @param polys
             * @param moe
             * @return
             */
            Planef getOptimSpliterPlane(CVector<CPolygon>& polys, int moe = 16);
            /**
             *
             * @param frontPolys
             * @return
             */
            fgBool formConvex(CVector<CPolygon>& frontPolys);

            /**
             *
             * @param nodeIdx
             * @param a
             * @param b
             * @param col
             * @return
             */
            fgBool R_SegmentIntersect(int nodeIdx,
                                      Vector3f& a,
                                      Vector3f& b,
                                      Vector3f& col);
            /**
             *
             * @param pNn
             */
            void addNode(CBspNode* pNode);
            /**
             *
             * @param _nflags
             * @return
             */
            CBspNode* createNode(unsigned int _nflags);

        public:
            ///
            CVector<CBspNode*> m_nodes;
            ///
            CVector<CBspLeaf*> m_leafs;
            ///
            CVector<CPolygon> m_polygons;
            ///
            CVector<Planef> m_planes;
            ///
            BspType m_bspType;
            ///
            int m_reachedDepth;
            ///
            int m_balance;
            ///
            fgBool m_hitTest;
            ///
            unsigned long int dw_deltatime;
        };
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BSP_TREE_BLOCK
#endif	/* FG_INC_GFX_BSP_TREE */
