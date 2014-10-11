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
#define FG_GFX_PARAM_BOOL			1
#define FG_GFX_PARAM_FLOAT			2
#define FG_GFX_PARAM_INT			3
#define FG_GFX_PARAM_ATTRIB			4
#define FG_GFX_PARAM_BLEND_FUNC			5
#define FG_GFX_PARAM_BLEND_EQ			6
#define FG_GFX_PARAM_BLEND_COLOR		7
#define FG_GFX_PARAM_VIEWPORT			8
#define FG_GFX_PARAM_SCISSOR			9
#define FG_GFX_PARAM_TEXTURE_2D			10
#define FG_GFX_PARAM_TEXTURE_3D			11
#define FG_GFX_PARAM_TEXTURE			12
#define FG_GFX_PARAM_VERT_BUFFER_BIND           13
#define FG_GFX_PARAM_ELEM_BUFFER_BIND           14
#define FG_GFX_PARAM_CLEAR_DEPTH		15
#define FG_GFX_PARAM_CLEAR_COLOR		16
#define FG_GFX_PARAM_COLOR_MASK			17
#define FG_GFX_PARAM_FRONT_FACE			18
#define FG_GFX_PARAM_CULL_FACE			19
#define FG_GFX_PARAM_PROGRAM			20
#define FG_GFX_PARAM_DEPTH_FUNC			21
#define FG_GFX_PARAM_DEPTH_RANGE		22
#define FG_GFX_PARAM_DEPTH_MASK			23
#define FG_GFX_PARAM_FRAME_BUFFER_BIND          24
#define FG_GFX_PARAM_RENDER_BUFFER_BIND         25
#define FG_GFX_PARAM_HINT                       26
#define FG_GFX_PARAM_SAMPLE_COVERAGE            27
#define FG_GFX_PARAM_STENCIL_FUNC		28
#define FG_GFX_PARAM_STENCIL_OP			29
#define FG_GFX_PARAM_STENCIL_MASK		30
#define FG_GFX_PARAM_CLEAR_STENCIL		31
#define FG_GFX_PARAM_PIXEL_STORE		32

/*
 *
 */
struct fgGfxContextParam {
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

    operator fgGFXint() const {
        return intVal;
    }

    operator fgGFXfloat() const {
        return floatVal;
    }

    operator fgGFXboolean() const {
        return boolVal;
    }

    operator fgGFXuint() const {
        return (fgGFXuint) intVal;
    }
#if defined(FG_USING_GL_BINDING)

    operator fgGFXenum() const {
        return (fgGFXenum) intVal;
    }
#endif

    operator bool() const {
        return ( intVal ? true : false);
    }

    inline bool operator==(fgGFXint a) const {
        return (intVal == a);
    }

    inline bool operator!=(fgGFXint a) const {
        return (intVal != a);
    }

    inline bool operator>(fgGFXint a) const {
        return (intVal > a);
    }

    inline bool operator<(fgGFXint a) const {
        return (intVal < a);
    }

    inline bool operator==(fgGFXfloat a) const {
        return (floatVal == a);
    }

    inline bool operator!=(fgGFXfloat a) const {
        return (floatVal != a);
    }

    inline bool operator>(fgGFXfloat a) const {
        return (floatVal > a);
    }

    inline bool operator<(fgGFXfloat a) const {
        return (floatVal < a);
    }

    inline bool operator==(fgGFXuint a) const {
        return ((fgGFXuint) intVal == a);
    }

    inline bool operator!=(fgGFXuint a) const {
        return ((fgGFXuint) intVal != a);
    }

    inline bool operator>(fgGFXuint a) const {
        return ((fgGFXuint) intVal > a);
    }

    inline bool operator<(fgGFXuint a) const {
        return ((fgGFXuint) intVal < a);
    }

    // 

