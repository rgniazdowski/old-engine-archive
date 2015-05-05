/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#include "fgResource.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

resource::CResource::CResource() :
m_priority(ResourcePriority::LOW),
m_quality(Quality::UNIVERSAL),
m_resType(resource::INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(Quality::UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource();");
}
//------------------------------------------------------------------------------

resource::CResource::CResource(const char *path) :
m_priority(ResourcePriority::LOW),
m_quality(Quality::UNIVERSAL),
m_resType(resource::INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(Quality::UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource(const char *path);");
    setFilePath(path);
}
//------------------------------------------------------------------------------

resource::CResource::CResource(const std::string& path) :
m_priority(ResourcePriority::LOW),
m_quality(Quality::UNIVERSAL),
m_resType(resource::INVALID),
m_nRefCount(0),
m_lastAccess(0),
m_size(0),
m_isReady(FG_FALSE) {
    setDefaultID(Quality::UNIVERSAL);
    //FG_LOG_DEBUG("fgResource::fgResource(std::string& path);");
    setFilePath(path);
}
//------------------------------------------------------------------------------

void resource::CResource::clear(void) {
    m_resType = resource::INVALID;
    m_priority = ResourcePriority::LOW;
    m_quality = Quality::UNIVERSAL;
    m_nRefCount = 0;
    m_lastAccess = 0;
    m_isReady = FG_FALSE;
    m_size = 0;
    m_fileMapping.clear();
    m_filePath.clear();
    m_pManager = NULL;
    //FG_LOG_DEBUG("fgResource::clear(void);");
}
//------------------------------------------------------------------------------

bool resource::CResource::operator <(CResource& container) {
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
//------------------------------------------------------------------------------

bool resource::CResource::operator >(CResource& container) {
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
//------------------------------------------------------------------------------
