/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceGroup.h"

/*
 *
 */
fgResourceGroup::fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::fgResourceGroup(); constructor");
}

/*
 *
 */
fgResourceGroup::~fgResourceGroup()
{
	FG_WriteLog("fgResourceGroup::~fgResourceGroup(); deconstructor");
	destroy();
}

/*
 *
 */
void fgResourceGroup::clear(void)
{
	fgResource::clear();
	m_rHandles.clear_optimised();
	m_resourceFiles.clear_optimised();
}

/*
 *
 */
bool fgResourceGroup::create(void)
{
	return true;
}

/*
 *
 */
void fgResourceGroup::destroy(void)
{
	FG_WriteLog("fgResourceGroup::destroy();");
}

/*
 *
 */
bool fgResourceGroup::recreate(void)
{
	return true;
}

/*
 *
 */
void fgResourceGroup::dispose(void)
{
	FG_WriteLog("fgResourceGroup::~dispose();");
}

/*
 *
 */
bool fgResourceGroup::isDisposed(void) const
{
	return false;
}

/*
 *
 */
bool fgResourceGroup::preLoadConfig(void)
{
	if(strnlen(m_filePath,sizeof(m_filePath)) == 0)
		return false;
	m_xmlParser = new fgXMLParser();
	// #FIXME #TODO P2 now this loading code for xml should be a lot different - 
	// probably somewhere in the future there needs to be some automatic loader / wrapper
	// for loading xml directly in to proper structures - or at least an xml wrapper that 
	// will parse deeply - recursively, no matter how much tag nesting there is - 
	// something like SAXParser(?) in Java... that's a good idea.
	if(!m_xmlParser)
	{
		// #TODO P2 error messages 
		return false;
	}
	m_xmlParser->loadXML(m_filePath);
	const char *rootName = m_xmlParser->getRootElementValue();

	printf("Root node name: '%s'\n", rootName);
	// Parsing attributes
	if(m_xmlParser->setFirstAttribute())
	{
		do {
			printf(" %ss' attribute '%s' value: '%s\n", rootName, m_xmlParser->getCurrentAttributeName(), m_xmlParser->getCurrentAttributeValue());
		} while(m_xmlParser->goToNextAttribute());
	}
	if(m_xmlParser->isXMLLoaded())
	{
		m_xmlParser->goDeeper();
		do {
			printf("Roots' child node name: '%s'\n", m_xmlParser->getCurrentNodeValue());
			const char *childName = m_xmlParser->getCurrentNodeValue();

			// Parsing attributes
			if(m_xmlParser->setFirstAttribute())
			{
				do {
					printf(" %ss' attribute '%s' value: '%s\n", childName, m_xmlParser->getCurrentAttributeName(), m_xmlParser->getCurrentAttributeValue());
				} while(m_xmlParser->goToNextAttribute());
			}

			// Parsing children nodes
			if(m_xmlParser->getCurrentNodeChildrenPresence())
			{
				m_xmlParser->goDeeper();
				do {
					printf("   %ss' child node (%s) name: '%s'\n", childName, (m_xmlParser->isCurrentElement() ? "ELEMENT" : "TEXT"), m_xmlParser->getCurrentNodeValue());
				} while(m_xmlParser->goToNextNode());
				m_xmlParser->goHigher();
			}
		} while(m_xmlParser->goToNextNode());
	}
	delete m_xmlParser;
	m_xmlParser = NULL;
	return true;
}