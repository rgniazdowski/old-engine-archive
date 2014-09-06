/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_MANAGER_BASE_H_
#define _FG_MANAGER_BASE_H_

#include "fgCommon.h"
#include "fgStatusReporter.h"
#include "Util/fgTag.h"

class fgManagerBase;

#define FG_TAG_MANAGER_BASE_NAME	"fgManagerBase"
//#define FG_TAG_MANAGER_BASE_ID		20 //#FIXME - something automatic maybe?
#define FG_TAG_MANAGER_BASE			FG_TAG_TYPE(fgManagerBase)

//FG_TAG_TEMPLATE(fgManagerBase, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fgManagerBase, FG_TAG_MANAGER_BASE_NAME);

// Special handle type for manager base
typedef FG_TAG_MANAGER_BASE fgManagerBaseTag;

class fgManagerBase : public fgStatusReporter<fgManagerBaseTag> {
public:
	fgManagerBase() : m_init(FG_FALSE) {}
	virtual ~fgManagerBase() {}
		
	virtual void clear(void) = 0;
	virtual void destroy(void) = 0;

	virtual fgBool initialize(void) = 0;
protected:
	fgBool m_init;
};

#endif /* _FG_MANAGER_BASE_H_ */
