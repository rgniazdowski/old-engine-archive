/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxPrimitives.h"
#include "GFX/Shaders/fgGfxShaderDefs.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "fgGfxAABoundingBox.h"
#include "GFX/fgGfxVertexData.h"
#include "fgGfxModelTypes.h"
#include "fgGfxDrawCall.h"

using namespace fg;

const fgColor4f colorWhite = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);

/*
 *
 */
const gfx::Vertex4v c_stripSkyBoxOptimized[] = {
                                                // Vertex data for face 0 // Front?
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(2.0f / 3.0f, 1.0f - 0.0f), colorWhite}, //  v0
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f - 0.0f), colorWhite}, //  v1
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v2
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v3

                                                // Vertex data for face 1 // Right?
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v4
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v5
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f - 2.0f / 3.0f), colorWhite}, //  v6
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, //  v7

                                                // Vertex data for face 2 // Back?
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v8
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, //  v9
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v10
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v11

                                                // Vertex data for face 3 // Left?
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v12
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v13
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v14
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v15

                                                // Vertex data for face 4 // Bottom?
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v16
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 1.0f / 3.0f), colorWhite}, // v17
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 0.0f), colorWhite}, // v18
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 0.0f), colorWhite}, // v19

                                                // Vertex data for face 5 // Top?
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 1.0f), colorWhite}, // v20 
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 1.0f), colorWhite}, // v21 
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite}, // v22 
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(2.0f / 3.0f, 1.0f - 2.0f / 3.0f), colorWhite} // v23 
};

/*
 *
 */
#if 0
const gfx::Vertex3v c_stripCube1x1[] = {
                                        // Vertex data for face 0
    {Vector3f(-0.5f, -0.5f, 0.5f)}, //  v0
    {Vector3f(0.5f, -0.5f, 0.5f)}, //  v1
    {Vector3f(-0.5f, 0.5f, 0.5f)}, //  v2
    {Vector3f(0.5f, 0.5f, 0.5f)}, //  v3

                                        // Vertex data for face 1
    {Vector3f(0.5f, -0.5f, 0.5f)}, //  v4
    {Vector3f(0.5f, -0.5f, -0.5f)}, //  v5
    {Vector3f(0.5f, 0.5f, 0.5f)}, //  v6
    {Vector3f(0.5f, 0.5f, -0.5f)}, //  v7

                                        // Vertex data for face 2
    {Vector3f(0.5f, -0.5f, -0.5f)}, //  v8
    {Vector3f(-0.5f, -0.5f, -0.5f)}, //  v9
    {Vector3f(0.5f, 0.5f, -0.5f)}, // v10
    {Vector3f(-0.5f, 0.5f, -0.5f)}, // v11

                                        // Vertex data for face 3
    {Vector3f(-0.5f, -0.5f, -0.5f)}, // v12
    {Vector3f(-0.5f, -0.5f, 0.5f)}, // v13
    {Vector3f(-0.5f, 0.5f, -0.5f)}, // v14
    {Vector3f(-0.5f, 0.5f, 0.5f)}, // v15

                                        // Vertex data for face 4
    {Vector3f(-0.5f, -0.5f, -0.5f)}, // v16
    {Vector3f(0.5f, -0.5f, -0.5f)}, // v17
    {Vector3f(-0.5f, -0.5f, 0.5f)}, // v18
    {Vector3f(0.5f, -0.5f, 0.5f)}, // v19

                                        // Vertex data for face 5
    {Vector3f(-0.5f, 0.5f, 0.5f)}, // v20
    {Vector3f(0.5f, 0.5f, 0.5f)}, // v21
    {Vector3f(-0.5f, 0.5f, -0.5f)}, // v22
    {Vector3f(0.5f, 0.5f, -0.5f)} // v23
};
#endif

