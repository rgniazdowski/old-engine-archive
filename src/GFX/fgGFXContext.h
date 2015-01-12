/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_CONTEXT
    #define FG_INC_GFX_CONTEXT
    #define FG_INC_GFX_CONTEXT_BLOCK

    #ifndef FG_INC_GFX_GL
        #include "fgGFXGL.h"
    #endif

    #ifndef FG_INC_GFX_TYPES
        #include "fgGFXTypes.h"
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

        /*
         *
         */
        struct SContextParam {
            /// Parameter name (special enum value)
            fgGFXenum pname;
            /// Generic type of the data storing information/values
            fgGFXenum type;
            /// Special parameter type, for determining special 
            /// functions to use when setting parameter value
            fgGFXuint paramType;
            /// Size of the data (eg. one float, two floats, etc...)
            int count;

            union {
                fgGFXboolean boolVal;
                fgGFXboolean booleans[12];
                fgGFXfloat floats[12];
                fgGFXfloat floatVal;
                fgGFXint ints[12];
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

            // 
            inline void load(void) {
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
                    default:
                        break;
                };
            }

            // Determines the special parameter type based on parameter name enumerator
            void determineParamType(void);

            // Updates the values on the server side
            fgBool update(void);

            // 
            SContextParam(const fgGFXenum _pname = (fgGFXenum)0) :
            pname(_pname),
            type(FG_GFX_BOOL),
            paramType(FG_GFX_PARAM_INVALID),
            count(1) {
                memset(ints, 0, 12);
                determineParamType();
            }

            // 
            SContextParam(const fgGFXenum _pname, const fgGFXfloat _fval) :
            pname(_pname),
            type(FG_GFX_FLOAT),
            count(1) {
                memset(ints, 0, 12);
                floats[0] = _fval;
                determineParamType();
            }

            // 
            SContextParam(const fgGFXenum _pname, const fgGFXint _ival) :
            pname(_pname),
            type(FG_GFX_INT),
            count(1) {
                memset(ints, 0, 12);
                ints[0] = _ival;
                determineParamType();
            }

            // 
            SContextParam(const fgGFXenum _pname, const fgGFXboolean _bval) :
            pname(_pname),
            type(FG_GFX_BOOL),
            count(1) {
                memset(ints, 0, 12);
                booleans[0] = _bval;
                determineParamType();
                //update();
            }

            // 
            SContextParam(const fgGFXenum _pname, const int _count, const fgGFXfloat *_fvals) :
            pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_fvals, FG_FALSE);
            }

            // 
            SContextParam(const fgGFXenum _pname, const int _count, const fgGFXint *_ivals) :
            pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_ivals, FG_FALSE);
            }

            // 
            SContextParam(const fgGFXenum _pname, const int _count, const fgGFXboolean *_bvals) :
            pname(_pname),
            count(_count) {
                memset(ints, 0, 12);
                determineParamType();
                set(_bvals, FG_FALSE);
            }

            // 
            inline void set(const fgGFXfloat _fval, const fgBool update = FG_TRUE) {
                type = FG_GFX_FLOAT;
                count = 1;
                if(fabsf(floats[0] - _fval) > FG_EPSILON) {
                    floats[0] = _fval;
                    if(update)
                        this->update();
                }
            }

            // 
            inline void set(const fgGFXint _ival, const fgBool update = FG_TRUE) {
                type = FG_GFX_INT;
                count = 1;
                if(ints[0] != _ival) {
                    ints[0] = _ival;
                    if(update)
                        this->update();
                }
            }

            //
            inline void set(const fgGFXint _i0, const fgGFXint _i1, const fgGFXint _i2, const fgGFXint _i3, const fgBool update = FG_TRUE) {
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

            //
            inline void set(const fgGFXfloat _f0, const fgGFXfloat _f1, const fgGFXfloat _f2, const fgGFXfloat _f3, const fgBool update = FG_TRUE) {
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

            // 
            inline void set(const fgGFXboolean _bval, const fgBool update = FG_TRUE) {
                type = FG_GFX_BOOL;
                if(booleans[0] != _bval) {
                    booleans[0] = _bval;
                    if(update)
                        this->update();
                }
            }

            // 
            inline void set(const fgGFXfloat *_fvals, const fgBool update = FG_TRUE) {
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

            // 
            inline void set(const fgGFXint *_ivals, const fgBool update = FG_TRUE) {
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

            // 
            inline void set(const fgGFXboolean *_bvals, const fgBool update = FG_TRUE) {
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

            // 
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

        /*
         * Special class for holding information about current GFX context.
         * Works as a special kind of cache for client and server side.
         */
        class CContext {
            friend class fg::gfx::CPlatform;

        public:
            ///
            typedef std::map<fgGFXuint, SContextParam> ParameterMap;
            ///
            typedef ParameterMap::iterator ParameterMapItor;

            ///
            typedef std::map<fgGFXuint, fgGfxTextureID*> TextureMap;
            ///
            typedef TextureMap::iterator TextureMapItor;

            ///
            typedef std::map<fgGFXuint, fgGfxBufferID*> BufferMap;
            ///
            typedef BufferMap::iterator BufferMapItor;

        private:
    #if defined(FG_USING_SDL2)
            SDL_Window *m_sdlWindow;
            SDL_GLContext m_GLContext; // #FIXME - context can be separate? ... P4
    #elif defined(FG_USING_EGL)    
            void* m_GLContext; // it's for EGL only...
    #else
            void *m_GLContext; // ?
    #endif
            /// Special parameter map used for caching and fast value check
            /// It's used for not calling redundant GL functions, like:
            /// glGet/glEnable/glDisable/glIsEnabled and so on. Also for
            /// functions like activating proper vertex attrib array idx,
            /// bounding textures... any kind of function that changes internal
            /// state values.
            ParameterMap m_params;
            /// Special map used for holding valid texture IDs
            /// Every texture needs to be created/deleted through
            /// this class. When texture is deleted its' ID is zeroed
            /// in every place in the app. Therefore there's no need to
            /// often call glIsTexture. If gfx ID is not zero the texture
            /// is surely valid.
            TextureMap m_textures;
            /// Special map used for holding valid VBO IDs. Use case
            /// is the same as for textures.
            BufferMap m_buffers;
            /// Viewport area (used for fast check if viewport changed)
            fgGFXuint m_viewportAreaQ;
            /// Scissor area
            fgGFXuint m_scissorAreaQ;

            /// Currently used attribute mask
            fgGFXuint m_attribMask;
            ///
            fgGfxAttributeData m_attrInfo[FG_GFX_ATTRIBUTE_DATA_MAX]; // #FIXME - attribute count ... why here?  hello?
            /// Currently bound texture ID
            fgGFXuint m_boundTexture;
            /// Supported shading language version
            fgGfxSLVersion m_SLVersion;
            ///
            Vector2i m_screenSize;
            /// Is context ready? Is initialization successful?
            fgBool m_init;

        protected:
    #if defined(FG_USING_SDL2)
            // Default constructor for the SDL build
            CContext(SDL_Window *sdlWindow);
    #else
            // Default constructor
            CContext();
    #endif
            // Default destructor for the GFX context object
            virtual ~CContext();

            // This function will set or unset given attrib bits
            // depending on the current mask value
            void updateAttribMask(const fgGFXuint index);

        public:
            /**
             * 
             * @return 
             */
            fgBool isInit(void) const {
                return m_init;
            }
            /**
             * Return version ID for shading language currently supported by the graphics context
             * @return 
             */
            fgGfxSLVersion getSLVersion(void) const {
                return m_SLVersion;
            }
            /**
             * 
             * @return 
             */
            void *getGLContext(void) const {
                return m_GLContext;
            }
            /**
             * 
             * @return 
             */
            Vector2i const & getScreenSize(void) const {
                return m_screenSize;
            }
            /**
             * 
             * @param w
             * @param h
             */
            void setScreenSize(const int w, const int h) {
                m_screenSize.x = w;
                m_screenSize.y = h;
            }
            /**
             * 
             * @param screenSize
             */
            void setScreenSize(const Vector2i & screenSize) {
                m_screenSize = screenSize;
            }
            /**
             * 
             * @param screenSize
             */
            void setScreenSize(const Vector2f & screenSize) {
                m_screenSize.x = (int)screenSize.x;
                m_screenSize.y = (int)screenSize.y;
            }

            // Initialize the context and internal parameter state
            void initialize(void);
            // Get parameter structure
            SContextParam& getParam(const fgGFXenum pname);

            // Enable GFX capability
            void enable(const fgGFXenum cap);
            // Disable GFX capability
            void disable(const fgGFXenum cap);

            // Is given capability/parameter enabled?
            fgGFXboolean isEnabled(const fgGFXenum pname);
            // Is given capability/parameter disabled?
            fgGFXboolean isDisabled(const fgGFXenum pname);

            // Is given buffer ID valid?
            fgGFXboolean isBuffer(const fgGFXuint buffer);
            // Is given buffer ID struct valid?
            fgGFXboolean isBuffer(const fgGfxBufferID& bufferID);
            // Is given pointer to buffer ID struct valid?
            fgGFXboolean isBuffer(const fgGfxBufferID* bufferID);

            // Delete/release all buffers registered within this context
            void deleteAllBuffers(void);

            // Generate given number of buffers
            fgGFXboolean genBuffers(const int count, fgGfxBufferID*& buffers, const fgGFXenum usage = GL_STATIC_DRAW);

            // Set buffer data
            void bufferData(
                            fgGfxBufferID& bufferID,
                            const fgGFXsizei size,
                            const fgGFXvoid* data,
                            const fgGFXenum target = GL_ARRAY_BUFFER,
                            const fgGFXenum usage = (fgGFXenum)0);

            // Bind given buffer ID to target array
            void bindBuffer(const fgGFXenum target, const fgGFXuint buffer);
            // Bind given buffer ID to target array
            void bindBuffer(fgGfxBufferID& bufferID, const fgGFXenum target = (fgGFXenum)0);
            // Return currently bound buffer
            fgGFXuint boundBuffer(const fgGFXenum target = GL_ARRAY_BUFFER);

            // Delete/release given buffer
            void deleteBuffer(fgGfxBufferID& bufferID);
            // Delete/release given number of buffers. IDs are zeroed and are no longer valid
            void deleteBuffers(const int count, fgGfxBufferID* buffers);

            // Currently bound texture ID
            fgGFXuint boundTexture(void) const;
            // Currently active texture unit ID
            fgGFXuint activeTexture(void);

            // Is given texture ID valid?
            fgGFXboolean isTexture(const fgGFXuint texture);
            // Is given texture ID valid?
            fgGFXboolean isTexture(const fgGfxTextureID& textureID);

            // Set active texture unit ID
            void activeTexture(const fgGFXenum texture);

            // Delete/release all registered textures
            void deleteAllTextures(void);

            // Generate given number of texture objects
            void genTextures(const int count, fgGfxTextureID* textures, const fgGFXenum target = GL_TEXTURE_2D);
            // Generate texture and store information in special structure
            void genTexture(fgGfxTextureID* texture, const fgGFXenum target = GL_TEXTURE_2D);

            // Delete the specified number of textures based on info in special array
            void deleteTextures(const int count, fgGfxTextureID* textures);
            // Delete the given texture based on the special information struct
            void deleteTexture(fgGfxTextureID& textureID);

            // Bind texture to 2D
            void bindTexture2D(const fgGFXuint texID);
            // Bind texture to 3D
            void bindTextureCube(const fgGFXuint texID);
            // Bind texture to given target
            void bindTexture(fgGfxTextureID& textureID, const fgGFXenum target = (fgGFXenum)0);

            // Specify the blend equation mode
            void blendEquation(const fgGFXenum mode);
            // Specify the blend equation mode separately for RGB and alpha channels
            void blendEquation(const fgGFXenum modeRGB, const fgGFXenum modeAlpha);
            // Specify the blend functions for source and destination
            void blendFunc(const fgGFXenum sfactor, const fgGFXenum dfactor);
            // Specify the blend functions for source and destination separately for RGB and alpha channels
            void blendFunc(const fgGFXenum srcRGB, const fgGFXenum dstRGB, const fgGFXenum srcAlpha, const fgGFXenum dstAlpha);

            // Use specified shader program
            void useProgram(const fgGFXuint program);
            // Returns the index to currently active vertex program
            fgGFXuint activeProgram(void);

            // Set the viewport dimensions
            void viewport(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height);
            // Set the viewport dimensions
            void viewport(const Vector2i& pos, const Vector2i& size);
            // Set the viewport dimensions
            void viewport(const Vector4i& dimensions);

            // Returns the viewport aspect ratio
            inline fgGFXfloat getViewportAspect(void) {
                fgGFXfloat y = (fgGFXfloat)m_params[(fgGFXuint)GL_VIEWPORT].ints[1];
                if(y <= FG_EPSILON)
                    return 1.0f;
                return (fgGFXfloat)m_params[(fgGFXuint)GL_VIEWPORT].ints[0] / y;
            }

            // Set the scissor box to default dimensions
            inline void scissor(void) {
                scissor(0, 0, m_screenSize.x, m_screenSize.y);
            }
            // Set the scissor box dimensions
            void scissor(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height);
            // Set the scissor box dimensions
            void scissor(const Vector2i& pos, const Vector2i& size);
            // Set the scissor box dimensions
            void scissor(const Vector4i& dimensions);

            // Returns the scissor box aspect ratio
            inline fgGFXfloat getScissorAspect(void) {
                fgGFXfloat y = (fgGFXfloat)m_params[(fgGFXuint)GL_SCISSOR_BOX].ints[1];
                if(y <= FG_EPSILON)
                    return 1.0f;
                return (fgGFXfloat)m_params[(fgGFXuint)GL_SCISSOR_BOX].ints[0] / y;
            }

            // Toggle scissor test capability
            void setScissorTest(const fgBool toggle = FG_TRUE);
            // Toggle depth testing
            void setDepthTest(const fgBool toggle = FG_TRUE);
            // Toggle cull face elimination
            void setCullFace(const fgBool toggle = FG_TRUE);
            // Toggle blending
            void setBlend(const fgBool toggle = FG_TRUE);
            // Set the front face
            void frontFace(const fgGFXenum mode = GL_CCW);
            // Set the cull face
            void cullFace(const fgGFXenum mode = GL_BACK);
            // Set the depth function
            void depthFunc(const fgGFXenum func);
            // Set the clear depth value
            void clearDepth(const fgGFXfloat depth = 1.0f);
            // Set the clear color
            void clearColor(const fgGFXfloat red, const fgGFXfloat green, const fgGFXfloat blue, const fgGFXfloat alpha);
            // Set the clear stencil value
            void clearStencil(const fgGFXint s);
            // Set the pixel unpacking alignment
            void pixelStoreUnPack(const fgGFXint param = 4);
            // Set the pixel packing alignment
            void pixelStorePack(const fgGFXint param = 4);

            // Returns the currently active vertex attribute mask
            fgGFXuint activeVertexAttribArrayMask(void) const;
            // Returns whether given index vertex attrib array is activated
            fgBool isVertexAttribArrayActive(const fgGFXuint index) const;

            // https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
            // Enable the given vertex attrib array index and also by default update the current attrib mask
            void enableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
            // Disable the given vertex attrib array index and also by default update the current attrib mask
            void disableVertexAttribArray(const fgGFXuint index, const fgBool updateMask = FG_TRUE);
            // Enable the vertex attrib arrays based on the given attrib mask
            // Attributes not in the mask will not be deactivated
            void enableVertexAttribArrayMask(const fgGFXuint mask);
            // Disable the vertex attrib arrays based on the given attrib mask
            void disableVertexAttribArrayMask(const fgGFXuint mask);
            // Disable or enable given vertex attrib arrays based on the given mask
            // Attributes not in the mask will be deactivated
            void diffVertexAttribArrayMask(const fgGFXuint mask);


            // https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetVertexAttrib.xml
            // Returns the buffer (VBO) index currently bound to given vertex attrib index
            fgGFXuint getVertexAttribBufferBinding(const fgGFXuint index);
            //
            fgGFXuint getVertexAttribSize(const fgGFXuint index);
            // Returns the vertex attrib data stride for the given index
            fgGFXuint getVertexAttribStride(const fgGFXuint index);
            // Returns the vertex attrib data type
            fgGFXenum getVertexAttribType(const fgGFXuint index);
            // Returns whether the given attrib array is normalized
            fgGFXboolean getVertexAttribNormalized(const fgGFXuint index);

            // https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
            // Sets the various data details for given vertex attribute index
            void vertexAttribPointer(fgGFXuint index,
                                     fgGFXint size,
                                     fgGFXenum type,
                                     fgGFXboolean normalized,
                                     fgGFXsizei stride,
                                     fgGFXvoid* ptr);

            // Sets the various data details based on a special attribute data struct
            void vertexAttribPointer(fgGfxAttributeData& attrData);

        };
    };
};

    #undef FG_INC_GFX_CONTEXT_BLOCK
#endif /* FG_INC_GFX_CONTEXT */
