/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_PRIMITIVES_H_
#define _FG_GFX_PRIMITIVES_H_

#include "fgGFXStdInc.h"
#include "Math/fgMathLib.h"
#ifndef _FG_GFX_SHADER_PROGRAM_H_
#include "GFX/Shaders/fgGFXShaderProgram.h"
#endif

enum fgGfxPrimitiveMode {
	FG_GFX_TRIANGLES		=	GL_TRIANGLES,
	FG_GFX_TRIANGLE_STRIP	=	GL_TRIANGLE_STRIP,
	FG_GFX_TRIANGLE_FAN		=	GL_TRIANGLE_FAN,
	FG_GFX_LINES			=	GL_LINES,
	FG_GFX_LINE_LOOP		=	GL_LINE_LOOP,
	FG_GFX_LINE_STRIP		=	GL_LINE_STRIP
};

/*
 *
 */
class fgGfxPrimitives
{
private:
	//
	fgGfxPrimitives() { }
	//
	~fgGfxPrimitives() { }

public:
	/*
	 *
	 */
	static void drawRect2D(void);

	/*
	 *
	 */
	static void drawArray2D(const fgVertexDataBase *inputData,
		const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES);

	/*
	 *
	 */
	static void drawArray2D(const fgVector<fgVertex2> &inputData,
		const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES);

	/*
	 *
	 */
	static void drawArray2D(const fgVector<fgVertex3> &inputData,
		const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES);

	/*
	 *
	 */
	static void drawArray2D(const fgVector<fgVertex4> &inputData,
		const unsigned int attribMask = FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES);

	/* ***************** 2 component vertex struct - pos, uv ************ */
#if 0
	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex2> &outputData, 
		float sizex, float sizey,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex2> &outputData, 
		const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex2> &outputData, 
		const fgVec2f &relPos, const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);
#endif
	/* ***************** 3 component vertex struct - pos, norm, uv ************ */

	/*
	 *
	 */
	static void appendRect2D(
		fgVertexDataBase *outputData,
		float sizex, float sizey,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgColor4f &color,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVertexDataBase *outputData,
		const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgColor4f &color,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVertexDataBase *outputData,
		const fgVec2f &relPos, const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgColor4f &color,
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/* ***************** 4 component vertex struct - pos, norm, uv ************ */
#if 0
	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex4> &outputData, 
		float sizex, float sizey,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex4> &outputData, 
		const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);

	/*
	 *
	 */
	static void appendRect2D(
		fgVector<fgVertex4> &outputData, 
		const fgVec2f &relPos, const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgGfxPrimitiveMode mode = FG_GFX_TRIANGLES,
		const fgBool rewind = FG_FALSE);
#endif
};

#endif /* _FG_GFX_PRIMITIVES_H_ */
