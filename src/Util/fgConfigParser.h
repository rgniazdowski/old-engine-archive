/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CONFIG_PARSER_H_
#define _FG_CONFIG_PARSER_H_

#include "fgStatus.h"
#include "fgFile.h"

#include "fgConfigStruct.h"

/*
 *
 */
class fgConfigParser : protected fgFile
{
protected:
	// Loaded file size
	unsigned int m_fileSize;
	// Data buffer
	char *m_fileBuffer;
public:
	// Default constructor for config parser object
	fgConfigParser();

	// Default destructor for config parser object
	virtual ~fgConfigParser();

	// Split section name
	static fgBool splitSectionName(std::string &fullSectionName, std::string &sectionName, std::string &subSectionName);

	// Load config and store all parameters in given section map
	fgBool load(const char *filePath, fgCfgTypes::sectionMap &sectionMap);

	// Parse data and store parameters in given section map (reference)
	fgBool parseData(const char *data, fgCfgTypes::sectionMap &sectionMap);

	// Free all data assiocated with the config
	void freeData(void);

	// Return the file size (in bytes)
	unsigned int getFileSize(void) const {
		return m_fileSize;
	}

	/*******************************************************
	 * These function are here because ConfigParser extends
	 * fgFile with access level protected. Need to make
	 * public methods of status reporter available. #FIXME
	 */

	fgBool isError(void) const {
		return fgStatusReporter::isError();
	}

	int getErrorCode(void) const {
		return fgStatusReporter::getErrorCode();
	}

	int getLastErrorCode(void) const {
		return fgStatusReporter::getLastErrorCode();
	}

	void setReportToMsgSystem(fgBool _set) {
		fgStatusReporter::setReportToMsgSystem(_set);
	}

	fgStatus *getLastStatus(void) const {
		return fgStatusReporter::getLastStatus();
	}
};

#endif /* _FG_CONFIG_PARSER_H_ */
