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
 * File:   CPreviewModeBase.h
 * Author: vigilant
 *
 * Created on May 14, 2015, 2:07 AM
 */

#ifndef FG_INC_PREVIEW_MODE_BASE
    #define FG_INC_PREVIEW_MODE_BASE
    #define FG_INC_PREVIEW_MODE_BASE_BLOCK

    #include "fgBool.h"

    #include <wx/string.h>
    #include <wx/menu.h>
    #include <wx/panel.h>

namespace fg {
    class CEngineMain;
}

namespace fg {
    namespace editor {

        /**
         *
         */
        class CPreviewModeBase {
        public:
            typedef CPreviewModeBase self_type;
            typedef CPreviewModeBase type;

        public:
            /**
             *
             * @param engineMainOrig
             */
            CPreviewModeBase(fg::CEngineMain** pEngineMainOrig) :
            m_name(),
            m_previewID(0),
            m_isActive(FG_FALSE),
            m_callbacksRegistered(FG_FALSE),
            m_leftPanel(NULL),
            m_bottomPanel(NULL),
            m_engineMainOrig(pEngineMainOrig) { }
            /**
             *
             */
            virtual ~CPreviewModeBase() { }

            /**
             *
             * @param toggle
             * @return
             */
            virtual fgBool activate(fgBool toggle = FG_FALSE) = 0;
            /**
             *
             * @return
             */
            virtual void refreshInternals(void) = 0;
            /**
             *
             * @return
             */
            virtual fgBool registerCallbacks(void) = 0;
            /**
             *
             * @return
             */
            virtual fgBool unregisterCallbacks(void) = 0;
            /**
             *
             * @return
             */
            fg::CEngineMain* getEngineMain(void) const {
                if(m_engineMainOrig) {
                    return *m_engineMainOrig;
                }
                return NULL;
            }
            /**
             * 
             * @param name
             */
            void setName(const wxString& name) {
                m_name = name;
            }
            /**
             * 
             * @param name
             */
            void setName(const char* name) {
                if(!name)
                    return;
                m_name.clear();
                m_name.append(name);
            }
            /**
             *
             * @return
             */
            wxString& getName(void) {
                return m_name;
            }
            /**
             *
             * @return
             */
            wxString const& getName(void) const {
                return m_name;
            }
            /**
             *
             * @return
             */
            const char* getNameStr(void) const {
                return m_name.c_str().AsChar();
            }
            /**
             *
             * @return
             */
            unsigned int getPreviewID(void) const {
                return m_previewID;
            }
            /**
             *
             * @return
             */
            fgBool isActive(void) const {
                return m_isActive;
            }
            /**
             *
             * @return
             */
            fgBool areCallbacksRegistered(void) const {
                return m_callbacksRegistered;
            }
            /**
             * 
             * @return
             */
            wxMenu* getContextMenu(void) {
                return &m_contextMenu;
            }
            /**
             * 
             * @return
             */
            wxEvtHandler* getEventHandler(void) {
                return (wxEvtHandler*)&m_contextMenu;
            }
            /**
             * 
             * @return
             */
            wxPanel* getLeftPanel(void) const {
                return m_leftPanel;
            }
            /**
             *
             * @return
             */
            wxPanel* getBottomPanel(void) const {
                return m_bottomPanel;
            }

        protected:
            /// Context menu - internal
            wxMenu m_contextMenu;
            /// Name of this preview mode
            wxString m_name;
            /// This preview mode identification number.
            /// It should correspond to main enumeration type (cast as unsigned int)
            unsigned int m_previewID;
            /// Is this preview mode currently activated? Only one preview mode
            /// can be activated at the given time.
            fgBool m_isActive;
            ///
            fgBool m_callbacksRegistered;
            ///
            wxPanel* m_leftPanel;
            ///
            wxPanel* m_bottomPanel;
            /// Pointer to pointer for the main engine instance. Double pointer is used
            /// so the pointer change is seen in every dependent Editor object.
            fg::CEngineMain** m_engineMainOrig;
        };
    } // namespace editor
} // namespace fg

    #undef FG_INC_PREVIEW_MODE_BASE_BLOCK
#endif	/* FG_INC_PREVIEW_MODE_BASE */
