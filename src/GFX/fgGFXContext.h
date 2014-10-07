/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_CONTEXT_H_
#define _FG_GFX_CONTEXT_H_

#ifndef _FG_GFX_GL_H_
#include "fgGFXGL.h"
#endif

#ifndef _FG_GFX_TYPES_H_
#include "fgGFXTypes.h"
#endif

#define FG_GFX_PARAM_INVALID			0
#define FG_GFX_PARAM_BOOL				1
#define FG_GFX_PARAM_FLOAT				2
#define FG_GFX_PARAM_INT				3
#define FG_GFX_PARAM_ATTRIB				4
#define FG_GFX_PARAM_BLEND_FUNC			5
#define FG_GFX_PARAM_BLEND_EQ			6
#define FG_GFX_PARAM_BLEND_COLOR		7
#define FG_GFX_PARAM_VIEWPORT			8
#define FG_GFX_PARAM_SCISSOR			9
#define FG_GFX_PARAM_TEXTURE_2D			10
#define FG_GFX_PARAM_TEXTURE_3D			11
#define FG_GFX_PARAM_TEXTURE			12
#define FG_GFX_PARAM_VERT_BUFFER_BIND	13
#define FG_GFX_PARAM_ELEM_BUFFER_BIND	14
#define FG_GFX_PARAM_CLEAR_DEPTH		15
#define FG_GFX_PARAM_CLEAR_COLOR		16
#define FG_GFX_PARAM_COLOR_MASK			17
#define FG_GFX_PARAM_FRONT_FACE			18
#define FG_GFX_PARAM_CULL_FACE			19
#define FG_GFX_PARAM_PROGRAM			20
#define FG_GFX_PARAM_DEPTH_FUNC			21
#define FG_GFX_PARAM_DEPTH_RANGE		22
#define FG_GFX_PARAM_DEPTH_MASK			23
#define FG_GFX_PARAM_FRAME_BUFFER_BIND	24
#define FG_GFX_PARAM_RENDER_BUFFER_BIND	25
#define FG_GFX_PARAM_HINT				26
#define FG_GFX_PARAM_SAMPLE_COVERAGE	27
#define FG_GFX_PARAM_STENCIL_FUNC		28
#define FG_GFX_PARAM_STENCIL_OP			29
#define FG_GFX_PARAM_STENCIL_MASK		30
#define FG_GFX_PARAM_CLEAR_STENCIL		31
#define FG_GFX_PARAM_PIXEL_STORE		32

/*
 *
 */
struct fgGfxContextParam
{
	/// 
	fgGFXenum pname;
	/// 
	fgGFXenum type;
	/// 
	fgGFXuint paramType;
	/// 
	int count;
	union {
		fgGFXboolean boolVal;
		fgGFXboolean booleans[12];
		fgGFXfloat floats[12];
		fgGFXfloat floatVal;
		fgGFXint ints[12];
		fgGFXint intVal;
	};

	operator fgGFXint()	const	{ return intVal; }
	operator fgGFXfloat() const	{ return floatVal; }
	operator fgGFXboolean() const	{ return boolVal; }
	operator fgGFXuint() const	{ return (fgGFXuint)intVal; }

	// 
	void load(void) {
		if(paramType == FG_GFX_PARAM_INVALID)
			return;
		switch(type) {
		case FG_GFX_BOOL:
			glGetBooleanv(pname, booleans);
			fgGLError("glGetBooleanv");
			break;
		case FG_GFX_FLOAT:
			glGetFloatv(pname, floats);
			fgGLError("glGetFloatv");
			break;
		case FG_GFX_INT:
			glGetIntegerv(pname, ints);
			fgGLError("glGetIntegerv");
			break;
		};
	}

	void determineParamType(void);

	fgBool update(void);

	// 
	fgGfxContextParam(const fgGFXenum _pname = 0) :
		pname(_pname),
		type(FG_GFX_BOOL),
		paramType(FG_GFX_PARAM_INVALID),
		count(1)
	{
		memset(ints, 0, 8);
		determineParamType();
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const fgGFXfloat _fval) :
		pname(_pname),
		type(FG_GFX_FLOAT),
		count(1)
	{
		floats[0] = _fval;
		determineParamType();
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const fgGFXint _ival) :
		pname(_pname),
		type(FG_GFX_INT),
		count(1)
	{
		ints[0] = _ival;
		determineParamType();
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const fgGFXboolean _bval) :
		pname(_pname),
		type(FG_GFX_BOOL),
		count(1)
	{
		booleans[0] = _bval;
		determineParamType();
		//update();
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXfloat *_fvals) :
		pname(_pname),
		count(_count)
	{
		determineParamType();
		set(_fvals, FG_FALSE);
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXint *_ivals) :
		pname(_pname),
		count(_count)
	{
		determineParamType();
		set(_ivals, FG_FALSE);
	}

