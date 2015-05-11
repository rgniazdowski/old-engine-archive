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
    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif
    #ifndef FG_INC_GFX_BSP_TYPES
        #include "fgGfxBspTypes.h"
    #endif
    #ifndef FG_INC_GFX_POLYGON
        #include "GFX/fgGfxPolygon.h"
    #endif
    #ifndef FG_INC_GFX_PORTAL
        #include "fgGfxPortal.h"
    #endif
    #ifndef FG_INC_GFX_BSP_TREE
        #include "fgGfxBspTree.h"
    #endif
    #ifndef FG_INC_GFX_BSP_NODE
        #include "fgGfxBspNode.h"
    #endif
    #ifndef FG_INC_GFX_PORTAL_PROCESSOR
        #include "fgGfxPortalProcessor.h"
    #endif
    #ifndef FG_INC_GFX_PVS_PROCESSOR
        #include "fgGfxPvsProcessor.h"
    #endif


namespace fg {
    namespace gfx {
        class CBspNode;
        class CBspLeaf;
        class CBspTree;
        class CBspCompiler;
        struct SPolygon;
        class CFrustum;
        class CPortal;
    }
}

namespace fg {
    namespace gfx {

        /**
         * 
         */
        class CBspCompiler {
        public:
            ///
            typedef CBspCompiler self_type;
            ///
            typedef CBspCompiler type;

            typedef CVector<SPolygon*> PPolygonsVec;
            ///
            typedef PPolygonsVec::iterator PPolygonsVecItor;
            ///
            typedef PPolygonsVec::const_iterator PPolygonsVecConstItor;

        public:
            /**
             *
             */
            CBspCompiler();
            /**
             *
             */
            virtual ~CBspCompiler() {
                clear();
            };

        public:
            /**
             *
             * @param brush
             * @param theDlg
             * @param usehthreads
             * @return
             */
            fgBool compile(CVector<SPolygon>& polygons, fgBool usehthreads = FG_FALSE);
            /**
             *
             */
            void clear(void);

        public:
            /**
             *
             * @param is3D
             * @param camPos
             * @param frustum
             */
            void display(const Vector3f& camPos, CFrustum& frustum, fgBool is3D = FG_TRUE);
            /**
             *
             */
            void render(void);
            /**
             * 
             * @param is3D
             */
            void renderPortals(fgBool is3D = FG_TRUE);

        public:
            /**
             *
             * @return
             */
            CPortalProcessor& getPortalProcessor(void) {
                return m_portalProcessor;
            }
            /**
             *
             * @return
             */
            CPortalProcessor const& getPortalProcessor(void) const {
                return m_portalProcessor;
            }
            /**
             *
             * @return
             */
            CPortalProcessor* getPortalProcessorPtr(void) {
                return &m_portalProcessor;
            }
            /**
             *
             * @return
             */
            CPvsProcessor& getPvsProcessor(void) {
                return m_pvsProcessor;
            }
            /**
             *
             * @return
             */
            CPvsProcessor const& getPvsProcessor(void) const {
                return m_pvsProcessor;
            }
            /**
             *
             * @return
             */
            CPvsProcessor* getPvsProcessorPtr(void) {
                return &m_pvsProcessor;
            }
            /**
             *
             * @return
             */
            CBspTree& getBspTree(void) {
                return m_bspTree;
            }
            /**
             *
             * @return
             */
            CBspTree const& getBspTree(void) const {
                return m_bspTree;
            }
            /**
             *
             * @return
             */
            CBspTree* getBspTreePtr(void) {
                return &m_bspTree;
            }

        public:
            CBspTree::BspType getBspType(void) const {
                return m_bspTree.getBspType();
            }

        private:
            ///
            CPortalProcessor m_portalProcessor;
            ///
            CPvsProcessor m_pvsProcessor;
            ///
            CBspTree m_bspTree;
            ///
            PPolygonsVec m_visiblePolygons;
            ///
            fgBool m_usethreads;
        };
    }
}

    #undef FG_INC_GFX_BSP_COMPILER_BLOCK
#endif /* FG_INC_GFX_BSP_COMPILER */
