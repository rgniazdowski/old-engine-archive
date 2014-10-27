/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXContext.h"
#include "Util/fgStrings.h"
#include "Util/fgMemory.h"

/*
 *
 */
void fgGfxContextParam::determineParamType(void) {
    count = 1;
    switch(this->pname) {
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
        default:
            break;
    };
}

/*
 *
 */
fgBool fgGfxContextParam::update(void) {
    if(this->paramType == FG_GFX_PARAM_INVALID)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    switch(this->paramType) {
        case FG_GFX_PARAM_BOOL:
            if(boolVal == FG_GFX_TRUE)
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
            glActiveTexture((fgGFXenum)intVal);
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
            glFrontFace((fgGFXenum)intVal);
            break;
        case FG_GFX_PARAM_CULL_FACE:
            glCullFace((fgGFXenum)intVal);
            break;
        case FG_GFX_PARAM_PROGRAM:
            glUseProgram((fgGFXuint)intVal);
            fgGLError("glUseProgram");
            break;
        case FG_GFX_PARAM_DEPTH_FUNC:
            glDepthFunc((fgGFXenum)intVal);
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
            glHint(pname, (fgGFXenum)intVal);
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
#if defined(FG_USING_SDL2)
fgGfxContext::fgGfxContext(SDL_Window *sdlWindow) :
#else

fgGfxContext::fgGfxContext() :
#endif
#if defined(FG_USING_SDL2)
m_GLContext(0),
m_sdlWindow(sdlWindow),
#endif
m_viewportAreaQ(0),
m_scissorAreaQ(0),
m_attribMask(0),
m_boundTexture(0),
m_SLVersion(FG_GFX_SHADING_LANGUAGE_INVALID),
m_init(FG_FALSE) {

#if defined(FG_USING_SDL2)
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // #FIXME seriously, this context should be created somewhere else, gfx Main ?
    m_GLContext = SDL_GL_CreateContext(m_sdlWindow);
    if(!m_GLContext) {
        FG_LOG::PrintError("GFX: Couldn't create GL context: '%s'", SDL_GetError());
        SDL_ClearError();
        // Failed so try again with least possible GL version
        FG_LOG::PrintInfo("GFX: Will try to create any kind of GL context...");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

        m_GLContext = SDL_GL_CreateContext(m_sdlWindow);
        if(!m_GLContext) {
            FG_LOG::PrintError("GFX: RETRY: Couldn't create GL context: '%s'", SDL_GetError());
            SDL_ClearError();
            return;
        }
    }
    int r, g, b, a, d, major, minor;
    SDL_GL_MakeCurrent(m_sdlWindow, m_GLContext);

    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &d);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);

    FG_LOG::PrintDebug("GFX: GL version %d.%d", major, minor);
    FG_LOG::PrintDebug("GFX: GL color buffer: red: %d, green: %d, blue: %d, alpha: %d, depth: %d,", r, g, b, a, d);

#if defined(FG_USING_GL_BINDING)
    FG_LOG::PrintDebug("Initializing GL bindings...");
    //    //glbinding::Binding::initialize((glbinding::ContextHandle)m_GLContext, true, true);
    glbinding::Binding::initialize();
#elif defined(FG_USING_OPENGL_GLEW)
    FG_LOG::PrintDebug("GFX: Initializing GLEW...");
    glewExperimental = FG_GFX_TRUE;
    fgGFXenum glewInitResult = glewInit();
    if(glewInitResult != GLEW_OK) {
        FG_LOG::PrintError("GFX: GLEW initialization error error '%s'", glewGetErrorString(glewInitResult));
        m_init = FG_FALSE;
        return;
    } else {
        FG_LOG::PrintDebug("GFX: GLEW init completed successfully.");
    }
    fgGFXenum errorCheckValue = fgGLError("glewInit");
    if(errorCheckValue != GL_NO_ERROR) {
        FG_LOG::PrintError("GFX: Context error, failed to initialize."); //, gluErrorString(errorCheckValue));
        m_init = FG_FALSE;
        return;
    }
    //glewIsSupported("GL_VERSION_3_0");
#endif

#endif
    FG_LOG::PrintDebug("GFX: Initializing GL parameter list...");
    m_params[(fgGFXuint)GL_ACTIVE_TEXTURE] = fgGfxContextParam(GL_ACTIVE_TEXTURE);
    m_params[(fgGFXuint)GL_ALIASED_LINE_WIDTH_RANGE] = fgGfxContextParam(GL_ALIASED_LINE_WIDTH_RANGE);
    m_params[(fgGFXuint)GL_ALIASED_POINT_SIZE_RANGE] = fgGfxContextParam(GL_ALIASED_POINT_SIZE_RANGE);
    m_params[(fgGFXuint)GL_ALPHA_BITS] = fgGfxContextParam(GL_ALPHA_BITS);
    m_params[(fgGFXuint)GL_BLEND] = fgGfxContextParam(GL_BLEND);
    m_params[(fgGFXuint)GL_BLEND_COLOR] = fgGfxContextParam(GL_BLEND_COLOR);
    m_params[(fgGFXuint)GL_BLEND_DST_ALPHA] = fgGfxContextParam(GL_BLEND_DST_ALPHA);
    m_params[(fgGFXuint)GL_BLEND_DST_RGB] = fgGfxContextParam(GL_BLEND_DST_RGB);
    m_params[(fgGFXuint)GL_BLEND_SRC_ALPHA] = fgGfxContextParam(GL_BLEND_SRC_ALPHA);
    m_params[(fgGFXuint)GL_BLEND_SRC_RGB] = fgGfxContextParam(GL_BLEND_SRC_RGB);
    m_params[(fgGFXuint)GL_BLEND_EQUATION_ALPHA] = fgGfxContextParam(GL_BLEND_EQUATION_ALPHA);
    m_params[(fgGFXuint)GL_BLEND_EQUATION_RGB] = fgGfxContextParam(GL_BLEND_EQUATION_RGB);
    m_params[(fgGFXuint)GL_RED_BITS] = fgGfxContextParam(GL_RED_BITS);
    m_params[(fgGFXuint)GL_GREEN_BITS] = fgGfxContextParam(GL_GREEN_BITS);
    m_params[(fgGFXuint)GL_BLUE_BITS] = fgGfxContextParam(GL_BLUE_BITS);
    m_params[(fgGFXuint)GL_DEPTH_BITS] = fgGfxContextParam(GL_DEPTH_BITS);
    m_params[(fgGFXuint)GL_COLOR_CLEAR_VALUE] = fgGfxContextParam(GL_COLOR_CLEAR_VALUE);
    m_params[(fgGFXuint)GL_COLOR_WRITEMASK] = fgGfxContextParam(GL_COLOR_WRITEMASK);
    //m_params[(fgGFXuint)GL_COMPRESSED_TEXTURE_FORMATS] = fgGfxContextParam(GL_COMPRESSED_TEXTURE_FORMATS);
    m_params[(fgGFXuint)GL_CULL_FACE] = fgGfxContextParam(GL_CULL_FACE);
    m_params[(fgGFXuint)GL_CULL_FACE_MODE] = fgGfxContextParam(GL_CULL_FACE_MODE);
    m_params[(fgGFXuint)GL_CURRENT_PROGRAM] = fgGfxContextParam(GL_CURRENT_PROGRAM);
    m_params[(fgGFXuint)GL_DEPTH_CLEAR_VALUE] = fgGfxContextParam(GL_DEPTH_CLEAR_VALUE);
    m_params[(fgGFXuint)GL_DEPTH_FUNC] = fgGfxContextParam(GL_DEPTH_FUNC);
    m_params[(fgGFXuint)GL_DEPTH_RANGE] = fgGfxContextParam(GL_DEPTH_RANGE);
    m_params[(fgGFXuint)GL_DEPTH_TEST] = fgGfxContextParam(GL_DEPTH_TEST);
    m_params[(fgGFXuint)GL_DEPTH_WRITEMASK] = fgGfxContextParam(GL_DEPTH_WRITEMASK);
    m_params[(fgGFXuint)GL_DITHER] = fgGfxContextParam(GL_DITHER);
    m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING] = fgGfxContextParam(GL_ARRAY_BUFFER_BINDING);
    m_params[(fgGFXuint)GL_ELEMENT_ARRAY_BUFFER_BINDING] = fgGfxContextParam(GL_ELEMENT_ARRAY_BUFFER_BINDING);
    m_params[(fgGFXuint)GL_FRAMEBUFFER_BINDING] = fgGfxContextParam(GL_FRAMEBUFFER_BINDING);
    m_params[(fgGFXuint)GL_FRONT_FACE] = fgGfxContextParam(GL_FRONT_FACE);
    m_params[(fgGFXuint)GL_GENERATE_MIPMAP_HINT] = fgGfxContextParam(GL_GENERATE_MIPMAP_HINT);
    m_params[(fgGFXuint)GL_IMPLEMENTATION_COLOR_READ_FORMAT] = fgGfxContextParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
    m_params[(fgGFXuint)GL_IMPLEMENTATION_COLOR_READ_TYPE] = fgGfxContextParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
    m_params[(fgGFXuint)GL_LINE_WIDTH] = fgGfxContextParam(GL_LINE_WIDTH);
    m_params[(fgGFXuint)GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS] = fgGfxContextParam(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    m_params[(fgGFXuint)GL_MAX_CUBE_MAP_TEXTURE_SIZE] = fgGfxContextParam(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
    m_params[(fgGFXuint)GL_MAX_FRAGMENT_UNIFORM_VECTORS] = fgGfxContextParam(GL_MAX_FRAGMENT_UNIFORM_VECTORS);
    m_params[(fgGFXuint)GL_MAX_RENDERBUFFER_SIZE] = fgGfxContextParam(GL_MAX_RENDERBUFFER_SIZE);
    m_params[(fgGFXuint)GL_MAX_TEXTURE_IMAGE_UNITS] = fgGfxContextParam(GL_MAX_TEXTURE_IMAGE_UNITS);
    m_params[(fgGFXuint)GL_MAX_TEXTURE_SIZE] = fgGfxContextParam(GL_MAX_TEXTURE_SIZE);
    m_params[(fgGFXuint)GL_MAX_VARYING_VECTORS] = fgGfxContextParam(GL_MAX_VARYING_VECTORS);
    m_params[(fgGFXuint)GL_MAX_VERTEX_ATTRIBS] = fgGfxContextParam(GL_MAX_VERTEX_ATTRIBS);
    m_params[(fgGFXuint)GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS] = fgGfxContextParam(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
    m_params[(fgGFXuint)GL_MAX_VERTEX_UNIFORM_VECTORS] = fgGfxContextParam(GL_MAX_VERTEX_UNIFORM_VECTORS);
    m_params[(fgGFXuint)GL_NUM_COMPRESSED_TEXTURE_FORMATS] = fgGfxContextParam(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
    m_params[(fgGFXuint)GL_NUM_SHADER_BINARY_FORMATS] = fgGfxContextParam(GL_NUM_SHADER_BINARY_FORMATS);
    m_params[(fgGFXuint)GL_PACK_ALIGNMENT] = fgGfxContextParam(GL_PACK_ALIGNMENT);
    m_params[(fgGFXuint)GL_POLYGON_OFFSET_FACTOR] = fgGfxContextParam(GL_POLYGON_OFFSET_FACTOR);
    m_params[(fgGFXuint)GL_POLYGON_OFFSET_FILL] = fgGfxContextParam(GL_POLYGON_OFFSET_FILL);
    m_params[(fgGFXuint)GL_POLYGON_OFFSET_UNITS] = fgGfxContextParam(GL_POLYGON_OFFSET_UNITS);
    m_params[(fgGFXuint)GL_RENDERBUFFER_BINDING] = fgGfxContextParam(GL_RENDERBUFFER_BINDING);
    m_params[(fgGFXuint)GL_SAMPLE_ALPHA_TO_COVERAGE] = fgGfxContextParam(GL_SAMPLE_ALPHA_TO_COVERAGE);
    m_params[(fgGFXuint)GL_SAMPLE_COVERAGE] = fgGfxContextParam(GL_SAMPLE_COVERAGE);
    m_params[(fgGFXuint)GL_SAMPLE_BUFFERS] = fgGfxContextParam(GL_SAMPLE_BUFFERS);
    m_params[(fgGFXuint)GL_SAMPLE_COVERAGE_INVERT] = fgGfxContextParam(GL_SAMPLE_COVERAGE_INVERT);
    m_params[(fgGFXuint)GL_SAMPLE_COVERAGE_VALUE] = fgGfxContextParam(GL_SAMPLE_COVERAGE_VALUE);
    m_params[(fgGFXuint)GL_SAMPLES] = fgGfxContextParam(GL_SAMPLES);
    m_params[(fgGFXuint)GL_MAX_VIEWPORT_DIMS] = fgGfxContextParam(GL_MAX_VIEWPORT_DIMS);
    m_params[(fgGFXuint)GL_SCISSOR_BOX] = fgGfxContextParam(GL_SCISSOR_BOX);
    m_params[(fgGFXuint)GL_SCISSOR_TEST] = fgGfxContextParam(GL_SCISSOR_TEST);
    //m_params[(fgGFXuint)GL_SHADER_BINARY_FORMATS] = fgGfxContextParam(GL_SHADER_BINARY_FORMATS);
    m_params[(fgGFXuint)GL_SHADER_COMPILER] = fgGfxContextParam(GL_SHADER_COMPILER);
    m_params[(fgGFXuint)GL_STENCIL_BACK_FUNC] = fgGfxContextParam(GL_STENCIL_BACK_FUNC);
    m_params[(fgGFXuint)GL_STENCIL_BACK_REF] = fgGfxContextParam(GL_STENCIL_BACK_REF);
    m_params[(fgGFXuint)GL_STENCIL_BACK_VALUE_MASK] = fgGfxContextParam(GL_STENCIL_BACK_VALUE_MASK);
    m_params[(fgGFXuint)GL_STENCIL_BACK_FAIL] = fgGfxContextParam(GL_STENCIL_BACK_FAIL);
    m_params[(fgGFXuint)GL_STENCIL_BACK_PASS_DEPTH_FAIL] = fgGfxContextParam(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
    m_params[(fgGFXuint)GL_STENCIL_BACK_PASS_DEPTH_PASS] = fgGfxContextParam(GL_STENCIL_BACK_PASS_DEPTH_PASS);
    m_params[(fgGFXuint)GL_STENCIL_BACK_WRITEMASK] = fgGfxContextParam(GL_STENCIL_BACK_WRITEMASK);
    m_params[(fgGFXuint)GL_STENCIL_FUNC] = fgGfxContextParam(GL_STENCIL_FUNC);
    m_params[(fgGFXuint)GL_STENCIL_REF] = fgGfxContextParam(GL_STENCIL_REF);
    m_params[(fgGFXuint)GL_STENCIL_VALUE_MASK] = fgGfxContextParam(GL_STENCIL_VALUE_MASK);
    m_params[(fgGFXuint)GL_STENCIL_FAIL] = fgGfxContextParam(GL_STENCIL_FAIL);
    m_params[(fgGFXuint)GL_STENCIL_PASS_DEPTH_FAIL] = fgGfxContextParam(GL_STENCIL_PASS_DEPTH_FAIL);
    m_params[(fgGFXuint)GL_STENCIL_PASS_DEPTH_PASS] = fgGfxContextParam(GL_STENCIL_PASS_DEPTH_PASS);
    m_params[(fgGFXuint)GL_STENCIL_WRITEMASK] = fgGfxContextParam(GL_STENCIL_WRITEMASK);
    m_params[(fgGFXuint)GL_STENCIL_TEST] = fgGfxContextParam(GL_STENCIL_TEST);
    m_params[(fgGFXuint)GL_STENCIL_BITS] = fgGfxContextParam(GL_STENCIL_BITS);
    m_params[(fgGFXuint)GL_STENCIL_CLEAR_VALUE] = fgGfxContextParam(GL_STENCIL_CLEAR_VALUE);
    m_params[(fgGFXuint)GL_SUBPIXEL_BITS] = fgGfxContextParam(GL_SUBPIXEL_BITS);
    m_params[(fgGFXuint)GL_TEXTURE_BINDING_2D] = fgGfxContextParam(GL_TEXTURE_BINDING_2D);
    m_params[(fgGFXuint)GL_TEXTURE_BINDING_CUBE_MAP] = fgGfxContextParam(GL_TEXTURE_BINDING_CUBE_MAP);
    m_params[(fgGFXuint)GL_UNPACK_ALIGNMENT] = fgGfxContextParam(GL_UNPACK_ALIGNMENT);
    m_params[(fgGFXuint)GL_VIEWPORT] = fgGfxContextParam(GL_VIEWPORT);

    memset(m_attrInfo, 0, sizeof (m_attrInfo));

    std::string glVendor = (const char*)glGetString(GL_VENDOR);
    std::string glRenderer = (const char *)glGetString(GL_RENDERER);
    std::string glVersion = (const char *)glGetString(GL_VERSION);
    std::string glSLVersion = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::string glExtensions;

#if defined(FG_USING_MARMALADE)
    glExtensions = (const char*)glGetString(GL_EXTENSIONS);
#elif defined(FG_USING_OPENGL_GLEW)
    if(glewIsSupported("GL_VERSION_3_0") || glewIsSupported("GL_VERSION_3_2") || glewIsSupported("GL_VERSION_3_2")) {
        int max = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &max);
        for(int i = 0; i < max; i++) {
            glExtensions.append((const char*)glGetStringi(GL_EXTENSIONS, i)).append(" ");
        }
    }
#endif

    FG_LOG::PrintDebug("GFX: GL vendor:     %s", glVendor.c_str());
    FG_LOG::PrintDebug("GFX: GL renderer:   %s", glRenderer.c_str());
    FG_LOG::PrintDebug("GFX: GL version:    %s", glVersion.c_str());
    FG_LOG::PrintDebug("GFX: GLSL version:  %s", glSLVersion.c_str());
    FG_LOG::PrintDebug("GFX: Extensions:    %s", (const char*)glExtensions.c_str());
    //glGetStringi(GL_EXTENSIONS, 0);
    fgStringVector vparts;
    fgStrings::split(glVersion, ' ', vparts);
    for(int i = 0; i < (int)vparts.size(); i++) {
        fgStrings::trim(vparts[i]);
        if(fgStrings::startsWith(vparts[i].c_str(), "3.0", FG_FALSE)) {
        } else if(fgStrings::startsWith(vparts[i].c_str(), "3.1", FG_FALSE)) {
        }
    }
    //GLSL Version      OpenGL Version
    //1.10		2.0
    //1.20		2.1
    //1.30		3.0
    //1.40		3.1
    //1.50		3.2
    //3.30		3.3
    //4.00		4.0
    //4.10		4.1
    //4.20		4.2
    //4.30		4.3
    //4.40		4.4
    //4.50              4.5

    vparts.clear();
    m_SLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
    fgStrings::split(glSLVersion, ' ', vparts);
    for(int i = 0; i < (int)vparts.size(); i++) {
        fgStrings::trim(vparts[i]);
        if(fgStrings::startsWith(vparts[i].c_str(), "1.0", FG_FALSE)) {
            if(g_fgBuildConfig.usingMarmaladeOpenGLES || g_fgBuildConfig.usingMarmalade)
                m_SLVersion = FG_GFX_ESSL_100;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "1.1", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_110;
            if(g_fgBuildConfig.usingMarmaladeOpenGLES || g_fgBuildConfig.usingMarmalade)
                m_SLVersion = FG_GFX_ESSL_100;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "1.2", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_120;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "1.3", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_130;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "1.4", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_140;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "1.5", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_150;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "3.0", FG_FALSE)) {
            if(g_fgBuildConfig.usingMarmaladeOpenGLES || g_fgBuildConfig.usingMarmalade)
                m_SLVersion = FG_GFX_ESSL_300;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "3.3", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_330;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.0", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_400;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.1", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_410;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.2", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_420;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.3", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_430;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.4", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_440;
        } else if(fgStrings::startsWith(vparts[i].c_str(), "4.5", FG_FALSE)) {
            m_SLVersion = FG_GFX_GLSL_450;
        }
        if(m_SLVersion != FG_GFX_SHADING_LANGUAGE_INVALID)
            break;
    }

    m_init = FG_TRUE;
}

/*
 *
 */
fgGfxContext::~fgGfxContext() {
#if defined(FG_USING_SDL2)
    if(m_GLContext)
        SDL_GL_DeleteContext(m_GLContext);
    m_GLContext = NULL;
#endif
    m_params.clear();
    m_init = FG_FALSE;
}

/*
 *
 */
void fgGfxContext::initialize(void) {
    gfxParamMapItor end = m_params.end(), itor = m_params.begin();
    for(; itor != end; itor++) {
        fgGfxContextParam &param = itor->second;
        param.load();
        //printf("Parameter GFX: %d = %d\n", (int)itor->first, (int)param.boolVal);
    }
}

/*
 *
 */
fgGfxContextParam& fgGfxContext::getParam(const fgGFXenum pname) {
    return m_params[(fgGFXuint)pname];
}

/*
 *
 */
void fgGfxContext::enable(const fgGFXenum cap) {
    m_params[(fgGFXuint)cap].set((fgGFXboolean)FG_GFX_TRUE);
}

/*
 *
 */
void fgGfxContext::disable(const fgGFXenum cap) {
    m_params[(fgGFXuint)cap].set((fgGFXboolean)FG_GFX_FALSE);
}

/*
 *
 */
fgGFXboolean fgGfxContext::isEnabled(const fgGFXenum pname) {
    return m_params[(fgGFXuint)pname].boolVal;
}

/*
 *
 */
fgGFXboolean fgGfxContext::isDisabled(const fgGFXenum pname) {
    return (fgGFXboolean)(FG_GFX_FALSE == m_params[(fgGFXuint)pname].boolVal);
}

/*
 *
 */
fgGFXboolean fgGfxContext::isBuffer(const fgGFXuint buffer) {
    if(buffer == 0)
        return FG_GFX_FALSE;
    if(m_buffers.empty())
        return FG_GFX_FALSE;
    if(m_buffers.find(buffer) == m_buffers.end())
        return FG_GFX_FALSE;
    return FG_GFX_TRUE;
}

/*
 *
 */
fgGFXboolean fgGfxContext::isBuffer(const fgGfxBufferID& bufferID) {
    return isBuffer(bufferID.id);
}
//
//#define foreach(_container_type, _variable_scan) \
//	_container_type::iterator itor = _variable_scan.begin(), \
//	end = _variable_scan.end(); \
//	for(;itor!=end;itor++) 
//

/*
 *
 */
void fgGfxContext::deleteAllBuffers(void) {
    if(m_buffers.empty())
        return;
    gfxBufferMapItor itor = m_buffers.begin(), end = m_buffers.end();
    for(; itor != end; itor++) {
        fgGfxBufferID *buffer = itor->second;
        if(!buffer)
            continue;
        glDeleteBuffers(1, buffer->ptrID());
        fgGLError("glDeleteBuffers");
        buffer->id = 0;
    }
    m_buffers.clear();
}

/*
 *
 */
fgGFXboolean fgGfxContext::genBuffers(const int count,
                                      fgGfxBufferID*& buffers,
                                      const fgGFXenum usage) {
    if(count <= 0)
        return FG_GFX_FALSE;
    if(!buffers) {
        buffers = fgMalloc<fgGfxBufferID>(count);
    }
    for(int i = 0; i < count; i++) {
        fgGfxBufferID &buffer = buffers[i];
        buffer.usage = usage;
        buffer.target = (fgGFXenum)0;
        if(!isBuffer(buffer))
            glGenBuffers(1, buffer.ptrID());
        if(buffer.id)
            m_buffers[buffer.id] = &buffers[i];
    }
    return FG_GFX_TRUE;
}

/*
 *
 */
void fgGfxContext::bufferData(fgGfxBufferID& bufferID,
                              const fgGFXsizei size,
                              const fgGFXvoid* data,
                              const fgGFXenum target,
                              const fgGFXenum usage) {
    if(!data)
        return;
    if((fgGFXenum)0 == target || (fgGFXenum)0 == bufferID.target) {
        bufferID.target = GL_ARRAY_BUFFER;
    }
    if(m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING] != bufferID.id && bufferID.target == GL_ARRAY_BUFFER) {
        FG_LOG::PrintError("GFX: Invalid buffer bound, can't set buffer data");
        return;
    }
    if(m_params[(fgGFXuint)GL_ELEMENT_ARRAY_BUFFER_BINDING] != bufferID.id && bufferID.target == GL_ELEMENT_ARRAY_BUFFER) {
        FG_LOG::PrintError("GFX: Invalid buffer bound, can't set buffer data");
        return;
    }
    if(usage != (fgGFXenum)0)
        bufferID.usage = usage;
    if((fgGFXenum)0 == bufferID.usage)
        bufferID.usage = GL_STATIC_DRAW;
    glBufferData(bufferID.target, size, data, bufferID.usage);
    fgGLError("glBufferData");
}

/*
 *
 */
void fgGfxContext::bindBuffer(fgGfxBufferID& bufferID, const fgGFXenum target) {
    if(bufferID.id == 0)
        return;
    if(target != (fgGFXenum)0)
        bufferID.target = target;
    if((fgGFXenum)0 == bufferID.target)
        bufferID.target = GL_ARRAY_BUFFER;
    bindBuffer(bufferID.target, bufferID.id);
}

/*
 *
 */
void fgGfxContext::bindBuffer(const fgGFXenum target, const fgGFXuint buffer) {
    if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
        m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
    } else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
        m_params[(fgGFXuint)GL_ELEMENT_ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
    }
}

