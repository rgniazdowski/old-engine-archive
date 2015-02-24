/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSceneCallback.h
 * Author: vigilant
 *
 * Created on February 18, 2015, 11:04 PM
 */

#ifndef FG_INC_GFX_SCENE_CALLBACK
    #define FG_INC_GFX_SCENE_CALLBACK
    #define FG_INC_GFX_SCENE_CALLBACK_BLOCK

    #include "Event/fgCallback.h"
    #include "fgGFXSceneEvent.h"

namespace fg {
    namespace gfx {

        class CSceneNode;
        class CSceneNodeTrigger;
        class CSceneManager;

        /**
         *
         */
        class CSceneCallback : public virtual fg::event::CFunctionCallback {
            friend class CSceneNode;
            friend class CSceneNodeTrigger;
            friend class CSceneManager;

        public:
            ///
            typedef fg::event::CFunctionCallback base_type;
            ///
            typedef CSceneCallback self_type;
            ///
            typedef CSceneCallback type;

        public:
            /**
             * 
             * @param pGuiMain
             */
            CSceneCallback() : m_ref(0) {
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::fgFunction)NULL);
            }
            /**
             * 
             */
            virtual ~CSceneCallback() { }

            using base_type::Call;

            /**
             * 
             * @param pNodeA
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA) = 0;

            /**
             * 
             * @param pNodeA
             * @param pNodeB
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA, CSceneNode* pNodeB) = 0;

        private:
            ///
            inline void upRef(void) {
                m_ref++;
            }
            ///
            inline unsigned int downRef(void) {
                if(m_ref) m_ref--;
                return m_ref;
            }

        private:
            ///
            unsigned int m_ref;
        };

        /**
         *
         */
        template < class TClass >
        class CSceneMethodCallback : public CSceneCallback {
        public:
            ///
            typedef CSceneCallback base_type;
            ///
            typedef CSceneMethodCallback self_type;
            ///
            typedef CSceneMethodCallback type;
            ///
            typedef fgBool(TClass::*fgSceneMethod)(CSceneNode* pNodeA, CSceneNode* pNodeB);
            ///
            typedef fgSceneMethod callback_type;

