/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_CAMERA_ANIMATION_H_
    #define _FG_GFX_CAMERA_ANIMATION_H_

    #include "fgGFXCamera.h"
    #include "fgGFXTypes.h"

typedef unsigned int fgGfxCameraType;

// Fly mode (like in noclip :)
    #define FG_GFX_CAMERA_FREE		1
// Locked/centered to some point, eye can change (rotate above the center point)
    #define FG_GFX_CAMERA_CENTER_LOCKED	2
// Locked to look at some object, follows it at the distance if it moves
// position of the eye changes automatically
    #define FG_GFX_CAMERA_FOLLOW	3
// Camera walks the specified path (checkpoints)
    #define FG_GFX_CAMERA_PATH		4

/*
 *
 */
class fgGfxCameraAnimation : public fgGfxCamera {
public:
    //
    fgGfxCameraAnimation(const fgGfxCameraType type = FG_GFX_CAMERA_FREE);
    //
    virtual ~fgGfxCameraAnimation();

    //
    virtual float * update(void);

    //
    virtual float * update(fgGFXfloat mouseXrel, fgGFXfloat mouseYrel);

    //
    void moveLeft(void);

    //
    void moveRight(void);

    //
    void moveForward(void);

    //
    void moveBackward(void);

    //
    void moveUp(void);

    //
    void moveDown(void);

    //
    inline void setType(fgGfxCameraType type) {
        m_type = type;
    }
    //
    inline fgGfxCameraType getType(void) const {
        return m_type;
    }

    //
    inline fgVec3f& getRefDirection(void) {
        return m_direction;
    }

    //
    inline fgVec3f& getRefRight(void) {
        return m_right;
    }

    //
    inline void setAngleH(fgGFXfloat angle) {
        m_hAngle = angle;
    }
    //
    inline fgGFXfloat getAngleH(void) const {
        return m_hAngle;
    }

    //
    inline void setAngleV(fgGFXfloat angle) {
        m_vAngle = angle;
    }
    //
    inline fgGFXfloat getAngleV(void) const {
        return m_vAngle;
    }

    //
    inline void setSpeed(fgGFXfloat speed) {
        m_speed = speed;
    }
    //
    inline fgGFXfloat getSpeed(void) const {
        return m_speed;
    }

    //
    inline void setMouseSpeed(fgGFXfloat mouseSpeed) {
        m_mouseSpeed = mouseSpeed;
    }
    //
    inline fgGFXfloat getMouseSpeed(void) const {
        return m_mouseSpeed;
    }

    //
    inline void setZoom(fgGFXfloat zoom) {
        m_zoom = zoom;
    }
    //
    inline fgGFXfloat getZoom(void) const {
        return m_mouseSpeed;
    }

    //
    inline void setDistance(fgGFXfloat distance) {
        m_distance = distance;
    }
    //
    inline fgGFXfloat getDistance(void) const {
        return m_distance;
    }

    //
    inline void setDT(fgGFXfloat dt) {
        m_dt = dt;
    }

private:
    ///
    fgGfxCameraType m_type;
    ///
    fgVec3f m_direction;
    ///
    fgVec3f m_right;
    ///
    fgGFXfloat m_hAngle;
    ///
    fgGFXfloat m_vAngle;
    ///
    fgGFXfloat m_speed;
    ///
    fgGFXfloat m_mouseSpeed;
    ///
    fgGFXfloat m_zoom;

    union {
        ///
        fgGFXfloat m_distance;
        ///
        fgGFXfloat m_radius;
    };
    ///
    fgGFXfloat m_dt;
};

#endif /* _FG_GFX_CAMERA_ANIMATION_H_ */
