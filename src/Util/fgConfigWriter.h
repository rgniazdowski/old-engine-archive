/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CONFIG_WRITER_H_
#define _FG_CONFIG_WRITER_H_

#include "fgFile.h"

#include "fgConfigStruct.h"

class fgConfigWriter : protected fgFile {
protected:
public:
	fgConfigWriter();
	~fgConfigWriter();

	fgBool save(const char *filePath, fgCfgTypes::sectionMap &sectionMap);

	/*******************************************************
	 * These function are here because ConfigWriter extends
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

#endif /* _FG_CONFIG_WRITER_H_ */
