/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_H_
#define _FG_RESOURCE_H_

#include "fgCommon.h"
#include "Hardware/fgQualityTypes.h"

#include <string>
#include <ctime>
#include <cstring>

// A resource handle is define as an unsigned integer
#ifndef FG_RHANDLE
#define FG_RHANDLE unsigned int
#endif

#ifndef FG_INVALID_RHANDLE
// All bits filled defines an invalid resource handle
#define FG_INVALID_RHANDLE			0xFFFFFFFFUL
#define FG_IS_INVALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? true : false)
#define FG_IS_VALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? false : true)
#endif

class fgResourceManager;
class fgResourceGroup;

// Maximum length of the path string for resource file
#define FG_RESOURCE_PATH_MAX	FG_PATH_MAX

#define FG_RESOURCE_INVALID_NAME				"Invalid"
#define FG_RESOURCE_SOUND_NAME					"Sound"
#define FG_RESOURCE_MUSIC_NAME					"Music"
#define FG_RESOURCE_3D_MODEL_NAME				"3DModel"
#define FG_RESOURCE_TEXTURE_NAME				"Texture"
#define FG_RESOURCE_FONT_NAME					"Font"
#define FG_RESOURCE_SAVE_FILE_NAME				"SaveFile"
#define FG_RESOURCE_GUI_STRUCTURE_SHEET_NAME 	"GuiStructureSheet"
#define FG_RESOURCE_GUI_STYLE_SHEET_NAME		"GuiStyleSheet"
#define FG_RESOURCE_SHADER_NAME					"Shader"
#define FG_RESOURCE_SCENE_NAME					"Scene"
#define FG_RESOURCE_SCRIPT_NAME					"Script"
#define FG_RESOURCE_GROUP_NAME					"ResourceGroup"
#define FG_RESOURCE_VARIA_NAME					"Varia"
#define FG_RESOURCE_BINARY_NAME 				"Binary"
#define FG_RESOURCE_LIBRARY_NAME 				"Library"
#define FG_RESOURCE_PLUGIN_NAME 				"Plugin"
#define FG_RESOURCE_CUSTOM_NAME 				"Custom"
#define FG_RESOURCE_ZIP_PACK_NAME				"ZipPack"

// Enum type holding all possible resource types
// used in the game engine
enum fgResourceType {
	FG_RESOURCE_INVALID,
	FG_RESOURCE_SOUND,
	FG_RESOURCE_MUSIC,
	FG_RESOURCE_3D_MODEL,
	FG_RESOURCE_TEXTURE,
	FG_RESOURCE_FONT,
	FG_RESOURCE_SAVE_FILE,
	FG_RESOURCE_GUI_STRUCTURE_SHEET,
	FG_RESOURCE_GUI_STYLE_SHEET,
	FG_RESOURCE_SHADER,
	FG_RESOURCE_SCENE,
	FG_RESOURCE_SCRIPT,
	FG_RESOURCE_GROUP,
	FG_RESOURCE_VARIA,
	FG_RESOURCE_BINARY,
	FG_RESOURCE_LIBRARY,
	FG_RESOURCE_PLUGIN,
	FG_RESOURCE_CUSTOM,
	FG_RESOURCE_ZIP_PACK,
	
	FG_NUM_RESOURCE_BASIC_TYPES,

	FG_RESOURCE_RESERVED1,
	FG_RESOURCE_RESERVED2,
	FG_RESOURCE_RESERVED3,
	FG_RESOURCE_RESERVED4,
	FG_RESOURCE_RESERVED5,
	FG_RESOURCE_RESERVED6,

	FG_NUM_RESOURCE_TYPES
};

// Name (string version) for the resource low priority enum
#define FG_RES_PRIORITY_LOW_NAME	"Low"
// Name (string version) for the resource medium priority enum
#define FG_RES_PRIORITY_MEDIUM_NAME "Medium"
// Name (string version) for the resource high priority enum
#define FG_RES_PRIORITY_HIGH_NAME	"High"

// Enum for resource priority (low, medium, high, ...)
enum fgResPriorityType
{
	FG_RES_PRIORITY_INVALID = -1,

	FG_RES_PRIORITY_LOW = 0,
	FG_RES_PRIORITY_MEDIUM = 1,
	FG_RES_PRIORITY_HIGH = 2,

	FG_RES_PRIORITY_RESERVED1 = 3,
	FG_RES_PRIORITY_RESERVED2 = 4,
	FG_RES_PRIORITY_RESERVED3 = 5
};

/*
 * Base class for resource
 */
