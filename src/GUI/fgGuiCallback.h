/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_CALLBACK
    #define FG_INC_GUI_CALLBACK
    #define FG_INC_GUI_CALLBACK_BLOCK

    #include "Event/fgCallback.h"

namespace fg {
    namespace gui {
        class CWidget;
        class CGuiMain;
    };
};


typedef fgBool(*fgGuiWidgetEventHandlerFunc) (fg::gui::CGuiMain *guiMain, fg::gui::CWidget *widget);

namespace fg {
    namespace gui {

        /**
         *
         */
        class CGuiCallback : public virtual fg::event::CFunctionCallback {
        public:
            ///
            typedef fg::event::CFunctionCallback base_type;

        public:
            /**
             * 
             * @param pGuiMain
             */
            CGuiCallback(CGuiMain *pGuiMain = NULL) {
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
                m_pGuiMain = pGuiMain;
            }
            /**
             * 
             */
            virtual ~CGuiCallback() {
                m_pGuiMain = NULL;
            }

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CWidget *pWidget) = 0;

            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CGuiMain *pGuiMain, CWidget *pWidget) = 0;
            /**
             * 
             * @param pGuiMain
             */
            void setGuiMain(CGuiMain *pGuiMain) {
                m_pGuiMain = pGuiMain;
            }
            /**
             * 
             * @return 
             */
            CGuiMain *getGuiMain(void) const {
                return m_pGuiMain;
            }

        protected:
            ///
            CGuiMain *m_pGuiMain;
        };

        /**
         *
         */
        template < class TClass >
        class CGuiMethodCallback : public CGuiCallback {
        public:
            ///
            typedef CGuiCallback base_type;
            ///
            typedef fgBool(TClass::*fgGuiMethod)(CGuiMain *guiMain, CWidget *widget);
            ///
            typedef fgGuiMethod callback_type;
            /**
             * 
             * @param pClassInstance
             * @param pMethod
             */
            CGuiMethodCallback(TClass* pClassInstance, fgGuiMethod pMethod) :
            CGuiCallback(NULL) {
                m_pClassInstance = pClassInstance;
                m_guiMethod = pMethod;
            }
            /**
             * 
             * @param pClassInstance
             * @param pGuiMain
             * @param pMethod
             */
            CGuiMethodCallback(TClass* pClassInstance, CGuiMain *pGuiMain, fgGuiMethod pMethod) :
            CGuiCallback(pGuiMain) {
                m_pClassInstance = pClassInstance;
                m_guiMethod = pMethod;
            }
            /**
             * 
             */
            virtual ~CGuiMethodCallback() {
                m_pClassInstance = NULL;
                m_guiMethod = NULL;
            }
            /**
             * 
             * @param pClassInstance
             */
            void setClassInstance(TClass* pClassInstance) {
                if(pClassInstance)
                    m_pClassInstance = pClassInstance;
            }
            /**
             * 
             * @param method
             */
            void setGuiMethod(fgGuiMethod method) {
                m_pClassInstance = NULL;
                m_guiMethod = method;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_guiMethod != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_guiMethod)(NULL, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList* argv) {
                if(m_guiMethod != NULL && m_pClassInstance != NULL) {
                    // If argument list is given then maybe should check for existence
                    // of STRUCT parameters ?
                    //return (m_classInstance->*m_guiMethod)(argv);
                    return FG_FALSE;
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CWidget *pWidget) {
                if(m_guiMethod != NULL && m_pClassInstance != NULL && m_pGuiMain != NULL)
                    return (m_pClassInstance->*m_guiMethod)(m_pGuiMain, pWidget);
                return FG_FALSE;
            }
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CGuiMain *pGuiMain, CWidget *pWidget) {
                if(m_guiMethod != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_guiMethod)(pGuiMain, pWidget);
                return FG_FALSE;
            }
            /**
             * 
             * @param pClassInstance
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            fgBool Call(TClass *pClassInstance, CGuiMain *pGuiMain = NULL, CWidget *pWidget = NULL) {
                if(m_guiMethod != NULL && pClassInstance != NULL)
                    return (pClassInstance->*m_guiMethod)(pGuiMain, pWidget);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline fgGuiMethod& getGuiMethod(void) {
                return m_guiMethod;
            }
            /**
             * 
             * @return 
             */
            inline fgGuiMethod const& getGuiMethod(void) const {
                return m_guiMethod;
            }

        private:
            /// 
            TClass* m_pClassInstance;
            ///
            fgGuiMethod m_guiMethod;
        };

        /**
         * GuiFunctionCallback is similar to fgPlainFunctionCallback
         * here you have (fgGuiMain *guiMain, fgGuiWidget *widget)
         * in plain function: (void *systemData, void *userData)
         * However the system data is *widget... and userData: guiMain
         * So the usage is almost interchangeable - however not recommended
         */
        class CGuiFunctionCallback : public CGuiCallback {
        public:
            ///
            typedef CGuiCallback base_type;
            ///
            typedef fgBool(*fgGuiFunction)(CGuiMain *guiMain, CWidget *widget);
            ///
            typedef fgGuiFunction callback_type;
            /**
             * 
             * @param function
             */
            CGuiFunctionCallback(fgGuiFunction pFunction) :
            CGuiCallback(NULL) {
                m_guiFunction = pFunction;
            }
            /**
             * 
             * @param guiMain
             * @param function
             */
            CGuiFunctionCallback(CGuiMain *pGuiMain, fgGuiFunction pFunction) :
            CGuiCallback(pGuiMain) {
                m_guiFunction = pFunction;
            }
            /**
             * 
             */
            virtual ~CGuiFunctionCallback() {
                m_guiFunction = NULL;
            }
            /**
             * 
             * @param function
             */
            void setGuiFunction(fgGuiFunction pFunction) {
                m_guiFunction = pFunction;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_guiFunction != NULL)
                    return m_guiFunction(m_pGuiMain, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void *pSystemData) {
                // This is for compatibility - fgFunctionCallback provides the
                // *(void *pSystemData) Call() function version however it is 
                // empty
                if(m_guiFunction != NULL) {
                    if(!pSystemData) {
                        return m_guiFunction(m_pGuiMain, NULL);
                    } else {
                        CWidget *pWidget = (CWidget *)pSystemData;
                        //if(pWidget->isManaged())
                        return m_guiFunction(m_pGuiMain, pWidget);
                    }

                }
                return FG_FALSE;
            }
            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CWidget *pWidget) {
                if(m_guiFunction != NULL)
                    return m_guiFunction(m_pGuiMain, pWidget);
                return FG_FALSE;
            }
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CGuiMain *pGuiMain, CWidget *pWidget) {
                if(m_guiFunction != NULL)
                    return m_guiFunction(pGuiMain, pWidget);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline fgGuiFunction& getGuiFunction(void) {
                return m_guiFunction;
            }
            /**
             * 
             * @return 
             */
            inline fgGuiFunction const& getGuiFunction(void) const {
                return m_guiFunction;
            }

        private:
            ///
            fgGuiFunction m_guiFunction;
        };
    };
};

    #undef FG_INC_GUI_CALLBACK_BLOCK
#endif /* FG_INC_GUI_CALLBACK */
