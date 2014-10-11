/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_DATA_OBJECT_BASE_H_
#define _FG_DATA_OBJECT_BASE_H_

// Global include needed (it defines the parameters of the build)
#include "fgBuildConfig.h"

#include <map>
#include <string>

#define FG_FILE_QUALITY_MAPPING_TEXT "FileQualityMap"

template<typename HandleType, typename MapKeyType>
/*
 * This is the base class for  data  objects  that are meant
 * to be handle in DataManager. It's for data that is loaded
 * from disk/storage. It's  also  designed  to hold multiple 
 * file paths depending  on the  MapKey type.  In most cases
 * the ID refers  to  the used  quality level throughout the 
 * project.  Quality  depends on some  explicit  settings or
 * device hardware  on which the program is being  executed.
 */
class fgDataObjectBase 
{
public:
	// Default empty constructor for resource base object
	fgDataObjectBase() : m_defaultID((MapKeyType)-1) {
		m_filePath.clear();
		m_fileMapping.clear();
	}

	// Default empty destructor for resource base object
	virtual ~fgDataObjectBase() {
		m_filePath.clear();
		m_fileMapping.clear();
	}
public:
	// Set file path to this resource
	virtual void setFilePath(const char *path) {
		if(!path)
			return;
		m_filePath.clear();
		m_filePath = path;
		m_fileMapping[m_defaultID] = path;
	}
	// Set file path to this resource
	virtual void setFilePath(const std::string& path) {
		m_filePath.clear();
		m_filePath = path;
		m_fileMapping[m_defaultID] = path;
	}

	// Get resource file path string
	std::string getFilePath(void) const {
		return m_filePath;
	}
	// Get reference to resource file path string
	std::string& getFilePath(void) {
		return m_filePath;
	}
	// Get resource file path as C-like string (char array)
	const char* getFilePathStr(void) const {
		return m_filePath.c_str();
	}

	// Set file path to this resource
	virtual void setFilePath(const char *path, MapKeyType id) {
		if(!path)
			return;
		m_fileMapping[id] = path;
		if(id == m_defaultID)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}
	// Set file path to this resource
	virtual void setFilePath(std::string& path, MapKeyType id) {
		m_fileMapping[id] = path;
		if(id == m_defaultID)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}

	// Get resource file path string
	std::string getFilePath(MapKeyType id) const {
		 // this lazy cast is ok - non-const version does not modify anything
		return (const_cast<fgDataObjectBase<HandleType, MapKeyType>*>(this)->getFilePath(id));
	}

	// Get reference to resource file path string
	std::string& getFilePath(MapKeyType id) {
		if(m_fileMapping.find(id) == m_fileMapping.end()) {
			return m_filePath;
		}
		return m_fileMapping[id];
	}

	// Get resource file path as C-like string (char array)
	const char* getFilePathStr(MapKeyType id) {
		if(m_fileMapping.find(id) == m_fileMapping.end()) {
			return m_filePath.c_str();
		}
		return m_fileMapping[id].c_str();
	}

	// Set default ID
	void setDefaultID(MapKeyType id) {
		m_defaultID = id;
	}

	// Set resource name (string TAG/ID)
	inline void setName(const char *name) {
		m_nameTag = name;
	}
	// Set resource name (string TAG/ID)
	inline void setName(const std::string& name) {
		m_nameTag = name;
	}

	// Get resource name string
	std::string getName(void) const {
		return m_nameTag;
	}
	// Get reference to resource name string
	std::string& getName(void) {
		return m_nameTag;
	}
	// Get resource name (TAG/string ID) as C-like string (char array)
	const char* getNameStr(void) const {
		return m_nameTag.c_str();
	}

	// Return the data handle ID
	HandleType getHandle(void) const {
		return m_handle;
	}

	// Set the data handle ID 
	void setHandle(HandleType handle) {
		m_handle = handle;
	}

	// Returns the reference to the data handle
	HandleType& getRefHandle(void) {
		return m_handle;
	}

protected:
	/// File mapping
	std::map<MapKeyType, std::string>	m_fileMapping;
	/// File path as separate string (by default this is for universal quality)
	std::string					m_filePath;
	/// Name of the data, string ID
	std::string					m_nameTag;
	/// Default ID to write to
	MapKeyType					m_defaultID;
	/// Unique handle number
	HandleType					m_handle;
};

#endif /* _FG_DATA_OBJECT_BASE_H_ */