/*
 *
 */
fgGFXuint fgGfxContext::boundBuffer(const fgGFXenum target) {
    if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
        return m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING];
    } else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
        return m_params[(fgGFXuint)GL_ELEMENT_ARRAY_BUFFER_BINDING];
    }
    return 0;
}

/*
 *
 */
void fgGfxContext::deleteBuffer(fgGfxBufferID& bufferID) {
    if(bufferID.id == 0)
        return;
    if(m_buffers.empty())
        return;
    gfxBufferMapItor itor = m_buffers.find(bufferID.id);
    if(itor == m_buffers.end())
        return;
    glDeleteBuffers(1, bufferID.ptrID());
    itor->second->id = 0;
    m_buffers.erase(itor);
}

/*
 *
 */
void fgGfxContext::deleteBuffers(const int count, fgGfxBufferID* buffers) {
    if(count <= 0 || !buffers)
        return;
    for(int i = 0; i < count; i++)
        deleteBuffer(buffers[i]);
}

/*
 *
 */
fgGFXuint fgGfxContext::boundTexture(void) const {
    return m_boundTexture;
}

/*
 *
 */
fgGFXuint fgGfxContext::activeTexture(void) {
    return m_params[(fgGFXuint)GL_ACTIVE_TEXTURE];
}

