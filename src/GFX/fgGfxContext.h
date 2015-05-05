/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_CONTEXT
    #define FG_INC_GFX_CONTEXT
    #define FG_INC_GFX_CONTEXT_BLOCK

    #ifndef FG_INC_GFX_GL
        #include "fgGfxGL.h"
    #endif

    #ifndef FG_INC_GFX_TYPES
        #include "fgGfxTypes.h"
    #endif

    #define FG_GFX_PARAM_INVALID                0
    #define FG_GFX_PARAM_BOOL                   1
    #define FG_GFX_PARAM_FLOAT                  2
    #define FG_GFX_PARAM_INT                    3
    #define FG_GFX_PARAM_ATTRIB                 4
    #define FG_GFX_PARAM_BLEND_FUNC             5
    #define FG_GFX_PARAM_BLEND_EQ               6
    #define FG_GFX_PARAM_BLEND_COLOR            7
    #define FG_GFX_PARAM_VIEWPORT               8
    #define FG_GFX_PARAM_SCISSOR                9
    #define FG_GFX_PARAM_TEXTURE_2D             10
    #define FG_GFX_PARAM_TEXTURE_3D             11
    #define FG_GFX_PARAM_TEXTURE                12
    #define FG_GFX_PARAM_VERT_BUFFER_BIND       13
    #define FG_GFX_PARAM_ELEM_BUFFER_BIND       14
    #define FG_GFX_PARAM_CLEAR_DEPTH            15
    #define FG_GFX_PARAM_CLEAR_COLOR            16
    #define FG_GFX_PARAM_COLOR_MASK		17
    #define FG_GFX_PARAM_FRONT_FACE		18
    #define FG_GFX_PARAM_CULL_FACE		19
    #define FG_GFX_PARAM_PROGRAM		20
    #define FG_GFX_PARAM_DEPTH_FUNC		21
    #define FG_GFX_PARAM_DEPTH_RANGE		22
    #define FG_GFX_PARAM_DEPTH_MASK		23
    #define FG_GFX_PARAM_FRAME_BUFFER_BIND      24
    #define FG_GFX_PARAM_RENDER_BUFFER_BIND     25
    #define FG_GFX_PARAM_HINT                   26
    #define FG_GFX_PARAM_SAMPLE_COVERAGE        27
    #define FG_GFX_PARAM_STENCIL_FUNC		28
    #define FG_GFX_PARAM_STENCIL_OP		29
    #define FG_GFX_PARAM_STENCIL_MASK		30
    #define FG_GFX_PARAM_CLEAR_STENCIL		31
    #define FG_GFX_PARAM_PIXEL_STORE		32


namespace fg {
    namespace gfx {

        /**
         * Enumeration for GL/GFX parameters that can be set on the server side
         * It's used mainly for mirroring on the client side, fast check if the
         * parameter value should be changed/updated. 
         */
        enum ParamType {
            /// a single value indicating the active multitexture unit
            /// The initial value is GL_TEXTURE0
            /// Supported by OpenGL ES 2.0+
            /// @see glActiveTexture
            ACTIVE_TEXTURE,

            /// a pair of values indicating the range of widths supported for
            /// aliased lines. 
            /// Supported by OpenGL ES 2.0+
            /// @see glLineWidth
            ALIASED_LINE_WIDTH_RANGE,

            /// two values, the smallest and largest supported sizes for aliased
            /// points. The range must include size 1.
            /// Supported *only* by OpenGL ES 2.0+
            ALIASED_POINT_SIZE_RANGE,

            /// one value, the number of alpha bitplanes in the color buffer of
            /// the currently bound framebuffer
            /// Supported *only* by OpenGL ES 2.0+
            ALPHA_BITS,

            /// a single value, the name of the buffer object currently bound to
            /// the target GL_ARRAY_BUFFER. If no buffer object is bound to this
            /// target, 0 is returned. The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBindBuffer
            ARRAY_BUFFER_BINDING,

            /// a single boolean value indicating whether blending is enabled. 
            /// The initial value is GL_FALSE.
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendFunc
            BLEND,

            /// four values, the red, green, blue, and alpha values which are 
            /// the components of the blend color. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendColor
            BLEND_COLOR,

            /// one value, the symbolic constant identifying the alpha destination
            /// blend function. The initial value is GL_ZERO.
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendFunc
            /// @see glBlendFuncSeparate
            BLEND_DST_ALPHA,

            /// one value, the symbolic constant identifying the RGB destination
            /// blend function. The initial value is GL_ZERO. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendFunc
            /// @see glBlendFuncSeparate
            BLEND_DST_RGB,

            /// one value, a symbolic constant indicating whether the RGB blend 
            /// equation is GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT,
            /// GL_MIN or GL_MAX.
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendEquationSeparate
            /// @see glBlendEquationSeparateiEXT
            BLEND_EQUATION_RGB,

            /// one value, a symbolic constant indicating whether the Alpha blend
            /// equation is GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, 
            /// GL_MIN or GL_MAX. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendEquationSeparate
            /// @see glBlendEquationSeparateiEXT
            BLEND_EQUATION_ALPHA,

            /// one value, the symbolic constant identifying the alpha source blend
            /// function. The initial value is GL_ONE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendFunc
            /// @see glBlendFuncSeparate
            BLEND_SRC_ALPHA,

            /// one value, the symbolic constant identifying the RGB source blend
            /// function. The initial value is GL_ONE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBlendFunc
            /// @see glBlendFuncSeparate
            BLEND_SRC_RGB,

            /// four values: the red, green, blue, and alpha values used to clear
            /// the color buffers. Integer values, if requested, are linearly 
            /// mapped from the internal floating-point representation such that 
            /// 1.0 returns the most positive representable integer value, and 
            /// -1.0 returns the most negative representable integer value. 
            /// The initial value is (0, 0, 0, 0). 
            /// Supported by OpenGL ES 2.0+
            /// @see glClearColor
            COLOR_CLEAR_VALUE,

            /// a single boolean value indicating whether a fragment's RGBA color
            /// values are merged into the framebuffer using a logical operation.
            /// The initial value is GL_FALSE. 
            /// @see glLogicOp
            COLOR_LOGIC_OP,

            /// four boolean values: the red, green, blue, and alpha write enables
            /// for the color buffers. The initial value is (GL_TRUE, GL_TRUE,
            /// GL_TRUE, GL_TRUE). 
            /// Supported by OpenGL ES 2.0+
            /// @see glColorMask
            COLOR_WRITEMASK,

            /// a list of symbolic constants of length GL_NUM_COMPRESSED_TEXTURE_FORMATS 
            /// indicating which compressed texture formats are available.
            /// Supported by OpenGL ES 2.0+
            /// @see glCompressedTexImage2D
            COMPRESSED_TEXTURE_FORMATS,

            /// one value, the maximum number of active shader storage blocks 
            /// that may be accessed by a compute shader.
            MAX_COMPUTE_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum total number of active shader storage blocks
            /// that may be accessed by all active shaders.
            MAX_COMBINED_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum number of uniform blocks per compute shader.
            /// The value must be at least 14. 
            /// @see glUniformBlockBinding
            MAX_COMPUTE_UNIFORM_BLOCKS,

            /// one value, the maximum supported texture image units that can be
            /// used to access texture maps from the compute shader. The value 
            /// may be at least 16.
            /// @see glActiveTexture
            MAX_COMPUTE_TEXTURE_IMAGE_UNITS,

            /// one value, the maximum number of individual floating-point, 
            /// integer, or boolean values that can be held in uniform variable
            /// storage for a compute shader. The value must be at least 1024.
            /// @see glUniform
            MAX_COMPUTE_UNIFORM_COMPONENTS,

            /// a single value, the maximum number of atomic counters available
            /// to compute shaders.
            MAX_COMPUTE_ATOMIC_COUNTERS,

            /// a single value, the maximum number of atomic counter buffers 
            /// that may be accessed by a compute shader.
            MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,

            /// one value, the number of words for compute shader uniform 
            /// variables in all uniform blocks (including default). The value 
            /// must be at least 1. 
            /// @see glUniform
            MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,

            /// one value, the number of invocations in a single local work group
            /// (i.e., the product of the three dimensions) that may be dispatched
            /// to a compute shader.
            MAX_COMPUTE_WORK_GROUP_INVOCATIONS,

            /// Accepted by the indexed versions of glGet. 
            /// Maximum number of work groups that may be dispatched to a compute
            /// shader. Indices 0, 1, and 2 correspond to the X, Y and Z
            /// dimensions, respectively.
            MAX_COMPUTE_WORK_GROUP_COUNT,

            // Accepted by the indexed versions of glGet. 
            /// Maximum size of a work groups that may be used during compilation
            /// of a compute shader. Indices 0, 1, and 2 correspond to the X, Y 
            /// and Z dimensions, respectively.
            MAX_COMPUTE_WORK_GROUP_SIZE,

            /// a single value, the name of the buffer object currently bound to
            /// the target GL_DISPATCH_INDIRECT_BUFFER. If no buffer object is 
            /// bound to this target, 0 is returned. The initial value is 0.
            /// @see glBindBuffer
            DISPATCH_INDIRECT_BUFFER_BINDING,

            /// a single value, the maximum depth of the debug message group stack
            MAX_DEBUG_GROUP_STACK_DEPTH,

            /// a single value, the current depth of the debug message group stack
            DEBUG_GROUP_STACK_DEPTH,

            /// one value, the flags with which the context was created 
            /// (such as debugging functionality)
            CONTEXT_FLAGS,

            /// a single boolean value indicating whether polygon culling is 
            /// enabled. The initial value is GL_FALSE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glCullFace
            CULL_FACE,

            /// one value, symbolic constant indicating which polygon faces are 
            /// to be culled. The initial value is GL_BACK.
            /// Supported by OpenGL ES 2.0+
            /// @see glCullFace
            CULL_FACE_MODE,

