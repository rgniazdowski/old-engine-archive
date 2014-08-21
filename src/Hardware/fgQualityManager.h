/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_QUALITY_MANAGER_H_
#define _FG_QUALITY_MANAGER_H_

#include "../fgSingleton.h"
#include "fgQualityTypes.h"

#include <map>
#include <string>

#define FG_QUALITY_DEFAULT FG_QUALITY_MEDIUM

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
class fgQualityManager : public fgSingleton<fgQualityManager> 
{
	friend class fgSingleton<fgQualityManager>;	
private:
	// Temporary map for storing display area sizes and corresponding quality
	// This will work only for mobile platforms (iOS especially)
	// Here the power of the given device is determined by max screen resolution
	// This can apply only to phones/tablets. On PC platforms there will be needed
	// some deeper checking / benchmarking...
	std::map<int, fgQuality> m_displayAreaQuality;
	// Hardware quality - this is determined by display area (mobile platforms)
	fgQuality m_hardwareQuality;
	// Forced quality - quality can be forced
	fgQuality m_forcedQuality;
	// Selected quality (this quality is reported outside)
	fgQuality m_selectedQuality;

protected:
	// Default constructor for Quality Manager object
	fgQualityManager();
	// Default destructor for Quality Manager object
	~fgQualityManager();

public:
	// Determine quality via screen resolution (this is bound to change in the future)
	void determineQuality(void);

	// Set value for forced quality (set quality upfront)
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

#define FG_QualityManager fgQualityManager::getInstance()

#endif /* _FG_QUALITY_MANAGER_H_ */
