/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGuiSlider.h
 * Author: vigilant
 *
 * Created on December 12, 2014, 10:12 PM
 */

#ifndef FG_INC_GUI_SLIDER
    #define FG_INC_GUI_SLIDER
    #define FG_INC_GUI_SLIDER_BLOCK

    #include "fgGuiWidget.h"

namespace fg {
    namespace gui {

        /**
         * 
         */
        class CSlider : public CWidget {
        public:
            ///
            typedef CSlider self_type;
            ///
            typedef CSlider type;
            ///
            typedef ::fg::gui::CWidget base_type;

            enum SliderAlign {
                SLIDER_UNDEFINED = 0,
                SLIDER_HORIZONTAL = 1,
                SLIDER_VERTICAL = 2,
                SLIDER_UNIVERSAL = 3
            };

        protected:
            ///
            float m_maxValue;
            ///
            Vec2f m_currentValue;
            /// This is special ratio - it's based on the position of the pointer over slider
            Vec2f m_pointerRatio;
            /// This is ratio of the slider - determines size of the slider
            Vec2f m_ratio;
            ///
            SliderAlign m_sliderAlign;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CSlider();
            /**
             * 
             */
            virtual ~CSlider();

            /**
             * 
             * @param guiLayer
             */
            virtual void preRender(CDrawer *guiLayer);

            /**
             * 
             * @param pointerData
             * @return 
             */
            virtual EventState updateState(const event::SPointerData *pointerData);

        public:
            /**
             * 
             * @param sliderAlign
             */
            void setAlignment(SliderAlign sliderAlign) {
                m_sliderAlign = sliderAlign;
                // alignment
            }
            /**
             * 
             * @return 
             */
            SliderAlign getAlignment(void) const {
                return m_sliderAlign;

            }
            /**
             * 
             * @return 
             */
            Vec2f const & getRatio(void) const {
                return m_ratio;
            }
            /**
             * 
             * @param ratio
             */
            void setRatio(float ratio) {
                if(ratio > 1.0f)
                    ratio = 1.0f;
                if(ratio < 0.15f)
                    ratio = 0.15f;
                if(m_sliderAlign & SLIDER_HORIZONTAL) {
                    m_ratio.x = ratio;
                }
                if(m_sliderAlign & SLIDER_VERTICAL) {
                    m_ratio.y = ratio;
                }

            }
            /**
             * 
             * @param x
             * @param y
             */
            void setRatio(float x, float y) {
                if(x > 1.0f)
                    x = 1.0f;
                if(y > 1.0f)
                    y = 1.0f;
                if(x < 0.15f)
                    x = 0.15f;
                if(y < 0.15f)
                    y = 0.15f;
                m_ratio.x = x;
                m_ratio.y = y;
            }
            /**
             * 
             * @param currentValue
             */
            void setRatio(const Vector2f& ratio) {
                m_ratio = ratio;
                if(m_ratio.x > 1.0f)
                    m_ratio.x = 1.0f;
                if(m_ratio.y > 1.0f)
                    m_ratio.y = 1.0f;
            }
            /**
             * 
             * @return 
             */
            Vec2f const & getCurrentValue(void) const {
                return m_currentValue;
            }
            /**
             * 
             * @param x
             * @param y
             */
            void setCurrentValue(float x, float y) {
                m_currentValue.x = x;
                m_currentValue.y = y;
                m_pointerRatio = m_currentValue / m_maxValue;
            }
            /**
             * 
             * @param currentValue
             */
            void setCurrentValue(const Vector2f& currentValue) {
                m_currentValue = currentValue;
                m_pointerRatio = m_currentValue / m_maxValue;
            }
            /**
             * 
             * @return 
             */
            float getMaxValue(void) const {
                return m_maxValue;
            }
            /**
             * 
             * @param maxValue
             */
            void setMaxValue(float maxValue) {
                m_maxValue = maxValue;
            }

        }; // class CSlider
        FG_ENUM_FLAGS(CSlider::SliderAlign);
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_SLIDER_BLOCK
#endif	/* FG_INC_GUI_SLIDER */
