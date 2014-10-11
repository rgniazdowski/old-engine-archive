/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_TYPES_H_
#define _FG_GFX_TYPES_H_
#define _FG_GFX_TYPES_BLOCK__

#ifdef _FG_TYPES_BLOCK__
#error "FG_TYPES_BLOCK constant is defined. Do not include fgGfxTypes header inside of fgTypes header."
#endif

#ifndef _FG_GFX_GL_H_
#include "fgGFXGL.h"
#endif

#include "fgGFXColor.h"

#ifndef FG_GFX_NONE
#define FG_GFX_NONE 0
#endif

#ifndef FG_GFX_ATTRIB_POS_LOCATION
#define FG_GFX_ATTRIB_POS_LOCATION		0
#endif

#ifndef FG_GFX_ATTRIB_NORM_LOCATION
#define FG_GFX_ATTRIB_NORM_LOCATION		1
#endif

#ifndef FG_GFX_ATTRIB_UVS_LOCATION
#define FG_GFX_ATTRIB_UVS_LOCATION		2
#endif

#ifndef FG_GFX_ATTRIB_COLOR_LOCATION
#define FG_GFX_ATTRIB_COLOR_LOCATION	3
#endif

#ifndef FG_GFX_ATTRIB_TANGENT_LOCATION
#define FG_GFX_ATTRIB_TANGENT_LOCATION	4
#endif

#ifndef FG_GFX_POSITION_BIT
#define FG_GFX_POSITION_BIT		0x0001
#endif

#ifndef FG_GFX_NORMAL_BIT
#define FG_GFX_NORMAL_BIT		0x0002
#endif 

#ifndef FG_GFX_UVS_BIT
#define FG_GFX_UVS_BIT		    0x0004
#endif 

#ifndef FG_GFX_COLOR_BIT
#define FG_GFX_COLOR_BIT		0x0008
#endif 

#ifndef FG_GFX_TANGENT_BIT
#define FG_GFX_TANGENT_BIT		0x0020
#endif 

#if !defined(FG_GFX_GL_MASK_TYPEDEFS_DEFINED) && defined(_FG_INCLUDED_GL_)
#define FG_GFX_GL_MASK_TYPEDEFS_DEFINED
typedef GLvoid		fgGFXvoid;
typedef GLchar		fgGFXchar;
typedef GLenum		fgGFXenum;
typedef GLboolean	fgGFXboolean;
typedef GLbitfield	fgGFXbitfield;
typedef GLbyte		fgGFXbyte;
typedef GLshort		fgGFXshort;
typedef GLint		fgGFXint;
typedef GLsizei		fgGFXsizei;
typedef GLubyte		fgGFXubyte;
typedef GLushort	fgGFXushort;
typedef GLuint		fgGFXuint;
typedef GLfloat		fgGFXfloat;
typedef GLclampf	fgGFXclampf;
#ifndef FG_USING_SDL2
typedef GLfixed		fgGFXfixed;
#else
typedef int         fgGFXfixed;
#endif

#endif

//
// Buffer / Texture / ... binding helper structures
//

struct fgGfxBufferID
{
	fgGFXuint id;
	fgGFXenum target;
	fgGFXenum usage;

	operator fgGFXint() const	{ return (fgGFXint)id; }
	operator fgGFXuint() const	{ return id; }

	fgGFXuint& refID(void) {
		return id;
	}

	fgGFXuint* ptrID(void) {
		return &id;
	}

	fgGfxBufferID(fgGFXuint _id = 0, fgGFXenum _target = (fgGFXenum)0) :
		id(_id), target(_target) {
	}
};

struct fgGfxTextureID
{
	fgGFXuint id;
	fgGFXenum target;

	operator fgGFXint() const	{ return (fgGFXint)id; }
	operator fgGFXuint() const	{ return id; }

	fgGFXuint& refID(void) {
		return id;
	}

	fgGFXuint* ptrID(void) {
		return &id;
	}

	fgGfxTextureID(fgGFXuint _id = 0, fgGFXenum _target = GL_TEXTURE_2D) :
		id(_id), target(_target) {
	}
};

//
// Data types
//

