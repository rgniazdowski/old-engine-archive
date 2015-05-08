/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgResourceGroup.h"
#include "fgResourceFactory.h"
#include "fgResourceConfigParser.h"

#include "fgLog.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"

using namespace fg;

//------------------------------------------------------------------------------

/*******************************************************************************
 * RESOURCE GROUP CONTENT HANDLER - READING XML FILE
 */

resource::CResourceGroupContentHandler::CResourceGroupContentHandler() :
m_resourceGroup(NULL),
m_resType(resource::INVALID),
m_resourcePtr(NULL),
m_curResPriority(ResourcePriority::INVALID),
m_isMapped(FG_FALSE),
m_isFileQualityMapTag(FG_FALSE) { }
//------------------------------------------------------------------------------

resource::CResourceGroupContentHandler::~CResourceGroupContentHandler() {
    while(!m_elemStack.empty())
        m_elemStack.pop();
}
//------------------------------------------------------------------------------

void resource::CResourceGroupContentHandler::endElement(const char *localName,
                                                        fgXMLElement *elementPtr,
                                                        fgXMLNodeType nodeType,
                                                        int depth) {
    m_elemStack.pop();
    ResourceType rtype = getResourceTypeFromText(localName);
    // If the resource was created...
    if(m_resourcePtr && (rtype != resource::GROUP && rtype != resource::INVALID)) {
        m_resourcePtr->setPriority(m_curResPriority);
        // ...then it can be added to the Resource Groups list.
        this->m_resourceGroup->getRefResourceFiles().push_back(m_resourcePtr);
        m_resType = resource::INVALID;
        m_resourcePtr = NULL;
        m_isMapped = FG_FALSE;
        m_isFileQualityMapTag = FG_FALSE;
        m_curResPriority = ResourcePriority::INVALID;
    }
}
//------------------------------------------------------------------------------

