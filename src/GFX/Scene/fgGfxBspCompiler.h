/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_BSP_COMPILER
    #define FG_INC_GFX_BSP_COMPILER
    #define FG_INC_GFX_BSP_COMPILER_BLOCK

    #include "fgBool.h"
    #include "fgVector.h"
    #include "GFX/fgGfxAABoundingBox.h"
    #include "fgGfxBspGeometry.h"

//--------------------------------------------------------------------------------
    #define NODE_EMPTY      0x0
    #define NODE_SOLID      0x1
    #define NODE_LEAF       0x80000000
    #define N_FRONT         1
    #define N_BACK          0
    #define FLAG_PROCESSED  0x8000000

namespace fg {
    namespace gfx {
        class CBspTree;
        class CPolygon;
    }
}

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CBspNode {
        public:
            CBspNode(CBspTree* pBsp, unsigned long int _nflags = 0) {
                m_idxNodeThis = -1;
                m_nodeIdx[0] = -1;
                m_nodeIdx[1] = -1;
                m_planeIdx = -1;
                m_nPolys = 0;
                m_polyIdx = -1;
                m_flags = _nflags;
                m_pBsp = pBsp;
                m_leafIdx = -1;
                m_idxParent = -1;
            }
            virtual ~CBspNode() { }
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
                return m_nodeIdx[1];
            }
            /**
             *
             * @return
             */
            int getBackIdx(void) const {
                return m_nodeIdx[0];
            }
            /**
             *
             * @return
             */
            fgBool isEmptyLeaf(void) const {
                return (fgBool)(m_flags & NODE_LEAF) && !(m_flags & NODE_SOLID);
            }
            /**
             *
             * @return
             */
            fgBool isLeaf(void) const {
                return (fgBool)(m_flags & NODE_LEAF);
            }
            /**
             *
             * @return
             */
            fgBool isSolid(void) const {
                return (fgBool)(m_flags & NODE_SOLID);
            }
            /**
             *
             * @return
             */
            fgBool isSpace(void) const {
                return (fgBool)(!(m_flags & NODE_SOLID) && (m_flags & NODE_LEAF));
            }
            /**
             *
             * @return
             */
            fgBool isNode(void) const {
                return (fgBool)(!(m_flags & NODE_LEAF));
            }
            /**
             * 
             * @return
             */
            inline Planef& getPlane(void) const;
            /**
             * 
             * @param count
             * @return
             */
            inline CPolygon* getPolygons(int& count);

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
            CBspTree* m_pBsp;
            ///
            AABoundingBox3Df m_bbox;
        };

        //--------------------------------------------------------------------------------

        /**
         *
         */
        class CBspLeaf : public CBspNode {
        public:
            typedef CBspNode base_type;
            typedef CBspLeaf type;
            typedef CBspLeaf self_type;

        public:
            /**
             *
             * @param pBsp
             * @param _nflags
             */
            CBspLeaf(CBspTree* pBsp, unsigned long int _nflags = 0) : CBspNode(pBsp, _nflags),
            m_pvsIdx(-1),
            m_portIdxes(),
            m_flags(0) {
                m_portIdxes.reserve(4);
            }
            /**
             *
             */
            virtual ~CBspLeaf() {
                m_portIdxes.clear();
            }
            /**
             *
             * @param idx
             */
            void addPortalIdx(int idx) {
                m_portIdxes.push_back(idx);
            };
            /**
             *
             * @return
             */
            CVector<int>& getPortalIdxes(void) {
                return m_portIdxes;
            }
            /**
             *
             * @return
             */
            CVector<int> const& getPortalIdxes(void) const {
                return m_portIdxes;
            }

        public:
            ///
            int m_pvsIdx;
            ///
            CVector<int> m_portIdxes;
            ///
            unsigned long int m_flags;
        };



        //--------------------------------------------------------------------------------
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
            CBspTree(int expected = 128) {
                m_polygons.reserve(expected);
                m_nodes.reserve(expected * 2);
                m_balance = 6;
                m_bspType = BSP_LEAFY;
                //::InitializeCriticalSection(&c_s);
            };
            /**
             *
             */
            virtual ~CBspTree() {
                //::DeleteCriticalSection(&c_s);
                clear();
            };
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
            void process(CVector<CPolygon>& polys); // virtual from base

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
            CPolygon& getPolygon(int idx) {
                //ASSERT(idx < (int)m_polygons.size());
                return m_polygons[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            CPolygon const& getPolygon(int idx) const {
                //ASSERT(idx < (int)m_polygons.size());
                return m_polygons[idx];
            }
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
            int getCurrentLeaf(Vector3f& pov, int nodeIdx = 0);
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
            void makeRoot(void) {
                //ASSERT(m_nodes.size() == 0);
                addNode(new CBspNode(this));
            };
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
            void addNode(CBspNode* pNn) {
                pNn->m_idxNodeThis = m_nodes.size();
                //_nodes << pNn;
                m_nodes.push_back(pNn);

                if(pNn->isEmptyLeaf()) {
                    pNn->m_leafIdx = m_leafs.size();
                    //_leafs << (CBspLeaf*)pNn;
                    m_leafs.push_back((CBspLeaf*)pNn);
                }
            }
            /**
             * 
             * @param _nflags
             * @return
             */
            CBspNode* createNode(unsigned int _nflags) {
                if(_nflags & NODE_SOLID)
                    return new CBspNode(this, _nflags);
                return new CBspLeaf(this, _nflags);
            }

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
            CVector<CPolygon>* _pInPolys;
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
            ///
            fgBool b_usethreads;
            int n_thrcount;
            long int n_threadsup;
            unsigned long int h_handles[64];
            //CRITICAL_SECTION c_s;
        };

        //--------------------------------------------------------------------------------
        inline Planef& CBspNode::getPlane(void) const {
            //ASSERT(m_planeIdx >= 0 && m_planeIdx < (int)m_pBsp->m_planes.size());
            if(m_planeIdx >= 0 && m_planeIdx < (int)m_pBsp->m_planes.size())
                return m_pBsp->m_planes[m_planeIdx];
            return m_pBsp->m_planes[0];
        };
        inline CPolygon* CBspNode::getPolygons(int& count) {
            count = m_nPolys;
            return &(m_pBsp->getPolygons()[m_polyIdx]);
        };

        //--------------------------------------------------------------------------------
        class CPortalProcessor;

        /**
         *
         */
        class CPortal : public Planef {
        public:
            typedef Planef base_type;

        public:

            enum RelPos {
                ON_PLANE,
                ON_FRONT,
                ON_BACK,
                ON_SPLIT
            };

            enum StateFlags {
                NONE = 0x00,
                INITIAL = 0x01,
                DUPLICATED = 0x02,
                REVERSED = 0x04,
                DELETED = 0x08
            };

        public:
            /**
             *
             */
            CPortal() { };
            /**
             *
             */
            virtual ~CPortal() {
                m_vertexes.clear();
                m_sideLIdx.clear();
                m_sideLIdxFinal.clear();
            }
            /**
             *
             * @param pp
             */
            CPortal(CPortalProcessor* pp) : m_planeIdx(-1), m_flags(NONE), m_pPortProc(pp) { }
            /**
             *
             * @param r
             */
            CPortal(const CPortal& r) {
                m_planeIdx = r.m_planeIdx;
                m_flags = r.m_flags;
                m_vertexes = r.m_vertexes;
                m_sideLIdx = r.m_sideLIdx;
                this->n = r.n;
                this->d = r.d;
                m_pPortProc = r.m_pPortProc;
                m_idxThis = r.m_idxThis;
            }

            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
            /**
             *
             */
            void reverse(void) {
                //m_flags |= REVERSED;
                setFlag(REVERSED, FG_TRUE);
                //_n.negate();
                this->n *= -1.0f;
                this->d = -d;
                m_vertexes.reverse();
            }
            /**
             * 
             * @param r
             * @return
             */
            CPortal& operator =(const CPortal& r) {
                if(this != &r) {
                    m_planeIdx = r.m_planeIdx;
                    m_flags = r.m_flags;
                    m_vertexes = r.m_vertexes;
                    m_sideLIdx = r.m_sideLIdx;
                    this->n = r.n;
                    this->d = r.d;
                    m_pPortProc = r.m_pPortProc;
                    m_idxThis = r.m_idxThis;
                }
                return *this;
            }
            /**
             *
             * @return
             */
            Vector3f getCenter(void) const {
                Vector3f ret;
                for(unsigned int i = 0; i < m_vertexes.size(); ++i) {
                    ret += m_vertexes[i];
                }
                ret /= (float)m_vertexes.size();
                return ret;
            }
            /**
             *              
             */
            void calcNormal(void);
            /*void AdjustVxOrder() {
                            Planef tp;
                GCalcNormal(&tp, _vxes[0], _vxes[1], _vxes[2]);
                if(!IsZero(Vdp(tp._n, _n) - 1.0f, .00625f)) {
                    _vxes.reverse();
                    GCalcNormal(&tp, _vxes[0], _vxes[1], _vxes[2]);
                }
            }*/
            RelPos classify(Planef& plane) {
                int fronts = 0, backs = 0, coinciss = 0;
                int vxes = m_vertexes.size();
                float rdp;
                CVector<Vector3f>::iterator end = m_vertexes.end();
                for(CVector<Vector3f>::iterator vx = m_vertexes.begin(); vx != end; vx++) {
                    rdp = plane.distance(*vx);
                    if(rdp > .5f)
                        fronts++;
                    else if(rdp < -.5f)
                        backs++;
                    else {
                        coinciss++;
                        backs++;
                        fronts++;
                    }
                }
                if(coinciss == vxes)
                    return RelPos::ON_PLANE;
                if(fronts == vxes)
                    return RelPos::ON_FRONT;
                if(backs == vxes)
                    return RelPos::ON_BACK;
                return RelPos::ON_SPLIT;
            }
            /**
             * 
             * @param pFrom
             */
            void copyProperties(CPortal& pFrom) {
                m_planeIdx = pFrom.m_planeIdx;
                m_flags = pFrom.m_flags;
                m_sideLIdx = pFrom.m_sideLIdx;
                this->n = pFrom.n;
                this->d = pFrom.d;
                m_idxThis = pFrom.m_idxThis;
            }
            /**
             * 
             * @param idx
             */
            void addSideLeafIdx(int idx) {
                //_sideLIdx << idx;
                m_sideLIdx.push_back(idx);
            }
            /**
             * 
             * @param plane
             * @param a
             * @param b
             */
            void split(Planef& plane,
                       CPortal& a,
                       CPortal& b);
            /**
             *
             * @return
             */
            inline CBspLeaf* getBackLeaf(void);
            /**
             *
             * @return
             */
            inline CBspLeaf* getFrontLeaf(void);
            /**
             * 
             * @return
             */
            inline Planef& getPlane(void);
            /**
             * 
             * @return 
             */
            inline Planef const& getPlane(void) const;
            /**
             *
             */
            inline void clear(void) {
                m_vertexes.clear();
            }

        public:
            ///
            int m_idxThis;
            ///
            int m_planeIdx; // index in planes index of the BSP wich ortal belons too
            ///
            StateFlags m_flags;
            ///
            CVector<Vector3f> m_vertexes;
            ///
            CVector<int> m_sideLIdx;
            ///
            CVector<int> m_sideLIdxFinal;
            ///
            CPortalProcessor* m_pPortProc;
        };

        FG_ENUM_FLAGS(CPortal::StateFlags);
        inline void CPortal::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_flags |= flags;
            } else {
                m_flags |= flags;
                m_flags ^= flags;
            }
        }

        //--------------------------------------------------------------------------------

        class CPortalProcessor {
        public:
            friend class CPortal;
            friend class CBspCompiler;

        public:
            /**
             *
             */
            CPortalProcessor() {
                m_pTree = 0;
            }
            /**
             *
             */
            virtual ~CPortalProcessor() {
                clear();
            }
            /**
             *
             * @param tree
             */
            void process(CBspTree& tree);
            /**
             *
             */
            void clear(void);
            /**
             *
             * @param idx
             * @return
             */
            inline CBspLeaf* getLeaf(int idx) {
                CBspNode* pL = m_pTree->getLeaf(idx);
                //ASSERT(pL->m_flags & NODE_LEAF);
                return (CBspLeaf*)pL;
            }
            /**
             * 
             * @param idx
             * @return
             */
            inline CPortal& getPortal(int idx) {
                return m_portals[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            inline CPortal const& getPortal(int idx) const {
                return m_portals[idx];
            }
            /**
             *
             * @return
             */
            inline CVector<CPortal>& getPortals(void) {
                return m_portals;
            }
            /**
             *
             * @return
             */
            inline CVector<CPortal> const& getPortals(void) const {
                return m_portals;
            }
            /**
             *
             * @return
             */
            inline fgBool hasPortals(void) {
                return m_portals.size() > 0;
            }

        private:
            /**
             *
             * @param portal
             * @param box
             * @param b
             */
            void cutPortalWithNodeBox(CPortal& portal,
                                      AABoundingBox3Df& box,
                                      fgBool b = 0);
            /**
             *
             * @param portal
             * @param pNode
             * @return
             */
            fgBool calculateInitialPortal(CPortal& portal,
                                          CBspNode* pNode);
            /**
             *
             * @param
             * @return
             */
            fgBool validatePortal(CPortal& portal);
            /**
             *
             * @param i
             * @param o
             * @return
             */
            fgBool duplicatePortals(CVector<CPortal>& i, CVector<CPortal>& o);
            /**
             *
             * @param idx
             * @return
             */
            Planef& getPlane(int idx) {
                return m_pTree->getPlane(idx);
            }
            /**
             * 
             * @param idx
             * @return 
             */
            Planef const& getPlane(int idx) const {
                return m_pTree->getPlane(idx);
            }
            /**
             *
             * @param p
             */
            void addPortal(CPortal& portal) {
                portal.m_idxThis = m_portals.size();
                //_portals << p;
                m_portals.push_back(portal);
            }
            /**
             *
             * @param pLeaf
             * @param portal
             */
            void clipWithLeafSides(CBspLeaf* pLeaf, CPortal& portal);

        public:
            ///
            CVector<CPortal> m_portals;
            ///
            CBspTree* m_pTree;
            ///
            unsigned long int dw_deltatime;
        };

        //----------------------------------------------------------------------------------------
        inline CBspLeaf* CPortal::getBackLeaf(void) {
            //ASSERT(m_sideLIdx.size() == 2);
            return m_pPortProc->getLeaf(m_sideLIdx[0]);
        }
        inline CBspLeaf* CPortal::getFrontLeaf(void) {
            //ASSERT(m_sideLIdx.size() == 2);
            return m_pPortProc->getLeaf(m_sideLIdx[1]);
        }
        Planef& CPortal::getPlane(void) {
            return m_pPortProc->getPlane(m_planeIdx);
        }
        Planef const& CPortal::getPlane(void) const {
            return m_pPortProc->getPlane(m_planeIdx);
        }

        //--------------------------------------------------------------------------------

        /**
         *
         * @param sz
         */
        struct SPortalData {
            /**
             *
             * @param sz
             */
            SPortalData(int sz) : portArrPvs(sz) {
                possibleVisCount = 0;
                size = portArrPvs.size();
            }
            /**
             *
             */
            virtual ~SPortalData() { }

        public:
            ///
            int size;
            ///
            int possibleVisCount;
            ///
            CBitArray portArrPvs;
        };

        //--------------------------------------------------------------------------------

        /**
         *
         */
        class CPvsProcessor {
        public:
            /**
             *
             */
            CPvsProcessor() : m_nLeafs(0), m_pvs(0), m_cPvss(0) { }
            /**
             *
             */
            virtual ~CPvsProcessor() {
                clear();
            };
            /**
             *
             */
            void clear(void) {
                delete[] m_pvs;
                m_pvs = 0;
                m_cPvss = 0;
                CVector<SPortalData*>::iterator end = m_portVs.end();
                for(CVector<SPortalData*>::iterator pp = m_portVs.begin(); pp != end; pp++) {
                    if(!(*pp))
                        continue;
                    delete[] (*pp);
                }
                m_portVs.clear();
                dw_deltatime = timesys::ticks();

            };
            /**
             * 
             * @param tree
             * @param portalprc
             */
            void process(CBspTree& tree, CPortalProcessor& portalprc);

        private:
            /**
             *
             * @param rPortals
             * @return
             */
            fgBool InitalPortalVis(CVector<CPortal>& rPortals);

            /**
             *
             * @param portal
             * @param pVis
             * @param nLeaf
             */
            void R_PortalFlood(CPortal& portal,
                               unsigned char* pVis,
                               int nLeaf); // flood in neghbour leaf

            /**
             * 
             * @param pOrigin
             * @param rPortals
             * @param prevPvs
             */
            void performPVS(CPortal& pOrigin,
                            CVector<CPortal>& rPortals,
                            unsigned char* prevPvs);

            /**
             * 
             */
            void gatherLeafsVis(void);

            /**
             *
             * @param a
             * @param b
             * @return
             */
            fgBool doesPortalSeesPortal(CPortal& a, CPortal& b);

            ///
            CBspTree* m_pBspTree;
            ///
            CPortalProcessor* m_pPortProc;
            ///
            int m_nLeafs;

        public:
            ///
            unsigned char* m_pvs;
            ///
            int m_cPvss;
            ///
            CVector<SPortalData*> m_portVs;
            ///
            unsigned long int dw_deltatime;
        };


        //--------------------------------------------------------------------------------

        /**
         * 
         */
        class CBspCompiler {
        public:
            /**
             *
             */
            CBspCompiler() { };
            /**
             *
             */
            virtual ~CBspCompiler() { };
            /**
             *
             * @param brush
             * @param theDlg
             * @param usehthreads
             * @return
             */
            fgBool compile(fgBool usehthreads);
            /**
             *
             * @param mode
             * @param is3D
             */
            void render(unsigned int mode, fgBool is3D);
            /**
             *
             */
            void clear(void);

        private:
            /**
             *
             * @param is3D
             */
            void renderBSP(fgBool is3D);
            /**
             * 
             * @param is3D
             */
            void renderPortals(fgBool is3D);

        public:
            ///
            CPortalProcessor m_portalProcesor;
            ///
            CPvsProcessor m_pvsProcesor;
            ///
            CBspTree m_bspTree;
            ///
            fgBool m_usethreads;
        };
    }
}

    #undef FG_INC_GFX_BSP_COMPILER_BLOCK
#endif /* FG_INC_GFX_BSP_COMPILER */