//	bool	-	a conditional type, taking on values of true or false
//	int		-	a signed integer
//	float	-	a single floating-point scalar
//	vec2	-	a two component floating-point vector
//	vec3	-	a three component floating-point vector
//	vec4	-	a four component floating-point vector
//	bvec2	-	a two component Boolean vector
//	bvec3	-	a three component Boolean vector
//	bvec4	-	a four component Boolean vector
//	ivec2	-	a two component integer vector
//	ivec3	-	a three component integer vector
//	ivec4	-	a four component integer vector
//	mat2	-	a 2x2 floating-point matrix
//	mat3	-	a 3x3 floating-point matrix
//	mat4	-	a 4x4 floating-point matrix
//	sampler2D	-	a handle for accessing a 2D texture
//	samplerCube	-	a handle for accessing a cube mapped texture

#define	FG_GFX_FLOAT			GL_FLOAT
#define	FG_GFX_FLOAT_VEC2		GL_FLOAT_VEC2
#define	FG_GFX_FLOAT_VEC3		GL_FLOAT_VEC3
#define	FG_GFX_FLOAT_VEC4		GL_FLOAT_VEC4
#define FG_GFX_INT				GL_INT
#define	FG_GFX_INT_VEC2			GL_INT_VEC2
#define	FG_GFX_INT_VEC3			GL_INT_VEC3
#define	FG_GFX_INT_VEC4			GL_INT_VEC4
#define	FG_GFX_BOOL				GL_BOOL
#define	FG_GFX_BOOL_VEC2		GL_BOOL_VEC2
#define	FG_GFX_BOOL_VEC3		GL_BOOL_VEC3
#define	FG_GFX_BOOL_VEC4		GL_BOOL_VEC4
#define	FG_GFX_FLOAT_MAT2		GL_FLOAT_MAT2
#define	FG_GFX_FLOAT_MAT3		GL_FLOAT_MAT3
#define	FG_GFX_FLOAT_MAT4		GL_FLOAT_MAT4	
#define	FG_GFX_SAMPLER_2D		GL_SAMPLER_2D
#define	FG_GFX_SAMPLER_CUBE		GL_SAMPLER_CUBE

//
// String literals for uniform data types (GL)
//

#define	FG_GFX_FLOAT_TEXT			"float"
#define	FG_GFX_FLOAT_VEC2_TEXT		"vec2"
#define	FG_GFX_FLOAT_VEC3_TEXT		"vec3"
#define	FG_GFX_FLOAT_VEC4_TEXT		"vec4"
#define FG_GFX_INT_TEXT				"int"
#define	FG_GFX_INT_VEC2_TEXT		"ivec2"
#define	FG_GFX_INT_VEC3_TEXT		"ivec3"
#define	FG_GFX_INT_VEC4_TEXT		"ivec4"
#define	FG_GFX_BOOL_TEXT			"bool"
#define	FG_GFX_BOOL_VEC2_TEXT		"bvec2"
#define	FG_GFX_BOOL_VEC3_TEXT		"bvec3"
#define	FG_GFX_BOOL_VEC4_TEXT		"bvec4"
#define	FG_GFX_FLOAT_MAT2_TEXT		"mat2"
#define	FG_GFX_FLOAT_MAT3_TEXT		"mat3"
#define	FG_GFX_FLOAT_MAT4_TEXT		"mat4"
#define	FG_GFX_SAMPLER_2D_TEXT		"sampler2D"
#define	FG_GFX_SAMPLER_CUBE_TEXT	"samplerCube"

//
// Convertion from string->enum,  enum->string for data types (GFX)
//

// Convert text (literal) to corresponding enum value
inline fgGFXenum _FG_GFX_DATA_TYPE_FROM_TEXT(const char* text) {
	if(!text)
		return (fgGFXenum)FG_GFX_NONE;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC2);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC3);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_VEC4);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC2);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC3);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_INT_VEC4);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC2);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC3);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_BOOL_VEC4);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT2);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT3);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_FLOAT_MAT4);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SAMPLER_2D);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_GFX_SAMPLER_CUBE);
	return (fgGFXenum)FG_GFX_NONE;
}