const gfx::Vertex3v c_stripCube1x1[] = {
                                        // Vertex data for face 0 // Front?
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 1.0f)}, //  v0
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f)}, //  v1
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0, 0.0f)}, //  v2
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 0.0f)}, //  v3

                                        // Vertex data for face 1 // Right?
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f)}, //  v4
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f)}, //  v5
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f)}, //  v6
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f)}, //  v7

                                        // Vertex data for face 2 // Back?
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f)}, //  v8
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f)}, //  v9
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f)}, // v10
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f)}, // v11

                                        // Vertex data for face 3 // Left?
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f)}, // v12
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f)}, // v13
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f)}, // v14
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f)}, // v15

                                        // Vertex data for face 4 // Bottom?
    {Vector3f(-0.5f, -0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f)}, // v16
    {Vector3f(0.5f, -0.5f, -0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 1.0f)}, // v17
    {Vector3f(-0.5f, -0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f)}, // v18
    {Vector3f(0.5f, -0.5f, 0.5f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f)}, // v19

                                        // Vertex data for face 5 // Top?
    {Vector3f(-0.5f, 0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 0.0f)}, // v20 
    {Vector3f(0.5f, 0.5f, 0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 0.0f)}, // v21 
    {Vector3f(-0.5f, 0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)}, // v22 
    {Vector3f(0.5f, 0.5f, -0.5f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f)} // v23 
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
const gfx::Vertex3v c_stripSquare1x1[] = {
    {Vector3f(0.5f, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f, 0.f)},
    {Vector3f(-0.5f, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(0.f, 0.f)},
    {Vector3f(0.5f, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f, 1.f)},
    {Vector3f(-0.5f, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(0.f, 1.f)}
};

/*
 * Rectangle, size 1.0fx1.0f, made of 3 quads (3x1) in triangle strip, (6 triangles)
 * mass centered, CCW, texture coords, no normals, no index
 */
const gfx::Vertex3v c_stripRect3x1[] = {
    {Vector3f(-0.5f, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(0.f, 1.f)},
    {Vector3f(-0.5f, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(0.f, 0.f)},
    {Vector3f(-0.5f / 3, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f / 3, 1.f)},
    {Vector3f(-0.5f / 3, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f / 3, 0.f)},

    {Vector3f(0.5f / 3, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(2.f / 3, 1.f)},
    {Vector3f(0.5f / 3, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(2.f / 3, 0.f)},

    {Vector3f(0.5f, 0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f, 1.f)},
    {Vector3f(0.5f, -0.5f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector2f(1.f, 0.f)}
};

void gfx::CPrimitives::drawSkyBoxOptimized(void) {
    context::diffVertexAttribArrayMask(Vertex4v::attribMask());

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripSkyBoxOptimized[0]);
    context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                 3,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex4v),
                                 reinterpret_cast<fgGFXvoid*>(offset));
    offset += sizeof (Vector3f); // Move offset to Normals
    context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                 3,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex4v),
                                 reinterpret_cast<fgGFXvoid*>(offset));

    offset += sizeof (Vector3f); // Move offset to UVS
    context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                 2,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex4v),
                                 reinterpret_cast<fgGFXvoid*>(offset));

    offset += sizeof (Vector2f); // Move offset to Color
    context::vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                 4,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex4v),
                                 reinterpret_cast<fgGFXvoid*>(offset));

    //(GLenum mode, GLsizei count, GLenum type, const void *indices)
    glDrawElements((GLenum)PrimitiveMode::TRIANGLE_STRIP,
                   sizeof (c_stripCube1x1Idx) / sizeof (c_stripCube1x1Idx[0]),
                   GL_UNSIGNED_SHORT,
                   c_stripCube1x1Idx);
}

void gfx::CPrimitives::createSphereMesh(fg::gfx::SMeshBase *mesh,
                                        unsigned int rings,
                                        unsigned int sectors,
                                        float radius) {
    if(!mesh) {
        return;
    }
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    mesh->clear();
    mesh->reserve(rings * sectors);
    for(unsigned int r = 0; r < rings; ++r) {
        for(unsigned int s = 0; s < sectors; ++s) {
            float const y = math::sin(-M_PI_2 + M_PI * r * R);
            float const x = math::cos(2 * M_PI * s * S) * math::sin(M_PI * r * R);
            float const z = math::sin(2 * M_PI * s * S) * math::sin(M_PI * r * R);

            mesh->append(Vector3f(x * radius, y * radius, z * radius),
                         Vector2f(s*S, r * R));
            //texcoords.push_back(vec2(s*S, r * R));
            //vertices.push_back();
            //push_indices(indices, sectors, r, s);
            if(r < rings - 1 && s < sectors - 1) {
                int curRow = r * sectors;
                int nextRow = (r + 1) * sectors;

                mesh->appendIndice(curRow + s);
                mesh->appendIndice(nextRow + s);
                mesh->appendIndice(nextRow + (s + 1));

                mesh->appendIndice(curRow + s);
                mesh->appendIndice(nextRow + (s + 1));
                mesh->appendIndice(curRow + (s + 1));
            }
        }
    }
    mesh->primMode = PrimitiveMode::TRIANGLES;
}