            FRONT_FACE,

            /// one value, the name of the program object that is currently 
            /// active, or 0 if no program object is active.
            /// Supported by OpenGL ES 2.0+
            /// @see glUseProgram
            CURRENT_PROGRAM,

            /// one value, the value that is used to clear the depth buffer. 
            /// Integer values, if requested, are linearly mapped from the 
            /// internal floating-point representation such that 1.0 returns 
            /// the most positive representable integer value, and -1.0 returns
            /// the most negative representable integer value. 
            /// The initial value is 1. 
            /// Supported by OpenGL ES 2.0+
            /// @see glClearDepth
            DEPTH_CLEAR_VALUE,

            /// one value, the symbolic constant that indicates the depth 
            /// comparison function. The initial value is GL_LESS. 
            /// Supported by OpenGL ES 2.0+
            /// @see glDepthFunc
            DEPTH_FUNC,

            /// two values: the near and far mapping limits for the depth buffer
            /// Integer values, if requested, are linearly mapped from the 
            /// internal floating-point representation such that 1.0 returns the
            /// most positive representable integer value, and -1.0 returns the 
            /// most negative representable integer value. 
            /// The initial value is (0, 1). 
            /// Supported by OpenGL ES 2.0+
            /// @see glDepthRange
            DEPTH_RANGE,

            /// a single boolean value indicating whether depth testing of 
            /// fragments is enabled. The initial value is GL_FALSE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glDepthFunc
            /// @see glDepthRange
            DEPTH_TEST,

            /// a single boolean value indicating if the depth buffer is enabled
            /// for writing. The initial value is GL_TRUE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glDepthMask
            DEPTH_WRITEMASK,

            /// a single boolean value indicating whether dithering of fragment
            /// colors and indices is enabled. The initial value is GL_TRUE.
            /// Supported by OpenGL ES 2.0+
            DITHER,

            /// boolean value indicating whether double buffering is supported.
            DOUBLEBUFFER,

            /// a symbolic constant indicating which buffers are being drawn to.             
            /// The initial value is GL_BACK if there are back buffers,
            /// otherwise it is GL_FRONT.
            /// @see glDrawBuffer
            DRAW_BUFFER,

            /// one value, a symbolic constant indicating which buffers are being
            /// drawn to by the corresponding output color. The initial value of
            /// GL_DRAW_BUFFER0 is GL_BACK if there are back buffers, otherwise 
            /// it is GL_FRONT. The initial values of draw buffers for all other
            /// output colors is GL_NONE.
            /// @see glDrawBuffers
            DRAW_BUFFER0,
            DRAW_BUFFER1,
            DRAW_BUFFER2,
            DRAW_BUFFER3,
            DRAW_BUFFER4,
            DRAW_BUFFER5,
            DRAW_BUFFER6,
            DRAW_BUFFER7,
            DRAW_BUFFER8,
            DRAW_BUFFER9,
            DRAW_BUFFER10,
            DRAW_BUFFER11,
            DRAW_BUFFER12,
            DRAW_BUFFER13,
            DRAW_BUFFER14,
            DRAW_BUFFER15,

            /// one value, the name of the framebuffer object currently bound to
            /// the GL_DRAW_FRAMEBUFFER target. If the default framebuffer is 
            /// bound, this value will be zero. The initial value is zero. 
            /// Supported by OpenGL ES 2.0+ (as GL_FRAMEBUFFER_BINDING)
            /// @see glBindFramebuffer
            DRAW_FRAMEBUFFER_BINDING,
            FRAMEBUFFER_BINDING = DRAW_FRAMEBUFFER_BINDING,

            /// one value, the name of the framebuffer object currently bound to
            /// the GL_READ_FRAMEBUFFER target. If the default framebuffer is 
            /// bound, this value will be zero. The initial value is zero. 
            /// @see glBindFramebuffer
            READ_FRAMEBUFFER_BINDING,

            /// a single value, the name of the buffer object currently bound to
            /// the target GL_ELEMENT_ARRAY_BUFFER. If no buffer object is bound
            /// to this target, 0 is returned. The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBindBuffer
            ELEMENT_ARRAY_BUFFER_BINDING,

            /// one value, a symbolic constant indicating the mode of the 
            /// derivative accuracy hint for fragment shaders. 
            /// The initial value is GL_DONT_CARE. 
            /// @see glHint
            FRAGMENT_SHADER_DERIVATIVE_HINT,

            /// a single GLenum value indicating the implementation's preferred 
            /// pixel data format
            /// Supported by OpenGL ES 2.0+. 
            /// @see glReadPixels
            IMPLEMENTATION_COLOR_READ_FORMAT,

            /// a single GLenum value indicating the implementation's preferred 
            /// pixel data type. 
            /// Supported by OpenGL ES 2.0+
            /// @see glReadPixels
            IMPLEMENTATION_COLOR_READ_TYPE,

            /// a single boolean value indicating whether antialiasing of lines 
            /// is enabled. The initial value is GL_FALSE. 
            /// *Not* in OpenGL ES 2.0
            /// @see glLineWidth
            LINE_SMOOTH,

            /// one value, a symbolic constant indicating the mode of the line
            /// antialiasing hint. The initial value is GL_DONT_CARE. 
            /// @see glHint
            /// *Not* in OpenGL ES 2.0
            LINE_SMOOTH_HINT,

            /// one value, the line width as specified with glLineWidth. 
            /// The initial value is 1.
            /// Supported by OpenGL ES 2.0+
            LINE_WIDTH,

            /// one value, the implementation dependent specific vertex of a 
            /// primitive that is used to select the rendering layer. 
            /// If the value returned is equivalent to GL_PROVOKING_VERTEX, 
            /// then the vertex selection follows the convention specified by 
            /// glProvokingVertex. If the value returned is equivalent to 
            /// GL_FIRST_VERTEX_CONVENTION, then the selection is always taken 
            /// from the first vertex in the primitive. If the value returned is
            /// equivalent to GL_LAST_VERTEX_CONVENTION, then the selection is 
            /// always taken from the last vertex in the primitive. 
            /// If the value returned is equivalent to GL_UNDEFINED_VERTEX, 
            /// then the selection is not guaranteed to be taken from any 
            /// specific vertex in the primitive.
            LAYER_PROVOKING_VERTEX,

            /// one value, a symbolic constant indicating the selected logic 
            /// operation mode. The initial value is GL_COPY. 
            /// @see glLogicOp
            LOGIC_OP_MODE,

            /// one value, the major version number of the OpenGL API supported 
            /// by the current context.
            /// *Not* in OpenGL ES 2.0
            MAJOR_VERSION,

            /// one value, a rough estimate of the largest 3D texture that the 
            /// GL can handle. The value must be at least 64. 
            /// Use GL_PROXY_TEXTURE_3D to determine if a texture is too large. 
            /// *Not* in OpenGL ES 2.0
            /// @see glTexImage3D
            MAX_3D_TEXTURE_SIZE,

            /// one value. The value indicates the maximum number of layers 
            /// allowed in an array texture, and must be at least 256. 
            /// @see glTexImage2D
            MAX_ARRAY_TEXTURE_LAYERS,

            /// one value, the maximum number of application-defined clipping
            /// distances. The value must be at least 8.
            MAX_CLIP_DISTANCES,

            /// the maximum number of samples in a color multisample texture.
            MAX_COLOR_TEXTURE_SAMPLES,

            /// a single value, the maximum number of atomic counters available
            /// to all active shaders.
            MAX_COMBINED_ATOMIC_COUNTERS,

            /// one value, the number of words for fragment shader uniform
            /// variables in all uniform blocks (including default). The value 
            /// must be at least 1. 
            /// @see glUniform
            MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,

            /// one value, the number of words for geometry shader uniform 
            /// variables in all uniform blocks (including default). The value 
            /// must be at least 1.
            /// @see glUniform
            MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,

            /// one value, the maximum supported texture image units that can be
            /// used to access texture maps from the vertex shader and the
            /// fragment processor combined. If both the vertex shader and the 
            /// fragment processing stage access the same texture image unit,
            /// then that counts as using two texture image units against this 
            /// limit. The value must be at least 48. 
            /// Supported by OpenGL ES 2.0+
            /// @see glActiveTexture
            MAX_COMBINED_TEXTURE_IMAGE_UNITS,

            /// one value, the maximum number of uniform blocks per program. 
            /// The value must be at least 70. 
            /// @see glUniformBlockBinding
            MAX_COMBINED_UNIFORM_BLOCKS,

            /// one value, the number of words for vertex shader uniform variables
            /// in all uniform blocks (including default). 
            /// The value must be at least 1. 
            /// @see glUniform
            MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,

            /// one value. The value gives a rough estimate of the largest 
            /// cube-map texture that the GL can handle. The value must be at 
            /// least 1024. Use GL_PROXY_TEXTURE_CUBE_MAP to determine if a 
            /// texture is too large. 
            /// Supported by OpenGL ES 2.0+
            /// @see glTexImage2D
            MAX_CUBE_MAP_TEXTURE_SIZE,

            /// one value, the maximum number of samples in a multisample depth 
            /// or depth-stencil texture.
            MAX_DEPTH_TEXTURE_SAMPLES,

            /// one value, the maximum number of simultaneous outputs that may 
            /// be written in a fragment shader. The value must be at least 8. 
            /// @see glDrawBuffers
            MAX_DRAW_BUFFERS,

            /// one value, the maximum number of active draw buffers when using 
            /// dual-source blending. The value must be at least 1. 
            /// @see glBlendFunc 
            /// @see glBlendFuncSeparate
            MAX_DUAL_SOURCE_DRAW_BUFFERS,

            /// one value, the recommended maximum number of vertex array indices
            /// @see glDrawRangeElements
            MAX_ELEMENTS_INDICES,

