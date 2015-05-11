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
 * File:   fgGfxPvsProcessor.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 12:03 PM
 */

#ifndef FG_INC_GFX_PVS_PROCESSOR
    #define FG_INC_GFX_PVS_PROCESSOR
    #define FG_INC_GFX_PVS_PROCESSOR_BLOCK

    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif

    #include "fgGfxBspTypes.h"

namespace fg {
    namespace gfx {

        /**
         * 
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

        class CBspNode;
        class CBspLeaf;
        class CBspTree;
        class CPortal;
        class CPortalProcessor;

        /**
         *
         */
        class CPvsProcessor {
        public:
            typedef CPvsProcessor self_type;
            typedef CPvsProcessor type;

            typedef CVector<CPortal> PortalsVec;
            typedef PortalsVec::iterator PortalsVecItor;

            typedef CVector<SPortalData*> PPortalsDataVec;
            typedef PPortalsDataVec::iterator PPortalsDataVecItor;

        public:
            /**
             *
             */
            CPvsProcessor();
            /**
             *
             */
            virtual ~CPvsProcessor();
            /**
             *
             */
            void clear(void);
            /**
             *
             * @param tree
             * @param portalprc
             */
            void process(CBspTree& bspTree, CPortalProcessor& portalProc);

        private:
            /**
             *
             * @param rPortals
             * @return
             */
            fgBool InitalPortalVis(PortalsVec& rPortals);

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
                            PortalsVec& rPortals,
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

        public:
            /**
             *
             * @return
             */
            PPortalsDataVec& getPortalsData(void) {
                return m_portVs;
            }
            /**
             * 
             * @return
             */
            PPortalsDataVec const& getPortalsData(void) const {
                return m_portVs;
            }
            /**
             * 
             * @return
             */
            int getNumLeafs(void) const {
                return m_numLeafs;
            }
            /**
             * 
             * @param numLeafs
             * @return 
             */
            void setNumLeafs(unsigned int numLeafs) {
                m_numLeafs = numLeafs;
            }
            /**
             *
             * @return
             */
            int getNumPvs(void) const {
                return m_numPvs;
            }
            /**
             * 
             * @return
             */
            unsigned char* getPvs(void) const {
                return m_pvs;
            }
            /**
             * 
             * @param ptr
             * @param numPvs
             */
            void setPvsArray(unsigned char *ptr, int numPvs) {
                if(m_pvs)
                    delete [] m_pvs;
                m_pvs = ptr;
                m_numPvs = numPvs;
            }

        private:
            ///
            CBspTree* m_pBspTree;
            ///
            CPortalProcessor* m_pPortProc;
            ///
            int m_numLeafs;

        public:
            ///
            unsigned char* m_pvs;
            ///
            int m_numPvs;
            ///
            PPortalsDataVec m_portVs;
            ///
            unsigned long int dw_deltatime;
        };
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PVS_PROCESSOR_BLOCK
#endif	/* FG_INC_GFX_PVS_PROCESSOR */
