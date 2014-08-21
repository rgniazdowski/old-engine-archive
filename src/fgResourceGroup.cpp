/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceGroup.h"
#include "fgResourceFactory.h"
#include "Graphics/Textures/fgTextureResource.h"
#include "GUI/fgFontResource.h"

// Base constructor of the resource group content handler object
fgResourceGroupContentHandler::fgResourceGroupContentHandler() : m_resourceGroup(NULL),
	m_resType(FG_RESOURCE_INVALID),
	m_resourcePtr(NULL),
	m_curResName(NULL),
	m_isMapped(FG_FALSE),
	m_isFileQualityMapTag(FG_FALSE),
	m_curResPriority(FG_RES_PRIORITY_INVALID)
{
}
// Base destructor of the resource group content handler object
fgResourceGroupContentHandler::~fgResourceGroupContentHandler()
{
	while(!m_elemStack.empty())
		m_elemStack.pop();
}

void fgResourceGroupContentHandler::endElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, int depth)
{
	m_elemStack.pop();
	fgResourceType rtype = FG_RESOURCE_TYPE_FROM_TEXT(localName);
	// If the resource was created...
	if(m_resourcePtr && (rtype != FG_RESOURCE_GROUP && rtype != FG_RESOURCE_INVALID)) {
		m_resourcePtr->setPriority(m_curResPriority);
		if(m_curResName)
			m_resourcePtr->setResourceName(m_curResName);
		// ...then it can be added to the Resource Groups' list.
		this->m_resourceGroup->getRefResourceFiles().push_back(m_resourcePtr);
		FG_WriteLog("PUSH RES: Resource name: '%s'", m_curResName);
		m_resType = FG_RESOURCE_INVALID;
		m_resourcePtr = NULL;
		m_isMapped = FG_FALSE;
		m_isFileQualityMapTag = FG_FALSE;
		m_curResName = NULL;
		m_curResPriority = FG_RES_PRIORITY_INVALID;
	}
	FG_WriteLog("END ELEMENT: %s\n", localName);
}

/*
 * Receive notification of the start of an element.
 * This function will add to the specified resource group any identified resources.
 */
void fgResourceGroupContentHandler::startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth)
{
	FG_WriteLog("START ELEMENT: %s", localName);
	// Sound
	// Music
	// 3DModel
	// Texture
	// Font
	// GuiStructureSheet
	// GuiStyleSheet
	// Shader
	// Scene
	// Script
	// SaveFile
	// Varia
	// Binary
	// ZipPack
	// Resource Group ?
	m_elemStack.push(elementPtr);
	
	m_resType = FG_RESOURCE_TYPE_FROM_TEXT(localName);
	// Handling for resource group tag type - in most cases it's the root node.
	// #TODO - there needs to be a security check - checking if the resource group does not
	// contain links to other resource group files - this is not support and not needed.
	if(m_resType == FG_RESOURCE_GROUP) {
		fgXMLAttribute *attribute = firstAttribute;
		// #FIXME #P5 - well looks like this could use some kind of error checking, maybe...
		while(attribute) {
			const char *attrname = attribute->Name();
			const char *attrvalue = attribute->Value();
			if(strnicmp(attrname, "name", 4) == 0) {
				m_resourceGroup->setResourceName(attrvalue);
				FG_WriteLog("RESOURCE GROUP: NAME: '%s'", attrvalue);
			} else if(strnicmp(attrname, "priority", 8) == 0) {
				m_resourceGroup->setPriority(FG_RES_PRIORITY_FROM_TEXT(attrvalue));
			}
			attribute = attribute->Next();
		}
	} else if(m_resType == FG_RESOURCE_INVALID) {
		if(strnicmp(localName, FG_FILE_QUALITY_MAPPING_TEXT, strlen(FG_FILE_QUALITY_MAPPING_TEXT)) == 0) {			
			m_isFileQualityMapTag = FG_TRUE;
		} else if(true) {
		}
	}

	// Here are common attributes for every resource tag in resource group
	// Path to the resource
	const char *resPath = NULL;
	// Resource name (ID/TAG string) 
	const char *resName = NULL;
	// Priority for the resource stored as a string
	const char *resPriorityStr = NULL;
	// Quality for the resource stored as a string
	const char *resQualityStr = NULL;
	// Pointer to the first attribute for checking
	fgXMLAttribute *attribute = firstAttribute;
	if(m_resType != FG_RESOURCE_GROUP && (m_resType != FG_RESOURCE_INVALID || m_isFileQualityMapTag)) {
		while(attribute) {
			const char *attrname = attribute->Name();
			const char *attrvalue = attribute->Value();
			if(strnicmp(attrname, "path", 4) == 0) {
				resPath = attrvalue;
			} else if(strnicmp(attrname, "name", 4) == 0) {
				resName = attrvalue;
				m_curResName = resName;
			} else if(strnicmp(attrname, "priority", 8) == 0) {
				resPriorityStr = attrvalue;
			} else if(strnicmp(attrname, "quality", 7) == 0) {
				resQualityStr = attrvalue;
			} else if(strnicmp(attrname, "ismapped", 8) == 0) {
				m_isMapped = FG_BOOL_FROM_TEXT(attrvalue);
			}
			if(!resQualityStr)
				resQualityStr = "universal";
			attribute = attribute->Next();
		}
	}
	if(resPriorityStr)
		m_curResPriority = FG_RES_PRIORITY_FROM_TEXT(resPriorityStr);
	if(m_resType == FG_RESOURCE_INVALID) {
		if(m_resourcePtr && m_isFileQualityMapTag && resPath) {
			FG_WriteLog("Setting path: '%s', for resource: '%s', quality='%s'", resPath, m_curResName, resQualityStr);
			m_resourcePtr->setFilePath(resPath, FG_QUALITY_FROM_TEXT(resQualityStr));
		}
		return;
	}

	if(!fgResourceFactory::isRegistered(m_resType)) {
		m_resourcePtr = NULL;
	} else {
		m_resourcePtr = fgResourceFactory::createResource(m_resType);
		m_resourcePtr->setFilePath(resPath);
	}
}

