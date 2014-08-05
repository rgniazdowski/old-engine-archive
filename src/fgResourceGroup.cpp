/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceGroup.h"
#include "Graphics/Textures/fgTextureResource.h"
#include "GUI/fgFontResource.h"

void fgResourceGroupContentHandler::startElement(const char *localName, fgXMLElement *elementPtr, fgXMLNodeType nodeType, fgXMLAttribute *firstAttribute, int depth)
{
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

	m_resType = FG_RESOURCE_INVALID;
	m_resourcePtr = NULL;

	// Handling for resource group tag type - in most cases it's the root node.
	if(strnicmp(localName, FG_RESOURCE_GROUP_NAME, strlen(FG_RESOURCE_GROUP_NAME)) == 0) {
		m_resType = FG_RESOURCE_GROUP;
		fgXMLAttribute *attribute = firstAttribute;
		while(attribute) {
			const char *attrname = attribute->Name();
			const char *attrvalue = attribute->Value();
			if(strnicmp(attrname, "name", 4) == 0) {
				m_resourceGroup->setResourceName(attrvalue);
			} else if(strnicmp(attrname, "priority", 8) == 0) {
				m_resourceGroup->setPriority((fgResPriorityType)atoi(attrvalue));
			}
			attribute = attribute->Next();
		}
	// 
	} else if(strnicmp(localName, FG_RESOURCE_SOUND_NAME, strlen(FG_RESOURCE_SOUND_NAME)) == 0) {
		m_resType = FG_RESOURCE_SOUND;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_MUSIC_NAME, strlen(FG_RESOURCE_MUSIC_NAME)) == 0) {
		m_resType = FG_RESOURCE_MUSIC;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_3D_MODEL_NAME, strlen(FG_RESOURCE_3D_MODEL_NAME)) == 0) {
		m_resType = FG_RESOURCE_3D_MODEL;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_TEXTURE_NAME, strlen(FG_RESOURCE_TEXTURE_NAME)) == 0) {
		m_resType = FG_RESOURCE_TEXTURE;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_FONT_NAME, strlen(FG_RESOURCE_FONT_NAME)) == 0) {
		m_resType = FG_RESOURCE_FONT;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_GUI_STRUCTURE_SHEET_NAME, strlen(FG_RESOURCE_GUI_STRUCTURE_SHEET_NAME)) == 0) {
		m_resType = FG_RESOURCE_GUI_STRUCTURE_SHEET;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_GUI_STYLE_SHEET_NAME, strlen(FG_RESOURCE_GUI_STYLE_SHEET_NAME)) == 0) {
		m_resType = FG_RESOURCE_GUI_STYLE_SHEET;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_SHADER_NAME, strlen(FG_RESOURCE_SHADER_NAME)) == 0) {
		m_resType = FG_RESOURCE_SHADER;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_SCENE_NAME, strlen(FG_RESOURCE_SCENE_NAME)) == 0) {
		m_resType = FG_RESOURCE_SCENE;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_SCRIPT_NAME, strlen(FG_RESOURCE_SCRIPT_NAME)) == 0) {
		m_resType = FG_RESOURCE_SCRIPT;
	// 
	} else if(strnicmp(localName, FG_RESOURCE_SAVE_FILE_NAME, strlen(FG_RESOURCE_SAVE_FILE_NAME)) == 0) {
		m_resType = FG_RESOURCE_SAVE_FILE;
	//
	} else if(strnicmp(localName, FG_RESOURCE_VARIA_NAME, strlen(FG_RESOURCE_VARIA_NAME)) == 0) {
		m_resType = FG_RESOURCE_VARIA;
	//
	} else if(strnicmp(localName, FG_RESOURCE_BINARY_NAME, strlen(FG_RESOURCE_BINARY_NAME)) == 0) {
		m_resType = FG_RESOURCE_BINARY;
	//
	} else if(strnicmp(localName, FG_RESOURCE_LIBRARY_NAME, strlen(FG_RESOURCE_LIBRARY_NAME)) == 0) {
		m_resType = FG_RESOURCE_LIBRARY;
	//
	} else if(strnicmp(localName, FG_RESOURCE_PLUGIN_NAME, strlen(FG_RESOURCE_PLUGIN_NAME)) == 0) {
		m_resType = FG_RESOURCE_PLUGIN;
	//
	} else if(strnicmp(localName, FG_RESOURCE_CUSTOM_NAME, strlen(FG_RESOURCE_CUSTOM_NAME)) == 0) {
		m_resType = FG_RESOURCE_CUSTOM;
	//
	} else if(strnicmp(localName, FG_RESOURCE_ZIP_PACK_NAME, strlen(FG_RESOURCE_ZIP_PACK_NAME)) == 0) {
		m_resType = FG_RESOURCE_ZIP_PACK;
	} /*if(strnicmp(localName, FG_RESOURCE_INVALID_NAME, strlen(FG_RESOURCE_INVALID_NAME)) == 0) {
	}*/

	// Here are common attributes for every resource tag in resource group
	const char *resPath = NULL;
	const char *resName = NULL;
	const char *resPriorityStr = NULL;
	const char *resQualityStr = NULL;
	fgResPriorityType resPriority = FG_RES_PRIORITY_INVALID;
	fgXMLAttribute *attribute = firstAttribute;

	if(m_resType != FG_RESOURCE_GROUP && m_resType != FG_RESOURCE_INVALID) {
		while(attribute) {
			const char *attrname = attribute->Name();
			const char *attrvalue = attribute->Value();
			if(strnicmp(attrname, "path", 4) == 0) {
				resPath = attrvalue;
			} else if(strnicmp(attrname, "name", 4) == 0) {
				resName = attrvalue;
			} else if(strnicmp(attrname, "priority", 8) == 0) {
				resPriorityStr = attrvalue;
			} else if(strnicmp(attrname, "quality", 7) == 0) {
				resQualityStr = attrvalue;
			}
			attribute = attribute->Next();
		}
	}
	resPriority = (fgResPriorityType)atoi(resPriorityStr);
	// quality_ = (Quality)atoi(resQualityStr);
	// #FIXME
	printf("%s: >>> path = '%s'; name = '%s'; priority = '%s'; quality = '%s'; \n",
		localName, resPath, resName, resPriorityStr, resQualityStr);

	switch(m_resType)
	{
	case FG_RESOURCE_SOUND:
		break;
	case FG_RESOURCE_MUSIC:
		break;
	case FG_RESOURCE_3D_MODEL:
		break;
	case FG_RESOURCE_TEXTURE:
		//#FIXME
		//m_resourcePtr = new fgTextureResource();
		m_resourcePtr = new fgTextureResource(resPath);
		break;
	case FG_RESOURCE_FONT:
		//#FIXME
		//m_resourcePtr = new fgFontResource();
		m_resourcePtr = new fgFontResource(resPath);
		break;
	case FG_RESOURCE_GUI_STRUCTURE_SHEET:
		break;
	case FG_RESOURCE_GUI_STYLE_SHEET:
		break;
	case FG_RESOURCE_SHADER:
		break;
	case FG_RESOURCE_SCENE:
		break;
	case FG_RESOURCE_SCRIPT:
		break;
	case FG_RESOURCE_SAVE_FILE:
		break;
	case FG_RESOURCE_VARIA:
		break;
	case FG_RESOURCE_BINARY:
		break;
	case FG_RESOURCE_LIBRARY:
		break;
	case FG_RESOURCE_PLUGIN:
		break;
	case FG_RESOURCE_CUSTOM:
		break;
	case FG_RESOURCE_ZIP_PACK:
		break;
	default:
		break;
	};

	if(m_resourcePtr) {
		m_resourcePtr->setPriority(resPriority);
		m_resourcePtr->setResourceName(resName);
	}
}

