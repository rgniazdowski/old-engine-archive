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

#include "fgCommon.h"

#include <string>
#include <ctime>
#include <cstring>

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

#define FG_RES_PRIORITY_LOW_NAME "Low"
#define FG_RES_PRIORITY_MEDIUM_NAME "Medium"
#define FG_RES_PRIORITY_HIGH_NAME "High"

/*
 * Base class for resource
 */
class fgResource 
{
public:
	enum fgResPriorityType
	{
		FG_RES_PRIORITY_LOW = 0,
		FG_RES_PRIORITY_MEDIUM = 1,
		FG_RES_PRIORITY_HIGH = 2,

		FG_RES_PRIORITY_RESERVED1 = 3,
		FG_RES_PRIORITY_RESERVED2 = 4,
		FG_RES_PRIORITY_RESERVED3 = 5,

		FG_RES_PRIORITY_INVALID = -1,
	};

	//
	fgResource()	{  clear();  }
	//
	~fgResource()	{ destroy(); }

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);

	// Create and destroy functions.  Note that the create() function of the
	// derived class does not have to exactly match the base class.  No assumptions
	// are made regarding parameters.
	// create() function should simply be overloaded to call any proper loading function,
	// which will load/interpret data from file in ROM and place it in RAM memory.
	virtual bool create(void) = 0;
	virtual void destroy(void) { };

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
	inline void setPriority(fgResPriorityType priority)		{  m_priority = priority;  }
	// Get the resource priority
	inline fgResPriorityType getPriority() const			{  return m_priority;  }

	// Get the resource type id
	inline fgResourceType getResourceType() const			{  return m_resType;  }

	inline void setReferenceCount(unsigned int nCount)	{  m_nRefCount = nCount;  }
	inline unsigned int getReferenceCount(void) const	{  return m_nRefCount;  }
	inline bool isLocked(void) const					{  return (m_nRefCount > 0) ? true : false;  }

	inline void setLastAccess(time_t lastAccess)		{  m_lastAccess = lastAccess;  }
	inline time_t getLastAccess(void) const				{  return m_lastAccess;  }

	// Set file path to this resource
	inline void setFilePath(const char *path) {
		strncpy(m_filePath, path, FG_RESOURCE_PATH_MAX-1);
	}

	// Set resource name (string ID)
	inline void setResourceName(const char *name) {
		m_resourceName = name;
	}

	// Set resource name (string ID)
	inline void setResourceName(std::string name) {
		m_resourceName = name;
	}

	// The less-than operator defines how resources get sorted for discarding.
	virtual bool operator < (fgResource& container);

	// Well using reference count as simple as below is not recommended, it is more difficult
	// to handle in the end, dims the code etc., can cause many problems. Need to migrate to
	// smart pointers... using boost or some implementation #FIXME #P3 #TODO
protected:
	// Increase the reference count
	inline void upRef(void)		{ m_nRefCount++; }
	// Decrease the reference count
	inline void downRef(void)	{ if(m_nRefCount > 0) m_nRefCount--; }

	inline void Lock(void) { upRef(); }
	inline void Unlock(void) { downRef(); }

protected:
	// Unique handle number (Resource Handle)
	FG_RHANDLE			m_handle;
	// Priority of this resource
	fgResPriorityType	m_priority;
	// Resource type
	fgResourceType		m_resType;
	// Number of references to this resource
	unsigned int		m_nRefCount;
	// Time of last access, may become handy
	time_t				m_lastAccess;
	// File path (can be relative) to file holding data
	char				m_filePath[FG_RESOURCE_PATH_MAX];
	// Is the resource loaded and ready to be used in program?
	bool				m_isReady;
	// Size in bytes of the loaded data
	size_t				m_size;
	// Name of the resource, string ID
	std::string			m_resourceName;

};

#endif
