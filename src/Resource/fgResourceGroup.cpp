/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgResourceGroup.h"
#include "fgResourceFactory.h"
#include "fgResourceConfigParser.h"

#include "fgLog.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"

/*******************************************************************************
 * RESOURCE GROUP CONTENT HANDLER - READING XML FILE
 */

/**
 * Base constructor of the resource group content handler object
 */
fg::resource::CResourceGroupContentHandler::CResourceGroupContentHandler() :
m_resourceGroup(NULL),
m_resType(FG_RESOURCE_INVALID),
m_resourcePtr(NULL),
m_curResPriority(FG_RES_PRIORITY_INVALID),
m_isMapped(FG_FALSE),
m_isFileQualityMapTag(FG_FALSE) { }

/**
 * Destructor of the resource group content handler object
 */
fg::resource::CResourceGroupContentHandler::~CResourceGroupContentHandler() {
    while(!m_elemStack.empty())
        m_elemStack.pop();
}

/*
 *
 */
void fg::resource::CResourceGroupContentHandler::endElement(const char *localName,
                                               fgXMLElement *elementPtr,
                                               fgXMLNodeType nodeType,
                                               int depth) {
    m_elemStack.pop();
    fgResourceType rtype = FG_RESOURCE_TYPE_FROM_TEXT(localName);
    // If the resource was created...
    if(m_resourcePtr && (rtype != FG_RESOURCE_GROUP && rtype != FG_RESOURCE_INVALID)) {
        m_resourcePtr->setPriority(m_curResPriority);
        // ...then it can be added to the Resource Groups list.
        this->m_resourceGroup->getRefResourceFiles().push_back(m_resourcePtr);
        m_resType = FG_RESOURCE_INVALID;
        m_resourcePtr = NULL;
        m_isMapped = FG_FALSE;
        m_isFileQualityMapTag = FG_FALSE;
        m_curResPriority = FG_RES_PRIORITY_INVALID;
    }
}

/**
 * 
 * @param path
 * @return 
 */
fgBool fg::resource::CResourceGroupContentHandler::loadResConfig(const char *path) {
    if(!path)
        return FG_FALSE;
    FG_LOG_DEBUG("Loading resource config: '%s'", path);
    fgResourceConfig *resCfg = new fgResourceConfig();
    // This references to external config file, config should be loaded and proper resource created
    if(!resCfg->load(path)) {
        delete resCfg;
        // MESSAGE?
        return FG_FALSE;
    }
    fgResourceHeader *header = &resCfg->getRefHeader();
    if(m_resourceGroup->getResourceFactory()->isRegistered(m_resType)) {
        m_resourcePtr = m_resourceGroup->getResourceFactory()->createResource(m_resType);
        m_resourcePtr->setName(header->name);
        m_resourcePtr->setFlags(header->flags);
        m_resourcePtr->setPriority(header->priority);
        m_resourcePtr->setQuality(header->quality);
        m_curResPriority = header->priority;
        if(header->paths.size() != header->qualities.size()) {
            FG_LOG_ERROR("Group config: number of qualities doesn't match number of files for: '%s'", header->name.c_str());
            delete m_resourcePtr;
            m_resourcePtr = NULL;
            if(resCfg)
                delete resCfg;
            return FG_FALSE;
        }
        for(int i = 0; i < (int)header->paths.size(); i++) {
            m_resourcePtr->setFilePath(header->paths[i], header->qualities[i]);
        }
        m_resourcePtr->setDefaultID(header->quality);
    }
    delete resCfg;
    return FG_TRUE;
    ;
}

/*
 * Receive notification of the start of an element.
 * This function will add to the specified resource group any identified resources.
 */
