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
    #define _FG_GFX_DRAW_CALL_H_BLOCK_

    #ifndef _FG_GFX_PRIMITIVES_H_
        #include "fgGFXPrimitives.h"
    #endif

    #define FG_GFX_DRAW_CALL_INVALID        0
    #define FG_GFX_DRAW_CALL_VERTEX_BUFFER  1
    #define FG_GFX_DRAW_CALL_CUSTOM_ARRAY   2
    #define FG_GFX_DRAW_CALL_MESH           3

    #ifndef _FG_GFX_SHADER_DEFS_H_
        #include "GFX/Shaders/fgGFXShaderDefs.h"
    #endif
    #ifndef _FG_GFX_SHADER_PROGRAM_H_
        #include "GFX/Shaders/fgGFXShaderProgram.h"
    #endif
    #ifndef _FG_GFX_TYPES_H_
        #include "fgGFXTypes.h"
    #endif

    #ifndef _FG_GFX_MVP_MATRIX_H_
        #include "fgGFXMVPMatrix.h"
    #endif

    #ifndef _FG_GFX_MODEL_TYPES_H_
        #include "fgGFXModelTypes.h"
    #endif

    #ifndef _FG_GFX_DRAWABLE_H_
        #include "fgGFXDrawable.h"
    #endif

// Draw call type
typedef unsigned int fgGfxDrawCallType;
// Draw call append mode
typedef unsigned int fgGfxDrawAppendMode;

    #define FG_GFX_DRAW_APPEND_ABSOLUTE 0
    #define FG_GFX_DRAW_APPEND_RELATIVE 1

// Drawable type
    #define FG_GFX_DRAWABLE_DRAWCALL 1


class fgGfxDrawingBatch;

/*
 * Special class representing a single draw call
 */