            /// one value, the recommended maximum number of vertex array vertices.
            /// @see glDrawRangeElements
            MAX_ELEMENTS_VERTICES,

            /// a single value, the maximum number of atomic counters available
            /// to fragment shaders.
            MAX_FRAGMENT_ATOMIC_COUNTERS,

            /// one value, the maximum number of active shader storage blocks
            /// that may be accessed by a fragment shader.
            MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum number of components of the inputs read 
            /// by the fragment shader, which must be at least 128.
            MAX_FRAGMENT_INPUT_COMPONENTS,

            /// one value, the maximum number of individual floating-point, 
            /// integer, or boolean values that can be held in uniform variable 
            /// storage for a fragment shader. The value must be at least 1024. 
            /// @see glUniform
            MAX_FRAGMENT_UNIFORM_COMPONENTS,

            /// one value, the maximum number of individual 4-vectors of 
            /// floating-point, integer, or boolean values that can be held in 
            /// uniform variable storage for a fragment shader. The value is 
            /// equal to the value of GL_MAX_FRAGMENT_UNIFORM_COMPONENTS divided
            /// by 4 and must be at least 256. 
            /// Supported by OpenGL ES 2.0+
            /// @see glUniform
            MAX_FRAGMENT_UNIFORM_VECTORS,

            /// one value, the maximum number of uniform blocks per fragment 
            /// shader. The value must be at least 12. 
            /// @see glUniformBlockBinding
            MAX_FRAGMENT_UNIFORM_BLOCKS,

            /// one value, the maximum width for a framebuffer that has no 
            /// attachments, which must be at least 16384. 
            /// @see glFramebufferParameter
            MAX_FRAMEBUFFER_WIDTH,

            /// one value, the maximum height for a framebuffer that has no 
            /// attachments, which must be at least 16384. 
            /// @see glFramebufferParameter
            MAX_FRAMEBUFFER_HEIGHT,

            /// one value, the maximum number of layers for a framebuffer that 
            /// has no attachments, which must be at least 2048. 
            /// @see glFramebufferParameter
            MAX_FRAMEBUFFER_LAYERS,

            /// one value, the maximum samples in a framebuffer that has no
            /// attachments, which must be at least 4. 
            /// @see glFramebufferParameter
            MAX_FRAMEBUFFER_SAMPLES,

            /// a single value, the maximum number of atomic counters available
            /// to geometry shaders.
            MAX_GEOMETRY_ATOMIC_COUNTERS,

            /// one value, the maximum number of active shader storage blocks 
            /// that may be accessed by a geometry shader.
            MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum number of components of inputs read by a 
            /// geometry shader, which must be at least 64.
            MAX_GEOMETRY_INPUT_COMPONENTS,

            /// one value, the maximum number of components of outputs written
            /// by a geometry shader, which must be at least 128.
            MAX_GEOMETRY_OUTPUT_COMPONENTS,

            /// one value, the maximum supported texture image units that can be
            /// used to access texture maps from the geometry shader. The value 
            /// must be at least 16.
            /// @see glActiveTexture
            MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,

            /// one value, the maximum number of uniform blocks per geometry shader.
            /// The value must be at least 12. 
            /// @see glUniformBlockBinding
            MAX_GEOMETRY_UNIFORM_BLOCKS,

            /// one value, the maximum number of individual floating-point, 
            /// integer, or boolean values that can be held in uniform variable 
            /// storage for a geometry shader. The value must be at least 1024.
            /// @see glUniform
            MAX_GEOMETRY_UNIFORM_COMPONENTS,

            /// one value, the maximum number of samples supported in integer 
            /// format multisample buffers.
            MAX_INTEGER_SAMPLES,

            /// one value, the minimum alignment in basic machine units of 
            /// pointers returned fromglMapBuffer and glMapBufferRange. 
            /// This value must be a power of two and must be at least 64.
            MIN_MAP_BUFFER_ALIGNMENT,

            /// one value, the maximum length of a label that may be assigned 
            /// to an object. 
            /// @see glObjectLabel
            /// @see glObjectPtrLabel
            MAX_LABEL_LENGTH,

            /// one value, the maximum texel offset allowed in a texture lookup,
            /// which must be at least 7.
            MAX_PROGRAM_TEXEL_OFFSET,

            /// one value, the minimum texel offset allowed in a texture lookup,
            /// which must be at most -8.
            MIN_PROGRAM_TEXEL_OFFSET,

            /// one value. The value gives a rough estimate of the largest 
            /// rectangular texture that the GL can handle. The value must be at
            /// least 1024. Use GL_PROXY_TEXTURE_RECTANGLE to determine if a 
            /// texture is too large. 
            /// @see glTexImage2D
            MAX_RECTANGLE_TEXTURE_SIZE,

            /// The value indicates the maximum supported size for renderbuffers
            /// Supported by OpenGL ES 2.0+
            /// @see glFramebufferRenderbuffer
            MAX_RENDERBUFFER_SIZE,

            /// one value, the maximum number of sample mask words.
            MAX_SAMPLE_MASK_WORDS,

            /// one value, the maximum glWaitSync timeout interval.
            MAX_SERVER_WAIT_TIMEOUT,

            /// one value, the maximum number of shader storage buffer binding 
            /// points on the context, which must be at least 8.
            MAX_SHADER_STORAGE_BUFFER_BINDINGS,

            /// a single value, the maximum number of atomic counters available 
            /// to tessellation control shaders.
            MAX_TESS_CONTROL_ATOMIC_COUNTERS,

            /// a single value, the maximum number of atomic counters available 
            /// to tessellation evaluation shaders.
            MAX_TESS_EVALUATION_ATOMIC_COUNTERS,

            /// one value, the maximum number of active shader storage blocks 
            /// that may be accessed by a tessellation control shader.
            MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum number of active shader storage blocks 
            /// that may be accessed by a tessellation evaluation shader.
            MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,

            /// one value. The value gives the maximum number of texels allowed 
            ///  in the texel array of a texture buffer object. 
            /// Value must be at least 65536.
            MAX_TEXTURE_BUFFER_SIZE,

            /// one value, the maximum supported texture image units that can be
            /// used to access texture maps from the fragment shader. The value
            /// must be at least 16. 
            /// Supported by OpenGL ES 2.0+
            /// @see glActiveTexture
            MAX_TEXTURE_IMAGE_UNITS,

            /// one value, the maximum, absolute value of the texture 
            /// level-of-detail bias. The value must be at least 2.0.
            MAX_TEXTURE_LOD_BIAS,

            /// one value. The value gives a rough estimate of the largest
            /// texture that the GL can handle. The value must be at least 1024.
            /// Use a proxy texture target such as GL_PROXY_TEXTURE_1D or 
            /// GL_PROXY_TEXTURE_2D to determine if a texture is too large.
            /// @see glTexImage1D 
            /// @see glTexImage2D
            MAX_TEXTURE_SIZE,

            /// one value, the maximum number of uniform buffer binding points 
            /// on the context, which must be at least 36.
            MAX_UNIFORM_BUFFER_BINDINGS,

            /// one value, the maximum size in basic machine units of a uniform
            /// block, which must be at least 16384.
            MAX_UNIFORM_BLOCK_SIZE,

            /// one value, the maximum number of explicitly assignable uniform
            /// locations, which must be at least 1024.
            MAX_UNIFORM_LOCATIONS,

            /// one value, the number components for varying variables, which
            /// must be at least 60.
            MAX_VARYING_COMPONENTS,

            /// one value, the number 4-vectors for varying variables, which is
            /// equal to the value of GL_MAX_VARYING_COMPONENTS and must be at least 15.
            MAX_VARYING_VECTORS,

            /// one value, the maximum number of interpolators available for 
            /// processing varying variables used by vertex and fragment shaders
            /// This value represents the number of individual floating-point
            /// values that can be interpolated; varying variables declared as 
            /// vectors, matrices, and arrays will all consume multiple
            /// interpolators. The value must be at least 32.
            MAX_VARYING_FLOATS,

            /// a single value, the maximum number of atomic counters available 
            /// to vertex shaders.
            MAX_VERTEX_ATOMIC_COUNTERS,

            /// one value, the maximum number of 4-component generic vertex 
            /// attributes accessible to a vertex shader. 
            /// The value must be at least 16. 
            /// @see glVertexAttrib
            MAX_VERTEX_ATTRIBS,

            /// one value, the maximum number of active shader storage blocks 
            /// that may be accessed by a vertex shader.
            MAX_VERTEX_SHADER_STORAGE_BLOCKS,

            /// one value, the maximum supported texture image units that can be
            /// used to access texture maps from the vertex shader. The value 
            /// may be at least 16
            /// @see glActiveTexture
            MAX_VERTEX_TEXTURE_IMAGE_UNITS,

            /// one value, the maximum number of individual floating-point,
            /// integer, or boolean values that can be held in uniform variable 
            /// storage for a vertex shader. The value must be at least 1024. 
            /// *Not* in OpenGL ES 2.0
            /// @see glUniform
            MAX_VERTEX_UNIFORM_COMPONENTS,

            /// one value, the maximum number of 4-vectors that may be held in 
            /// uniform variable storage for the vertex shader. 
            /// The value of GL_MAX_VERTEX_UNIFORM_VECTORS is equal to the value
            /// of GL_MAX_VERTEX_UNIFORM_COMPONENTS and must be at least 256.
            /// Supported by OpenGL ES 2.0+
            MAX_VERTEX_UNIFORM_VECTORS,

            /// one value, the maximum number of components of output written by
            /// a vertex shader, which must be at least 64.
            /// *Not* in OpenGL ES 2.0
            MAX_VERTEX_OUTPUT_COMPONENTS,