void fg::resource::CResourceGroupContentHandler::startElement(const char *localName,
                                                 fgXMLElement *elementPtr,
                                                 fgXMLNodeType nodeType,
                                                 fgXMLAttribute *firstAttribute,
                                                 int depth) {
    //FG_LOG_DEBUG("START ELEMENT: %s", localName);
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
                m_resourceGroup->setName(attrvalue);
            } else if(strncasecmp(attrname, "priority", 8) == 0) {
                m_resourceGroup->setPriority(FG_RES_PRIORITY_FROM_TEXT(attrvalue));
            }
            attribute = attribute->Next();
        }
    } else if(m_resType == FG_RESOURCE_INVALID) {
        if(strncasecmp(localName, FG_FILE_QUALITY_MAPPING_TEXT, strlen(FG_FILE_QUALITY_MAPPING_TEXT)) == 0) {
            m_isFileQualityMapTag = FG_TRUE;
        }
    }
    m_curResPriority = FG_RES_PRIORITY_LOW;
    fgQuality resQuality = FG_QUALITY_UNIVERSAL;
    // Here are common attributes for every resource tag in resource group
    // Path to the resource
    const char *resPath = NULL;
    // Resource name (ID/TAG string)
    const char *resName = NULL;
    // Pointer to the first attribute for checking
    fgXMLAttribute *attribute = firstAttribute;
    std::string cfgDirPath = m_resourceGroup->getFilePath();
    fg::path::dirName(cfgDirPath, cfgDirPath);

    if(m_resType != FG_RESOURCE_GROUP && (m_resType != FG_RESOURCE_INVALID || m_isFileQualityMapTag)) {
        while(attribute) {
            const char *attrname = attribute->Name();
            const char *attrvalue = attribute->Value();
            if(strncasecmp(attrname, "config", 6) == 0) {
                if(attrvalue) {
                    std::string newPath = fg::path::join(cfgDirPath, std::string(attrvalue));
                    if(!loadResConfig(newPath.c_str())) {
                        attribute = attribute->Next();
                        continue;
                    } else {
                        return;
                    }
                } else {
                    attribute = attribute->Next();
                    continue;
                }
                break;
            }

            if(strncasecmp(attrname, "path", 4) == 0) {
                resPath = attrvalue;
            } else if(strncasecmp(attrname, "name", 4) == 0) {
                resName = attrvalue;
            } else if(strncasecmp(attrname, "priority", 8) == 0) {
                m_curResPriority = FG_RES_PRIORITY_FROM_TEXT(attrvalue);
            } else if(strncasecmp(attrname, "quality", 7) == 0) {
                resQuality = FG_QUALITY_FROM_TEXT(attrvalue);
            } else if(strncasecmp(attrname, "ismapped", 8) == 0) {
                m_isMapped = FG_BOOL_FROM_TEXT(attrvalue);
            }
            attribute = attribute->Next();
        }
    }

    if(m_resType == FG_RESOURCE_INVALID) {
        if(m_resourcePtr && m_isFileQualityMapTag && resPath) {
            //FG_LOG_DEBUG("Setting path: '%s', for resource: '%s', quality='%s'", resPath, m_curResName, resQualityStr);
            std::string newPath = fg::path::join(cfgDirPath, std::string(resPath));
            m_resourcePtr->setFilePath(newPath, resQuality);
        }
        return;
    }

    // Check if the create function for current resource type is registered.
    // Also ignore resource group type.
    if(!m_resourceGroup->getResourceFactory()->isRegistered(m_resType) || m_resType == FG_RESOURCE_GROUP) {
        m_resourcePtr = NULL;
    } else {
        m_resourcePtr = m_resourceGroup->getResourceFactory()->createResource(m_resType);
        if(resPath) {
            std::string newPath = fg::path::join(cfgDirPath, std::string(resPath));
            m_resourcePtr->setFilePath(newPath);
        }
        m_resourcePtr->setName(resName);
    }
}

/*********************************************************/

/**
 * Base constructor of the resource group object
 */
fg::resource::CResourceGroup::CResourceGroup() {
    clear();
}

/**
 * 
 * @param resourceFactory
 */
fg::resource::CResourceGroup::CResourceGroup(fgResourceFactory *resourceFactory) {
    clear();
    setResourceFactory(resourceFactory);
}

/**
 * Destructor of the resource group object
 */
fg::resource::CResourceGroup::~CResourceGroup() {
    fg::resource::CResourceGroup::destroy();
}

/**
 * 
 * @param resourceFactory
 */
void fg::resource::CResourceGroup::setResourceFactory(fgResourceFactory *resourceFactory) {
    if(resourceFactory)
        m_resourceFactory = resourceFactory;
}

/**
 * 
 * @return 
 */
fgResourceFactory *fg::resource::CResourceGroup::getResourceFactory(void) const {
    return m_resourceFactory;
}

/**
 * Clears the class data, this actually does not free allocated memory, just resets base class attributes
 */
void fg::resource::CResourceGroup::clear(void) {
    CResource::clear();
    m_rHandles.clear_optimised();
    m_resourceFiles.clear_optimised();
    m_resType = FG_RESOURCE_GROUP;
    m_resourceFactory = NULL;
}

/**
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 * @return
 */
