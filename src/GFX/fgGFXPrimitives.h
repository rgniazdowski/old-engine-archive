/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_PRIMITIVES
    #define FG_INC_GFX_PRIMITIVES
    #define FG_INC_GFX_PRIMITIVES_BLOCK

    #include "fgGFXStdInc.h"
    #include "Math/fgMathLib.h"
    #ifndef FG_INC_GFX_SHADER_PROGRAM
        #include "GFX/Shaders/fgGFXShaderProgram.h"
    #endif

    #include "fgGFXAABoundingBox.h"

enum class fgGfxPrimitiveMode {
    FG_GFX_TRIANGLES = (fgGFXenum)GL_TRIANGLES,
    FG_GFX_TRIANGLE_STRIP = (fgGFXenum)GL_TRIANGLE_STRIP,
    FG_GFX_TRIANGLE_FAN = (fgGFXenum)GL_TRIANGLE_FAN,
    FG_GFX_LINES = (fgGFXenum)GL_LINES,
    FG_GFX_LINE_LOOP = (fgGFXenum)GL_LINE_LOOP,
    FG_GFX_LINE_STRIP = (fgGFXenum)GL_LINE_STRIP
};

namespace fg {
    namespace gfx {

        /*
         *
         */
        class CPrimitives {
        public:
            static void drawSquare2D(void);

            static void drawRect2D(void);

            static void drawSkyBoxOptimized(void);

            static void drawAABBLines(const AABoundingBox3Df& aabb);

            /*
             *
             */
            static void drawArray2D(const CVertexData *inputData,
                                    const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                    const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES);

            /*
             *
             */
            static void drawArray2D(const fg::CVector<Vertex2v> &inputData,
                                    const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                    const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES);

            /*
             *
             */
            static void drawArray2D(const fg::CVector<Vertex3v> &inputData,
                                    const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT,
                                    const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES);

            /*
             *
             */
            static void drawArray2D(const fg::CVector<Vertex4v> &inputData,
                                    const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT,
                                    const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES);

            /* ***************** 2 component vertex struct - pos, uv ************ */
    #if 0
            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     float sizex, float sizey,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     const Vector2f &size,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     const Vector2f &relPos, const Vector2f &size,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);
    #endif
            /* ***************** 3 component vertex struct - pos, norm, uv ************ */

            /*
             *
             */
            static void appendRect2D(CVertexData *outputData,
                                     float sizex, float sizey,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgColor4f &color,
                                     const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(CVertexData *outputData,
                                     const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgColor4f &color,
                                     const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(CVertexData *outputData,
                                     const fg::Vector2f &relPos, const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgColor4f &color,
                                     const fgGfxPrimitiveMode mode = fgGfxPrimitiveMode::FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /* ***************** 4 component vertex struct - pos, norm, uv ************ */
    #if 0
            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     float sizex, float sizey,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     const fg::Vector2f &relPos, const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);
    #endif
        };
    };
};

    #undef FG_INC_GFX_PRIMITIVES_BLOCK
#endif /* FG_INC_GFX_PRIMITIVES */
