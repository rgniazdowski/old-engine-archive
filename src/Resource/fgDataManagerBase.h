/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_DATA_MANAGER_BASE
    #define FG_INC_DATA_MANAGER_BASE

    #include "fgManagerBase.h"
    #include "Util/fgHandleManager.h"
    #include "fgResourceErrorCodes.h"

    #include "fgMessageSubsystem.h"

    #define FG_MANAGER_DATA_BASE    0x00000080

namespace fg {
    namespace resource {

        /**
         *
         */
        template <typename TDataType, typename THandleType, typename TTagType>
        class CDataManagerBase :
        public fg::base::CManager,
        protected fg::util::CHandleManager<TDataType, THandleType> {
        public:
            ///
            typedef CDataManagerBase<TDataType, THandleType, TTagType> self_type;
            ///
            typedef TTagType tag_type;
            ///
            typedef THandleType handle_type;
            ///
            typedef fg::util::CHandleManager<TDataType, THandleType> handle_mgr_type;

        public:
            /**
             * 
             */
            CDataManagerBase() {
                m_managerType = FG_MANAGER_DATA_BASE;
            }
            /**
             * 
             */
            virtual ~CDataManagerBase() {
                clear();
            }

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void) = 0;
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void) = 0;

            /**
             * 
             * @param dhUniqueID
             * @param pData
             * @param nameTag
             * @return 
             */
            virtual fgBool insert(TDataType pData, const std::string& nameTag);

            /**
             * 
             * @param pData
             * @return 
             */
            virtual fgBool remove(TDataType pData);
            /**
             * 
             * @param dhUniqueID
             * @return 
             */
            virtual fgBool remove(const THandleType& dhUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool remove(const char *nameTag);

            /**
             * 
             * @param pData
             * @return 
             */
            virtual fgBool destroyData(TDataType& pData);
            /**
             * 
             * @param dhUniqueID
             * @return 
             */
            virtual fgBool destroyData(const THandleType& dhUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyData(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool destroyData(const char *nameTag);

            /**
             * 
             * @param dhUniqueID
             * @return 
             */
            virtual TDataType get(const THandleType& dhUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual TDataType get(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual TDataType get(const char *nameTag);

            /**
             * 
             * @param info
             * @return 
             */
            virtual TDataType request(const std::string& info) = 0;
            /**
             * 
             * @param info
             * @return 
             */
            virtual TDataType request(const char *info) = 0;

            /**
             * 
             * @param pData
             * @return 
             */
            virtual fgBool isManaged(TDataType pData);
            /**
             * 
             * @param dhUniqueID
             * @return 
             */
            virtual fgBool isManaged(const THandleType& dhUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            virtual fgBool isManaged(const char *nameTag);
        };
    };
};
/**
 * 
 */
template <typename DataType, typename HandleType, typename TagType>
void fg::resource::CDataManagerBase<DataType, HandleType, TagType>::clear(void) {
    handle_mgr_type::releaseAllHandles();
}
/**
 * 
 * @param dhUniqueID
 * @param pData
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::insert(DataType pData, const std::string& nameTag) {
    if(!pData) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    HandleType dhUniqueID;
    if(handle_mgr_type::isDataManaged(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_ALREADY_MANAGED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }

    if(!pData->getHandle().isNull()) {
        // Resource has already initialized handle
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_INITIALIZED_HANDLE, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // Acquire next valid resource handle
    // Insert the resource into the current catalog
    if(!handle_mgr_type::acquireHandle(dhUniqueID, pData)) {
        // Could not aquire handle for the resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_ACQUIRE_HANDLE, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // This is important - on addition need to update the handle
    pData->setHandle(dhUniqueID);
    if(!handle_mgr_type::setupName(nameTag, dhUniqueID)) {
        // Could not setup handle string tag/name for the resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    #if defined(FG_DEBUG)
    FG_MessageSubsystem->reportSuccess(tag_type::name(), FG_ERRNO_RESOURCE_OK, "Inserted data with name[%s], index[%u], magic[%u], handle[%u], hash[%u]",
                                       nameTag.c_str(), pData->getName().getIndex(), dhUniqueID.getMagic(), dhUniqueID.getHandle(), pData->getName().getHash());
    #endif
    return FG_TRUE;
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::remove(DataType pData) {
    if(!self_type::isManaged(pData)) {
        return FG_FALSE;
    }
    return handle_mgr_type::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::remove(const HandleType& dhUniqueID) {
    DataType pData = self_type::get(dhUniqueID);
    if(!pData)
        return FG_FALSE;
    return handle_mgr_type::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::remove(const std::string& nameTag) {
    DataType pData = self_type::get(nameTag);
    if(!pData)
        return FG_FALSE;
    return handle_mgr_type::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::remove(const char *nameTag) {
    DataType pData = self_type::get(nameTag);
    if(!pData)
        return FG_FALSE;
    return handle_mgr_type::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::destroyData(DataType& pData) {
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    pData = NULL;
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::destroyData(const HandleType& dhUniqueID) {
    DataType pData = handle_mgr_type::dereference(dhUniqueID);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::destroyData(const std::string& nameTag) {
    DataType pData = handle_mgr_type::dereference(nameTag);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::destroyData(const char *nameTag) {
    DataType pData = handle_mgr_type::dereference(nameTag);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fg::resource::CDataManagerBase<DataType, HandleType, TagType>::get(const HandleType& dhUniqueID) {
    DataType pData = handle_mgr_type::dereference(dhUniqueID);
    return pData;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fg::resource::CDataManagerBase<DataType, HandleType, TagType>::get(const std::string& nameTag) {
    if(nameTag.empty()) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NAME_TAG_EMPTY, FG_MSG_IN_FUNCTION);
        return NULL;
    }
    DataType pData = handle_mgr_type::dereference(nameTag);
    if(!pData) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_NAME_TAG_INVALID, " tag='%s', in function: %s", nameTag.c_str(), __FUNCTION__);
        return NULL;
    }
    return pData;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fg::resource::CDataManagerBase<DataType, HandleType, TagType>::get(const char *nameTag) {
    DataType pData = handle_mgr_type::dereference(nameTag);
    return pData;
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::isManaged(DataType pData) {
    if(!pData) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pData->getHandle())
            || !handle_mgr_type::isHandleValid(pData->getHandle())) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_HANDLE_INVALID, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    if(!handle_mgr_type::isDataManaged(pData)) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NOT_MANAGED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::isManaged(const HandleType& dhUniqueID) {
    DataType pData = self_type::get(dhUniqueID);
    return (fgBool)(pData != NULL);
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::isManaged(const std::string& nameTag) {
    DataType pData = self_type::get(nameTag);
    return (fgBool)(pData != NULL);
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fg::resource::CDataManagerBase<DataType, HandleType, TagType>::isManaged(const char *nameTag) {
    DataType pData = self_type::get(nameTag);
    return (fgBool)(pData != NULL);
}

#endif /* FG_INC_DATA_MANAGER_BASE */
