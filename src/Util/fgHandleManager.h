/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/**
 * Portions Copyright (C) Scott Bilas, 2000
 */

#ifndef FG_INC_HANDLE_MANAGER
    #define FG_INC_HANDLE_MANAGER

    #include "fgBuildConfig.h"
    #include "fgCommon.h"

    #include "fgPath.h"
    #include "fgLog.h"
    #include "fgHandle.h"

    #ifdef FG_USING_MARMALADE
        #include <hash_map>

        #ifndef FG_HASH_STD_STRING_TEMPLATE_DEFINED_
            #define FG_HASH_STD_STRING_TEMPLATE_DEFINED_

namespace std {

    template<> struct hash<std::string> {
        size_t operator ()(const std::string& x) const {
            return hash<const char*>()(x.c_str());
        }
    };
};

        #endif /* FG_HASH_STD_STRING_TEMPLATE_DEFINED_ */
    #else
        #include <unordered_map>
    #endif /* FG_USING_MARMALADE */

namespace fg {
    namespace util {

        /**
         * // HandleType HAS TO BE template of fgHandle
         */
        template <typename TDataType, typename THandleType>
        class CHandleManager {
    #ifdef FG_USING_MARMALADE
        protected:

            struct hmEqualTo {
                bool operator ()(const char* s1, const char* s2) const {
                    return strcmp(s1, s2) == 0;
                }
                bool operator ()(const std::string& s1, const std::string& s2) const {
                    return s1.compare(s2) == 0;
                }
            };
    #endif
        public:
            ///
            typedef TDataType data_type;
            ///
            typedef std::string HashKey;
            // Type for vector storing Data pointers
            typedef fg::CVector <TDataType> DataVec;
            typedef typename fg::CVector <TDataType>::iterator DataVecItor;
    #ifdef FG_USING_MARMALADE
            typedef std::hash<std::string> hashFunc;
            // Type for map, assigning handle index value to string ID (case sensitive)
            typedef std::hash_map <HashKey, fgRawIndex, hashFunc, hmEqualTo> NameMap;
    #else
            typedef std::unordered_map <HashKey, fgRawIndex> NameMap;
    #endif

        private:
            ///
            typedef fg::CVector <fgRawMagic> MagicVec;
            ///
            typedef fg::CVector <HashKey> NameVec;
            ///
            typedef fg::CVector <unsigned int> FreeSlotsVec;

            /// Data storage
            DataVec m_managedData;
            /// Corresponding magic numbers
            MagicVec m_magicData;
            /// Free slots in the database
            FreeSlotsVec m_freeSlots;
            /// Map for name (string) IDs
            NameMap m_nameMap;
            /// Vector for storing string IDs
            NameVec m_nameVec;

        protected:
            /**
             * Reset internal data
             */
            void clear(void);
        public:
            /**
             * Default constructor for Handle Manager object
             */
            CHandleManager() {
                clear();
            }
            /**
             * Destructor for Handle Manager object
             */
            virtual ~CHandleManager() {
                clear();
            }

            /**
             * 
             * @param rHandle
             * @param pResource
             * @return 
             */
            fgBool acquireHandle(THandleType& rHandle, TDataType pResource);
            /**
             * 
             * @param name
             * @param rHandle
             * @return 
             */
            fgBool setupName(const std::string& name, const THandleType& rHandle);
            /**
             * 
             * @param name
             * @param rHandle
             * @return 
             */
            fgBool setupName(const char* name, const THandleType& rHandle);
            /**
             * 
             * @param handle
             * @return 
             */
            fgBool releaseHandle(const THandleType& handle);
            /**
             * 
             */
            void releaseAllHandles(void);