/*
 *
 */
void fgGfxContext::activeTexture(const fgGFXenum texture) {
    m_params[(fgGFXuint)GL_ACTIVE_TEXTURE].set((fgGFXint)texture);
}

/*
 *
 */
fgGFXboolean fgGfxContext::isTexture(const fgGFXuint texture) {
    if(texture == 0)
        return FG_GFX_FALSE;
    if(m_textures.empty())
        return FG_GFX_FALSE;
    if(m_textures.find(texture) == m_textures.end())
        return FG_GFX_FALSE;
    return FG_GFX_TRUE;
}

/*
 *
 */
fgGFXboolean fgGfxContext::isTexture(const fgGfxTextureID& textureID) {
    return isTexture(textureID.id);
}

/*
 *
 */
void fgGfxContext::deleteAllTextures(void) {
    if(m_textures.empty())
        return;
    gfxTextureMapItor itor = m_textures.begin(), end = m_textures.end();
    for(; itor != end; itor++) {
        fgGfxTextureID *tex = itor->second;
        if(!tex)
            continue;
        glDeleteTextures(1, tex->ptrID());
        fgGLError("glDeleteTextures");
        tex->id = 0;
    }
    m_textures.clear();
}

/*
 *
 */
void fgGfxContext::genTextures(const int count,
                               fgGfxTextureID* textures,
                               const fgGFXenum target/* = GL_TEXTURE_2D*/) {
    if(count <= 0 || !textures)
        return;
    if(!textures)
        return;
    for(int i = 0; i < count; i++) {
        genTexture(&textures[i]);
    }
}

