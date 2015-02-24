/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_DRAW_CALL
    #define FG_INC_GFX_DRAW_CALL
    #define FG_INC_GFX_DRAW_CALL_BLOCK

    #ifndef FG_INC_GFX_PRIMITIVES
        #include "fgGFXPrimitives.h"
    #endif

    #define FG_GFX_DRAW_CALL_INVALID        0
    #define FG_GFX_DRAW_CALL_VERTEX_BUFFER  1
    #define FG_GFX_DRAW_CALL_CUSTOM_ARRAY   2
    #define FG_GFX_DRAW_CALL_MESH           3

    #ifndef FG_INC_GFX_SHADER_DEFS
        #include "GFX/Shaders/fgGFXShaderDefs.h"
    #endif
    #ifndef FG_INC_GFX_SHADER_PROGRAM
        #include "GFX/Shaders/fgGFXShaderProgram.h"
    #endif
    #ifndef FG_INC_GFX_TYPES
        #include "fgGFXTypes.h"
    #endif

    #ifndef FG_INC_GFX_MVP_MATRIX
        #include "fgGFXMVPMatrix.h"
    #endif

    #ifndef FG_INC_GFX_MODEL_TYPES
        #include "fgGFXModelTypes.h"
    #endif

    #ifndef FG_INC_GFX_DRAWABLE
        #include "fgGFXDrawable.h"
    #endif

// Draw call type
typedef unsigned int fgGfxDrawCallType;

    #include "Util/fgFastCmp.h"

namespace fg {
    namespace gfx {

        const unsigned int Z_INDEX_DEFAULT = 127; // center / zero
        const unsigned int Z_INDEX_MIN = 0; // it's like -127
        const unsigned int Z_INDEX_MAX = 255; // +127
        
        const unsigned int Z_INDEX_PARTICLES = 100;
        const unsigned int Z_INDEX_OBJECTS_3D = 120;

        /**
         * Draw call append mode
         */
        enum DrawAppendMode {
            ///
            DRAW_APPEND_ABSOLUTE,
            ///
            DRAW_APPEND_RELATIVE
        };

        class CDrawingBatch;
        struct SMaterial;

        /**
         * Special class representing a single draw call
         */
        class CDrawCall : public CDrawable {
            friend class fg::gfx::CDrawingBatch;
            
        public:
            typedef fg::gfx::CDrawable base_type;

