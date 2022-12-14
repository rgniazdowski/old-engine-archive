/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
#ifndef FG_INC_GFX_GL
    #define FG_INC_GFX_GL
    #define FG_INC_GFX_GL_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include "fgLog.h"

    #ifndef FG_GFX_GL_INCLUDES_FINISHED
        #define FG_GFX_GL_INCLUDES_FINISHED

       #if defined(FG_USING_PLATFORM_LINUX) && !defined(FG_USING_PLATFORM_ANDROID)
//	GFX includes for OpenGL/SDL - platform LINUX

            #if defined(FG_USING_OPENGL)

                #if !defined(FG_USING_SDL2)
                    #if !defined(FG_USING_OPENGL_GLEW)
                        #define GL_GLEXT_PROTOTYPES
                        #include <GL/gl.h>
                        #include <GL/glext.h>
                    #elif defined(FG_USING_OPENGL_GLEW)
                        #include <GL/glew.h>                    
                    #endif /* FG_USING_OPENGL_GLEW */
                    #define FG_INC_INCLUDED_GL_
                #else /* FG_USING_SDL2 */
// if defined SDL2 - then use specific GL code for SDL2
                    #include <SDL2/SDL.h>
                    #if !defined(FG_USING_OPENGL_GLEW)
                        #include <SDL2/SDL_opengl.h>
                    #elif defined(FG_USING_OPENGL_GLEW)
                        #include <GL/glew.h>                    
                    #endif
                    #define FG_INC_INCLUDED_GL_
                #endif /* FG_USING_SDL2 */

            #else /* FG_USING_OPENGL */

                #if defined FG_USING_SDL2
                    #include <SDL2/SDL.h>
                #endif

            #endif /* FG_USING_OPENGL */

        #endif /* FG_USING_PLATFORM_LINUX && !ANDROID */

        #if defined(FG_USING_OPENGL_ES)

            #if defined(FG_USING_SDL2)
                #include <SDL2/SDL.h>
                #include <SDL2/SDL_opengles2.h>
                #define FG_INC_INCLUDED_GL_
            #else /* if SDL2 is not defined - native GLES2 support ? */
                #include <GLES2/gl2.h>
                #include <GLES2/gl2ext.h>
                #include <GLES2/gl2platform.h>
                #define FG_INC_INCLUDED_GL_
            #endif /* defined FG_USING_SDL2 */

            #if defined FG_USING_EGL
                #include <EGL/egl.h>
                #define FG_EGL_MAX_CONFIG 32
            #endif /* FG_USING_EGL */

        #endif /* FG_USING_OPENGL_ES */

    #endif /* FG_GFX_GL_INCLUDES_FINISHED */


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

namespace fg {
    namespace gfx {

        enum ShadingLangVersion {
            FG_GFX_SHADING_LANGUAGE_INVALID = 0,
            FG_GFX_ESSL_100 = 100,
            FG_GFX_ESSL_300 = 300,
            FG_GFX_GLSL_110 = 110,
            FG_GFX_GLSL_120 = 120,
            FG_GFX_GLSL_130 = 130,
            FG_GFX_GLSL_140 = 140,
            FG_GFX_GLSL_150 = 150,
            FG_GFX_GLSL_330 = 330,
            FG_GFX_GLSL_400 = 400,
            FG_GFX_GLSL_410 = 410,
            FG_GFX_GLSL_420 = 420,
            FG_GFX_GLSL_430 = 430,
            FG_GFX_GLSL_440 = 440,
            FG_GFX_GLSL_450 = 450
        };
    }
}

    #if defined FG_USING_OPENGL_ES
        #define FG_GFX_SHADING_LANG_VERSION_DEFAULT FG_GFX_ESSL_100
    #else
        #define FG_GFX_SHADING_LANG_VERSION_DEFAULT FG_GFX_GLSL_330 // ?
    #endif