inline const char * _FG_GFX_DATA_TYPE_TO_TEXT(fgGFXenum value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT,			FG_TEXT(FG_GFX_FLOAT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC2,	FG_TEXT(FG_GFX_FLOAT_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC3,	FG_TEXT(FG_GFX_FLOAT_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_VEC4,	FG_TEXT(FG_GFX_FLOAT_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT,			FG_TEXT(FG_GFX_INT));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC2,		FG_TEXT(FG_GFX_INT_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC3,		FG_TEXT(FG_GFX_INT_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_INT_VEC4,		FG_TEXT(FG_GFX_INT_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL,			FG_TEXT(FG_GFX_BOOL));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC2,		FG_TEXT(FG_GFX_BOOL_VEC2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC3,		FG_TEXT(FG_GFX_BOOL_VEC3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_BOOL_VEC4,		FG_TEXT(FG_GFX_BOOL_VEC4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT2,	FG_TEXT(FG_GFX_FLOAT_MAT2));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT3,	FG_TEXT(FG_GFX_FLOAT_MAT3));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_FLOAT_MAT4,	FG_TEXT(FG_GFX_FLOAT_MAT4));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_2D,	FG_TEXT(FG_GFX_SAMPLER_2D));
	FG_RETURN_VAL_IF_EQUAL(value, FG_GFX_SAMPLER_CUBE,	FG_TEXT(FG_GFX_SAMPLER_CUBE));

	return NULL;
}

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_GFX_DATA_TYPE_FROM_TEXT(text)	_FG_GFX_DATA_TYPE_FROM_TEXT(text)
#define FG_GFX_DATA_TYPE_TO_TEXT(value)		_FG_GFX_DATA_TYPE_TO_TEXT(value)

#include <cmath>

#ifndef FG_EPSILON
#define FG_EPSILON 1e-6f
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PIF
#define M_PIF 3.14159265358979323846f
#endif

#ifndef FG_DEG2RAD
#define FG_DEG2RAD (M_PIF / 180.0f)
#endif
#ifndef FG_RAD2DEG
#define FG_RAD2DEG (180.0f / M_PIF)
#endif

#if defined FG_USING_GLM
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#ifndef FG_MATH_GLM_VECTOR_MASK
#define FG_MATH_GLM_VECTOR_MASK

typedef glm::bvec2 fgVector2b;
typedef glm::bvec3 fgVector3b;
typedef glm::bvec4 fgVector4b;

typedef glm::uvec2 fgVector2u;
typedef glm::uvec3 fgVector3u;
typedef glm::uvec4 fgVector4u;

typedef glm::ivec2 fgVector2i;
typedef glm::ivec3 fgVector3i;
typedef glm::ivec4 fgVector4i;

typedef glm::vec2 fgVector2f;
typedef glm::vec3 fgVector3f;
typedef glm::vec4 fgVector4f;

typedef glm::dvec2 fgVector2d;
typedef glm::dvec3 fgVector3d;
typedef glm::dvec4 fgVector4d;

#endif /* FG_MATH_GLM_VECTOR_MASK */

#ifdef FG_MATH_GLM_VECTOR_MASK
typedef fgVector2b	fgVec2b;
typedef fgVector3b	fgVec3b;
typedef fgVector4b	fgVec4b;

typedef fgVector2u	fgVec2u;
typedef fgVector3u	fgVec3u;
typedef fgVector4u	fgVec4u;

typedef fgVector2i	fgVec2i;
typedef fgVector3i	fgVec3i;
typedef fgVector4i	fgVec4i;

typedef fgVector2f	fgVec2f;
typedef fgVector3f	fgVec3f;
typedef fgVector4f	fgVec4f;

typedef fgVector2d	fgVec2d;
typedef fgVector3d	fgVec3d;
typedef fgVector4d	fgVec4d;
#endif /* FG_MATH_GLM_VECTOR_MASK */

#else

#endif /* FG_USING_GLM */

struct fgArea
{
		int x;
		int y;
		int w;
		int h;
		fgArea(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
		fgArea() : x(0), y(0), w(0), h(0) {}

        int left() const {
            return x;
        }

        int right() const {
            return x + w;
        }

        int top() const {
            return y;
        }

        int bottom() const {
            return y + h;
        }

        int width() const {
            return w;
        }

        int height() const {
            return h;
        }

        void setLeft(int l) {
            x = l;
        }

        void setRight(int r) {
            w = r - x;
        }

        void setTop(int t) {
            y = t;
        }

        void setBottom(int b) {
            h = b - y;
        }

        void setWidth(int _w) {
            w = _w;
        }

        void setHeight(int _h) {
            h = _h;
        }
};

///////////////////////////////////////////////////////////

//#pragma pack(push, 0)

// Vertex4 - pos, norm, uv, color
struct fgVertex4
{
	fgVector3f position;	// location 0
	fgVector3f normal;		// location 1
	fgVector2f uv;			// location 2
	fgColor4f color;		// location 3

	static unsigned int size(void) {
		return 4;
	}

	static fgGFXuint getAttribMask(void) {
		return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT;
	}
};

//#pragma pack(pop)
//#pragma pack(push, 0)

// Vertex3 - pos, norm, uv
struct fgVertex3
{
	fgVector3f position;
	fgVector3f normal;
	fgVector2f uv;

	// #FIXME - change name 'size'
	static unsigned int size(void) {
		return 3;
	}

	static fgGFXuint getAttribMask(void) {
		return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT;
	}	
};

//#pragma pack(pop)
//#pragma pack(push, 0)

// Vertex2 - pos, uv
struct fgVertex2
{
	fgVector3f position;
	fgVector2f uv;

	static unsigned int size(void) {
		return 2;
	}

	static fgGFXuint getAttribMask(void) {
		return FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT;
	}
};

//#pragma pack(pop)

#include "fgVector.h"

/*
 *
 */
class fgVertexDataBase
{
public:
	//
	fgVertexDataBase() { }
	//
	virtual ~fgVertexDataBase() { }

	//
	virtual fgBool isSoA(void) const = 0;

	//
	virtual fgBool isAoS(void) const = 0;

	//
	virtual void append(const fgVector3f &pos) = 0;
	
	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector2f &uv) = 0;

	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal,
		const fgVector2f &uv) = 0;
	
	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal,
		const fgVector2f &uv,
		const fgColor3f &color) = 0;
	
	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal,
		const fgVector2f &uv,
		const fgColor4f &color) = 0;
	
	//
	virtual void pop_back(void) = 0;
	
	//
	virtual fgGFXvoid *back(void) const = 0;
	
	//
	virtual void clear(void) = 0;
	
	//
	virtual fgGFXvoid *front(void) const = 0;
	
	//
	virtual fgGFXuint size(void) const = 0;
	
	//
	virtual fgGFXsizei stride(void) const = 0;
	
	//
	virtual fgGFXuint attribMask(void) const = 0;

	//
	virtual bool empty(void) const = 0;
};

/*
 *
 */
class fgVertexData2 : public fgVertexDataBase, public fgVector<fgVertex2>
{
public:
	//
	virtual ~fgVertexData2() { }

	//
	virtual fgBool isSoA(void) const {
		return FG_FALSE;
	}

	// 
	virtual fgBool isAoS(void) const {
		return FG_TRUE;
	}	

	//
	virtual void append(const fgVector3f &pos)
	{
		fgVertex2 vertex;
		vertex.position = pos;
		vertex.uv = fgVector2f(1.0f, 1.0f);
		fgVector<fgVertex2>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector2f &uv)
	{
		fgVertex2 vertex;
		vertex.position = pos;
		vertex.uv = uv;
		fgVector<fgVertex2>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv)
	{
		append(pos, uv);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv, 
		const fgColor3f &color)
	{
		append(pos, uv);
	}

	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal, 
		const fgVector2f &uv,
		const fgColor4f &color)
	{
		append(pos, uv);
	}

	//
	virtual void pop_back(void)
	{
		fgVector<fgVertex2>::pop_back();
	}

	//
	virtual fgGFXvoid *back(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex2>::back());
	}

	//
	virtual void clear(void)
	{
		fgVector<fgVertex2>::clear();
	}

	//
	virtual fgGFXvoid *front(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex2>::front());
	}

	//
	virtual fgGFXuint size(void) const 
	{
		return fgVector<fgVertex2>::size();
	}

	//
	virtual fgGFXsizei stride(void) const
	{
		return sizeof(fgVertex2);
	}

	//
	virtual fgGFXuint attribMask(void) const
	{
		return (fgGFXuint) fgVertex2::getAttribMask();
	}

	//
	virtual bool empty(void) const
	{
		return (bool) fgVector<fgVertex2>::empty();
	}
};

