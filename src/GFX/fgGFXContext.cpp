/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXContext.h"
#include "Util/fgStrings.h"
#include "Util/fgMemory.h"
#include "fgGFXPlatform.h"


namespace fg {
    namespace gfx {
        namespace context {
#if defined(FG_USING_SDL2)
            SDL_Window *g_sdlWindow;
            SDL_GLContext g_GLContext; // #FIXME - context can be separate? ... P4
#elif defined(FG_USING_EGL)    
            void* g_GLContext; // it's for EGL only...
#else
            void *g_GLContext; // ?
#endif
            /// Special parameter map used for caching and fast value check
            /// It's used for not calling redundant GL functions, like:
            /// glGet/glEnable/glDisable/glIsEnabled and so on. Also for
            /// functions like activating proper vertex attrib array idx,
            /// bounding textures... any kind of function that changes internal
            /// state values.
            ParameterVec g_params;
            /// Special map used for holding valid texture IDs
            /// Every texture needs to be created/deleted through
            /// this class. When texture is deleted its' ID is zeroed
            /// in every place in the app. Therefore there's no need to
            /// often call glIsTexture. If gfx ID is not zero the texture
            /// is surely valid.
            TextureMap g_textures;
            /// Special map used for holding valid VBO IDs. Use case
            /// is the same as for textures.
            BufferMap g_buffers;
            /// Viewport area (used for fast check if viewport changed)
            fgGFXuint g_viewportAreaQ;
            /// Scissor area
            fgGFXuint g_scissorAreaQ;

            /// Currently used attribute mask
            fgGFXuint g_attribMask;
            ///
            SAttributeData g_attrInfo[FG_GFX_ATTRIBUTE_DATA_MAX]; // #FIXME - attribute count ... why here?  hello?
            /// Currently bound texture ID
            fgGFXuint g_boundTexture;
            /// Supported shading language version
            ShadingLangVersion g_SLVersion;
            ///
            Vector2i g_screenSize;
            /// Is context ready? Is initialization successful?
            fgBool g_contextInit;
        }
    }
}
using namespace fg;

