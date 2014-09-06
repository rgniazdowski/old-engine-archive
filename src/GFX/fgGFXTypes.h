/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_TYPES_H_
#define _FG_GFX_TYPES_H_

#include <cmath>

#ifndef FG_EPSILON
#define FG_EPSILON 1e-6f
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PIF
#define M_PIF 3.14159265358979323846f
#endif

#ifndef FG_DEG2RAD
#define FG_DEG2RAD (M_PIF / 180.0f)
#endif
#ifndef FG_RAD2DEG
#define FG_RAD2DEG (180.0f / M_PIF)
#endif

struct fgColor3f;
struct fgColor4f;

struct fgColor3f {
	
	inline fgColor3f() : r(0), g(0), b(0) { }
	inline fgColor3f(float r,float g,float b) : r(r), g(g), b(b) { }
	inline fgColor3f(const float *c) : r(c[0]), g(c[1]), b(c[2]) { }
	inline fgColor3f(const fgColor3f &c) : r(c.r), g(c.g), b(c.b) { }
	inline fgColor3f(const fgColor4f &c);
	
	inline int operator==(const fgColor3f &c) { return (fabs(r - c.r) < FG_EPSILON && fabs(g - c.g) < FG_EPSILON && fabs(b - c.b) < FG_EPSILON); }
	inline int operator!=(const fgColor3f &c) { return !(*this == c); }
	
	inline const fgColor3f operator*(float f) const { return fgColor3f(r * f,g * f,b * f); }
	inline const fgColor3f operator/(float f) const { return fgColor3f(r / f,g / f,b / f); }
	inline const fgColor3f operator+(const fgColor3f &c) const { return fgColor3f(r + c.r,g + c.g,b + c.b); }
	inline const fgColor3f operator-() const { return fgColor3f(-r,-g,-b); }
	inline const fgColor3f operator-(const fgColor3f &c) const { return fgColor3f(r - c.r,g - c.g,b - c.b); }
	
	inline fgColor3f &operator*=(float f) { return *this = *this * f; }
	inline fgColor3f &operator/=(float f) { return *this = *this / f; }
	inline fgColor3f &operator+=(const fgColor3f &c) { return *this = *this + c; }
	inline fgColor3f &operator-=(const fgColor3f &c) { return *this = *this - c; }
	
	inline float operator*(const fgColor3f &c) const { return r * c.r + g * c.g + b * c.b; }
	inline float operator*(const fgColor4f &c) const;
	
	inline operator float*() { return (float*)&r; }
	inline operator const float*() const { return (float*)&r; }
	
	inline float &operator[](int i) { return ((float*)&r)[i]; }
	inline const float operator[](int i) const { return ((float*)&r)[i]; }
	
	inline float length() const { return sqrtf(r * r + g * g + b * b); }
	inline float normalibe() {
		float inv,length = sqrtf(r * r + g * g + b * b);
		if(length < FG_EPSILON) return 0.0;
		inv = 1.0f / length;
		r *= inv;
		g *= inv;
		b *= inv;
		return length;
	}
	inline void cross(const fgColor3f &c1,const fgColor3f &c2) {
		r = c1.g * c2.b - c1.b * c2.g;
		g = c1.b * c2.r - c1.r * c2.b;
		b = c1.r * c2.g - c1.g * c2.r;
	}
	
	union {
		struct {
			float r,g,b;
		};
		float color[3];
		float c[3];
	};
};

inline fgColor3f cross(const fgColor3f &c1,const fgColor3f &c2) {
	fgColor3f ret;
	ret.r = c1.g * c2.b - c1.b * c2.g;
	ret.g = c1.b * c2.r - c1.r * c2.b;
	ret.b = c1.r * c2.g - c1.g * c2.r;
	return ret;
}

struct fgColor4f {
	
	inline fgColor4f() : r(0), g(0), b(0), a(1.0f) { }
	inline fgColor4f(float r,float g,float b,float a) : r(r), g(g), b(b), a(a) { }
	inline fgColor4f(float r,float g,float b) : r(r), g(g), b(b), a(1.0f) { }
	inline fgColor4f(const float *c) : r(c[0]), g(c[1]), b(c[2]), a(c[3]) { }
	inline fgColor4f(const fgColor3f &c) : r(c.r), g(c.g), b(c.b), a(1) { }
	inline fgColor4f(const fgColor3f &c,float a) : r(c.r), g(c.g), b(c.b), a(a) { }
	inline fgColor4f(const fgColor4f &c) : r(c.r), g(c.g), b(c.b), a(c.a) { }
	
	inline int operator==(const fgColor4f &c) { return (fabs(r - c.r) < FG_EPSILON && fabs(g - c.g) < FG_EPSILON && fabs(b - c.b) < FG_EPSILON && fabs(a - c.a) < FG_EPSILON); }
	inline int operator!=(const fgColor4f &c) { return !(*this == c); }
	
	inline const fgColor4f operator*(float f) const { return fgColor4f(r * f,g * f,b * f,a * f); }
	inline const fgColor4f operator/(float f) const { return fgColor4f(r / f,g / f,b / f,a / f); }
	inline const fgColor4f operator+(const fgColor4f &c) const { return fgColor4f(r + c.r,g + c.g,b + c.b,a + c.a); }
	inline const fgColor4f operator-() const { return fgColor4f(-r,-g,-b,-a); }
	inline const fgColor4f operator-(const fgColor4f &c) const { return fgColor4f(r - c.r,g - c.g,b - c.b,b - c.a); }
	
	inline fgColor4f &operator*=(float f) { return *this = *this * f; }
	inline fgColor4f &operator/=(float f) { return *this = *this / f; }
	inline fgColor4f &operator+=(const fgColor4f &c) { return *this = *this + c; }
	inline fgColor4f &operator-=(const fgColor4f &c) { return *this = *this - c; }
	
	inline float operator*(const fgColor3f &c) const { return r * c.r + g * c.g + b * c.b + a; }
	inline float operator*(const fgColor4f &c) const { return r * c.r + g * c.g + b * c.b + a * c.a; }
	
	inline operator float*() { return (float*)&r; }
	inline operator const float*() const { return (float*)&r; }
	
	inline float &operator[](int i) { return ((float*)&r)[i]; }
	inline const float operator[](int i) const { return ((float*)&r)[i]; }
	
	union {
		struct {
			float r,g,b,a;
		};		
		float color[4];
		float c[4];
	};
};

inline fgColor3f::fgColor3f(const fgColor4f &c) {
	r = c.r;
	g = c.g;
	b = c.b;
}

inline float fgColor3f::operator*(const fgColor4f &c) const {
	return r * c.r + g * c.g + b * c.b + c.a;
}

typedef fgColor4f fgColor;

// #FIXME FG_AREA, fgArea, standard !
struct fgArea
{
		int x;
		int y;
		int w;
		int h;
		fgArea(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
		fgArea() : x(0), y(0), w(0), h(0) {}

        int left() const {
            return x;
        }

        int right() const {
            return x + w;
        }

        int top() const {
            return y;
        }

        int bottom() const {
            return y + h;
        }

        int width() const {
            return w;
        }

        int height() const {
            return h;
        }

        void set_left(int l) {
            x = l;
        }

        void set_right(int r) {
            w = r - x;
        }

        void set_top(int t) {
            y = t;
        }

        void set_bottom(int b) {
            h = b - y;
        }

        void set_width(int _w) {
            w = _w;
        }

        void set_height(int _h) {
            h = _h;
        }
};

#endif /* _FG_GFX_TYPES_H_ */
