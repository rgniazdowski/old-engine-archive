/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceGroup.h"

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
				m_resourceGroup->setPriority((fgResource::fgResPriorityType)atoi(attrvalue));
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
	} else if(strnicmp(localName, FG_RESOURCE_ZIP_PACK_NAME, strlen(FG_RESOURCE_ZIP_PACK_NAME)) == 0) {
		m_resType = FG_RESOURCE_ZIP_PACK;
	} /*if(strnicmp(localName, FG_RESOURCE_INVALID_NAME, strlen(FG_RESOURCE_INVALID_NAME)) == 0) {
	}*/

	// Here are common attributes for every resource tag in resource group
	const char *path = NULL;
	const char *name = NULL;
	const char *priority = NULL;
	const char *quality = NULL;
	fgResource::fgResPriorityType resPriority = fgResource::FG_RES_PRIORITY_INVALID;

	fgXMLAttribute *attribute = firstAttribute;

	if(m_resType != FG_RESOURCE_GROUP && m_resType != FG_RESOURCE_INVALID) {
		while(attribute) {
			const char *attrname = attribute->Name();
			const char *attrvalue = attribute->Value();
			if(strnicmp(attrname, "path", 4) == 0) {
				path = attrvalue;
			} else if(strnicmp(attrname, "name", 4) == 0) {
				name = attrvalue;
			} else if(strnicmp(attrname, "priority", 8) == 0) {
				priority = attrvalue;
			} else if(strnicmp(attrname, "quality", 7) == 0) {
				quality = attrvalue;
			}
			attribute = attribute->Next();
		}
	}

	printf("%s: >>> path = '%s'; name = '%s'; priority = '%s'; quality = '%s'; \n", localName, path, name, priority, quality);

	switch(m_resType)
	{
	case FG_RESOURCE_SOUND:
		break;
	case FG_RESOURCE_MUSIC:
		break;
	case FG_RESOURCE_3D_MODEL:
		break;
	case FG_RESOURCE_TEXTURE:
		//m_resourcePtr = new fgTextureResource();
		break;
	case FG_RESOURCE_FONT:
		//m_resourcePtr = new fgFontResource();
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
	case FG_RESOURCE_ZIP_PACK:
		break;
	default:
		break;
	};
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
}

/*
 *
 */
bool fgResourceGroup::create(void)
{
	return true;
}

/*
 *
 */
void fgResourceGroup::destroy(void)
{
	FG_WriteLog("fgResourceGroup::destroy();");
}

/*
 *
 */
bool fgResourceGroup::recreate(void)
{
	return true;
}

/*
 *
 */
void fgResourceGroup::dispose(void)
{
	FG_WriteLog("fgResourceGroup::~dispose();");
}

/*
 *
 */
bool fgResourceGroup::isDisposed(void) const
{
	return false;
}

/*
 *
 */
bool fgResourceGroup::preLoadConfig(void)
{
	if(strnlen(m_filePath,sizeof(m_filePath)) == 0)
		return false;
	m_xmlParser = new fgXMLParser();
	fgResourceGroupContentHandler *contentHandler = new fgResourceGroupContentHandler();
	contentHandler->setResourceGroupPointer(this);
	m_xmlParser->setContentHandler(contentHandler);
	if(!m_xmlParser) {
		// #TODO #P2 error messages 
		return false;
	}
	if(!m_xmlParser->loadXML(m_filePath)) {
		return false;
	}
	// ! #FIXME
	m_xmlParser->parseWithHandler();
	delete m_xmlParser;
	delete contentHandler;
	m_xmlParser = NULL;
	return true;
}