            /// one value, the maximum number of uniform blocks per vertex shader
            /// The value must be at least 12. 
            /// @see glUniformBlockBinding
            /// *Not* in OpenGL ES 2.0
            MAX_VERTEX_UNIFORM_BLOCKS,

            /// two values: the maximum supported width and height of the viewport.
            /// These must be at least as large as the visible dimensions of the
            /// display being rendered to.
            /// Supported by OpenGL ES 2.0+
            /// @see glViewport
            MAX_VIEWPORT_DIMS,

            /// one value, the maximum number of simultaneous viewports that are
            /// supported. The value must be at least 16. 
            /// @see glViewportIndexed
            MAX_VIEWPORTS,

            /// one value, the minor version number of the OpenGL API supported 
            /// by the current context.
            /// *Not* in OpenGL ES 2.0
            MINOR_VERSION,

            /// a single integer value indicating the number of available 
            /// compressed texture formats. The minimum value is 4. 
            /// @see glCompressedTexImage2D
            NUM_COMPRESSED_TEXTURE_FORMATS,

            /// one value, the number of extensions supported by the GL 
            /// implementation for the current context. 
            /// @see glGetString
            NUM_EXTENSIONS,

            /// one value, the number of program binary formats supported by 
            /// the implementation.
            NUM_PROGRAM_BINARY_FORMATS,

            /// one value, the number of binary shader formats supported by the
            /// implementation. If this value is greater than zero, then the
            /// implementation supports loading binary shaders. If it is zero,
            /// then the loading of binary shaders by the implementation
            /// is not supported.
            NUM_SHADER_BINARY_FORMATS,

            /// Supported *only* by OpenGL ES 2.0+
            SHADER_BINARY_FORMATS,

            /// one value, the byte alignment used for writing pixel data to 
            /// memory. The initial value is 4. 
            /// Supported by OpenGL ES 2.0+
            /// @see glPixelStore
            PACK_ALIGNMENT,

            /// one value, the image height used for writing pixel data to memory.
            /// The initial value is 0. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_IMAGE_HEIGHT,

            /// a single boolean value indicating whether single-bit pixels 
            /// being written to memory are written first to the least significant
            /// bit of each unsigned byte. The initial value is GL_FALSE. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_LSB_FIRST,

            /// one value, the row length used for writing pixel data to memory.
            /// The initial value is 0.
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_ROW_LENGTH,

            /// one value, the number of pixel images skipped before the first 
            /// pixel is written into memory. The initial value is 0. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_SKIP_IMAGES,

            /// one value, the number of pixel locations skipped before the 
            /// first pixel is written into memory. The initial value is 0. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_SKIP_PIXELS,

            /// one value, the number of rows of pixel locations skipped before 
            /// the first pixel is written into memory. The initial value is 0.
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore
            PACK_SKIP_ROWS,

            /// a single boolean value indicating whether the bytes of two-byte 
            /// and four-byte pixel indices and components are swapped before 
            /// being written to memory. The initial value is GL_FALSE. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPixelStore.
            PACK_SWAP_BYTES,

            /// a single value, the name of the buffer object currently bound to 
            /// the target GL_PIXEL_PACK_BUFFER. If no buffer object is bound to
            /// this target, 0 is returned. The initial value is 0. 
            /// *Not* in OpenGL ES 2.0
            /// @see glBindBuffer
            PIXEL_PACK_BUFFER_BINDING,

            /// a single value, the name of the buffer object currently bound to
            /// the target GL_PIXEL_UNPACK_BUFFER. If no buffer object is bound 
            /// to this target, 0 is returned. The initial value is 0.
            /// *Not* in OpenGL ES 2.0
            /// @see glBindBuffer
            PIXEL_UNPACK_BUFFER_BINDING,

            /// the point size threshold for determining the point size.
            /// *Not* in OpenGL ES 2.0
            /// @see glPointParameter
            POINT_FADE_THRESHOLD_SIZE,

            /// one value, the current primitive restart index. 
            /// The initial value is 0
            /// *Not* in OpenGL ES 2.0
            /// @see glPrimitiveRestartIndex
            PRIMITIVE_RESTART_INDEX,

            /// data an array of GL_NUM_PROGRAM_BINARY_FORMATS values, 
            /// indicating the program binary formats supported by the implementation.
            /// Supported in OpenGL ES 2.0 extensions (*_OES) #FIXME
            PROGRAM_BINARY_FORMATS,

            /// data a single value, the name of the currently bound program 
            /// pipeline object, or zero if no program pipeline object is bound.
            /// Supported in OpenGL ES 2.0 extension (*_EXT) #FIXME
            /// @see glBindProgramPipeline
            PROGRAM_PIPELINE_BINDING,

            /// a single boolean value indicating whether vertex program point
            /// size mode is enabled. If enabled, then the point size is taken 
            /// from the shader built-in gl_PointSize. If disabled, then the
            /// point size is taken from the point state as specified by 
            /// glPointSize. The initial value is GL_FALSE.
            /// *Not* in OpenGL ES 2.0
            PROGRAM_POINT_SIZE,

            /// one value, the currently selected provoking vertex convention. 
            /// The initial value is GL_LAST_VERTEX_CONVENTION.
            /// *Not* in OpenGL ES 2.0
            /// @see glProvokingVertex
            PROVOKING_VERTEX,

            /// one value, the point size as specified by glPointSize.
            /// *Not* in OpenGL ES 2.0
            /// The initial value is 1.
            POINT_SIZE,

            /// one value, the size difference between adjacent supported sizes 
            /// for antialiased points.
            /// *Not* in OpenGL ES 2.0
            /// @see glPointSize
            POINT_SIZE_GRANULARITY,

            /// two values: the smallest and largest supported sizes for
            /// antialiased points. The smallest size must be at most 1, and the
            /// largest size must be at least 1. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPointSize
            POINT_SIZE_RANGE,

            /// one value, the scaling factor used to determine the variable
            /// offset that is added to the depth value of each fragment
            /// generated when a polygon is rasterized. The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glPolygonOffset
            POLYGON_OFFSET_FACTOR,

            /// one value. This value is multiplied by an implementation-specific
            /// value and then added to the depth value of each fragment
            /// generated when a polygon is rasterized. The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glPolygonOffset
            POLYGON_OFFSET_UNITS,

            /// a single boolean value indicating whether polygon offset is
            /// enabled for polygons in fill mode. The initial value is GL_FALSE
            /// Supported by OpenGL ES 2.0+
            /// @see glPolygonOffset
            POLYGON_OFFSET_FILL,

            /// a single boolean value indicating whether polygon offset is 
            /// enabled for polygons in line mode. The initial value is GL_FALSE
            /// *Not* in OpenGL ES 2.0
            /// @see glPolygonOffset
            POLYGON_OFFSET_LINE,

            /// a single boolean value indicating whether polygon offset is 
            /// enabled for polygons in point mode. The initial value is GL_FALSE
            /// *Not* in OpenGL ES 2.0
            /// @see glPolygonOffset
            POLYGON_OFFSET_POINT,

            /// a single boolean value indicating whether antialiasing of
            /// polygons is enabled. The initial value is GL_FALSE. 
            /// *Not* in OpenGL ES 2.0
            /// @see glPolygonMode
            POLYGON_SMOOTH,

            /// one value, a symbolic constant indicating the mode of the
            /// polygon antialiasing hint. The initial value is GL_DONT_CARE. 
            /// *Not* in OpenGL ES 2.0
            /// @see glHint
            POLYGON_SMOOTH_HINT,

            /// number of red bitplanes in the color buffer of the currently 
            /// bound framebuffer
            /// Supported by OpenGL ES 2.0+
            RED_BITS,
            /// number of green bitplanes in the color buffer of the currently 
            /// bound framebuffer
            /// Supported by OpenGL ES 2.0+
            GREEN_BITS,
            /// number of blue bitplanes in the color buffer of the currently 
            /// bound framebuffer
            /// Supported by OpenGL ES 2.0+
            BLUE_BITS,
            /// number of bitplanes in the depth buffer of the currently bound
            /// framebuffer
            /// Supported by OpenGL ES 2.0+
            DEPTH_BITS,

            /// one value, a symbolic constant indicating which color buffer is
            /// selected for reading. The initial value is GL_BACK if there is 
            /// a back buffer, otherwise it is GL_FRONT.
            /// *Not* in OpenGL ES 2.0
            /// @see glReadPixels
            READ_BUFFER,

            /// a single value, the name of the renderbuffer object currently
            /// bound to the target GL_RENDERBUFFER. If no renderbuffer object 
            /// is bound to this target, 0 is returned. The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glBindRenderbuffer
            RENDERBUFFER_BINDING,

            /// single boolean value indicating if the fragment coverage value 
            /// should be ANDed with a temporary coverage value based  on the 
            /// fragment's alpha value. The initial value is GL_FALSE.
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLE_ALPHA_TO_COVERAGE,

            /// a single integer value indicating the number of sample buffers 
            /// associated with the framebuffer. 
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLE_BUFFERS,

            /// single boolean value indicating if the fragment coverage value 
            /// should be ANDed with a temporary coverage value based on the 
            /// current sample coverage value. The initial value is GL_FALSE.
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLE_COVERAGE,

            /// a single positive floating-point value indicating the current
            /// sample coverage value. 
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLE_COVERAGE_VALUE,

            /// a single boolean value indicating if the temporary coverage value 
            /// should be inverted.
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLE_COVERAGE_INVERT,

            /// a single value, the name of the sampler object currently bound
            /// to the active texture unit. The initial value is 0.
            /// @see glBindSampler
            SAMPLER_BINDING,

            /// a single integer value indicating the coverage mask size.
            /// Supported by OpenGL ES 2.0+
            /// @see glSampleCoverage
            SAMPLES,