/*******************************************************/

/*
 *
 */
fgResourceGroup::fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::fgResourceGroup(); constructor");
}

/*
 *
 */
fgResourceGroup::~fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::~fgResourceGroup(); deconstructor");
	destroy();
}

/*
 *
 */
void fgResourceGroup::clear(void)
{
	fgResource::clear();
	m_rHandles.clear_optimised();
	m_resourceFiles.clear_optimised();
	m_resType = FG_RESOURCE_GROUP;
}

/*
 *
 */
bool fgResourceGroup::create(void)
{
	bool status = true;
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->create()) {
			status = false;
		}
	}
	return status;
}

/*
 *
 */
void fgResourceGroup::destroy(void)
{
	FG_WriteLog("fgResourceGroup::destroy();");
	ZeroLock();
	dispose();
	clear();
}

/*
 *
 */
bool fgResourceGroup::recreate(void)
{
	bool status = true;
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->recreate()) {
			status = false;
		}
	}
	return status;
}

/*
 *
 */
void fgResourceGroup::dispose(void)
{
	FG_WriteLog("fgResourceGroup::~dispose();");
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->dispose();
	}
}

/*
 *
 */
bool fgResourceGroup::isDisposed(void) const
{
	bool status = true;
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		if(!(*it)->isDisposed())
			status = false;
	}
	return status;
}

/*
 *
 */
bool fgResourceGroup::preLoadConfig(void)
{
	if(m_filePath.empty())
		return false;
	m_xmlParser = new fgXMLParser();
	fgResourceGroupContentHandler *contentHandler = new fgResourceGroupContentHandler();
	contentHandler->setResourceGroupPointer(this);
	m_xmlParser->setContentHandler(contentHandler);
	if(!m_xmlParser) {
		// #TODO #P2 error messages 
		return false;
	}
	if(!m_xmlParser->loadXML(m_filePath.c_str())) {
		return false;
	}
	// ! #FIXME
	m_xmlParser->parseWithHandler();
	delete m_xmlParser;
	delete contentHandler;
	m_xmlParser = NULL;
	return true;
}

/*
 *
 */
void fgResourceGroup::refreshArrays(void)
{
	m_rHandles.clear();
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		m_rHandles.push_back((*it)->getHandle());
	}
}

/*
 * Lock the resource (reference counter +1)
 */
unsigned int fgResourceGroup::Lock(void)
{
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->Lock();
	}
	return upRef();
}

/*
 * Unlock the resource (reference counter -1)
 */
unsigned int fgResourceGroup::Unlock(void)
{
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->Unlock();
	}
	return downRef();
}

/*
 * Unlock completely the resource (reference counter = 0)
 */
void fgResourceGroup::ZeroLock(void)
{
	for(ResVecIt it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
		(*it)->ZeroLock();
	}
	ZeroLock();
}
