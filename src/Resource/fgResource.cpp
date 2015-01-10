/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#include "fgResource.h"
#include "fgLog.h"

/*
 * Base constructor of the resource object
 */
CResource::CResource() :
m_priority(FG_RES_PRIORITY_LOW),
m_quality(FG_QUALITY_UNIVERSAL),
m_resType(FG_RESOURCE_INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(FG_QUALITY_UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource();");
}

/*
 * Constructor with additional parameter (path)
 */
CResource::CResource(const char *path) :
m_priority(FG_RES_PRIORITY_LOW),
m_quality(FG_QUALITY_UNIVERSAL),
m_resType(FG_RESOURCE_INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(FG_QUALITY_UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource(const char *path);");
    setFilePath(path);
}

/*
 * Constructor with additional parameter (path)
 */
CResource::CResource(std::string& path) :
m_priority(FG_RES_PRIORITY_LOW),
m_quality(FG_QUALITY_UNIVERSAL),
m_resType(FG_RESOURCE_INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(FG_QUALITY_UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource(std::string& path);");
    setFilePath(path);
}

/*
 * Clears the class data, this actually does not free allocated memory,
 * just resets base class attributes
 */
void CResource::clear(void) {
    m_resType = FG_RESOURCE_INVALID;
    m_priority = FG_RES_PRIORITY_LOW;
    m_quality = FG_QUALITY_UNIVERSAL;
    m_nRefCount = 0;
    m_lastAccess = 0;
    m_isReady = FG_FALSE;
    m_size = 0;
    m_fileMapping.clear();
    m_filePath.clear();
    m_pManager = NULL;
    //FG_LOG_DEBUG("fgResource::clear(void);");
}

/**
 * 
 * @param container
 * @return 
 */
bool CResource::operator <(CResource& container) {
    if(getPriority() < container.getPriority())
        return true;
    else if(getPriority() > container.getPriority())
        return false;
    else {
        if(m_lastAccess < container.getLastAccess())
            return true;
        else if(m_lastAccess > container.getLastAccess())
            return false;
        else {
            if(getSize() < container.getSize())
                return true;
            else
                return false;
        }
    }
    return false;
}

/**
 * 
 * @param container
 * @return 
 */
bool CResource::operator >(CResource& container) {
    if(getPriority() < container.getPriority())
        return false;
    else if(getPriority() > container.getPriority())
        return true;
    else {
        if(m_lastAccess < container.getLastAccess())
            return false;
        else if(m_lastAccess > container.getLastAccess())
            return true;
        else {
            if(getSize() < container.getSize())
                return false;
            else
                return true;
        }
    }
    return false;
}
