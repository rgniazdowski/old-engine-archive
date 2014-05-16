/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_GROUP_H_
#define _FG_RESOURCE_GROUP_H_

#include "fgCommon.h"
#include "fgResource.h"
#include "fgXMLParser.h"

// This is resource group and it is treated like normal resource.
// The idea behind is that when ResourceGroup  is loaded/released 
// it will also release  all binded resources - however only when
// all resource inside  the group have reference count equal zero
// Also it  needs to  work in  a way  that ResourceGroup can lock 
// resources blocking their separate removal/release even if some
// resources have reference count equal zero.
//
// In other words this class binds separate resources into one.
// ResourceGroup files are loaded via xml configs from predefined
// location. The config files will specify the type and  location
// resources that will be part of this group/union. Additional 
// parameters include things like priority, tags, etc.
class fgResourceGroup : public fgResource {
public:
	fgResourceGroup();
	~fgResourceGroup();
	
	virtual void clear();

	virtual bool create();
	virtual void destroy();
	virtual bool recreate();
	virtual void dispose();
	virtual size_t getSize();
	virtual bool isDisposed();

protected:
	fgArrayVector<FG_RHANDLE> m_rHandles;
	fgArrayVector<std::string> resourceFiles;

};

#endif