/*
 *
 */
void fgGfxContext::genTexture(fgGfxTextureID* texture,
                              const fgGFXenum target/* = GL_TEXTURE_2D*/) {
    if(!texture)
        return;
    texture->target = target;
    if(texture->target != (fgGFXenum)0)
        texture->target = GL_TEXTURE_2D;
    glGenTextures(1, texture->ptrID());
    if(texture->id)
        m_textures[texture->id] = texture;
}

/*
 *
 */
void fgGfxContext::deleteTextures(const int count, fgGfxTextureID* textures) {
    if(count <= 0 || !textures)
        return;
    for(int i = 0; i < count; i++)
        deleteTexture(textures[i]);
}

/*
 *
 */
void fgGfxContext::deleteTexture(fgGfxTextureID& textureID) {
    if(textureID.id == 0)
        return;
    if(m_textures.empty())
        return;
    gfxTextureMapItor itor = m_textures.find(textureID.id);
    if(itor == m_textures.end())
        return;
    glDeleteTextures(1, textureID.ptrID());
    textureID.id = 0;
    fgGLError("glDeleteTextures");
    itor->second->id = 0;
    m_textures.erase(itor);
}

/*
 *
 */
void fgGfxContext::bindTexture(fgGfxTextureID& textureID, const fgGFXenum target/*=0*/) {
    if(textureID.id == 0)
        return;
    if(target != (fgGFXenum)0)
        textureID.target = target;
    if(textureID.target != (fgGFXenum)0)
        textureID.target = GL_TEXTURE_2D;
    if(textureID.target == GL_TEXTURE_2D) {
        bindTexture2D(textureID.id);
    } else if(textureID.target == GL_TEXTURE_CUBE_MAP) {
        bindTexture3D(textureID.id);
    }
}