            /**
             * 
             * @param handle
             * @return 
             */
            TDataType dereference(const THandleType& handle);
            /**
             * 
             * @param name
             * @return 
             */
            TDataType dereference(const std::string& name);
            /**
             * 
             * @param name
             * @return 
             */
            TDataType dereference(const char* name);
            /**
             * 
             * @return 
             */
            unsigned int getUsedHandleCount(void) const {
                return ( m_magicData.size() - m_freeSlots.size());
            }
            /**
             * 
             * @return 
             */
            fgBool hasUsedHandles(void) const {
                return (fgBool)(!!getUsedHandleCount());
            }
            /**
             * 
             * @return 
             */
            DataVec& getRefDataVector(void) {
                return m_managedData;
            }
            /**
             * 
             * @return 
             */
            const DataVec& getRefDataVector(void) const {
                return m_managedData;
            }

            /**
             * 
             * @param pData
             * @return 
             */
            fgBool isDataManaged(TDataType pData);
            /**
             * 
             * @param handle
             * @return 
             */
            fgBool isHandleValid(const THandleType& handle);
        };
    };
};
/**
 * 
 */
template <typename TDataType, typename THandleType>
void fg::util::CHandleManager<TDataType, THandleType>::clear(void) {
    m_managedData.clear_optimised();
    m_magicData.clear_optimised();
    m_freeSlots.clear_optimised();
    m_nameVec.clear_optimised();
    m_nameMap.clear();
}
/**
 * 
 * @param rHandle
 * @param pResource
 * @return 
 */
template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::acquireHandle(THandleType& rHandle, TDataType pResource) {
    // If free list is empty, add a new one otherwise use first one found
    unsigned int index;
    if(m_freeSlots.empty()) {
        index = m_magicData.size();
        if(!rHandle.init(index))
            return FG_FALSE;
        m_managedData.push_back(pResource);
        m_magicData.push_back(rHandle.getMagic());
        m_nameVec.push_back(std::string());
    } else {
        index = m_freeSlots.back();
        if(!rHandle.init(index))
            return FG_FALSE;
        m_freeSlots.pop_back();
        m_managedData[index] = pResource;
        m_magicData[index] = rHandle.getMagic();
        m_nameVec[index] = std::string();
    }
    return FG_TRUE;
}
/**
 * 
 * @param name
 * @param rHandle
 * @return 
 */
template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::setupName(const std::string& name, const THandleType& rHandle) {
    if(!isHandleValid(rHandle)) {
        return FG_FALSE;
    }
    if(m_nameMap.find(name) != m_nameMap.end()) {
        FG_LOG_ERROR("%s(%d): Such key already exists in name map - name_tag[%s], function[%s]", fg::path::fileName(__FILE__), __LINE__ - 1, name.c_str(), __FUNCTION__);
        return FG_FALSE; // Such key already exists
    }
    fgRawIndex index = rHandle.getIndex();
    if(!m_nameVec[index].empty()) {
        FG_LOG_ERROR("%s(%d): There is name tag already in the vector - index[%s], name_tag[%s], function[%s]", fg::path::fileName(__FILE__), __LINE__ - 1, index, name.c_str(), __FUNCTION__);
        // There is already some set on the current index
        return FG_FALSE;
    }
    m_nameMap[name] = index;
    m_nameVec[index] = name;
    return FG_TRUE;
}
/**
 * 
 * @param name
 * @param rHandle
 * @return 
 */
template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::setupName(const char* name, const THandleType& rHandle) {
    if(!isHandleValid(rHandle)) {
        return FG_FALSE;
    }
    if(m_nameMap.find(std::string(name)) != m_nameMap.end()) {
        FG_LOG_ERROR("%s(%d): Such key already exists in name map - name_tag[%s], function[%s]", fg::path::fileName(__FILE__), __LINE__ - 1, name, __FUNCTION__);
        return FG_FALSE; // Such key already exists
    }
    fgRawIndex index = rHandle.getIndex();
    if(m_nameVec[index].size() > 0) {
        FG_LOG_ERROR("%s(%d): There is name tag already in the vector - index[%s], name_tag[%s], function[%s]", fg::path::fileName(__FILE__), __LINE__ - 1, index, name, __FUNCTION__);
        // There is already some set on the current index
        // No reassignment is allowed
        return FG_FALSE;
    }
    m_nameMap[std::string(name)] = index;
    m_nameVec[index] = std::string(name);
    return FG_TRUE;
}
/**
 * 
 * @param handle
 * @return 
 */