namespace fg {
    namespace gfx {
        /**
         *
         * @param afterFunc
         * @param params
         * @return
         */
        inline unsigned int GLCheckError(const char *afterFunc = NULL, const char *params = NULL) {
            static unsigned int repeatCnt = 0;
            static GLenum lastCode = GL_NO_ERROR;
            GLenum retCode = GL_NO_ERROR;
            GLenum code = GL_NO_ERROR;

            const char * const invalidEnum = "An unacceptable value is specified for an enumerated argument.";
            const char * const invalidValue = "A numeric argument is out of range.";
            const char * const invalidOperation = "The specified operation is not allowed in the current state.";
            const char * const outOfMemory = "There is not enough memory left to execute the command. The state of the GL is undefined";
            const char * const invalidFBOp = "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE).";

            if(afterFunc == NULL)
                afterFunc = "gl*";
            if(params == NULL)
                params = "\0";

            while(FG_TRUE) {
                code = glGetError();
                retCode = code;

                if(code == GL_NO_ERROR)
                    break;
                if(repeatCnt >= 2 && lastCode == code) {
                    break;
                } else if(lastCode != code) {
                    repeatCnt = 0;
                }
                switch(code) {
                    case GL_INVALID_ENUM:
                        FG_LOG_ERROR("GFX: GL_INVALID_ENUM after %s(%s): '%s'", afterFunc, params, invalidEnum);
                        break;
                    case GL_INVALID_VALUE:
                        FG_LOG_ERROR("GFX: GL_INVALID_VALUE after %s(%s): '%s'", afterFunc, params, invalidValue);
                        break;
                    case GL_INVALID_OPERATION:
                        FG_LOG_ERROR("GFX: GL_INVALID_OPERATION after %s(%s): '%s'", afterFunc, params, invalidOperation);
                        break;
                    case GL_OUT_OF_MEMORY:
                        FG_LOG_ERROR("GFX: GL_OUT_OF_MEMORY after %s(%s): '%s'", afterFunc, params, outOfMemory);
                        break;
                    case GL_INVALID_FRAMEBUFFER_OPERATION:
                        FG_LOG_ERROR("GFX: GL_INVALID_FRAMEBUFFER_OPERATION after %s(%s): '%s'", afterFunc, params, invalidFBOp);
                        break;
                    default:
                        retCode = 0;
                        break;
                }
                if(lastCode == code)
                    repeatCnt++;
                lastCode = code;
            }
            return (unsigned int)retCode;
        }
    } // namespace gfx
} // namespace fg

    #if defined(FG_USING_EGL)
