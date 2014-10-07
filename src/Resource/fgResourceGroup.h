/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_GROUP_H_
#define _FG_RESOURCE_GROUP_H_

#include "fgCommon.h"
#include "fgResource.h"
#include "fgResourceFactory.h"

#include <cstdlib>

#include "XML/fgXMLParser.h"
#include "XML/fgXMLDefaultHandler.h"

// -----------------------------
// Predefined classes

class fgResourceGroup;
class fgResourceGroupContentHandler;

// -----------------------------

/*
 * This is ResourceGroup content handler helper class used for deep/recursive
 * automatic xml parsing  (SAXP alike).  This resource group  handler will be
 * somehow universal for every resource group. Which means that there need to
 * be some other helper  functions/classes to properly handle all current and 
 * future data/resource types.
 * #TODO #FIXME #P3 #CONTINUE
 */
class fgResourceGroupContentHandler : public fgXMLDefaultHandler {
	friend class fgResourceGroup;
private:
	// Pointer to the resource group - this groups' xml config file is being parsed by this handler
	fgResourceGroup *m_resourceGroup;
	// Current resource type
	fgResourceType m_resType;
	// Current resource object pointer
	fgResource *m_resourcePtr;
	// Current resource priority
	fgResPriorityType m_curResPriority;
	// Is current resource tag mapped? (file names mapped to quality)
	fgBool m_isMapped;
	// Is current xml used for mapping file to quality?
	fgBool m_isFileQualityMapTag;
	// Element stack (not used yet, #FIXME)
	std::stack<fgXMLElement *> m_elemStack;

	// Base constructor of the resource group content handler object
	fgResourceGroupContentHandler();
	// Base destructor of the resource group content handler object
	virtual ~fgResourceGroupContentHandler();
protected:
	// Set pointer to resource group object - this group is being parsed
	void setResourceGroupPointer(fgResourceGroup *group) { m_resourceGroup = group; }

	fgBool loadResConfig(const char *path);
public:
	// Receive notification of the end of the document.
	virtual void endDocument(fgXMLDocument *document)
	{
		// End document
	}

    // Receive notification of the end of an element.
	virtual void endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth = 0);

	// Receive notification of the beginning of the document.
	virtual void startDocument(fgXMLDocument *document)
	{
		// Start document
	}

	// Receive notification of the start of an element.
	virtual void startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth = 0);

	// Receive notification of character data inside an element or comment
	virtual void characters(const char ch[], int start, int length, fgXMLNodeType nodeType, int depth = 0)
	{
		// Characters - wont be needed
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
// of resources that will be part of this group/union. Additional 
// parameters include things like priority, tags, etc.
//
// Hint: Use smart pointers in the future - from boost library or
// own proper implementation
class fgResourceGroup : public fgResource
{
	friend class fgResourceGroupContentHandler;
	friend class fgResourceManager;
public:
	typedef fgVector<fgResource *>				rgResVec;
	typedef fgVector<FG_RHANDLE>				rgHandleVec;
	typedef fgVector<fgResource *>::iterator	rgResVecItor;
	typedef fgVector<FG_RHANDLE>::iterator		rgHandleVecItor;
	typedef fgVector<fgResource *>::const_iterator	rgResVecConstItor;
	typedef fgVector<FG_RHANDLE>::const_iterator	rgHandleVecConstItor;

public:
	// Base constructor of the resource group object
	fgResourceGroup();
	//
	fgResourceGroup(fgResourceFactory *resourceFactory);
	// Base destructor of the resource group object
	~fgResourceGroup();

	FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgResourceGroup)

	//
	void setResourceFactory(fgResourceFactory *resourceFactory);
	//
	fgResourceFactory *getResourceFactory(void) const;
protected:
	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);
public:
	// Create function loads/interprets data from file in ROM and place it in RAM memory.
	virtual fgBool create(void);
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void);
	// Reloads any data, recreates the resource (refresh)
	virtual fgBool recreate(void);
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void);
	// Check if resource is disposed (not loaded yet or disposed after)
	virtual fgBool isDisposed(void) const;

	// Return the size of the data actually loaded inside the class
	// For the resource group this allways returns zero
	virtual size_t getSize() const { return 0; }

	// This will parse/load xml group config file. It wont
	// load or allocate any data - this is for 'create' to do.
	// This function will return false if file path is not set.
	virtual fgBool preLoadConfig(void);

	// Refresh arrays holding handles and resource pointers within this group
	virtual void refreshArrays(void);

	// Return reference to array of resource pointers (objects) within this resource group
	rgResVec& getRefResourceFiles(void) {
		return m_resourceFiles;
	}
	// Return reference to array of resource handles within this resource group
	rgHandleVec& getRefResourceHandles(void) {
		return m_rHandles;
	}

protected:
	// Lock the resource (reference counter +1)
	virtual unsigned int Lock(void);
	// Unlock the resource (reference counter -1)
	virtual unsigned int Unlock(void);
	// Unlock completely the resource (reference counter = 0) #NOTSAFE #FIXME
	virtual void ZeroLock(void);

private:
	fgBool _parseIniConfig(void);

protected:
	// List of all handles within this resource group
	rgHandleVec m_rHandles;
	// List of all resource files 
	rgResVec m_resourceFiles;
	// Parser for xml config files (here: resource group xml files)
	fgXMLParser *m_xmlParser;
	// Resource factory
	fgResourceFactory *m_resourceFactory;

};

#endif /* _FG_RESOURCE_GROUP_H_ */
