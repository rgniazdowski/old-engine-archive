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
 * File:   fgGfxPortalProcessor.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 12:03 PM
 */

#ifndef FG_INC_GFX_PORTAL_PROCESSOR
    #define FG_INC_GFX_PORTAL_PROCESSOR
    #define FG_INC_GFX_PORTAL_PROCESSOR_BLOCK

    #include "fgBool.h"
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

        class CPortal;
        class CBspNode;
        class CBspLeaf;
        class CBspTree;
        class CBspCompiler;

        /**
         * 
         */
        class CPortalProcessor {
            friend class CPortal;
            friend class CBspCompiler;

        public:
            ///
            typedef CPortalProcessor self_type;
            ///
            typedef CPortalProcessor type;
            ///
            typedef CVector<CPortal> PortalsVec;
            ///
            typedef PortalsVec::iterator PortalsVecItor;

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
            CBspLeaf* getLeaf(int idx);
            /**
             *
             * @param idx
             * @return
             */
            CPortal& getPortal(int idx) {
                return m_portals[idx];
            }
            /**
             *
             * @param idx
             * @return
             */
            CPortal const& getPortal(int idx) const {
                return m_portals[idx];
            }
            /**
             *
             * @return
             */
            PortalsVec& getPortals(void) {
                return m_portals;
            }
            /**
             *
             * @return
             */
            inline PortalsVec const& getPortals(void) const {
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
            fgBool duplicatePortals(PortalsVec& input, PortalsVec& output);
            /**
             *
             * @param idx
             * @return
             */
            Planef& getPlane(int idx);
            /**
             *
             * @param idx
             * @return
             */
            Planef const& getPlane(int idx) const;
            /**
             *
             * @param p
             */
            void addPortal(CPortal& portal);
            /**
             *
             * @param pLeaf
             * @param portal
             */
            void clipWithLeafSides(CBspLeaf* pLeaf, CPortal& portal);

        public:
            ///
            PortalsVec m_portals;
            ///
            CBspTree* m_pTree;
            ///
            unsigned long int dw_deltatime;
        };

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PORTAL_PROCESSOR_BLOCK
#endif	/* FG_INC_GFX_PORTAL_PROCESSOR */
