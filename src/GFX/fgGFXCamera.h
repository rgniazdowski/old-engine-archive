/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_CAMERA_H_
    #define _FG_GFX_CAMERA_H_

// FIXME! #mathlib too big?
    #include "Math/fgMathLib.h"

/*
 * Simple wrapper class for functions regarding the View matrix
 * Contains special vectors (eye, center, up) and uses lookAt
 */
class fgGfxCamera {
public:
    // Default constructor for camera object
    fgGfxCamera() : m_up(0.0f, 1.0f, 0.0f) { }

    // Default destructor for camera object
    virtual ~fgGfxCamera() { }

    // Returns reference to the internal view matrix
    inline fgMatrix4f & getRefViewMatrix(void) {
        return m_viewMatrix;
    }

    // Updates the view matrix based on the internal vector values
    virtual float * update(void) {
        m_viewMatrix = glm::lookAt(m_eye, m_center, m_up);
        return getViewMatPtr();
    }

    // Returns the pointer to the view matrix
    inline const float * getViewMatPtr(void) const {
        return glm::value_ptr(m_viewMatrix);
    }

    // Returns the pointer to the view matrix
    inline float * getViewMatPtr(void) {
        return glm::value_ptr(m_viewMatrix);
    }

    //
    inline void setEye(const fgVec3f& eye) {
        m_eye = eye;
    }

    //
    inline void setCenter(const fgVec3f& center) {
        m_center = center;
    }

    //
    inline void setUp(const fgVec3f& up) {
        m_up = up;
    }

    // Returns the reference to the eye vector
    inline fgVec3f & getRefEye(void) {
        return m_eye;
    }
    // Returns the reference to the center vector
    inline fgVec3f & getRefCenter(void) {
        return m_center;
    }
    // Returns the reference to the up vector
    inline fgVec3f & getRefUp(void) {
        return m_up;
    }

    // Returns the reference to the eye vector
    inline const fgVec3f & getRefEye(void) const {
        return m_eye;
    }
    // Returns the reference to the center vector
    inline const fgVec3f & getRefCenter(void) const {
        return m_center;
    }
    // Returns the reference to the up vector
    inline const fgVec3f & getRefUp(void) const {
        return m_up;
    }

    // Returns the pointer to the eye vector data
    inline const float * getPtrEye(void) const {
        return glm::value_ptr(m_eye);
    }

    // Returns the pointer to the eye vector data
    inline float * getPtrEye(void) {
        return glm::value_ptr(m_eye);
    }

    // Returns the pointer to the center vector data
    inline const float * getPtrCenter(void) const {
        return glm::value_ptr(m_center);
    }

    // Returns the pointer to the center vector data
    inline float * getPtrCenter(void) {
        return glm::value_ptr(m_center);
    }

    //  Returns the pointer to the up vector data
    inline const float * getPtrUp(void) const {
        return glm::value_ptr(m_up);
    }

    // Returns the pointer to the up vector data
    inline float * getPtrUp(void) {
        return glm::value_ptr(m_up);
    }

    // Resets the internal view matrix
    // The internal vectors (eye,...) are unchanged
    inline void identity(void) {
        m_viewMatrix = fgMatrix4f();
    }

protected:
    /// The view matrix of this camera
    fgMatrix4f m_viewMatrix;
    /// Position of the camera in world space
    fgVec3f m_eye;
    /// Where the camera is looking?
    fgVec3f m_center;
    /// Head by default will be up (0,1,0)
    fgVec3f m_up;
};

#endif /* _FG_GFX_CAMERA_H_ */