void gfx::SContextParam::determineParamType(void) {
    count = 1;
    switch(this->internal_pname) {
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

            // params returns two values: the near and far mapping limits for the depth buffer.
            // Integer values, if requested, are linearly mapped from the internal 
            // floating-point representation such that 1.0 returns the most positive representable
            // integer value, and -1.0 returns the most negative representable integer
            // value. The initial value is (0, 1). See glDepthRangef.
        case GL_DEPTH_RANGE:
            count = 2;
            type = FG_GFX_FLOAT;
            paramType = FG_GFX_PARAM_DEPTH_RANGE;
            break;

            // params returns a single boolean value indicating whether depth testing
            // of fragments is enabled. The initial value is GL_FALSE.
            // See glDepthFunc and glDepthRangef.
        case GL_DEPTH_TEST:
            count = 1;
            type = FG_GFX_BOOL;
            paramType = FG_GFX_PARAM_BOOL;
            break;

            // params returns a single boolean value indicating if the depth buffer
            // is enabled for writing. The initial value is GL_TRUE.
            // See glDepthMask.
        case GL_DEPTH_WRITEMASK:
            count = 1;
            type = FG_GFX_BOOL;
            paramType = FG_GFX_PARAM_DEPTH_MASK;
            break;

            // params returns a single boolean value indicating whether dithering of
            // fragment colors and indices is enabled. The initial value is GL_TRUE.
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

            // params returns a single value, the name of the buffer object
            // currently bound to the target GL_ELEMENT_ARRAY_BUFFER. If no buffer object
            // is bound to this target, 0 is returned.  The initial value is 0.
            // See glBindBuffer.
        case GL_ELEMENT_ARRAY_BUFFER_BINDING:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_ELEM_BUFFER_BIND;
            break;

            // params returns a single value, the name of the currently bound
            // framebuffer. The initial value is 0, indicating the default framebuffer.
            // See glBindFramebuffer.
        case GL_FRAMEBUFFER_BINDING:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_FRAME_BUFFER_BIND;
            break;

            // params returns one value,
            // a symbolic constant indicating whether clockwise or counterclockwise
            // polygon winding is treated as front-facing. The initial value is
            // GL_CCW.
            // See glFrontFace.
        case GL_FRONT_FACE:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_FRONT_FACE;
            break;

            // params returns one value,
            // a symbolic constant indicating the mode of the mipmap generation filtering
            // hint. The initial value is GL_DONT_CARE.
            // See glHint.
        case GL_GENERATE_MIPMAP_HINT:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_HINT;
            break;

            // params returns one value, the format
            // chosen by the implementation in which pixels may be read from the
            // color buffer of the currently bound framebuffer in conjunction with
            // GL_IMPLEMENTATION_COLOR_READ_TYPE.
            // In addition to this implementation-dependent format/type pair,
            // format GL_RGBA in conjunction with type GL_UNSIGNED_BYTE is always
            // allowed by every implementation, regardless of the currently bound
            // render surface.  See glReadPixels.
        case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
            break;

            // params returns one value, the type
            // chosen by the implementation with which pixels may be read from the
            // color buffer of the currently bound framebuffer in conjunction with
            // GL_IMPLEMENTATION_COLOR_READ_FORMAT.
            // In addition
            // to this implementation-dependent format/type pair, format 
            // GL_RGBA in conjunction with type 
            // GL_UNSIGNED_BYTE is always allowed by every
            // implementation, regardless of the currently bound render surface.
            // See glReadPixels.
        case GL_IMPLEMENTATION_COLOR_READ_TYPE:
            break;

            // params returns one value,
            // the line width as specified with glLineWidth. The initial value is 1.
        case GL_LINE_WIDTH:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_INT;
            break;

            // params returns one value, the maximum supported texture image units that 
            // can be used to access texture maps from the vertex shader and the fragment processor combined. 
            // If both the vertex shader and the fragment processing stage access the same texture image
            // unit, then that counts as using two texture image units against this limit.
            // The value must be at least 8.
            // See glActiveTexture.
        case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
            // params returns one value.
            // The value gives a rough estimate of the largest cube-map texture that
            // the GL can handle. The value must be at least 16.
            // See glTexImage2D.
        case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
            // params returns one value,
            // the maximum number of four-element floating-point, integer, or boolean vectors that can be held 
            // in uniform variable storage for a fragment shader. The value must be at least 16.
            // See glUniform.
        case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
            // params returns one value.
            // The value indicates the largest renderbuffer width and height
            // that the GL can handle. The value must be at least 1.
            // See glRenderbufferStorage.
        case GL_MAX_RENDERBUFFER_SIZE:
            // params returns one value,
            // the maximum supported texture image units that 
            // can be used to access texture maps from the fragment shader. 
            // The value must be at least 8.
            // See glActiveTexture.
        case GL_MAX_TEXTURE_IMAGE_UNITS:
            // params returns one value.
            // The value gives a rough estimate of the largest texture that
            // the GL can handle. The value must be at least 64.
            // See glTexImage2D.
        case GL_MAX_TEXTURE_SIZE:
            // params returns one value,
            // the maximum number four-element floating-point vectors available for interpolating varying variables used by
            // vertex and fragment shaders. Varying variables declared as matrices or arrays 
            // will consume multiple interpolators. The value must be at least 8.
        case GL_MAX_VARYING_VECTORS:
            // params returns one value,
            // the maximum number of 4-component generic vertex attributes accessible to a vertex shader. 
            // The value must be at least 8.
            // See glVertexAttrib.
        case GL_MAX_VERTEX_ATTRIBS:
            // params returns one value, the maximum supported texture image units that 
            // can be used to access texture maps from the vertex shader. The value may be 0.
            // See glActiveTexture.
        case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
            // params returns one value,
            // the maximum number of four-element floating-point, integer, or boolean vectors that can be held 
            // in uniform variable storage for a vertex shader. The value must be at least 128.
            // See glUniform.
        case GL_MAX_VERTEX_UNIFORM_VECTORS:
            // params returns a single integer value indicating the number of available
            // compressed texture formats.  The minimum value is 0.
            // See glCompressedTexImage2D.
        case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
            // params returns a single integer value indicating the number of available
            // shader binary formats.  The minimum value is 0.
            // See glShaderBinary.
        case GL_NUM_SHADER_BINARY_FORMATS:
            // params returns one value,
            // the byte alignment used for writing pixel data to memory. The initial
            // value is 4.
            // See glPixelStorei.
        case GL_PACK_ALIGNMENT:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_INT;
            break;

            // params returns one value,
            // the scaling factor used to determine the variable offset that is added
            // to the depth value of each fragment generated when a polygon is
            // rasterized. The initial value is 0.
            // See glPolygonOffset.
        case GL_POLYGON_OFFSET_FACTOR:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_INT;
            break;

            // params returns a single boolean value indicating whether polygon offset
            // is enabled for polygons in fill mode. The initial value is GL_FALSE.
            // See glPolygonOffset.
        case GL_POLYGON_OFFSET_FILL:
            count = 1;
            type = FG_GFX_BOOL;
            paramType = FG_GFX_PARAM_BOOL;
            break;

            // params returns one value.
            // This value is multiplied by an implementation-specific value and then
            // added to the depth value of each fragment
            // generated when a polygon is rasterized. The initial value is 0.
            // See glPolygonOffset.
        case GL_POLYGON_OFFSET_UNITS:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_INT;
            break;

            // params returns a single value, the name of the currently bound
            // renderbuffer. The initial value is 0, indicating no renderbuffer is bound.
            // See glBindRenderbuffer.
        case GL_RENDERBUFFER_BINDING:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_RENDER_BUFFER_BIND;
            break;

            // params returns a single boolean value indicating if the 
            // fragment coverage value should be ANDed with a temporary coverage value based
            // on the fragment's alpha value. The initial value is GL_FALSE.
            // See glSampleCoverage.
        case GL_SAMPLE_ALPHA_TO_COVERAGE:
            // params returns a single boolean value indicating if the 
            // fragment coverage value should be ANDed with a temporary coverage value based
            // on the current sample coverage value. The initial value is GL_FALSE.
            // See glSampleCoverage.
        case GL_SAMPLE_COVERAGE:
            count = 1;
            type = FG_GFX_BOOL;
            paramType = FG_GFX_PARAM_BOOL;
            break;

            // params returns a single integer value indicating the number of sample buffers
            // associated with the currently bound framebuffer.
            // See glSampleCoverage.
        case GL_SAMPLE_BUFFERS:
            count = 1;
            type = FG_GFX_INT;
            paramType = FG_GFX_PARAM_INT;
            break;

            // params returns a single boolean value indicating if the temporary
            // coverage value should be inverted.
            // See glSampleCoverage.
        case GL_SAMPLE_COVERAGE_INVERT:
            //glSampleCoverage(value, invert);
            count = 1;
            type = FG_GFX_BOOL;
            paramType = FG_GFX_PARAM_SAMPLE_COVERAGE;
            break;

            // params returns a single positive floating-point value indicating the
            // current sample coverage value.
            // See glSampleCoverage.
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
            break;
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

/**
 * 
 * @return 
 */
fgBool gfx::SContextParam::update(void) {
    if(this->paramType == FG_GFX_PARAM_INVALID)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    switch(this->paramType) {
        case FG_GFX_PARAM_BOOL:
            if(boolVal == FG_GFX_TRUE)
                glEnable(internal_pname);
            else
                glDisable(internal_pname);
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
            GLCheckError("glBindTexture");
            break;
        case FG_GFX_PARAM_TEXTURE_3D:
            glBindTexture(GL_TEXTURE_CUBE_MAP, (fgGFXuint)intVal);
            GLCheckError("glBindTexture");
            break;
        case FG_GFX_PARAM_TEXTURE:
            glActiveTexture((fgGFXenum)intVal);
            GLCheckError("glActiveTexture");
            break;
        case FG_GFX_PARAM_VERT_BUFFER_BIND:
            glBindBuffer(GL_ARRAY_BUFFER, intVal);
            GLCheckError("glBindBuffer");
            break;
        case FG_GFX_PARAM_ELEM_BUFFER_BIND:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, intVal);
            GLCheckError("glBindBuffer");
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
            GLCheckError("glUseProgram");
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
            GLCheckError("glBindFramebuffer");
            break;
        case FG_GFX_PARAM_RENDER_BUFFER_BIND:
            glBindRenderbuffer(GL_RENDERBUFFER, intVal);
            GLCheckError("glBindRenderbuffer");
            break;
        case FG_GFX_PARAM_HINT:
            glHint(internal_pname, (fgGFXenum)intVal);
            GLCheckError("glHint");
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

fgBool gfx::context::isInit(void) {
    return g_contextInit;
}

gfx::ShadingLangVersion gfx::context::getSLVersion(void) {
    return g_SLVersion;
}

void *gfx::context::getGLContext(void) {
    return g_GLContext;
}

Vector2i const& gfx::context::getScreenSize(void) {
    return g_screenSize;
}

void gfx::context::setScreenSize(const int w, const int h) {
    g_screenSize.x = w;
    g_screenSize.y = h;
}

void gfx::context::setScreenSize(const Vector2i& screenSize) {
    g_screenSize = screenSize;
}

void gfx::context::setScreenSize(const Vector2f& screenSize) {
    g_screenSize.x = (int)screenSize.x;
    g_screenSize.y = (int)screenSize.y;
}

#if defined(FG_USING_SDL2)
fgBool gfx::context::initialize(SDL_Window *sdlWindow)
#else

fgBool gfx::context::initialize(void)
#endif
{
#if defined(FG_USING_SDL2)

    g_sdlWindow = sdlWindow;
    g_GLContext = 0;
#endif
    g_viewportAreaQ = 0;
    g_scissorAreaQ = 0;
    g_attribMask = 0;
    g_boundTexture = 0;
    g_SLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
    g_contextInit = FG_FALSE;

#if defined(FG_USING_MARMALADE_EGL) || defined(FG_USING_EGL)
    /**********************************
     * CONTEXT PART - GFX CONTEXT
     */
    // Using EGL based on Marmalade build
    EGLDisplay eglDisplay = (EGLDisplay)CPlatform::getDefaultDisplay();
    EGLConfig eglConfig = (EGLConfig)CPlatform::getDefaultConfig();

    // #FIXME !
#if defined FG_USING_MARMALADE
    int glVersionN = s3eGLGetInt(S3E_GL_VERSION) >> 8;
#else
    int glVersionN = 2; // FIXME
#endif
    if(glVersionN != 2) {
        FG_LOG_ERROR("GFX: reported GL version: %d", glVersionN);
        FG_LOG_ERROR("GFX: required GLES v2.x");
        return; // #FIXME
    }
    FG_LOG_DEBUG("EGL: requesting GL version: %d", glVersionN);
    EGLint attribs[] = {EGL_CONTEXT_CLIENT_VERSION, glVersionN, EGL_NONE,};
    g_GLContext = eglCreateContext(eglDisplay, eglConfig, NULL, attribs);
    if(!g_GLContext) {
        FG_LOG_ERROR("EGL: CreateContext failed");
        fgEGLError("eglCreateContext");
        return;
    }
    EGLenum boundAPI = eglQueryAPI();
    if(boundAPI != EGL_OPENGL_ES_API) {
        FG_LOG_DEBUG("EGL is not bound to OpenGL ES api");
    } else {
        FG_LOG_DEBUG("EGL bound to OpenGL ES api");
    }
#elif defined(FG_USING_SDL2)
    /**********************************
     * CONTEXT PART - GFX CONTEXT
     */
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

    // Lists opengl es versions intended to try
#if defined(FG_USING_OPENGL_ES)
    const int numGLVersions = 3;
    const std::pair<int, int> glVersions[3] {
        {2, 0}, // Just for now the OGLES 2.0 has top priority
        {3, 0},
        {3, 1}
    };
    std::string glName = "OpenGL ES";
#else
    const int numGLVersions = 11;
    const std::pair<int, int> glVersions[11] {
        {4, 4},
        {4, 3},
        {4, 2},
        {4, 1},
        {4, 0},
        {3, 3},
        {3, 2},
        {3, 1},
        {3, 0},
        {2, 1},
        {2, 0}
    };
    std::string glName = "OpenGL";
#endif

#if !defined(FG_USING_PLATFORM_ANDROID)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // #FIXME seriously, this context should be created somewhere else, gfx Main ? - #NOPE
    // Well there is a difference here with the EGL - in SDL first there needs to be
    // a window created to bound GL context to it
    // As for the EGL on Marmalade there is no Window - there's a Surface instead, bound
    // to the native window - the native window, the handle to it is provided via Marmalade
    g_GLContext = SDL_GL_CreateContext(g_sdlWindow);
    if(!g_GLContext) {
        FG_LOG_ERROR("GFX: Couldn't create GL context: '%s'", SDL_GetError());
        SDL_ClearError();
        // Failed so try again with least possible GL version
        FG_LOG_INFO("GFX: Will try to create any kind of GL context...");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

        g_GLContext = SDL_GL_CreateContext(g_sdlWindow);
        if(!g_GLContext) {
            FG_LOG_ERROR("GFX: RETRY: Couldn't create GL context: '%s'", SDL_GetError());
            SDL_ClearError();
            return FG_FALSE;
        }
    }
#else
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    for(int i = 0; i < numGLVersions; i++) {
        const std::pair<int, int>& glVersion = glVersions[i];
        FG_LOG_DEBUG("GFX: Will try to create %s %d.%d context ...",
                     glName.c_str(),
                     glVersion.first,
                     glVersion.second);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glVersion.first);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glVersion.second);
        g_GLContext = SDL_GL_CreateContext(g_sdlWindow);
        if(!g_GLContext) {
            FG_LOG_ERROR("GFX: RETRY: Couldn't create GL context: '%s'", SDL_GetError());
        } else {
            FG_LOG_DEBUG("GFX: Successfully created %s %d.%d context",
                         glName.c_str(),
                         glVersion.first,
                         glVersion.second);
            break;
        }
    }
#endif /* !FG_USING_PLATFORM_ANDROID */
    int r, g, b, a, d, major, minor;
    SDL_GL_MakeCurrent(g_sdlWindow, g_GLContext);

    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);
    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);
    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);
    SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &d);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