class fgResource 
{
	friend class fgResourceManager;
	friend class fgResourceGroup;
public:
	// Base constructor of the resource object
	fgResource()	{  clear();  }
	// Base constructor with additional parameter (path)
	fgResource(const char *path) { clear(); setFilePath(path); };
	// Base constructor with additional parameter (path)
	fgResource(std::string& path) { clear(); setFilePath(path); };
	// Base destructor of the resource object
	~fgResource()	{ destroy(); }

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);
	// Create and destroy functions.  Note that the create() function of the
	// derived class does not have to exactly match the base class.  No assumptions
	// are made regarding parameters.
	// create() function should simply be overloaded to call any proper loading function,
	// which will load/interpret data from file in ROM and place it in RAM memory.
	virtual bool create(void) = 0;
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void) { clear(); };
	// Dispose and recreate must be able to discard and then completely recreate
	// the data contained in the class with no additional parameters
	// This functions should NOT be overloaded to have different number of parameters.
	virtual bool recreate(void) = 0;
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void) = 0;

	// Return the size of the data actually loaded inside the class
	virtual size_t getSize(void) const { return m_size; }
	// Return true if the data exists (it's loaded and ready)
	virtual bool isDisposed(void) const = 0;

	// These functions set the parameters by which the sorting operator determines
	// in what order resources are discarded

	// Set the resource priority
	void setPriority(fgResPriorityType priority)		{  m_priority = priority;  }
	// Get the resource priority
	fgResPriorityType getPriority() const			{  return m_priority;  }

	// Set the resource quality
	inline void setQuality(fgQuality quality)		{  m_quality = quality;  }
	// Get the resource quality
	fgQuality getQuality() const			{  return m_quality;  }

	// Get the resource type id
	fgResourceType getResourceType() const			{  return m_resType;  }
protected:
	// Set the reference counter for the resource
	void setReferenceCount(unsigned int nCount)	{  m_nRefCount = nCount;  }
public:
	// Return the current hit of the reference counter for the resource
	unsigned int getReferenceCount(void) const	{  return m_nRefCount;  }
	// Check if the resource is locked (reference counter is not zero)
	bool isLocked(void) const					{  return (m_nRefCount > 0) ? true : false;  }

	// Set the last access time
	void setLastAccess(time_t lastAccess)		{  m_lastAccess = lastAccess;  }
	// Return the current access time of the resource
	time_t getLastAccess(void) const				{  return m_lastAccess;  }

	// Set file path to this resource
	virtual void setFilePath(const char *path) {
		m_filePath.clear();
		m_filePath = path;
	}
	// Set file path to this resource
	virtual void setFilePath(std::string& path) {
		m_filePath.clear();
		m_filePath.append(path, 0, FG_RESOURCE_PATH_MAX);
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

	// Set resource name (string TAG/ID)
	inline void setResourceName(const char *name) {
		m_resourceName.clear();
		m_resourceName = name;
	}
	// Set resource name (string TAG/ID)
	inline void setResourceName(std::string& name) {
		m_resourceName.clear();
		m_resourceName.append(name);
	}

	// Get resource name string
	std::string getResourceName(void) const {
		return m_resourceName;
	}
	// Get reference to resource name string
	std::string& getResourceName(void) {
		return m_resourceName;
	}
	// Get resource name (TAG/string ID) as C-like string (char array)
	const char* getResourceNameStr(void) const {
		return m_resourceName.c_str();
	}

	// The less-than operator defines how resources get sorted for discarding.
	virtual bool operator < (fgResource& container);
	// The greater-than operator is used for comparison (eg. while sorting)
	virtual bool operator > (fgResource& container);

	// Well using reference count as simple as below is not recommended, it is more difficult
	// to handle in the end, dims the code etc., can cause many problems. Need to migrate to
	// smart pointers... using boost or some implementation #FIXME #P3 #TODO
protected:
	// Increase the reference count
	inline unsigned int upRef(void)		{ m_nRefCount++; return m_nRefCount; }
	// Decrease the reference count
	inline unsigned int downRef(void)	{ if(m_nRefCount > 0) m_nRefCount--; return m_nRefCount; }

	// Lock the resource (reference counter +1)
	virtual unsigned int Lock(void) { return upRef(); }
	// Unlock the resource (reference counter -1)
	virtual unsigned int Unlock(void) { return downRef(); }
	// Unlock completely the resource (reference counter = 0) #NOTSAFE #FIXME
	virtual void ZeroLock(void) { m_nRefCount = 0; }
	// Set the resource handle ID out front (internal use, restricted)
	void setResourceHandle(FG_RHANDLE handle) {
		m_handle = handle;
	}
public:
	// Return the resource handle ID
	FG_RHANDLE getHandle(void) const {
		return m_handle;
	}
protected:
	// Unique handle number (Resource Handle)
	FG_RHANDLE			m_handle;
	// Priority of this resource
	fgResPriorityType	m_priority;
	// Quality of the resource
	fgQuality			m_quality;
	// Resource type
	fgResourceType		m_resType;
	// Number of references to this resource
	unsigned int		m_nRefCount;
	// Time of last access, may become handy #TESTME
	time_t				m_lastAccess;
	// File path (can be relative) to file holding data #FIXME
	std::string			m_filePath;
	// Is the resource loaded and ready to be used in program?
	bool				m_isReady;
	// Size in bytes of the loaded data
	size_t				m_size;
	// Name of the resource, string ID
	std::string			m_resourceName;

};

#endif /* _FG_RESOURCE_H_ */