void gfx::CPrimitives::createCubeMesh(fg::gfx::SMeshBase *mesh,
                                      float scale) {
    if(!mesh) {
        return;
    }
    if(scale < 0.0f) {
        scale = math::abs(scale);
    }
    if(scale <= FG_EPSILON) {
        scale = 1.0f;
    }

    mesh->clear();
    int n = sizeof (c_stripCube1x1) / sizeof (c_stripCube1x1[0]);
    mesh->reserve(n);
    for(int i = 0; i < n; i++) {
        mesh->append(c_stripCube1x1[i].position*scale,
                     c_stripCube1x1[i].normal,
                     c_stripCube1x1[i].uv);
    }
    n = sizeof (c_stripCube1x1Idx) / sizeof (c_stripCube1x1Idx[0]);
    for(int i = 0; i < n; i++) {
        mesh->appendIndice(c_stripCube1x1Idx[i]);
    }
    mesh->primMode = PrimitiveMode::TRIANGLE_STRIP;
}

/* 
 * Osmioscian foremny (inaczej oktaedr) - octahedron: rings 3 | sectors 5 ? 
 */
void gfx::CPrimitives::drawAABBLines(const AABoundingBox3Df& aabb, const fgColor4f& color) {
    context::diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT);

    const Vec3f center = aabb.getCenter();
    const Vec3f extent = aabb.getExtent();

    const Vec3f v[8] = {
                        Vec3f(center.x - extent.x, center.y - extent.y, center.z + extent.z), // 1 -x, -y, +z
                        Vec3f(center.x + extent.x, center.y - extent.y, center.z + extent.z), // 2 +x, -y, +z
                        Vec3f(center.x + extent.x, center.y + extent.y, center.z + extent.z), // 3 +x, +y, +z
                        Vec3f(center.x - extent.x, center.y + extent.y, center.z + extent.z), // 4 -x, +y, +z

                        Vec3f(center.x - extent.x, center.y + extent.y, center.z - extent.z), // 5 -x, +y, -z
                        Vec3f(center.x + extent.x, center.y + extent.y, center.z - extent.z), // 6 +x, +y, -z
                        Vec3f(center.x + extent.x, center.y - extent.y, center.z - extent.z), // 7 +x, -y, -z
                        Vec3f(center.x - extent.x, center.y - extent.y, center.z - extent.z) // 8 -x, -y, -z
    };
#define _id_vec(_X) v[(_X-1)]
    const Vector3f aabbLineStripBuf[] = {
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
                                   color,
                                   color,
                                   color,
                                   color,

                                   color,
                                   color,
                                   color,
                                   color,

                                   color,
                                   color,
                                   color,
                                   color,

                                   color,
                                   color,
                                   color,
                                   color,

                                   color

    };
#undef _id_vec
    uintptr_t offset = (uintptr_t)((unsigned int*)&aabbLineStripBuf[0]);
    context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                 3,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vector3f),
                                 reinterpret_cast<fgGFXvoid*>(offset));

    offset = (uintptr_t)((unsigned int*)&aabbColor[0]);
    context::vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                 4,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vector4f),
                                 reinterpret_cast<fgGFXvoid*>(offset));
    glDrawArrays((GLenum)PrimitiveMode::LINE_STRIP, 0, sizeof (aabbLineStripBuf) / sizeof (aabbLineStripBuf[0]));

}

