/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgResourceGroup.h"
#include "fgResourceFactory.h"

#include "Util/fgPath.h"
#include "Util/fgConfig.h"
#include "Util/fgStrings.h"

/**********************************************************
 * RESOURCE GROUP CONTENT HANDLER - READING XML FILE
 */

/*
 * Base constructor of the resource group content handler object
 */
fgResourceGroupContentHandler::fgResourceGroupContentHandler() : m_resourceGroup(NULL),
	m_resType(FG_RESOURCE_INVALID),
	m_resourcePtr(NULL),
	m_curResName(NULL),
	m_isMapped(FG_FALSE),
	m_isFileQualityMapTag(FG_FALSE),
	m_curResPriority(FG_RES_PRIORITY_INVALID)
{
}

/*
 * Base destructor of the resource group content handler object
 */
fgResourceGroupContentHandler::~fgResourceGroupContentHandler()
{
	while(!m_elemStack.empty())
		m_elemStack.pop();
}

/*
 *
 */
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
		m_resType = FG_RESOURCE_INVALID;
		m_resourcePtr = NULL;
		m_isMapped = FG_FALSE;
		m_isFileQualityMapTag = FG_FALSE;
		m_curResName = NULL;
		m_curResPriority = FG_RES_PRIORITY_INVALID;
	}
	FG_LOG::PrintDebug("END ELEMENT: %s\n", localName);
}

/*
 * Receive notification of the start of an element.
 * This function will add to the specified resource group any identified resources.
 */
void fgResourceGroupContentHandler::startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth)
{
	FG_LOG::PrintDebug("START ELEMENT: %s", localName);
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
			if(strncasecmp(attrname, "name", 4) == 0) {
				m_resourceGroup->setResourceName(attrvalue);
			} else if(strncasecmp(attrname, "priority", 8) == 0) {
				m_resourceGroup->setPriority(FG_RES_PRIORITY_FROM_TEXT(attrvalue));
			}
			attribute = attribute->Next();
		}
	} else if(m_resType == FG_RESOURCE_INVALID) {
		if(strncasecmp(localName, FG_FILE_QUALITY_MAPPING_TEXT, strlen(FG_FILE_QUALITY_MAPPING_TEXT)) == 0) {
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
			if(strncasecmp(attrname, "path", 4) == 0) {
				resPath = attrvalue;
			} else if(strncasecmp(attrname, "name", 4) == 0) {
				resName = attrvalue;
				m_curResName = resName;
			} else if(strncasecmp(attrname, "priority", 8) == 0) {
				resPriorityStr = attrvalue;
			} else if(strncasecmp(attrname, "quality", 7) == 0) {
				resQualityStr = attrvalue;
			} else if(strncasecmp(attrname, "ismapped", 8) == 0) {
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
			FG_LOG::PrintDebug("Setting path: '%s', for resource: '%s', quality='%s'", resPath, m_curResName, resQualityStr);
			m_resourcePtr->setFilePath(resPath, FG_QUALITY_FROM_TEXT(resQualityStr));
		}
		return;
	}

	// Check if the create function for current resource type is registered.
	// Also ignore resource group type.
	if(!FG_ResourceFactory->isRegistered(m_resType) || m_resType == FG_RESOURCE_GROUP) {
		m_resourcePtr = NULL;
	} else {
		m_resourcePtr = FG_ResourceFactory->createResource(m_resType);
		m_resourcePtr->setFilePath(resPath);
	}
}

/*********************************************************/

/*
 * Base constructor of the resource group object
 */
fgResourceGroup::fgResourceGroup()
{
	FG_LOG::PrintDebug("fgResourceGroup::fgResourceGroup(); constructor");
	clear();
}

/*
 * Base destructor of the resource group object
 */
fgResourceGroup::~fgResourceGroup()
{
	FG_LOG::PrintDebug("fgResourceGroup::~fgResourceGroup(); destructor");
	destroy();
}

