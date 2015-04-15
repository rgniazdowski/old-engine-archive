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

namespace fg {

    namespace gfx {

        /**
         *
         */
        class CLayer {
        public:
            /**
             * 
             */
            CLayer() : m_zIndex(0) { }
            /**
             * 
             */
            virtual ~CLayer() { }
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

        protected:
            ///
            int m_zIndex;
        };
    };
};

    #undef FG_INC_GFX_LAYER_BLOCK
#endif /* FG_INC_GFX_LAYER */
