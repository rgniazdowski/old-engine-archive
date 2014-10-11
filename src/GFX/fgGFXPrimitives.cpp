/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXPrimitives.h"

/*
 *
 */
const fgVertex3 c_stripCube1x1[] = {
         // Vertex data for face 0
         {fgVector3f(-0.5f, -0.5f,  0.5f)}, //  v0
         {fgVector3f( 0.5f, -0.5f,  0.5f)}, //  v1
         {fgVector3f(-0.5f,  0.5f,  0.5f)}, //  v2
         {fgVector3f( 0.5f,  0.5f,  0.5f)}, //  v3

         // Vertex data for face 1
         {fgVector3f( 0.5f, -0.5f,  0.5f)}, //  v4
         {fgVector3f( 0.5f, -0.5f, -0.5f)}, //  v5
         {fgVector3f( 0.5f,  0.5f,  0.5f)}, //  v6
         {fgVector3f( 0.5f,  0.5f, -0.5f)}, //  v7

         // Vertex data for face 2
         {fgVector3f( 0.5f, -0.5f, -0.5f)}, //  v8
         {fgVector3f(-0.5f, -0.5f, -0.5f)}, //  v9
         {fgVector3f( 0.5f,  0.5f, -0.5f)}, // v10
         {fgVector3f(-0.5f,  0.5f, -0.5f)}, // v11

         // Vertex data for face 3
         {fgVector3f(-0.5f, -0.5f, -0.5f)}, // v12
         {fgVector3f(-0.5f, -0.5f,  0.5f)}, // v13
         {fgVector3f(-0.5f,  0.5f, -0.5f)}, // v14
         {fgVector3f(-0.5f,  0.5f,  0.5f)}, // v15

         // Vertex data for face 4
         {fgVector3f(-0.5f, -0.5f, -0.5f)}, // v16
         {fgVector3f( 0.5f, -0.5f, -0.5f)}, // v17
         {fgVector3f(-0.5f, -0.5f,  0.5f)}, // v18
         {fgVector3f( 0.5f, -0.5f,  0.5f)}, // v19

         // Vertex data for face 5
         {fgVector3f(-0.5f,  0.5f,  0.5f)}, // v20
         {fgVector3f( 0.5f,  0.5f,  0.5f)}, // v21
         {fgVector3f(-0.5f,  0.5f, -0.5f)}, // v22
         {fgVector3f( 0.5f,  0.5f, -0.5f)}  // v23
     };

/*
 *
 */
const fgGFXuint c_stripCube1x1Idx[] = {
          0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
          4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
          8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
         12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
         16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
         20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
     };

/*
 *
 */
static const GLfloat c_trisCube1x1[] = { 
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		 0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,

		 0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f,
		 0.5f, 0.5f,-0.5f,
		 0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,

		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		 0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		 0.5f,-0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,
		 0.5f,-0.5f,-0.5f,
		 0.5f, 0.5f,-0.5f,

		 0.5f,-0.5f,-0.5f,
		 0.5f, 0.5f, 0.5f,
		 0.5f,-0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,
		 0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,

		 0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		 0.5f,-0.5f, 0.5f
	};

/*
 * Square is size of 1.0fx1.0f, point 0.0 is centered (0.0 is center mass),
 * triangle strip format, no index, CCW
 */