class fgGfxDrawCall : public fgGfxDrawable {
    friend class fgGfxDrawingBatch;
public:
    typedef fgGfxDrawable base_type;

private:
    /// Attribute binding data // Need to think what do with indices ?
    fgGfxAttributeData m_attrData[FG_GFX_ATTRIBUTE_COUNT];
    /// Information on indices used in this draw call
    /// Pointers within must be always valid
    fgGfxDrawingInfo m_drawingInfo;
    /// Special vector data
    fgVertexData *m_vecDataBase;
    /// Pointer to the shader program used in this draw call
    /// It can be set to NULL, then the draw call will use
    /// last active shader program. The pointer to the shader
    /// program is required for updating uniform variables
    fgGfxShaderProgram *m_program;
    /// Pointer to the used texture - this will require also pointer
    /// to the shader program (so the proper uniform sampler variable
    /// can be updated). However this is not always required.
    /// If there is no multitexturing then there's always one
    /// texture active (TEXTURE0).
    fgGfxTextureID m_textureID;
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
    /// Append mode
    fgGfxDrawAppendMode m_drawAppendMode;
    /// Primitive mode used for drawing the vertex buffer
    /// It defaults to FG_GFX_TRIANGLES, however the most
    /// optimal is the Triangle Strip - this requires however
    /// modification of the vertex data after loading
    fgGfxPrimitiveMode m_primMode;
    /// Current color used
    fgColor4f m_color;
    /// Holds the value for the relative move
    fgVector3f m_relMove;
    /// Holds value for special Z index used for more direct sorting
    int m_zIndex;
    /// Is this draw call managed by the drawing batch? 
    /// Or any other mechanism? If true then when on drawing batch flush
    /// this draw call will be destroyed. If false no destructor will be called.
    /// Use with caution, if set to false wrongfully it may cause overallocation
    /// and memory leaks.
    fgBool m_isManaged;

private:
    /**
     * 
     * @param attribMask
     */
    void setupVertexData(fgGFXuint attribMask);
    /**
     * 
     */
    fgBool applyAttributeData(void);

protected:
    // Toggle the managed flag
    void setManaged(const fgBool toggle = FG_TRUE);

public:
    /**
     * Default constructor
     * @param type
     * @param attribMask
     */
    fgGfxDrawCall(const fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                  const fgGFXuint attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    /**
     * Default destructor for the draw call object
     */
    virtual ~fgGfxDrawCall();

    /**
     * 
     * @param pMesh
     */
    void setupFromMesh(const fgGfxMeshBase* pMesh);

    // Returns the current Z index
    int getZIndex(void) const;
    // Returns whether the draw call is managed
    fgBool isManaged(void) const;
    // Returns the pointer to the attribute data array
    fgGfxAttributeData* getAttributeData(void);
    // Returns currently active attribute mask
    fgGFXuint getAttribMask(void) const;
    // Returns the draw call type identifier
    fgGfxDrawCallType getDrawCallType(void) const;
    // Returns the append mode for the current draw call
    fgGfxDrawAppendMode getDrawAppendMode(void) const;
    // Returns the primitive mode used for drawing
    fgGfxPrimitiveMode getPrimitiveMode(void) const;
    //
    fgVertexData *getVertexData(void) const;

    // Sets the Z index to specified value
    void setZIndex(const int zIndex);
    // Increments by 1 the Z index
    void upZIndex(void);
    // Lowers the Z index
    void downZIndex(void);
    // Sets the draw call type
    void setDrawCallType(const fgGfxDrawCallType type);
    // Sets the append mode
    void setDrawAppendMode(const fgGfxDrawAppendMode mode);
    // Sets the primitive mode for the draw call
    void setPrimitiveMode(const fgGfxPrimitiveMode mode);

    // Whether to set UVs, normals or colors active
    void setComponentActive(unsigned int component);

    // Set active color for the next data
    virtual void setColor(const fgColor3f& color);
    // Set active color for the next data
    virtual void setColor(const fgColor4f& color);
    // This will reset used color
    virtual void resetColor(void);

    // Sets the pointer to given MVP matrix
    void setMVP(fgGfxMVPMatrix *MVP = NULL);
    // Returns the pointer to currently used MVP matrix
    fgGfxMVPMatrix *getMVP(void) const;

    // Can be null, which would mean that this draw call does not care about such thing
    // However it should be avoided. Shader program knows if it's being currently used.
    // Also only through shader manager given shader program can be set as active.
    void setShaderProgram(fgGfxShaderProgram *pProgram = NULL);
    // Returns the currently used shader program for this draw call
    fgGfxShaderProgram *getShaderProgram(void) const;

    // Sets the texture pointer
    void setTexture(const fgGfxTextureID& textureID);
    // Returns the texture ID reference
    fgGfxTextureID const & getTexture(void) const;
    // Returns the texture ID reference
    fgGfxTextureID& getTexture(void);

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

    // Draw
    virtual void draw(void);
    // Draw with relative 2D position
    virtual inline void draw(const fgVec2f& relPos) {
        fgGfxDrawCall::draw(fgMath::translate(fgMatrix4f(), fgVec3f(relPos.x, relPos.y, 0.0f)));
    }
    // Draw with relative 3D position
    virtual inline void draw(const fgVec3f& relPos) {
        fgGfxDrawCall::draw(fgMath::translate(fgMatrix4f(), relPos));
    }
    // Draw with given model matrix
    virtual inline void draw(const fgMatrix4f& modelMat) {
        if(m_MVP && m_program) {
            m_MVP->calculate(modelMat);
        }
        fgGfxDrawCall::draw();
    }

    ///////////////////////////////////////////////////////
    // COMPARISON OPERATORS

    //
    inline int operator ==(const fgGfxDrawCall& b) const {
        if(b.m_program == this->m_program) {
            if(b.m_textureID == this->m_textureID) {
                if(b.m_attribMask == this->m_attribMask) {
                    return 1;
                }
            }
        }
        return 0;
    }

    //
    inline int operator !=(const fgGfxDrawCall& b) const {
        if(b.m_program != this->m_program)
            return 1;

        if(b.m_textureID != this->m_textureID)
            return 1;

        if(b.m_attribMask != this->m_attribMask)
            return 1;


        return 0;
    }

    //
    inline bool operator <(const fgGfxDrawCall& a) const {
        if(this->m_program < a.m_program)
            return true;
        else if(this->m_program > a.m_program)
            return false;
        else {
            if(this->m_zIndex < a.m_zIndex)
                return true;
            else if(this->m_zIndex > a.m_zIndex)
                return false;
            else {
                if(this->m_textureID < a.m_textureID)
                    return true;
                else if(this->m_textureID > a.m_textureID)
                    return false;
                else {
                    if(this->m_attribMask < a.m_attribMask)
                        return true;
                    else
                        return false;
                }
            }
        }
        return false;
    }

    //
    inline bool operator >(const fgGfxDrawCall& a) const {
        if(this->m_program < a.m_program)
            return false;
        else if(this->m_program > a.m_program)
            return true;
        else {
            if(this->m_zIndex < a.m_zIndex)
                return false;
            else if(this->m_zIndex > a.m_zIndex)
                return true;
            else {
                if(this->m_textureID < a.m_textureID)
                    return false;
                else if(this->m_textureID > a.m_textureID)
                    return true;
                else {
                    if(this->m_attribMask < a.m_attribMask)
                        return false;
                    else
                        return true;
                }
            }
        }
        return false;
    }

    //
    inline bool operator <=(const fgGfxDrawCall& a) const {
        if(this->m_program < a.m_program)
            return true;
        else if(this->m_program > a.m_program)
            return false;
        else {
            if(this->m_zIndex < a.m_zIndex)
                return true;
            else if(this->m_zIndex > a.m_zIndex)
                return false;
            else {
                if(this->m_textureID < a.m_textureID)
                    return true;
                else if(this->m_textureID > a.m_textureID)
                    return false;
                else {
                    if(this->m_attribMask < a.m_attribMask)
                        return true;
                    else if(this->m_attribMask > a.m_attribMask)
                        return false;
                }
            }
        }
        return true;
    }

    //
    inline bool operator >=(const fgGfxDrawCall& a) const {
        if(this->m_program < a.m_program)
            return false;
        else if(this->m_program > a.m_program)
            return true;
        else {
            if(this->m_zIndex < a.m_zIndex)
                return false;
            else if(this->m_zIndex > a.m_zIndex)
                return true;
            else {
                if(this->m_textureID < a.m_textureID)
                    return false;
                else if(this->m_textureID > a.m_textureID)
                    return true;
                else {
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

    #if 0
        #ifndef FG_PTR_COMPARE_DRAWABLE_DEFINED_
            #define FG_PTR_COMPARE_DRAWABLE_DEFINED_

template <>
class fgPtrLess<fgGfxDrawable *> {
public:
    inline bool operator ()(fgGfxDrawable * left, fgGfxDrawable * right) {
        if(left->getDrawableType() == FG_GFX_DRAWABLE_DRAWCALL) {
            return *(static_cast<fgGfxDrawCall *>(left)) < *(static_cast<fgGfxDrawCall *>(right));
        }
        //return ((*left) < (*right));
        return false;
    }
};

template <>
class fgPtrGreater<fgGfxDrawable *> {
public:
    inline bool operator ()(fgGfxDrawable * left, fgGfxDrawable * right) {
        if(left->getDrawableType() == FG_GFX_DRAWABLE_DRAWCALL) {
            return !(*(static_cast<fgGfxDrawCall *>(left)) < *(static_cast<fgGfxDrawCall *>(right)));
        }
        //return !((*left) < (*right));
        return false;
    }
};

template <>
class fgPtrLessEq<fgGfxDrawable *> {
public:
    inline bool operator ()(fgGfxDrawable * left, fgGfxDrawable * right) {
        if(left->getDrawableType() == FG_GFX_DRAWABLE_DRAWCALL) {
            return *(static_cast<fgGfxDrawCall *>(left)) <= *(static_cast<fgGfxDrawCall *>(right));
        }
        //return ((*left) <= (*right));
        return false;
    }
};

template <>
class fgPtrGreaterEq<fgGfxDrawable *> {
public:
    inline bool operator ()(fgGfxDrawable * left, fgGfxDrawable * right) {
        if(left->getDrawableType() == FG_GFX_DRAWABLE_DRAWCALL) {
            return !(*(static_cast<fgGfxDrawCall *>(left)) <= *(static_cast<fgGfxDrawCall *>(right)));
        }
        return false;
        //return !((*left) <= (*right));
    }
};
        #endif /* FG_PTR_COMPARE_DRAWABLE_DEFINED_ */
    #endif

    #undef _FG_GFX_DRAW_CALL_H_BLOCK_
#endif /* _FG_GFX_DRAW_CALL_H_ */