            /// four values: the x and y window coordinates of the scissor box,
            /// followed by its width and height. Initially the x and y window 
            /// coordinates are both 0 and the width and height are set to the 
            /// size of the window.
            /// Supported by OpenGL ES 2.0+
            /// @see glScissor
            SCISSOR_BOX,

            /// a single boolean value indicating whether scissoring is enabled.
            /// The initial value is GL_FALSE. 
            /// Supported by OpenGL ES 2.0+
            /// @see glScissor
            SCISSOR_TEST,



            /// a single boolean value indicating whether an online shader compiler 
            /// is present in the implementation. 
            /// All desktop OpenGL implementations must support online shader 
            /// compilations, and therefore the value of GL_SHADER_COMPILER 
            /// will always be GL_TRUE.
            /// Supported by OpenGL ES 2.0+
            SHADER_COMPILER,

            // When used with non-indexed variants of glGet (such as glGetIntegerv)
            /// a single value, the name of the buffer object currently bound to 
            /// the target GL_SHADER_STORAGE_BUFFER. 
            /// If no buffer object is bound to this target, 0 is returned. 
            /// When used with indexed variants of glGet (such as glGetIntegeri_v)
            /// a single value, the name of the buffer object bound to the indexed
            /// shader storage buffer binding points. The initial value is 0 for
            /// all targets. 
            /// @see glBindBuffer
            /// @see glBindBufferBase
            /// @see glBindBufferRange
            SHADER_STORAGE_BUFFER_BINDING,

            /// a single value, the minimum required alignment for shader storage
            /// buffer sizes and offset. The initial value is 1.
            /// @see glShaderStorateBlockBinding
            SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT,

            // When used with indexed variants of glGet (such as glGetInteger64i_v)
            /// a single value, the start offset of the binding range for each 
            /// indexed shader storage buffer binding. The initial value is 0 for
            /// all bindings. 
            /// @see glBindBufferRange
            SHADER_STORAGE_BUFFER_START,

            // When used with indexed variants of glGet (such as glGetInteger64i_v)
            /// a single value, the size of the binding range for each indexed 
            /// shader storage buffer binding. The initial value is 0 for all
            /// bindings.
            /// @see glBindBufferRange
            SHADER_STORAGE_BUFFER_SIZE,

            /// a pair of values indicating the range of widths supported for 
            /// smooth (antialiased) lines. 
            /// *Not* in OpenGL ES 2.0
            /// @see glLineWidth
            SMOOTH_LINE_WIDTH_RANGE,

            /// a single value indicating the level of quantization applied to 
            /// smooth line width parameters.
            /// *Not* in OpenGL ES 2.0
            SMOOTH_LINE_WIDTH_GRANULARITY,

            /// one value, a symbolic constant indicating what action is taken
            /// for back-facing polygons when the stencil test fails. 
            /// The initial value is GL_KEEP.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilOpSeparate
            STENCIL_BACK_FAIL,

            /// one value, a symbolic constant indicating what function is used
            /// for back-facing polygons to compare the stencil reference value
            /// with the stencil buffer value. The initial value is GL_ALWAYS.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_BACK_FUNC,

            /// one value, a symbolic constant indicating what action is taken
            /// for back-facing polygons when the stencil test passes, but the 
            /// depth test fails. The initial value is GL_KEEP.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilOpSeparate
            STENCIL_BACK_PASS_DEPTH_FAIL,

            /// one value, a symbolic constant indicating what action is taken 
            /// for back-facing polygons when the stencil test passes and the 
            /// depth test passes. The initial value is GL_KEEP.
            /// Supported by OpenGL ES 2.0+            
            /// @see glStencilOpSeparate
            STENCIL_BACK_PASS_DEPTH_PASS,

            /// one value, the reference value that is compared with the contents 
            /// of the stencil buffer for back-facing polygons. 
            /// The initial value is 0. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_BACK_REF,

            /// one value, the mask that is used for back-facing polygons to mask
            /// both the stencil reference value and the stencil buffer value
            /// before they are compared. The initial value is all 1's. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_BACK_VALUE_MASK,

            /// one value, the mask that controls writing of the stencil bitplanes
            /// for back-facing polygons. The initial value is all 1's.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilMaskSeparate
            STENCIL_BACK_WRITEMASK,

            /// number of bitplanes in the stencil buffer of the currently bound
            /// framebuffer.
            /// Supported by OpenGL ES 2.0+ (only?)
            STENCIL_BITS,

            /// one value, the index to which the stencil bitplanes are cleared.
            /// The initial value is 0.
            /// Supported by OpenGL ES 2.0+
            /// @see glClearStencil
            STENCIL_CLEAR_VALUE,

            /// one value, a symbolic constant indicating what action is taken 
            /// when the stencil test fails. The initial value is GL_KEEP.
            /// @see glStencilOp
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilOpSeparate
            STENCIL_FAIL,

            /// one value, a symbolic constant indicating what function is used
            /// to compare the stencil reference value with the stencil buffer 
            /// value. The initial value is GL_ALWAYS. 
            /// @see glStencilFunc
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_FUNC,

            /// one value, a symbolic constant indicating what action is taken 
            /// when the stencil test passes, but the depth test fails. 
            /// The initial value is GL_KEEP. 
            /// @see glStencilOp
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilOpSeparate
            STENCIL_PASS_DEPTH_FAIL,

            /// one value, a symbolic constant indicating what action is taken 
            /// when the stencil test passes and the depth test passes. 
            /// The initial value is GL_KEEP. 
            /// @see glStencilOp
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilOpSeparate
            STENCIL_PASS_DEPTH_PASS,

            /// one value, the reference value that is compared with the contents
            /// of the stencil buffer. The initial value is 0. 
            /// @see glStencilFunc
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_REF,

            /// a single boolean value indicating whether stencil testing of 
            /// fragments is enabled. The initial value is GL_FALSE.
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFunc
            /// @see glStencilOp
            STENCIL_TEST,

            /// one value, the mask that is used to mask both the stencil 
            /// reference value and the stencil buffer value before they are 
            /// compared. The initial value is all 1's. 
            /// @see glStencilFunc
            /// This stencil state only affects non-polygons and front-facing
            /// polygons. Back-facing polygons use separate stencil state. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilFuncSeparate
            STENCIL_VALUE_MASK,

            /// one value, the mask that controls writing of the stencil 
            /// bitplanes. The initial value is all 1's. 
            /// @see glStencilMask
            /// This stencil state only affects non-polygons and front-facing 
            /// polygons. Back-facing polygons use separate stencil state. 
            /// Supported by OpenGL ES 2.0+
            /// @see glStencilMaskSeparate
            STENCIL_WRITEMASK,

            /// a single boolean value indicating whether stereo buffers 
            /// (left and right) are supported.
            STEREO,

            /// one value, an estimate of the number of bits of subpixel 
            /// resolution that are used to position rasterized geometry in 
            /// window coordinates. The value must be at least 4.
            SUBPIXEL_BITS,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_1D. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_1D,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_1D_ARRAY. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_1D_ARRAY,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_2D. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_2D,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_2D_ARRAY. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_2D_ARRAY,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_2D_MULTISAMPLE. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_2D_MULTISAMPLE,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_2D_MULTISAMPLE_ARRAY. The initial value is 0.
            /// @see glBindTexture
            TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_3D. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_3D,

            /// a single value, the name of the texture currently bound to the
            /// target GL_TEXTURE_BUFFER. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_BUFFER,

            /// a single value, the name of the texture currently bound to the 
            /// target GL_TEXTURE_CUBE_MAP. The initial value is 0. 
            /// @see glBindTexture
            TEXTURE_BINDING_CUBE_MAP,

            /// a single value, the name of the texture currently bound to the 
            /// target GL_TEXTURE_RECTANGLE. The initial value is 0. 
            /// @see glBindTexture.
            TEXTURE_BINDING_RECTANGLE,

            /// a single value indicating the mode of the texture compression hint.
            /// The initial value is GL_DONT_CARE.
            TEXTURE_COMPRESSION_HINT,

            /// a single value, the name of the buffer object currently bound to
            /// the GL_TEXTURE_BUFFER buffer binding point. 
            /// The initial value is 0.
            /// @see glBindBuffer
            //TEXTURE_BINDING_BUFFER,

            /// a single value, the minimum required alignment for texture buffer
            /// sizes and offset. The initial value is 1. 
            /// @see glUniformBlockBinding
            TEXTURE_BUFFER_OFFSET_ALIGNMENT,

            /// a single value, the 64-bit value of the current GL time. 
            /// @see glQueryCounter
            TIMESTAMP,

            /// When used with non-indexed variants of glGet (such as glGetIntegerv)
            /// a single value, the name of the buffer object currently bound to 
            /// the target GL_TRANSFORM_FEEDBACK_BUFFER. If no buffer object is 
            /// bound to this target, 0 is returned. When used with indexed 
            /// variants of glGet (such as glGetIntegeri_v) 
            /// a single value, the name of the buffer object bound to the indexed
            /// transform feedback attribute stream. The initial value is 0 for 
            /// all targets. 
            /// @see glBindBuffer
            /// @see glBindBufferBase
            /// @see glBindBufferRange
            TRANSFORM_FEEDBACK_BUFFER_BINDING,

            /// When used with indexed variants of glGet (such as glGetInteger64i_v)
            /// a single value, the start offset of the binding range for each 
            /// transform feedback attribute stream. The initial value is 0 for 
            /// all streams
            /// @see glBindBufferRange
            TRANSFORM_FEEDBACK_BUFFER_START,

            /// When used with indexed variants of glGet (such as glGetInteger64i_v)
            /// a single value, the size of the binding range for each transform 
            /// feedback attribute stream. The initial value is 0 for all streams.
            /// @see glBindBufferRange
            TRANSFORM_FEEDBACK_BUFFER_SIZE,

