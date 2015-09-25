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
 * Implementation file for the coarse collision detector.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgCollisionCoarse.h"
#if !defined(FG_USING_BULLET)
using namespace fg;
//------------------------------------------------------------------------------

physics::SBoundingSphere::SBoundingSphere(const Vector3f &centre, real radius) {
    SBoundingSphere::centre = centre;
    SBoundingSphere::radius = radius;
}
//------------------------------------------------------------------------------

physics::SBoundingSphere::SBoundingSphere(const SBoundingSphere &one,
                                          const SBoundingSphere &two) {
    Vector3f centreOffset = two.centre - one.centre;
    real distance = math::squareLength(centreOffset);
    real radiusDiff = two.radius - one.radius;

    // Check if the larger sphere encloses the small one
    if(radiusDiff * radiusDiff >= distance) {
        if(one.radius > two.radius) {
            centre = one.centre;
            radius = one.radius;
        } else {
            centre = two.centre;
            radius = two.radius;
        }
    }// Otherwise we need to work with partially
        // overlapping spheres
    else {
        distance = real_sqrt(distance);
        radius = (distance + one.radius + two.radius) * ((real)0.5);

        // The new centre is based on one's centre, moved towards
        // two's centre by an ammount proportional to the spheres'
        // radii.
        centre = one.centre;
        if(distance > 0) {
            centre += centreOffset * ((radius - one.radius) / distance);
        }
    }

}
//------------------------------------------------------------------------------

bool physics::SBoundingSphere::overlaps(const SBoundingSphere *other) const {
    //real distanceSquared = (centre - other->centre).squareMagnitude();
    real distanceSquared = math::squareLength(centre - other->centre);
    return distanceSquared < (radius + other->radius)*(radius + other->radius);
}
//------------------------------------------------------------------------------

physics::real physics::SBoundingSphere::getGrowth(const SBoundingSphere &other) const {
    SBoundingSphere newSphere(*this, other);

    // We return a value proportional to the change in surface
    // area of the sphere.
    return newSphere.radius * newSphere.radius - radius*radius;
}
//------------------------------------------------------------------------------
#endif /* FG_USING_BULLET */