fgBool fg::resource::CResourceGroup::create(void) {
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

/**
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void fg::resource::CResourceGroup::destroy(void) {
    ZeroLock();
    dispose();
    clear();
}

/**
 * Reloads any data, recreates the resource (refresh)
 * @return
 */
fgBool fg::resource::CResourceGroup::recreate(void) {
    //FG_LOG_DEBUG("fgResourceGroup::recreate();");
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

/**
 * Dispose completely of the all loaded data, free all memory
 */
void fg::resource::CResourceGroup::dispose(void) {
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->dispose();
    }
}

/**
 * Check if resource is disposed (not loaded yet or disposed after)
 * @return
 */
fgBool fg::resource::CResourceGroup::isDisposed(void) const {
    if(m_resourceFiles.empty())
        return FG_TRUE;
    fgBool status = FG_TRUE;
    for(rgResVecConstItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        if(!(*it)->isDisposed())
            status = FG_FALSE;
    }
    return status;
}

/**
 *
 * @return
 */
fgBool fg::resource::CResourceGroup::private_parseIniConfig(void) {
    if(!m_resourceFactory) {
        return FG_FALSE;
    }
    if(m_filePath.empty())
        return FG_FALSE;
    fgResourceConfig *config = new fgResourceConfig();
    if(!config->load(m_filePath.c_str())) {
        delete config;
        return FG_FALSE;
    }
    fgResourceConfig::resourceHeaderMap &headerMap = config->getRefResourceHeaders();
    fgResourceConfig::resourceHeaderMapItor rhit = headerMap.begin(),
            end = headerMap.end();
    this->setName(config->getName());
    this->setPriority(config->getPriority());
    for(; rhit != end; rhit++) {
        fgResourceHeader &headerRef = rhit->second;
        fgResourceHeader *header = NULL;
        fgResourceConfig *resCfg = NULL;
        if(headerRef.isConfig) {
            resCfg = new fgResourceConfig();
            // This references to external config file, config should be loaded and proper resource created
            if(!resCfg->load(headerRef.configPath.c_str())) {
                delete resCfg;
                // MESSAGE?
                continue;
            }
            header = &resCfg->getRefHeader();
        } else {
            header = &headerRef;
        }
        if(!m_resourceFactory->isRegistered(header->resType) || header->resType == FG_RESOURCE_GROUP) {
            if(resCfg)
                delete resCfg;
            continue;
        }

        CResource *resource = m_resourceFactory->createResource(header->resType);
        if(!resource) {
            if(resCfg)
                delete resCfg;
            continue;
        }
        resource->setName(header->name);
        resource->setFlags(header->flags);
        resource->setPriority(header->priority);
        resource->setQuality(header->quality);

        if(header->paths.size() != header->qualities.size()) {
            FG_LOG_ERROR("Group config: number of qualities doesn't match number of files for: '%s'", header->name.c_str());
            delete resource;
            if(resCfg)
                delete resCfg;
            continue;
        }
        for(int i = 0; i < (int)header->paths.size(); i++) {
            resource->setFilePath(header->paths[i], header->qualities[i]);
            //FG_LOG_DEBUG("Setting path: '%s', for resource: '%s', quality='%d'", pathVec[i].c_str(), name.c_str(), (int)qualityVec[i]);
        }
        resource->setDefaultID(header->quality); // #FIXME - watch out! retarded function name!
        m_resourceFiles.push_back(resource);
        if(resCfg)
            delete resCfg;
        resCfg = NULL;
    }

    delete config;
    config = NULL;

    return FG_TRUE;
}

/**
 * This will parse/load xml group config file. It wont
 * load or allocate any data - this is for 'create' to do.
 * This function will return false if file path is not set.
 * @return
 */
fgBool fg::resource::CResourceGroup::preLoadConfig(void) {
    if(!m_resourceFactory) {
        return FG_FALSE;
    }
    if(m_filePath.empty())
        return FG_FALSE;
    const char *ext = fg::path::fileExt(m_filePath.c_str(), FG_TRUE);
    if(!ext)
        return FG_FALSE;
    if(strcasecmp(ext, "group.xml") == 0) {
        // Resource group config file is in XML format
        m_xmlParser = new fgXMLParser();
        CResourceGroupContentHandler *contentHandler = new CResourceGroupContentHandler();
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
        if(!private_parseIniConfig())
            return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * Refresh arrays holding handles and resource pointers within this group
 */
void fg::resource::CResourceGroup::refreshArrays(void) {
    m_rHandles.clear();
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        m_rHandles.push_back((*it)->getHandle());
    }
}

/**
 * Lock the resource (reference counter +1)
 * @return
 */
unsigned int fg::resource::CResourceGroup::Lock(void) {
    if(m_resourceFiles.empty())
        return -1;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->Lock();
    }
    return upRef();
}

/**
 * Unlock the resource (reference counter -1)
 * @return
 */
unsigned int fg::resource::CResourceGroup::Unlock(void) {
    if(m_resourceFiles.empty())
        return -1;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->Unlock();
    }
    return downRef();
}

/**
 * Unlock completely the resource (reference counter = 0)
 */
void fg::resource::CResourceGroup::ZeroLock(void) {
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->ZeroLock();
    }
    CResource::ZeroLock();
}
