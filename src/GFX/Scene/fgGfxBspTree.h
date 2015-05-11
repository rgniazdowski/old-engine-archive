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
    #ifndef FG_INC_GFX_MATERIAL
        #include "GFX/fgGfxMaterial.h"
    #endif

namespace fg {
    namespace gfx {

        struct SMaterial;
        struct SPolygon;
        class CBspNode;
        class CBspLeaf;
        class CBspCompiler;

        /**
         *
         */
        class CBspTree {
        public:
            ///
            typedef CBspTree type;
            ///
            typedef CBspTree self_type;

            typedef CVector<CBspNode*> NodesVec;
            typedef NodesVec::iterator NodesVecItor;
            typedef NodesVec::const_iterator NodesVecConstItor;

            typedef CVector<CBspLeaf*> LeafsVec;
            typedef LeafsVec::iterator LeafsVecItor;
            typedef LeafsVec::const_iterator LeafsVecConstItor;

            typedef CVector<SPolygon> PolygonsVec;
            typedef PolygonsVec::iterator PolygonsVecItor;
            typedef PolygonsVec::const_iterator PolygonsVecConstItor;

            typedef CVector<Planef> PlanesVec;
            typedef PlanesVec::iterator PlanesVecItor;
            typedef PlanesVec::const_iterator PlanesVecConstItor;

            typedef CVector<SMaterial> MaterialsVec;
            typedef MaterialsVec::iterator MaterialsVecItor;
            typedef MaterialsVec::const_iterator MaterialsVecConstItor;

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
            void setType(BspType bt) {
                m_bspType = bt;
            }
            /**
             *
             */
            void clear(void);

            /**
             *
             * @param polygons
             * @param busethreads
             */
            void process(PolygonsVec& polygons);

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

            //------------------------------------------------------------------
        public:
            /**
             *
             * @return
             */
            BspType getBspType(void) const {
                return m_bspType;
            }
            //------------------------------------------------------------------
            /**
             *
             * @return
             */
            NodesVec& getNodes(void) {
                return m_nodes;
            }
            /**
             *
             * @return
             */
            NodesVec const& getNodes(void) const {
                return m_nodes;
            }
            /**
             *
             * @return
             */
            LeafsVec& getLeafs(void) {
                return m_leafs;
            }
            /**
             *
             * @return
             */
            LeafsVec const& getLeafs(void) const {
                return m_leafs;
            }
            /**
             *
             * @return
             */
            PolygonsVec& getPolygons(void) {
                return m_polygons;
            }
            /**
             *
             * @return
             */
            PolygonsVec const& getPolygons(void) const {
                return m_polygons;
            }
            /**
             *
             * @return
             */
            PlanesVec& getPlanes(void) {
                return m_planes;
            }
            /**
             *
             * @return
             */
            PlanesVec const& getPlanes(void) const {
                return m_planes;
            }
            /**
             *
             * @return
             */
            MaterialsVec& getMaterials(void) {
                return m_materials;
            }
            /**
             *
             * @return
             */
            MaterialsVec const& getMaterials(void) const {
                return m_materials;
            }
            //------------------------------------------------------------------
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
             * @param idx
             * @return
             */
            CBspNode* getNode(unsigned int idx) {
                if(idx >= m_nodes.size())
                    return NULL;
                return m_nodes[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            const CBspNode* getNode(unsigned int idx) const {
                if(idx >= m_nodes.size())
                    return NULL;
                return m_nodes[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            Planef& getPlane(unsigned int idx) {
                return m_planes[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            Planef const& getPlane(unsigned int idx) const {
                return m_planes[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            SPolygon& getPolygon(unsigned int idx);
            /**
             *
             * @param idx
             * @return
             */
            SPolygon const& getPolygon(unsigned int idx) const;
            /**
             *
             * @param idx
             * @return
             */
            CBspLeaf* getLeaf(unsigned int idx) {
                if(idx >= m_leafs.size())
                    return NULL;
                return m_leafs[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            const CBspLeaf* getLeaf(unsigned int idx) const {
                if(idx >= m_leafs.size())
                    return NULL;
                return m_leafs[idx];
            }
            //------------------------------------------------------------------
        public:
            /**
             * 
             * @return
             */
            int getBalance(void) const {
                return m_balance;
            }
            /**
             * 
             * @param balance
             */
            void setBalance(unsigned int balance) {
                m_balance = balance;
            }
            //------------------------------------------------------------------
        private:
            /**
             *
             * @param nodeIdx
             * @param polygons
             */
            void R_TerrainCompile(int nodeIdx, PolygonsVec& polygons);
            /**
             *
             * @param pNode
             * @param polygons
             * @param frontPlys
             * @param backPolys
             */
            void partitionTerrain(CBspNode* pNode,
                                  PolygonsVec& polygons,
                                  PolygonsVec& frontPlys,
                                  PolygonsVec& backPolys);
            /**
             *
             * @param nodeIdx
             * @param polygons
             */
            void R_Compile(int nodeIdx, PolygonsVec& polygons);
            /**
             *
             * @param pNode
             * @param polygons
             * @param frontPolys
             * @param backPolys
             * @return
             */
            int partition(CBspNode* pNode,
                          PolygonsVec& polygons,
                          PolygonsVec& frontPolys,
                          PolygonsVec& backPolys);
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
             * @param pNode
             * @param polygons
             */
            void updateNodeBB(CBspNode* pNode, PolygonsVec& polygons);
            /**
             *
             */
            void makeRoot(void);
            /**
             *
             * @param polygons
             */
            void buildPlaneArray(PolygonsVec& polygons);

            /**
             *
             * @param polygons
             * @param pWantPoly
             * @return
             */
            int getBestSplitter(PolygonsVec& polygons,
                                SPolygon* pWantPoly = 0);

            /**
             *
             * @param polygons
             * @param pNode
             */
            void findSplitterPlane(PolygonsVec& polygons, CBspNode* pNode);
            /**
             *
             * @param polygons
             * @param moe
             * @return
             */
            Planef getOptimSpliterPlane(PolygonsVec& polygons, int moe = 16);
            /**
             *
             * @param frontPolys
             * @return
             */
            fgBool formConvex(PolygonsVec& frontPolygons);
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
            CBspNode* createNode(unsigned int flags);

        public:
            ///
            NodesVec m_nodes;
            ///
            LeafsVec m_leafs;
            ///
            PolygonsVec m_polygons;
            ///
            PlanesVec m_planes;
            ///
            MaterialsVec m_materials;
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
