/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_TEXT_AREA
    #define FG_INC_GUI_TEXT_AREA
    #define FG_INC_GUI_TEXT_AREA_BLOCK

    #include "fgGuiScrollArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #include "fgVector.h"

namespace fg {
    namespace gui {

        /**
         * 
         */
        class CTextArea : public CScrollArea {
        public:
            ///
            typedef CScrollArea base_type;

        protected:
            ///
            fg::CStringVector m_textData;
            ///

            struct TextAreaSize {
                ///
                unsigned short cols; // x
                ///
                unsigned short rows; // y
                /**
                 * 
                 * @param _cols
                 * @param _rows
                 */
                TextAreaSize(unsigned short _cols = 32, unsigned short _rows = 1) :
                cols(_cols), rows(_rows) { }
            } m_textAreaSize;



        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CTextArea();
            /**
             * 
             */
            virtual ~CTextArea();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CTextArea)

            /**
             * 
             * @param guiLayer
             */
            virtual void display(CDrawer *guiLayer);

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);

        public:
            /**
             * 
             * @param text
             */
            virtual void pushText(const char *text) {
                m_textData.push_back(std::string(text));
            }
            /**
             * 
             * @param text
             */
            virtual void pushText(const std::string &text) {
                m_textData.push_back(text);
            }
            /**
             * 
             * @param text
             */
            virtual void setText(const std::string &text) {
                m_text.clear();
                m_textData.clear_optimised();
                m_textData.resize(0);
                m_textData.push_back(text);
            }
            /**
             * 
             * @param text
             */
            virtual void setText(const char *text) {
                if(text) {
                    m_textData.clear_optimised();
                    m_textData.resize(0);
                    m_textData.push_back(std::string(text));
                }
                m_text.clear();
            }
            /**
             * 
             */
            virtual void clearText(void) {
                m_text.clear();
                m_textData.clear_optimised();
                m_textData.resize(0);
            }

        };
    };
};

    #undef FG_INC_GUI_TEXT_AREA_BLOCK
#endif /* FG_INC_GUI_TEXT_AREA */
