/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_GROUP_H_
#define _FG_RESOURCE_GROUP_H_

//#include <utility>

#include "fgCommon.h"
#include "fgResource.h"
#include "fgXMLParser.h"

#include <cstdlib>

// -----------------------------
// Predefined classes

class fgResourceGroup;
class fgResourceGroupContentHandler;

// #FIXME #P2 well this seems... wrong. Moving on...
namespace FG_GFX {
	class fgGfxModelResource;
};

class fgTextureResource;
class fgFontResource;

// -----------------------------

/*
 * This is ResourceGroup content handler helper class used for deep/recursive automatic xml parsing (SAXP alike).
 * This resource group handler will be somehow universal for every resource group. Which means that there need
 * to be some other helper functions/classes to properly handle all current and future data/resource types.
 * #TODO #FIXME #P3 #CONTINUE
 */
class fgResourceGroupContentHandler : public fgXMLDefaultHandler {
	friend class fgResourceGroup;
private:
	fgResourceGroup *m_resourceGroup;
	fgResourceType m_resType;
	fgResource *m_resourcePtr;

	fgResourceGroupContentHandler() : m_resourceGroup(NULL), m_resType(FG_RESOURCE_INVALID), m_resourcePtr(NULL)
	{
	}

	~fgResourceGroupContentHandler()
	{
	}
protected:
	void setResourceGroupPointer(fgResourceGroup *group) { m_resourceGroup = group; }
public:
	// Receive notification of the end of the document.
	virtual void endDocument(fgXMLDocument *document)
	{
		// End document
	}

    // Receive notification of the end of an element.
	virtual void endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth = -1)
	{
		// End of element
	}

	// Receive notification of the beginning of the document.
	virtual void startDocument(fgXMLDocument *document)
	{
		// Start document
	}

	// Receive notification of the start of an element.
	virtual void startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth = -1);

	// Receive notification of character data inside an element or comment
	virtual void characters(const char ch[], int start, int length)
	{
		// Characters - wont be needed
		//printf("characters: n: %d, val: '%s'\n", length, ch);
	}

};

// This is resource group and it is treated like normal resource.
// The idea behind is that when ResourceGroup  is loaded/released 
// it will also release  all binded resources - however only when
// all resource inside  the group have reference count equal zero
// Also it  needs to  work in  a way  that ResourceGroup can lock 
// resources blocking their separate removal/release even if some
// resources have reference count equal zero.
//
// In other words this class binds separate resources into one.
// ResourceGroup files are loaded via xml configs from predefined
// location. The config files will specify the type and  location
// resources that will be part of this group/union. Additional 
// parameters include things like priority, tags, etc.
//
// Hint: Use smart pointers in the future - from boost library or
// own proper implementation
class fgResourceGroup : public fgResource {
	friend class fgResourceGroupContentHandler;
public:
	typedef fgArrayVector<fgResource *>::iterator ResVecIt;
	// Base constructor of the resource group object
	fgResourceGroup();
	// Base destructor of the resource group object
	~fgResourceGroup();

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);
	// Create function loads/interprets data from file in ROM and place it in RAM memory.
	virtual bool create(void);
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void);
	// Reloads any data, recreates the resource (refresh)
	virtual bool recreate(void);
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void);
	// Check if resource is disposed (not loaded yet or disposed after)
	virtual bool isDisposed(void) const;

	// This will parse/load xml group config file. It wont
	// load or allocate any data - this is for 'create' to do.
	// This function will return false if file path is not set.
	virtual bool preLoadConfig(void);

	// Refresh arrays holding handles and resource pointers within this group
	virtual void refreshArrays(void);

	// Return reference to array of resource pointers (objects) within this resource group
	fgArrayVector<fgResource *>& getRefResourceFiles(void) {
		return m_resourceFiles;
	}
	// Return reference to array of resource handles within this resource group
	fgArrayVector<FG_RHANDLE>& getRefResourceHandles(void) {
		return m_rHandles;
	}

	// Lock the resource (reference counter +1)
	virtual unsigned int Lock(void);
	// Unlock the resource (reference counter -1)
	virtual unsigned int Unlock(void);
	// Unlock completely the resource (reference counter = 0) #NOTSAFE #FIXME
	virtual void ZeroLock(void);

protected:
	// List of all handles within this resource group
	fgArrayVector<FG_RHANDLE> m_rHandles;
	// List of all resource files 
	fgArrayVector<fgResource *> m_resourceFiles;

	// Parser for xml config files (here: resource group xml files)
	fgXMLParser *m_xmlParser;
};

#endif
