/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_CALLBACK
    #define FG_INC_CALLBACK
    #define FG_INC_CALLBACK_BLOCK

    #include "fgTypes.h"
    #include "fgArgumentList.h"

namespace fg {
    namespace event {

        typedef unsigned int CallbackType;

        const CallbackType INVALID_CALLBACK = 0;
        const CallbackType FUNCTION_CALLBACK = 1;
        const CallbackType PLAIN_FUNCTION_CALLBACK = 2;
        const CallbackType METHOD_CALLBACK = 3;

        /**
         *
         */
        class CFunctionCallback {
        public:
            /// This is function pointer (to global or static member function)
            typedef fgBool(*Function)(CArgumentList *argv);
            ///
            typedef Function callback_type;

        public:
            /**
             * 
             */
            CFunctionCallback() : m_function(NULL) { }
            /**
             * 
             * @param function
             */
            CFunctionCallback(Function function) {
                m_function = function;
            }
            /**
             * 
             */
            virtual ~CFunctionCallback() {
                m_function = NULL;
            }
            /**
             * 
             * @param function
             */
            void setFunction(Function function) {
                m_function = function;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_function != NULL)
                    return m_function(NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(CArgumentList *argv) {
                if(m_function != NULL)
                    return m_function(argv);
                return FG_FALSE;
            }
            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void *pSystemData) {
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline Function& getFunction(void) {
                return m_function;
            }
            /**
             * 
             * @return 
             */
            inline Function const& getFunction(void) const {
                return m_function;
            }
            /**
             *
             */
            inline CallbackType getCallbackType(void) const {
                return m_callbackType;
            }

        protected:
            ///
            CallbackType m_callbackType;

        private:
            ///
            Function m_function;
        };

        /**
         *
         */
        class CPlainFunctionCallback : public virtual CFunctionCallback {
        public:
            ///
            typedef CFunctionCallback base_type;
            ///
            typedef CPlainFunctionCallback self_type;
            ///
            typedef CPlainFunctionCallback type;

            /// This is function pointer (to global or static member function)
            typedef fgBool(*PlainFunction)(void *systemData, void *userData);
            ///
            typedef PlainFunction callback_type;

        public:
            /**
             * 
             */
            CPlainFunctionCallback() :
            CFunctionCallback(),
            m_plainFunction(NULL),
            m_pUserData(NULL) {
                m_callbackType = PLAIN_FUNCTION_CALLBACK;
                // just to make sure that fgFunctionCallback::m_function is NULL
                // this is because of virtual inheritance
                CFunctionCallback::setFunction((CFunctionCallback::Function)NULL);
            }
            /**
             * 
             * @param function
             */
            CPlainFunctionCallback(PlainFunction pPlainFunction, void *pUserData = NULL) {
                m_plainFunction = pPlainFunction;
                m_pUserData = pUserData;
                m_callbackType = PLAIN_FUNCTION_CALLBACK;
                CFunctionCallback::setFunction((CFunctionCallback::Function)NULL);

            }
            /**
             * 
             */
            virtual ~CPlainFunctionCallback() {
                m_plainFunction = NULL;
                m_pUserData = NULL;
                m_callbackType = INVALID_CALLBACK;
            }
            /**
             * 
             * @param function
             */
            void setFunction(PlainFunction pPlainFunction) {
                m_plainFunction = pPlainFunction;
            }
            /**
             * 
             * @param pUserData
             */
            void setUserData(void *pUserData) {
                m_pUserData = pUserData;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_plainFunction != NULL)
                    return m_plainFunction(NULL, m_pUserData);
                else
                    return CFunctionCallback::Call();
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(CArgumentList *pArgv) {
                // #FIXME - this is for compatibility with other functions
                if(m_plainFunction != NULL)
                    return m_plainFunction((void *)pArgv, m_pUserData);
                else
                    return CFunctionCallback::Call(pArgv);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(void *pSystemData) {
                if(m_plainFunction != NULL)
                    return m_plainFunction(pSystemData, m_pUserData);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline PlainFunction& getPlainFunction(void) {
                return m_plainFunction;
            }
            /**
             * 
             * @return 
             */
            inline PlainFunction const& getPlainFunction(void) const {
                return m_plainFunction;
            }
        private:
            ///
            PlainFunction m_plainFunction;
            ///
            void *m_pUserData;
        };

        /**
         *
         */
        template < class TClass >
        class CMethodCallback : public virtual CFunctionCallback {
        public:
            ///
            typedef CFunctionCallback base_type;
            ///
            typedef CMethodCallback self_type;
            ///
            typedef CMethodCallback type;
            ///
            typedef fgBool(TClass::*ClassMethod)(CArgumentList *argv);
            ///
            typedef ClassMethod callback_type;

        public:
            /**
             * 
             * @param class_instance
             * @param method
             */
            CMethodCallback(TClass* pClassInstance, ClassMethod pMethod) :
            CFunctionCallback(),
            m_pClassInstance(pClassInstance),
            m_method(pMethod) {
                m_callbackType = METHOD_CALLBACK;
            }
            /**
             * 
             */
            virtual ~CMethodCallback() {
                m_pClassInstance = NULL;
                m_method = NULL;
                m_callbackType = INVALID_CALLBACK;
            }
            /**
             * 
             * @param method
             */
            void setMethod(ClassMethod pMethod) {
                m_pClassInstance = NULL;
                m_method = pMethod;
            }
            /**
             * 
             * @param pClassInstance
             */
            void setClass(TClass* pClassInstance) {
                m_pClassInstance = pClassInstance;
            }
            using base_type::Call;
            
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_method != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_method)(NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(CArgumentList *argv) {
                if(m_method != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_method)(argv);
                return FG_FALSE;
            }
            /**
             * 
             * @param pClassInstance
             * @return 
             */
            fgBool Call(TClass *pClassInstance) {
                if(m_method != NULL && pClassInstance != NULL)
                    return (pClassInstance->*m_method)(NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param pClassInstance
             * @param argv
             * @return 
             */
            fgBool Call(TClass *pClassInstance, CArgumentList *argv) {
                if(m_method != NULL && pClassInstance != NULL)
                    return (pClassInstance->*m_method)(argv);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline ClassMethod& getMethod(void) {
                return m_method;
            }
            /**
             * 
             * @return 
             */
            inline ClassMethod const& getMethod(void) const {
                return m_method;
            }

        private:
            /// 
            TClass* m_pClassInstance;
            ///
            ClassMethod m_method;
        };
    };
};

    #undef FG_INC_CALLBACK_BLOCK
#endif /* FG_INC_CALLBACK */