// #FIXME | this can be also used for EGL / SDL ? make it universal?
inline unsigned int fgEGLError(const char *afterFunc = NULL) {
    std::map<unsigned int, const char *> errMap;
    // !FIXME
    errMap[EGL_SUCCESS] = "The last function succeeded without error.";
    errMap[EGL_NOT_INITIALIZED] = "EGL is not initialized, or could not be initialized, for the specified EGL display connection.";
    errMap[EGL_BAD_ACCESS] = "EGL cannot access a requested resource (for example a context is bound in another thread).";
    errMap[EGL_BAD_ALLOC] = "EGL failed to allocate resources for the requested operation.";
    errMap[EGL_BAD_ATTRIBUTE] = "An unrecognized attribute or attribute value was passed in the attribute list.";
    errMap[EGL_BAD_CONTEXT] = "An EGLContext argument does not name a valid EGL rendering context.";
    errMap[EGL_BAD_CONFIG] = "An EGLConfig argument does not name a valid EGL frame buffer configuration.";
    errMap[EGL_BAD_CURRENT_SURFACE] = "The current surface of the calling thread is a window, pixel buffer or pixmap that is no longer valid.";
    errMap[EGL_BAD_DISPLAY] = "An EGLDisplay argument does not name a valid EGL display connection.";
    errMap[EGL_BAD_SURFACE] = "An EGLSurface argument does not name a valid surface (window, pixel buffer or pixmap) configured for GL rendering.";
    errMap[EGL_BAD_MATCH] = "Arguments are inconsistent (for example, a valid context requires buffers not supplied by a valid surface).";
    errMap[EGL_BAD_PARAMETER] = "One or more argument values are invalid.";
    errMap[EGL_BAD_NATIVE_PIXMAP] = "A NativePixmapType argument does not refer to a valid native pixmap.";
    errMap[EGL_BAD_NATIVE_WINDOW] = "A NativeWindowType argument does not refer to a valid native window.";
    errMap[EGL_CONTEXT_LOST] = "A power management event has occurred. The application must destroy all contexts and reinitialize OpenGL ES state and objects to continue rendering. ";

    unsigned int retCode = 0;
    if(afterFunc == NULL)
        afterFunc = "gl*";
    unsigned int code = 0;

    while(FG_TRUE) {
        code = eglGetError();
        retCode = code;
        if(code == EGL_SUCCESS)
            break;
        switch(code) {
            case EGL_NOT_INITIALIZED:
                FG_LOG_ERROR("GFX: EGL_NOT_INITIALIZED after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_ACCESS:
                FG_LOG_ERROR("GFX: EGL_BAD_ACCESS after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_ALLOC:
                FG_LOG_ERROR("GFX: EGL_BAD_ALLOC after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_ATTRIBUTE:
                FG_LOG_ERROR("GFX: EGL_BAD_ATTRIBUTE after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_CONTEXT:
                FG_LOG_ERROR("GFX: EGL_BAD_CONTEXT after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_CONFIG:
                FG_LOG_ERROR("GFX: EGL_BAD_CONFIG after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_CURRENT_SURFACE:
                FG_LOG_ERROR("GFX: EGL_BAD_CURRENT_SURFACE after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_DISPLAY:
                FG_LOG_ERROR("GFX: EGL_BAD_DISPLAY after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_SURFACE:
                FG_LOG_ERROR("GFX: EGL_BAD_SURFACE after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_MATCH:
                FG_LOG_ERROR("GFX: EGL_BAD_MATCH after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_PARAMETER:
                FG_LOG_ERROR("GFX: EGL_BAD_PARAMETER after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_NATIVE_PIXMAP:
                FG_LOG_ERROR("GFX: EGL_BAD_NATIVE_PIXMAP after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_BAD_NATIVE_WINDOW:
                FG_LOG_ERROR("GFX: EGL_BAD_NATIVE_WINDOW after %s(): %s", afterFunc, errMap[code]);
                break;
            case EGL_CONTEXT_LOST:
                FG_LOG_ERROR("GFX: EGL_CONTEXT_LOST after %s(): %s", afterFunc, errMap[code]);
                break;
            default:
                FG_LOG_ERROR("GFX: EGL error after %s(): %s", afterFunc, errMap[code]);
                retCode = 0;
                break;
        }
    }
    return retCode;
}
    #endif /* FG_USING_EGL */

    #ifndef FG_GFX_FALSE
        #define FG_GFX_FALSE	GL_FALSE
    #endif

    #ifndef FG_GFX_TRUE
        #define FG_GFX_TRUE	GL_TRUE
    #endif

    #if !defined(FG_GFX_GL_MASK_TYPEDEFS_DEFINED) && defined(FG_INC_INCLUDED_GL_)
        #define FG_GFX_GL_MASK_TYPEDEFS_DEFINED
typedef GLvoid fgGFXvoid;
typedef GLchar fgGFXchar;
typedef GLenum fgGFXenum;
typedef GLboolean fgGFXboolean;
typedef GLbitfield fgGFXbitfield;
typedef GLbyte fgGFXbyte;
typedef GLshort fgGFXshort;
typedef GLint fgGFXint;
typedef GLsizei fgGFXsizei;
typedef GLubyte fgGFXubyte;
typedef GLushort fgGFXushort;
typedef GLuint fgGFXuint;
typedef GLfloat fgGFXfloat;
typedef GLclampf fgGFXclampf;
        #ifndef FG_USING_SDL2
typedef GLfixed fgGFXfixed;
        #else
typedef int fgGFXfixed;
        #endif

    #endif /* FG_GFX_GL_MASK_TYPEDEFS_DEFINED && FG_INC_INCLUDED_GL_ */

//
// Data types
//

//	bool	-	a conditional type, taking on values of true or false
//	int	-	a signed integer
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

    #define FG_GFX_FLOAT                GL_FLOAT
    #define FG_GFX_FLOAT_VEC2           GL_FLOAT_VEC2
    #define FG_GFX_FLOAT_VEC3           GL_FLOAT_VEC3
    #define FG_GFX_FLOAT_VEC4           GL_FLOAT_VEC4
    #define FG_GFX_INT                  GL_INT
    #define FG_GFX_INT_VEC2             GL_INT_VEC2
    #define FG_GFX_INT_VEC3             GL_INT_VEC3
    #define FG_GFX_INT_VEC4             GL_INT_VEC4
    #define FG_GFX_BOOL                 GL_BOOL
    #define FG_GFX_BOOL_VEC2            GL_BOOL_VEC2
    #define FG_GFX_BOOL_VEC3            GL_BOOL_VEC3
    #define FG_GFX_BOOL_VEC4            GL_BOOL_VEC4
    #define FG_GFX_FLOAT_MAT2           GL_FLOAT_MAT2
    #define FG_GFX_FLOAT_MAT3           GL_FLOAT_MAT3
    #define FG_GFX_FLOAT_MAT4           GL_FLOAT_MAT4	
    #define FG_GFX_SAMPLER_2D           GL_SAMPLER_2D
    #define FG_GFX_SAMPLER_CUBE         GL_SAMPLER_CUBE

    #undef FG_INC_GFX_GL_BLOCK
#endif /* FG_INC_GFX_GL */
