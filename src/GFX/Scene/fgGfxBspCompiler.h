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
        class CPolygon;
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
            /**
             *
             * @param brush
             * @param theDlg
             * @param usehthreads
             * @return
             */
            fgBool compile(CVector<CPolygon>& polys, fgBool usehthreads);
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
            ///
            CPortalProcessor m_portalProcesor;
            ///
            CPvsProcessor m_pvsProcesor;
            ///
            CBspTree m_bspTree;
            ///
            CVector<CPolygon*> m_visiblePolygons;
            ///
            fgBool m_usethreads;
        };
    }
}

    #undef FG_INC_GFX_BSP_COMPILER_BLOCK
#endif /* FG_INC_GFX_BSP_COMPILER */
