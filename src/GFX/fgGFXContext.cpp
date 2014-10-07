/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXContext.h"

/*
 *
 */
void fgGfxContextParam::determineParamType(void)
{
	switch(this->pname)
	{
	// params returns a single value indicating the active multitexture unit. The initial value is GL_TEXTURE0.
	// See glActiveTexture.
	case GL_ACTIVE_TEXTURE:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_TEXTURE;
		break;

	// params returns two values, the smallest and largest supported widths for aliased lines.
	// The range must include width 1.
	case GL_ALIASED_LINE_WIDTH_RANGE:
	// params returns two values, the smallest and largest supported sizes for aliased points.
	// The range must include size 1.
	case GL_ALIASED_POINT_SIZE_RANGE:
		count = 2;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	// params returns one value, the number of alpha bitplanes in the color buffer of the
	// currently bound framebuffer.
	case GL_ALPHA_BITS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	// params returns a single boolean value indicating whether blending is enabled. 
	// The initial value is GL_FALSE. See glBlendFunc.
	case GL_BLEND:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	// params returns four values, the red, green, blue, and alpha values which are
	// the components of the blend color. See glBlendColor.
	case GL_BLEND_COLOR:
		count = 4;
		type = FG_GFX_FLOAT;
		paramType = FG_GFX_PARAM_BLEND_COLOR;
		break;

	// params returns one value, the symbolic constant identifying the alpha destination blend function. The initial value is GL_ZERO.
	// See glBlendFunc and glBlendFuncSeparate.
	case GL_BLEND_DST_ALPHA:
	// params returns one value, the symbolic constant identifying the RGB destination blend
	// function. The initial value is GL_ZERO. See glBlendFunc and glBlendFuncSeparate.
	case GL_BLEND_DST_RGB:
	// params returns one value, the symbolic constant identifying the alpha source blend function.
	// The initial value is GL_ONE. See glBlendFunc and glBlendFuncSeparate.
	case GL_BLEND_SRC_ALPHA:
	// params returns one value, the symbolic constant identifying the RGB source blend function. 
	// The initial value is GL_ONE.
	// See glBlendFunc and glBlendFuncSeparate.
	case GL_BLEND_SRC_RGB:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_BLEND_FUNC;
		break;

	// params returns one value, a symbolic constant indicating whether the Alpha blend equation 
	// is GL_FUNC_ADD, GL_FUNC_SUBTRACT, or GL_FUNC_REVERSE_SUBTRACT.
	// See glBlendEquationSeparate.
	case GL_BLEND_EQUATION_ALPHA:
	// params returns one value, a symbolic constant indicating whether the RGB blend equation 
	// is GL_FUNC_ADD, GL_FUNC_SUBTRACT, or GL_FUNC_REVERSE_SUBTRACT.
	// See glBlendEquationSeparate.
	case GL_BLEND_EQUATION_RGB:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_BLEND_EQ;
		break;

	// params returns one value,
	// the number of red bitplanes in the color buffer of the
	// currently bound framebuffer.
	case GL_RED_BITS:
	// params returns one value,
	// the number of green bitplanes in the color buffer of the
	// currently bound framebuffer.
	case GL_GREEN_BITS:
	// params returns one value, 
	// the number of blue bitplanes in the color buffer of the
	// currently bound framebuffer.
	case GL_BLUE_BITS:
	// params returns one value,
	// the number of bitplanes in the depth buffer of the
	// currently bound framebuffer.
	case GL_DEPTH_BITS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns four values:
	//    the red, green, blue, and alpha values used to clear the color buffers.
	//    Integer values, if requested,
	//    are linearly mapped from the internal floating-point representation such
	//    that 1.0 returns the most positive representable integer value,
	//    and -1.0 returns the most negative representable integer
	//    value. The initial value is (0, 0, 0, 0).
	//    See glClearColor.
	case GL_COLOR_CLEAR_VALUE:
		count = 4;
		type = FG_GFX_FLOAT;
		paramType = FG_GFX_PARAM_CLEAR_COLOR;
		break;

	//    params returns four boolean values:
	//    the red, green, blue, and alpha write enables for the color
	//    buffers. The initial value is (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE).
	//    See glColorMask.
	case GL_COLOR_WRITEMASK:
		count = 4;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_COLOR_MASK;
		break;

	//    params returns a list of symbolic
	//    constants of length GL_NUM_COMPRESSED_TEXTURE_FORMATS 
	//    indicating which compressed texture formats are available.
	//    See glCompressedTexImage2D.
	case GL_COMPRESSED_TEXTURE_FORMATS:
		// #FIXME
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns a single boolean value indicating whether polygon culling
	//    is enabled. The initial value is GL_FALSE.
	//    See glCullFace.
	case GL_CULL_FACE:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns one value,
	//    a symbolic constant indicating which polygon faces are to be
	//    culled. The initial value is GL_BACK.
	//    See glCullFace.
	case GL_CULL_FACE_MODE:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_CULL_FACE;
		break;

	//    params returns one value,
	//    the name of the program object that is currently active, or 0 if no program object is active.
	//    See glUseProgram.
	case GL_CURRENT_PROGRAM:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_PROGRAM;
		break;

	//    params returns one value,
	//    the value that is used to clear the depth buffer.
	//    Integer values, if requested,
	//    are linearly mapped from the internal floating-point representation such
	//    that 1.0 returns the most positive representable integer value,
	//    and -1.0 returns the most negative representable integer
	//    value. The initial value is 1.
	//    See glClearDepthf.
	case GL_DEPTH_CLEAR_VALUE:
		count = 1;
		type = FG_GFX_FLOAT;
		paramType = FG_GFX_PARAM_CLEAR_DEPTH;
		break;

	//    params returns one value, the symbolic constant that indicates the depth comparison
	//    function. The initial value is GL_LESS.
	//    See glDepthFunc.
	case GL_DEPTH_FUNC:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_DEPTH_FUNC;
		break;

	//    params returns two values: the near and far mapping limits for the depth buffer.
	//    Integer values, if requested, are linearly mapped from the internal 
	//	  floating-point representation such that 1.0 returns the most positive representable
	//	  integer value, and -1.0 returns the most negative representable integer
	//    value. The initial value is (0, 1). See glDepthRangef.
	case GL_DEPTH_RANGE:
		count = 2;
		type = FG_GFX_FLOAT;
		paramType = FG_GFX_PARAM_DEPTH_RANGE;
		break;

	//    params returns a single boolean value indicating whether depth testing
	//    of fragments is enabled. The initial value is GL_FALSE.
	//    See glDepthFunc and glDepthRangef.
	case GL_DEPTH_TEST:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns a single boolean value indicating if the depth buffer
	//    is enabled for writing. The initial value is GL_TRUE.
	//    See glDepthMask.
	case GL_DEPTH_WRITEMASK:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_DEPTH_MASK;
		break;

	//    params returns a single boolean value indicating whether dithering of
	//    fragment colors and indices is enabled. The initial value is GL_TRUE.
	case GL_DITHER:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	// params returns a single value, the name of the buffer object
	// currently bound to the target GL_ARRAY_BUFFER. If no buffer object
	// is bound to this target, 0 is returned.  The initial value is 0.
	// See glBindBuffer.
	case GL_ARRAY_BUFFER_BINDING:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_VERT_BUFFER_BIND;
		break;

	//    params returns a single value, the name of the buffer object
	//    currently bound to the target GL_ELEMENT_ARRAY_BUFFER. If no buffer object
	//    is bound to this target, 0 is returned.  The initial value is 0.
	//    See glBindBuffer.
	case GL_ELEMENT_ARRAY_BUFFER_BINDING:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_ELEM_BUFFER_BIND;
		break;

	//    params returns a single value, the name of the currently bound
	//    framebuffer. The initial value is 0, indicating the default framebuffer.
	//    See glBindFramebuffer.
	case GL_FRAMEBUFFER_BINDING:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_FRAME_BUFFER_BIND;
		break;

	//    params returns one value,
	//    a symbolic constant indicating whether clockwise or counterclockwise
	//    polygon winding is treated as front-facing. The initial value is
	//    GL_CCW.
	//    See glFrontFace.
	case GL_FRONT_FACE:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_FRONT_FACE;
		break;

	//    params returns one value,
	//    a symbolic constant indicating the mode of the mipmap generation filtering
	//    hint. The initial value is GL_DONT_CARE.
	//    See glHint.
	case GL_GENERATE_MIPMAP_HINT:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_HINT;
		break;

	//    params returns one value, the format
	//    chosen by the implementation in which pixels may be read from the
	//    color buffer of the currently bound framebuffer in conjunction with
	//    GL_IMPLEMENTATION_COLOR_READ_TYPE.
	//    In addition
	//    to this implementation-dependent format/type pair, format 
	//    GL_RGBA in conjunction with type 
	//    GL_UNSIGNED_BYTE is always allowed by every
	//    implementation, regardless of the currently bound render surface.
	//    See glReadPixels.
	case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
		break;

	//    params returns one value, the type
	//    chosen by the implementation with which pixels may be read from the
	//    color buffer of the currently bound framebuffer in conjunction with
	//    GL_IMPLEMENTATION_COLOR_READ_FORMAT.
	//    In addition
	//    to this implementation-dependent format/type pair, format 
	//    GL_RGBA in conjunction with type 
	//    GL_UNSIGNED_BYTE is always allowed by every
	//    implementation, regardless of the currently bound render surface.
	//    See glReadPixels.
	case GL_IMPLEMENTATION_COLOR_READ_TYPE:
		break;

	//    params returns one value,
	//    the line width as specified with glLineWidth. The initial value is 1.
	case GL_LINE_WIDTH:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns one value, the maximum supported texture image units that 
	//    can be used to access texture maps from the vertex shader and the fragment processor combined. 
	//    If both the vertex shader and the fragment processing stage access the same texture image
	//    unit, then that counts as using two texture image units against this limit.
	//    The value must be at least 8.
	//    See glActiveTexture.
	case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
	//    params returns one value.
	//    The value gives a rough estimate of the largest cube-map texture that
	//    the GL can handle. The value must be at least 16.
	//    See glTexImage2D.
	case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
	//    params returns one value,
	//    the maximum number of four-element floating-point, integer, or boolean vectors that can be held 
	//    in uniform variable storage for a fragment shader. The value must be at least 16.
	//    See glUniform.
	case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
	//    params returns one value.
	//    The value indicates the largest renderbuffer width and height
	//    that the GL can handle. The value must be at least 1.
	//    See glRenderbufferStorage.
	case GL_MAX_RENDERBUFFER_SIZE:
	// params returns one value,
	// the maximum supported texture image units that 
	// can be used to access texture maps from the fragment shader. 
	// The value must be at least 8.
	// See glActiveTexture.
	case GL_MAX_TEXTURE_IMAGE_UNITS:
	//    params returns one value.
	//    The value gives a rough estimate of the largest texture that
	//    the GL can handle. The value must be at least 64.
	//    See glTexImage2D.
	case GL_MAX_TEXTURE_SIZE:
	//    params returns one value,
	//    the maximum number four-element floating-point vectors available for interpolating varying variables used by
	//    vertex and fragment shaders. Varying variables declared as matrices or arrays 
	//    will consume multiple interpolators. The value must be at least 8.
	case GL_MAX_VARYING_VECTORS:
	//    params returns one value,
	//    the maximum number of 4-component generic vertex attributes accessible to a vertex shader. 
	//    The value must be at least 8.
	//    See glVertexAttrib.
	case GL_MAX_VERTEX_ATTRIBS:
	//    params returns one value, the maximum supported texture image units that 
	//    can be used to access texture maps from the vertex shader. The value may be 0.
	//    See glActiveTexture.
	case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
	//    params returns one value,
	//    the maximum number of four-element floating-point, integer, or boolean vectors that can be held 
	//    in uniform variable storage for a vertex shader. The value must be at least 128.
	//    See glUniform.
	case GL_MAX_VERTEX_UNIFORM_VECTORS:		
	//    params returns a single integer value indicating the number of available
	//    compressed texture formats.  The minimum value is 0.
	//    See glCompressedTexImage2D.
	case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
	//    params returns a single integer value indicating the number of available
	//    shader binary formats.  The minimum value is 0.
	//    See glShaderBinary.
	case GL_NUM_SHADER_BINARY_FORMATS:
	//    params returns one value,
	//    the byte alignment used for writing pixel data to memory. The initial
	//    value is 4.
	//    See glPixelStorei.
	case GL_PACK_ALIGNMENT:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns one value,
	//    the scaling factor used to determine the variable offset that is added
	//    to the depth value of each fragment generated when a polygon is
	//    rasterized. The initial value is 0.
	//    See glPolygonOffset.
	case GL_POLYGON_OFFSET_FACTOR:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns a single boolean value indicating whether polygon offset
	//    is enabled for polygons in fill mode. The initial value is GL_FALSE.
	//    See glPolygonOffset.
	case GL_POLYGON_OFFSET_FILL:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns one value.
	//    This value is multiplied by an implementation-specific value and then
	//    added to the depth value of each fragment
	//    generated when a polygon is rasterized. The initial value is 0.
	//    See glPolygonOffset.
	case GL_POLYGON_OFFSET_UNITS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns a single value, the name of the currently bound
	//    renderbuffer. The initial value is 0, indicating no renderbuffer is bound.
	//    See glBindRenderbuffer.
	case GL_RENDERBUFFER_BINDING:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_RENDER_BUFFER_BIND;
		break;

	//    params returns a single boolean value indicating if the 
	//    fragment coverage value should be ANDed with a temporary coverage value based
	//    on the fragment's alpha value. The initial value is GL_FALSE.
	//    See glSampleCoverage.
	case GL_SAMPLE_ALPHA_TO_COVERAGE:
	//    params returns a single boolean value indicating if the 
	//    fragment coverage value should be ANDed with a temporary coverage value based
	//    on the current sample coverage value. The initial value is GL_FALSE.
	//    See glSampleCoverage.
	case GL_SAMPLE_COVERAGE:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns a single integer value indicating the number of sample buffers
	//    associated with the currently bound framebuffer.
	//    See glSampleCoverage.
	case GL_SAMPLE_BUFFERS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns a single boolean value indicating if the temporary
	//    coverage value should be inverted.
	//    See glSampleCoverage.
	case GL_SAMPLE_COVERAGE_INVERT:
		//glSampleCoverage(value, invert);
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_SAMPLE_COVERAGE;
		break;

	//    params returns a single positive floating-point value indicating the
	//    current sample coverage value.
	//    See glSampleCoverage.
	case GL_SAMPLE_COVERAGE_VALUE:
		count = 1;
		type = FG_GFX_FLOAT;
		paramType = FG_GFX_PARAM_SAMPLE_COVERAGE;
		break;

	//    params returns a single integer value 
	//    indicating the coverage mask size of the currently bound framebuffer.
	//    See glSampleCoverage.
	case GL_SAMPLES:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns two values:
	//    the maximum supported width and height of the viewport.
	//    These must be at least as large as the visible dimensions of the display
	//    being rendered to.
	//    See glViewport.
	case GL_MAX_VIEWPORT_DIMS:
		count = 2;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns four values:
	//    the x and y window coordinates of the scissor box,
	//    followed by its width and height. Initially the x and y
	//    window coordinates are both 0 and the width and height are set to the size of the window.
	//    See glScissor.
	case GL_SCISSOR_BOX:
		count = 4;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_SCISSOR;
		break;

	//    params returns a single boolean value indicating whether scissoring is
	//    enabled. The initial value is GL_FALSE.
	//    See glScissor.
	case GL_SCISSOR_TEST:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;

	//    params returns a list of symbolic
	//    constants of length GL_NUM_SHADER_BINARY_FORMATS 
	//    indicating which shader binary formats are available.
	//    See glShaderBinary.
	case GL_SHADER_BINARY_FORMATS:
		count = 1; // #FIXME
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT; // #FIXME
		break;

	//    params returns a single boolean value indicating whether a shader compiler
	//    is supported. GL_FALSE indicates that any call to
	//    glShaderSource, glCompileShader, or glReleaseShaderCompiler will result in a
	//    GL_INVALID_OPERATION error being generated.
	case GL_SHADER_COMPILER:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns one value,
	//    a symbolic constant indicating what function is used for back-facing polygons to compare the
	//    stencil reference value with the stencil buffer value. The initial value
	//    is GL_ALWAYS.
	//    See glStencilFuncSeparate.
	case GL_STENCIL_BACK_FUNC:
	//    params returns one value,
	//    the reference value that is compared with the contents of the stencil
	//    buffer for back-facing polygons. The initial value is 0.
	//    See glStencilFuncSeparate.
	case GL_STENCIL_BACK_REF:
	//    params returns one value,
	//    the mask that is used for back-facing polygons to mask both the stencil reference value and the
	//    stencil buffer value before they are compared. The initial value is all 1's.
	//    See glStencilFuncSeparate.
	case GL_STENCIL_BACK_VALUE_MASK:
		//void glStencilFuncSeparate(GLenum face,  GLenum func,  GLint ref,  GLuint mask);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_FUNC;
		break;
		
	//    params returns one value,
	//    a symbolic constant indicating what action is taken for back-facing polygons when the stencil
	//    test fails. The initial value is GL_KEEP.
	//    See glStencilOpSeparate.
	case GL_STENCIL_BACK_FAIL:
	//    params returns one value,
	//    a symbolic constant indicating what action is taken for back-facing polygons when the stencil
	//    test passes,
	//    but the depth test fails. The initial value is GL_KEEP.
	//    See glStencilOpSeparate.
	case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
	//    params returns one value,
	//    a symbolic constant indicating what action is taken for back-facing polygons when the stencil
	//    test passes and the depth test passes. The initial value is GL_KEEP.
	//    See glStencilOpSeparate.
	case GL_STENCIL_BACK_PASS_DEPTH_PASS:
		//void glStencilOpSeparate(GLenum face,  GLenum sfail,  GLenum dpfail,  GLenum dppass);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_OP;
		break;

	//    params returns one value,
	//    the mask that controls writing of the stencil bitplanes for back-facing polygons. The initial value
	//    is all 1's.
	//    See glStencilMaskSeparate.
	case GL_STENCIL_BACK_WRITEMASK:
		//void glStencilMaskSeparate(GLenum face,  GLuint mask);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_MASK;
		break;

	//    params returns one value,
	//    a symbolic constant indicating what function is used to compare the
	//    stencil reference value with the stencil buffer value for front-facing polygons and non-polygons.
	//    The initial value is GL_ALWAYS.
	//    See glStencilFunc and
	//    glStencilFuncSeparate.
	case GL_STENCIL_FUNC: // FRONT
	//    params returns one value,
	//    the reference value that is compared with the contents of the stencil
	//    buffer for front-facing polygons and non-polygons.
	//    The initial value is 0.
	//    See glStencilFunc and
	//    glStencilFuncSeparate.
	case GL_STENCIL_REF: // FRONT
	//    params returns one value,
	//    the mask that is used to mask both the stencil reference value and the
	//    stencil buffer value before they are compared for front-facing polygons and non-polygons.
	//    The initial value is all 1's.
	//    See glStencilFunc and
	//    glStencilFuncSeparate.
	case GL_STENCIL_VALUE_MASK: // FRONT
		//void glStencilFunc(GLenum func,  GLint ref,  GLuint mask);
		//void glStencilFuncSeparate(GLenum face,  GLenum func,  GLint ref,  GLuint mask);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_FUNC;
		break;

	//    params returns one value,
	//    a symbolic constant indicating what action is taken when the stencil
	//    test fails for front-facing polygons and non-polygons. 
	//    The initial value is GL_KEEP.
	//    See glStencilOp and
	//    glStencilOpSeparate.
	case GL_STENCIL_FAIL: // FRONT
	//    params returns one value,
	//    a symbolic constant indicating what action is taken when the stencil
	//    test passes, but the depth test fails for front-facing polygons and non-polygons. 
	//    The initial value is GL_KEEP.
	//    See glStencilOp and
	//    glStencilOpSeparate.
	case GL_STENCIL_PASS_DEPTH_FAIL: // FRONT
	//    params returns one value,
	//    a symbolic constant indicating what action is taken when the stencil
	//    test passes and the depth test passes for front-facing polygons and non-polygons. 
	//    The initial value is GL_KEEP.
	//    See glStencilOp and
	//    glStencilOpSeparate.
	case GL_STENCIL_PASS_DEPTH_PASS: // FRONT
		//void glStencilOp(GLenum sfail,  GLenum dpfail,  GLenum dppass);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_OP;
		break;

	//    params returns one value,
	//    the mask that controls writing of the stencil bitplanes for front-facing polygons and non-polygons.
	//    The initial value is all 1's.
	//    See glStencilMask and
	//    glStencilMaskSeparate.
	case GL_STENCIL_WRITEMASK: // FRONT
		//void glStencilMask(GLuint mask);
		//void glStencilMaskSeparate(GLenum face,  GLuint mask);
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_STENCIL_MASK;
		break;

	//    params returns a single boolean value indicating whether stencil testing
	//    of fragments is enabled. The initial value is GL_FALSE.
	//    See glStencilFunc and glStencilOp.
	case GL_STENCIL_TEST:
		count = 1;
		type = FG_GFX_BOOL;
		paramType = FG_GFX_PARAM_BOOL;
		break;

	//    params returns one value,
	//    the number of bitplanes in the stencil buffer of the
	//    currently bound framebuffer.
	case GL_STENCIL_BITS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns one value,
	//    the index to which the stencil bitplanes are cleared. The initial value is 0.
	//    See glClearStencil.
	case GL_STENCIL_CLEAR_VALUE:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_CLEAR_STENCIL;
		break;

	//    params returns one value,
	//    an estimate of the number of bits of subpixel resolution that are used to
	//    position rasterized geometry in window coordinates. The value must be at least 4.
	case GL_SUBPIXEL_BITS:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns a single value, the name of the texture
	//    currently bound to the target GL_TEXTURE_2D for the active multitexture unit. The initial value is 0.
	//    See glBindTexture.
	case GL_TEXTURE_BINDING_2D:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_TEXTURE_2D;
		break;

	//    params returns a single value, the name of the texture
	//    currently bound to the target GL_TEXTURE_CUBE_MAP for the active multitexture unit. The initial value is 0.
	//    See glBindTexture.
	case GL_TEXTURE_BINDING_CUBE_MAP:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_TEXTURE_3D;
		break;

	//    params returns one value,
	//    the byte alignment used for reading pixel data from memory. The initial
	//    value is 4.
	//    See glPixelStorei.
	case GL_UNPACK_ALIGNMENT:
		count = 1;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_INT;
		break;

	//    params returns four values:
	//    the x and y window coordinates of the viewport,
	//    followed by its width and height. Initially the x and y
	//    window coordinates are both set to 0, and the width and height are set to
	//	  the width and height of the window into which the GL will do its rendering.
	//    See glViewport.
	case GL_VIEWPORT:
		count = 4;
		type = FG_GFX_INT;
		paramType = FG_GFX_PARAM_VIEWPORT;
		break;
	};
}