            /// When used with non-indexed variants of glGet (such as glGetIntegerv)
            /// a single value, the name of the buffer object currently bound to
            /// the target GL_UNIFORM_BUFFER. If no buffer object is bound to this
            /// target, 0 is returned. 
            /// When used with indexed variants of glGet (such as glGetIntegeri_v)
            /// a single value, the name of the buffer object bound to the indexed
            /// uniform buffer binding point. The initial value is 0 for all targets.
            /// @see glBindBuffer
            /// @see glBindBufferBase
            /// @see glBindBufferRange
            UNIFORM_BUFFER_BINDING,

            /// a single value, the minimum required alignment for uniform buffer
            /// sizes and offset. The initial value is 1.
            /// @see glUniformBlockBinding
            UNIFORM_BUFFER_OFFSET_ALIGNMENT,

            /// When used with indexed variants of glGet (such as glGetInteger64i_v),
            /// a single value, the size of the binding range for each indexed 
            /// uniform buffer binding. The initial value is 0 for all bindings. 
            /// @see glBindBufferRange
            UNIFORM_BUFFER_SIZE,

            /// When used with indexed variants of glGet (such as glGetInteger64i_v)
            /// a single value, the start offset of the binding range for each 
            /// indexed uniform buffer binding. The initial value is 0 for all
            /// bindings. 
            /// @see glBindBufferRange
            UNIFORM_BUFFER_START,

            /// one value, the byte alignment used for reading pixel data from memory.
            /// The initial value is 4. 
            /// Supported by OpenGL ES 2.0+
            /// @see glPixelStore
            UNPACK_ALIGNMENT,

            /// one value, the image height used for reading pixel data from memory.
            /// The initial is 0. 
            /// @see glPixelStore
            UNPACK_IMAGE_HEIGHT,

            /// a single boolean value indicating whether single-bit pixels being 
            /// read from memory are read first from the least significant bit of
            /// each unsigned byte. The initial value is GL_FALSE.
            /// @see glPixelStore
            UNPACK_LSB_FIRST,

            /// one value, the row length used for reading pixel data from memory.
            /// The initial value is 0. 
            /// @see glPixelStore
            UNPACK_ROW_LENGTH,

            /// one value, the number of pixel images skipped before the first 
            /// pixel is read from memory. The initial value is 0. 
            /// @see glPixelStore
            UNPACK_SKIP_IMAGES,

            /// one value, the number of pixel locations skipped before the first
            /// pixel is read from memory. The initial value is 0. 
            /// @see glPixelStore
            UNPACK_SKIP_PIXELS,

            /// one value, the number of rows of pixel locations skipped before 
            /// the first pixel is read from memory. The initial value is 0. 
            /// @see glPixelStore
            UNPACK_SKIP_ROWS,

            /// a single boolean value indicating whether the bytes of two-byte 
            /// and four-byte pixel indices and components are swapped after 
            /// being read from memory. The initial value is GL_FALSE. 
            /// @see glPixelStore
            UNPACK_SWAP_BYTES,

            /// a single value, the name of the vertex array object currently
            /// bound to the context. If no vertex array object is bound to the 
            /// context, 0 is returned. The initial value is 0. 
            /// @see glBindVertexArray
            VERTEX_ARRAY_BINDING,

            /// Accepted by the indexed forms. 
            /// a single integer value representing the instance step divisor of
            /// the first element in the bound buffer's data store for vertex 
            /// attribute bound to index.
            VERTEX_BINDING_DIVISOR,

            /// Accepted by the indexed forms.
            /// a single integer value representing the byte offset of the first
            /// element in the bound buffer's data store for vertex attribute
            /// bound to index.
            VERTEX_BINDING_OFFSET,

            /// Accepted by the indexed forms.
            /// a single integer value representing the byte offset between the 
            /// start of each element in the bound buffers data store for vertex
            /// attribute bound to index.
            VERTEX_BINDING_STRIDE,

            /// a single integer value containing the maximum offset that may be
            /// added to a vertex binding offset.
            MAX_VERTEX_ATTRIB_RELATIVE_OFFSET,

            /// a single integer value containing the maximum number of vertex 
            /// buffers that may be bound.
            MAX_VERTEX_ATTRIB_BINDINGS,

            /// When used with non-indexed variants of glGet (such as glGetIntegerv)
            /// four values: the x and y window coordinates of the viewport, 
            /// followed by its width and height. Initially the x and y window 
            /// coordinates are both set to 0, and the width and height are set 
            /// to the width and height of the window into which the GL will do
            /// its rendering. 
            /// @see glViewport
            /// 
            /// When used with indexed variants of glGet (such as glGetIntegeri_v)
            /// four values: the x and y window coordinates of the indexed viewport,
            /// followed by its width and height. Initially the x and y window 
            /// coordinates are both set to 0, and the width and height are set 
            /// to the width and height of the window into which the GL will do 
            /// its rendering. 
            /// @see glViewportIndexedf
            VIEWPORT,

            /// two values, the minimum and maximum viewport bounds range.
            /// The minimum range should be at least [-32768, 32767].
            VIEWPORT_BOUNDS_RANGE,

            /// one value, the implementation dependent specific vertex of a 
            /// primitive that is used to select the viewport index. 
            /// If the value returned is equivalent to GL_PROVOKING_VERTEX, 
            /// then the vertex selection follows the convention specified by 
            /// glProvokingVertex. If the value returned is equivalent to 
            /// GL_FIRST_VERTEX_CONVENTION, then the selection is always taken 
            /// from the first vertex in the primitive. If the value returned is
            /// equivalent to GL_LAST_VERTEX_CONVENTION, then the selection is 
            /// always taken from the last vertex in the primitive. 
            /// If the value returned is equivalent to GL_UNDEFINED_VERTEX, then
            /// the selection is not guaranteed to be taken from any specific 
            /// vertex in the primitive.
            VIEWPORT_INDEX_PROVOKING_VERTEX,

            /// a single value, the number of bits of sub-pixel precision which 
            /// the GL uses to interpret the floating point viewport bounds. 
            /// The minimum value is 0.
            VIEWPORT_SUBPIXEL_BITS,

            /// a single value, the maximum index that may be specified during
            /// the transfer of generic vertex attributes to the GL.
            MAX_ELEMENT_INDEX,

            /// Supported by OpenGL ES 2.0+
            GENERATE_MIPMAP_HINT,

            /// Number of GL parameters that can be set via glSet* functions
            /// This will be also the size of special parameter array (client side)
            NUM_GL_PARAMETERS
        };

        /**
         *
         */
        struct SContextParam {
            /// Parameter name (special enum value)
            fgGFXenum internal_pname;
            /// Generic type of the data storing information/values
            fgGFXenum type;
            /// Special parameter type, for determining special 
            /// functions to use when setting parameter value
            fgGFXuint paramType;
            /// Size of the data (eg. one float, two floats, etc...)
            int count;

            union {
                ///
                fgGFXboolean booleans[12];
                ///
                fgGFXboolean boolVal;
                ///
                fgGFXfloat floats[12];
                ///
                fgGFXfloat floatVal;
                ///
                fgGFXint ints[12];
                ///
                fgGFXint intVal;
            };

            // Special overload operator for GFX integer type
            operator fgGFXint() const {
                return intVal;
            }

            // Special overload operator for GFX float type
            operator fgGFXfloat() const {
                return floatVal;
            }

            // Special overload operator for GFX boolean type (it's unsigned char mostly)
            operator fgGFXboolean() const {
                return boolVal;
            }

            // Special overload operator for GFX unsigned int type
            operator fgGFXuint() const {
                return (fgGFXuint)intVal;
            }

    #if defined(FG_USING_GL_BINDING)
            // Special overload operator for GFX enum type (when using glbinding,
            // the GFXenum type is actually an enum class, so overloading needs to
            // be done explictly)
            operator fgGFXenum() const {
                return (fgGFXenum)intVal;
            }
    #endif
            // Special overload operator for the builtin bool type
            operator bool() const {
                return ( intVal ? true : false);
            }

            // Comparison operator for integer type
            inline bool operator ==(fgGFXint a) const {
                return (intVal == a);
            }
            // Not equal operator for integer type
            inline bool operator !=(fgGFXint a) const {
                return (intVal != a);
            }
            // Greater than operator for integer type
            inline bool operator >(fgGFXint a) const {
                return (intVal > a);
            }
            // Less than operator for integer type
            inline bool operator <(fgGFXint a) const {
                return (intVal < a);
            }
            //
            inline bool operator ==(fgGFXfloat a) const {
                return (floatVal == a);
            }
            //
            inline bool operator !=(fgGFXfloat a) const {
                return (floatVal != a);
            }
            //
            inline bool operator >(fgGFXfloat a) const {
                return (floatVal > a);
            }
            //
            inline bool operator <(fgGFXfloat a) const {
                return (floatVal < a);
            }
            //
            inline bool operator ==(fgGFXuint a) const {
                return ((fgGFXuint)intVal == a);
            }
            //
            inline bool operator !=(fgGFXuint a) const {
                return ((fgGFXuint)intVal != a);
            }
            //
            inline bool operator >(fgGFXuint a) const {
                return ((fgGFXuint)intVal > a);
            }
            //
            inline bool operator <(fgGFXuint a) const {
                return ((fgGFXuint)intVal < a);
            }
            /**
             * Determines the special parameter type based on parameter name enumerator
             */
            inline void load(void) {
                if(paramType == FG_GFX_PARAM_INVALID)
                    return;
                switch(type) {
                    case FG_GFX_BOOL:
                        glGetBooleanv(internal_pname, booleans);
                        GLCheckError("glGetBooleanv");
                        break;
                    case FG_GFX_FLOAT:
                        glGetFloatv(internal_pname, floats);
                        GLCheckError("glGetFloatv");
                        break;
                    case FG_GFX_INT:
                        glGetIntegerv(internal_pname, ints);
                        GLCheckError("glGetIntegerv");
                        break;
                    default:
                        break;
                };
            }

