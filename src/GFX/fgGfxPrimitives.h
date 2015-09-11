/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_PRIMITIVES
    #define FG_INC_GFX_PRIMITIVES
    #define FG_INC_GFX_PRIMITIVES_BLOCK

    #include "fgGfxStdInc.h"
    #include "Math/fgMathLib.h"
    #ifndef FG_INC_GFX_SHADER_PROGRAM
        #include "GFX/Shaders/fgGfxShaderProgram.h"
    #endif

    #include "fgGfxAABoundingBox.h"

namespace fg {
    namespace gfx {

        struct SMeshBase;
        struct SMeshAoS;
        struct SMeshSoA;

        /*
         *
         */
        namespace primitives {

            //------------------------------------------------------------------

            /**
             * 
             * @param attrData
             * @param drawingInfo
             * @param attribMask
             */
            void applyAttributeData(SAttributeData *attrData,
                                    SDrawingInfo& drawingInfo,
                                    const AttributeMask attribMask,
                                    unsigned int count = 0);

            /**
             * 
             * @param attrData
             * @param drawingInfo
             * @param attribMask
             */
            inline void applyAttributeData(CVector<SAttributeData>& attrData,
                                           SDrawingInfo& drawingInfo,
                                           const AttributeMask attribMask) {
                unsigned int count = attrData.size();
                if(!count)
                    return;
                applyAttributeData(&attrData.front(), drawingInfo, attribMask, count);
            }

            /**
             * 
             * @param mesh
             * @param rings
             * @param sectors
             * @param radius
             */
            void createSphereMesh(SMeshBase *mesh,
                                  unsigned int rings,
                                  unsigned int sectors,
                                  float radius = 1.0f);

            /**
             * 
             * @param mesh
             * @param scale
             */
            void createHexagonalPrismMesh(SMeshBase *pMesh, float scale = 1.0f,
                                          fgBool shouldPreRotate = FG_FALSE,
                                          float angle = 0.0f,
                                          const Vec3f& axis = Vec3f(0.0f, 0.0f, 0.0f));

            /**
             * 
             * @param mesh
             * @param scale
             * @param shouldPreRotate
             * @param angle
             * @param axis
             */
            void createOctagonalPrismMesh(SMeshBase *pMesh, float scale = 1.0f,
                                          fgBool shouldPreRotate = FG_FALSE,
                                          float angle = 0.0f,
                                          const Vec3f& axis = Vec3f(0.0f, 0.0f, 0.0f));

            /**
             * 
             * @param mesh
             * @param scale
             */
            void createCubeMesh(SMeshBase *mesh, float scale = 1.0f);

            /**
             * 
             * @param mesh
             * @param scale
             */
            void createQuadMesh(SMeshBase *mesh, float scale = 1.0f);

            /*void drawVertexDataIndexed(const CVertexData *inputData,
                                       const CVector<fgGFXushort>& indices,
                                       const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                       const PrimitiveMode mode = PrimitiveMode::TRIANGLES);*/

            //------------------------------------------------------------------

            void drawSkyBoxOptimized(void);

            /**
             * 
             * @param aabb
             * @param color
             */
            void drawAABBLines(const AABoundingBox3Df& aabb, const Color4f& color = Color4f(1.0f, 1.0f, 1.0f, 1.0f));

            void drawSquare2D(void);

            void drawRect2D(void);

            //------------------------------------------------------------------

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            void drawVertexData(const CVertexData *inputData,
                                const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT,
                                const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param mode
             */
            void drawArray(const CVector<Vector3f>& inputData,
                           const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            void drawArray(const CVector<Vertex2v> &inputData,
                           const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT,
                           const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            void drawArray(const CVector<Vertex3v> &inputData,
                           const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_NORMAL_BIT | ATTRIBUTE_UVS_BIT,
                           const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param attribMask
             * @param mode
             */
            void drawArray(const CVector<Vertex4v> &inputData,
                           const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_NORMAL_BIT | ATTRIBUTE_UVS_BIT | ATTRIBUTE_COLOR_BIT,
                           const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            //------------------------------------------------------------------

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            void drawArrayIndexed(const CVector<Vertex2v> &inputData,
                                  const CVector<fgGFXushort>& indices,
                                  const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            void drawArrayIndexed(const CVector<Vertex3v> &inputData,
                                  const CVector<fgGFXushort>& indices,
                                  const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_NORMAL_BIT | ATTRIBUTE_UVS_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /**
             * 
             * @param inputData
             * @param indices
             * @param attribMask
             * @param mode
             */
            void drawArrayIndexed(const CVector<Vertex4v> &inputData,
                                  const CVector<fgGFXushort>& indices,
                                  const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_NORMAL_BIT | ATTRIBUTE_UVS_BIT | ATTRIBUTE_COLOR_BIT,
                                  const PrimitiveMode mode = PrimitiveMode::TRIANGLES);

            /* ***************** 2 component vertex struct - pos, uv **********/
    #if 0
            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex2v> &outputData,
                              float sizex, float sizey,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex2v> &outputData,
                              const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex2v> &outputData,
                              const Vector2f &relPos, const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);
    #endif
            /* ***************** 3 component vertex struct - pos, norm, uv ************ */

            /*
             *
             */
            void appendRect2D(CVertexData *outputData,
                              float sizex, float sizey,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const Color4f &color,
                              const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(CVertexData *outputData,
                              const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const Color4f &color,
                              const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(CVertexData *outputData,
                              const Vector2f &relPos, const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const Color4f &color,
                              const PrimitiveMode mode = PrimitiveMode::TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /* ***************** 4 component vertex struct - pos, norm, uv ************ */
    #if 0
            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex4v> &outputData,
                              float sizex, float sizey,
                              const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex4v> &outputData,
                              const fg::Vector2f &size,
                              const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);

            /*
             *
             */
            void appendRect2D(fg::CVector<Vertex4v> &outputData,
                              const fg::Vector2f &relPos, const fg::Vector2f &size,
                              const fg::Vector2f &uv1, const fg::Vector2f &uv2,
                              const PrimitiveMode mode = FG_GFX_TRIANGLES,
                              const fgBool rewind = FG_FALSE);
    #endif
        }
    }
}

    #undef FG_INC_GFX_PRIMITIVES_BLOCK
#endif /* FG_INC_GFX_PRIMITIVES */