/*
 *
 */
fgBool fgGfxContextParam::update(void)
{
	if(this->paramType == FG_GFX_PARAM_INVALID)
		return FG_FALSE;
	fgBool status = FG_TRUE;
	switch(this->paramType) 
	{
	case FG_GFX_PARAM_BOOL:
		if(boolVal)
			glEnable(pname);
		else
			glDisable(pname);
		break;
	case FG_GFX_PARAM_FLOAT:
		// NOPE
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_INT:
		// NOPE
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_ATTRIB:
		// #FIXME
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_BLEND_FUNC:
		// MULTI VALUE
		//glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
		//glBlendFunc(sfactor, dfactor);
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_BLEND_EQ:
		// MULTI VALUE
		//glBlendEquation(intVal);
		//glBlendEquationSeparate(intVal);
		break;
	case FG_GFX_PARAM_BLEND_COLOR:
		glBlendColor(floats[0], floats[1], floats[2], floats[3]);
		break;
	case FG_GFX_PARAM_VIEWPORT:
		glViewport(ints[0], ints[1], ints[2], ints[3]);
		break;
	case FG_GFX_PARAM_SCISSOR:
		glScissor(ints[0], ints[1], ints[2], ints[3]);
		break;
	case FG_GFX_PARAM_TEXTURE_2D:
		glBindTexture(GL_TEXTURE_2D, (fgGFXuint)intVal);
		fgGLError("glBindTexture");
		break;
	case FG_GFX_PARAM_TEXTURE_3D:
		glBindTexture(GL_TEXTURE_CUBE_MAP, (fgGFXuint)intVal);
		fgGLError("glBindTexture");
		break;
	case FG_GFX_PARAM_TEXTURE:
		glActiveTexture(intVal);
		fgGLError("glActiveTexture");
		break;
	case FG_GFX_PARAM_VERT_BUFFER_BIND:
		glBindBuffer(GL_ARRAY_BUFFER, intVal);
		fgGLError("glBindBuffer");
		break;
	case FG_GFX_PARAM_ELEM_BUFFER_BIND:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, intVal);
		fgGLError("glBindBuffer");
		break;
	case FG_GFX_PARAM_CLEAR_DEPTH:
		// #FIXME / ALIAS glClearDepth/f
		#if defined FG_USING_OPENGL_ES
			glClearDepthf(floatVal);
		#else
			glClearDepth(floatVal);
		#endif
		break;
	case FG_GFX_PARAM_CLEAR_COLOR:
		glClearColor(floats[0], floats[1], floats[2], floats[3]);
		break;
	case FG_GFX_PARAM_COLOR_MASK:
		glColorMask(booleans[0], booleans[1], booleans[2], booleans[3]);
		break;
	case FG_GFX_PARAM_FRONT_FACE:
		glFrontFace(intVal);
		break;
	case FG_GFX_PARAM_CULL_FACE:
		glCullFace(intVal);
		break;
	case FG_GFX_PARAM_PROGRAM:
		glUseProgram((fgGFXuint)intVal);
		fgGLError("glUseProgram");
		break;
	case FG_GFX_PARAM_DEPTH_FUNC:
		glDepthFunc(intVal);
		break;
	case FG_GFX_PARAM_DEPTH_RANGE:
		glDepthRangef(floats[0], floats[1]);
		break;
	case FG_GFX_PARAM_DEPTH_MASK:
		glDepthMask(boolVal);
		break;
	case FG_GFX_PARAM_FRAME_BUFFER_BIND:
		glBindFramebuffer(GL_FRAMEBUFFER, intVal);
		fgGLError("glBindFramebuffer");
		break;
	case FG_GFX_PARAM_RENDER_BUFFER_BIND:
		glBindRenderbuffer(GL_RENDERBUFFER, intVal);
		fgGLError("glBindRenderbuffer");
		break;
	case FG_GFX_PARAM_HINT:
		glHint(pname, intVal);
		fgGLError("glHint");
		break;
	case FG_GFX_PARAM_SAMPLE_COVERAGE:
		// MULTI VALUE
		//glSampleCoverage(value, invert);
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_STENCIL_FUNC:
		// MULTI VALUE
		//glStencilFunc(func, mask);
		//glStencilFuncSeparate(face, func, mask);
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_STENCIL_OP:
		// MULTI VALUE
		//glStencilOp(fail, zfail, zpass);
		//glStencilOpSeparate(face, fail, zfail, zpass);
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_STENCIL_MASK:
		// MULTI VALUE
		//glStencilMask(mask);
		//glStencilMaskSeparate(face, mask);
		status = FG_FALSE;
		break;
	case FG_GFX_PARAM_CLEAR_STENCIL:
		glClearStencil(intVal);
		break;
	default:
		status = FG_FALSE;
		break;
	};
	return status;
}