/*
 *
 */
class fgVertexData3 : public fgVertexDataBase, public fgVector<fgVertex3>
{
public:
	//
	virtual ~fgVertexData3() { }

	//
	virtual fgBool isSoA(void) const {
		return FG_FALSE;
	}

	// 
	virtual fgBool isAoS(void) const {
		return FG_TRUE;
	}	

	//
	virtual void append(const fgVector3f &pos)
	{
		fgVertex3 vertex;
		vertex.position = pos;
		vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
		vertex.uv = fgVector2f(1.0f, 1.0f);
		fgVector<fgVertex3>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector2f &uv)
	{
		fgVertex3 vertex;
		vertex.position = pos;
		vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
		vertex.uv = uv;
		fgVector<fgVertex3>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv)
	{
		fgVertex3 vertex;
		vertex.position = pos;
		vertex.normal = normal;
		vertex.uv = uv;
		fgVector<fgVertex3>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv, 
		const fgColor3f &color)
	{
		append(pos, normal, uv);
	}

	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal, 
		const fgVector2f &uv,
		const fgColor4f &color)
	{
		append(pos, normal, uv);
	}

	//
	virtual void pop_back(void)
	{
		fgVector<fgVertex3>::pop_back();
	}

	//
	virtual fgGFXvoid *back(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex3>::back());
	}

	//
	virtual void clear(void)
	{
		fgVector<fgVertex3>::clear();
	}

	//
	virtual fgGFXvoid *front(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex3>::front());
	}

	//
	virtual fgGFXuint size(void) const
	{
		return fgVector<fgVertex3>::size();
	}

	//
	virtual fgGFXsizei stride(void) const
	{
		return sizeof(fgVertex3);
	}

	//
	virtual fgGFXuint attribMask(void) const
	{
		return (fgGFXuint) fgVertex3::getAttribMask();
	}

	//
	virtual bool empty(void) const
	{
		return (bool) fgVector<fgVertex3>::empty();
	}
};

