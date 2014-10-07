/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_DATA_MANAGER_BASE_H_
#define _FG_DATA_MANAGER_BASE_H_

#include "fgManagerBase.h"
#include "Util/fgHandleManager.h"
#include "fgResourceErrorCodes.h"
#include "fgStatusReporter.h"

#define FG_MANAGER_DATA_BASE	0x00000080

template <typename DataType, typename HandleType, typename TagType>
/*
 *
 */
class fgDataManagerBase : public fgManagerBase, public fgStatusReporter<TagType>, protected fgHandleManager<DataType, HandleType>
{
public:
	// 
	fgDataManagerBase() { m_managerType = FG_MANAGER_DATA_BASE; }
	// 
	virtual ~fgDataManagerBase() { clear(); }

protected:
	// 
	virtual void clear(void);

public:
	// 
	virtual fgBool destroy(void) = 0;
	// 
	virtual fgBool initialize(void) = 0;

	// 
	virtual fgBool insert(HandleType& dhUniqueID, DataType pData, const std::string& nameTag);

	// 
	virtual fgBool remove(DataType pData);
	// 
	virtual fgBool remove(const HandleType& dhUniqueID);
	// 
	virtual fgBool remove(const std::string& nameTag);
	//
	virtual fgBool remove(const char *nameTag);

	// 
	virtual fgBool destroyData(DataType& pData);
	// 
	virtual fgBool destroyData(const HandleType& dhUniqueID);
	// 
	virtual fgBool destroyData(const std::string& nameTag);
	// 
	virtual fgBool destroyData(const char *nameTag);

	// 
	virtual DataType get(const HandleType& dhUniqueID);
	// 
	virtual DataType get(const std::string& nameTag);
	// 
	virtual DataType get(const char *nameTag);

	// 
	virtual DataType request(const std::string& info) = 0;
	// 
	virtual DataType request(const char *info) = 0;

	// 
	virtual fgBool isManaged(DataType pData);
	// 
	virtual fgBool isManaged(const HandleType& dhUniqueID);
	// 
	virtual fgBool isManaged(const std::string& nameTag);
	// 
	virtual fgBool isManaged(const char *nameTag);
};

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
void fgDataManagerBase<DataType, HandleType, TagType>::clear(void)
{
	fgHandleManager<DataType, HandleType>::releaseAllHandles();
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::insert(HandleType& dhUniqueID, DataType pData, const std::string& nameTag)
{
	if(!pData) {
		this->reportWarning(FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}

	if(fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
		this->reportError(FG_ERRNO_RESOURCE_ALREADY_MANAGED, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}

	if(!pData->getHandle().isNull()) {
		// Resource has already initialized handle
		this->reportError(FG_ERRNO_RESOURCE_INITIALIZED_HANDLE, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	// Acquire next valid resource handle
	// Insert the resource into the current catalog
	if(!fgHandleManager<DataType, HandleType>::acquireHandle(dhUniqueID, pData)) {
		// Could not aquire handle for the resource
		this->reportError(FG_ERRNO_RESOURCE_ACQUIRE_HANDLE, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	pData->setHandle(dhUniqueID);
	if(!fgHandleManager<DataType, HandleType>::setupName(nameTag, dhUniqueID)) {
		// Could not setup handle string tag/name for the resource
		this->reportError(FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(DataType pData)
{
	if(!fgDataManagerBase<DataType, HandleType, TagType>::isManaged(pData)) {
		return FG_FALSE;
	}
	return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const HandleType& dhUniqueID)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(dhUniqueID);
	if(!pData)
		return FG_FALSE;
	return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const std::string& nameTag)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
	if(!pData)
		return FG_FALSE;
	return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const char *nameTag)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
	if(!pData)
		return FG_FALSE;
	return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}


/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(DataType& pData)
{
	if(!remove(pData)) {
		this->reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	pData = NULL;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const HandleType& dhUniqueID)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
	if(!remove(pData)) {
		this->reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const std::string& nameTag)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	if(!remove(pData)) {
		this->reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const char *nameTag)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	if(!remove(pData)) {
		this->reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const HandleType& dhUniqueID)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
	return pData;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const std::string& nameTag)
{
	if(nameTag.empty()) {
		this->reportWarning(FG_ERRNO_RESOURCE_NAME_TAG_EMPTY, FG_MSG_IN_FUNCTION);
		return NULL;
	}
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	if(!pData) {
		this->reportError(FG_ERRNO_RESOURCE_NAME_TAG_INVALID, " tag='%s', in function: %s",nameTag.c_str(), __FUNCTION__);
		return NULL;
	}
	return pData;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const char *nameTag)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	return pData;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(DataType pData)
{
	if(!pData) {
		this->reportWarning(FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	if(FG_IS_INVALID_HANDLE(pData->getHandle())
		|| !fgHandleManager<DataType, HandleType>::isHandleValid(pData->getHandle())) {
			this->reportError(FG_ERRNO_RESOURCE_HANDLE_INVALID, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	if(!fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
		this->reportWarning(FG_ERRNO_RESOURCE_NOT_MANAGED, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	return FG_TRUE;
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const HandleType& dhUniqueID)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(dhUniqueID);
	return (fgBool)(pData != NULL);
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const std::string& nameTag)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
	return (fgBool)(pData != NULL);
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const char *nameTag)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
	return (fgBool)(pData != NULL);
}

#endif /* _FG_DATA_MANAGER_BASE_H_ */