#if defined(FG_USING_PLATFORM_ANDROID)
    FG_LOG_DEBUG("GFX: Using Android platform");
#elif defined(FG_USING_PLATFORM_LINUX)
    FG_LOG_DEBUG("GFX: Using Linux platform");
#elif defined(FG_USING_PLATFORM_WINDOW)
    FG_LOG_DEBUG("GFX: Using Windows platform");
#endif
    FG_LOG_DEBUG("GFX: GL version %d.%d", major, minor);
    FG_LOG_DEBUG("GFX: GL color buffer: red: %d, green: %d, blue: %d, alpha: %d, depth: %d,", r, g, b, a, d);

    // Support for GLEW is enabled?
#if defined(FG_USING_OPENGL_GLEW)
    FG_LOG_DEBUG("GFX: Initializing GLEW...");
    glewExperimental = FG_GFX_TRUE;
    fgGFXenum glewInitResult = glewInit();
    if(glewInitResult != GLEW_OK) {
        FG_LOG_ERROR("GFX: GLEW initialization error error '%s'", glewGetErrorString(glewInitResult));
        g_contextInit = FG_FALSE;
        return FG_FALSE;
    } else {
        FG_LOG_DEBUG("GFX: GLEW init completed successfully.");
    }
    fgGFXenum errorCheckValue = GLCheckError("glewInit");
    if(errorCheckValue != GL_NO_ERROR) {
        FG_LOG_ERROR("GFX: Context error, failed to initialize."); //, gluErrorString(errorCheckValue));
        g_contextInit = FG_FALSE;
        return FG_FALSE;
    }
    //glewIsSupported("GL_VERSION_3_0");
#else
    FG_LOG_DEBUG("GFX: Not using GLEW...");
#endif