/*
 *
 */
void fgGfxContext::bindTexture2D(const fgGFXuint texID) {
    m_params[(fgGFXuint)GL_TEXTURE_BINDING_2D].set((fgGFXint)texID);
    m_boundTexture = texID;
}

/*
 *
 */
void fgGfxContext::bindTexture3D(const fgGFXuint texID) {
    m_params[(fgGFXuint)GL_TEXTURE_BINDING_CUBE_MAP].set((fgGFXint)texID);
    m_boundTexture = texID;
}

/*
 *
 */
void fgGfxContext::blendEquation(const fgGFXenum mode) {
    fgGfxContextParam& modeRGB = m_params[(fgGFXuint)GL_BLEND_EQUATION_RGB];
    fgGfxContextParam& modeAlpha = m_params[(fgGFXuint)GL_BLEND_EQUATION_ALPHA];
    if(modeRGB.intVal != (fgGFXint)mode || modeAlpha.intVal != (fgGFXint)mode) {
        modeAlpha = modeRGB = mode;
        glBlendEquationSeparate(mode, mode);
    }
}

/*
 *
 */
void fgGfxContext::blendFunc(const fgGFXenum sfactor, const fgGFXenum dfactor) {
    fgGfxContextParam& srcRGB = m_params[(fgGFXuint)GL_BLEND_SRC_RGB];
    fgGfxContextParam& dstRGB = m_params[(fgGFXuint)GL_BLEND_DST_RGB];
    fgGfxContextParam& srcAlpha = m_params[(fgGFXuint)GL_BLEND_SRC_ALPHA];
    fgGfxContextParam& dstAlpha = m_params[(fgGFXuint)GL_BLEND_DST_ALPHA];

    if(srcRGB.intVal != (fgGFXint)sfactor ||
       srcAlpha.intVal != (fgGFXint)sfactor ||
       dstRGB.intVal != (fgGFXint)dfactor ||
       dstAlpha.intVal != (fgGFXint)dfactor) {
        
        srcRGB.intVal = (fgGFXint)sfactor;
        dstRGB.intVal = (fgGFXint)dfactor;
        srcAlpha.intVal = (fgGFXint)sfactor;
        dstAlpha.intVal = (fgGFXint)dfactor;
        glBlendFuncSeparate((fgGFXenum)srcRGB,
                            (fgGFXenum)dstRGB,
                            (fgGFXenum)srcAlpha,
                            (fgGFXenum)dstAlpha);
    }
}

