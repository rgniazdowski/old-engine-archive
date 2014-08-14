/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/**
 * Portions Copyright (C) Scott Bilas, 2000
 */

#ifndef _FG_HANDLE_MANAGER_H_
#define _FG_HANDLE_MANAGER_H_

#include "fgCommon.h"
#include "fgHandle.h"

#include <hash_map>

template <typename DataType, typename HandleType>
class fgHandleManager
{
public:
    typedef fgArrayVector <DataType> hmDataVec;
private:
    typedef fgArrayVector <fgRawMagic>   hmMagicVec;
    typedef fgArrayVector <unsigned int> hmFreeSlotsVec;
	// Data storage
    hmDataVec  m_managedData;
	// Corresponding magic numbers
    hmMagicVec m_magicData;
	// Free slots in the database
    hmFreeSlotsVec  m_FreeSlots;

protected:
	// Reset internal data
	void clear(void);
public:
	// Default constructor for Handle Manager object
	fgHandleManager() { clear(); }
	// Default destructor for Handle Manager object
	~fgHandleManager() { clear(); }

	//
    fgBool acquireHandle(HandleType& rHandle, DataType pResource);
	//
    fgBool  releaseHandle(HandleType handle);
	//
	void releaseAllHandles(void);

	//
    DataType dereference(HandleType handle);
    //const DataType* Dereference( HandleType handle ) const;

	//
    unsigned int getUsedHandleCount(void) const {
		return ( m_magicData.size() - m_FreeSlots.size());
	}

	//
    fgBool hasUsedHandles(void) const {
		return (fgBool)(!!GetUsedHandleCount());  
	}

	// 
	hmDataVec& getRefDataVector(void) {
		return m_managedData;
	}

	//
	fgBool isDataManaged(DataType pData);
	//
	fgBool isHandleValid(HandleType handle);
};

/*
 *
 */
template <typename DataType, typename HandleType>
void fgHandleManager<DataType, HandleType>::clear(void)
{
	m_managedData.clear_optimised();
	m_magicData.clear_optimised();
	m_FreeSlots.clear_optimised();
}

/*
 *
 */
template <typename DataType, typename HandleType>
fgBool fgHandleManager<DataType, HandleType>::acquireHandle(HandleType& rHandle, DataType pResource)
{
    // If free list is empty, add a new one otherwise use first one found
    unsigned int index;
    if(m_FreeSlots.empty()) {
        index = m_magicData.size();
        if(!rHandle.init(index))
			return FG_FALSE;
        m_managedData.push_back(pResource);
        m_magicData.push_back(rHandle.getMagic());
    } else {
        index = m_FreeSlots.back();
		if(!rHandle.init(index))
			return FG_FALSE;
        m_FreeSlots.pop_back();
		m_managedData[index] = pResource;
        m_magicData[index] = rHandle.getMagic();
    }
    return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType>
fgBool fgHandleManager<DataType, HandleType>::releaseHandle(HandleType handle)
{
	if(!isHandleValid(handle))
		return FG_FALSE;
    // which one?
    fgRawIndex index = handle.getIndex();
    // ok remove it - tag as unused and add to free list
    m_magicData[index] = 0;
	m_managedData[index] = NULL;
    m_FreeSlots.push_back(index);
	return FG_TRUE;
}

/*
 *
 */
template <typename DataType, typename HandleType>
void fgHandleManager<DataType, HandleType>::releaseAllHandles(void)
{
	clear();
}

/*
 *
 */
template <typename DataType, typename HandleType>
inline DataType fgHandleManager<DataType, HandleType>::dereference(HandleType handle)
{
	if(!isHandleValid(handle))
		return NULL;
	fgRawIndex index = handle.getIndex();
    return *(m_managedData.begin() + index);
}

/*
 *
 */
template <typename DataType, typename HandleType>
inline fgBool fgHandleManager<DataType, HandleType>::isDataManaged(DataType pData)
{
	if(m_managedData.find(pData) != -1)
		return FG_TRUE;
	return FG_FALSE;
}

/*
 *
 */
template <typename DataType, typename HandleType>
inline fgBool fgHandleManager<DataType, HandleType>::isHandleValid(HandleType handle)
{
	if(handle.isNull())
		return FG_FALSE;
	// check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
	fgRawIndex index = handle.getIndex();
    if ((index >= m_managedData.size()) || (m_magicData[index] != handle.getMagic()))
    {
        // no good! invalid handle == client programming error
        return FG_FALSE;
    }
	return FG_TRUE;
}

#if 0
template <typename DataType, typename HandleType>
inline const DataType* fgHandleManager <DataType, HandleType>
:: Dereference( HandleType handle ) const
{
    // this lazy cast is ok - non-const version does not modify anything
    typedef fgHandleManager <DataType, HandleType> ThisType;
    return ( const_cast <ThisType*> ( this )->Dereference( handle ) );
}
#endif

#endif /* _FG_HANDLE_MANAGER_H_ */