/*
 *
 */
fgGfxContext::fgGfxContext() : 
	m_viewportAreaQ(0),
	m_scissorAreaQ(0),
	m_attribMask(0),
	m_boundTexture(0)
{
	m_params[GL_ACTIVE_TEXTURE]				= fgGfxContextParam(GL_ACTIVE_TEXTURE);
	m_params[GL_ALIASED_LINE_WIDTH_RANGE]	= fgGfxContextParam(GL_ALIASED_LINE_WIDTH_RANGE);
	m_params[GL_ALIASED_POINT_SIZE_RANGE]	= fgGfxContextParam(GL_ALIASED_POINT_SIZE_RANGE);
	m_params[GL_ALPHA_BITS]					= fgGfxContextParam(GL_ALPHA_BITS);
	m_params[GL_BLEND]						= fgGfxContextParam(GL_BLEND);
	m_params[GL_BLEND_COLOR]				= fgGfxContextParam(GL_BLEND_COLOR);
	m_params[GL_BLEND_DST_ALPHA]			= fgGfxContextParam(GL_BLEND_DST_ALPHA);
	m_params[GL_BLEND_DST_RGB]				= fgGfxContextParam(GL_BLEND_DST_RGB);
	m_params[GL_BLEND_SRC_ALPHA]			= fgGfxContextParam(GL_BLEND_SRC_ALPHA);
	m_params[GL_BLEND_SRC_RGB]				= fgGfxContextParam(GL_BLEND_SRC_RGB);
	m_params[GL_BLEND_EQUATION_ALPHA]		= fgGfxContextParam(GL_BLEND_EQUATION_ALPHA);
	m_params[GL_BLEND_EQUATION_RGB]			= fgGfxContextParam(GL_BLEND_EQUATION_RGB);
	m_params[GL_RED_BITS]					= fgGfxContextParam(GL_RED_BITS);
	m_params[GL_GREEN_BITS]					= fgGfxContextParam(GL_GREEN_BITS);
	m_params[GL_BLUE_BITS]					= fgGfxContextParam(GL_BLUE_BITS);
	m_params[GL_DEPTH_BITS]					= fgGfxContextParam(GL_DEPTH_BITS);
	m_params[GL_COLOR_CLEAR_VALUE]			= fgGfxContextParam(GL_COLOR_CLEAR_VALUE);
	m_params[GL_COLOR_WRITEMASK]			= fgGfxContextParam(GL_COLOR_WRITEMASK);
	m_params[GL_COMPRESSED_TEXTURE_FORMATS] = fgGfxContextParam(GL_COMPRESSED_TEXTURE_FORMATS);
	m_params[GL_CULL_FACE]					= fgGfxContextParam(GL_CULL_FACE);
	m_params[GL_CULL_FACE_MODE]				= fgGfxContextParam(GL_CULL_FACE_MODE);
	m_params[GL_CURRENT_PROGRAM]			= fgGfxContextParam(GL_CURRENT_PROGRAM);
	m_params[GL_DEPTH_CLEAR_VALUE]			= fgGfxContextParam(GL_DEPTH_CLEAR_VALUE);
	m_params[GL_DEPTH_FUNC]					= fgGfxContextParam(GL_DEPTH_FUNC);
	m_params[GL_DEPTH_RANGE]				= fgGfxContextParam(GL_DEPTH_RANGE);
	m_params[GL_DEPTH_TEST]					= fgGfxContextParam(GL_DEPTH_TEST);
	m_params[GL_DEPTH_WRITEMASK]			= fgGfxContextParam(GL_DEPTH_WRITEMASK);
	m_params[GL_DITHER]						= fgGfxContextParam(GL_DITHER);
	m_params[GL_ARRAY_BUFFER_BINDING]		= fgGfxContextParam(GL_ARRAY_BUFFER_BINDING);
	m_params[GL_ELEMENT_ARRAY_BUFFER_BINDING] = fgGfxContextParam(GL_ELEMENT_ARRAY_BUFFER_BINDING);
	m_params[GL_FRAMEBUFFER_BINDING]		= fgGfxContextParam(GL_FRAMEBUFFER_BINDING);
	m_params[GL_FRONT_FACE]					= fgGfxContextParam(GL_FRONT_FACE);
	m_params[GL_GENERATE_MIPMAP_HINT]		= fgGfxContextParam(GL_GENERATE_MIPMAP_HINT);
	m_params[GL_IMPLEMENTATION_COLOR_READ_FORMAT] = fgGfxContextParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
	m_params[GL_IMPLEMENTATION_COLOR_READ_TYPE] = fgGfxContextParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
	m_params[GL_LINE_WIDTH]					= fgGfxContextParam(GL_LINE_WIDTH);
	m_params[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS] = fgGfxContextParam(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	m_params[GL_MAX_CUBE_MAP_TEXTURE_SIZE]	= fgGfxContextParam(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
	m_params[GL_MAX_FRAGMENT_UNIFORM_VECTORS] = fgGfxContextParam(GL_MAX_FRAGMENT_UNIFORM_VECTORS);
	m_params[GL_MAX_RENDERBUFFER_SIZE]		= fgGfxContextParam(GL_MAX_RENDERBUFFER_SIZE);
	m_params[GL_MAX_TEXTURE_IMAGE_UNITS]	= fgGfxContextParam(GL_MAX_TEXTURE_IMAGE_UNITS);
	m_params[GL_MAX_TEXTURE_SIZE]			= fgGfxContextParam(GL_MAX_TEXTURE_SIZE);
	m_params[GL_MAX_VARYING_VECTORS]		= fgGfxContextParam(GL_MAX_VARYING_VECTORS);
	m_params[GL_MAX_VERTEX_ATTRIBS]			= fgGfxContextParam(GL_MAX_VERTEX_ATTRIBS);
	m_params[GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS] = fgGfxContextParam(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	m_params[GL_MAX_VERTEX_UNIFORM_VECTORS] = fgGfxContextParam(GL_MAX_VERTEX_UNIFORM_VECTORS);
	m_params[GL_NUM_COMPRESSED_TEXTURE_FORMATS] = fgGfxContextParam(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
	m_params[GL_NUM_SHADER_BINARY_FORMATS]	= fgGfxContextParam(GL_NUM_SHADER_BINARY_FORMATS);
	m_params[GL_PACK_ALIGNMENT]				= fgGfxContextParam(GL_PACK_ALIGNMENT);
	m_params[GL_POLYGON_OFFSET_FACTOR]		= fgGfxContextParam(GL_POLYGON_OFFSET_FACTOR);
	m_params[GL_POLYGON_OFFSET_FILL]		= fgGfxContextParam(GL_POLYGON_OFFSET_FILL);
	m_params[GL_POLYGON_OFFSET_UNITS]		= fgGfxContextParam(GL_POLYGON_OFFSET_UNITS);
	m_params[GL_RENDERBUFFER_BINDING]		= fgGfxContextParam(GL_RENDERBUFFER_BINDING);
	m_params[GL_SAMPLE_ALPHA_TO_COVERAGE]	= fgGfxContextParam(GL_SAMPLE_ALPHA_TO_COVERAGE);
	m_params[GL_SAMPLE_COVERAGE]			= fgGfxContextParam(GL_SAMPLE_COVERAGE);
	m_params[GL_SAMPLE_BUFFERS]				= fgGfxContextParam(GL_SAMPLE_BUFFERS);
	m_params[GL_SAMPLE_COVERAGE_INVERT]		= fgGfxContextParam(GL_SAMPLE_COVERAGE_INVERT);
	m_params[GL_SAMPLE_COVERAGE_VALUE]		= fgGfxContextParam(GL_SAMPLE_COVERAGE_VALUE);
	m_params[GL_SAMPLES]					= fgGfxContextParam(GL_SAMPLES);
	m_params[GL_MAX_VIEWPORT_DIMS]			= fgGfxContextParam(GL_MAX_VIEWPORT_DIMS);
	m_params[GL_SCISSOR_BOX]				= fgGfxContextParam(GL_SCISSOR_BOX);
	m_params[GL_SCISSOR_TEST]				= fgGfxContextParam(GL_SCISSOR_TEST);
	m_params[GL_SHADER_BINARY_FORMATS]		= fgGfxContextParam(GL_SHADER_BINARY_FORMATS);
	m_params[GL_SHADER_COMPILER]			= fgGfxContextParam(GL_SHADER_COMPILER);
	m_params[GL_STENCIL_BACK_FUNC]			= fgGfxContextParam(GL_STENCIL_BACK_FUNC);
	m_params[GL_STENCIL_BACK_REF]			= fgGfxContextParam(GL_STENCIL_BACK_REF);
	m_params[GL_STENCIL_BACK_VALUE_MASK]	= fgGfxContextParam(GL_STENCIL_BACK_VALUE_MASK);
	m_params[GL_STENCIL_BACK_FAIL]			= fgGfxContextParam(GL_STENCIL_BACK_FAIL);
	m_params[GL_STENCIL_BACK_PASS_DEPTH_FAIL] = fgGfxContextParam(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
	m_params[GL_STENCIL_BACK_PASS_DEPTH_PASS] = fgGfxContextParam(GL_STENCIL_BACK_PASS_DEPTH_PASS);
	m_params[GL_STENCIL_BACK_WRITEMASK]		= fgGfxContextParam(GL_STENCIL_BACK_WRITEMASK);
	m_params[GL_STENCIL_FUNC]				= fgGfxContextParam(GL_STENCIL_FUNC);
	m_params[GL_STENCIL_REF]				= fgGfxContextParam(GL_STENCIL_REF);
	m_params[GL_STENCIL_VALUE_MASK]			= fgGfxContextParam(GL_STENCIL_VALUE_MASK);
	m_params[GL_STENCIL_FAIL]				= fgGfxContextParam(GL_STENCIL_FAIL);
	m_params[GL_STENCIL_PASS_DEPTH_FAIL]	= fgGfxContextParam(GL_STENCIL_PASS_DEPTH_FAIL);
	m_params[GL_STENCIL_PASS_DEPTH_PASS]	= fgGfxContextParam(GL_STENCIL_PASS_DEPTH_PASS);
	m_params[GL_STENCIL_WRITEMASK]			= fgGfxContextParam(GL_STENCIL_WRITEMASK);
	m_params[GL_STENCIL_TEST]				= fgGfxContextParam(GL_STENCIL_TEST);
	m_params[GL_STENCIL_BITS]				= fgGfxContextParam(GL_STENCIL_BITS);
	m_params[GL_STENCIL_CLEAR_VALUE]		= fgGfxContextParam(GL_STENCIL_CLEAR_VALUE);
	m_params[GL_SUBPIXEL_BITS]				= fgGfxContextParam(GL_SUBPIXEL_BITS);
	m_params[GL_TEXTURE_BINDING_2D]			= fgGfxContextParam(GL_TEXTURE_BINDING_2D);
	m_params[GL_TEXTURE_BINDING_CUBE_MAP]	= fgGfxContextParam(GL_TEXTURE_BINDING_CUBE_MAP);
	m_params[GL_UNPACK_ALIGNMENT]			= fgGfxContextParam(GL_UNPACK_ALIGNMENT);
	m_params[GL_VIEWPORT]					= fgGfxContextParam(GL_VIEWPORT);

	memset(m_attrInfo, 0, sizeof(m_attrInfo));
}

/*
 *
 */
fgGfxContext::~fgGfxContext()
{
	m_params.clear();
}

/*
 *
 */
void fgGfxContext::initialize(void)
{
	gfxParamMapItor end = m_params.end(), itor = m_params.begin();
	for(;itor!=end;itor++) {
		fgGfxContextParam &param = itor->second;

		param.load();
	}
}

/*
 *
 */
fgGfxContextParam& fgGfxContext::getParam(const fgGFXenum pname)
{
	return m_params[pname];
}

/*
 *
 */
void fgGfxContext::enable(const fgGFXenum cap)
{
	m_params[cap].set((fgGFXboolean)FG_GFX_TRUE);
}

/*
 *
 */
void fgGfxContext::disable(const fgGFXenum cap)
{
	m_params[cap].set((fgGFXboolean)FG_GFX_FALSE);
}

/*
 *
 */
fgBool fgGfxContext::isEnabled(const fgGFXenum pname)
{
	return m_params[pname].boolVal;
}

/*
 *
 */
fgBool fgGfxContext::isDisabled(const fgGFXenum pname)
{
	return !m_params[pname].boolVal;
}

/*
 *
 */
void fgGfxContext::bindBuffer(const fgGFXenum target, const fgGFXuint buffer)
{
	if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
		m_params[GL_ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
	} else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
		m_params[GL_ELEMENT_ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
	}
}

/*
 *
 */
fgGFXuint fgGfxContext::boundBuffer(const fgGFXenum target)
{
	if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
		return m_params[GL_ARRAY_BUFFER_BINDING];
	} else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
		return m_params[GL_ELEMENT_ARRAY_BUFFER_BINDING];
	}
	return 0;
}

/*
 *
 */
fgGFXuint fgGfxContext::boundTexture(void) const
{
	return m_boundTexture;
}

/*
 *
 */
fgGFXuint fgGfxContext::activeTexture(void)
{
	return m_params[GL_ACTIVE_TEXTURE];
}

/*
 *
 */
void fgGfxContext::activeTexture(const fgGFXenum texture)
{
	m_params[GL_ACTIVE_TEXTURE].set((fgGFXint)texture);
}

/*
 *
 */
void fgGfxContext::bindTexture2D(const fgGFXuint texID)
{
	m_params[GL_TEXTURE_BINDING_2D].set((fgGFXint)texID);
	m_boundTexture = texID;
}

/*
 *
 */
void fgGfxContext::bindTexture3D(const fgGFXuint texID)
{
	m_params[GL_TEXTURE_BINDING_CUBE_MAP].set((fgGFXint)texID);
	m_boundTexture = texID;
}

/*
 *
 */
void fgGfxContext::blendEquation(const fgGFXenum mode)
{
	fgGfxContextParam& modeRGB = m_params[GL_BLEND_EQUATION_RGB];
	fgGfxContextParam& modeAlpha = m_params[GL_BLEND_EQUATION_ALPHA];
	if(modeRGB.intVal != mode || modeAlpha.intVal != mode) {
		modeAlpha = modeRGB = mode;
		glBlendEquationSeparate(mode, mode);
	}
}

/*
 *
 */
void fgGfxContext::blendFunc(const fgGFXenum sfactor, const fgGFXenum dfactor)
{
	fgGfxContextParam& srcRGB = m_params[GL_BLEND_SRC_RGB];
	fgGfxContextParam& dstRGB = m_params[GL_BLEND_DST_RGB];
	fgGfxContextParam& srcAlpha = m_params[GL_BLEND_SRC_ALPHA];
	fgGfxContextParam& dstAlpha = m_params[GL_BLEND_DST_ALPHA];

	if(srcRGB.intVal != sfactor ||
		srcAlpha.intVal != sfactor ||
		dstRGB.intVal != dfactor ||
		dstAlpha.intVal != dfactor) {
		glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
		srcRGB.intVal = sfactor;
		dstRGB.intVal = dfactor;
		srcAlpha.intVal = sfactor;
		dstAlpha.intVal = dfactor;
	}
}

/*
 *
 */
void fgGfxContext::blendFunc(const fgGFXenum srcRGB, const fgGFXenum dstRGB, const fgGFXenum srcAlpha, const fgGFXenum dstAlpha)
{
	fgGfxContextParam& srcRGBparam = m_params[GL_BLEND_SRC_RGB];
	fgGfxContextParam& dstRGBparam = m_params[GL_BLEND_DST_RGB];
	fgGfxContextParam& srcAlphaparam = m_params[GL_BLEND_SRC_ALPHA];
	fgGfxContextParam& dstAlphaparam = m_params[GL_BLEND_DST_ALPHA];
	if(srcRGBparam.intVal != srcRGB ||
		srcAlphaparam.intVal != srcAlpha ||
		dstRGBparam.intVal != dstRGB ||
		dstAlphaparam.intVal != dstAlpha) {
		glBlendFuncSeparate(srcRGBparam, dstRGBparam, srcAlphaparam, dstAlphaparam);
		srcRGBparam.intVal = srcRGB;
		dstRGBparam.intVal = dstRGB;
		srcAlphaparam.intVal = srcAlpha;
		dstAlphaparam.intVal = dstAlpha;
	}
}


/*
 *
 */
void fgGfxContext::useProgram(const fgGFXuint program)
{
	if(m_params[GL_CURRENT_PROGRAM].intVal != program) {
		m_params[GL_CURRENT_PROGRAM].set((fgGFXint)program);
	}
}

/*
 *
 */
fgGFXuint fgGfxContext::activeProgram(void)
{
	return m_params[GL_CURRENT_PROGRAM];
}

/*
 *
 */
void fgGfxContext::viewport(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height)
{
	fgGFXuint areaQ = x*y+width*height;
	if(areaQ != m_viewportAreaQ) {
		m_viewportAreaQ = areaQ;
		m_params[GL_VIEWPORT].set(x, y, width, height);;
	}
}

/*
 *
 */
void fgGfxContext::viewport(const fgVector2i& pos, const fgVector2i& size)
{
	viewport(pos.x, pos.y, size.x, size.y);
}

/*
 *
 */
void fgGfxContext::viewport(const fgVector4i& dimensions)
{
	viewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

/*
 *
 */
void fgGfxContext::scissor(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height)
{
	fgGFXuint areaQ = x*y+width*height;
	if(areaQ != m_scissorAreaQ) {
		m_scissorAreaQ = areaQ;
		m_params[GL_SCISSOR_BOX].set(x, y, width, height);;
	}
}

/*
 *
 */
void fgGfxContext::scissor(const fgVector2i& pos, const fgVector2i& size)
{
	scissor(pos.x, pos.y, size.x, size.y);
}

/*
 *
 */
void fgGfxContext::scissor(const fgVector4i& dimensions)
{
	scissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

/*
 *
 */
void fgGfxContext::setScissorTest(const fgBool toggle)
{
	m_params[GL_SCISSOR_TEST].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setDepthTest(const fgBool toggle)
{
	m_params[GL_DEPTH_TEST].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setCullFace(const fgBool toggle)
{
	m_params[GL_CULL_FACE].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setBlend(const fgBool toggle)
{
	m_params[GL_BLEND].set((fgGFXboolean)toggle);
}

/*
*
*/
void fgGfxContext::frontFace(const fgGFXenum mode)
{
	m_params[GL_FRONT_FACE].set((fgGFXint)mode);
}

/*
*
*/
void fgGfxContext::cullFace(const fgGFXenum mode)
{
	m_params[GL_CULL_FACE_MODE].set((fgGFXint)mode);
}

/*
 *
 */
void fgGfxContext::depthFunc(const fgGFXenum func)
{
	m_params[GL_DEPTH_FUNC].set((fgGFXint)func);
}

/*
 *
 */
void fgGfxContext::clearDepth(const fgGFXfloat depth)
{
	m_params[GL_DEPTH_CLEAR_VALUE].set(depth);
}

/*
 *
 */
void fgGfxContext::clearColor(const fgGFXfloat red, const fgGFXfloat green, const fgGFXfloat blue, const fgGFXfloat alpha)
{
	m_params[GL_COLOR_CLEAR_VALUE].set(red, green, blue, alpha);
}

/*
 *
 */
void fgGfxContext::clearStencil(const fgGFXint s)
{
	m_params[GL_STENCIL_CLEAR_VALUE].set(s);
}

/*
 *
 */
fgGFXuint fgGfxContext::activeVertexAttribArrayMask(void) const
{
	return m_attribMask;
}

/*
 *
 */
fgBool fgGfxContext::isVertexAttribArrayActive(const fgGFXuint index) const
{
	return m_attrInfo[index].enabled;
}

/*
 *
 */
void fgGfxContext::updateAttribMask(const fgGFXuint index)
{
	if(index == FG_GFX_ATTRIB_POS_LOCATION) {
		m_attribMask ^= FG_GFX_POSITION_BIT;
	} else if(index == FG_GFX_ATTRIB_NORM_LOCATION) {
		m_attribMask ^= FG_GFX_NORMAL_BIT;
	} else if(index == FG_GFX_ATTRIB_UVS_LOCATION) {
		m_attribMask ^= FG_GFX_UVS_BIT;
	} else if(index == FG_GFX_ATTRIB_COLOR_LOCATION) {
		m_attribMask ^= FG_GFX_COLOR_BIT;
	} else if(index == FG_GFX_ATTRIB_TANGENT_LOCATION) {
		m_attribMask ^= FG_GFX_TANGENT_BIT;
	}
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
 */
void fgGfxContext::enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask)
{
	if(!m_attrInfo[index].enabled) {
		m_attrInfo[index].enabled = FG_TRUE;
		glEnableVertexAttribArray(index);
		if(updateMask)
			updateAttribMask(index);
	}
}

/*
 *
 */
void fgGfxContext::disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask)
{
	if(m_attrInfo[index].enabled) {
		m_attrInfo[index].enabled = FG_FALSE;
		glDisableVertexAttribArray(index);
		if(updateMask)
			updateAttribMask(index);
	}
}

/*
 *
 */
void fgGfxContext::enableVertexAttribArrayMask(const fgGFXuint mask)
{
	if(mask == m_attribMask)
		return;
	if(mask & FG_GFX_POSITION_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION, FG_FALSE);
	if(mask & FG_GFX_NORMAL_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION, FG_FALSE);
	if(mask & FG_GFX_UVS_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION, FG_FALSE);
	if(mask & FG_GFX_COLOR_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_COLOR_LOCATION, FG_FALSE);
	if(mask & FG_GFX_TANGENT_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_TANGENT_LOCATION, FG_FALSE);
	m_attribMask = mask;
}

/*
 *
 */
void fgGfxContext::disableVertexAttribArrayMask(const fgGFXuint mask)
{
	if(mask == m_attribMask)
		return;
	if(!(mask & FG_GFX_POSITION_BIT))
		disableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION, FG_FALSE);
	if(!(mask & FG_GFX_NORMAL_BIT))
		disableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION, FG_FALSE);
	if(!(mask & FG_GFX_UVS_BIT))
		disableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION, FG_FALSE);
	if(!(mask & FG_GFX_COLOR_BIT))
		disableVertexAttribArray(FG_GFX_ATTRIB_COLOR_LOCATION, FG_FALSE);
	if(!(mask & FG_GFX_TANGENT_BIT))
		disableVertexAttribArray(FG_GFX_ATTRIB_TANGENT_LOCATION, FG_FALSE);
	m_attribMask = mask;
}

/*
 *
 */
void fgGfxContext::diffVertexAttribArrayMask(const fgGFXuint mask)
{
	if(mask == m_attribMask)
		return;
	if(mask & FG_GFX_POSITION_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION, FG_FALSE);
	else
		disableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION, FG_FALSE);
	
	if(mask & FG_GFX_NORMAL_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION, FG_FALSE);
	else
		disableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION, FG_FALSE);
	
	if(mask & FG_GFX_UVS_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION, FG_FALSE);
	else
		disableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION, FG_FALSE);
	
	if(mask & FG_GFX_COLOR_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_COLOR_LOCATION, FG_FALSE);
	else
		disableVertexAttribArray(FG_GFX_ATTRIB_COLOR_LOCATION, FG_FALSE);
	
	if(mask & FG_GFX_TANGENT_BIT)
		enableVertexAttribArray(FG_GFX_ATTRIB_TANGENT_LOCATION, FG_FALSE);
	else
		disableVertexAttribArray(FG_GFX_ATTRIB_TANGENT_LOCATION, FG_FALSE);
	m_attribMask = mask;
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetVertexAttrib.xml
 */
fgGFXuint fgGfxContext::getVertexAttribBufferBinding(const fgGFXuint index)
{
	return m_attrInfo[index].bufferBind;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribSize(const fgGFXuint index)
{
	return m_attrInfo[index].size;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribStride(const fgGFXuint index)
{
	if(index >= 12)
		return 0;
	return m_attrInfo[index].stride;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribType(const fgGFXuint index)
{
	if(index >= 12)
		return 0;
	return m_attrInfo[index].type;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribNormalized(const fgGFXuint index)
{
	// #FIXME checks
	if(index >= 12)
		return 0;
	return m_attrInfo[index].normalized;
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
 */
void fgGfxContext::vertexAttribPointer(fgGFXuint index,
	fgGFXint size,
	fgGFXenum type, 
	fgGFXboolean normalized, 
	fgGFXsizei stride, 
	fgGFXvoid* ptr)
{
	if(index >= 12)
		return;
	// #FIXME
	// # index checks
	// # max attrib prop check
	// # mirror
	// # usage of main attrib array in other places
	//
	fgGfxAttrInfo &attr = m_attrInfo[index];
	attr.index = index;
	attr.size = size;
	attr.type = type;
	attr.normalized = normalized;
	attr.stride =  stride;
	attr.ptr = ptr;
	attr.bufferBind = m_params[GL_ARRAY_BUFFER_BINDING];
	glVertexAttribPointer(index, size, type, normalized, stride, ptr);
	fgGLError("glVertexAttribPointer"); // #FIXME
}
