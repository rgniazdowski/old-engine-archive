/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
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
    #include "fgNamedHandle.h"

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
            typedef CHandleManager<TDataType, THandleType> self_type;
            ///
            typedef TDataType data_type;
            ///
            typedef std::string HashKeyString;

    #if defined(FG_USING_MARMALADE)
            ///
            typedef std::hash<std::string> hashFunc;
            /// Type for map, assigning handle index value to string ID (case sensitive)
            typedef std::hash_map<HashKeyString, fgRawIndex, hashFunc, hmEqualTo> NameMap;
    #else
            /// Special Name map - maps std::string to the index
            typedef std::unordered_map<HashKeyString, unsigned int> NameMap;
            /// Iterator through the Name map
            typedef NameMap::iterator NameMapItor;
    #endif
            /// Hash map - maps the name tags hash sum to the data vector index
            typedef std::map<unsigned int, unsigned int> HashMap;
            /// Iterator through the hash map
            typedef HashMap::iterator HashMapItor;


        protected:

            /**
             * Special data holder - DataVec[index] -> data / magic / nameTag
             */
            struct SDataHolder {
                ///
                data_type data;
                ///
                fgRawMagic magic;
                ///
                CNamedHandle nameTag;
                /**
                 * 
                 */
                SDataHolder() : data(NULL), magic(0), nameTag() { }
                /**
                 * 
                 */
                ~SDataHolder() {
                    clear();
                }
                /**
                 * 
                 */
                void clear(void) {
                    data = NULL;
                    magic = 0;
                    nameTag.setIndex(0);
                    nameTag.clear();
                }
            }; // struct SDataHolder

            // Type for vector storing Data pointers
            typedef CVector<SDataHolder> DataVec;
            /// Iterator through the managed data vector
            typedef typename CVector<SDataHolder>::iterator DataVecItor;

        private:
            /// Free slots vector
            typedef CVector<unsigned int> FreeSlotsVec;

            /// Free slots in the database
            FreeSlotsVec m_freeSlots;
            /// Special data storage
            DataVec m_managedData;
            /// Map for name (string) IDs - bind str name to index
            NameMap m_nameMap;
            /// Map for binding hash sum to index
            HashMap m_hashMap;

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
            TDataType dereference(CNamedHandle& name);
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
                return (m_managedData.size() - m_freeSlots.size());
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
        }; // class CHandleManager
    } // namespace util
} // namespace fg
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
void fg::util::CHandleManager<TDataType, THandleType>::clear(void) {
    m_managedData.clear_optimised();
    m_freeSlots.clear_optimised();
    m_nameMap.clear();
    m_hashMap.clear();
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::acquireHandle(THandleType& rHandle, TDataType pResource) {
    // If free list is empty, add a new one otherwise use first one found
    unsigned int index;
    if(m_freeSlots.empty()) {
        index = m_managedData.size();
        if(!rHandle.init(index))
            return FG_FALSE;
        SDataHolder holder;
        holder.data = pResource;
        holder.magic = rHandle.getMagic();
        holder.nameTag.setIndex(index);
        m_managedData.push_back(holder);

    } else {
        index = m_freeSlots.back();
        if(!rHandle.init(index))
            return FG_FALSE;
        m_freeSlots.pop_back();
        m_managedData[index].data = pResource;
        m_managedData[index].magic = rHandle.getMagic();
        m_managedData[index].nameTag.setIndex(index);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::setupName(const std::string& name, const THandleType& rHandle) {
    if(!isHandleValid(rHandle)) {
        return FG_FALSE;
    }
    fgRawIndex index = rHandle.getIndex();
    if(m_nameMap.find(name) != m_nameMap.end()) {
        FG_LOG_ERROR("HandleManager[%s] Such key already exists in name map - index[%u], name_tag[%s]",
                     THandleType::getTagName(),
                     index,
                     name.c_str());
        return FG_FALSE; // Such key already exists
    }
    if(!m_managedData[index].nameTag.empty()) {
        FG_LOG_ERROR("HandleManager[%s]: There is name tag already in the vector - index[%u], name_tag[%s]",
                     THandleType::getTagName(),
                     index,
                     name.c_str());
        // There is already some set on the current index
        return FG_FALSE;
    }
    m_managedData[index].nameTag.set(name);
    m_managedData[index].nameTag.setIndex(index);
    unsigned int hash = m_managedData[index].nameTag.getStringHash();
    m_nameMap[name] = index;
    m_hashMap[hash] = index;
    FG_LOG_DEBUG("HandleManager[%s]: Setup name[%s], hash[%10u], index[%u]",
                 THandleType::getTagName(),
                 name.c_str(),
                 hash,
                 index);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::setupName(const char* name, const THandleType& rHandle) {
    if(!isHandleValid(rHandle)) {
        return FG_FALSE;
    }
    std::string strname = std::string(name);
    fgRawIndex index = rHandle.getIndex();
    if(m_nameMap.find(strname) != m_nameMap.end()) {
        FG_LOG_ERROR("HandleManager[%s] Such key already exists in name map - index[%u], name_tag[%s]",
                     THandleType::getTagName(),
                     index,
                     name);
        return FG_FALSE; // Such key already exists
    }
    if(!m_managedData[index].nameTag.empty()) {
        FG_LOG_ERROR("HandleManager[%s]: There is name tag already in the vector - index[%u], name_tag[%s]",
                     THandleType::getTagName(),
                     index,
                     name);
        // There is already some set on the current index
        // No reassignment is allowed
        return FG_FALSE;
    }
    m_managedData[index].nameTag.set(strname);
    m_managedData[index].nameTag.setIndex(index);
    unsigned int hash = m_managedData[index].nameTag.getStringHash();
    m_nameMap[strname] = index;
    m_hashMap[hash] = index;
    FG_LOG_DEBUG("HandleManager[%s]: Setup name[%s], hash[%10u], index[%u]",
                 THandleType::getTagName(),
                 name,
                 hash,
                 index);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
fgBool fg::util::CHandleManager<TDataType, THandleType>::releaseHandle(const THandleType& handle) {
    if(!isHandleValid(handle)) {
        FG_LOG_DEBUG("HandleManager[%s]: can't release handle - handle is invalid, tag_name[%s]", THandleType::getTagName(), THandleType::getTagName());
        return FG_FALSE;
    }
    // which one?
    fgRawIndex index = handle.getIndex();
    // ok remove it - tag as unused and add to free list
    m_managedData[index].data = NULL;
    m_managedData[index].magic = 0;
    FG_LOG_DEBUG("HandleManager[%s]: Releasing handle: index[%d], magic[%d], handle[%d], name[%s]",
                 THandleType::getTagName(),
                 index,
                 handle.getMagic(),
                 handle.getHandle(),
                 m_managedData[index].nameTag.c_str());
    if(!m_managedData[index].nameTag.empty()) {
        m_nameMap.erase(std::string(m_managedData[index].nameTag.c_str()));
    }
    unsigned int hash = m_managedData[index].nameTag.getStringHash();
    if(hash) {
        m_hashMap.erase(hash);
    }
    m_managedData[index].nameTag.clear();
    m_freeSlots.push_back(index);
    if(!this->getUsedHandleCount()) {
        this->clear();
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
void fg::util::CHandleManager<TDataType, THandleType>::releaseAllHandles(void) {
    this->clear();
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const THandleType& handle) {
    #if defined(FG_DEBUG)
    if(!this->isHandleValid(handle)) {
        return NULL;
    }
    #else
    if(handle.isNull()) {
        return NULL;
    }
    #endif
    fgRawIndex index = handle.getIndex();
    return (*(m_managedData.begin() + index)).data;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const std::string& name) {
    if(name.empty()) {
        return NULL;
    }
    CNamedHandle nameTag;
    nameTag.set(name);
    unsigned int hash = nameTag.getStringHash();
    HashMapItor hashIt = m_hashMap.find(hash);
    if(hashIt == m_hashMap.end()) {
        return NULL;
    }
    fgRawIndex index = hashIt->second;
    #if defined(FG_DEBUG)
    if(index >= m_managedData.size()) {
        return NULL;
    }
    #endif
    return (*(m_managedData.begin() + index)).data;

    #if 0
    if(0) {
        NameMapItor it = m_nameMap.find(name);
        if(it == m_nameMap.end()) {
            return NULL;
        }
        fgRawIndex index = (*it).second;
        if(index >= m_managedData.size()) {
            return NULL;
        }
        if(m_managedData[index].nameTag.compare(name) == 0) {

        } else {
            return NULL;
        }
    }
    #endif
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    std::string key = name;
    return self_type::dereference(key);
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline TDataType fg::util::CHandleManager<TDataType, THandleType>::dereference(CNamedHandle& name) {
    if(name.empty()) {
        return NULL;
    }
    if(name.isIndexSet()) {
        unsigned int index = name.getIndex();
    #if defined(FG_DEBUG)
        if(index >= m_managedData.size()) {
            return NULL;
        }
    #endif
        return *(m_managedData.begin() + index);
    } else {
        unsigned int hash = name.getStringHash();
        HashMapItor hashIt = m_hashMap.find(hash);
        if(hashIt == m_hashMap.end()) {
            return NULL;
        }
        fgRawIndex index = hashIt->second;
    #if defined(FG_DEBUG)
        if(index >= m_managedData.size()) {
            return NULL;
        }
    #endif
        name.setIndex(index);
        return *(m_managedData.begin() + index);
    }
    return NULL;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline fgBool fg::util::CHandleManager<TDataType, THandleType>::isDataManaged(TDataType pData) {
    int n = m_managedData.size();
    for(int i = 0; i < n; i++) {
        if(m_managedData[i].data == pData) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

template <typename TDataType, typename THandleType>
inline fgBool fg::util::CHandleManager<TDataType, THandleType>::isHandleValid(const THandleType& handle) {
    if(handle.isNull()) {
        return FG_FALSE;
    }
    // check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
    fgRawIndex index = handle.getIndex();

    if((index >= m_managedData.size()) || (m_managedData[index].magic != handle.getMagic())) {
        // no good! invalid handle == client programming error
        FG_LOG_DEBUG("HandleManager[%s]: invalid handle, magic numbers don't match with index: index[%d], magic[%d], handle[%d], true_magic[%d]",
                     THandleType::getTagName(),
                     index,
                     handle.getMagic(),
                     handle.getHandle(),
                     m_managedData[index].magic);
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

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
