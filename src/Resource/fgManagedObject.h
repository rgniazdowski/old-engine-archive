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
 * File:   fgManagedObjectBase.h
 * Author: vigilant
 *
 * Created on October 24, 2014, 5:17 PM
 */

#ifndef FG_INC_MANAGED_OBJECT
    #define FG_INC_MANAGED_OBJECT
    #define FG_INC_MANAGED_OBJECT_BLOCK

    #include "Util/fgNamedHandle.h"
    #include "fgManagerBase.h"
    #include "fgBool.h"
    #include <string>
    #include <cstdio>

namespace fg {
    namespace resource {

        /**
         * 
         */
        template<typename THandleType>
        class CManagedObject {
        public:
            ///
            typedef THandleType handle_type;
            ///
            typedef CManagedObject<THandleType> self_type;
            // System data is always set to (void *)this
            typedef fgBool(*CallbackFuncPtr)(void* systemData, void* userData);
            ///
            typedef CallbackFuncPtr callback_type;

        public:
            /**
             * Default empty constructor for managed base object
             */
            CManagedObject() : m_pManager(NULL), m_nameTag(), m_isManaged(FG_FALSE) { }
            
            /**
             * 
             * @param orig
             */
            CManagedObject(const self_type& orig) {
                if(this != &orig) {
                    m_pManager = orig.m_pManager;
                    m_nameTag = orig.m_nameTag;
                    m_isManaged = orig.m_isManaged;
                }
            }
            /**
             * Destructor for managed base object
             */
            virtual ~CManagedObject() {
                // Now call the special destructor callbacks
                int n = m_onDestructorCallbacks.size();
                for(int i = 0; i < n; i++) {
                    SCallbackData& info = m_onDestructorCallbacks[i];
                    if(info.callback) {
                        info.callback((void *)this, (void *)info.userData);
                        info.callback = NULL;
                        info.userData = NULL;
                    }
                }
                m_onDestructorCallbacks.clear_optimised();                
            }

        public:
            /**
             * 
             * @param pCallback
             * @param pUserData
             * @return 
             */
            fgBool registerOnDestruct(CallbackFuncPtr pCallback, void* pUserData = NULL) {
                if(!pCallback || isRegistered(pCallback))
                    return FG_FALSE;
                SCallbackData callbackInfo(pCallback, pUserData);
                m_onDestructorCallbacks.push_back(callbackInfo);
                return FG_TRUE;
            }
            /**
             * 
             * @param pCallback
             * @return 
             */
            fgBool isRegistered(CallbackFuncPtr pCallback) {
                if(!pCallback)
                    return FG_FALSE;
                int n = m_onDestructorCallbacks.size();
                // Check for duplicates
                for(int i = 0; i < n; i++) {
                    SCallbackData &info = m_onDestructorCallbacks[i];
                    if(info.callback == pCallback)
                        return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             * Set resource name (string TAG/ID)
             * @param name
             */
            inline void setName(const char* name) {
                if(name)
                    m_nameTag = name;
            }
            /**
             * 
             * @param name
             */
            inline void setName(const std::string& name) {
                m_nameTag = name;
            }
            /**
             * Get reference to resource name string
             * @return 
             */
            inline util::CNamedHandle& getName(void) {
                return m_nameTag;
            }
            /**
             * 
             * @return 
             */
            inline util::CNamedHandle const& getName(void) const {
                return m_nameTag;
            }
            /**
             * 
             * @return 
             */
            inline const char* getNameStr(void) const {
                return m_nameTag.c_str();
            }
            /**
             * Return the data handle ID
             * @return 
             */
            inline THandleType getHandle(void) const {
                return m_handle;
            }
            /**
             * Set the data handle ID 
             * @param handle
             */
            inline void setHandle(const THandleType handle) {
                m_handle = handle;
                m_nameTag.setIndex(m_handle.getIndex());
            }
            /**
             * Gets the reference to the data handle
             * @return Reference to the data handle
             */
            inline THandleType& getRefHandle(void) {
                return m_handle;
            }
            /**
             * 
             * @return 
             */
            inline THandleType const& getRefHandle(void) const {
                return m_handle;
            }
            /**
             * 
             * @param toggle
             */
            inline void setManaged(fgBool toggle = FG_TRUE) {
                m_isManaged = toggle;
            }
            /**
             * 
             * @return 
             */
            inline fgBool isManaged(void) const {
                return m_isManaged;
            }
            /**
             * 
             * @return 
             */
            inline fg::base::CManager* getManager(void) const {
                return m_pManager;
            }
            /**
             * 
             * @param pManager
             */
            inline void setManager(fg::base::CManager* pManager) {
                m_pManager = pManager;
            }

        protected:
            /// Pointer to the managing class - can be NULL
            fg::base::CManager* m_pManager;
            /// Name of the data, string ID
            util::CNamedHandle m_nameTag;
            /// Unique handle number
            THandleType m_handle;
            /// Is this data currently managed inside of any kind manager?
            fgBool m_isManaged;

        private:

            /**
             *
             */
            struct SCallbackData {
                ///
                CallbackFuncPtr callback;
                ///
                void* userData;
                /**
                 * 
                 */
                SCallbackData() : userData(NULL), callback(NULL) { }
                /**
                 * 
                 * @param pUserData
                 * @param pCallback
                 */
                SCallbackData(CallbackFuncPtr pCallback, void* pUserData) :
                callback(pCallback),
                userData(pUserData) { }
            }; // struct SCallbackData

            ///
            typedef fg::CVector<SCallbackData> CallbacksVec;
            ///
            typedef typename CallbacksVec::iterator CallbacksVecItor;
            /// Callbacks to call when the destructor is called
            CallbacksVec m_onDestructorCallbacks;
        }; // class CManagedObject
    } // namespace resource
} // namespace fg
    #undef FG_INC_MANAGED_OBJECT_BLOCK
#endif /* FG_INC_MANAGED_OBJECT */
