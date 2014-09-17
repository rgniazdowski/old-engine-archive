/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#ifndef _FG_RESOURCE_H_
#define _FG_RESOURCE_H_

#include "fgCommon.h"
#include "fgStatusReporter.h"
#include "Hardware/fgQualityTypes.h"

#include <string>
#include <ctime>
#include <cstring>

#include "fgDataObjectBase.h"
#include "Util/fgHandle.h"
#include "Util/fgTag.h"

class fgResourceManager;
class fgResourceGroup;
class fgResource;

#include "fgResourceFactoryTypes.h"

#define FG_TAG_RESOURCE_NAME	"Resource"
//#define FG_TAG_RESOURCE_ID		10 //#FIXME - something automatic maybe?
#define FG_TAG_RESOURCE			FG_TAG_TYPE(fgResource)

//FG_TAG_TEMPLATE(fgResource, FG_TAG_RESOURCE_NAME, FG_TAG_RESOURCE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fgResource, FG_TAG_RESOURCE_NAME);

// Special handle type for resource
typedef FG_TAG_RESOURCE fgResourceTag;
typedef fgHandle<fgResourceTag> fgResourceHandle;

#ifndef FG_RHANDLE
#define FG_RHANDLE fgResourceHandle
#endif

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
#define FG_RESOURCE_SHADER_TEXT					"Shader" // #FIXME
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
typedef unsigned int fgResourceType;

#define FG_RESOURCE_INVALID				0x0000
#define	FG_RESOURCE_SOUND				0x0AB0
#define	FG_RESOURCE_MUSIC				0x0AB1
#define	FG_RESOURCE_3D_MODEL			0x0AB2
#define	FG_RESOURCE_TEXTURE				0x0AB3
#define	FG_RESOURCE_FONT				0x0AB4
#define	FG_RESOURCE_SAVE_FILE			0x0AB5
#define	FG_RESOURCE_GUI_STRUCTURE_SHEET	0x0AB6
#define	FG_RESOURCE_GUI_STYLE_SHEET		0x0AB7
#define	FG_RESOURCE_SHADER				0x0AB8	// #FIXME
#define	FG_RESOURCE_SCENE				0x0AB9
#define	FG_RESOURCE_SCRIPT				0x0ABA
#define	FG_RESOURCE_GROUP				0x0ABB
#define	FG_RESOURCE_VARIA				0x0ABC
#define	FG_RESOURCE_BINARY				0x0ABD
#define	FG_RESOURCE_LIBRARY				0x0ABE
#define	FG_RESOURCE_PLUGIN				0x0ABF
#define	FG_RESOURCE_CUSTOM				0x0AC0
#define	FG_RESOURCE_ZIP_PACK			0x0AC1

#define FG_NUM_RESOURCE_BASIC_TYPES		(FG_RESOURCE_ZIP_PACK-FG_RESOURCE_SOUND)

#define FG_RESOURCE_RESERVED1			0x0ACA
#define FG_RESOURCE_RESERVED2			0x0ACB
#define FG_RESOURCE_RESERVED3			0x0ACC
#define FG_RESOURCE_RESERVED4			0x0ACD
#define FG_RESOURCE_RESERVED5			0x0ACE
#define FG_RESOURCE_RESERVED6			0x0ACF

#define FG_NUM_RESOURCE_TYPES			(1)

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
// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
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

// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
#define FG_RES_PRIORITY_FROM_TEXT(text) _FG_RES_PRIORITY_FROM_TEXT(text)

/*
 * Base class for resource
 */
class fgResource : public fgDataObjectBase<fgResourceHandle, fgQuality>, public fgStatusReporter<fgResourceTag>
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

protected:
	// Clears the class data, this actually does not free allocated memory,
	// just resets base class attributes
	virtual void clear(void);

public:
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

protected:
	/// Priority of this resource
	fgResPriorityType	m_priority;
	/// Quality of the resource
	fgQuality			m_quality;
	/// Resource type
	fgResourceType		m_resType;
	/// Number of references to this resource
	unsigned int		m_nRefCount;
	/// Time of last access, may become handy #TESTME
	time_t				m_lastAccess;
	/// Size in bytes of the loaded data
	size_t				m_size;
	/// Is the resource loaded and ready to be used in program?
	fgBool				m_isReady;
};

#endif /* _FG_RESOURCE_H_ */