/**
 * 
 * @param inputData
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArray(const fg::CVector<Vertex2v> &inputData,
                                 const unsigned int attribMask,
                                 const PrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;
    context::diffVertexAttribArrayMask(attribMask);

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex2v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex2v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    GLCheckError("glDrawArrays");
}

/**
 * 
 * @param inputData
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArray(const fg::CVector<Vertex3v> &inputData,
                                 const unsigned int attribMask,
                                 const PrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;
    // Need to optimize this
    // VertexAttrib arrays locations do not need to be enabled/disabled
    // every time, this may cause some slow down - find a way to remember the 
    // state of the active attribute arrays...
    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    context::diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    GLCheckError("glDrawArrays");
}

/**
 * 
 * @param inputData
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArray(const fg::CVector<Vertex4v> &inputData,
                                 const unsigned int attribMask,
                                 const PrimitiveMode mode) {
    if(inputData.empty() || !attribMask)
        return;

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    context::diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector2f);
    if(attribMask & FG_GFX_COLOR_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                     4,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawArrays((GLenum)mode, 0, inputData.size());
    GLCheckError("glDrawArrays");
}

/**
 * 
 * @param inputData
 * @param indices
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArrayIndexed(const CVector<Vertex2v> &inputData,
                                        const CVector<fgGFXushort>& indices,
                                        const unsigned int attribMask,
                                        const PrimitiveMode mode) {

    if(inputData.empty() || !attribMask || indices.empty())
        return;
    context::diffVertexAttribArrayMask(attribMask);

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex2v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex2v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawElements((GLenum)mode, indices.size(), GL_UNSIGNED_SHORT, &indices.front());
    GLCheckError("glDrawElements");
}

/**
 * 
 * @param inputData
 * @param indices
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArrayIndexed(const CVector<Vertex3v> &inputData,
                                        const CVector<fgGFXushort>& indices,
                                        const unsigned int attribMask,
                                        const PrimitiveMode mode) {
    if(inputData.empty() || !attribMask || indices.empty())
        return;
    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    context::diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex3v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawElements((GLenum)mode, indices.size(), GL_UNSIGNED_SHORT, &indices.front());
    GLCheckError("glDrawElements");
}

/**
 * 
 * @param inputData
 * @param indices
 * @param attribMask
 * @param mode
 */
void gfx::CPrimitives::drawArrayIndexed(const CVector<Vertex4v> &inputData,
                                        const CVector<fgGFXushort>& indices,
                                        const unsigned int attribMask,
                                        const PrimitiveMode mode) {
    if(inputData.empty() || !attribMask || indices.empty())
        return;

    uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
    context::diffVertexAttribArrayMask(attribMask);
    if(attribMask & FG_GFX_POSITION_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_NORMAL_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                     3,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector3f);
    if(attribMask & FG_GFX_UVS_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                     2,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    offset += sizeof (Vector2f);
    if(attribMask & FG_GFX_COLOR_BIT) {
        context::vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                     4,
                                     FG_GFX_FLOAT,
                                     FG_GFX_FALSE,
                                     sizeof (Vertex4v),
                                     reinterpret_cast<fgGFXvoid*>(offset));
    }
    glDrawElements((GLenum)mode, indices.size(), GL_UNSIGNED_SHORT, &indices.front());
    GLCheckError("glDrawElements");
}