	// 
	fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXboolean *_bvals) : 
		pname(_pname),
		count(_count)
	{
		determineParamType();
		set(_bvals, FG_FALSE);
	}

	// 
	void set(const fgGFXfloat _fval, const fgBool update = FG_TRUE)
	{
		type = FG_GFX_FLOAT;
		if(fabsf(floats[0] - _fval) > FG_EPSILON) {
			floats[0] = _fval;
			if(update)
				this->update();
		}
	}

	// 
	void set(const fgGFXint _ival, const fgBool update = FG_TRUE)
	{
		type = FG_GFX_INT;
		if(ints[0] != _ival) {
			ints[0] = _ival;	
			if(update)
				this->update();
		}
	}

	void set(const fgGFXint _i0, const fgGFXint _i1, const fgGFXint _i2, const fgGFXint _i3, const fgBool update = FG_TRUE)
	{
		type = FG_GFX_INT;
		if(ints[0] != _i0 ||
			ints[1] != _i1 ||
			ints[2] != _i2 ||
			ints[3] != _i3) {
				ints[0] = _i0;
				ints[1] = _i1;
				ints[2] = _i2;
				ints[3] = _i3;
				if(update)
					this->update();
		}
	}

	void set(const fgGFXfloat _f0, const fgGFXfloat _f1, const fgGFXfloat _f2, const fgGFXfloat _f3, const fgBool update = FG_TRUE)
	{
		type = FG_GFX_INT;
		if(floats[0] != _f0 ||
			floats[1] != _f1 ||
			floats[2] != _f2 ||
			floats[3] != _f3) {
				floats[0] = _f0;
				floats[1] = _f1;
				floats[2] = _f2;
				floats[3] = _f3;
				if(update)
					this->update();
		}
	}

	// 
	void set(const fgGFXboolean _bval, const fgBool update = FG_TRUE)
	{
		type = FG_GFX_BOOL;
		if(booleans[0] != _bval) {
			booleans[0] = _bval;
			if(update)
				this->update();
		}
	}

	// 
	void set(const fgGFXfloat *_fvals, const fgBool update = FG_TRUE)
	{
		if(!_fvals)
			return;
		type = FG_GFX_FLOAT;
		fgBool diff = FG_FALSE;
		for(int i=0;i<count;i++) {
			if(diff || fabsf(floats[i] - _fvals[i]) > FG_EPSILON) {
				floats[i] = _fvals[i];
				diff = FG_TRUE;
			}
		}
		if(update && diff)
			this->update();
	}

	// 
	void set(const fgGFXint *_ivals, const fgBool update = FG_TRUE)
	{
		if(!_ivals)
			return;
		type = FG_GFX_INT;
		fgBool diff = FG_FALSE;
		for(int i=0;i<count;i++) {
			if(diff || ints[i] != _ivals[i]) {
				ints[i] = _ivals[i];
				diff = FG_TRUE;
			}
		}
		if(update && diff)
			this->update();
	}

	// 
	void set(const fgGFXboolean *_bvals, const fgBool update = FG_TRUE)
	{
		if(!_bvals)
			return;
		type = FG_GFX_BOOL;
		fgBool diff = FG_FALSE;
		for(int i=0;i<count;i++) {
			if(booleans[i] != _bvals[i]) {
				booleans[i] = _bvals[i];
				diff = FG_TRUE;
			}
		}
		if(update && diff)
			this->update();
	}

	// 
	void *get(fgGFXenum *_type = NULL)
	{
		if(_type)
			*_type = type;
		
		if(type == FG_GFX_FLOAT)
			return (void *)floats;
		else if(type == FG_GFX_INT)
			return (void *)ints;
		return (void *)booleans;
	}
};

struct fgGfxAttrInfo
{
	fgGFXuint		index;
	fgGFXint		size;
	fgGFXenum		type;
	fgGFXboolean	normalized;
	fgGFXsizei		stride;
	fgGFXvoid*		ptr;
	fgBool			enabled;
	fgGFXuint		bufferBind;
};

