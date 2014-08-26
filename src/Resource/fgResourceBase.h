/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_BASE_H_
#define _FG_RESOURCE_BASE_H_

// Global include needed (it defines the parameters of the build)
#include "fgBuildConfig.h"

#include <map>
#include <string>

#define FG_FILE_QUALITY_MAPPING_TEXT "FileQualityMap"

/*
 *
 */
class fgResourceBase {
public:
	// Default empty constructor for resource base object
	fgResourceBase() : m_defaultID(-1) {
		m_filePath.clear();
		m_fileMapping.clear();
	}

	// Default empty destructor for resource base object
	virtual ~fgResourceBase() {
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
	virtual void setFilePath(std::string& path) {
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
	virtual void setFilePath(const char *path, int id) {
		if(!path)
			return;
		m_fileMapping[id] = path;
		if(id == m_defaultID)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}
	// Set file path to this resource
	virtual void setFilePath(std::string& path, int id) {
		m_fileMapping[id] = path;
		if(id == m_defaultID)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}

	// Get resource file path string
	std::string getFilePath(int id) const {
		 // this lazy cast is ok - non-const version does not modify anything
		return (const_cast<fgResourceBase*>(this)->getFilePath(id));
	}

	// Get reference to resource file path string
	std::string& getFilePath(int id) {
		if(m_fileMapping.find(id) == m_fileMapping.end()) {
			return m_filePath;
		}
		return m_fileMapping[id];
	}

	// Get resource file path as C-like string (char array)
	const char* getFilePathStr(int id) {
		if(m_fileMapping.find(id) == m_fileMapping.end()) {
			return m_filePath.c_str();
		}
		return m_fileMapping[id].c_str();
	}

	// Set default ID
	void setDefaultID(int id) {
		m_defaultID = id;
	}
protected:
	// File mapping, the key is int (quality)
	std::map<int, std::string>	m_fileMapping;
	// File path as separate string (by default this is for universal quality)
	std::string					m_filePath;
	int							m_defaultID;
};

#endif /* _FG_RESOURCE_BASE_H_ */
