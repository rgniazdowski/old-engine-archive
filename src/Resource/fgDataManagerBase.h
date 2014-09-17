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

template <typename DataType, typename HandleType, typename TagType>
class fgDataManagerBase : public fgManagerBase, public fgStatusReporter<TagType>, protected fgHandleManager<DataType, HandleType>
{
protected:
private:
public:
	// 
	fgDataManagerBase() { }
	// 
	virtual ~fgDataManagerBase() { }

protected:
	// 
	virtual void clear(void);

public:
	// 
	virtual fgBool destroy(void);
	// 
	virtual fgBool initialize(void);

	// 
	virtual fgBool insert(HandleType& dhUniqueID, DataType pData, std::string& nameTag);

	// 
	virtual fgBool remove(DataType pData);
	// 
	virtual fgBool remove(HandleType dhUniqueID);
	// 
	virtual fgBool remove(std::string& nameTag);

	// 
	virtual fgBool destroyData(DataType pData);
	// 
	virtual fgBool destroyData(HandleType dhUniqueID);
	// 
	virtual fgBool destroyData(std::string& nameTag);

	// 
	virtual DataType get(HandleType dhUniqueID);
	// 
	virtual DataType get(std::string& nameTag);

	// 
	virtual fgBool isManaged(DataType pData);
	// 
	virtual fgBool isManaged(HandleType dhUniqueID);
	// 
	virtual fgBool isManaged(std::string& nameTag);
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
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroy(void)
{
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::initialize(void)
{
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::insert(HandleType& dhUniqueID, DataType pData, std::string& nameTag)
{
	if(!pData) {
		reportWarning(FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}

	if(fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
		reportError(FG_ERRNO_RESOURCE_ALREADY_MANAGED, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}

	if(!pData->getHandle().isNull()) {
		// Resource has already initialized handle
		reportError(FG_ERRNO_RESOURCE_INITIALIZED_HANDLE, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	// Acquire next valid resource handle
	// Insert the resource into the current catalog
	if(!fgHandleManager<DataType, HandleType>::acquireHandle(dhUniqueID, pData)) {
		// Could not aquire handle for the resource
		reportError(FG_ERRNO_RESOURCE_ACQUIRE_HANDLE, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	pData->setHandle(dhUniqueID);
	//pData->setHandle(dhUniqueID);
	if(!fgHandleManager<DataType, HandleType>::setupName(nameTag, dhUniqueID)) {
		// Could not setup handle string tag/name for the resource
		reportError(FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME, FG_MSG_IN_FUNCTION);
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
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(HandleType dhUniqueID)
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
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(std::string& nameTag)
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
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(DataType pData)
{
	if(!remove(pData)) {
		reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(HandleType dhUniqueID)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
	if(!remove(pData)) {
		reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(std::string& nameTag)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	if(!remove(pData)) {
		reportError(FG_ERRNO_RESOURCE_REMOVE);
		return FG_FALSE;
	}
	delete pData;
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(HandleType dhUniqueID)
{
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
	if(!pData) {
		// Could not find resource to remove, handle is invalid
		reportError(FG_ERRNO_RESOURCE_NOT_FOUND_INVALID_HANDLE, FG_MSG_IN_FUNCTION);
		return NULL;
	}
	return pData;
}

template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(std::string& nameTag)
{
	if(nameTag.empty()) {
		reportWarning(FG_ERRNO_RESOURCE_NAME_TAG_EMPTY, FG_MSG_IN_FUNCTION);
		return NULL;
	}
	DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
	if(!pData) {
		reportError(FG_ERRNO_RESOURCE_NAME_TAG_INVALID, FG_MSG_IN_FUNCTION);
		return NULL;
	}
	return pData;
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(DataType pData)
{
	if(!pData) {
		reportWarning(FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	if(FG_IS_INVALID_HANDLE(pData->getHandle())
		|| !fgHandleManager<DataType, HandleType>::isHandleValid(pData->getHandle())) {
			reportError(FG_ERRNO_RESOURCE_HANDLE_INVALID, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	if(!fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
		reportWarning(FG_ERRNO_RESOURCE_NOT_MANAGED, FG_MSG_IN_FUNCTION);
		return FG_FALSE;
	}
	return FG_TRUE;
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(HandleType dhUniqueID)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(dhUniqueID);
	return (fgBool)(pData != NULL);
}

template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(std::string& nameTag)
{
	DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
	return (fgBool)(pData != NULL);
}

#endif /* _FG_DATA_MANAGER_BASE_H_ */
