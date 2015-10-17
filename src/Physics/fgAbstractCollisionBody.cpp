/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgAbstractCollisionBody.cpp
 * Author: vigilant
 * 
 * Created on October 10, 2015, 12:29 AM
 */

#include "fgAbstractCollisionBody.h"

using namespace fg;
//------------------------------------------------------------------------------

physics::CAbstractCollisionBody::CAbstractCollisionBody(const BodyType bodyType) :
m_bodyType(bodyType),
m_pOwner(NULL) {
 }
//------------------------------------------------------------------------------

physics::CAbstractCollisionBody::CAbstractCollisionBody(const self_type& orig) :
self_type(orig.getBodyType()) { }
//------------------------------------------------------------------------------

physics::CAbstractCollisionBody::~CAbstractCollisionBody() {
    m_pOwner = NULL;
}
//------------------------------------------------------------------------------