/*
 *
 */
void fgGfxContext::blendFunc(const fgGFXenum srcRGB, const fgGFXenum dstRGB, const fgGFXenum srcAlpha, const fgGFXenum dstAlpha) {
    fgGfxContextParam& srcRGBparam = m_params[(fgGFXuint)GL_BLEND_SRC_RGB];
    fgGfxContextParam& dstRGBparam = m_params[(fgGFXuint)GL_BLEND_DST_RGB];
    fgGfxContextParam& srcAlphaparam = m_params[(fgGFXuint)GL_BLEND_SRC_ALPHA];
    fgGfxContextParam& dstAlphaparam = m_params[(fgGFXuint)GL_BLEND_DST_ALPHA];
    
    if(srcRGBparam.intVal != (fgGFXint)srcRGB ||
       srcAlphaparam.intVal != (fgGFXint)srcAlpha ||
       dstRGBparam.intVal != (fgGFXint)dstRGB ||
       dstAlphaparam.intVal != (fgGFXint)dstAlpha) {
        srcRGBparam.intVal = (fgGFXint)srcRGB;
        dstRGBparam.intVal = (fgGFXint)dstRGB;
        srcAlphaparam.intVal = (fgGFXint)srcAlpha;
        dstAlphaparam.intVal = (fgGFXint)dstAlpha;
        
        glBlendFuncSeparate((fgGFXenum)srcRGBparam,
                            (fgGFXenum)dstRGBparam,
                            (fgGFXenum)srcAlphaparam,
                            (fgGFXenum)dstAlphaparam);
    }
}

