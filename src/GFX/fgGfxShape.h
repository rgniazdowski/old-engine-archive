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
 * File:   fgGfxShape.h
 * Author: vigilant
 *
 * Created on September 10, 2015, 11:15 AM
 */

#ifndef FG_INC_GFX_SHAPE
    #define FG_INC_GFX_SHAPE
    #define FG_INC_GFX_SHAPE_BLOCK

    #include "fgGfxMesh.h"
    #include "fgGfxSkinnedMesh.h"

    #ifndef FG_INC_GFX_MATERIAL
        #include "fgGfxMaterial.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SShape {
            typedef SShape self_type;
            typedef SShape type;

            ///
            std::string name;
            ///
            SMaterial* material;
            ///
            SMeshBase* mesh;
            /**
             *
             */
            SShape();
            /**
             *
             */
            virtual ~SShape();
            //------------------------------------------------------------------

            /**
             *
             */
            void updateAABB(void);
            /**
             *
             */
            void destroy(void);
            /**
             *
             */
            void clear(void);
            //------------------------------------------------------------------

            /**
             *
             * @return
             */
            fgBool isSoA(void) const;
            /**
             *
             * @return
             */
            fgBool isAoS(void) const;
            /**
             *
             * @return
             */
            fgBool isSkinned(void) const;
            /**
             *
             * @return
             */
            SSkinnedMesh* getSkinnedMesh(void);
            /**
             *
             * @return
             */
            SMeshAoS* getMeshAoS(void);
            /**
             *
             * @return
             */
            SMeshSoA* getMeshSoA(void);
            //------------------------------------------------------------------

            /**
             *
             * @return
             */
            fgGFXuint size(void) const;
            /**
             *
             * @return
             */
            fgGFXsizei stride(void) const;
            /**
             *
             * @return
             */
            fgGFXuint attribMask(void) const;

            /**
             *
             * @return
             */
            fgGFXuint components(void) const;
            /**
             *
             * @return
             */
            fgBool empty(void) const;
            /**
             * 
             * @return
             */
            fgGFXvoid *front(void) const;
            /**
             *
             * @return
             */
            size_t getDataSize(void);
        }; // struct SShape

    } // namespace gfx
} // namespace fg


    #undef FG_INC_GFX_SHAPE_BLOCK
#endif	/* FG_INC_GFX_SHAPE */
