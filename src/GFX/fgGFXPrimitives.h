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
    
namespace fg {
    namespace gfx {

        struct SMeshBase;
        struct SMeshAoS;
        struct SMeshSoA;
        
        /**
         *
         */
        enum class PrimitiveMode {
            TRIANGLES = (fgGFXenum)GL_TRIANGLES,
            TRIANGLE_STRIP = (fgGFXenum)GL_TRIANGLE_STRIP,
            TRIANGLE_FAN = (fgGFXenum)GL_TRIANGLE_FAN,
            LINES = (fgGFXenum)GL_LINES,
            LINE_LOOP = (fgGFXenum)GL_LINE_LOOP,
            LINE_STRIP = (fgGFXenum)GL_LINE_STRIP
        };

        /*
         *
         */
        class CPrimitives {
        public:

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param attrData
             * @param drawingInfo
             * @param attribMask
             */
            static void applyAttributeData(SAttributeData *attrData,
                                           SDrawingInfo& drawingInfo,
                                           const unsigned int attribMask);

            /**
             * 
             * @param mesh
             * @param rings
             * @param sectors
             * @param radius
             */
            static void createSphereMesh(SMeshBase *mesh,
                                         unsigned int rings,
                                         unsigned int sectors,
                                         float radius = 1.0f);

            /**
             * 
             * @param mesh
             * @param scale
             */
            static void createCubeMesh(SMeshBase *mesh,
                                       float scale = 1.0f);

            /*static void drawVertexDataIndexed(const CVertexData *inputData,
                                       const CVector<fgGFXushort>& indices,
                                       const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                       const PrimitiveMode mode = PrimitiveMode::TRIANGLES);*/

            ////////////////////////////////////////////////////////////////////

            static void drawSkyBoxOptimized(void);

            /**
             * 
             * @param aabb
             * @param color
             */
            static void drawAABBLines(const AABoundingBox3Df& aabb, const fgColor4f& color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f));

            static void drawSquare2D(void);

            static void drawRect2D(void);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            static void drawVertexData(const CVertexData *inputData,
                                       const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                       const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            static void drawArray(const fg::CVector<Vertex2v> &inputData,
                                  const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            static void drawArray(const fg::CVector<Vertex3v> &inputData,
                                  const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            static void drawArray(const fg::CVector<Vertex4v> &inputData,
                                  const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            ////////////////////////////////////////////////////////////////////

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            static void drawArrayIndexed(const fg::CVector<Vertex2v> &inputData,
                                         const CVector<fgGFXushort>& indices,
                                         const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                         const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            static void drawArrayIndexed(const fg::CVector<Vertex3v> &inputData,
                                         const CVector<fgGFXushort>& indices,
                                         const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT,
                                         const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            static void drawArrayIndexed(const fg::CVector<Vertex4v> &inputData,
                                         const CVector<fgGFXushort>& indices,
                                         const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT,
                                         const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /* ***************** 2 component vertex struct - pos, uv **********/
    #if 0
            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     float sizex, float sizey,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     const Vector2f &size,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex2v> &outputData,
                                     const Vector2f &relPos, const Vector2f &size,
                                     const Vector2f &uv1, const Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
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
                                     const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(CVertexData *outputData,
                                     const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgColor4f &color,
                                     const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(CVertexData *outputData,
                                     const fg::Vector2f &relPos, const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const fgColor4f &color,
                                     const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /* ***************** 4 component vertex struct - pos, norm, uv ************ */
    #if 0
            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     float sizex, float sizey,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);

            /*
             *
             */
            static void appendRect2D(fg::CVector<Vertex4v> &outputData,
                                     const fg::Vector2f &relPos, const fg::Vector2f &size,
                                     const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                                     const PrimitiveMode mode = FG_GFX_TRIANGLES,
                                     const fgBool rewind = FG_FALSE);
    #endif
        };
    };
};

    #undef FG_INC_GFX_PRIMITIVES_BLOCK
#endif /* FG_INC_GFX_PRIMITIVES */
