/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_QUALITY_MANAGER_H_
#define _FG_QUALITY_MANAGER_H_

#include <map>
#include <string>

#include "../fgSingleton.h"

// FIXME

#include "../Graphics/Textures/fgTextureCommon.h"

// FIXME

class fgQualityManager : public fgSingleton<fgQualityManager> {
	friend class fgSingleton<fgQualityManager>;
	
private:
	// Key: texture quality; value: display area;
	std::map<int, Tex::Quality> m_displayAreaQuality;
	std::map<int, std::string> m_textureFileName;
    Tex::Quality m_selectedQuality; // FIXME

protected:
	fgQualityManager();
	~fgQualityManager();

public:

	void determineQuality(void);

	// FIXME well now this is reallllllllly retarded
	// QualityManager is for determining what quality is currently available
	// It should manage it by screen resolution which is a good hint regarding
	// the power of the device as higher resoulutions are on more powerful devices
	// also QM can determine quality by the device ID and generation
	// QM cant hold any information about the textures and other
	std::string & getFileName(int texture_id);
	void setFileName(int texture_id, const char *filename);
	int getTextureID(const char *filename);

    Tex::Quality quality() const { // FIXME
        return m_selectedQuality;
    }
};

#define FG_QualityManager fgQualityManager::getInstance()

#endif