void gfx::CPrimitives::applyAttributeData(SAttributeData *attrData,
                                          SDrawingInfo& drawingInfo,
                                          const unsigned int attribMask) {
    if(!attrData)
        return;
    context::diffVertexAttribArrayMask(attribMask);
    if(attrData[0].isInterleaved == FG_TRUE && attrData[0].isBO) {
        context::bindBuffer(GL_ARRAY_BUFFER, attrData[0].buffer);
    } else {
        context::bindBuffer(GL_ARRAY_BUFFER, 0);
    }
    for(int i = 0; i < FG_GFX_ATTRIBUTE_COUNT; i++) {
        if(attrData[i].isEnabled) {
            if(attrData[i].isInterleaved == FG_FALSE && attrData[i].isBO) {
                context::bindBuffer(GL_ARRAY_BUFFER, attrData[i].buffer);
            }
            context::vertexAttribPointer(attrData[i].index,
                                         attrData[i].size,
                                         attrData[i].dataType,
                                         attrData[i].isNormalized,
                                         attrData[i].stride,
                                         attrData[i].offset);
        }
    }
    if(drawingInfo.buffer) {
        context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawingInfo.buffer);
    } else {
        context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

/*
 *
 */
void gfx::CPrimitives::drawVertexData(const CVertexData *inputData,
                                      const unsigned int attribMask,
                                      const PrimitiveMode mode) {
    if(!inputData)
        return;
    if(inputData->empty() || !attribMask)
        return;
    unsigned int andMask = (attribMask & inputData->attribMask());
    SAttributeData attrData[FG_GFX_ATTRIBUTE_COUNT];
    SDrawingInfo drawingInfo;
    inputData->setupAttributes(attrData);
    if(inputData->hasIndices()) {
        drawingInfo.buffer = inputData->getIndicesVBO();
        drawingInfo.indices.pointer = inputData->getIndicesPointer();
        if(!drawingInfo.buffer && !drawingInfo.indices.pointer)
            drawingInfo.count = inputData->getNumVertices();
        else
            drawingInfo.count = inputData->getNumIndices();
        // If both pointer/offset and buffer are zero
        // then it means that there is no indices array
    }
    applyAttributeData(attrData, drawingInfo, andMask);
    // attribute data array is set
    // unsigned short is mainly because of ES
    if(drawingInfo.buffer || drawingInfo.indices.pointer) {
        glDrawElements((fgGFXenum)mode, drawingInfo.count, GL_UNSIGNED_SHORT, drawingInfo.indices.offset);
    } else {
        // #FIXME
        glDrawArrays((fgGFXenum)mode, 0, drawingInfo.count);
    }
    // #FIXME
    context::bindBuffer(GL_ARRAY_BUFFER, 0);
    context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if(0) {

        context::diffVertexAttribArrayMask(andMask);
        uintptr_t offset = (uintptr_t)((unsigned int*)inputData->front());
        if(andMask & FG_GFX_POSITION_BIT) {
            context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                         3,
                                         FG_GFX_FLOAT,
                                         FG_GFX_FALSE,
                                         inputData->stride(),
                                         reinterpret_cast<fgGFXvoid*>(offset));
        }
        if(inputData->attribMask() & FG_GFX_POSITION_BIT)
            offset += sizeof (Vector3f);
        if(andMask & FG_GFX_NORMAL_BIT) {
            context::vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
                                         3,
                                         FG_GFX_FLOAT,
                                         FG_GFX_FALSE,
                                         inputData->stride(),
                                         reinterpret_cast<fgGFXvoid*>(offset));
        }
        if(inputData->attribMask() & FG_GFX_UVS_BIT)
            offset += sizeof (Vector3f);
        if(andMask & FG_GFX_UVS_BIT) {
            context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                         2,
                                         FG_GFX_FLOAT,
                                         FG_GFX_FALSE,
                                         inputData->stride(),
                                         reinterpret_cast<fgGFXvoid*>(offset));
        }
        if(inputData->attribMask() & FG_GFX_COLOR_BIT)
            offset += sizeof (Vector2f);
        if(andMask & FG_GFX_COLOR_BIT) {
            context::vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION,
                                         4,
                                         FG_GFX_FLOAT,
                                         FG_GFX_FALSE,
                                         inputData->stride(),
                                         reinterpret_cast<fgGFXvoid*>(offset));
        }
        glDrawArrays((fgGFXenum)mode, 0, inputData->size());
        GLCheckError("glDrawArrays");
    }

}

void gfx::CPrimitives::drawSquare2D(void) {
    context::diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                 3,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex3v),
                                 (fgGFXvoid *)c_stripSquare1x1);

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripSquare1x1[0]) + sizeof (Vector3f) * 2;
    context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                 2,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex3v),
                                 (fgGFXvoid*)offset);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof (c_stripSquare1x1) / sizeof (Vertex3v));
}

/*
 *
 */
void gfx::CPrimitives::drawRect2D(void) {
    context::diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    context::vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
                                 3,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex3v),
                                 (fgGFXvoid *)c_stripRect3x1);

    uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripRect3x1[0]) + sizeof (fgGFXfloat) * 6;
    context::vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
                                 2,
                                 FG_GFX_FLOAT,
                                 FG_GFX_FALSE,
                                 sizeof (Vertex3v),
                                 (fgGFXvoid*)offset);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof (c_stripRect3x1) / sizeof (Vertex3v));
    GLCheckError("glDrawArrays");
}