/*
 * Clears the class data, this actually does not free allocated memory, just resets base class attributes
 */
void fgResourceGroup::clear(void)
{
	FG_LOG::PrintDebug("fgResourceGroup::clear();");
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
	FG_LOG::PrintDebug("fgResourceGroup::create();");
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
	FG_LOG::PrintDebug("fgResourceGroup::destroy();");
	ZeroLock();
	dispose();
	clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool fgResourceGroup::recreate(void)
{
	FG_LOG::PrintDebug("fgResourceGroup::recreate();");
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
	FG_LOG::PrintDebug("fgResourceGroup::~dispose();");
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
	for(rgResVecConstItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->isDisposed())
			status = FG_FALSE;
	}
	return status;
}

/*
 *
 */
fgBool fgResourceGroup::_parseIniConfig(void)
{
	if(m_filePath.empty())
		return FG_FALSE;
	fgConfig *config = new fgConfig();
	config->load(m_filePath.c_str());
	fgCfgTypes::sectionMap &sectionMap = config->getRefSectionMap();
	if(sectionMap.empty()) {
		delete config;
		return FG_FALSE;
	}
	fgCfgTypes::sectionMapItor smit = sectionMap.begin(),
		end = sectionMap.end();
	for(;smit!=end;smit++)
	{
		fgCfgSection *section = smit->second;
		
		if(strncasecmp(section->name.c_str(), FG_RESOURCE_GROUP_TEXT, strlen(FG_RESOURCE_GROUP_TEXT)) == 0) {
			fgCfgParameter *param = NULL;
			if((param = section->getParameter("name")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_STRING)
					setResourceName(param->string);

				printf("RESOURCE GROUP NAME: %s\n", param->string);
			} else {
			}
			if((param = section->getParameter("priority")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_STRING)
					setPriority(FG_RES_PRIORITY_FROM_TEXT(param->string));
			} else {
			}
		} else {
			fgBool foundName = FG_TRUE, foundType = FG_TRUE, foundQuality = FG_TRUE, foundPath = FG_TRUE, foundPriority = FG_TRUE;
			std::string name;
			std::string path;
			fgResourceType type = FG_RESOURCE_INVALID;
			fgCfgParameter *param = NULL;
			fgQuality quality = FG_QUALITY_UNIVERSAL;
			fgResPriorityType priority = FG_RES_PRIORITY_LOW;
			fgBool isMapped = FG_FALSE;
			fgArrayVector<fgQuality> qualityVec;
			fgArrayVector<std::string> pathVec;
			fgArrayVector<std::string> _helperVec;

			/// Get the resource name
			if((param = section->getParameter("name")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_STRING)
					name = param->string;
				printf("RESOURCE NAME: %s\n", param->string);
			} else {
				foundName = FG_FALSE;
			}
			// Get the resource type
			if((param = section->getParameter("type")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_STRING)
					type = FG_RESOURCE_TYPE_FROM_TEXT(param->string);
				printf("TYPE STR : %s\n", param->string);
			} else {
				foundType = FG_FALSE;
			}
			// Get the resource priority
			if((param = section->getParameter("priority")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_STRING)
					priority = FG_RES_PRIORITY_FROM_TEXT(param->string);
			} else {
				foundPriority = FG_FALSE;
			}
			// Check if the resource has files mapped to different qualities
			if((param = section->getParameter("isMapped")) != NULL) {
				if(param->type == FG_CFG_PARAMETER_BOOL)
					isMapped = param->bool_val;
			} else {
				isMapped = FG_FALSE;
			}
			// When isMapped is true, then check for different parameters names
			// indicating that the values stored inside are separated by ';' char (array/vector)
			if(isMapped) {
				// Get the parameter: quality vector
				if((param = section->getParameter("qualityVec")) != NULL) {
					if(param->type == FG_CFG_PARAMETER_STRING) {
						printf("QUALITY  VEC : %s\n", param->string);
						std::string _q_vec = param->string;
						_helperVec.clear_optimised();
						fgStrings::split(_q_vec, ';', _helperVec);
						for(int i=0;i<(int)_helperVec.size();i++) {
							qualityVec.push_back(FG_QUALITY_FROM_TEXT(_helperVec[i].c_str()));
						}
						if(qualityVec.empty())
							foundQuality = FG_FALSE;
						_q_vec.clear();
						_helperVec.clear_optimised();
					}
				} else {
					foundQuality = FG_FALSE;
				}
				if((param = section->getParameter("pathVec")) != NULL) {
					if(param->type == FG_CFG_PARAMETER_STRING) {
						printf("PATH VEC : %s\n", param->string);

						std::string _p_vec = param->string;
						_helperVec.clear_optimised();
						fgStrings::split(_p_vec, ';', _helperVec);
						for(int i=0;i<(int)_helperVec.size();i++) {
							pathVec.push_back(_helperVec[i]);
						}
						if(pathVec.empty())
							foundPath = FG_FALSE;
						_p_vec.clear();
						_helperVec.clear_optimised();
					}
				} else {
					foundPath = FG_FALSE;
				}
				// In other case, the resource has single quality selected and stores single file
			} else {
				if((param = section->getParameter("quality")) != NULL) {
					if(param->type == FG_CFG_PARAMETER_STRING) {
						quality = FG_QUALITY_FROM_TEXT(param->string);
						printf("QUALITY : %s\n", param->string);
					}
				} else {
					quality = FG_QUALITY_UNIVERSAL;
				}
				if((param = section->getParameter("path")) != NULL) {
					if(param->type == FG_CFG_PARAMETER_STRING)
						path = param->string;
					
				} else {
					foundPath = FG_FALSE;
				}
			}
			if(!foundPath || !foundType || !foundName || !foundQuality)
				continue;
			if(!FG_ResourceFactory->isRegistered(type) || type == FG_RESOURCE_GROUP) {
				continue;
			}
			fgResource *resource = FG_ResourceFactory->createResource(type);
			if(!resource)
				continue;
			printf("NAME __ : __ %s\n", name.c_str());
			resource->setResourceName(name);
			if(foundPriority)
				resource->setPriority(priority);
			if(isMapped) {
				if(pathVec.size() != qualityVec.size()) {
					// ERROR #TODO
					qualityVec.clear_optimised();
					pathVec.clear_optimised();
					delete resource;
					continue;
				}
				for(int i=0;i<(int)pathVec.size();i++) {
					resource->setFilePath(pathVec[i],qualityVec[i]);
					FG_LOG::PrintDebug("Setting path: '%s', for resource: '%s', quality='%d'", pathVec[i].c_str(), name.c_str(), (int)qualityVec[i]);

				}
			} else {
				resource->setFilePath(path);
			}
			m_resourceFiles.push_back(resource);
			// Finish
		} // else if ( name == RESOURCE_GROUP )
	} // iteration through section map
	
	delete config;
	config = NULL;

	return FG_TRUE;
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
	const char *ext = fgPath::fileExt(m_filePath.c_str(), FG_TRUE);
	if(!ext)
		return FG_FALSE;
	if(strcasecmp(ext, "group.xml") == 0) {
		// Resource group config file is in XML format
		m_xmlParser = new fgXMLParser();
		fgResourceGroupContentHandler *contentHandler = new fgResourceGroupContentHandler();
		contentHandler->setResourceGroupPointer(this);
		m_xmlParser->setContentHandler(contentHandler);

		if(!m_xmlParser->loadXML(m_filePath.c_str())) {
			return FG_FALSE;
		}
		m_xmlParser->parseWithHandler();
		delete m_xmlParser;
		delete contentHandler;
		m_xmlParser = NULL;
	} else if(strcasecmp(ext, "group.ini") == 0) {
		if(!_parseIniConfig())
			return FG_FALSE;
	}	
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
