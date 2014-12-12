/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_QUALITY_MANAGER
    #define FG_INC_QUALITY_MANAGER

    #include "fgQualityTypes.h"
    #include "fgManagerBase.h"
    
    #include <map>
    #include <string>

    #define FG_QUALITY_DEFAULT      FG_QUALITY_MEDIUM

    #define FG_MANAGER_QUALITY      0x00002000
/*
 * Class QualityManager
 * 
 * Currently quality manager is used solely for simple quality check
 * It uses screen resolution to determine if device is powerful enough
 * This is kinda slick - however it is bound to errors and works (?) only
 * for mobile platforms
 *
 * QualityManager is for determining what quality is currently available
 * It should manage it by screen resolution which is a good hint regarding
 * the power of the device as higher resoulutions are on more powerful devices
 * also QM can determine quality by the device ID and generation
 * QM cant hold any information about the textures and other
 *
 * This is bound to change in the future
 * Let's call this version v0.1
 */
class fgQualityManager : public fg::base::Manager {
private:
    typedef std::map<int, fgQuality> areaQMap;
    typedef areaQMap::iterator areaQMapItor;
    typedef fg::base::Manager base_type; // ?
    /// Temporary map for storing display area sizes and corresponding quality
    /// This will work only for mobile platforms (iOS especially)
    /// Here the power of the given device is determined by max screen resolution
    /// This can apply only to phones/tablets. On PC platforms there will be needed
    /// some deeper checking / benchmarking...
    std::map<int, fgQuality> m_displayAreaQuality;
    /// Hardware quality - this is determined by display area (mobile platforms)
    fgQuality m_hardwareQuality;
    /// Forced quality - quality can be forced
    fgQuality m_forcedQuality;
    /// Selected quality (this quality is reported outside)
    fgQuality m_selectedQuality;
    ///
    int m_currentDispArea;

public:
    /**
     * Default constructor for Quality Manager object
     */
    fgQualityManager(const int dispArea = -1);
    /**
     * Default destructor for Quality Manager object
     */
    virtual ~fgQualityManager();
    
protected:
    /**
     * 
     */
    virtual void clear(void);

public:
    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void);
    
public:
    /**
     * Determine quality via screen resolution (this is bound to change in the future)
     */
    void determineQuality(void);

    /**
     * 
     * @param dispArea
     */
    void setDisplayArea(const int dispArea) {
        m_currentDispArea = dispArea;
    }
    
    /**
     * 
     * @param w
     * @param h
     */
    void setDisplayArea(const int w, const int h) {
        m_currentDispArea = w * h;
    }
    
    // Set value for forced quality (set quality up front)
    void setForcedQuality(fgQuality forceQuality) {
        m_forcedQuality = forceQuality;
        m_selectedQuality = m_forcedQuality;
    }

    // Set currently selected quality to determined via hardware (screen resolution)
    void setHardwareQuality(void) {
        m_selectedQuality = m_hardwareQuality;
    }

    // Return true if currently set quality is hardware
    fgBool isHardwareQuality(void) const {
        return (fgBool)(m_hardwareQuality == m_selectedQuality);
    }

    // Get currently selected quality
    fgQuality getQuality(void) const {
        return m_selectedQuality;
    }

    // Get value for hardware quality
    fgQuality getHardwareQuality(void) const {
        return m_hardwareQuality;
    }
};

#endif /* FG_INC_QUALITY_MANAGER */
