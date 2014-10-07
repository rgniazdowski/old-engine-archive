/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_DRAW_CALL_H_
#define _FG_GFX_DRAW_CALL_H_

#ifndef _FG_GFX_PRIMITIVES_H_
#include "fgGFXPrimitives.h"
#endif

#define FG_GFX_DRAW_CALL_INVALID		0
#define FG_GFX_DRAW_CALL_VERTEX_BUFFER	1
#define FG_GFX_DRAW_CALL_CUSTOM_ARRAY	2
#define FG_GFX_DRAW_CALL_OBJECT			3

#ifndef _FG_GFX_SHADER_DEFS_H_
#include "GFX/Shaders/fgGFXShaderDefs.h"
#endif
#ifndef _FG_GFX_SHADER_PROGRAM_H_
#include "GFX/Shaders/fgGFXShaderProgram.h"
#endif
#ifndef _FG_GFX_TYPES_H_
#include "fgGFXTypes.h"
#endif

#ifndef _FG_TEXTURE_RESOURCE_H_
#include "Textures/fgTextureResource.h"
#endif

#ifndef _FG_GFX_MVP_MATRIX_H_
#include "fgGFXMVPMatrix.h"
#endif

typedef unsigned int fgGfxDrawCallType;
typedef unsigned int fgGfxDrawAppendMode;

#define FG_GFX_DRAW_APPEND_ABSOLUTE 0
#define FG_GFX_DRAW_APPEND_RELATIVE	1

class fgGfxDrawCall
{
private:
	/// Attribute binding data // Need to think what do with indices ?
	fgGfxAttributeData m_attrData[FG_GFX_ATTRIBUTE_COUNT];
	///
	fgVertexDataBase *m_vecDataBase;
	/// Pointer to the shader program used in this draw call
	/// It can be set to NULL, then the draw call will use
	/// last active shader program. The pointer to the shader
	/// program is required for updating uniform variables
	fgGfxShaderProgram *m_program;
	/// Pointer to the used texture - this will require also pointer
	/// to the shader program (so the proper uniform sampler variable
	/// can be updated). However this is not always required.
	/// If there is no multitexturing then theres always one
	/// texture active (TEXTURE0).
	fgTextureResource *m_texture;
	/// Pointer to external MVP matrix to use
	/// this will need to be updated for every drawcall made
	/// because the model matrix would change
	/// view and projection matrix parameters stay the same (mostly)
	/// through all drawing batch
	fgGfxMVPMatrix *m_MVP;
	/// Used vertex data will depend on the attribute mask used
	/// Appending specific data however may alter this and make 
	/// other buffers invalid
	fgGFXuint m_attribMask;
	/// What kind of draw call is this?
	fgGfxDrawCallType m_drawCallType;
	///
	fgGfxDrawAppendMode m_drawAppendMode;
	/// Primitive mode used for drawing the vertex buffer
	/// It defaults to FG_GFX_TRIANGLES, however the most
	/// optimal is the Triangle Strip - this requires however
	/// modification of the vertex data after loading
	fgGfxPrimitiveMode m_primMode;
	/// Model matrix for current draw call
	fgMatrix4f	m_modelMat;
	/// Current color used
	fgColor4f m_color;
	///
	fgVector3f m_relMove;
	///
	int m_zIndex;

private:
	//
	void setupVertexData(fgGFXuint attribMask);

public:
	//
	fgGfxDrawCall();
	//
	virtual ~fgGfxDrawCall();
	
	//
	int getZIndex(void) const;
	//
	fgGfxAttributeData* getAttributeData(void);
	//
	fgGFXuint getAttribMask(void) const;
	//
	fgGfxDrawCallType getDrawCallType(void) const;
	//
	fgGfxDrawAppendMode getDrawAppendMode(void) const;
	//
	fgGfxPrimitiveMode getPrimitiveMode(void) const;

	//
	void setZIndex(const int zIndex);
	//
	void upZIndex(void);
	//
	void downZIndex(void);
	//
	void setDrawCallType(const fgGfxDrawCallType type);
	//
	void setDrawAppendMode(const fgGfxDrawAppendMode mode);
	//
	void setPrimitiveMode(const fgGfxPrimitiveMode mode);

	// Whether to set UVs, normals or colors active
	void setComponentActive(unsigned int component);

	// Set active color for the next data
	virtual void setColor(const fgColor3f& color);
	// Set active color for the next data
	virtual void setColor(const fgColor4f& color);
	// This will reset used color
	virtual void resetColor(void);