/*
 *
 */
void fgGfxContext::useProgram(const fgGFXuint program) {
    if(m_params[(fgGFXuint)GL_CURRENT_PROGRAM].intVal != (fgGFXint)program) {
        m_params[(fgGFXuint)GL_CURRENT_PROGRAM].set((fgGFXint)program);
    }
}

/*
 *
 */
fgGFXuint fgGfxContext::activeProgram(void) {
    return m_params[(fgGFXuint)GL_CURRENT_PROGRAM];
}

/*
 *
 */
void fgGfxContext::viewport(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height) {
    fgGFXuint areaQ = x * y + width*height;
    if(areaQ != m_viewportAreaQ) {
        m_viewportAreaQ = areaQ;
        m_params[(fgGFXuint)GL_VIEWPORT].set(x, y, width, height);
    }
}

/*
 *
 */
void fgGfxContext::viewport(const fgVector2i& pos, const fgVector2i& size) {
    viewport(pos.x, pos.y, size.x, size.y);
}

/*
 *
 */
void fgGfxContext::viewport(const fgVector4i& dimensions) {
    viewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

/*
 *
 */
void fgGfxContext::scissor(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height) {
    fgGFXuint areaQ = x * y + width*height;
    if(areaQ != m_scissorAreaQ) {
        m_scissorAreaQ = areaQ;
        m_params[(fgGFXuint)GL_SCISSOR_BOX].set(x, y, width, height);
    }
}

/*
 *
 */
void fgGfxContext::scissor(const fgVector2i& pos, const fgVector2i& size) {
    scissor(pos.x, pos.y, size.x, size.y);
}

/*
 *
 */
void fgGfxContext::scissor(const fgVector4i& dimensions) {
    scissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

/*
 *
 */
void fgGfxContext::setScissorTest(const fgBool toggle) {
    m_params[(fgGFXuint)GL_SCISSOR_TEST].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setDepthTest(const fgBool toggle) {
    m_params[(fgGFXuint)GL_DEPTH_TEST].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setCullFace(const fgBool toggle) {
    //gfxParamMapItor itor = m_params.find((fgGFXuint)GL_CULL_FACE);
    m_params[(fgGFXuint)GL_CULL_FACE].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::setBlend(const fgBool toggle) {
    m_params[(fgGFXuint)GL_BLEND].set((fgGFXboolean)toggle);
}

/*
 *
 */
void fgGfxContext::frontFace(const fgGFXenum mode) {
    m_params[(fgGFXuint)GL_FRONT_FACE].set((fgGFXint)mode);
}

/*
 *
 */
void fgGfxContext::cullFace(const fgGFXenum mode) {
    m_params[(fgGFXuint)GL_CULL_FACE_MODE].set((fgGFXint)mode);
}

/*
 *
 */
void fgGfxContext::depthFunc(const fgGFXenum func) {
    m_params[(fgGFXuint)GL_DEPTH_FUNC].set((fgGFXint)func);
}

/*
 *
 */
void fgGfxContext::clearDepth(const fgGFXfloat depth) {
    m_params[(fgGFXuint)GL_DEPTH_CLEAR_VALUE].set(depth);
}

/*
 *
 */
void fgGfxContext::clearColor(const fgGFXfloat red, const fgGFXfloat green, const fgGFXfloat blue, const fgGFXfloat alpha) {
    m_params[(fgGFXuint)GL_COLOR_CLEAR_VALUE].set(red, green, blue, alpha);
}

/*
 *
 */
void fgGfxContext::clearStencil(const fgGFXint s) {
    m_params[(fgGFXuint)GL_STENCIL_CLEAR_VALUE].set(s);
}

/*
 *
 */
fgGFXuint fgGfxContext::activeVertexAttribArrayMask(void) const {
    return m_attribMask;
}

/*
 *
 */
fgBool fgGfxContext::isVertexAttribArrayActive(const fgGFXuint index) const {
    return m_attrInfo[index].isEnabled;
}

/*
 *
 */
void fgGfxContext::updateAttribMask(const fgGFXuint index) {
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
void fgGfxContext::enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask) {
    if(!m_attrInfo[index].isEnabled) {
        m_attrInfo[index].isEnabled = FG_GFX_TRUE;
        glEnableVertexAttribArray(index);
        if(updateMask)
            updateAttribMask(index);
    }
}

/*
 *
 */
void fgGfxContext::disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask) {
    if(m_attrInfo[index].isEnabled) {
        m_attrInfo[index].isEnabled = FG_GFX_FALSE;
        glDisableVertexAttribArray(index);
        if(updateMask)
            updateAttribMask(index);
    }
}

/*
 *
 */
void fgGfxContext::enableVertexAttribArrayMask(const fgGFXuint mask) {
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
void fgGfxContext::disableVertexAttribArrayMask(const fgGFXuint mask) {
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
void fgGfxContext::diffVertexAttribArrayMask(const fgGFXuint mask) {
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
fgGFXuint fgGfxContext::getVertexAttribBufferBinding(const fgGFXuint index) {
    return m_attrInfo[index].buffer;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribSize(const fgGFXuint index) {
    return m_attrInfo[index].size;
}

/*
 *
 */
fgGFXuint fgGfxContext::getVertexAttribStride(const fgGFXuint index) {
    if(index >= 12)
        return 0;
    return m_attrInfo[index].stride;
}

/*
 *
 */
fgGFXenum fgGfxContext::getVertexAttribType(const fgGFXuint index) {
    if(index >= 12)
        return (fgGFXenum)0;
    return m_attrInfo[index].type;
}

/*
 *
 */
fgGFXboolean fgGfxContext::getVertexAttribNormalized(const fgGFXuint index) {
    // #FIXME checks
    if(index >= 12)
        return FG_GFX_FALSE;
    return m_attrInfo[index].isNormalized;
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
 */
void fgGfxContext::vertexAttribPointer(fgGFXuint index,
                                       fgGFXint size,
                                       fgGFXenum type,
                                       fgGFXboolean normalized,
                                       fgGFXsizei stride,
                                       fgGFXvoid* ptr) {
    if(index >= 12)
        return;
    // #FIXME
    // # index checks
    // # max attrib prop check
    // # mirror
    // # usage of main attrib array in other places
    //
    fgGfxAttributeData &attr = m_attrInfo[index];
    attr.index = index;
    attr.size = size;
    attr.dataType = type;
    attr.isNormalized = normalized;
    attr.stride = stride;
    attr.pointer = ptr;
    attr.buffer = m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING];
    glVertexAttribPointer(index, size, type, normalized, stride, ptr);
    fgGLError("glVertexAttribPointer"); // #FIXME
}

/*
 *
 */
void fgGfxContext::vertexAttribPointer(fgGfxAttributeData& attrData) {
    fgGFXint index = attrData.index;
    if(index < 0)
        return;
    fgGFXboolean isEnabled = m_attrInfo[index].isEnabled;
    m_attrInfo[index] = attrData;
    m_attrInfo[index].isEnabled = isEnabled;
    m_attrInfo[index].buffer = m_params[(fgGFXuint)GL_ARRAY_BUFFER_BINDING];

    glVertexAttribPointer(attrData.index,
                          attrData.size,
                          attrData.dataType,
                          attrData.isNormalized,
                          attrData.stride,
                          attrData.pointer);
    fgGLError("glVertexAttribPointer"); // #FIXME
}