/*
 *
 */
void gfx::CPrimitives::appendRect2D(CVertexData *outputData,
                                    const Vec2f &size,
                                    const Vec2f &uv1,
                                    const Vec2f &uv2,
                                    const fgColor4f &color,
                                    const PrimitiveMode mode,
                                    const fgBool rewind) {
    appendRect2D(outputData, Vec2f(0.0f, 0.0f), size, uv1, uv2, color, mode, rewind);
}

/*
 *
 */
void gfx::CPrimitives::appendRect2D(CVertexData *outputData,
                                    float sizex,
                                    float sizey,
                                    const Vec2f &uv1,
                                    const Vec2f &uv2,
                                    const fgColor4f &color,
                                    const PrimitiveMode mode,
                                    const fgBool rewind) {
    appendRect2D(outputData, Vec2f(0.0f, 0.0f), Vec2f(sizex, sizey), uv1, uv2, color, mode, rewind);
}

/*
 * This goes from left to right, this is not optimal in any way 
 * (does not use indexing, quad is specified via 6 vertices - two separate triangles)
 * Currently specifing UVs for Triangle strip is not obvious (it's tricky, needs changing)
 */
void gfx::CPrimitives::appendRect2D(CVertexData *outputData,
                                    const Vec2f &relPos,
                                    const Vec2f &size,
                                    const Vec2f &uv1,
                                    const Vec2f &uv2,
                                    const fgColor4f &color,
                                    const PrimitiveMode mode,
                                    const fgBool rewind) {
    if(!outputData)
        return;
    float x1 = 0.0f, y1 = 0.0f;
    //int n = outputData->size();

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
    Vector3f norm = Vector3f(1.0f, 1.0f, 1.0f);
    if(mode == PrimitiveMode::TRIANGLE_STRIP || mode == PrimitiveMode::TRIANGLES) {

        Vertex2v v1, v2;
        v1.position = Vec3f(x1, y1, 0.0f);
        v1.uv = Vec2f(uv1.x, 1 - uv1.y);
        v2.position = Vec3f(x1, y1 + size.y, 0.0f);
        v2.uv = Vec2f(uv1.x, 1 - uv2.y);
        if(mode == PrimitiveMode::TRIANGLE_STRIP && outputData->empty()) {
            Vertex3v v3, v4;
            v3.position = Vec3f(x1 + size.x, y1, 0.0f);
            v3.uv = Vec2f(uv2.x, 1 - uv1.y);

            v4.position = Vec3f(x1 + size.x, y1 + size.y, 0.0f);
            v4.uv = Vec2f(uv2.x, 1 - uv2.y);
            outputData->append(v1.position, norm, v1.uv, color);
            outputData->append(v2.position, norm, v2.uv, color);
            outputData->append(v3.position, norm, v3.uv, color);
            outputData->append(v4.position, norm, v4.uv, color);
        } else {
            if(mode == PrimitiveMode::TRIANGLE_STRIP) {
                v1.position[0] += size.x;
                v2.position[0] += size.x;
            }
            outputData->append(v1.position, norm, v1.uv, color);
            outputData->append(v2.position, norm, v2.uv, color);
        }


        if(mode == PrimitiveMode::TRIANGLES) {
            Vertex2v v3, v4;
            Vertex2v v5, v6;
            v3.position = Vec3f(x1 + size.x, y1, 0.0f);
            v3.uv = Vec2f(uv2.x, 1 - uv1.y);

            v4.position = Vec3f(x1, y1 + size.y, 0.0f);
            v4.uv = Vec2f(uv1.x, 1 - uv2.y);

            v5.position = Vec3f(x1 + size.x, y1 + size.y, 0.0f);
            v5.uv = Vec2f(uv2.x, 1 - uv2.y);

            v6.position = Vec3f(x1 + size.x, y1, 0.0f);
            v6.uv = Vec2f(uv2.x, 1 - uv1.y);

            outputData->append(v3.position, norm, v3.uv, color);
            outputData->append(v4.position, norm, v4.uv, color);
            outputData->append(v5.position, norm, v5.uv, color);
            outputData->append(v6.position, norm, v6.uv, color);
        }
    }
}
