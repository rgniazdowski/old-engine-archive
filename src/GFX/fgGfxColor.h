/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_COLOR
    #define FG_INC_GFX_COLOR

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #if defined(FG_USING_GLM)
        #include "glm/vec3.hpp"
        #include "glm/vec4.hpp"

namespace fg {
        #ifndef FG_MATH_GLM_COLOR_MASK
            #define FG_MATH_GLM_COLOR_MASK
    typedef ::glm::vec3 Color3f;
    typedef ::glm::vec4 Color4f;

    typedef ::glm::ivec3 Color3i;
    typedef ::glm::ivec4 Color4i;

    typedef ::glm::uvec3 Color3u;
    typedef ::glm::uvec4 Color4u;

        #endif /* FG_MATH_GLM_COLOR_MASK */
}
    #else

        #include <cmath>

        #ifndef FG_EPSILON
            #define FG_EPSILON 1e-6f
        #endif

        #ifndef M_PI
            #define M_PI 3.14159265358979323846
        #endif

struct Color3f;
struct Color4f;

struct Color3f {
    inline Color3f() : r(0), g(0), b(0) { }
    inline Color3f(float r, float g, float b) : r(r), g(g), b(b) { }
    inline Color3f(const float *c) : r(c[0]), g(c[1]), b(c[2]) { }
    inline Color3f(const Color3f &c) : r(c.r), g(c.g), b(c.b) { }
    inline Color3f(const Color4f &c);
    inline int operator ==(const Color3f &c) {
        return (fabs(r - c.r) < FG_EPSILON && fabs(g - c.g) < FG_EPSILON && fabs(b - c.b) < FG_EPSILON);
    }
    inline int operator !=(const Color3f &c) {
        return !(*this == c);
    }
    inline const Color3f operator *(float f)const {
        return Color3f(r * f, g * f, b * f);
    }
    inline const Color3f operator /(float f)const {
        return Color3f(r / f, g / f, b / f);
    }
    inline const Color3f operator +(const Color3f &c) const {
        return Color3f(r + c.r, g + c.g, b + c.b);
    }
    inline const Color3f operator -() const {
        return Color3f(-r, -g, -b);
    }
    inline const Color3f operator -(const Color3f &c) const {
        return Color3f(r - c.r, g - c.g, b - c.b);
    }
    inline Color3f &operator *=(float f) {
        return *this = *this * f;
    }
    inline Color3f &operator /=(float f) {
        return *this = *this / f;
    }
    inline Color3f &operator +=(const Color3f &c) {
        return *this = *this +c;
    }
    inline Color3f &operator -=(const Color3f &c) {
        return *this = *this -c;
    }
    inline float operator *(const Color3f &c) const {
        return r * c.r + g * c.g + b * c.b;
    }
    inline float operator *(const Color4f &c) const;
    inline operator float*() {
        return (float*)&r;
    }
    inline operator const float*() const {
        return (float*)&r;
    }
    inline float &operator [](int i) {
        return ((float*)&r)[i];
    }
    inline const float operator [](int i)const {
        return ((float*)&r)[i];
    }
    inline float length() const {
        return sqrtf(r * r + g * g + b * b);
    }
    inline float normalibe() {
        float inv, length = sqrtf(r * r + g * g + b * b);
        if(length < FG_EPSILON) return 0.0;
        inv = 1.0f / length;
        r *= inv;
        g *= inv;
        b *= inv;
        return length;
    }
    inline void cross(const Color3f &c1, const Color3f &c2) {
        r = c1.g * c2.b - c1.b * c2.g;
        g = c1.b * c2.r - c1.r * c2.b;
        b = c1.r * c2.g - c1.g * c2.r;
    }

    union {

        struct {
            float r, g, b;
        };
        float color[3];
        float c[3];
    };
};
inline Color3f cross(const Color3f &c1, const Color3f &c2) {
    Color3f ret;
    ret.r = c1.g * c2.b - c1.b * c2.g;
    ret.g = c1.b * c2.r - c1.r * c2.b;
    ret.b = c1.r * c2.g - c1.g * c2.r;
    return ret;
}

struct Color4f {
    inline Color4f() : r(0), g(0), b(0), a(1.0f) { }
    inline Color4f(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
    inline Color4f(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) { }
    inline Color4f(const float *c) : r(c[0]), g(c[1]), b(c[2]), a(c[3]) { }
    inline Color4f(const Color3f &c) : r(c.r), g(c.g), b(c.b), a(1) { }
    inline Color4f(const Color3f &c, float a) : r(c.r), g(c.g), b(c.b), a(a) { }
    inline Color4f(const Color4f &c) : r(c.r), g(c.g), b(c.b), a(c.a) { }
    inline int operator ==(const Color4f &c) {
        return (fabs(r - c.r) < FG_EPSILON && fabs(g - c.g) < FG_EPSILON && fabs(b - c.b) < FG_EPSILON && fabs(a - c.a) < FG_EPSILON);
    }
    inline int operator !=(const Color4f &c) {
        return !(*this == c);
    }
    inline const Color4f operator *(float f)const {
        return Color4f(r * f, g * f, b * f, a * f);
    }
    inline const Color4f operator /(float f)const {
        return Color4f(r / f, g / f, b / f, a / f);
    }
    inline const Color4f operator +(const Color4f &c) const {
        return Color4f(r + c.r, g + c.g, b + c.b, a + c.a);
    }
    inline const Color4f operator -() const {
        return Color4f(-r, -g, -b, -a);
    }
    inline const Color4f operator -(const Color4f &c) const {
        return Color4f(r - c.r, g - c.g, b - c.b, b - c.a);
    }
    inline Color4f &operator *=(float f) {
        return *this = *this * f;
    }
    inline Color4f &operator /=(float f) {
        return *this = *this / f;
    }
    inline Color4f &operator +=(const Color4f &c) {
        return *this = *this +c;
    }
    inline Color4f &operator -=(const Color4f &c) {
        return *this = *this -c;
    }
    inline float operator *(const Color3f &c) const {
        return r * c.r + g * c.g + b * c.b + a;
    }
    inline float operator *(const Color4f &c) const {
        return r * c.r + g * c.g + b * c.b + a * c.a;
    }
    inline operator float*() {
        return (float*)&r;
    }
    inline operator const float*() const {
        return (float*)&r;
    }
    inline float &operator [](int i) {
        return ((float*)&r)[i];
    }
    inline const float operator [](int i)const {
        return ((float*)&r)[i];
    }

    union {

        struct {
            float r, g, b, a;
        };
        float color[4];
        float c[4];
    };
};
inline Color3f::fgColor3f(const Color4f &c) {
    r = c.r;
    g = c.g;
    b = c.b;
}
inline float Color3f::operator *(const Color4f &c) const {
    return r * c.r + g * c.g + b * c.b + c.a;
}

typedef Color4f Color4f;

    #endif /* FG_USING_GLM */

#endif /* FG_INC_GFX_COLOR */
