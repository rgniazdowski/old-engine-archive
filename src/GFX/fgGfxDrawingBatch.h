/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_DRAWING_BATCH
    #define FG_INC_GFX_DRAWING_BATCH
    #define FG_INC_GFX_DRAWING_BATCH_BLOCK

    #include "fgGfxDrawCall.h"
    #include "fgGfxLayer.h"

    #include "fgQueue.h"

    #define FG_GFX_DRAWING_BATCH_DEFAULT_RESERVE 64

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CDrawingBatch : public CLayer {
        public:
            ///
            typedef CLayer base_type;
            ///
            typedef CDrawingBatch self_type;
            ///
            typedef CDrawingBatch type;

        protected:
            ///
            typedef CPriorityQueue<CDrawCall*, std::deque<CDrawCall*>, fgPtrLessEq<CDrawCall*> > BatchPriorityQueue;
            ///
            typedef CVector<CDrawCall*> DrawCallVec;
            ///
            typedef DrawCallVec::iterator DrawCallVecItor;
            ///
            typedef CVector<unsigned int> FreeSlotsVec;
            ///
            typedef FreeSlotsVec::iterator FreeSlotsVecItor;

        private:
            ///
            BatchPriorityQueue m_priorityBatch;
            ///
            DrawCallVec m_drawCalls;
            ///
            DrawCallVec m_duplicates;
            ///
            FreeSlotsVec m_freeSlots;
            ///
            unsigned int m_numDrawCalls;
            ///
            unsigned int m_reservedSize;
            ///
            unsigned int m_numNotManaged;
            ///
            DrawCallType m_defaultDrawCallType;
            ///
            AttributeMask m_defaultAttribMask;
            ///
            Vector4i m_scissorBox;

        protected:
            /// Relative move
            Vector3f m_relMove;            
            /// Pointer to external Shader Manager
            fg::base::CManager* m_pShaderMgr;
            ///
            CShaderProgram* m_pDefaultShader;

        protected:
            /**
             * 
             * @return 
             */
            inline BatchPriorityQueue& getPriorityQueue(void) {
                return m_priorityBatch;
            }
            /**
             *
             * @return
             */
            inline BatchPriorityQueue const& getPriorityQueue(void) const {
                return m_priorityBatch;
            }
            /**
             * 
             * @return 
             */
            inline DrawCallVec& getDrawCalls(void) {
                return m_drawCalls;
            }
            /**
             *
             * @return
             */
            inline DrawCallVec const& getDrawCalls(void) const {
                return m_drawCalls;
            }
            /**
             * 
             * @param maximum
             * @return 
             */
            int getFreeSlot(int maximum);

        public:
            /**
             * 
             * @param reservedSize
             * @param drawCallType
             * @param attribMask
             */
            CDrawingBatch(const unsigned int reservedSize = FG_GFX_DRAWING_BATCH_DEFAULT_RESERVE,
                          const DrawCallType drawCallType = DRAW_CALL_INTERNAL_ARRAY,
                          const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT);
            /**
             * 
             */
            virtual ~CDrawingBatch();
            
            /**
             * 
             * @return 
             */
            inline fg::base::CManager* getShaderManager(void) const {
                return m_pShaderMgr;
            }
            /**
             *
             * @return
             */
            inline CShaderProgram* getDefaultShader(void) const {
                return m_pDefaultShader;
            }

            /**
             * 
             * @param pShaderMgr
             */
            virtual void setShaderManager(fg::base::CManager* pShaderMgr);

            /**
             *
             * @param pDefaultShader
             */
            void setDefaultShader(CShaderProgram* pDefaultShader);
            /**
             *
             * @param nameTag
             */
            void setDefaultShader(const char* nameTag);
            /**
             * 
             * @param nameTag
             */
            void setDefaultShader(const std::string& nameTag);

            /**
             * 
             * @param index
             * @return 
             */
            CDrawCall* requestDrawCall(int& index,
                                       const DrawCallType type = DRAW_CALL_INTERNAL_ARRAY,
                                       const AttributeMask attribMask = ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT,
                                       CShaderProgram* pProgram = NULL);
            /**
             * 
             * @param index
             * @return 
             */
            CDrawCall* getDrawCall(int index);
            /**
             * 
             * @return 
             */
            CDrawCall* getLastDrawCall(void);
            // Appends the specified draw call to the drawing batch
            // The check flag is used for duplicates
            int appendDrawCall(CDrawCall* drawCall,
                               fgBool manage = FG_TRUE,
                               fgBool check = FG_TRUE);
            /**
             * Removes the given draw call from the drawing batch
             * @param index Specifies the index of a draw call to remove
             * @return      Returns the pointer of the removed draw call or NULL 
             *              if index was out of bounds (or the batch is empty)
             */
            CDrawCall* removeDrawCall(int index);
            /**
             * Remove given draw call from batch
             * @param drawCall
             * @return 
             */
            fgBool removeDrawCall(CDrawCall* drawCall);
            /**
             * Delete selected draw call
             * @param index
             * @return 
             */
            fgBool deleteDrawCall(int index);
            /**
             * Delete given draw call (will also remove from batch)
             * @param drawCall
             * @return 
             */
            fgBool deleteDrawCall(CDrawCall*& drawCall);
            /**
             * Get current number of active DrawCalls in the batch.
             * @return  Number of active DrawCalls.
             */
            unsigned int count(void) const {
                return m_numDrawCalls;
            }
            /**
             * Get current number of active DrawCalls in the batch.
             * @return  Number of active DrawCalls.
             */
            unsigned int size(void) const {
                return m_numDrawCalls;
            }
            /**
             * Get current capacity of Drawing batch.
             * @return  Maximum number of supported DrawCalls.
             */
            unsigned int capacity(void) const {
                return m_reservedSize;
            }
            /**
             * 
             * @param reservedSize
             * @param force
             */
            void reserve(unsigned int reservedSize, fgBool force = FG_FALSE);
            /**
             * 
             * @return 
             */
            fgBool empty(void) const {
                return (fgBool)(m_numDrawCalls == 0);
            }
            //------------------------------------------------------------------
            /**
             * 
             */
            virtual void flush(void);
            /**
             * 
             */
            virtual void sortCalls(void);
            /**
             * 
             */
            virtual void render(void);
            //------------------------------------------------------------------
            /**
             * 
             * @param n
             * @return 
             */
            CDrawCall* operator [](size_t n) {
                return m_drawCalls[n];
            }
            /**
             * 
             * @param n
             * @return 
             */
            const CDrawCall* operator [](size_t n) const {
                return m_drawCalls[n];
            }
            /**
             * 
             * @return 
             */
            Vector3f const& getRelMove(void) const {
                return m_relMove;
            }
            /**
             * 
             * @param relMove
             */
            void setRelMove(const Vector3f& relMove) {
                m_relMove = relMove;
            }
            /**
             * 
             * @param relMove
             */
            void setRelMove(const Vector2f& relMove) {
                m_relMove.x = relMove.x;
                m_relMove.y = relMove.y;
                m_relMove.z = 0.0f;
            }
            /**
             * 
             * @return 
             */
            Vector4i const& getScissorBox(void) const {
                return m_scissorBox;
            }
            /**
             * 
             * @return 
             */
            inline Vector2i const& getScreenSize(void) const {
                return context::getScreenSize();
            }
            /**
             * 
             * @param x
             * @param y
             * @param width
             * @param height
             */
            void setScissorBox(const fgGFXint x,
                               const fgGFXint y,
                               const fgGFXint width,
                               const fgGFXint height) {
                m_scissorBox.x = x;
                m_scissorBox.y = y;
                m_scissorBox.z = width;
                m_scissorBox.w = height;
            }
            /**
             * 
             * @param pos
             * @param size
             */
            void setScissorBox(const Vector2i& pos,
                               const Vector2i& size) {
                m_scissorBox.x = pos.x;
                m_scissorBox.y = pos.y;
                m_scissorBox.z = size.x;
                m_scissorBox.w = size.y;
            }
            /**
             * 
             * @param dimensions
             */
            void setScissorBox(const Vector4i& dimensions) {
                m_scissorBox = dimensions;
            }

        }; // class CDrawingBatch
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_DRAWING_BATCH_BLOCK
#endif /* FG_INC_GFX_DRAWING_BATCH */
