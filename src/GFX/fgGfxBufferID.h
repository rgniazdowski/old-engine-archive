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
 * File:   fgGFXBufferID.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:39 PM
 */

#ifndef FG_INC_GFX_BUFFERID
    #define FG_INC_GFX_BUFFERID
    #define FG_INC_GFX_BUFFERID_BLOCK

    #include "fgGfxGL.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SBufferID {
            ///
            fgGFXuint id;
            ///
            fgGFXenum target;
            ///
            fgGFXenum usage;

            //
            operator fgGFXint() const {
                return (fgGFXint)id;
            }

            //
            operator fgGFXuint() const {
                return id;
            }

            //
            fgGFXuint& refID(void) {
                return id;
            }

            //
            fgGFXuint* ptrID(void) {
                return &id;
            }
            /**
             *
             * @param _id
             * @param _target
             */
            SBufferID(fgGFXuint _id = 0, fgGFXenum _target = (fgGFXenum)0) :
            id(_id), target(_target) { }
        };
    }
}

    #undef FG_INC_GFX_BUFFERID_BLOCK
#endif	/* FG_INC_GFX_BUFFERID */