            /**
             * Determines the special parameter type based on parameter name enumerator
             */
            void determineParamType(void);

            /**
             *  Updates the values on the server side
             * @return 
             */
            fgBool update(void);
            /**
             * 
             * @param _pname
             */
            SContextParam(const fgGFXenum _pname = (fgGFXenum)0) :
            internal_pname(_pname),
            type(FG_GFX_BOOL),
            paramType(FG_GFX_PARAM_INVALID),
            count(1) {
                memset(ints, 0, 12);
                determineParamType();
            }
            /**
             * 
             * @param _pname
             * @param _fval
             */
            SContextParam(const fgGFXenum _pname, const fgGFXfloat _fval) :
            internal_pname(_pname),
            type(FG_GFX_FLOAT),
            count(1) {
                memset(ints, 0, 12);
                floats[0] = _fval;
                determineParamType();
                set(_fval);
            }
            /**
             *
             * @param _pname
             * @param _ival
             */
            SContextParam(const fgGFXenum _pname, const fgGFXint _ival) :
            internal_pname(_pname),
            type(FG_GFX_INT),
            count(1) {
                memset(ints, 0, 12);
                ints[0] = _ival;
                determineParamType();
                set(_ival);
            }
            /**
             *
             * @param _pname
             * @param _bval
             */
            SContextParam(const fgGFXenum _pname,
                          const fgGFXboolean _bval) :
            internal_pname(_pname),
            type(FG_GFX_BOOL),
            count(1) {
                memset(ints, 0, 12);
                booleans[0] = _bval;
                determineParamType();
                set(_bval);
            }
            /**
             *
             * @param _pname
             * @param _count
             * @param _fvals
             */
            SContextParam(const fgGFXenum _pname,
                          const int _count,
                          const fgGFXfloat *_fvals) :
            internal_pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_fvals, FG_TRUE);
            }
            /**
             * 
             * @param _pname
             * @param _count
             * @param _ivals
             */
            SContextParam(const fgGFXenum _pname,
                          const int _count,
                          const fgGFXint *_ivals) :
            internal_pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_ivals, FG_TRUE);
            }
            /**
             * 
             * @param _pname
             * @param _count
             * @param _bvals
             */
            SContextParam(const fgGFXenum _pname,
                          const int _count,
                          const fgGFXboolean *_bvals) :
            internal_pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_bvals, FG_TRUE);
            }
            /**
             * 
             * @param _fval
             * @param update
             */
            inline void set(const fgGFXfloat _fval,
                            const fgBool update = FG_TRUE) {
                type = FG_GFX_FLOAT;
                count = 1;
                if(fabsf(floats[0] - _fval) > FG_EPSILON) {
                    floats[0] = _fval;
                    if(update)
                        this->update();
                }
            }
            /**
             * 
             * @param _ival
             * @param update
             */
            inline void set(const fgGFXint _ival,
                            const fgBool update = FG_TRUE) {
                type = FG_GFX_INT;
                count = 1;
                if(ints[0] != _ival) {
                    ints[0] = _ival;
                    if(update)
                        this->update();
                }
            }
            /**
             * 
             * @param _i0
             * @param _i1
             * @param _i2
             * @param _i3
             * @param update
             */
            inline void set(const fgGFXint _i0,
                            const fgGFXint _i1,
                            const fgGFXint _i2,
                            const fgGFXint _i3,
                            const fgBool update = FG_TRUE) {
                type = FG_GFX_INT;
                count = 4;
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
            /**
             * 
             * @param _f0
             * @param _f1
             * @param _f2
             * @param _f3
             * @param update
             */
            inline void set(const fgGFXfloat _f0,
                            const fgGFXfloat _f1,
                            const fgGFXfloat _f2,
                            const fgGFXfloat _f3,
                            const fgBool update = FG_TRUE) {
                type = FG_GFX_INT;
                count = 4;
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
            /**
             * 
             * @param _bval
             * @param update
             */
            inline void set(const fgGFXboolean _bval,
                            const fgBool update = FG_TRUE) {
                type = FG_GFX_BOOL;
                if(booleans[0] != _bval) {
                    booleans[0] = _bval;
                    if(update)
                        this->update();
                }
            }
            /**
             * 
             * @param _fvals
             * @param update
             */
            inline void set(const fgGFXfloat *_fvals,
                            const fgBool update = FG_TRUE) {
                if(!_fvals)
                    return;
                type = FG_GFX_FLOAT;
                fgBool diff = FG_FALSE;
                for(int i = 0; i < count; i++) {
                    if(diff || fabs(floats[i] - _fvals[i]) > FG_EPSILON) {
                        floats[i] = _fvals[i];
                        diff = FG_TRUE;
                    }
                }
                if(update && diff)
                    this->update();
            }
            /**
             * 
             * @param _ivals
             * @param update
             */
            inline void set(const fgGFXint *_ivals,
                            const fgBool update = FG_TRUE) {
                if(!_ivals)
                    return;
                type = FG_GFX_INT;
                fgBool diff = FG_FALSE;
                for(int i = 0; i < count; i++) {
                    if(diff || ints[i] != _ivals[i]) {
                        ints[i] = _ivals[i];
                        diff = FG_TRUE;
                    }
                }
                if(update && diff)
                    this->update();
            }
            /**
             * 
             * @param _bvals
             * @param update
             */
            inline void set(const fgGFXboolean *_bvals,
                            const fgBool update = FG_TRUE) {
                if(!_bvals)
                    return;
                type = FG_GFX_BOOL;
                fgBool diff = FG_FALSE;
                for(int i = 0; i < count; i++) {
                    if(booleans[i] != _bvals[i]) {
                        booleans[i] = _bvals[i];
                        diff = FG_TRUE;
                    }
                }
                if(update && diff)
                    this->update();
            }
            /**
             * 
             * @param _type
             * @return 
             */
            inline void *get(fgGFXenum *_type = NULL) {
                if(_type)
                    *_type = type;

                if(type == FG_GFX_FLOAT)
                    return (void *)floats;
                else if(type == FG_GFX_INT)
                    return (void *)ints;
                return (void *)booleans;
            }
        };

        class CPlatform;

        namespace context {

            ///
            typedef CVector<SContextParam> ParameterVec;
            ///
            typedef ParameterVec::iterator ParameterVecItor;

            ///
            typedef std::map<fgGFXuint, STextureID*> TextureMap;
            ///
            typedef TextureMap::iterator TextureMapItor;

            ///
            typedef std::map<fgGFXuint, SBufferID*> BufferMap;
            ///
            typedef BufferMap::iterator BufferMapItor;



    #if defined(FG_USING_SDL2)
            // Default constructor for the SDL build
            fgBool initialize(SDL_Window *sdlWindow);
    #else
            // Default constructor
            fgBool initialize(void);
    #endif
            // Destructor for the GFX context object
            void destroy(void);

            // This function will set or unset given attrib bits
            // depending on the current mask value
            void updateAttribMask(const fgGFXuint index);

            /**
             * 
             * @return 
             */
            fgBool isInit(void);
            /**
             * Return version ID for shading language currently supported by the graphics context
             * @return 
             */
            ShadingLangVersion getSLVersion(void);
            /**
             * 
             * @return 
             */
            void *getGLContext(void);
            /**
             * 
             * @return 
             */
            Vector2i const& getScreenSize(void);
            /**
             * 
             * @param w
             * @param h
             */
            void setScreenSize(const int w, const int h);
            /**
             * 
             * @param screenSize
             */
            void setScreenSize(const Vector2i& screenSize);
            /**
             * 
             * @param screenSize
             */
            void setScreenSize(const Vector2f& screenSize);

            /**
             *  Initialize the context and internal parameter state
             */
            //void initialize(void);

            /**
             * Get parameter structure
             * @param pname
             * @return 
             */
            SContextParam& getParam(const ParamType pname);

            /**
             * Enable GFX capability
             * @param cap
             */
            void enable(const ParamType cap);
            /**
             * Disable GFX capability
             * @param cap
             */
            void disable(const ParamType cap);

            /**
             * 
             * @param cap
             * @param toggle
             */
            void setCapability(const ParamType cap, const fgBool toggle = FG_TRUE);

            /**
             * Is given capability/parameter enabled?
             * @param pname
             * @return 
             */
            fgGFXboolean isEnabled(const ParamType pname);
            /**
             * Is given capability/parameter disabled?
             * @param pname
             * @return 
             */
            fgGFXboolean isDisabled(const ParamType pname);

            /**
             *  Is given buffer ID valid?
             * @param buffer
             * @return 
             */
            fgGFXboolean isBuffer(const fgGFXuint buffer);
            /**
             * Is given buffer ID struct valid?
             * @param bufferID
             * @return 
             */
            fgGFXboolean isBuffer(const SBufferID& bufferID);
            /**
             * Is given pointer to buffer ID struct valid?
             * @param bufferID
             * @return 
             */
            fgGFXboolean isBuffer(const SBufferID* bufferID);

            /**
             * Delete/release all buffers registered within this context
             */
            void deleteAllBuffers(void);

            /**
             * Generate given number of buffers
             * @param count
             * @param buffers
             * @param usage
             * @return 
             */
            fgGFXboolean genBuffers(const int count,
                                    SBufferID*& buffers,
                                    const fgGFXenum usage = GL_STATIC_DRAW);

            /**
             * Set buffer data
             * @param bufferID
             * @param size
             * @param data
             * @param target
             * @param usage
             */
            void bufferData(gfx::SBufferID& bufferID,
                            const fgGFXsizei size,
                            const fgGFXvoid* data,
                            const fgGFXenum target = GL_ARRAY_BUFFER,
                            const fgGFXenum usage = (fgGFXenum)0);

            /**
             * Bind given buffer ID to target array
             * @param target
             * @param buffer
             */
            void bindBuffer(const fgGFXenum target, const fgGFXuint buffer);
            /**
             * Bind given buffer ID to target array
             * @param bufferID
             * @param target
             */
            void bindBuffer(SBufferID& bufferID, const fgGFXenum target = (fgGFXenum)0);
            /**
             * Return currently bound buffer
             * @param target
             * @return 
             */
            fgGFXuint boundBuffer(const fgGFXenum target = GL_ARRAY_BUFFER);

            /**
             * Delete/release given buffer
             * @param bufferID
             */
            void deleteBuffer(SBufferID& bufferID);
            /**
             * Delete/release given number of buffers. 
             * IDs are zeroed and are no longer valid
             * @param count
             * @param buffers
             */
            void deleteBuffers(const int count, SBufferID* buffers);

            /**
             * Currently bound texture ID
             * @return 
             */
            fgGFXuint boundTexture(void);
            /**
             * Currently active texture unit ID
             * @return 
             */
            fgGFXuint activeTexture(void);

            /**
             * Is given texture ID valid?
             * @param texture
             * @return 
             */
            fgGFXboolean isTexture(const fgGFXuint texture);
            /**
             * Is given texture ID valid?
             * @param textureID
             * @return 
             */
            fgGFXboolean isTexture(const STextureID& textureID);

            /**
             * Set active texture unit ID
             * @param texture
             */
            void activeTexture(const fgGFXenum texture);

            /**
             * Delete/release all registered textures
             */
            void deleteAllTextures(void);

            /**
             * Generate given number of texture objects
             * @param count
             * @param textures
             * @param target
             */
            void genTextures(const int count,
                             STextureID* textures,
                             const fgGFXenum target = GL_TEXTURE_2D);
            /**
             * Generate texture and store information in special structure
             * @param texture
             * @param target
             */
            void genTexture(STextureID* texture,
                            const fgGFXenum target = GL_TEXTURE_2D);

            /**
             * Delete the specified number of textures based on info in special array
             * @param count
             * @param textures
             */
            void deleteTextures(const int count, STextureID* textures);
            /**
             * Delete the given texture based on the special information struct
             * @param textureID
             */
            void deleteTexture(STextureID& textureID);

            /**
             * Bind texture to 2D
             * @param texID
             */
            void bindTexture2D(const fgGFXuint texID);
            /**
             * Bind texture to Cube
             * @param texID
             */
            void bindTextureCube(const fgGFXuint texID);
            /**
             * Bind texture to given target
             * @param textureID
             * @param target
             */
            void bindTexture(STextureID& textureID,
                             const fgGFXenum target = (fgGFXenum)0);

            /**
             * Specify the blend equation mode
             * @param mode
             */
            void blendEquation(const fgGFXenum mode);
            /**
             * Specify the blend equation mode separately for RGB and alpha channels
             * @param modeRGB
             * @param modeAlpha
             */
            void blendEquation(const fgGFXenum modeRGB,
                               const fgGFXenum modeAlpha);
            /**
             * Specify the blend functions for source and destination
             * @param sfactor
             * @param dfactor
             */
            void blendFunc(const fgGFXenum sfactor,
                           const fgGFXenum dfactor);
            /**
             * Specify the blend functions for source and destination separately 
             * for RGB and alpha channels
             * @param srcRGB
             * @param dstRGB
             * @param srcAlpha
             * @param dstAlpha
             */
            void blendFunc(const fgGFXenum srcRGB,
                           const fgGFXenum dstRGB,
                           const fgGFXenum srcAlpha,
                           const fgGFXenum dstAlpha);

            /**
             * Use specified shader program
             * @param program
             */
            void useProgram(const fgGFXuint program);
            /**
             * Returns the index to currently active vertex program
             * @return 
             */
            fgGFXuint activeProgram(void);

            /**
             * Set viewport box to default dimensions
             */
            void viewport(void);
            /**
             * Set the viewport dimensions
             * @param x
             * @param y
             * @param width
             * @param height
             */
            void viewport(const fgGFXint x,
                          const fgGFXint y,
                          const fgGFXint width,
                          const fgGFXint height);
            /**
             * Set the viewport dimensions
             * @param pos
             * @param size
             */
            void viewport(const Vector2i& pos,
                          const Vector2i& size);
            /**
             * Set the viewport dimensions
             * @param dimensions
             */
            void viewport(const Vector4i& dimensions);
            /**
             * 
             * @return 
             */
            Vector4i getViewport(void);
            /**
             * Returns the viewport aspect ratio
             * @return 
             */
            fgGFXfloat getViewportAspect(void);
            /**
             * Set the scissor box to default dimensions
             */
            void scissor(void);
            /**
             * Set the scissor box dimensions
             * @param x
             * @param y
             * @param width
             * @param height
             */
            void scissor(const fgGFXint x,
                         const fgGFXint y,
                         const fgGFXint width,
                         const fgGFXint height);
            /**
             * Set the scissor box dimensions
             * @param pos
             * @param size
             */
            void scissor(const Vector2i& pos,
                         const Vector2i& size);
            /**
             * Set the scissor box dimensions
             * @param dimensions
             */
            void scissor(const Vector4i& dimensions);
            /**
             * Returns the scissor box aspect ratio
             * @return 
             */
            fgGFXfloat getScissorAspect(void);

            /**
             * Toggle scissor test capability
             * @param toggle
             */
            void setScissorTest(const fgBool toggle = FG_TRUE);
            /**
             * Toggle depth testing
             * @param toggle
             */
            void setDepthTest(const fgBool toggle = FG_TRUE);
            /**
             * Toggle cull face elimination
             * @param toggle
             */
            void setCullFace(const fgBool toggle = FG_TRUE);
            /**
             * Toggle blending
             * @param toggle
             */
            void setBlend(const fgBool toggle = FG_TRUE);
            /**
             * Set the front face
             * @param mode
             */
            void frontFace(const fgGFXenum mode = GL_CCW);
            /**
             * Set the cull face
             * @param mode
             */
            void cullFace(const fgGFXenum mode = GL_BACK);
            /**
             * Set the depth function
             * @param func
             */
            void depthFunc(const fgGFXenum func);
            /**
             * Set the clear depth value
             * @param depth
             */
            void clearDepth(const fgGFXfloat depth = 1.0f);
            /**
             * Set the clear color
             * @param red
             * @param green
             * @param blue
             * @param alpha
             */
            void clearColor(const fgGFXfloat red,
                            const fgGFXfloat green,
                            const fgGFXfloat blue,
                            const fgGFXfloat alpha);
            /**
             * Set the clear stencil value
             * @param s
             */
            void clearStencil(const fgGFXint s);
            /**
             * Set the pixel unpacking alignment
             * @param param
             */
            void pixelStoreUnPack(const fgGFXint param = 4);
            /**
             * Set the pixel packing alignment
             * @param param
             */
            void pixelStorePack(const fgGFXint param = 4);

            /**
             * Returns the currently active vertex attribute mask
             * @return 
             */
            fgGFXuint activeVertexAttribArrayMask(void);
            /**
             * Returns whether given index vertex attrib array is activated
             * @param index
             * @return 
             */
            fgBool isVertexAttribArrayActive(const fgGFXuint index);

            /**
             * Enable the given vertex attrib array index and also by default update the current attrib mask
             * @see https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
             * @param index
             * @param updateMask
             */
            void enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
            /**
             * Disable the given vertex attrib array index and also by default update the current attrib mask
             * @param index
             * @param updateMask
             */
            void disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
            /**
             * Enable the vertex attrib arrays based on the given attrib mask
             * Attributes not in the mask will not be deactivated
             * @param mask
             */
            void enableVertexAttribArrayMask(const fgGFXuint mask);
            /**
             * Disable the vertex attrib arrays based on the given attrib mask
             * @param mask
             */
            void disableVertexAttribArrayMask(const fgGFXuint mask);
            /**
             * Disable or enable given vertex attrib arrays based on the given mask
             * Attributes not in the mask will be deactivated
             * @param mask
             */
            void diffVertexAttribArrayMask(const fgGFXuint mask);

            /**
             * Returns the buffer (VBO) index currently bound to given vertex attrib index
             * @see https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetVertexAttrib.xml
             * @param index
             * @return 
             */
            fgGFXuint getVertexAttribBufferBinding(const fgGFXuint index);
            /**
             * 
             * @param index
             * @return 
             */
            fgGFXuint getVertexAttribSize(const fgGFXuint index);
            /**
             * Returns the vertex attrib data stride for the given index
             * @param index
             * @return 
             */
            fgGFXuint getVertexAttribStride(const fgGFXuint index);
            /**
             * Returns the vertex attrib data type
             * @param index
             * @return 
             */
            fgGFXenum getVertexAttribType(const fgGFXuint index);
            /**
             * Returns whether the given attrib array is normalized
             * @param index
             * @return 
             */
            fgGFXboolean getVertexAttribNormalized(const fgGFXuint index);

            /**
             * Sets the various data details for given vertex attribute index
             * @see https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
             * @param index
             * @param size
             * @param type
             * @param normalized
             * @param stride
             * @param ptr
             */
            void vertexAttribPointer(fgGFXuint index,
                                     fgGFXint size,
                                     fgGFXenum type,
                                     fgGFXboolean normalized,
                                     fgGFXsizei stride,
                                     fgGFXvoid* ptr);

            /**
             * Sets the various data details based on a special attribute data struct
             * @param attrData
             */
            void vertexAttribPointer(SAttributeData& attrData);

        };
    };
};

    #undef FG_INC_GFX_CONTEXT_BLOCK
#endif /* FG_INC_GFX_CONTEXT */