/*
 *
 */
class fgVertexData4 : public fgVertexDataBase, public fgVector<fgVertex4>
{
public:
	//
	virtual ~fgVertexData4() { }

	//
	virtual fgBool isSoA(void) const {
		return FG_FALSE;
	}

	// 
	virtual fgBool isAoS(void) const {
		return FG_TRUE;
	}	

	//
	virtual void append(const fgVector3f &pos)
	{
		fgVertex4 vertex;
		vertex.position = pos;
		vertex.uv = fgVector2f(1.0f, 1.0f);
		vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
		vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		fgVector<fgVertex4>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector2f &uv)
	{
		fgVertex4 vertex;
		vertex.position = pos;
		vertex.uv = uv;
		vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
		vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		fgVector<fgVertex4>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv)
	{
		fgVertex4 vertex;
		vertex.position = pos;
		vertex.normal = normal;
		vertex.uv = uv;
		vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		fgVector<fgVertex4>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos, 
		const fgVector3f &normal,
		const fgVector2f &uv, 
		const fgColor3f &color)
	{
		fgVertex4 vertex;
		vertex.position = pos;
		vertex.normal = normal;
		vertex.uv = uv;
		vertex.color = fgColor4f(color.r, color.g, color.b, 1.0f);
		fgVector<fgVertex4>::push_back(vertex);
	}

	//
	virtual void append(
		const fgVector3f &pos,
		const fgVector3f &normal, 
		const fgVector2f &uv,
		const fgColor4f &color)
	{
		fgVertex4 vertex;
		vertex.position = pos;
		vertex.normal = normal;
		vertex.uv = uv;
		vertex.color = color;
		fgVector<fgVertex4>::push_back(vertex);
	}

	//
	virtual void pop_back(void)
	{
		fgVector<fgVertex4>::pop_back();
	}

	//
	virtual fgGFXvoid *back(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex4>::back());
	}

	//
	virtual void clear(void)
	{
		fgVector<fgVertex4>::clear();
	}

	//
	virtual fgGFXvoid *front(void) const
	{
		return (fgGFXvoid *)(&fgVector<fgVertex4>::front());
	}

	//
	virtual fgGFXuint size(void) const
	{
		return fgVector<fgVertex4>::size();
	}

	//
	virtual fgGFXsizei stride(void) const
	{
		return sizeof(fgVertex4);
	}

	//
	virtual fgGFXuint attribMask(void) const
	{
		return (fgGFXuint) fgVertex4::getAttribMask();
	}

	//
	virtual bool empty(void) const
	{
		return (bool) fgVector<fgVertex4>::empty();
	}
};

#undef _FG_GFX_TYPES_BLOCK__
#endif /* _FG_GFX_TYPES_H_ */