        private:
            /// Attribute binding data
            SAttributeData m_attrData[FG_GFX_ATTRIBUTE_COUNT];
            /// Information on indices used in this draw call
            /// Pointers within must be always valid
            SDrawingInfo m_drawingInfo;
            /// Special vector data
            CVertexData *m_vecDataBase;
            ///
            CVertexData *m_vecData2v;
            ///
            CVertexData *m_vecData3v;
            ///
            CVertexData *m_vecData4v;
            /// Pointer to the shader program used in this draw call
            /// It can be set to NULL, then the draw call will use
            /// last active shader program. The pointer to the shader
            /// program is required for updating uniform variables
            CShaderProgram *m_program;
            /// Pointer to the used texture - this will require also pointer
            /// to the shader program (so the proper uniform sampler variable
            /// can be updated). However this is not always required.
            /// If there is no multitexturing then there's always one
            /// texture active (TEXTURE0).
            STextureID m_textureID;
            /// Pointer to external MVP matrix to use
            /// this will need to be updated for every drawcall made
            /// because the model matrix would change
            /// view and projection matrix parameters stay the same (mostly)
            /// through all drawing batch
            CMVPMatrix *m_MVP;
            /// Pointer to external material struct - can be NULL
            SMaterial *m_material;
            /// Used vertex data will depend on the attribute mask used
            /// Appending specific data however may alter this and make 
            /// other buffers invalid
            fgGFXuint m_attribMask;
            /// What kind of draw call is this?
            fgGfxDrawCallType m_drawCallType;
            /// Append mode
            DrawAppendMode m_drawAppendMode;
            /// Primitive mode used for drawing the vertex buffer
            /// It defaults to FG_GFX_TRIANGLES, however the most
            /// optimal is the Triangle Strip - this requires however
            /// modification of the vertex data after loading
            PrimitiveMode m_primMode;
            /// Current color used
            fgColor4f m_color;
            /// Holds the value for the relative move
            Vector3f m_relMove;
            /// Scissor box for current draw call
            Vector4i m_scissorBox;
            ///
            util::FastCmp m_fastCmp;
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
            CDrawCall(const fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                      const fgGFXuint attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
            /**
             * Default destructor for the draw call object
             */
            virtual ~CDrawCall();

            /**
             * 
             * @param pMesh
             */
            void setupFromMesh(const SMeshBase* pMesh);
            
            /**
             * 
             * @param pShape
             */
            void setupFromShape(const SShape* pShape);
            
            /**
             * 
             * @param pMaterial
             */
            void setupMaterial(const SMaterial* pMaterial);

            ////////////////////////////////////////////////////////////////////
            
            /**
             * 
             * @return 
             */
            SMaterial *getMaterial(void) const;
            
            /**
             * 
             * @return 
             */
            Vector4i const& getScissorBox(void) const;
            /**
             * 
             * @return 
             */
            Vector3f const& getRelMove(void) const;
            /**
             * Returns the current Z index
             * @return 
             */
            int getZIndex(void) const;
            /**
             * Returns whether the draw call is managed
             * @return 
             */
            fgBool isManaged(void) const;
            /**
             * Returns the pointer to the attribute data array
             * @return 
             */
            SAttributeData* getAttributeData(void);
            /**
             * Returns currently active attribute mask
             * @return 
             */
            fgGFXuint getAttribMask(void) const;
            /**
             * Returns the draw call type identifier
             * @return 
             */
            fgGfxDrawCallType getDrawCallType(void) const;
            /**
             * Returns the append mode for the current draw call
             * @return 
             */
            DrawAppendMode getDrawAppendMode(void) const;
            /**
             * Returns the primitive mode used for drawing
             * @return 
             */
            PrimitiveMode getPrimitiveMode(void) const;
            /**
             * 
             * @return 
             */
            CVertexData *getVertexData(void) const;

            /**
             * 
             * @param x
             * @param y
             * @param width
             * @param height
             */
            void setScissorBox(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height);
            /**
             * 
             * @param pos
             * @param size
             */
            void setScissorBox(const Vector2i& pos, const Vector2i& size);
            /**
             * 
             * @param dimensions
             */
            void setScissorBox(const Vector4i& dimensions);
            /**
             * 
             * @param relMove
             */
            void setRelMove(const Vector3f& relMove);
            /**
             * 
             * @param relMove
             */
            void setRelMove(const Vector2f& relMove);
            /**
             * Sets the Z index to specified value
             * @param zIndex
             */
            void setZIndex(const int zIndex = Z_INDEX_DEFAULT);
            /**
             * Increments by 1 the Z index
             */
            void upZIndex(void);
            /**
             *  Lowers the Z index
             */
            void downZIndex(void);
            /**
             * Sets the draw call type
             * @param type
             */
            void setDrawCallType(const fgGfxDrawCallType type);
            /**
             * Sets the append mode
             * @param mode
             */
            void setDrawAppendMode(const DrawAppendMode mode);
            /**
             *  Sets the primitive mode for the draw call
             * @param mode
             */
            void setPrimitiveMode(const PrimitiveMode mode);

            /**
             * Whether to set UVs, normals or colors active
             * @param component
             * @param reset
             */
            void setComponentActive(unsigned int component, const fgBool reset = FG_FALSE);

            ////////////////////////////////////////////////////////////////////
            
            /**
             * Set active color for the next data
             * @param color
             */
            virtual void setColor(const fgColor3f & color);
            /**
             * Set active color for the next data
             * @param color
             */
            virtual void setColor(const fgColor4f & color);
            /**
             * This will reset used color
             */
            virtual void resetColor(void);
            
            ////////////////////////////////////////////////////////////////////

            /**
             * Sets the pointer to given MVP matrix
             * @param MVP
             */
            void setMVP(CMVPMatrix* MVP = NULL);
            /**
             * Returns the pointer to currently used MVP matrix
             * @return 
             */
            CMVPMatrix* getMVP(void) const;

            // Can be null, which would mean that this draw call does not care about such thing
            // However it should be avoided. Shader program knows if it's being currently used.
            // Also only through shader manager given shader program can be set as active.
            void setShaderProgram(gfx::CShaderProgram* pProgram = NULL);
            /**
             * Returns the currently used shader program for this draw call
             * @return 
             */
            gfx::CShaderProgram* getShaderProgram(void) const;

            ////////////////////////////////////////////////////////////////////
            
            /**
             * Sets the texture pointer
             * @param textureID
             */
            void setTexture(const STextureID& textureID);
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID const& getTexture(void) const;
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID& getTexture(void);

            ////////////////////////////////////////////////////////////////////
            
            /**
             * Clear the buffers
             */
            virtual void flush(void);

            /**
             * Append simple rectangle next to the last one
             * @param size
             * @param uv1
             * @param uv2
             * @param rewind
             */
            void appendRect2D(const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const fgBool rewind = FG_FALSE);

            /**
             * Append simple rectangle with relative position to the last data
             * @param relPos
             * @param size
             * @param uv1
             * @param uv2
             * @param rewind
             */
            void appendRect2D(const Vector2f &relPos, const Vector2f &size,
                              const Vector2f &uv1, const Vector2f &uv2,
                              const fgBool rewind = FG_FALSE);

            ////////////////////////////////////////////////////////////////////
            
            /**
             * 
             */
            virtual void draw(void);
            /**
             * Draw with relative 2D position
             * @param relPos
             */
            virtual inline void draw(const Vector2f & relPos) {
                CDrawCall::draw(math::translate(Matrix4f(), Vector3f(relPos.x, relPos.y, 0.0f)));
            }
            /**
             * Draw with relative 3D position
             * @param relPos
             */
            virtual inline void draw(const Vector3f & relPos) {
                CDrawCall::draw(math::translate(Matrix4f(), relPos));
            }
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual inline void draw(const Matrix4f & modelMat) {
                if(m_MVP && m_program) {
                    m_MVP->calculate(modelMat);
                }
                CDrawCall::draw();
            }

            ////////////////////////////////////////////////////////////////////
            // COMPARISON OPERATORS

            //
            inline int operator ==(const CDrawCall & b) const {
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
            inline int operator !=(const CDrawCall & b) const {
                if(b.m_program != this->m_program)
                    return 1;

                if(b.m_textureID != this->m_textureID)
                    return 1;

                if(b.m_attribMask != this->m_attribMask)
                    return 1;

                return 0;
            }

            //
            inline bool operator <(const CDrawCall & a) const {
                return fg::util::FastCmp::less32(this->m_fastCmp, a.m_fastCmp);
            }

            //
            inline bool operator >(const CDrawCall & a) const {
                return fg::util::FastCmp::greater32(this->m_fastCmp, a.m_fastCmp);
            }

            //
            inline bool operator <=(const CDrawCall & a) const {
                return fg::util::FastCmp::less_eq32(this->m_fastCmp, a.m_fastCmp);
            }

            //
            inline bool operator >=(const CDrawCall & a) const {
                return fg::util::FastCmp::greater_eq32(this->m_fastCmp, a.m_fastCmp);
            }

            //
    #if 0
            inline bool operator <(const CDrawCall & a) const {
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
            inline bool operator >(const CDrawCall & a) const {
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
            inline bool operator <=(const CDrawCall & a) const {
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
            inline bool operator >=(const CDrawCall & a) const {
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
    #endif
        };
    };
};
    #if 0
        #ifndef FG_PTR_COMPARE_DRAWABLE_DEFINED_
            #define FG_PTR_COMPARE_DRAWABLE_DEFINED_

template <>
class fgPtrLess<CDrawable *> {
public:
    inline bool operator ()(CDrawable * left, CDrawable * right) {
        if(left->getDrawableType() == DRAWABLE_DRAWCALL) {
            return *(static_cast<CDrawCall *>(left)) < *(static_cast<CDrawCall *>(right));
        }
        //return ((*left) < (*right));
        return false;
    }
};

template <>
class fgPtrGreater<CDrawable *> {
public:
    inline bool operator ()(CDrawable * left, CDrawable * right) {
        if(left->getDrawableType() == DRAWABLE_DRAWCALL) {
            return !(*(static_cast<CDrawCall *>(left)) < *(static_cast<CDrawCall *>(right)));
        }
        //return !((*left) < (*right));
        return false;
    }
};

template <>
class fgPtrLessEq<CDrawable *> {
public:
    inline bool operator ()(CDrawable * left, CDrawable * right) {
        if(left->getDrawableType() == DRAWABLE_DRAWCALL) {
            return *(static_cast<CDrawCall *>(left)) <= *(static_cast<CDrawCall *>(right));
        }
        //return ((*left) <= (*right));
        return false;
    }
};

template <>
class fgPtrGreaterEq<CDrawable *> {
public:
    inline bool operator ()(CDrawable * left, CDrawable * right) {
        if(left->getDrawableType() == DRAWABLE_DRAWCALL) {
            return !(*(static_cast<CDrawCall *>(left)) <= *(static_cast<CDrawCall *>(right)));
        }
        return false;
        //return !((*left) <= (*right));
    }
};
        #endif /* FG_PTR_COMPARE_DRAWABLE_DEFINED_ */
    #endif

    #undef FG_INC_GFX_DRAW_CALL_BLOCK
#endif /* FG_INC_GFX_DRAW_CALL */