/*******************************************************/

/*
 * Base constructor of the resource group object
 */
fgResourceGroup::fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::fgResourceGroup(); constructor");
	clear();
}

/*
 * Base destructor of the resource group object
 */
fgResourceGroup::~fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::~fgResourceGroup(); destructor");
	destroy();
}

/*
 * Clears the class data, this actually does not free allocated memory, just resets base class attributes
 */
void fgResourceGroup::clear(void)
{
	FG_WriteLog("fgResourceGroup::clear();");
	fgResource::clear();
	m_rHandles.clear_optimised();
	m_resourceFiles.clear_optimised();
	m_resType = FG_RESOURCE_GROUP;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
fgBool fgResourceGroup::create(void)
{
	FG_WriteLog("fgResourceGroup::create();");
	if(m_resourceFiles.empty())
		return FG_FALSE;
	fgBool status = FG_TRUE;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->create()) {
			status = FG_FALSE;
		}
	}
	return status;
}

/*
 * Destroy all loaded data including additional metadata (called with deconstructor)
 */
void fgResourceGroup::destroy(void)
{
	FG_WriteLog("fgResourceGroup::destroy();");
	ZeroLock();
	dispose();
	clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool fgResourceGroup::recreate(void)
{
	FG_WriteLog("fgResourceGroup::recreate();");
	if(m_resourceFiles.empty())
		return FG_FALSE;
	fgBool status = FG_TRUE;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->recreate()) {
			status = FG_FALSE;
		}
	}
	return status;
}

/*
 * Dispose completely of the all loaded data, free all memory
 */
void fgResourceGroup::dispose(void)
{
	FG_WriteLog("fgResourceGroup::~dispose();");
	if(m_resourceFiles.empty())
		return;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->dispose();
	}
}

/*
 * Check if resource is disposed (not loaded yet or disposed after)
 */
fgBool fgResourceGroup::isDisposed(void) const
{
	if(m_resourceFiles.empty())
		return FG_TRUE;
	fgBool status = FG_TRUE;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->isDisposed())
			status = FG_FALSE;
	}
	return status;
}

/*
 * This will parse/load xml group config file. It wont
 * load or allocate any data - this is for 'create' to do.
 * This function will return false if file path is not set.
 */
fgBool fgResourceGroup::preLoadConfig(void)
{
	if(m_filePath.empty())
		return FG_FALSE;
	m_xmlParser = new fgXMLParser();
	fgResourceGroupContentHandler *contentHandler = new fgResourceGroupContentHandler();
	contentHandler->setResourceGroupPointer(this);
	m_xmlParser->setContentHandler(contentHandler);
	if(!m_xmlParser) {
		// #TODO #P2 error messages 
		return FG_FALSE;
	}
	if(!m_xmlParser->loadXML(m_filePath.c_str())) {
		return FG_FALSE;
	}
	m_xmlParser->parseWithHandler();
	delete m_xmlParser;
	delete contentHandler;
	m_xmlParser = NULL;
	return FG_TRUE;
}

/*
 * Refresh arrays holding handles and resource pointers within this group
 */
void fgResourceGroup::refreshArrays(void)
{
	m_rHandles.clear();
	if(m_resourceFiles.empty())
		return;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		m_rHandles.push_back((*it)->getHandle());
	}
}

/*
 * Lock the resource (reference counter +1)
 */
unsigned int fgResourceGroup::Lock(void)
{
	if(m_resourceFiles.empty())
		return -1;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->Lock();
	}
	return upRef();
}

/*
 * Unlock the resource (reference counter -1)
 */
unsigned int fgResourceGroup::Unlock(void)
{
	if(m_resourceFiles.empty())
		return -1;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->Unlock();
	}
	return downRef();
}

/*
 * Unlock completely the resource (reference counter = 0)
 */
void fgResourceGroup::ZeroLock(void)
{
	if(m_resourceFiles.empty())
		return;
	for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->ZeroLock();
	}
	fgResource::ZeroLock();
}
