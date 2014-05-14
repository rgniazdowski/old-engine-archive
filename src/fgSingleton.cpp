/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include <iostream>
#include "fgSingleton.h"

template <typename Class>
bool fgSingleton<Class>::instanceFlag = false;

template <typename Class>
Class *fgSingleton<Class>::instance = NULL;