#endif
    FG_LOG_DEBUG("GFX: Initializing GL parameter list...");
    //m_params[(fgGFXuint)GL_ACTIVE_TEXTURE] = SContextParam(GL_ACTIVE_TEXTURE);

    g_params.reserve(gfx::NUM_GL_PARAMETERS);
    g_params.resize(gfx::NUM_GL_PARAMETERS);

    g_params[gfx::ACTIVE_TEXTURE] = SContextParam(GL_ACTIVE_TEXTURE);
    g_params[gfx::ALIASED_LINE_WIDTH_RANGE] = SContextParam(GL_ALIASED_LINE_WIDTH_RANGE);
    g_params[gfx::ALIASED_POINT_SIZE_RANGE] = SContextParam(GL_ALIASED_POINT_SIZE_RANGE);
    g_params[gfx::ALPHA_BITS] = SContextParam(GL_ALPHA_BITS);
    g_params[gfx::BLEND] = SContextParam(GL_BLEND);
    g_params[gfx::BLEND_COLOR] = SContextParam(GL_BLEND_COLOR);
    g_params[gfx::BLEND_DST_ALPHA] = SContextParam(GL_BLEND_DST_ALPHA);
    g_params[gfx::BLEND_DST_RGB] = SContextParam(GL_BLEND_DST_RGB);
    g_params[gfx::BLEND_SRC_ALPHA] = SContextParam(GL_BLEND_SRC_ALPHA);
    g_params[gfx::BLEND_SRC_RGB] = SContextParam(GL_BLEND_SRC_RGB);
    g_params[gfx::BLEND_EQUATION_ALPHA] = SContextParam(GL_BLEND_EQUATION_ALPHA);
    g_params[gfx::BLEND_EQUATION_RGB] = SContextParam(GL_BLEND_EQUATION_RGB);
    g_params[gfx::RED_BITS] = SContextParam(GL_RED_BITS);
    g_params[gfx::GREEN_BITS] = SContextParam(GL_GREEN_BITS);
    g_params[gfx::BLUE_BITS] = SContextParam(GL_BLUE_BITS);
    g_params[gfx::DEPTH_BITS] = SContextParam(GL_DEPTH_BITS);
    g_params[gfx::COLOR_CLEAR_VALUE] = SContextParam(GL_COLOR_CLEAR_VALUE);
    g_params[gfx::COLOR_WRITEMASK] = SContextParam(GL_COLOR_WRITEMASK);
    g_params[gfx::COMPRESSED_TEXTURE_FORMATS] = SContextParam(GL_COMPRESSED_TEXTURE_FORMATS);
    g_params[gfx::CULL_FACE] = SContextParam(GL_CULL_FACE);
    g_params[gfx::CULL_FACE_MODE] = SContextParam(GL_CULL_FACE_MODE);
    g_params[gfx::CURRENT_PROGRAM] = SContextParam(GL_CURRENT_PROGRAM);
    g_params[gfx::DEPTH_CLEAR_VALUE] = SContextParam(GL_DEPTH_CLEAR_VALUE);
    g_params[gfx::DEPTH_FUNC] = SContextParam(GL_DEPTH_FUNC);
    g_params[gfx::DEPTH_RANGE] = SContextParam(GL_DEPTH_RANGE);
    g_params[gfx::DEPTH_TEST] = SContextParam(GL_DEPTH_TEST);
    g_params[gfx::DEPTH_WRITEMASK] = SContextParam(GL_DEPTH_WRITEMASK);
    g_params[gfx::DITHER] = SContextParam(GL_DITHER);
    g_params[gfx::ARRAY_BUFFER_BINDING] = SContextParam(GL_ARRAY_BUFFER_BINDING);
    g_params[gfx::ELEMENT_ARRAY_BUFFER_BINDING] = SContextParam(GL_ELEMENT_ARRAY_BUFFER_BINDING);
    g_params[gfx::FRAMEBUFFER_BINDING] = SContextParam(GL_FRAMEBUFFER_BINDING);
    g_params[gfx::FRONT_FACE] = SContextParam(GL_FRONT_FACE);
    g_params[gfx::GENERATE_MIPMAP_HINT] = SContextParam(GL_GENERATE_MIPMAP_HINT);
    g_params[gfx::IMPLEMENTATION_COLOR_READ_FORMAT] = SContextParam(GL_IMPLEMENTATION_COLOR_READ_FORMAT);
    g_params[gfx::IMPLEMENTATION_COLOR_READ_TYPE] = SContextParam(GL_IMPLEMENTATION_COLOR_READ_TYPE);
    g_params[gfx::LINE_WIDTH] = SContextParam(GL_LINE_WIDTH);
    g_params[gfx::MAX_COMBINED_TEXTURE_IMAGE_UNITS] = SContextParam(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    g_params[gfx::MAX_CUBE_MAP_TEXTURE_SIZE] = SContextParam(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
    g_params[gfx::MAX_FRAGMENT_UNIFORM_VECTORS] = SContextParam(GL_MAX_FRAGMENT_UNIFORM_VECTORS);
    g_params[gfx::MAX_RENDERBUFFER_SIZE] = SContextParam(GL_MAX_RENDERBUFFER_SIZE);
    g_params[gfx::MAX_TEXTURE_IMAGE_UNITS] = SContextParam(GL_MAX_TEXTURE_IMAGE_UNITS);
    g_params[gfx::MAX_TEXTURE_SIZE] = SContextParam(GL_MAX_TEXTURE_SIZE);
    g_params[gfx::MAX_VARYING_VECTORS] = SContextParam(GL_MAX_VARYING_VECTORS);
    g_params[gfx::MAX_VERTEX_ATTRIBS] = SContextParam(GL_MAX_VERTEX_ATTRIBS);
    g_params[gfx::MAX_VERTEX_TEXTURE_IMAGE_UNITS] = SContextParam(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
    g_params[gfx::MAX_VERTEX_UNIFORM_VECTORS] = SContextParam(GL_MAX_VERTEX_UNIFORM_VECTORS);
    g_params[gfx::NUM_COMPRESSED_TEXTURE_FORMATS] = SContextParam(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
    g_params[gfx::NUM_SHADER_BINARY_FORMATS] = SContextParam(GL_NUM_SHADER_BINARY_FORMATS);
    g_params[gfx::PACK_ALIGNMENT] = SContextParam(GL_PACK_ALIGNMENT);
    g_params[gfx::POLYGON_OFFSET_FACTOR] = SContextParam(GL_POLYGON_OFFSET_FACTOR);
    g_params[gfx::POLYGON_OFFSET_FILL] = SContextParam(GL_POLYGON_OFFSET_FILL);
    g_params[gfx::POLYGON_OFFSET_UNITS] = SContextParam(GL_POLYGON_OFFSET_UNITS);
    g_params[gfx::RENDERBUFFER_BINDING] = SContextParam(GL_RENDERBUFFER_BINDING);
    g_params[gfx::SAMPLE_ALPHA_TO_COVERAGE] = SContextParam(GL_SAMPLE_ALPHA_TO_COVERAGE);
    g_params[gfx::SAMPLE_COVERAGE] = SContextParam(GL_SAMPLE_COVERAGE);
    g_params[gfx::SAMPLE_BUFFERS] = SContextParam(GL_SAMPLE_BUFFERS);
    g_params[gfx::SAMPLE_COVERAGE_INVERT] = SContextParam(GL_SAMPLE_COVERAGE_INVERT);
    g_params[gfx::SAMPLE_COVERAGE_VALUE] = SContextParam(GL_SAMPLE_COVERAGE_VALUE);
    g_params[gfx::SAMPLES] = SContextParam(GL_SAMPLES);
    g_params[gfx::MAX_VIEWPORT_DIMS] = SContextParam(GL_MAX_VIEWPORT_DIMS);
    g_params[gfx::SCISSOR_BOX] = SContextParam(GL_SCISSOR_BOX);
    g_params[gfx::SCISSOR_TEST] = SContextParam(GL_SCISSOR_TEST);
#if defined(FG_USING_OPENGL_ES) || defined(FG_USING_MARMALADE_OPENGL_ES)
    g_params[gfx::SHADER_BINARY_FORMATS] = SContextParam(GL_SHADER_BINARY_FORMATS);
#endif
    g_params[gfx::SHADER_COMPILER] = SContextParam(GL_SHADER_COMPILER);
    g_params[gfx::STENCIL_BACK_FUNC] = SContextParam(GL_STENCIL_BACK_FUNC);
    g_params[gfx::STENCIL_BACK_REF] = SContextParam(GL_STENCIL_BACK_REF);
    g_params[gfx::STENCIL_BACK_VALUE_MASK] = SContextParam(GL_STENCIL_BACK_VALUE_MASK);
    g_params[gfx::STENCIL_BACK_FAIL] = SContextParam(GL_STENCIL_BACK_FAIL);
    g_params[gfx::STENCIL_BACK_PASS_DEPTH_FAIL] = SContextParam(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
    g_params[gfx::STENCIL_BACK_PASS_DEPTH_PASS] = SContextParam(GL_STENCIL_BACK_PASS_DEPTH_PASS);
    g_params[gfx::STENCIL_BACK_WRITEMASK] = SContextParam(GL_STENCIL_BACK_WRITEMASK);
    g_params[gfx::STENCIL_FUNC] = SContextParam(GL_STENCIL_FUNC);
    g_params[gfx::STENCIL_REF] = SContextParam(GL_STENCIL_REF);
    g_params[gfx::STENCIL_VALUE_MASK] = SContextParam(GL_STENCIL_VALUE_MASK);
    g_params[gfx::STENCIL_FAIL] = SContextParam(GL_STENCIL_FAIL);
    g_params[gfx::STENCIL_PASS_DEPTH_FAIL] = SContextParam(GL_STENCIL_PASS_DEPTH_FAIL);
    g_params[gfx::STENCIL_PASS_DEPTH_PASS] = SContextParam(GL_STENCIL_PASS_DEPTH_PASS);
    g_params[gfx::STENCIL_WRITEMASK] = SContextParam(GL_STENCIL_WRITEMASK);
    g_params[gfx::STENCIL_TEST] = SContextParam(GL_STENCIL_TEST);
    g_params[gfx::STENCIL_BITS] = SContextParam(GL_STENCIL_BITS);
    g_params[gfx::STENCIL_CLEAR_VALUE] = SContextParam(GL_STENCIL_CLEAR_VALUE);
    g_params[gfx::SUBPIXEL_BITS] = SContextParam(GL_SUBPIXEL_BITS);
    g_params[gfx::TEXTURE_BINDING_2D] = SContextParam(GL_TEXTURE_BINDING_2D);
    g_params[gfx::TEXTURE_BINDING_CUBE_MAP] = SContextParam(GL_TEXTURE_BINDING_CUBE_MAP);
    g_params[gfx::UNPACK_ALIGNMENT] = SContextParam(GL_UNPACK_ALIGNMENT);
    g_params[gfx::VIEWPORT] = SContextParam(GL_VIEWPORT);

    FG_LOG_DEBUG("GFX: Currently monitoring %d context parameters", g_params.size());

    memset(g_attrInfo, 0, sizeof (g_attrInfo));

    std::string glVendor = (const char*)glGetString(GL_VENDOR);
    std::string glRenderer = (const char *)glGetString(GL_RENDERER);
    std::string glVersion = (const char *)glGetString(GL_VERSION);
    std::string glSLVersion = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
#if defined(FG_DEBUG)
    GLCheckError("glGetString", "GL_SHADING_LANGUAGE_VERSION");
#endif
    std::string glExtensions;

#if defined(FG_USING_MARMALADE)
    glExtensions = (const char*)glGetString(GL_EXTENSIONS);
#elif defined(FG_USING_OPENGL_GLEW)
    if(glewIsSupported("GL_VERSION_3_0") ||
       glewIsSupported("GL_VERSION_3_2") ||
       glewIsSupported("GL_VERSION_3_3")) {
        int max = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &max);
        for(int i = 0; i < max; i++) {
            glExtensions.append((const char*)glGetStringi(GL_EXTENSIONS, i)).append(" ");
        }
    }
#endif

    FG_LOG_DEBUG("GFX: Using %s", glName.c_str());
    FG_LOG_DEBUG("GFX: GL vendor:     %s", glVendor.c_str());
    FG_LOG_DEBUG("GFX: GL renderer:   %s", glRenderer.c_str());
    FG_LOG_DEBUG("GFX: GL version:    %s", glVersion.c_str());
    FG_LOG_DEBUG("GFX: GLSL version:  %s", glSLVersion.c_str());
    FG_LOG_DEBUG("GFX: Extensions:    %s", (const char*)glExtensions.c_str());
    //glGetStringi(GL_EXTENSIONS, 0);
    CStringVector vparts;
    strings::split(glVersion, ' ', vparts);
    for(int i = 0; i < (int)vparts.size(); i++) {
        strings::trim(vparts[i]);
        if(strings::startsWith(vparts[i].c_str(), "3.0", FG_FALSE)) {
        } else if(strings::startsWith(vparts[i].c_str(), "3.1", FG_FALSE)) {
        }
    }
    //GLSL Version      OpenGL Version
    //1.10              2.0
    //1.20              2.1
    //1.30              3.0
    //1.40              3.1
    //1.50              3.2
    //3.30              3.3
    //4.00              4.0
    //4.10              4.1
    //4.20              4.2
    //4.30              4.3
    //4.40              4.4
    //4.50              4.5

    vparts.clear();
    g_SLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
    strings::split(glSLVersion, ' ', vparts);
    const char *selectedVersionNum = NULL;
    const char *selectedSLType = "GLSL";
    for(int i = 0; i < (int)vparts.size(); i++) {
        strings::trim(vparts[i]);
        if(strings::startsWith(vparts[i].c_str(), "1.0", FG_FALSE)) {
            if(g_fgBuildConfig.usingMarmaladeOpenGLES ||
               g_fgBuildConfig.usingMarmalade ||
               g_fgBuildConfig.isPlatformAndroid) {
                g_SLVersion = FG_GFX_ESSL_100;
                selectedSLType = "ESSL";
                selectedVersionNum = "1.0";
            }
        } else if(strings::startsWith(vparts[i].c_str(), "1.1", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_110;
            if(g_fgBuildConfig.usingMarmaladeOpenGLES ||
               g_fgBuildConfig.usingMarmalade ||
               g_fgBuildConfig.isPlatformAndroid) {
                g_SLVersion = FG_GFX_ESSL_100;
                selectedSLType = "ESSL";
                selectedVersionNum = "1.0";
            }
        } else if(strings::startsWith(vparts[i].c_str(), "1.2", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_120;
            selectedVersionNum = "1.2";
        } else if(strings::startsWith(vparts[i].c_str(), "1.3", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_130;
            selectedVersionNum = "1.3";
        } else if(strings::startsWith(vparts[i].c_str(), "1.4", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_140;
            selectedVersionNum = "1.4";
        } else if(strings::startsWith(vparts[i].c_str(), "1.5", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_150;
            selectedVersionNum = "1.5";
        } else if(strings::startsWith(vparts[i].c_str(), "3.0", FG_FALSE)) {
            if(g_fgBuildConfig.usingMarmaladeOpenGLES ||
               g_fgBuildConfig.usingMarmalade ||
               g_fgBuildConfig.isPlatformAndroid ||
               g_fgBuildConfig.usingOpenGLES) {
                g_SLVersion = FG_GFX_ESSL_300;
                selectedSLType = "ESSL";
                selectedVersionNum = "3.0";
                // If engine is using version 2.0 of OGLES
                if(major == 2) {
                    selectedVersionNum = "1.0";
                    g_SLVersion = FG_GFX_ESSL_100;
                }
            }
        } else if(strings::startsWith(vparts[i].c_str(), "3.3", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_330;
            selectedVersionNum = "3.3";
        } else if(strings::startsWith(vparts[i].c_str(), "4.0", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_400;
            selectedVersionNum = "4.0";
        } else if(strings::startsWith(vparts[i].c_str(), "4.1", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_410;
            selectedVersionNum = "4.1";
        } else if(strings::startsWith(vparts[i].c_str(), "4.2", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_420;
            selectedVersionNum = "4.2";
        } else if(strings::startsWith(vparts[i].c_str(), "4.3", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_430;
            selectedVersionNum = "4.3"; // #FIXME
        } else if(strings::startsWith(vparts[i].c_str(), "4.4", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_440;
            selectedVersionNum = "4.4";
        } else if(strings::startsWith(vparts[i].c_str(), "4.5", FG_FALSE)) {
            g_SLVersion = FG_GFX_GLSL_450;
            selectedVersionNum = "4.5";
        }
        if(g_SLVersion != FG_GFX_SHADING_LANGUAGE_INVALID)
            break;
    }
    if(selectedVersionNum) {
        FG_LOG_DEBUG("GFX: Selected shading language version: %s %s", selectedSLType, selectedVersionNum);
    }

    ParameterVecItor end = g_params.end(), itor = g_params.begin();
    for(; itor != end; itor++) {
        SContextParam &param = *itor;
        param.load();
        //printf("Parameter GFX: %d = %d\n", (int)itor->first, (int)param.boolVal);
    }

    g_contextInit = FG_TRUE;
    return FG_TRUE;
}

void gfx::context::destroy(void) {
#if defined(FG_USING_SDL2)
    if(g_GLContext)
        SDL_GL_DeleteContext(g_GLContext);
    g_GLContext = NULL;
#elif defined(FG_USING_EGL)
    if(g_GLContext) {
        eglDestroyContext(CPlatform::getDefaultDisplay(), g_GLContext);
        g_GLContext = NULL;
    }
#endif
    g_params.clear();
    g_contextInit = FG_FALSE;
}

gfx::SContextParam& gfx::context::getParam(const ParamType pname) {
    return g_params[(unsigned int)pname];
}

void gfx::context::enable(const ParamType cap) {
    g_params[(unsigned int)cap].set((fgGFXboolean)FG_GFX_TRUE);
}

void gfx::context::disable(const ParamType cap) {
    g_params[(unsigned int)cap].set((fgGFXboolean)FG_GFX_FALSE);
}

void gfx::context::setCapability(const ParamType cap, const fgBool toggle) {
    g_params[(unsigned int)cap].set((fgGFXboolean)toggle);
}

fgGFXboolean gfx::context::isEnabled(const ParamType pname) {
    return g_params[(unsigned int)pname].boolVal;
}

fgGFXboolean gfx::context::isDisabled(const ParamType pname) {
    return (fgGFXboolean)(FG_GFX_FALSE == g_params[(unsigned int)pname].boolVal);
}

fgGFXboolean gfx::context::isBuffer(const fgGFXuint buffer) {
    if(buffer == 0)
        return FG_GFX_FALSE;
    if(g_buffers.empty())
        return FG_GFX_FALSE;
    if(g_buffers.find(buffer) == g_buffers.end())
        return FG_GFX_FALSE;
    return FG_GFX_TRUE;
}

fgGFXboolean gfx::context::isBuffer(const SBufferID& bufferID) {
    return isBuffer(bufferID.id);
}

fgGFXboolean gfx::context::isBuffer(const SBufferID* bufferID) {
    if(!bufferID)
        return FG_GFX_FALSE;
    return isBuffer(bufferID->id);
}

//
//#define foreach(_container_type, _variable_scan) 
//	_container_type::iterator itor = _variable_scan.begin(), 
//	end = _variable_scan.end(); 
//	for(;itor!=end;itor++) 
//

void gfx::context::deleteAllBuffers(void) {
    if(g_buffers.empty())
        return;
    BufferMapItor itor = g_buffers.begin(), end = g_buffers.end();
    for(; itor != end; itor++) {
        SBufferID *buffer = itor->second;
        if(!buffer)
            continue;
        glDeleteBuffers(1, buffer->ptrID());
        GLCheckError("glDeleteBuffers");
        buffer->id = 0;
    }
    g_buffers.clear();
}

fgGFXboolean gfx::context::genBuffers(const int count,
                                      SBufferID*& buffers,
                                      const fgGFXenum usage) {
    if(count <= 0)
        return FG_GFX_FALSE;
    if(!buffers) {
        buffers = fgMalloc<SBufferID>(count);
    }
    for(int i = 0; i < count; i++) {
        SBufferID &buffer = buffers[i];
        buffer.usage = usage;
        buffer.target = (fgGFXenum)0;
        if(!isBuffer(buffer))
            glGenBuffers(1, buffer.ptrID());
        if(buffer.id)
            g_buffers[buffer.id] = &buffers[i];
    }
    return FG_GFX_TRUE;
}

void gfx::context::bufferData(SBufferID& bufferID,
                              const fgGFXsizei size,
                              const fgGFXvoid* data,
                              const fgGFXenum target,
                              const fgGFXenum usage) {
    if(!data)
        return;
    if((fgGFXenum)0 == target || (fgGFXenum)0 == bufferID.target) {
        bufferID.target = GL_ARRAY_BUFFER;
    }
    if(g_params[gfx::ARRAY_BUFFER_BINDING] != bufferID.id && bufferID.target == GL_ARRAY_BUFFER) {
        FG_LOG_ERROR("GFX: Invalid buffer bound, can't set buffer data");
        return;
    }
    if(g_params[gfx::ELEMENT_ARRAY_BUFFER_BINDING] != bufferID.id && bufferID.target == GL_ELEMENT_ARRAY_BUFFER) {
        FG_LOG_ERROR("GFX: Invalid buffer bound, can't set buffer data");

        return;
    }
    if(usage != (fgGFXenum)0)
        bufferID.usage = usage;
    if((fgGFXenum)0 == bufferID.usage)
        bufferID.usage = GL_STATIC_DRAW;
    glBufferData(bufferID.target, size, data, bufferID.usage);
    GLCheckError("glBufferData");
}

void gfx::context::bindBuffer(SBufferID& bufferID, const fgGFXenum target) {
    if(bufferID.id == 0)
        return;
    if(target != (fgGFXenum)0)
        bufferID.target = target;
    if((fgGFXenum)0 == bufferID.target)
        bufferID.target = GL_ARRAY_BUFFER;
    bindBuffer(bufferID.target, bufferID.id);
}

void gfx::context::bindBuffer(const fgGFXenum target, const fgGFXuint buffer) {
    if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
        g_params[gfx::ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
    } else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
        g_params[gfx::ELEMENT_ARRAY_BUFFER_BINDING].set((fgGFXint)buffer);
    }
}

fgGFXuint gfx::context::boundBuffer(const fgGFXenum target) {
    if(target == GL_ARRAY_BUFFER || target == GL_ARRAY_BUFFER_BINDING) {
        return g_params[gfx::ARRAY_BUFFER_BINDING];
    } else if(target == GL_ELEMENT_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER_BINDING) {
        return g_params[gfx::ELEMENT_ARRAY_BUFFER_BINDING];
    }
    return 0;
}

void gfx::context::deleteBuffer(SBufferID& bufferID) {
    if(bufferID.id == 0)
        return;
    if(g_buffers.empty())
        return;
    BufferMapItor itor = g_buffers.find(bufferID.id);
    if(itor == g_buffers.end())
        return;
    glDeleteBuffers(1, bufferID.ptrID());
    itor->second->id = 0;
    g_buffers.erase(itor);
}

void gfx::context::deleteBuffers(const int count, SBufferID* buffers) {
    if(count <= 0 || !buffers)
        return;
    for(int i = 0; i < count; i++)
        deleteBuffer(buffers[i]);
}

fgGFXuint gfx::context::boundTexture(void) {
    return g_boundTexture;
}

fgGFXuint gfx::context::activeTexture(void) {
    return g_params[gfx::ACTIVE_TEXTURE];
}

void gfx::context::activeTexture(const fgGFXenum texture) {
    g_params[gfx::ACTIVE_TEXTURE].set((fgGFXint)texture);
}

fgGFXboolean gfx::context::isTexture(const fgGFXuint texture) {
    if(texture == 0)
        return FG_GFX_FALSE;
    if(g_textures.empty())
        return FG_GFX_FALSE;
    if(g_textures.find(texture) == g_textures.end())
        return FG_GFX_FALSE;
    return FG_GFX_TRUE;
}

fgGFXboolean gfx::context::isTexture(const STextureID& textureID) {
    return isTexture(textureID.id);
}

void gfx::context::deleteAllTextures(void) {
    if(g_textures.empty())
        return;
    TextureMapItor itor = g_textures.begin(), end = g_textures.end();
    for(; itor != end; itor++) {
        STextureID *tex = itor->second;
        if(!tex)
            continue;
        glDeleteTextures(1, tex->ptrID());
        GLCheckError("glDeleteTextures");
        tex->id = 0;
    }
    g_textures.clear();
}

void gfx::context::genTextures(const int count,
                               STextureID* textures,
                               const fgGFXenum target/* = GL_TEXTURE_2D*/) {
    if(count <= 0 || !textures)
        return;
    if(!textures)
        return;
    for(int i = 0; i < count; i++) {
        genTexture(&textures[i]);
    }
}

void gfx::context::genTexture(STextureID* texture,
                              const fgGFXenum target/* = GL_TEXTURE_2D*/) {
    if(!texture)
        return;
    texture->target = target;
    if(texture->target != (fgGFXenum)0)
        texture->target = GL_TEXTURE_2D;
    glGenTextures(1, texture->ptrID());
    if(texture->id)
        g_textures[texture->id] = texture;
}

void gfx::context::deleteTextures(const int count, STextureID* textures) {
    if(count <= 0 || !textures)
        return;
    for(int i = 0; i < count; i++)
        deleteTexture(textures[i]);
}

void gfx::context::deleteTexture(STextureID& textureID) {
    if(textureID.id == 0)
        return;
    if(g_textures.empty())
        return;
    TextureMapItor itor = g_textures.find(textureID.id);
    if(itor == g_textures.end())
        return;
    glDeleteTextures(1, textureID.ptrID());
    textureID.id = 0;
    GLCheckError("glDeleteTextures");
    itor->second->id = 0;
    g_textures.erase(itor);
}

void gfx::context::bindTexture(STextureID& textureID, const fgGFXenum target/*=0*/) {
    if(textureID.id == 0)
        return;
    if(target != (fgGFXenum)0)
        textureID.target = target;
    if(textureID.target != (fgGFXenum)0)
        textureID.target = GL_TEXTURE_2D;
    if(textureID.target == GL_TEXTURE_2D) {
        bindTexture2D(textureID.id);
    } else if(/*textureID.target == GL_TEXTURE_3D*/0) {
        // #FIXME
    } else if(textureID.target == GL_TEXTURE_CUBE_MAP) {
        bindTextureCube(textureID.id);
    }
}

void gfx::context::bindTexture2D(const fgGFXuint texID) {
    g_params[gfx::TEXTURE_BINDING_2D].set((fgGFXint)texID);
    g_boundTexture = texID;
}

void gfx::context::bindTextureCube(const fgGFXuint texID) {
    g_params[gfx::TEXTURE_BINDING_CUBE_MAP].set((fgGFXint)texID);
    g_boundTexture = texID;
}

void gfx::context::blendEquation(const fgGFXenum mode) {
    SContextParam& modeRGB = g_params[gfx::BLEND_EQUATION_RGB];
    SContextParam& modeAlpha = g_params[gfx::BLEND_EQUATION_ALPHA];
    if(modeRGB.intVal != (fgGFXint)mode || modeAlpha.intVal != (fgGFXint)mode) {
        modeAlpha = modeRGB = mode;
        glBlendEquationSeparate(mode, mode);
    }
}

void gfx::context::blendFunc(const fgGFXenum sfactor, const fgGFXenum dfactor) {
    SContextParam& srcRGB = g_params[gfx::BLEND_SRC_RGB];
    SContextParam& dstRGB = g_params[gfx::BLEND_DST_RGB];
    SContextParam& srcAlpha = g_params[gfx::BLEND_SRC_ALPHA];
    SContextParam& dstAlpha = g_params[gfx::BLEND_DST_ALPHA];

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

void gfx::context::blendFunc(const fgGFXenum srcRGB,
                             const fgGFXenum dstRGB,
                             const fgGFXenum srcAlpha,
                             const fgGFXenum dstAlpha) {
    SContextParam& srcRGBparam = g_params[gfx::BLEND_SRC_RGB];
    SContextParam& dstRGBparam = g_params[gfx::BLEND_DST_RGB];
    SContextParam& srcAlphaparam = g_params[gfx::BLEND_SRC_ALPHA];
    SContextParam& dstAlphaparam = g_params[gfx::BLEND_DST_ALPHA];

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

void gfx::context::useProgram(const fgGFXuint program) {
    if(g_params[gfx::CURRENT_PROGRAM].intVal != (fgGFXint)program) {
        g_params[gfx::CURRENT_PROGRAM].set((fgGFXint)program);
    }
}

fgGFXuint gfx::context::activeProgram(void) {
    return g_params[gfx::CURRENT_PROGRAM];
}

void gfx::context::viewport(const fgGFXint x,
                            const fgGFXint y,
                            const fgGFXint width,
                            const fgGFXint height) {
    fgGFXuint areaQ = x * y + width*height;
    if(areaQ != g_viewportAreaQ) {
        g_viewportAreaQ = areaQ;
        g_params[gfx::VIEWPORT].set(x, y, width, height);
    }
}

void gfx::context::viewport(const Vector2i& pos,
                            const Vector2i& size) {
    viewport(pos.x, pos.y, size.x, size.y);
}

void gfx::context::viewport(const Vector4i& dimensions) {
    viewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

fgGFXfloat gfx::context::getViewportAspect(void) {
    fgGFXfloat y = (fgGFXfloat)g_params[(fgGFXuint)GL_VIEWPORT].ints[1];
    if(y <= FG_EPSILON)
        return 1.0f;
    return (fgGFXfloat)g_params[(fgGFXuint)GL_VIEWPORT].ints[0] / y;
}

void gfx::context::scissor(void) {
    scissor(0, 0, g_screenSize.x, g_screenSize.y);
}

void gfx::context::scissor(const fgGFXint x,
                           const fgGFXint y,
                           const fgGFXint width,
                           const fgGFXint height) {
    fgGFXuint areaQ = x * y + width*height;
    if(areaQ != g_scissorAreaQ) {
        g_scissorAreaQ = areaQ;
        g_params[gfx::SCISSOR_BOX].set(x, y, width, height);
    }
}

void gfx::context::scissor(const Vector2i& pos,
                           const Vector2i& size) {
    scissor(pos.x, pos.y, size.x, size.y);
}

void gfx::context::scissor(const Vector4i& dimensions) {
    scissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
}

fgGFXfloat gfx::context::getScissorAspect(void) {
    fgGFXfloat y = (fgGFXfloat)g_params[(fgGFXuint)GL_SCISSOR_BOX].ints[1];
    if(y <= FG_EPSILON)
        return 1.0f;
    return (fgGFXfloat)g_params[(fgGFXuint)GL_SCISSOR_BOX].ints[0] / y;
}

void gfx::context::setScissorTest(const fgBool toggle) {
    g_params[gfx::SCISSOR_TEST].set((fgGFXboolean)toggle);
}

void gfx::context::setDepthTest(const fgBool toggle) {
    g_params[gfx::DEPTH_TEST].set((fgGFXboolean)toggle);
}

void gfx::context::setCullFace(const fgBool toggle) {
    //gfxParamMapItor itor = m_params.find(gfx::CULL_FACE);
    g_params[gfx::CULL_FACE].set((fgGFXboolean)toggle);
}

void gfx::context::setBlend(const fgBool toggle) {
    g_params[gfx::BLEND].set((fgGFXboolean)toggle);
}

void gfx::context::frontFace(const fgGFXenum mode) {
    g_params[gfx::FRONT_FACE].set((fgGFXint)mode);
}

void gfx::context::cullFace(const fgGFXenum mode) {
    g_params[gfx::CULL_FACE_MODE].set((fgGFXint)mode);
}

void gfx::context::depthFunc(const fgGFXenum func) {
    g_params[gfx::DEPTH_FUNC].set((fgGFXint)func);
}

void gfx::context::clearDepth(const fgGFXfloat depth) {
    g_params[gfx::DEPTH_CLEAR_VALUE].set(depth);
}

void gfx::context::clearColor(const fgGFXfloat red,
                              const fgGFXfloat green,
                              const fgGFXfloat blue,
                              const fgGFXfloat alpha) {
    g_params[gfx::COLOR_CLEAR_VALUE].set(red, green, blue, alpha);
}

void gfx::context::clearStencil(const fgGFXint s) {
    g_params[gfx::STENCIL_CLEAR_VALUE].set(s);
}

fgGFXuint gfx::context::activeVertexAttribArrayMask(void) {
    return g_attribMask;
}

fgBool gfx::context::isVertexAttribArrayActive(const fgGFXuint index) {
    return g_attrInfo[index].isEnabled;
}

void gfx::context::updateAttribMask(const fgGFXuint index) {
    if(index == FG_GFX_ATTRIB_POS_LOCATION) {
        g_attribMask ^= FG_GFX_POSITION_BIT;
    } else if(index == FG_GFX_ATTRIB_NORM_LOCATION) {
        g_attribMask ^= FG_GFX_NORMAL_BIT;
    } else if(index == FG_GFX_ATTRIB_UVS_LOCATION) {
        g_attribMask ^= FG_GFX_UVS_BIT;
    } else if(index == FG_GFX_ATTRIB_COLOR_LOCATION) {
        g_attribMask ^= FG_GFX_COLOR_BIT;
    } else if(index == FG_GFX_ATTRIB_TANGENT_LOCATION) {
        g_attribMask ^= FG_GFX_TANGENT_BIT;
    }
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
 */

void gfx::context::enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask) {
    if(!g_attrInfo[index].isEnabled) {
        g_attrInfo[index].isEnabled = FG_GFX_TRUE;
        glEnableVertexAttribArray(index);
        if(updateMask)
            updateAttribMask(index);
    }
}

void gfx::context::disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask) {
    if(g_attrInfo[index].isEnabled) {
        g_attrInfo[index].isEnabled = FG_GFX_FALSE;
        glDisableVertexAttribArray(index);
        if(updateMask)
            updateAttribMask(index);
    }
}

void gfx::context::enableVertexAttribArrayMask(const fgGFXuint mask) {
    if(mask == g_attribMask)
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
    g_attribMask = mask;
}

void gfx::context::disableVertexAttribArrayMask(const fgGFXuint mask) {
    if(mask == g_attribMask)
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
    g_attribMask = mask;
}

void gfx::context::diffVertexAttribArrayMask(const fgGFXuint mask) {
    if(mask == g_attribMask)
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
    g_attribMask = mask;
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetVertexAttrib.xml
 */
fgGFXuint gfx::context::getVertexAttribBufferBinding(const fgGFXuint index) {
    return g_attrInfo[index].buffer;
}

fgGFXuint gfx::context::getVertexAttribSize(const fgGFXuint index) {
    return g_attrInfo[index].size;
}

fgGFXuint gfx::context::getVertexAttribStride(const fgGFXuint index) {
    if(index >= 12)
        return 0;
    return g_attrInfo[index].stride;
}

fgGFXenum gfx::context::getVertexAttribType(const fgGFXuint index) {
    if(index >= 12)
        return (fgGFXenum)0;
    return g_attrInfo[index].type;
}

fgGFXboolean gfx::context::getVertexAttribNormalized(const fgGFXuint index) {
    // #FIXME checks
    if(index >= 12)
        return FG_GFX_FALSE;
    return g_attrInfo[index].isNormalized;
}

/*
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
 */
void gfx::context::vertexAttribPointer(fgGFXuint index,
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
    SAttributeData &attr = g_attrInfo[index];
    attr.index = index;
    attr.size = size;
    attr.dataType = type;
    attr.isNormalized = normalized;
    attr.stride = stride;
    attr.pointer = ptr;
    attr.buffer = g_params[gfx::ARRAY_BUFFER_BINDING];
    glVertexAttribPointer(index, size, type, normalized, stride, ptr);
    GLCheckError("glVertexAttribPointer"); // #FIXME
}

void gfx::context::vertexAttribPointer(SAttributeData& attrData) {
    fgGFXint index = attrData.index;
    if(index < 0)
        return;
    fgGFXboolean isEnabled = g_attrInfo[index].isEnabled;
    g_attrInfo[index] = attrData;
    g_attrInfo[index].isEnabled = isEnabled;
    g_attrInfo[index].buffer = g_params[gfx::ARRAY_BUFFER_BINDING];

    glVertexAttribPointer(attrData.index,
                          attrData.size,
                          attrData.dataType,
                          attrData.isNormalized,
                          attrData.stride,
                          attrData.pointer);
    GLCheckError("glVertexAttribPointer"); // #FIXME
}
