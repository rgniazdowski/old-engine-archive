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
 * File:   fgAbstractFactory.h
 * Author: vigilant
 *
 * Created on September 21, 2015, 4:19 PM
 */

#ifndef FG_INC_ABSTRACT_FACTORY
    #define FG_INC_ABSTRACT_FACTORY
    #define FG_INC_ABSTRACT_FACTORY_BLOCK

    #include "fgBool.h"
    #include "fgBTreeMap.h"

namespace fg {
    namespace util {
    #if __cplusplus > 199711L
        using AbstractCreateFunction = void* (*)(void);
    #else
        typedef void* (*AbstractCreateFunction)(void);
    #endif

        /**
         *
         */
        class CFactoryObjectBase {
        public:
            typedef CFactoryObjectBase self_type;
            typedef CFactoryObjectBase type;

        public:
            /**
             *
             */
            CFactoryObjectBase() { }
            /**
             *
             */
            virtual ~CFactoryObjectBase() { }

            /**
             * 
             * @return
             */
            virtual void* create(void) = 0;
        }; // class CFactoryObjectBase

        /**
         *
         */
        template<typename TYPE>
        class CFactoryObject : public CFactoryObjectBase {
        public:
            typedef CFactoryObjectBase base_type;
            typedef CFactoryObject<TYPE> self_type;
            typedef CFactoryObject<TYPE> type;

        public:
            /**
             *
             */
            CFactoryObject() : base_type() { }
            /**
             *
             */
            virtual ~CFactoryObject() { }
            /**
             * 
             * @return
             */
            virtual void* create(void) {
                return (void*)new TYPE();
            }
        }; // class CFactoryObject

        /**
         *
         */
        template <typename KEY, typename TYPE>
        class CAbstractFactory {
        public:
            typedef btree_map<KEY, CFactoryObjectBase*> FactoryMap;
            typedef typename FactoryMap::iterator FactoryMapItor;
            typedef typename FactoryMap::const_iterator FactoryMapConstItor;

            typedef KEY key_type;
            typedef TYPE return_type;

        public:
            /**
             *
             */
            CAbstractFactory() : m_factoryMap() { }
            /**
             *
             */
            virtual ~CAbstractFactory() {
                destroy();
            }
            /**
             *
             */
            void destroy(void) {
                FactoryMapItor it = m_factoryMap.begin();
                FactoryMapItor end = m_factoryMap.end();
                for(; it != end; it++) {
                    delete (it->second);
                }
                m_factoryMap.clear();
            }
            /**
             * 
             * @param key
             * @param pObject
             * @return
             */
            fgBool registerObject(const key_type& key, CFactoryObjectBase* pObject) {
                if(!pObject) {
                    return FG_FALSE; // invalid
                }
                FactoryMapItor it = m_factoryMap.find(key);
                if(it != m_factoryMap.end()) {
                    // already exists
                    return FG_FALSE;
                }
                m_factoryMap[key] = pObject;
                return true;
            }
            /**
             * 
             * @param key
             * @return
             */
            fgBool isRegistered(const key_type& key) const {
                FactoryMapConstItor it = m_factoryMap.find(key);
                if(it != m_factoryMap.end()) {
                    return FG_TRUE;
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param key
             * @param pResult
             * @return
             */
            fgBool create(const key_type& key, return_type** pResult) {
                if(!pResult)
                    return FG_FALSE;
                if(!isRegistered(key)) {
                    return FG_FALSE;
                }
                if(!m_factoryMap[key]) {
                    return FG_FALSE;
                }
                *pResult = static_cast<return_type*>(m_factoryMap[key]->create());
                return FG_TRUE;
            }
            /**
             * 
             * @param key
             * @return
             */
            return_type* create(const key_type& key) {
                if(!isRegistered(key)) {
                    return NULL;
                }
                if(!m_factoryMap[key]) {
                    return NULL;
                }
                return static_cast<return_type *>(m_factoryMap[key]->create());
            }

        private:
            ///
            FactoryMap m_factoryMap;
        }; // class CAbstractFactort
    } // namespace util
} // namespace fg


    #undef FG_INC_ABSTRACT_FACTORY_BLOCK
#endif	/* FG_INC_ABSTRACT_FACTORY */
