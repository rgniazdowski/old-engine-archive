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
 * File:   fgGfxPlaneGrid.h
 * Author: vigilant
 *
 * Created on May 9, 2015, 6:58 PM
 */

#ifndef FG_INC_GFX_PLANE_GRID
    #define FG_INC_GFX_PLANE_GRID
    #define FG_INC_GFX_PLANE_GRID_BLOCK

    #ifndef FG_INC_GFX_PLANE
        #include "fgGfxPlane.h"
    #endif
    #ifndef FG_INC_GFX_VERTEX_DATA
        #include "fgGfxVertexData.h"
    #endif

namespace fg {
    namespace gfx {

        class CShaderProgram;
        class CProjection;
        class CMVMatrix;
        class CMVPMatrix;
        class CVertexData;
        class CVertexData4v;

        /**
         *
         */
        struct SPlaneGridf : public Planef {
            typedef SPlaneGridf self_type;
            typedef SPlaneGridf type;
            typedef Planef base_type;

            ///
            float cellSize;
            ///
            Vector2f dimensions;
            ///
            Matrix4f modelMat;
            ///
            CVertexData4v gridLines;
            /**
             * 
             */
            SPlaneGridf();
            /**
             *
             */
            SPlaneGridf(float _cellSize, const Vector2f& _dimensions);
            /**
             *
             */
            virtual ~SPlaneGridf() { }

            /**
             *
             */
            void render(CShaderProgram* pProgram, CMVPMatrix* pMVP);

            /**
             *
             * @param inputPoint
             * @param outputPoint
             */
            void snapTo(const Vector3f& inputPoint,
                        Vector3f& outputPoint,
                        float threshold = 0.2f,
                        fgBool snapHalf = FG_FALSE,
                        fgBool refreshMatrix = FG_FALSE);
            /**
             *
             * @param inputPoint
             * @return
             */
            inline Vector3f snapTo(const Vector3f& inputPoint,
                                   float threshold = 0.2f,
                                   fgBool snapHalf = FG_FALSE,
                                   fgBool refreshMatrix = FG_FALSE) {
                Vector3f outputPoint;
                snapTo(inputPoint, outputPoint, threshold, snapHalf, refreshMatrix);
                return outputPoint;
            }

        };
    }
}

    #undef FG_INC_GFX_PLANE_GRID_BLOCK
#endif	/* FG_INC_GFX_PLANE_GRID */
