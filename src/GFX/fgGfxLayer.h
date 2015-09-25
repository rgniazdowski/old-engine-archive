/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_LAYER
    #define FG_INC_GFX_LAYER
    #define FG_INC_GFX_LAYER_BLOCK

    #include "GFX/fgGfxMVPMatrix.h"

namespace fg {

    namespace gfx {

        class CDrawingBatch;
        class CSceneManager;
        class CGfxMain;

        /**
         *
         */
        class CLayer {
            friend class CGfxMain;
            friend class CSceneManager;
            friend class CDrawingBatch;
            
        public:
            typedef CLayer self_type;
            typedef CLayer type;

        public:
            /**
             * 
             */
            CLayer() : m_zIndex(0) { }
            /**
             * 
             */
            virtual ~CLayer() { }
            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            virtual int getZIndex(void) const {
                return m_zIndex;
            }
            /**
             * 
             * @param zIndex
             */
            virtual void setZIndex(const int zIndex) {
                m_zIndex = zIndex;
            }
            /**
             * 
             */
            virtual void upZIndex(void) {
                m_zIndex++;
            }
            /**
             * 
             */
            virtual void downZIndex(void) {
                m_zIndex--;
            }
            /**
             *
             * @return
             */
            inline CMVPMatrix* getMVP(void) {
                return &m_MVP;
            }
            //------------------------------------------------------------------

            /**
             * 
             */
            virtual void flush(void) = 0;

            /**
             * 
             */
            virtual void sortCalls(void) = 0;

            /**
             * 
             */
            virtual void render(void) = 0;

        public:
            int getLayerID(void) const {
                return m_id;
            }
            std::string& getLayerName(void) {
                return m_layerName;
            }
            std::string const& getLayerName(void) const {
                return m_layerName;
            }


        public:
            inline bool operator ==(const self_type& a) {
                return (this->m_id == a.m_id && this->m_layerName.compare(a.m_layerName) == 0);
            }
            inline bool operator !=(const self_type& a) {
                return (this->m_id != a.m_id);
            }
            inline bool operator <(const self_type& a) {
                return (this->m_id < a.m_id);
            }
            inline bool operator <=(const self_type& a) {
                return (this->m_id <= a.m_id);
            }
            inline bool operator >(const self_type& a) {
                return (this->m_id > a.m_id);
            }
            inline bool operator >=(const self_type& a) {
                return (this->m_id >= a.m_id);
            }

        protected:
            void setLayerID(int id) {
                m_id = id;
            }
            void setLayerName(const std::string& name) {
                m_layerName.clear();
                m_layerName.reserve(name.length() + 1);
                m_layerName.append(name);
            }
            void setLayerName(const char* name) {
                if(name) {
                    m_layerName.clear();
                    m_layerName.reserve(strlen(name) + 1);
                    m_layerName.append(name);
                }
            }

        protected:
            ///
            int m_zIndex;
            /// Internal MVP matrix to use
            CMVPMatrix m_MVP;

        private:
            ///
            int m_id;
            ///
            std::string m_layerName;
        }; // class CLayer

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_LAYER_BLOCK
#endif /* FG_INC_GFX_LAYER */