fgBool resource::CResourceGroupContentHandler::loadResConfig(const char *path) {
    if(!path)
        return FG_FALSE;
    FG_LOG_DEBUG("Loading resource config: '%s'", path);
    CResourceConfig *resCfg = new CResourceConfig();
    // This references to external config file, config should be loaded and proper resource created
    if(!resCfg->load(path)) {
        delete resCfg;
        // MESSAGE?
        return FG_FALSE;
    }
    SResourceHeader *header = &resCfg->getRefHeader();
    if(m_resourceGroup->getFactory()->isRegistered(m_resType)) {
        m_resourcePtr = m_resourceGroup->getFactory()->createResource(m_resType);
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
//------------------------------------------------------------------------------

void resource::CResourceGroupContentHandler::startElement(const char *localName,
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
    m_resType = getResourceTypeFromText(localName);
    // Handling for resource group tag type - in most cases it's the root node.
    // #TODO - there needs to be a security check - checking if the resource group does not
    // contain links to other resource group files - this is not support and not needed.
    if(m_resType == resource::GROUP) {
        fgXMLAttribute *attribute = firstAttribute;
        // #FIXME #P5 - well looks like this could use some kind of error checking, maybe...
        while(attribute) {
            const char *attrname = attribute->Name();
            const char *attrvalue = attribute->Value();
            if(strncasecmp(attrname, "name", 4) == 0) {
                m_resourceGroup->setName(attrvalue);
            } else if(strncasecmp(attrname, "priority", 8) == 0) {
                m_resourceGroup->setPriority(getResourcePriorityFromText(attrvalue));
            } else if(strncasecmp(attrname, "forceCreate", 11) == 0) {
                m_resourceGroup->setForceCreate(FG_BOOL_FROM_TEXT(attrvalue));
            }
            attribute = attribute->Next();
        }
    } else if(m_resType == resource::INVALID) {
        if(strncasecmp(localName, FG_FILE_QUALITY_MAPPING_TEXT, strlen(FG_FILE_QUALITY_MAPPING_TEXT)) == 0) {
            m_isFileQualityMapTag = FG_TRUE;
        }
    }
    m_curResPriority = ResourcePriority::LOW;
    Quality resQuality = Quality::UNIVERSAL;
    // Here are common attributes for every resource tag in resource group
    // Path to the resource
    const char *resPath = NULL;
    // Resource name (ID/TAG string)
    const char *resName = NULL;
    // Pointer to the first attribute for checking
    fgXMLAttribute *attribute = firstAttribute;
    std::string cfgDirPath = m_resourceGroup->getFilePath();
    path::dirName(cfgDirPath, cfgDirPath);

    if(m_resType != resource::GROUP &&
       (m_resType != resource::INVALID || m_isFileQualityMapTag)) {
        while(attribute) {
            const char *attrname = attribute->Name();
            const char *attrvalue = attribute->Value();
            if(strncasecmp(attrname, "config", 6) == 0) {
                if(attrvalue) {
                    std::string newPath = path::join(cfgDirPath, std::string(attrvalue));
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
                m_curResPriority = getResourcePriorityFromText(attrvalue);
            } else if(strncasecmp(attrname, "quality", 7) == 0) {
                resQuality = getQualityFromText(attrvalue);
            } else if(strncasecmp(attrname, "ismapped", 8) == 0) {
                m_isMapped = FG_BOOL_FROM_TEXT(attrvalue);
            }
            attribute = attribute->Next();
        }
    }

    if(m_resType == resource::INVALID) {
        if(m_resourcePtr && m_isFileQualityMapTag && resPath) {
            //FG_LOG_DEBUG("Setting path: '%s', for resource: '%s', quality='%s'", resPath, m_curResName, resQualityStr);
            std::string newPath = path::join(cfgDirPath, std::string(resPath));
            m_resourcePtr->setFilePath(newPath, resQuality);
        }
        return;
    }

    // Check if the create function for current resource type is registered.
    // Also ignore resource group type.
    if(!m_resourceGroup->getFactory()->isRegistered(m_resType) || m_resType == resource::GROUP) {
        m_resourcePtr = NULL;
    } else {
        m_resourcePtr = m_resourceGroup->getFactory()->createResource(m_resType);
        if(resPath) {
            std::string newPath = path::join(cfgDirPath, std::string(resPath));
            m_resourcePtr->setFilePath(newPath);
        }
        m_resourcePtr->setName(resName);
    }
}
//------------------------------------------------------------------------------

resource::CResourceGroup::CResourceGroup() :
m_isForceCreate(FG_FALSE),
m_rHandles(),
m_resourceFiles(),
m_xmlParser(NULL),
m_resFactory(NULL) {
    clear();
}
//------------------------------------------------------------------------------

resource::CResourceGroup::CResourceGroup(CResourceFactory *resourceFactory) :
m_isForceCreate(FG_FALSE),
m_rHandles(),
m_resourceFiles(),
m_xmlParser(NULL),
m_resFactory(NULL) {
    clear();
    setResourceFactory(resourceFactory);
}
//------------------------------------------------------------------------------

resource::CResourceGroup::~CResourceGroup() {
    resource::CResourceGroup::destroy();
}
//------------------------------------------------------------------------------

void resource::CResourceGroup::setResourceFactory(CResourceFactory *resourceFactory) {
    if(resourceFactory)
        m_resFactory = resourceFactory;
}
//------------------------------------------------------------------------------

resource::CResourceFactory *resource::CResourceGroup::getFactory(void) const {
    return m_resFactory;
}
//------------------------------------------------------------------------------

void resource::CResourceGroup::clear(void) {
    CResource::clear();
    m_rHandles.clear_optimised();
    m_resourceFiles.clear_optimised();
    m_resType = resource::GROUP;
    m_resFactory = NULL;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceGroup::create(void) {
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
//------------------------------------------------------------------------------

void resource::CResourceGroup::destroy(void) {
    ZeroLock();
    dispose();
    clear();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceGroup::recreate(void) {
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
//------------------------------------------------------------------------------

void resource::CResourceGroup::dispose(void) {
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->dispose();
    }
}
//------------------------------------------------------------------------------

fgBool resource::CResourceGroup::isDisposed(void) const {
    if(m_resourceFiles.empty())
        return FG_TRUE;
    fgBool status = FG_TRUE;
    for(rgResVecConstItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        if(!(*it)->isDisposed())
            status = FG_FALSE;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceGroup::private_parseIniConfig(void) {
    if(!m_resFactory) {
        return FG_FALSE;
    }
    if(m_filePath.empty())
        return FG_FALSE;
    CResourceConfig *config = new CResourceConfig();
    if(!config->load(m_filePath.c_str())) {
        delete config;
        return FG_FALSE;
    }
    // #FIXME - need to support forceCreate option
    CResourceConfig::ResourceHeaderMap &headerMap = config->getRefHeaders();
    CResourceConfig::ResourceHeaderMapItor rhit = headerMap.begin(),
            end = headerMap.end();
    this->setName(config->getName());
    this->setPriority(config->getPriority());
    for(; rhit != end; rhit++) {
        SResourceHeader &headerRef = rhit->second;
        SResourceHeader *header = NULL;
        CResourceConfig *resCfg = NULL;
        if(headerRef.isConfig) {
            resCfg = new CResourceConfig();
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
        if(!m_resFactory->isRegistered(header->resType) || header->resType == resource::GROUP) {
            if(resCfg)
                delete resCfg;
            continue;
        }

        CResource *resource = m_resFactory->createResource(header->resType);
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
//------------------------------------------------------------------------------

fgBool resource::CResourceGroup::preLoadConfig(void) {
    if(!m_resFactory) {
        return FG_FALSE;
    }
    if(m_filePath.empty())
        return FG_FALSE;
    const char *ext = path::fileExt(m_filePath.c_str(), FG_TRUE);
    if(!ext)
        return FG_FALSE;
    if(strcasecmp(ext, "group.xml") == 0) {
        // Resource group config file is in XML format
        m_xmlParser = new xml::CParser();
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
//------------------------------------------------------------------------------

void resource::CResourceGroup::refreshArrays(void) {
    m_rHandles.clear();
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        m_rHandles.push_back((*it)->getHandle());
    }
}
//------------------------------------------------------------------------------

unsigned int resource::CResourceGroup::Lock(void) {
    if(m_resourceFiles.empty())
        return -1;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->Lock();
    }
    return upRef();
}
//------------------------------------------------------------------------------

unsigned int resource::CResourceGroup::Unlock(void) {
    if(m_resourceFiles.empty())
        return -1;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->Unlock();
    }
    return downRef();
}
//------------------------------------------------------------------------------

void resource::CResourceGroup::ZeroLock(void) {
    if(m_resourceFiles.empty())
        return;
    for(rgResVecItor it = m_resourceFiles.begin(); it != m_resourceFiles.end(); it++) {
        (*it)->ZeroLock();
    }
    CResource::ZeroLock();
}
//------------------------------------------------------------------------------