/*
 *
 */
class fgGfxContext
{
	friend class fgGfxPlatform;
public:
	typedef std::map<fgGFXenum, fgGfxContextParam> gfxParamMap;
	typedef gfxParamMap::iterator gfxParamMapItor;

private:
	///
	gfxParamMap m_params;
	///
	fgGFXuint m_viewportAreaQ;
	///
	fgGFXuint m_scissorAreaQ;

	///
	fgGFXuint m_attribMask;
	///
	fgGfxAttrInfo m_attrInfo[12];
	///
	fgGFXuint m_boundTexture;

protected:
	//
	fgGfxContext();
	//
	virtual ~fgGfxContext();
	
	void updateAttribMask(const fgGFXuint index);

public:
	//
	void initialize(void);
	//
	fgGfxContextParam& getParam(const fgGFXenum pname);
	
	//
	void enable(const fgGFXenum cap);
	//
	void disable(const fgGFXenum cap);

	//
	fgBool isEnabled(const fgGFXenum pname);
	//
	fgBool isDisabled(const fgGFXenum pname);
	
	//
	void bindBuffer(const fgGFXenum target, const fgGFXuint buffer);
	//
	fgGFXuint boundBuffer(const fgGFXenum target = GL_ARRAY_BUFFER);

	//
	fgGFXuint boundTexture(void) const;
	//
	fgGFXuint activeTexture(void);

	//
	void activeTexture(const fgGFXenum texture);

	//
	void bindTexture2D(const fgGFXuint texID);
	//
	void bindTexture3D(const fgGFXuint texID);

	//
	void blendEquation(const fgGFXenum mode);
	//
	void blendEquation(const fgGFXenum modeRGB, const fgGFXenum modeAlpha);
	//
	void blendFunc(const fgGFXenum sfactor, const fgGFXenum dfactor);
	//
	void blendFunc(const fgGFXenum srcRGB, const fgGFXenum dstRGB, const fgGFXenum srcAlpha, const fgGFXenum dstAlpha);

	//
	void useProgram(const fgGFXuint program);
	//
	fgGFXuint activeProgram(void);

	//
	void viewport(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height);
	//
	void viewport(const fgVector2i& pos, const fgVector2i& size);
	//
	void viewport(const fgVector4i& dimensions);

	//
	void scissor(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height);
	//
	void scissor(const fgVector2i& pos, const fgVector2i& size);
	//
	void scissor(const fgVector4i& dimensions);

	//
	void setScissorTest(const fgBool toggle = FG_TRUE);
	//
	void setDepthTest(const fgBool toggle = FG_TRUE);
	//
	void setCullFace(const fgBool toggle = FG_TRUE);
	//
	void setBlend(const fgBool toggle = FG_TRUE);
	//
	void frontFace(const fgGFXenum mode = GL_CCW);
	//
	void cullFace(const fgGFXenum mode = GL_BACK);
	//
	void depthFunc(const fgGFXenum func);
	//
	void clearDepth(const fgGFXfloat depth = 1.0f);
	//
	void clearColor(const fgGFXfloat red, const fgGFXfloat green, const fgGFXfloat blue, const fgGFXfloat alpha);
	//
	void clearStencil(const fgGFXint s);

	//
	fgGFXuint activeVertexAttribArrayMask(void) const;
	//
	fgBool isVertexAttribArrayActive(const fgGFXuint index) const;

	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
	void enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
	//
	void disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
	//
	void enableVertexAttribArrayMask(const fgGFXuint mask);
	//
	void disableVertexAttribArrayMask(const fgGFXuint mask);
	//
	void diffVertexAttribArrayMask(const fgGFXuint mask);


	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetVertexAttrib.xml
	fgGFXuint getVertexAttribBufferBinding(const fgGFXuint index);
	//
	fgGFXuint getVertexAttribSize(const fgGFXuint index);
	//
	fgGFXuint getVertexAttribStride(const fgGFXuint index);
	//
	fgGFXuint getVertexAttribType(const fgGFXuint index);
	//
	fgGFXuint getVertexAttribNormalized(const fgGFXuint index);

	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	void vertexAttribPointer(fgGFXuint index,
		fgGFXint size,
		fgGFXenum type, 
		fgGFXboolean normalized, 
		fgGFXsizei stride, 
		fgGFXvoid* ptr);

};

#endif /* _FG_GFX_CONTEXT_H_ */
