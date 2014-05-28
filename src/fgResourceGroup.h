/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_GROUP_H_
#define _FG_RESOURCE_GROUP_H_

//#include <utility>

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
//
// Hint: Use smart pointers in the future - from boost library or
// own proper implementation
class fgResourceGroup : public fgResource {
public:
	fgResourceGroup();
	~fgResourceGroup();

	virtual void clear(void);

	virtual bool create(void);
	virtual void destroy(void);
	virtual bool recreate(void);
	virtual void dispose(void);
	virtual bool isDisposed(void) const;

	// This will parse/load xml group config file. It wont
	// load or allocate any data - this is for 'create' to do.
	// This function will return false if file path is not set.
	virtual bool preLoadConfig(void);

	// Simple wrapper for managing the resource bundle
	struct fgResGroupItem {
		FG_RHANDLE rhandle;
		std::string resourceName;
		fgResource *resource;

		fgResGroupItem() {
			rhandle = FG_INVALID_RHANDLE;
			resourceName.clear();
			resource = NULL;
		}

		bool create(void) {
			if(resource)
				return resource->create();
			else
				return false;
		}

		void destroy(void) {
			if(resource)
				resource->destroy();
			resource = NULL;
			rhandle = FG_INVALID_RHANDLE;
		}

		bool recreate(void) {
			if(resource)
				return resource->recreate();
			else
				return false;
		}

		void dispose(void) {
			if(resource)
				resource->dispose();
		}

		size_t getSize(void) const {
			if(resource)
				return resource->getSize();
			else
				return 0;
		}

		bool isDisposed(void) const {
			if(resource)
				return resource->isDisposed();
			else
				return false;
		}
	};

protected:
	fgArrayVector<FG_RHANDLE> m_rHandles;
	// List of all resource files 
	fgArrayVector<fgResGroupItem> m_resourceFiles;

	// Parser for xml config files (here: resource group xml files)
	fgXMLParser *m_xmlParser;
};

#endif
