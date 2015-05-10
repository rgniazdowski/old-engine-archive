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
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PVS_PROCESSOR_BLOCK
#endif	/* FG_INC_GFX_PVS_PROCESSOR */
