/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXPrimitives.h"

fgVector4f colorWhite(1.0f, 1.0f, 1.0f, 1.0f);

/*
 *
 */
const fgVertex4v c_stripSkyBoxOptimized[] = {
                                             // Vertex data for face 0 // Front?
    {fgVector3f(-0.5f, -0.5f, 0.5f), fgVector3f(0.0f, 0.0f, -1.0f), fgVector2f(2.0f / 3.0f, 1.0f - 0.0f), colorWhite}, //  v0
    {fgVector3f(0.5f, -0.5f, 0.5f), fgVector3f(0.0f, 0.0f, -1.0f), fgVector2f(1.0f, 1.0f - 0.0f), colorWhite}, //  v1
    {fgVector3f(-0.5f, 0.5f, 0.5f), fgVector3f(0.0f, 0.0f, -1.0f), fgVector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v2
    {fgVector3f(0.5f, 0.5f, 0.5f), fgVector3f(0.0f, 0.0f, -1.0f), fgVector2f(1.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v3

                                             // Vertex data for face 1 // Right?
    {fgVector3f(0.5f, -0.5f, 0.5f), fgVector3f(-1.0f, 0.0f, 0.0f), fgVector2f(1.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v4
    {fgVector3f(0.5f, -0.5f, -0.5f), fgVector3f(-1.0f, 0.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v5
    {fgVector3f(0.5f, 0.5f, 0.5f), fgVector3f(-1.0f, 0.0f, 0.0f), fgVector2f(1.0f, 1.0f - 2.0f / 3.0f), colorWhite}, //  v6
    {fgVector3f(0.5f, 0.5f, -0.5f), fgVector3f(-1.0f, 0.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, //  v7

                                             // Vertex data for face 2 // Back?
    {fgVector3f(0.5f, -0.5f, -0.5f), fgVector3f(0.0f, 0.0f, 1.0f), fgVector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v8
    {fgVector3f(-0.5f, -0.5f, -0.5f), fgVector3f(0.0f, 0.0f, 1.0f), fgVector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v9
    {fgVector3f(0.5f, 0.5f, -0.5f), fgVector3f(0.0f, 0.0f, 1.0f), fgVector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v10
    {fgVector3f(-0.5f, 0.5f, -0.5f), fgVector3f(0.0f, 0.0f, 1.0f), fgVector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v11

                                             // Vertex data for face 3 // Left?
    {fgVector3f(-0.5f, -0.5f, -0.5f), fgVector3f(1.0f, 0.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v12
    {fgVector3f(-0.5f, -0.5f, 0.5f), fgVector3f(1.0f, 0.0f, 0.0f), fgVector2f(0.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v13
    {fgVector3f(-0.5f, 0.5f, -0.5f), fgVector3f(1.0f, 0.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v14
    {fgVector3f(-0.5f, 0.5f, 0.5f), fgVector3f(1.0f, 0.0f, 0.0f), fgVector2f(0.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v15

                                             // Vertex data for face 4 // Bottom?
    {fgVector3f(-0.5f, -0.5f, -0.5f), fgVector3f(0.0f, 1.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v16
    {fgVector3f(0.5f, -0.5f, -0.5f), fgVector3f(0.0f, 1.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v17
    {fgVector3f(-0.5f, -0.5f, 0.5f), fgVector3f(0.0f, 1.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 0.0f), colorWhite}, // v18
    {fgVector3f(0.5f, -0.5f, 0.5f), fgVector3f(0.0f, 1.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 0.0f), colorWhite}, // v19

                                             // Vertex data for face 5 // Top?
    {fgVector3f(-0.5f, 0.5f, 0.5f), fgVector3f(0.0f, -1.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 1.0f), colorWhite}, // v20 
    {fgVector3f(0.5f, 0.5f, 0.5f), fgVector3f(0.0f, -1.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 1.0f), colorWhite}, // v21 
    {fgVector3f(-0.5f, 0.5f, -0.5f), fgVector3f(0.0f, -1.0f, 0.0f), fgVector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v22 
    {fgVector3f(0.5f, 0.5f, -0.5f), fgVector3f(0.0f, -1.0f, 0.0f), fgVector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite} // v23 
};

/*
 *
 */
const fgVertex3v c_stripCube1x1[] = {
                                     // Vertex data for face 0
    {fgVector3f(-0.5f, -0.5f, 0.5f)}, //  v0
    {fgVector3f(0.5f, -0.5f, 0.5f)}, //  v1
    {fgVector3f(-0.5f, 0.5f, 0.5f)}, //  v2
    {fgVector3f(0.5f, 0.5f, 0.5f)}, //  v3

                                     // Vertex data for face 1
    {fgVector3f(0.5f, -0.5f, 0.5f)}, //  v4
    {fgVector3f(0.5f, -0.5f, -0.5f)}, //  v5
    {fgVector3f(0.5f, 0.5f, 0.5f)}, //  v6
    {fgVector3f(0.5f, 0.5f, -0.5f)}, //  v7

                                     // Vertex data for face 2
    {fgVector3f(0.5f, -0.5f, -0.5f)}, //  v8
    {fgVector3f(-0.5f, -0.5f, -0.5f)}, //  v9
    {fgVector3f(0.5f, 0.5f, -0.5f)}, // v10
    {fgVector3f(-0.5f, 0.5f, -0.5f)}, // v11

                                     // Vertex data for face 3
    {fgVector3f(-0.5f, -0.5f, -0.5f)}, // v12
    {fgVector3f(-0.5f, -0.5f, 0.5f)}, // v13
    {fgVector3f(-0.5f, 0.5f, -0.5f)}, // v14
    {fgVector3f(-0.5f, 0.5f, 0.5f)}, // v15

                                     // Vertex data for face 4
    {fgVector3f(-0.5f, -0.5f, -0.5f)}, // v16
    {fgVector3f(0.5f, -0.5f, -0.5f)}, // v17
    {fgVector3f(-0.5f, -0.5f, 0.5f)}, // v18
    {fgVector3f(0.5f, -0.5f, 0.5f)}, // v19

                                     // Vertex data for face 5
    {fgVector3f(-0.5f, 0.5f, 0.5f)}, // v20
    {fgVector3f(0.5f, 0.5f, 0.5f)}, // v21
    {fgVector3f(-0.5f, 0.5f, -0.5f)}, // v22
    {fgVector3f(0.5f, 0.5f, -0.5f)} // v23
};

/*
 *
 */
const fgGFXushort c_stripCube1x1Idx[] = {
                                         0, 1, 2, 3, 3, // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
                                         4, 4, 5, 6, 7, 7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
                                         8, 8, 9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
                                         12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
                                         16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
                                         20, 20, 21, 22, 23 // Face 5 - triangle strip (v20, v21, v22, v23)
};

/*
 *
 */
static const GLfloat c_trisCube1x1[] = {
                                        -0.5f, -0.5f, -0.5f,
                                        -0.5f, -0.5f, 0.5f,
                                        -0.5f, 0.5f, 0.5f,
                                        0.5f, 0.5f, -0.5f,
                                        -0.5f, -0.5f, -0.5f,
                                        -0.5f, 0.5f, -0.5f,

                                        0.5f, -0.5f, 0.5f,
                                        -0.5f, -0.5f, -0.5f,
                                        0.5f, -0.5f, -0.5f,
                                        0.5f, 0.5f, -0.5f,
                                        0.5f, -0.5f, -0.5f,
                                        -0.5f, -0.5f, -0.5f,

                                        -0.5f, -0.5f, -0.5f,
                                        -0.5f, 0.5f, 0.5f,
                                        -0.5f, 0.5f, -0.5f,
                                        0.5f, -0.5f, 0.5f,
                                        -0.5f, -0.5f, 0.5f,
                                        -0.5f, -0.5f, -0.5f,

                                        -0.5f, 0.5f, 0.5f,
                                        -0.5f, -0.5f, 0.5f,
                                        0.5f, -0.5f, 0.5f,
                                        0.5f, 0.5f, 0.5f,
                                        0.5f, -0.5f, -0.5f,
                                        0.5f, 0.5f, -0.5f,

                                        0.5f, -0.5f, -0.5f,
                                        0.5f, 0.5f, 0.5f,
                                        0.5f, -0.5f, 0.5f,
                                        0.5f, 0.5f, 0.5f,
                                        0.5f, 0.5f, -0.5f,
                                        -0.5f, 0.5f, -0.5f,

                                        0.5f, 0.5f, 0.5f,
                                        -0.5f, 0.5f, -0.5f,
                                        -0.5f, 0.5f, 0.5f,
                                        0.5f, 0.5f, 0.5f,
                                        -0.5f, 0.5f, 0.5f,
                                        0.5f, -0.5f, 0.5f
};

/*
 * Square is size of 1.0fx1.0f, point 0.0 is centered (0.0 is center mass),
 * triangle strip format, no index, CCW
 */
const fgVertex3v c_stripSquare1x1[] = {
    {fgVector3f(0.5f, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f, 0.f)},
    {fgVector3f(-0.5f, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(0.f, 0.f)},
    {fgVector3f(0.5f, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f, 1.f)},
    {fgVector3f(-0.5f, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(0.f, 1.f)}
};

/*
 * Rectangle, size 1.0fx1.0f, made of 3 quads (3x1) in triangle strip, (6 triangles)
 * mass centered, CCW, texture coords, no normals, no index
 */
const fgVertex3v c_stripRect3x1[] = {
    {fgVector3f(-0.5f, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(0.f, 1.f)},
    {fgVector3f(-0.5f, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(0.f, 0.f)},
    {fgVector3f(-0.5f / 3, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f / 3, 1.f)},
    {fgVector3f(-0.5f / 3, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f / 3, 0.f)},

    {fgVector3f(0.5f / 3, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(2.f / 3, 1.f)},
    {fgVector3f(0.5f / 3, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(2.f / 3, 0.f)},

    {fgVector3f(0.5f, 0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f, 1.f)},
    {fgVector3f(0.5f, -0.5f, 0.f), fgVector3f(0.f, 0.f, 0.f), fgVector2f(1.f, 0.f)}
};

#include "GFX/Shaders/fgGFXShaderDefs.h"
#include "GFX/Shaders/fgGFXShaderProgram.h"
#include "fgGFXAABoundingBox.h"

void fgGfxPrimitives::drawSkyBoxOptimized(void) {
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(fgVertex4v::attribMask());

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripSkyBoxOptimized[0]);
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                  3,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex4v),
                                                  reinterpret_cast<fgGFXvoid*>(offset));
    offset += sizeof (fgVector3f); // Move offset to Normals
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                                  3,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex4v),
                                                  reinterpret_cast<fgGFXvoid*>(offset));
    
    offset += sizeof (fgVector3f); // Move offset to UVS
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                  2,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex4v),
                                                  reinterpret_cast<fgGFXvoid*>(offset));
    
    offset += sizeof (fgVector2f); // Move offset to Color
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                                  4,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex4v),
                                                  reinterpret_cast<fgGFXvoid*>(offset));

    //(GLenum mode, GLsizei count, GLenum type, const void *indices)
    glDrawElements((GLenum)fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP,
                   sizeof (c_stripCube1x1Idx) / sizeof (c_stripCube1x1Idx[0]),
                   GL_UNSIGNED_SHORT,
                   c_stripCube1x1Idx);
}

void fgGfxPrimitives::drawAABBLines(const fgAABoundingBox3Df& aabb) {
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    fgVec3f center = aabb.getCenter();
    fgVec3f extent = aabb.getExtent();

    fgVec3f v[8] = {
                    fgVec3f(center.x - extent.x, center.y - extent.y, center.z + extent.z), // 1 -x, -y, +z
                    fgVec3f(center.x + extent.x, center.y - extent.y, center.z + extent.z), // 2 +x, -y, +z
                    fgVec3f(center.x + extent.x, center.y + extent.y, center.z + extent.z), // 3 +x, +y, +z
                    fgVec3f(center.x - extent.x, center.y + extent.y, center.z + extent.z), // 4 -x, +y, +z

                    fgVec3f(center.x - extent.x, center.y + extent.y, center.z - extent.z), // 5 -x, +y, -z
                    fgVec3f(center.x + extent.x, center.y + extent.y, center.z - extent.z), // 6 +x, +y, -z
                    fgVec3f(center.x + extent.x, center.y - extent.y, center.z - extent.z), // 7 +x, -y, -z
                    fgVec3f(center.x - extent.x, center.y - extent.y, center.z - extent.z) // 8 -x, -y, -z
    };
#define _id_vec(_X) v[(_X-1)]
    const fgVector3f aabbLineStripBuf[] = {
                                           // 1st face
                                           _id_vec(4), // 0
                                           _id_vec(1), // 1
                                           _id_vec(2), // 2
                                           _id_vec(4), // 3
                                           _id_vec(3), // 4
                                           _id_vec(2), // 5

                                           // 2nd face
                                           _id_vec(7), // 6
                                           _id_vec(3), // 7
                                           _id_vec(6), // 8
                                           _id_vec(7), // 9

                                           // 3rd face
                                           _id_vec(8), // 10
                                           _id_vec(6), // 11
                                           _id_vec(5), // 12
                                           _id_vec(8), // 13

                                           // 4th face
                                           _id_vec(1), // 14
                                           _id_vec(5), // 15
                                           _id_vec(4), // 16
    };
    const fgColor4f aabbColor[] = {
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),

                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),

                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),

                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),
                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f),

                                   fgColor4f(1.0f, 1.0f, 1.0f, 1.0f)

    };
#undef _id_vec
    uintptr_t offset = (uintptr_t)((unsigned int*)&aabbLineStripBuf[0]);
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                  3,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVector3f),
                                                  reinterpret_cast<fgGFXvoid*>(offset));

    offset = (uintptr_t)((unsigned int*)&aabbColor[0]);
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                                  4,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVector4f),
                                                  reinterpret_cast<fgGFXvoid*>(offset));
    glDrawArrays((GLenum)fgGfxPrimitiveMode::FG_GFX_LINE_STRIP, 0, sizeof (aabbLineStripBuf) / sizeof (aabbLineStripBuf[0]));

}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fg::CVector<fgVertex2v> &inputData,
                                  const unsigned int attribMask,
                                  const fgGfxPrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(attribMask);

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    if(attribMask & FG_GFX_POSITION_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex2v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                      2,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex2v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fg::CVector<fgVertex3v> &inputData,
                                  const unsigned int attribMask,
                                  const fgGfxPrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;
    // Need to optimize this
    // VertexAttrib arrays locations do not need to be enabled/disabled
    // every time, this may cause some slow down - find a way to remember the 
    // state of the active attribute arrays...
    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex3v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex3v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                      2,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex3v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fg::CVector<fgVertex4v> &inputData,
                                  const unsigned int attribMask,
                                  const fgGfxPrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex4v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex4v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                      2,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex4v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (fgVector2f);
    if(attribMask & FG_GFX_COLOR_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                                      4,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      sizeof (fgVertex4v),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fgVertexData *inputData,
                                  const unsigned int attribMask,
                                  const fgGfxPrimitiveMode mode) {
    if(!inputData)
        return;
    if(inputData->empty() || !attribMask)
        return;
    unsigned int andMask = (attribMask & inputData->attribMask());
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(andMask);
    uintptr_t offset = (uintptr_t)((unsigned int*)inputData->front());
    if(andMask & FG_GFX_POSITION_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      inputData->stride(),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    if(inputData->attribMask() & FG_GFX_POSITION_BIT)
        offset += sizeof (fgVector3f);
    if(andMask & FG_GFX_NORMAL_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                                      3,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      inputData->stride(),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    if(inputData->attribMask() & FG_GFX_UVS_BIT)
        offset += sizeof (fgVector3f);
    if(andMask & FG_GFX_UVS_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                      2,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      inputData->stride(),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    if(inputData->attribMask() & FG_GFX_COLOR_BIT)
        offset += sizeof (fgVector2f);
    if(andMask & FG_GFX_COLOR_BIT) {
        fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                                      4,
                                                      FG_GFX_FLOAT,
                                                      FG_GFX_FALSE,
                                                      inputData->stride(),
                                                      reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((fgGFXenum)mode, 0, inputData->size());
    fgGLError("glDrawArrays");

}

void fgGfxPrimitives::drawSquare2D(void) {
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                  3,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex3v),
                                                  (fgGFXvoid *)c_stripSquare1x1);

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripSquare1x1[0]) + sizeof (fgVector3f) * 2;
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                  2,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex3v),
                                                  (fgGFXvoid*)offset);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof (c_stripSquare1x1) / sizeof (fgVertex3v));
}

/*
 *
 */
void fgGfxPrimitives::drawRect2D(void) {
    fg::gfx::CPlatform::context()->diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                                  3,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex3v),
                                                  (fgGFXvoid *)c_stripRect3x1);

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripRect3x1[0]) + sizeof (fgGFXfloat) * 6;
    fg::gfx::CPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                                  2,
                                                  FG_GFX_FLOAT,
                                                  FG_GFX_FALSE,
                                                  sizeof (fgVertex3v),
                                                  (fgGFXvoid*)offset);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof (c_stripRect3x1) / sizeof (fgVertex3v));
    fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::appendRect2D(fgVertexData *outputData,
                                   const fgVec2f &size,
                                   const fgVec2f &uv1,
                                   const fgVec2f &uv2,
                                   const fgColor4f &color,
                                   const fgGfxPrimitiveMode mode,
                                   const fgBool rewind) {
    appendRect2D(outputData, fgVec2f(0.0f, 0.0f), size, uv1, uv2, color, mode, rewind);
}

/*
 *
 */
void fgGfxPrimitives::appendRect2D(fgVertexData *outputData,
                                   float sizex,
                                   float sizey,
                                   const fgVec2f &uv1,
                                   const fgVec2f &uv2,
                                   const fgColor4f &color,
                                   const fgGfxPrimitiveMode mode,
                                   const fgBool rewind) {
    appendRect2D(outputData, fgVec2f(0.0f, 0.0f), fgVec2f(sizex, sizey), uv1, uv2, color, mode, rewind);
}

/*
 * This goes from left to right, this is not optimal in any way 
 * (does not use indexing, quad is specified via 6 vertices - two separate triangles)
 * Currently specifing UVs for Triangle strip is not obvious (it's tricky, needs changing)
 */
void fgGfxPrimitives::appendRect2D(fgVertexData *outputData,
                                   const fgVec2f &relPos,
                                   const fgVec2f &size,
                                   const fgVec2f &uv1,
                                   const fgVec2f &uv2,
                                   const fgColor4f &color,
                                   const fgGfxPrimitiveMode mode,
                                   const fgBool rewind) {
    if(!outputData)
        return;
    float x1 = 0.0f, y1 = 0.0f;
    int n = outputData->size();

    /*if(!outputData.empty()) {
            if(rewind) {
                    x1 = outputData[1].position[0];
                    if(mode == FG_GFX_TRIANGLES)
                            y1 = outputData[n-2].position[1];
                    else if(mode == FG_GFX_TRIANGLE_STRIP)
                            y1 = outputData[n-1].position[1];
            } else {
                    if(mode == FG_GFX_TRIANGLE_STRIP) {
                            x1 = outputData[n-2].position[0];
                            y1 = outputData[n-2].position[1];
                    } else {
                            x1 = outputData[n-1].position[0];
                            y1 = outputData[n-1].position[1];
                    }
            }
    }*/
    x1 += relPos.x;
    y1 += relPos.y;
    fgVector3f norm = fgVector3f(1.0f, 1.0f, 1.0f);
    if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP || mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLES) {

        fgVertex2v v1, v2;
        v1.position = fgVec3f(x1, y1, 0.0f);
        v1.uv = fgVec2f(uv1.x, 1 - uv1.y);
        v2.position = fgVec3f(x1, y1 + size.y, 0.0f);
        v2.uv = fgVec2f(uv1.x, 1 - uv2.y);
        if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP && outputData->empty()) {
            fgVertex3v v3, v4;
            v3.position = fgVec3f(x1 + size.x, y1, 0.0f);
            v3.uv = fgVec2f(uv2.x, 1 - uv1.y);

            v4.position = fgVec3f(x1 + size.x, y1 + size.y, 0.0f);
            v4.uv = fgVec2f(uv2.x, 1 - uv2.y);
            outputData->append(v1.position, norm, v1.uv, color);
            outputData->append(v2.position, norm, v2.uv, color);
            outputData->append(v3.position, norm, v3.uv, color);
            outputData->append(v4.position, norm, v4.uv, color);
        } else {
            if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP) {
                v1.position[0] += size.x;
                v2.position[0] += size.x;
            }
            outputData->append(v1.position, norm, v1.uv, color);
            outputData->append(v2.position, norm, v2.uv, color);
        }


        if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLES) {
            fgVertex2v v3, v4;
            fgVertex2v v5, v6;
            v3.position = fgVec3f(x1 + size.x, y1, 0.0f);
            v3.uv = fgVec2f(uv2.x, 1 - uv1.y);

            v4.position = fgVec3f(x1, y1 + size.y, 0.0f);
            v4.uv = fgVec2f(uv1.x, 1 - uv2.y);

            v5.position = fgVec3f(x1 + size.x, y1 + size.y, 0.0f);
            v5.uv = fgVec2f(uv2.x, 1 - uv2.y);

            v6.position = fgVec3f(x1 + size.x, y1, 0.0f);
            v6.uv = fgVec2f(uv2.x, 1 - uv1.y);

            outputData->append(v3.position, norm, v3.uv, color);
            outputData->append(v4.position, norm, v4.uv, color);
            outputData->append(v5.position, norm, v5.uv, color);
            outputData->append(v6.position, norm, v6.uv, color);
        }
    }
}