const fgVertex3 c_stripSquare1x1[] = {
	{fgVector3f(-0.5f, 0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(0.f, 1.f)},
	{fgVector3f(-0.5f,-0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(0.f, 0.f)},
	{fgVector3f( 0.5f, 0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f, 1.f)},
	{fgVector3f( 0.5f,-0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f, 0.f)},
};

/*
 * Rectangle, size 1.0fx1.0f, made of 3 quads (3x1) in triangle strip, (6 triangles)
 * mass centered, CCW, texture coords, no normals, no index
 */
const fgVertex3 c_stripRect3x1[] = {
	{fgVector3f(-0.5f,	 0.5f,		0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(0.f, 1.f)},
	{fgVector3f(-0.5f,	-0.5f,		0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(0.f, 0.f)},
	{fgVector3f(-0.5f/3, 0.5f,		0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f/3, 1.f)},
	{fgVector3f(-0.5f/3,-0.5f,		0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f/3, 0.f)},

	{fgVector3f( 0.5f/3, 0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(2.f/3, 1.f)},
	{fgVector3f( 0.5f/3,-0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(2.f/3, 0.f)},

	{fgVector3f( 0.5f, 0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f, 1.f)},
	{fgVector3f( 0.5f,-0.5f, 0.f), fgVector3f(0.f,0.f,0.f), fgVector2f(1.f, 0.f)},
};

#include "GFX/Shaders/fgGFXShaderDefs.h"
#include "GFX/Shaders/fgGFXShaderProgram.h"

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fgVector<fgVertex2> &inputData,
								  const unsigned int attribMask,
								  const fgGfxPrimitiveMode mode)
{
	if(inputData.empty() || !attribMask)
		return;
	fgGfxPlatform::context()->diffVertexAttribArrayMask(attribMask);

	uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
	if(attribMask & FG_GFX_POSITION_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION, 
			3, 
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex2),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector3f); 
	if(attribMask & FG_GFX_UVS_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION, 
			2,
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex2),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	glDrawArrays((GLenum)mode, 0, inputData.size());
	fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fgVector<fgVertex3> &inputData,
								  const unsigned int attribMask,
								  const fgGfxPrimitiveMode mode)
{
	if(inputData.empty() || !attribMask)
		return;
	// Need to optimize this
	// VertexAttrib arrays locations do not need to be enabled/disabled
	// every time, this may cause some slow down - find a way to remember the 
	// state of the active attribute arrays...
	uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
	fgGfxPlatform::context()->diffVertexAttribArrayMask(attribMask);
	if(attribMask & FG_GFX_POSITION_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION, 
			3,
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex3),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector3f); 
	if(attribMask & FG_GFX_NORMAL_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION, 
			3,
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex3),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector3f); 
	if(attribMask & FG_GFX_UVS_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION, 
			2,
			GL_FLOAT,
			FG_GFX_FALSE, 
			sizeof(fgVertex3),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	glDrawArrays((GLenum)mode, 0, inputData.size());
	fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::drawArray2D(const fgVector<fgVertex4> &inputData,
								  const unsigned int attribMask,
								  const fgGfxPrimitiveMode mode)
{
	if(inputData.empty() || !attribMask)
		return;

	uintptr_t offset = (uintptr_t)((unsigned int*)&inputData.front());
	fgGfxPlatform::context()->diffVertexAttribArrayMask(attribMask);
	if(attribMask & FG_GFX_POSITION_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
			3, 
			GL_FLOAT, 
			FG_GFX_FALSE,
			sizeof(fgVertex4),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector3f); 
	if(attribMask & FG_GFX_NORMAL_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
			3, 
			GL_FLOAT, 
			FG_GFX_FALSE, 
			sizeof(fgVertex4),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector3f); 
	if(attribMask & FG_GFX_UVS_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
			2,
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex4),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	offset += sizeof(fgVector2f); 
	if(attribMask & FG_GFX_COLOR_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION, 
			4,
			GL_FLOAT,
			FG_GFX_FALSE,
			sizeof(fgVertex4),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	glDrawArrays((GLenum)mode, 0, inputData.size());
	fgGLError("glDrawArrays");
}

void fgGfxPrimitives::drawArray2D(const fgVertexDataBase *inputData,
								  const unsigned int attribMask,
								  const fgGfxPrimitiveMode mode)
{
	if(!inputData)
		return;
	if(inputData->empty() || !attribMask)
		return;
	unsigned int andMask = (attribMask & inputData->attribMask());
	fgGfxPlatform::context()->diffVertexAttribArrayMask(andMask);
	uintptr_t offset = (uintptr_t)((unsigned int*)inputData->front());
	if(andMask & FG_GFX_POSITION_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION,
			3, 
			GL_FLOAT, 
			FG_GFX_FALSE,
			inputData->stride(),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	if(inputData->attribMask() & FG_GFX_POSITION_BIT)
		offset += sizeof(fgVector3f); 
	if(andMask & FG_GFX_NORMAL_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,
			3, 
			GL_FLOAT, 
			FG_GFX_FALSE, 
			inputData->stride(),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	if(inputData->attribMask() & FG_GFX_UVS_BIT)
		offset += sizeof(fgVector3f); 
	if(andMask & FG_GFX_UVS_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
			2,
			GL_FLOAT,
			FG_GFX_FALSE,
			inputData->stride(),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	if(inputData->attribMask() & FG_GFX_COLOR_BIT)
		offset += sizeof(fgVector2f); 
	if(andMask & FG_GFX_COLOR_BIT) {
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_COLOR_LOCATION, 
			4, 
			GL_FLOAT, 
			FG_GFX_FALSE, 
			inputData->stride(),
			reinterpret_cast<fgGFXvoid*>(offset));
	}
	glDrawArrays((fgGFXenum)mode, 0, inputData->size());
	fgGLError("glDrawArrays");

}

/*
 *
 */
void fgGfxPrimitives::drawRect2D(void)
{
	fgGfxPlatform::context()->diffVertexAttribArrayMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
	fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION, 
		3,
		GL_FLOAT,
		FG_GFX_FALSE,
		sizeof(fgVertex3),
		(fgGFXvoid *)c_stripRect3x1);
        
	uintptr_t offset = (uintptr_t)((unsigned int*)&c_stripRect3x1[0]) + sizeof(fgGFXfloat) * 6;
	fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,
		2,
		GL_FLOAT,
		FG_GFX_FALSE,
		sizeof(fgVertex3),
		(fgGFXvoid*)offset);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(c_stripRect3x1)/sizeof(fgVertex3)); 
	fgGLError("glDrawArrays");
}

/*
 *
 */
void fgGfxPrimitives::appendRect2D(fgVertexDataBase *outputData,
								   const fgVec2f &size,
								   const fgVec2f &uv1, 
								   const fgVec2f &uv2,
								   const fgColor4f &color,
								   const fgGfxPrimitiveMode mode,
								   const fgBool rewind)
{
	appendRect2D(outputData, fgVec2f(0.0f, 0.0f), size, uv1, uv2, color, mode, rewind);
}

/*
 *
 */
void fgGfxPrimitives::appendRect2D(fgVertexDataBase *outputData,
								   float sizex, 
								   float sizey, 
								   const fgVec2f &uv1,
								   const fgVec2f &uv2,
								   const fgColor4f &color,
								   const fgGfxPrimitiveMode mode,
								   const fgBool rewind)
{
	appendRect2D(outputData, fgVec2f(0.0f, 0.0f), fgVec2f(sizex, sizey), uv1, uv2, color, mode, rewind);
}

/*
 * This goes from left to right, this is not optimal in any way 
 * (does not use indexing, quad is specified via 6 vertices - two separate triangles)
 * Currently specifing UVs for Triangle strip is not obvious (it's tricky, needs changing)
 */
void fgGfxPrimitives::appendRect2D(fgVertexDataBase *outputData,
								   const fgVec2f &relPos,
								   const fgVec2f &size,
								   const fgVec2f &uv1,
								   const fgVec2f &uv2,
								   const fgColor4f &color,
								   const fgGfxPrimitiveMode mode, 
								   const fgBool rewind)
{
	if(!outputData)
		return;
	float x1=0.0f,y1=0.0f;
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
	x1+=relPos.x; y1+=relPos.y;
	fgVector3f norm = fgVector3f(1.0f, 1.0f, 1.0f);
	if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP || mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLES) {
		
		fgVertex2 v1, v2;
		v1.position = fgVec3f(x1, y1, 0.0f);
		v1.uv = fgVec2f(uv1.x, 1-uv1.y);
		v2.position = fgVec3f(x1, y1+size.y, 0.0f);
		v2.uv = fgVec2f(uv1.x, 1-uv2.y);
		if(mode == fgGfxPrimitiveMode::FG_GFX_TRIANGLE_STRIP && outputData->empty()) {
			fgVertex3 v3, v4;
			v3.position = fgVec3f(x1+size.x, y1, 0.0f);
			v3.uv = fgVec2f(uv2.x, 1-uv1.y);

			v4.position = fgVec3f(x1+size.x, y1+size.y, 0.0f);
			v4.uv = fgVec2f(uv2.x, 1-uv2.y);
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
			fgVertex2 v3, v4;
			fgVertex2 v5, v6;
			v3.position = fgVec3f(x1+size.x, y1, 0.0f);
			v3.uv = fgVec2f(uv2.x, 1-uv1.y);

			v4.position = fgVec3f(x1, y1+size.y, 0.0f);
			v4.uv = fgVec2f(uv1.x, 1-uv2.y);

			v5.position = fgVec3f(x1+size.x, y1+size.y, 0.0f);
			v5.uv = fgVec2f(uv2.x, 1-uv2.y);

			v6.position = fgVec3f(x1+size.x, y1, 0.0f);
			v6.uv = fgVec2f(uv2.x, 1-uv1.y);
			
			outputData->append(v3.position, norm, v3.uv, color);
			outputData->append(v4.position, norm, v4.uv, color);
			outputData->append(v5.position, norm, v5.uv, color);
			outputData->append(v6.position, norm, v6.uv, color);
		} 
	} 
}
