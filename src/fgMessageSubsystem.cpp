/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgMessageSubsystem.h"

template <>
bool fgSingleton<fgMessageSubsystem>::instanceFlag = false;

template <>
fgMessageSubsystem *fgSingleton<fgMessageSubsystem>::instance = NULL;

/*
 *
 */
fgMessageSubsystem::fgMessageSubsystem() 
{
}

/*
 *
 */
fgMessageSubsystem::~fgMessageSubsystem()
{
}

/*
 *
 */
void fgMessageSubsystem::clear(void) {
}

/*
 *
 */
void fgMessageSubsystem::destroy(void) {
}

/*
 *
 */
fgBool fgMessageSubsystem::initialize(void) {
	return FG_TRUE;
}
