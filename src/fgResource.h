/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#ifndef _FG_RESOURCE_H_
#define _FG_RESOURCE_H_

#include "fgCommon.h"
#include "Hardware/fgQualityTypes.h"

#include <string>
#include <ctime>
#include <cstring>

#include "fgHandle.h"
#include "fgFileQualityMapping.h" // #FIXME

#ifndef FG_FACTORY_CREATE_FUNCTION
#define FG_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * __stdcall createResource(void) { return new CREATETYPE(); }
#endif

#ifndef FG_RESOURCE_FACTORY_CREATE_FUNCTION
#define FG_RESOURCE_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fgResource * __stdcall createResource(void) { return new CREATETYPE(); }
#endif

// Empty structure for resource tag
struct fgTagResource  {  };
// Special handle type for resource
typedef fgHandle<fgTagResource> fgResourceHandle;

#ifndef FG_RHANDLE
#define FG_RHANDLE fgResourceHandle
#endif

class fgResourceManager;
class fgResourceGroup;

// Maximum length of the path string for resource file
#define FG_RESOURCE_PATH_MAX	FG_PATH_MAX

#define FG_RESOURCE_INVALID_TEXT				"Invalid"
#define FG_RESOURCE_SOUND_TEXT					"Sound"
#define FG_RESOURCE_MUSIC_TEXT					"Music"
#define FG_RESOURCE_3D_MODEL_TEXT				"3DModel"
#define FG_RESOURCE_TEXTURE_TEXT				"Texture"
#define FG_RESOURCE_FONT_TEXT					"Font"
#define FG_RESOURCE_SAVE_FILE_TEXT				"SaveFile"
#define FG_RESOURCE_GUI_STRUCTURE_SHEET_TEXT 	"GuiStructureSheet"
#define FG_RESOURCE_GUI_STYLE_SHEET_TEXT		"GuiStyleSheet"
#define FG_RESOURCE_SHADER_TEXT					"Shader"
#define FG_RESOURCE_SCENE_TEXT					"Scene"
#define FG_RESOURCE_SCRIPT_TEXT					"Script"
#define FG_RESOURCE_GROUP_TEXT					"ResourceGroup"
#define FG_RESOURCE_VARIA_TEXT					"Varia"
#define FG_RESOURCE_BINARY_TEXT 				"Binary"
#define FG_RESOURCE_LIBRARY_TEXT 				"Library"
#define FG_RESOURCE_PLUGIN_TEXT 				"Plugin"
#define FG_RESOURCE_CUSTOM_TEXT 				"Custom"
#define FG_RESOURCE_ZIP_PACK_TEXT				"ZipPack"

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

/*
 *
 */
inline fgResourceType _FG_RESOURCE_TYPE_FROM_TEXT(const char* text) {
	
	if(!text)
		return FG_RESOURCE_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_INVALID);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SOUND);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_MUSIC);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_3D_MODEL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_TEXTURE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_FONT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SAVE_FILE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_GUI_STRUCTURE_SHEET);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_GUI_STYLE_SHEET);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SHADER);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SCENE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SCRIPT);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_GROUP);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_VARIA);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_BINARY);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_LIBRARY);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_PLUGIN);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_CUSTOM);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_ZIP_PACK);
	return FG_RESOURCE_INVALID;
}

#define FG_RESOURCE_TYPE_FROM_TEXT(text) _FG_RESOURCE_TYPE_FROM_TEXT(text)

// Text (string version) for the resource low priority enum
#define FG_RES_PRIORITY_LOW_TEXT		"low"
// Text (string version) for the resource medium priority enum
#define FG_RES_PRIORITY_MEDIUM_TEXT		"medium"
// Text (string version) for the resource high priority enum
#define FG_RES_PRIORITY_HIGH_TEXT		"high"
// Text (string version_ for the resource invalid priority enum
#define FG_RES_PRIORITY_INVALID_TEXT	"invalid"

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

// Convert text (literal) to corresponding enum value
inline fgResPriorityType _FG_RES_PRIORITY_FROM_TEXT(const char* text) {
	if(!text)
		return FG_RES_PRIORITY_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RES_PRIORITY_INVALID);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RES_PRIORITY_LOW);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RES_PRIORITY_MEDIUM);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_RES_PRIORITY_HIGH);
	return FG_RES_PRIORITY_INVALID;
}

#define FG_RES_PRIORITY_FROM_TEXT(text) _FG_RES_PRIORITY_FROM_TEXT(text)

/*
 * Base class for resource
 */
class fgResource : public fgFileQualityMapping
{
	friend class fgResourceManager;
	friend class fgResourceGroup;
public:
	// Base constructor of the resource object
	fgResource();
	// Constructor with additional parameter (path)
	fgResource(const char *path);
	// Constructor with additional parameter (path)
	fgResource(std::string& path);
	// Base destructor of the resource object
	virtual ~fgResource()	{ destroy(); }

	// Clears the class data, this actually does not free allocated memory,
	// just resets base class attributes
	virtual void clear(void);
	// Create and destroy functions.  Note that the create() function of the
	// derived class does not have to exactly match the base class.  No assumptions
	// are made regarding parameters.
	// create() function should simply be overloaded to call any proper loading function,
	// which will load/interpret data from file in ROM and place it in RAM memory.
	virtual fgBool create(void) = 0;
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void) { clear(); };
	// Dispose and recreate must be able to discard and then completely recreate
	// the data contained in the class with no additional parameters
	// This functions should NOT be overloaded to have different number of parameters.
	virtual fgBool recreate(void) = 0;
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void) = 0;

	// Return the size of the data actually loaded inside the class
	virtual size_t getSize(void) const { return m_size; }
	// Return true if the data exists (it's loaded and ready)
	virtual fgBool isDisposed(void) const = 0;

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
	fgBool isLocked(void) const					{  return (m_nRefCount > 0) ? FG_TRUE : FG_FALSE;  }

	// Set the last access time
	void setLastAccess(time_t lastAccess)		{  m_lastAccess = lastAccess;  }
	// Return the current access time of the resource
	time_t getLastAccess(void) const				{  return m_lastAccess;  }

	// Set file path to this resource #FIXME
	virtual void setFilePath(const char *path) {
		fgFileQualityMapping::setFilePath(path);
	}
	// Set file path to this resource #FIXME
	virtual void setFilePath(std::string& path) {
		fgFileQualityMapping::setFilePath(path);
	}
	// Set file path to this resource #FIXME
	virtual void setFilePath(const char *path, fgQuality quality) {
		fgFileQualityMapping::setFilePath(path, quality);
	}
	// Set file path to this resource #FIXME
	virtual void setFilePath(std::string& path, fgQuality quality) {
		fgFileQualityMapping::setFilePath(path, quality);
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
	// Is the resource loaded and ready to be used in program?
	fgBool				m_isReady;
	// Size in bytes of the loaded data
	size_t				m_size;
	// Name of the resource, string ID
	std::string			m_resourceName;

};

#endif /* _FG_RESOURCE_H_ */
