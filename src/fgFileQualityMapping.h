/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_FILE_QUALITY_MAPPING_H_
#define _FG_FILE_QUALITY_MAPPING_H_

// Global include needed (it defines the parameters of the build)
#include "fgBuildConfig.h"

#include <map>
#include <string>

#include "Hardware\fgQualityTypes.h"

#define FG_FILE_QUALITY_MAPPING_NAME "FileQualityMap"

/*
 *
 */
class fgFileQualityMapping {
public:
	// Default empty constructor for file quality mapping object
	fgFileQualityMapping() {
		m_filePath.clear();
		m_fileMapping.clear();
	}

	// Default empty destructor for file quality mapping object
	~fgFileQualityMapping() {
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
		m_fileMapping[(int)FG_QUALITY_UNIVERSAL] = path;
	}
	// Set file path to this resource
	virtual void setFilePath(std::string& path) {
		m_filePath.clear();
		m_filePath = path;
		m_fileMapping[(int)FG_QUALITY_UNIVERSAL] = path;
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
	virtual void setFilePath(const char *path, fgQuality quality) {
		if(!path)
			return;
		m_fileMapping[(int)quality] = path;
		if(quality == FG_QUALITY_UNIVERSAL)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}
	// Set file path to this resource
	virtual void setFilePath(std::string& path, fgQuality quality) {
		m_fileMapping[(int)quality] = path;
		if(quality == FG_QUALITY_UNIVERSAL)
			m_filePath = path;
		else if(m_filePath.empty())
			m_filePath = path;
	}

	// Get resource file path string
	std::string getFilePath(fgQuality quality) const {
		 // this lazy cast is ok - non-const version does not modify anything
		return (const_cast<fgFileQualityMapping*>(this)->getFilePath(quality));
	}

	// Get reference to resource file path string
	std::string& getFilePath(fgQuality quality) {
		if(m_fileMapping.find((int)quality) == m_fileMapping.end()) {
			return m_filePath;
		}
		return m_fileMapping[(int)quality];
	}

	// Get resource file path as C-like string (char array)
	const char* getFilePathStr(fgQuality quality) {
		if(m_fileMapping.find((int)quality) == m_fileMapping.end()) {
			return m_filePath.c_str();
		}
		return m_fileMapping[(int)quality].c_str();
	}
protected:
	// File mapping, the key is int (quality)
	std::map<int, std::string>	m_fileMapping;
	// File path as separate string (by default this is for universal quality)
	std::string					m_filePath;
};

#endif /* _FG_FILE_QUALITY_MAPPING_H_ */
