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

    #include "fgGfxPrimitives.h"
    #include "GFX/Shaders/fgGfxShaderDefs.h"
    #include "fgGfxTypes.h"
    #include "fgGfxMVPMatrix.h"    

    #include "Util/fgFastCmp.h"
    #include "Textures/fgTextureTypes.h"

namespace fg {
    namespace gfx {
        /// Default Z index - center/zero
        const unsigned int Z_INDEX_DEFAULT = 127;
        /// Minimal Z index
        const unsigned int Z_INDEX_MIN = 0;
        /// Maximal Z index
        const unsigned int Z_INDEX_MAX = 255;
        /// Default Z index for particles
        const unsigned int Z_INDEX_PARTICLES = 100;
        /// Default Z index for 3D objects
        const unsigned int Z_INDEX_OBJECTS_3D = 120;

        /**
         * Draw call append mode
         */
        enum DrawAppendMode {
            ///
            DRAW_APPEND_ABSOLUTE,
            ///
            DRAW_APPEND_RELATIVE
        }; // enum DrawAppendMode

        enum DrawCallType {
            DRAW_CALL_INVALID = 0,
            DRAW_CALL_VERTEX_BUFFER = 1,
            DRAW_CALL_INTERNAL_ARRAY = 2,
            DRAW_CALL_EXTERNAL_ARRAY = 3,
            DRAW_CALL_MESH = 4
        }; // enum DrawCallType

        class CDrawingBatch;
        struct SMaterial;
        struct SShape;
        struct SMeshBase;
        struct SMeshSoA;
        struct SMeshAoS;
        class CShaderProgram;
        class CTextureResource;

        /**
         * Special class representing a single draw call
         */
        class CDrawCall {
            friend class ::fg::gfx::CDrawingBatch;

        public:
            typedef CDrawCall self_type;
            typedef CDrawCall type;

        public:
            static const unsigned char CMP_SLOT_ATTRIB_MASK = 0;
            static const unsigned char CMP_SLOT_TEXTURE = 1;
            static const unsigned char CMP_SLOT_SHADER_PROGRAM = 2;
            static const unsigned char CMP_SLOT_Z_INDEX = 3;

            typedef CVector<STextureID> TextureSlotsVec;
            typedef TextureSlotsVec::iterator TextureSlotsVecItor;
            typedef TextureSlotsVec::const_iterator TextureSlotsVecConstItor;

        protected:
            /**
             *
             * @param toggle
             */
            void setManaged(const fgBool toggle = FG_TRUE);
            /**
             * 
             */
            void resetAttributeData(void);

        public:
            /**
             * Default constructor
             * @param type
             * @param attribMask
             */
            CDrawCall(const DrawCallType type = DRAW_CALL_INTERNAL_ARRAY,
                      const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_TEXTURE_COORD_BIT);
            /**
             * Default destructor for the draw call object
             */
            virtual ~CDrawCall();

            /**
             *
             * @param pVertexData
             */
            void setupFromVertexData(const CVertexData* pVertexData);

            /**
             * 
             * @param pVertexData
             */
            void refreshDrawingInfo(const CVertexData* pVertexData);

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

            //------------------------------------------------------------------

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
            DrawCallType getDrawCallType(void) const;
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

            //------------------------------------------------------------------

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
            void setDrawCallType(const DrawCallType type);
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
            void setComponentActive(AttributeMask component, const fgBool reset = FG_FALSE);

            //------------------------------------------------------------------

            /**
             * Set active color for the next data
             * @param color
             */
            virtual void setColor(const Color3f & color);
            /**
             * Set active color for the next data
             * @param color
             */
            virtual void setColor(const Color4f & color);
            /**
             * This will reset used color
             */
            virtual void resetColor(void);

            //------------------------------------------------------------------

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
            void setShaderProgram(CShaderProgram* pProgram = NULL);
            /**
             * Returns the currently used shader program for this draw call
             * @return 
             */
            CShaderProgram* getShaderProgram(void) const;

            //------------------------------------------------------------------