	//
	void setMVP(fgGfxMVPMatrix *MVP = NULL);
	//
	fgGfxMVPMatrix *getMVP(void) const;

	// Can be null, which would mean that this draw call does not care about such thing
	// However it should be avoided. Shader program knows if it's being currently used.
	// Also only through shader manager given shader program can be set as active.
	void setShaderProgram(fgGfxShaderProgram *pProgram = NULL);
	//
	fgGfxShaderProgram *getShaderProgram(void) const;

	//
	void setTexture(fgTextureResource *texture = NULL);
	//
	fgTextureResource *getTexture(void) const;
	
	// Clear the buffers
	virtual void flush(void);

	// Append simple rectangle next to the last one
	void appendRect2D(const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgBool rewind = FG_FALSE);

	// Append simple rectangle with relative position to the last data
	void appendRect2D(const fgVec2f &relPos, const fgVec2f &size,
		const fgVec2f &uv1, const fgVec2f &uv2, 
		const fgBool rewind = FG_FALSE);

	//
	virtual void draw(void);
	//
	virtual void draw(const fgVec2f& relPos);
	//
	virtual void draw(const fgVec3f& relPos);
	//
	virtual void draw(const fgMatrix4f& modelMat);

	///////////////////////////////////////////////////////
	// COMPARISON OPERATORS

	inline int operator==(const fgGfxDrawCall& b) const {
		if(b.m_program == this->m_program) {
			if(b.m_texture == this->m_texture) {
				if(b.m_attribMask == this->m_attribMask) {
					return 1;
				}
			}
		}
		return 0;
	}

	inline int operator!=(const fgGfxDrawCall& b) const {
		if(b.m_program != this->m_program)
			return 1;

		if(b.m_texture != this->m_texture) 
			return 1;

		if(b.m_attribMask != this->m_attribMask)
			return 1;
		
		
		return 0;
	}

	inline bool operator<(const fgGfxDrawCall& a) const {
		if(this->m_program < a.m_program)
			return true;
		else if(this->m_program > a.m_program)
			return false;
		else
		{
			if(this->m_texture < a.m_texture)
				return true;
			else if(this->m_texture  > a.m_texture)
				return false;
			else
			{
				if(this->m_zIndex < a.m_zIndex)
					return true;
				else if(this->m_zIndex > a.m_zIndex)
					return false;
				else
				{ 
					if(this->m_attribMask < a.m_attribMask)
						return true;
					else
						return false;
				}
			}
		}
		return false;
    }

	inline bool operator>(const fgGfxDrawCall& a) const {
		if(this->m_program < a.m_program)
			return false;
		else if(this->m_program > a.m_program)
			return true;
		else
		{
			if(this->m_texture < a.m_texture)
				return false;
			else if(this->m_texture  > a.m_texture)
				return true;
			else
			{
				if(this->m_zIndex < a.m_zIndex)
					return false;
				else if(this->m_zIndex > a.m_zIndex)
					return true;
				else
				{ 
					if(this->m_attribMask < a.m_attribMask)
						return false;
					else
						return true;
				}
			}
		}
		return false;
    }

	inline bool operator<=(const fgGfxDrawCall& a) const {
		if(this->m_program < a.m_program)
			return true;
		else if(this->m_program > a.m_program)
			return false;
		else
		{
			if(this->m_texture < a.m_texture)
				return true;
			else if(this->m_texture  > a.m_texture)
				return false;
			else
			{
				if(this->m_zIndex < a.m_zIndex)
					return true;
				else if(this->m_zIndex > a.m_zIndex)
					return false;
				else
				{ 
					if(this->m_attribMask < a.m_attribMask)
						return true;
					else if(this->m_attribMask > a.m_attribMask)
						return false;
				}
			}
		}
		return true;
    }

	inline bool operator>=(const fgGfxDrawCall& a) const {
		if(this->m_program < a.m_program)
			return false;
		else if(this->m_program > a.m_program)
			return true;
		else
		{
			if(this->m_texture < a.m_texture)
				return false;
			else if(this->m_texture  > a.m_texture)
				return true;
			else
			{
				if(this->m_zIndex < a.m_zIndex)
					return false;
				else if(this->m_zIndex > a.m_zIndex)
					return true;
				else
				{ 
					if(this->m_attribMask < a.m_attribMask)
						return false;
					else if(this->m_attribMask > a.m_attribMask)
						return true;
				}
			}
		}
		return true;
    }
};

#endif /* _FG_GFX_DRAW_CALL_H_ */