        public:
            /**
             * 
             * @param pClassInstance
             * @param pMethod
             */
            CSceneMethodCallback(TClass* pClassInstance, fgSceneMethod pMethod) :
            CSceneCallback() {
                m_pClassInstance = pClassInstance;
                m_sceneMethod = pMethod;
            }
            /**
             * 
             */
            virtual ~CSceneMethodCallback() {
                m_pClassInstance = NULL;
                m_sceneMethod = NULL;
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
            void setSceneMethod(fgSceneMethod method) {
                m_pClassInstance = NULL;
                m_sceneMethod = method;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_sceneMethod != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_sceneMethod)(NULL, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList* argv) {
                if(m_sceneMethod != NULL && m_pClassInstance != NULL) {
                    // If argument list is given then maybe should check for existence
                    // of STRUCT parameters ?                    
                    if(!argv)
                        return FG_FALSE;
                    /// THis will probably contain argument list with Event structure pointer
                    if(argv->getCount()) {
                        event::SArgument::Type arg_type;
                        void *ptr = argv->getValueByID(0, &arg_type);
                        if(arg_type != event::SArgument::Type::ARG_TMP_POINTER)
                            return FG_FALSE;
                        event::SSceneEvent* pSceneNodeEvent = (event::SSceneEvent*)ptr;
                        if(pSceneNodeEvent->code != event::INVALID) {
                            return this->Call(pSceneNodeEvent->node.pNodeA, pSceneNodeEvent->node.pNodeB);
                            //return this->Call(ptr); // THis will handle the structure passed as void*
                        }
                    }
                    return FG_FALSE;
                } else if(this->getFunction()) {
                    base_type::base_type::Call(argv);
                }
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
                if(m_sceneMethod != NULL && m_pClassInstance != NULL) {
                    if(!pSystemData) {
                        return (m_pClassInstance->*m_sceneMethod)(NULL, NULL);
                    } else {
                        // #FIXME - when using void* parameter the most probable
                        // scenario is that it's event structure of some kind
                        CSceneNode* pNode = static_cast<CSceneNode *>(pSystemData);
                        //if(pWidget->isManaged())
                        return (m_pClassInstance->*m_sceneMethod)(pNode, NULL);
                    }
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA) {
                if(m_sceneMethod != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_sceneMethod)(pNodeA, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA, CSceneNode* pNodeB) {
                if(m_sceneMethod != NULL && m_pClassInstance != NULL)
                    return (m_pClassInstance->*m_sceneMethod)(pNodeA, pNodeB);
                return FG_FALSE;
            }
            /**
             * 
             * @param pClassInstance
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            fgBool Call(TClass *pClassInstance, CSceneNode* pNodeA = NULL, CSceneNode* pNodeB = NULL) {
                if(m_sceneMethod != NULL && pClassInstance != NULL)
                    return (pClassInstance->*m_sceneMethod)(pNodeA, pNodeB);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline fgSceneMethod& getSceneMethod(void) {
                return m_sceneMethod;
            }
            /**
             * 
             * @return 
             */
            inline fgSceneMethod const& getSceneMethod(void) const {
                return m_sceneMethod;
            }

        private:
            /// 
            TClass* m_pClassInstance;
            ///
            fgSceneMethod m_sceneMethod;
        };

        /**
         * 
         */
        class CSceneFunctionCallback : public CSceneCallback {
        public:
            ///
            typedef CSceneCallback base_type;
            ///
            typedef CSceneFunctionCallback self_type;
            ///
            typedef CSceneFunctionCallback type;
            ///
            typedef fgBool(*fgSceneFunction)(CSceneNode* pNodeA, CSceneNode* pNodeB);
            ///
            typedef fgSceneFunction callback_type;
            /**
             * 
             * @param function
             */
            CSceneFunctionCallback(fgSceneFunction pFunction) :
            CSceneCallback() {
                m_sceneFunction = pFunction;
            }
            /**
             * 
             */
            virtual ~CSceneFunctionCallback() {
                m_sceneFunction = NULL;
            }
            /**
             * 
             * @param function
             */
            void setSceneFunction(fgSceneFunction pFunction) {
                m_sceneFunction = pFunction;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void) {
                if(m_sceneFunction != NULL)
                    return m_sceneFunction(NULL, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList* argv) {
                if(m_sceneFunction != NULL) {
                    // If argument list is given then maybe should check for existence
                    // of STRUCT parameters ?                    
                    if(!argv)
                        return FG_FALSE;
                    /// THis will probably contain argument list with Event structure pointer
                    if(argv->getCount()) {
                        event::SArgument::Type arg_type;
                        void *ptr = argv->getValueByID(0, &arg_type);
                        if(arg_type != event::SArgument::Type::ARG_TMP_POINTER)
                            return FG_FALSE;
                        event::SSceneEvent* pSceneNodeEvent = (event::SSceneEvent*)ptr;
                        if(pSceneNodeEvent->code != event::INVALID) {
                            return this->Call(pSceneNodeEvent->node.pNodeA, pSceneNodeEvent->node.pNodeB);
                            //return this->Call(ptr); // THis will handle the structure passed as void*
                        }
                    }
                    return FG_FALSE;
                } else if(this->getFunction()) {
                    return base_type::base_type::Call(argv);
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void* pSystemData) {
                // This is for compatibility - fgFunctionCallback provides the
                // *(void *pSystemData) Call() function version however it is 
                // empty
                if(m_sceneFunction != NULL) {
                    if(!pSystemData) {
                        return m_sceneFunction(NULL, NULL);
                    } else {
                        CSceneNode* pNode = static_cast<CSceneNode *>(pSystemData);
                        //if(pWidget->isManaged())
                        return m_sceneFunction(pNode, NULL);
                    }
                } else if(this->getFunction()) {
                    return base_type::base_type::Call(pSystemData);
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA) {
                if(m_sceneFunction != NULL)
                    return m_sceneFunction(pNodeA, NULL);
                return FG_FALSE;
            }
            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(CSceneNode* pNodeA, CSceneNode* pNodeB) {
                if(m_sceneFunction != NULL)
                    return m_sceneFunction(pNodeA, pNodeB);
                return FG_FALSE;
            }
            /**
             * 
             * @return 
             */
            inline fgSceneFunction& getSceneFunction(void) {
                return m_sceneFunction;
            }
            /**
             * 
             * @return 
             */
            inline fgSceneFunction const& getSceneFunction(void) const {
                return m_sceneFunction;
            }

        private:
            ///
            fgSceneFunction m_sceneFunction;
        };
    }
}

    #undef FG_INC_GFX_SCENE_CALLBACK_BLOCK
#endif	/* FG_INC_GFX_SCENE_CALLBACK */