template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::releaseHandle(const THandleType& handle) {
    if(!isHandleValid(handle)) {
        FG_LOG_DEBUG("HandleManager[%s]: can't release handle - handle is invalid, tag_name[%s]", THandleType::getTagName(), THandleType::getTagName());
        return FG_FALSE;
    }
    // which one?
    fgRawIndex index = handle.getIndex();
    // ok remove it - tag as unused and add to free list
    m_magicData[index] = 0;
    m_managedData[index] = NULL;
    FG_LOG_DEBUG("HandleManager[%s]: Releasing handle: index[%d], magic[%d], handle[%d]", THandleType::getTagName(), index, handle.getMagic(), handle.getHandle());
    if(!m_nameVec[index].empty()) {
        m_nameMap.erase(m_nameVec[index]);
        FG_LOG_DEBUG("HandleManager[%s]: erasing '%s' from handle map...", THandleType::getTagName(), m_nameVec[index].c_str());
    }
    m_nameVec[index].clear();
    m_freeSlots.push_back(index);
    if(!getUsedHandleCount()) {
        clear();
    }
    return FG_TRUE;
}
/**
 * 
 */
template <typename TDataType, typename THandleType>
void fg::util::CHandleManager<TDataType, THandleType>::releaseAllHandles(void) {
    clear();
}
/**
 * 
 * @param handle
 * @return 
 */
template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const THandleType& handle) {
    if(!isHandleValid(handle)) {
        return NULL;
    }
    fgRawIndex index = handle.getIndex();
    return *(m_managedData.begin() + index);
}
/**
 * 
 * @param name
 * @return 
 */
template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const std::string& name) {
    if(name.empty()) {
        return NULL;
    }
    typename NameMap::iterator it = m_nameMap.find(name);
    if(it == m_nameMap.end()) {
        return NULL;
    }
    fgRawIndex index = (*it).second;
    if(index >= m_managedData.size()) {
        return NULL;
    }
    if(m_nameVec[index].compare(name) == 0) {
        return *(m_managedData.begin() + index);
    } else {
        return NULL;
    }
}
/**
 * 
 * @param name
 * @return 
 */
template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    std::string key = name;
    return CHandleManager<TDataType, THandleType>::dereference(key);
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename TDataType, typename THandleType>
inline fgBool fg::util::CHandleManager<TDataType, THandleType>::isDataManaged(TDataType pData) {
    if(m_managedData.find(pData) != -1) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
/**
 * 
 * @param handle
 * @return 
 */
template <typename TDataType, typename THandleType>
inline fgBool fg::util::CHandleManager<TDataType, THandleType>::isHandleValid(const THandleType& handle) {
    if(handle.isNull()) {
        return FG_FALSE;
    }
    // check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
    fgRawIndex index = handle.getIndex();
    if((index >= m_managedData.size()) || (m_magicData[index] != handle.getMagic())) {
        // no good! invalid handle == client programming error
        FG_LOG_DEBUG("HandleManager[%s]: invalid handle, magic numbers don't match with index: index[%d], magic[%d], handle[%d], true_magic[%d]", THandleType::getTagName(), index, handle.getMagic(), handle.getHandle(), m_magicData[index]);
        return FG_FALSE;
    }
    return FG_TRUE;
}

    #if 0
template <typename DataType, typename HandleType>
inline const DataType* CHandleManager <DataType, HandleType>
::Dereference(HandleType handle) const {
    // this lazy cast is ok - non-const version does not modify anything
    typedef CHandleManager <DataType, HandleType> ThisType;
    return ( const_cast<ThisType*>(this)->Dereference(handle));
}
    #endif

#endif /* FG_INC_HANDLE_MANAGER */
