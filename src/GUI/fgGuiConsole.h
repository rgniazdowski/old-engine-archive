/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_CONSOLE
    #define FG_INC_GUI_CONSOLE
    #define FG_INC_GUI_CONSOLE_BLOCK

    #include "fgGuiTextArea.h"

namespace fg {
    namespace msg {
        struct SStatus;
    };
};

namespace fg {
    namespace gui {

        /**
         *
         */
        class CConsole : public CTextArea {
        public:
            ///
            typedef CConsole self_type;
            ///
            typedef CConsole type;
            ///
            typedef CTextArea base_type;

        protected:
            ///
            unsigned int m_numConsoleRecords;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CConsole();
            /**
             * 
             */
            virtual ~CConsole();

            /**
             * 
             * @param guiLayer
             */
            virtual void preRender(CDrawer *guiLayer);

            using gui::CWidget::updateBounds;

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
             * @return 
             */
            unsigned int getNumConsoleRecords(void) const {
                return m_numConsoleRecords;
            }
            /**
             * 
             * @param statusVec
             */
            void updateFromStatusVec(const CVector<msg::SStatus *> &statusVec);

        public:
            /**
             * 
             * @param text
             */
            virtual void pushText(const char *text) {
                base_type::pushText(text);
                m_numConsoleRecords = m_textData.size();
            }
            /**
             * 
             * @param text
             */
            virtual void pushText(const std::string &text) {
                base_type::pushText(text);
                m_numConsoleRecords = m_textData.size();
            }
            /**
             * 
             * @param text
             */
            virtual void setText(const std::string &text) {
                base_type::setText(text);
                m_numConsoleRecords = m_textData.size();
            }
            /**
             * 
             * @param text
             */
            virtual void setText(const char *text) {
                base_type::setText(text);
                m_numConsoleRecords = m_textData.size();
            }
            /**
             * 
             */
            virtual void clearText(void) {
                base_type::clearText();
                m_numConsoleRecords = m_textData.size();
            }
        }; // class CConsole
        
    } // namespace gui
} // namespace fg

    #undef FG_INC_GUI_CONSOLE_BLOCK
#endif /* FG_INC_GUI_CONSOLE */