    void load(void) {
        if (paramType == FG_GFX_PARAM_INVALID)
            return;
        switch (type) {
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

    void determineParamType(void);

    fgBool update(void);

    // 

    fgGfxContextParam(const fgGFXenum _pname = (fgGFXenum) 0) :
    pname(_pname),
    type(FG_GFX_BOOL),
    paramType(FG_GFX_PARAM_INVALID),
    count(1) {
        memset(ints, 0, 8);
        determineParamType();
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const fgGFXfloat _fval) :
    pname(_pname),
    type(FG_GFX_FLOAT),
    count(1) {
        floats[0] = _fval;
        determineParamType();
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const fgGFXint _ival) :
    pname(_pname),
    type(FG_GFX_INT),
    count(1) {
        ints[0] = _ival;
        determineParamType();
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const fgGFXboolean _bval) :
    pname(_pname),
    type(FG_GFX_BOOL),
    count(1) {
        booleans[0] = _bval;
        determineParamType();
        //update();
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXfloat *_fvals) :
    pname(_pname),
    count(_count) {
        determineParamType();
        set(_fvals, FG_FALSE);
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXint *_ivals) :
    pname(_pname),
    count(_count) {
        determineParamType();
        set(_ivals, FG_FALSE);
    }

    // 

    fgGfxContextParam(const fgGFXenum _pname, const int _count, const fgGFXboolean *_bvals) :
    pname(_pname),
    count(_count) {
        determineParamType();
        set(_bvals, FG_FALSE);
    }

    // 

    void set(const fgGFXfloat _fval, const fgBool update = FG_TRUE) {
        type = FG_GFX_FLOAT;
        count = 1;
        if (fabsf(floats[0] - _fval) > FG_EPSILON) {
            floats[0] = _fval;
            if (update)
                this->update();
        }
    }

    // 

    void set(const fgGFXint _ival, const fgBool update = FG_TRUE) {
        type = FG_GFX_INT;
        count = 1;
        if (ints[0] != _ival) {
            ints[0] = _ival;
            if (update)
                this->update();
        }
    }

    void set(const fgGFXint _i0, const fgGFXint _i1, const fgGFXint _i2, const fgGFXint _i3, const fgBool update = FG_TRUE) {
        type = FG_GFX_INT;
        count = 4;
        if (ints[0] != _i0 ||
                ints[1] != _i1 ||
                ints[2] != _i2 ||
                ints[3] != _i3) {
            ints[0] = _i0;
            ints[1] = _i1;
            ints[2] = _i2;
            ints[3] = _i3;
            if (update)
                this->update();
        }
    }

    void set(const fgGFXfloat _f0, const fgGFXfloat _f1, const fgGFXfloat _f2, const fgGFXfloat _f3, const fgBool update = FG_TRUE) {
        type = FG_GFX_INT;
        count = 4;
        if (floats[0] != _f0 ||
                floats[1] != _f1 ||
                floats[2] != _f2 ||
                floats[3] != _f3) {
            floats[0] = _f0;
            floats[1] = _f1;
            floats[2] = _f2;
            floats[3] = _f3;
            if (update)
                this->update();
        }
    }

    // 

    void set(const fgGFXboolean _bval, const fgBool update = FG_TRUE) {
        type = FG_GFX_BOOL;
        if (booleans[0] != _bval) {
            booleans[0] = _bval;
            if (update)
                this->update();
        }
    }

    // 

    void set(const fgGFXfloat *_fvals, const fgBool update = FG_TRUE) {
        if (!_fvals)
            return;
        type = FG_GFX_FLOAT;
        fgBool diff = FG_FALSE;
        for (int i = 0; i < count; i++) {
            if (diff || fabs(floats[i] - _fvals[i]) > FG_EPSILON) {
                floats[i] = _fvals[i];
                diff = FG_TRUE;
            }
        }
        if (update && diff)
            this->update();
    }

    // 

    void set(const fgGFXint *_ivals, const fgBool update = FG_TRUE) {
        if (!_ivals)
            return;
        type = FG_GFX_INT;
        fgBool diff = FG_FALSE;
        for (int i = 0; i < count; i++) {
            if (diff || ints[i] != _ivals[i]) {
                ints[i] = _ivals[i];
                diff = FG_TRUE;
            }
        }
        if (update && diff)
            this->update();
    }

    // 

    void set(const fgGFXboolean *_bvals, const fgBool update = FG_TRUE) {
        if (!_bvals)
            return;
        type = FG_GFX_BOOL;
        fgBool diff = FG_FALSE;
        for (int i = 0; i < count; i++) {
            if (booleans[i] != _bvals[i]) {
                booleans[i] = _bvals[i];
                diff = FG_TRUE;
            }
        }
        if (update && diff)
            this->update();
    }

    // 

    void *get(fgGFXenum *_type = NULL) {
        if (_type)
            *_type = type;

        if (type == FG_GFX_FLOAT)
            return (void *) floats;
        else if (type == FG_GFX_INT)
            return (void *) ints;
        return (void *) booleans;
    }
};

struct fgGfxAttrInfo {
    fgGFXuint   index;
    fgGFXint    size;
    fgGFXenum   type;
    fgGFXboolean normalized;
    fgGFXsizei  stride;
    fgGFXvoid*  ptr;
    fgBool      enabled;
    fgGFXuint   bufferBind;
};

/*
 *
 */
class fgGfxContext {
    friend class fgGfxPlatform;
public:
    //typedef std::map<fgGFXenum, fgGfxContextParam> gfxParamMap;
    typedef std::map<fgGFXuint, fgGfxContextParam> gfxParamMap;
    typedef gfxParamMap::iterator gfxParamMapItor;

    typedef std::map<fgGFXuint, fgGfxTextureID*> gfxTextureMap;
    typedef gfxTextureMap::iterator gfxTextureMapItor;

    typedef std::map<fgGFXuint, fgGfxBufferID*> gfxBufferMap;
    typedef gfxBufferMap::iterator gfxBufferMapItor;

private:
#if defined(FG_USING_SDL2)
    SDL_GLContext   m_GLContext;  // #FIXME - context can be separate? ... P4
    SDL_Window*     m_sdlWindow;    // #FIXME - NOPE, NOPE, NOPE
#endif
    /// Special parameter map used for caching and fast value check
    /// It's used for not calling redundant GL functions, like:
    /// glGet/glEnable/glDisable/glIsEnabled and so on. Also for
    /// functions like activating proper vertex attrib array idx,
    /// bounding textures... any kind of function that changes internal
    /// state values.
    gfxParamMap     m_params;
    /// Special map used for holding valid texture IDs
    /// Every texture needs to be created/deleted through
    /// this class. When texture is deleted its' ID is zeroed
    /// in every place in the app. Therefore there's no need to
    /// often call glIsTexture. If gfx ID is not zero the texture
    /// is surely valid.
    gfxTextureMap   m_textures;
    /// Special map used for holding valid VBO IDs. Use case
    /// is the same as for textures.
    gfxBufferMap    m_buffers;
    /// Viewport area (used for fast check if viewport changed)
    fgGFXuint       m_viewportAreaQ;
    /// Scissor area
    fgGFXuint       m_scissorAreaQ;

    /// Currently used attribute mask
    fgGFXuint       m_attribMask;
    ///
    fgGfxAttrInfo   m_attrInfo[12];   // #FIXME - attribute count ... why here?  hello?
    /// Currently bound texture ID
    fgGFXuint       m_boundTexture;
    /// Supported shading language version
    fgGfxSLVersion  m_SLVersion;

protected:
    //
#if defined(FG_USING_SDL2)
    fgGfxContext(SDL_Window *sdlWindow);
#else
    fgGfxContext();
#endif
    //
    virtual ~fgGfxContext();
    
    // This function will set or unset given attrib bits
    // depending on the current mask value
    void updateAttribMask(const fgGFXuint index);

public:
    // Return version ID for shading language currently supported by the graphics context
    fgGfxSLVersion getSLVersion(void) const {
        return m_SLVersion;
    }
    
    // Initialize the context and internal parameter state
    void initialize(void);
    // Get parameter structure
    fgGfxContextParam& getParam(const fgGFXenum pname);

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

    // Delete/release all buffers registered within this context
    void deleteAllBuffers(void);

    // Generate given number of buffers
    fgGFXboolean genBuffers(const int count, fgGfxBufferID* buffers, const fgGFXenum usage = GL_STATIC_DRAW);

    // Set buffer data
    void bufferData(
            fgGfxBufferID& bufferID,
            const fgGFXsizei size,
            const fgGFXvoid* data,
            const fgGFXenum target = GL_ARRAY_BUFFER,
            const fgGFXenum usage = (fgGFXenum) 0);

    // Bind given buffer ID to target array
    void bindBuffer(const fgGFXenum target, const fgGFXuint buffer);
    // Bind given buffer ID to target array
    void bindBuffer(fgGfxBufferID& bufferID, const fgGFXenum target = (fgGFXenum) 0);
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

    //
    void genTextures(const int count, fgGfxTextureID* textures, const fgGFXenum target = GL_TEXTURE_2D);
    //
    void genTexture(fgGfxTextureID* texture, const fgGFXenum target = GL_TEXTURE_2D);

    //
    void deleteTextures(const int count, fgGfxTextureID* textures);
    //
    void deleteTexture(fgGfxTextureID& textureID);

    //
    void bindTexture2D(const fgGFXuint texID);
    //
    void bindTexture3D(const fgGFXuint texID);
    //
    void bindTexture(fgGfxTextureID& textureID, const fgGFXenum target = (fgGFXenum) 0);

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
    void pixelStoreUnPack(const fgGFXint param = 4);
    //
    void pixelStorePack(const fgGFXint param = 4);

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
    fgGFXenum getVertexAttribType(const fgGFXuint index);
    //
    fgGFXboolean getVertexAttribNormalized(const fgGFXuint index);

    // https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
    void vertexAttribPointer(fgGFXuint index,
            fgGFXint size,
            fgGFXenum type,
            fgGFXboolean normalized,
            fgGFXsizei stride,
            fgGFXvoid* ptr);

};

#endif /* _FG_GFX_CONTEXT_H_ */