            /**
             * Sets the texture pointer
             * @param textureID
             */
            void setTexture(const STextureID& textureID,
                            const unsigned int slot = (unsigned int)texture::UNIT_DEFAULT);
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID const& getTexture(const unsigned int slot = (unsigned int)texture::UNIT_DEFAULT) const;
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID& getTexture(const unsigned int slot = (unsigned int)texture::UNIT_DEFAULT);

            //------------------------------------------------------------------

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

            //------------------------------------------------------------------
            void draw(void) {
                this->draw(Matrix4f());
            }
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat);
            //------------------------------------------------------------------
            /**
             *
             * @param drawCall
             * @return
             */
            inline int operator ==(const CDrawCall& drawCall) const {
                return util::CFastCmp::equal32(this->m_fastCmp, drawCall.m_fastCmp);
            }
            /**
             * 
             * @param drawCall
             * @return
             */
            inline int operator !=(const CDrawCall& drawCall) const {
                return !util::CFastCmp::equal32(this->m_fastCmp, drawCall.m_fastCmp);
            }
            /**
             *
             * @param drawCall
             * @return
             */
            inline bool operator <(const CDrawCall& drawCall) const {
                return util::CFastCmp::less32(this->m_fastCmp, drawCall.m_fastCmp);
            }
            /**
             *
             * @param drawCall
             * @return
             */
            inline bool operator >(const CDrawCall& drawCall) const {
                return util::CFastCmp::greater32(this->m_fastCmp, drawCall.m_fastCmp);
            }
            /**
             *
             * @param drawCall
             * @return
             */
            inline bool operator <=(const CDrawCall& drawCall) const {
                return util::CFastCmp::less_eq32(this->m_fastCmp, drawCall.m_fastCmp);
            }
            /**
             *
             * @param drawCall
             * @return
             */
            inline bool operator >=(const CDrawCall& drawCall) const {
                return util::CFastCmp::greater_eq32(this->m_fastCmp, drawCall.m_fastCmp);
            }

        private:
            /**
             *
             * @param attribMask
             */
            void setupVertexData(AttributeMask attribMask);

        private:
            /// Attribute binding data #FIXME
            SAttributeData m_attrData[NUM_ATTRIBUTE_TYPES];
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
            CShaderProgram *m_pProgram;
            /// Pointer to the used texture - this will require also pointer
            /// to the shader program (so the proper uniform sampler variable
            /// can be updated). However this is not always required.
            /// If there is no multitexturing then there's always one
            /// texture active (TEXTURE0).
            TextureSlotsVec m_textureIDs;
            ///
            CVector<unsigned char> m_textureSlots;
            /// Pointer to external MVP matrix to use
            /// this will need to be updated for every drawcall made
            /// because the model matrix would change
            /// view and projection matrix parameters stay the same (mostly)
            /// through all drawing batch
            CMVPMatrix *m_pMVP;
            /// Pointer to external material struct - can be NULL
            SMaterial *m_pMaterial;
            /// Used vertex data will depend on the attribute mask used
            /// Appending specific data however may alter this and make
            /// other buffers invalid
            AttributeMask m_attribMask;
            /// What kind of draw call is this?
            DrawCallType m_drawCallType;
            /// Append mode
            DrawAppendMode m_drawAppendMode;
            /// Primitive mode used for drawing the vertex buffer
            /// It defaults to FG_GFX_TRIANGLES, however the most
            /// optimal is the Triangle Strip - this requires however
            /// modification of the vertex data after loading
            PrimitiveMode m_primMode;
            /// Current color used
            Color4f m_color;
            /// Holds the value for the relative move
            Vector3f m_relMove;
            /// Scissor box for current draw call
            Vector4i m_scissorBox;
            ///
            util::CFastCmp m_fastCmp;
            /// Holds value for special Z index used for more direct sorting
            int m_zIndex;
            /// Is this draw call managed by the drawing batch?
            /// Or any other mechanism? If true then when on drawing batch flush
            /// this draw call will be destroyed. If false no destructor will be called.
            /// Use with caution, if set to false wrongfully it may cause overallocation
            /// and memory leaks.
            fgBool m_isManaged;
        }; // class CDrawCall

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_DRAW_CALL_BLOCK
#endif /* FG_INC_GFX_DRAW_CALL */
