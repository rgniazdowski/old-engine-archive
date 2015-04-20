/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MATHLIB
    #define FG_INC_MATHLIB
    #define FG_INC_MATHLIB_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include <cmath>

    #if !defined(FG_RAND)
        #define FG_RAND(_A, _B) (_A + (int)(((float)(_B - _A + 1)) * rand() / (((float)RAND_MAX) + 1.0f)))
    #endif

    #if defined FG_USING_GLM
        #include "glm/common.hpp"
        #include "glm/vec2.hpp"
        #include "glm/vec3.hpp"
        #include "glm/vec4.hpp"
        #include "glm/mat3x3.hpp"
        #include "glm/mat4x4.hpp"
        #include "glm/geometric.hpp"
        #include "glm/gtx/component_wise.hpp"
        #include "glm/gtx/quaternion.hpp"
        #include "glm/gtx/norm.hpp"
        #include "glm/gtc/matrix_transform.hpp"
        #include "glm/gtc/matrix_inverse.hpp"
        #include "glm/gtc/epsilon.hpp"
        #include "glm/gtc/type_ptr.hpp"
    #endif

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

namespace fg {

    #if defined(FG_USING_GLM)
    namespace math {
        using namespace ::glm;

        namespace detail {
            using namespace ::glm::detail;
        }
        /**
         *
         * @param value
         * @return
         */
        inline fgBool isPowOf2(int value) {
            return (fgBool)((value & (value - 1)) == 0);
        }
        /**
         *
         * @param value
         * @param sv
         * @return
         */
        inline int toPow2(int value, int sv = 0x1) {
            while(value >>= 1) {
                sv <<= 1;
            }
            return sv;
        }
        /**
         *
         * @param a
         * @param b
         * @return
         */
        inline fgBool isZero(float a, float b = (float)0.00001) {
            if(a == (float)0.0)return FG_TRUE;
            return ( a > -b && a < b);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec2<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec3<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y + v.z * v.z);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec4<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec2<T, P> componentProduct(detail::tvec2<T, P> const & v1, detail::tvec2<T, P> const & v2) {
            return detail::tvec2<T, P>(v1.x * v2.x,
                    v1.y * v2.y);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec3<T, P> componentProduct(detail::tvec3<T, P> const & v1, detail::tvec3<T, P> const & v2) {
            return detail::tvec3<T, P>(v1.x * v2.x,
                    v1.y * v2.y,
                    v1.z * v2.z);
        }
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec4<T, P> componentProduct(detail::tvec4<T, P> const & v1, detail::tvec4<T, P> const & v2) {
            return detail::tvec4<T, P>(v1.x * v2.x,
                    v1.y * v2.y,
                    v1.z * v2.z,
                    v1.w * v2.w);
        }

    }; /* namespace math; */

        #if !defined(FG_MATH_GLM_VECTOR_MASK)
            #define FG_MATH_GLM_VECTOR_MASK

            #if !defined(FG_MATH_GLM_VECTOR_TEMPLATE_MASK)
                #define FG_MATH_GLM_VECTOR_TEMPLATE_MASK
    // #FIXME - This requires c++11
                #if defined(FG_USING_MARMALADE)

    template<typename T>
    struct Vector2T {
        typedef glm::detail::tvec2<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vector3T {
        typedef glm::detail::tvec3<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vector4T {
        typedef glm::detail::tvec4<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec2T {
        typedef glm::detail::tvec2<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec3T {
        typedef glm::detail::tvec3<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec4T {
        typedef glm::detail::tvec4<T, glm::defaultp> type;
    };
                #else
    template<typename T>
    using Vector2T = glm::detail::tvec2<T, glm::defaultp>;
    template<typename T>
    using Vector3T = glm::detail::tvec3<T, glm::defaultp>;
    template<typename T>
    using Vector4T = glm::detail::tvec4<T, glm::defaultp>;

    template<typename T>
    using Vec2T = glm::detail::tvec2<T, glm::defaultp>;
    template<typename T>
    using Vec3T = glm::detail::tvec3<T, glm::defaultp>;
    template<typename T>
    using Vec4T = glm::detail::tvec4<T, glm::defaultp>;
                #endif /* FG_USING_MARMALADE */
            #endif /* !defined(FG_MATH_GLM_VECTOR_TEMPLATE_MASK */

    typedef glm::bvec2 Vector2b;
    typedef glm::bvec3 Vector3b;
    typedef glm::bvec4 Vector4b;

    typedef glm::uvec2 Vector2u;
    typedef glm::uvec3 Vector3u;
    typedef glm::uvec4 Vector4u;

    typedef glm::ivec2 Vector2i;
    typedef glm::ivec3 Vector3i;
    typedef glm::ivec4 Vector4i;

    typedef glm::vec2 Vector2f;
    typedef glm::vec3 Vector3f;
    typedef glm::vec4 Vector4f;

    typedef glm::dvec2 Vector2d;
    typedef glm::dvec3 Vector3d;
    typedef glm::dvec4 Vector4d;
        #endif

        #if !defined(FG_MATH_GLM_MATRIX_MASK)
            #define FG_MATH_GLM_MATRIX_MASK

            #if !defined(FG_MATH_GLM_MATRIX_TEMPLATE_MASK)
                #define FG_MATH_GLM_MATRIX_TEMPLATE_MASK
    // #FIXME - This requires c++11 - alias template/typedef cap
                #if defined(FG_USING_MARMALADE)

    template<typename T>
    struct Matrix2T {
        typedef glm::detail::tmat2x2<T, glm::defaultp> type;
    };

    template<typename T>
    struct Matrix3T {
        typedef glm::detail::tmat3x3<T, glm::defaultp> type;
    };

    template<typename T>
    struct Matrix4T {
        typedef glm::detail::tmat4x4<T, glm::defaultp> type;
    };

    template<typename T>
    struct Mat2T {
        typedef glm::detail::tmat2x2<T, glm::defaultp> type;
    };

    template<typename T>
    struct Mat3T {
        typedef glm::detail::tmat3x3<T, glm::defaultp> type;
    };

    template<typename T>
    struct Mat4T {
        typedef glm::detail::tmat4x4<T, glm::defaultp> type;
    };
                #else
    template<typename T>
    using Matrix2T = glm::detail::tmat2x2<T, glm::defaultp>;
    template<typename T>
    using Matrix3T = glm::detail::tmat3x3<T, glm::defaultp>;
    template<typename T>
    using Matrix4T = glm::detail::tmat4x4<T, glm::defaultp>;

    template<typename T>
    using Mat2T = glm::detail::tmat2x2<T, glm::defaultp>;
    template<typename T>
    using Mat3T = glm::detail::tmat3x3<T, glm::defaultp>;
    template<typename T>
    using Mat4T = glm::detail::tmat4x4<T, glm::defaultp>;
                #endif /* FG_USING_MARMALADE */
            #endif /* !defined(FG_MATH_MATRIX_TEMPLATE_MASK) */

    typedef glm::mat2 Matrix2f;
    typedef glm::mat3 Matrix3f;
    typedef glm::mat4 Matrix4f;

    typedef glm::dmat2 Matrix2d;
    typedef glm::dmat3 Matrix3d;
    typedef glm::dmat4 Matrix4d;
        #endif /* !defined(FG_MATH_GLM_MATRIX_MASK) */

        #ifndef FG_MATH_GLM_QUAT_MASK
            #define FG_MATH_GLM_QUAT_MASK
    typedef glm::quat Quaternionf;
    typedef glm::dquat Quaterniond;
        #endif

    #else /* FG_USING_GLM */

    struct Vector2i;
    struct Vector2f;
    struct Vector3f;
    struct Vector4f;
    struct Matrix3f;
    struct Matrix4f;
    struct Quaterionf;

    /*****************************************************************************/
    /*                                                                           */
    /* Vector2f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Vector2i {
        inline Vector2i() : x(0), y(0) { }
        inline Vector2i(int x, int y) : x(x), y(y) { }
        inline Vector2i(const int *v) : x(v[0]), y(v[1]) { }
        inline Vector2i(const Vector2i &v) : x(v.x), y(v.y) { }
        inline int operator ==(const Vector2i &v) {
            return (x == v.x && y == v.y);
        }
        inline int operator !=(const Vector2i &v) {
            return !(*this == v);
        }
        inline const Vector2i operator *(int f)const {
            return Vector2i(int(x * f), int(y * f));
        }
        inline const Vector2i operator /(int f)const {
            return Vector2i(int(x / f), int(y / f));
        }
        inline const Vector2i operator +(const Vector2i &v) const {
            return Vector2i(x + v.x, y + v.y);
        }
        inline const Vector2i operator -() const {
            return Vector2i(-x, -y);
        }
        inline const Vector2i operator -(const Vector2i &v) const {
            return Vector2i(x - v.x, y - v.y);
        }
        inline Vector2i &operator *=(int f) {
            return *this = *this * f;
        }
        inline Vector2i &operator /=(int f) {
            return *this = *this / f;
        }
        inline Vector2i &operator +=(const Vector2i &v) {
            return *this = *this +v;
        }
        inline Vector2i &operator -=(const Vector2i &v) {
            return *this = *this -v;
        }
        inline int operator *(const Vector2i &v) const {
            return x * v.x + y * v.y;
        }
        inline operator int*() {
            return (int*)&x;
        }
        inline operator const int*() const {
            return (int*)&x;
        }
        inline int &operator [](int i) {
            return ((int*)&x)[i];
        }
        inline const int operator [](int i)const {
            return ((int*)&x)[i];
        }
        inline float length() const {
            return sqrtf(float(x * x + y * y));
        }

        union {

            struct {
                int x, y;
            };
            int v[2];
        };
    };

    /*****************************************************************************/
    /*                                                                           */
    /* Vector2f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Vector2f {
        inline Vector2f() : x(0), y(0) { }
        inline Vector2f(float x, float y) : x(x), y(y) { }
        inline Vector2f(const float *v) : x(v[0]), y(v[1]) { }
        inline Vector2f(const Vector2f &v) : x(v.x), y(v.y) { }
        inline int operator ==(const Vector2f &v) {
            return (fabs(x - v.x) < FG_EPSILON && fabs(y - v.y) < FG_EPSILON);
        }
        inline int operator !=(const Vector2f &v) {
            return !(*this == v);
        }
        inline const Vector2f operator *(float f)const {
            return Vector2f(x * f, y * f);
        }
        inline const Vector2f operator /(float f)const {
            return Vector2f(x / f, y / f);
        }
        inline const Vector2f operator +(const Vector2f &v) const {
            return Vector2f(x + v.x, y + v.y);
        }
        inline const Vector2f operator -() const {
            return Vector2f(-x, -y);
        }
        inline const Vector2f operator -(const Vector2f &v) const {
            return Vector2f(x - v.x, y - v.y);
        }
        inline Vector2f &operator *=(float f) {
            return *this = *this * f;
        }
        inline Vector2f &operator /=(float f) {
            return *this = *this / f;
        }
        inline Vector2f &operator +=(const Vector2f &v) {
            return *this = *this +v;
        }
        inline Vector2f &operator -=(const Vector2f &v) {
            return *this = *this -v;
        }
        inline float operator *(const Vector2f &v) const {
            return x * v.x + y * v.y;
        }
        inline operator float*() {
            return (float*)&x;
        }
        inline operator const float*() const {
            return (float*)&x;
        }
        inline float &operator [](int i) {
            return ((float*)&x)[i];
        }
        inline const float operator [](int i)const {
            return ((float*)&x)[i];
        }
        inline float length() const {
            return sqrtf(x * x + y * y);
        }
        inline float normalize() {
            float inv, length = sqrtf(x * x + y * y);
            if(length < FG_EPSILON) return 0.0;
            inv = 1.0f / length;
            x *= inv;
            y *= inv;
            return length;
        }

        union {

            struct {
                float x, y;
            };
            float v[2];
        };
    };

    /*****************************************************************************/
    /*                                                                           */
    /* Vector3f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Vector3f {
        inline Vector3f() : x(0), y(0), z(0) { }
        inline Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }
        inline Vector3f(const float *v) : x(v[0]), y(v[1]), z(v[2]) { }
        inline Vector3f(const Vector3f &v) : x(v.x), y(v.y), z(v.z) { }
        inline Vector3f(const Vector4f &v);
        inline int operator ==(const Vector3f &v) {
            return (fabs(x - v.x) < FG_EPSILON && fabs(y - v.y) < FG_EPSILON && fabs(z - v.z) < FG_EPSILON);
        }
        inline int operator !=(const Vector3f &v) {
            return !(*this == v);
        }
        inline const Vector3f operator *(float f)const {
            return Vector3f(x * f, y * f, z * f);
        }
        inline const Vector3f operator /(float f)const {
            return Vector3f(x / f, y / f, z / f);
        }
        inline const Vector3f operator +(const Vector3f &v) const {
            return Vector3f(x + v.x, y + v.y, z + v.z);
        }
        inline const Vector3f operator -() const {
            return Vector3f(-x, -y, -z);
        }
        inline const Vector3f operator -(const Vector3f &v) const {
            return Vector3f(x - v.x, y - v.y, z - v.z);
        }
        inline Vector3f &operator *=(float f) {
            return *this = *this * f;
        }
        inline Vector3f &operator /=(float f) {
            return *this = *this / f;
        }
        inline Vector3f &operator +=(const Vector3f &v) {
            return *this = *this +v;
        }
        inline Vector3f &operator -=(const Vector3f &v) {
            return *this = *this -v;
        }
        inline float operator *(const Vector3f &v) const {
            return x * v.x + y * v.y + z * v.z;
        }
        inline float operator *(const Vector4f &v) const;
        inline operator float*() {
            return (float*)&x;
        }
        inline operator const float*() const {
            return (float*)&x;
        }
        inline float &operator [](int i) {
            return ((float*)&x)[i];
        }
        inline const float operator [](int i)const {
            return ((float*)&x)[i];
        }
        inline float length() const {
            return sqrtf(x * x + y * y + z * z);
        }
        inline float normalize() {
            float inv, length = sqrtf(x * x + y * y + z * z);
            if(length < FG_EPSILON) return 0.0;
            inv = 1.0f / length;
            x *= inv;
            y *= inv;
            z *= inv;
            return length;
        }
        inline void cross(const Vector3f &v1, const Vector3f &v2) {
            x = v1.y * v2.z - v1.z * v2.y;
            y = v1.z * v2.x - v1.x * v2.z;
            z = v1.x * v2.y - v1.y * v2.x;
        }

        union {

            struct {
                float x, y, z;
            };
            float v[3];
        };
    };
    inline Vector3f cross(const Vector3f &v1, const Vector3f &v2) {
        Vector3f ret;
        ret.x = v1.y * v2.z - v1.z * v2.y;
        ret.y = v1.z * v2.x - v1.x * v2.z;
        ret.z = v1.x * v2.y - v1.y * v2.x;
        return ret;
    }

    /*****************************************************************************/
    /*                                                                           */
    /* Vector4f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Vector4f {
        inline Vector4f() : x(0), y(0), z(0), w(1) { }
        inline Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
        inline Vector4f(const float *v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) { }
        inline Vector4f(const Vector3f &v) : x(v.x), y(v.y), z(v.z), w(1) { }
        inline Vector4f(const Vector3f &v, float w) : x(v.x), y(v.y), z(v.z), w(w) { }
        inline Vector4f(const Vector4f &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
        inline int operator ==(const Vector4f &v) {
            return (fabs(x - v.x) < FG_EPSILON && fabs(y - v.y) < FG_EPSILON && fabs(z - v.z) < FG_EPSILON && fabs(w - v.w) < FG_EPSILON);
        }
        inline int operator !=(const Vector4f &v) {
            return !(*this == v);
        }
        inline const Vector4f operator *(float f)const {
            return Vector4f(x * f, y * f, z * f, w * f);
        }
        inline const Vector4f operator /(float f)const {
            return Vector4f(x / f, y / f, z / f, w / f);
        }
        inline const Vector4f operator +(const Vector4f &v) const {
            return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        inline const Vector4f operator -() const {
            return Vector4f(-x, -y, -z, -w);
        }
        inline const Vector4f operator -(const Vector4f &v) const {
            return Vector4f(x - v.x, y - v.y, z - v.z, z - v.w);
        }
        inline Vector4f &operator *=(float f) {
            return *this = *this * f;
        }
        inline Vector4f &operator /=(float f) {
            return *this = *this / f;
        }
        inline Vector4f &operator +=(const Vector4f &v) {
            return *this = *this +v;
        }
        inline Vector4f &operator -=(const Vector4f &v) {
            return *this = *this -v;
        }
        inline float operator *(const Vector3f &v) const {
            return x * v.x + y * v.y + z * v.z + w;
        }
        inline float operator *(const Vector4f &v) const {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }
        inline operator float*() {
            return (float*)&x;
        }
        inline operator const float*() const {
            return (float*)&x;
        }
        inline float &operator [](int i) {
            return ((float*)&x)[i];
        }
        inline const float operator [](int i)const {
            return ((float*)&x)[i];
        }

        union {

            struct {
                float x, y, z, w;
            };
            float v[4];
        };
    };
    inline Vector3f::Vector3f(const Vector4f &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    inline float Vector3f::operator *(const Vector4f &v) const {
        return x * v.x + y * v.y + z * v.z + v.w;
    }

    /*****************************************************************************/
    /*                                                                           */
    /* Matrix3f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Matrix3f {
        Matrix3f() {
            mat[0] = 1.0;
            mat[3] = 0.0;
            mat[6] = 0.0;
            mat[1] = 0.0;
            mat[4] = 1.0;
            mat[7] = 0.0;
            mat[2] = 0.0;
            mat[5] = 0.0;
            mat[8] = 1.0;
        }
        Matrix3f(const float *m) {
            mat[0] = m[0];
            mat[3] = m[3];
            mat[6] = m[6];
            mat[1] = m[1];
            mat[4] = m[4];
            mat[7] = m[7];
            mat[2] = m[2];
            mat[5] = m[5];
            mat[8] = m[8];
        }
        Matrix3f(const Matrix3f &m) {
            mat[0] = m[0];
            mat[3] = m[3];
            mat[6] = m[6];
            mat[1] = m[1];
            mat[4] = m[4];
            mat[7] = m[7];
            mat[2] = m[2];
            mat[5] = m[5];
            mat[8] = m[8];
        }
        Matrix3f(const Matrix4f &m);
        Vector3f operator *(const Vector3f &v) const {
            Vector3f ret;
            ret[0] = mat[0] * v[0] + mat[3] * v[1] + mat[6] * v[2];
            ret[1] = mat[1] * v[0] + mat[4] * v[1] + mat[7] * v[2];
            ret[2] = mat[2] * v[0] + mat[5] * v[1] + mat[8] * v[2];
            return ret;
        }
        Vector4f operator *(const Vector4f &v) const {
            Vector4f ret;
            ret[0] = mat[0] * v[0] + mat[3] * v[1] + mat[6] * v[2];
            ret[1] = mat[1] * v[0] + mat[4] * v[1] + mat[7] * v[2];
            ret[2] = mat[2] * v[0] + mat[5] * v[1] + mat[8] * v[2];
            ret[3] = v[3];
            return ret;
        }
        Matrix3f operator *(float f)const {
            Matrix3f ret;
            ret[0] = mat[0] * f;
            ret[3] = mat[3] * f;
            ret[6] = mat[6] * f;
            ret[1] = mat[1] * f;
            ret[4] = mat[4] * f;
            ret[7] = mat[7] * f;
            ret[2] = mat[2] * f;
            ret[5] = mat[5] * f;
            ret[8] = mat[8] * f;
            return ret;
        }
        Matrix3f operator *(const Matrix3f &m) const {
            Matrix3f ret;
            ret[0] = mat[0] * m[0] + mat[3] * m[1] + mat[6] * m[2];
            ret[1] = mat[1] * m[0] + mat[4] * m[1] + mat[7] * m[2];
            ret[2] = mat[2] * m[0] + mat[5] * m[1] + mat[8] * m[2];
            ret[3] = mat[0] * m[3] + mat[3] * m[4] + mat[6] * m[5];
            ret[4] = mat[1] * m[3] + mat[4] * m[4] + mat[7] * m[5];
            ret[5] = mat[2] * m[3] + mat[5] * m[4] + mat[8] * m[5];
            ret[6] = mat[0] * m[6] + mat[3] * m[7] + mat[6] * m[8];
            ret[7] = mat[1] * m[6] + mat[4] * m[7] + mat[7] * m[8];
            ret[8] = mat[2] * m[6] + mat[5] * m[7] + mat[8] * m[8];
            return ret;
        }
        Matrix3f operator +(const Matrix3f &m) const {
            Matrix3f ret;
            ret[0] = mat[0] + m[0];
            ret[3] = mat[3] + m[3];
            ret[6] = mat[6] + m[6];
            ret[1] = mat[1] + m[1];
            ret[4] = mat[4] + m[4];
            ret[7] = mat[7] + m[7];
            ret[2] = mat[2] + m[2];
            ret[5] = mat[5] + m[5];
            ret[8] = mat[8] + m[8];
            return ret;
        }
        Matrix3f operator -(const Matrix3f &m) const {
            Matrix3f ret;
            ret[0] = mat[0] - m[0];
            ret[3] = mat[3] - m[3];
            ret[6] = mat[6] - m[6];
            ret[1] = mat[1] - m[1];
            ret[4] = mat[4] - m[4];
            ret[7] = mat[7] - m[7];
            ret[2] = mat[2] - m[2];
            ret[5] = mat[5] - m[5];
            ret[8] = mat[8] - m[8];
            return ret;
        }
        Matrix3f &operator *=(float f) {
            return *this = *this * f;
        }
        Matrix3f &operator *=(const Matrix3f &m) {
            return *this = *this * m;
        }
        Matrix3f &operator +=(const Matrix3f &m) {
            return *this = *this +m;
        }
        Matrix3f &operator -=(const Matrix3f &m) {
            return *this = *this -m;
        }
        operator float*() {
            return mat;
        }
        operator const float*() const {
            return mat;
        }
        float &operator [](int i) {
            return mat[i];
        }
        const float operator [](int i)const {
            return mat[i];
        }
        Matrix3f transpose() const {
            Matrix3f ret;
            ret[0] = mat[0];
            ret[3] = mat[1];
            ret[6] = mat[2];
            ret[1] = mat[3];
            ret[4] = mat[4];
            ret[7] = mat[5];
            ret[2] = mat[6];
            ret[5] = mat[7];
            ret[8] = mat[8];
            return ret;
        }
        float det() const {
            float det;
            det = mat[0] * mat[4] * mat[8];
            det += mat[3] * mat[7] * mat[2];
            det += mat[6] * mat[1] * mat[5];
            det -= mat[6] * mat[4] * mat[2];
            det -= mat[3] * mat[1] * mat[8];
            det -= mat[0] * mat[7] * mat[5];
            return det;
        }
        Matrix3f inverse() const {
            Matrix3f ret;
            float idet = 1.0f / det();
            ret[0] = (mat[4] * mat[8] - mat[7] * mat[5]) * idet;
            ret[1] = -(mat[1] * mat[8] - mat[7] * mat[2]) * idet;
            ret[2] = (mat[1] * mat[5] - mat[4] * mat[2]) * idet;
            ret[3] = -(mat[3] * mat[8] - mat[6] * mat[5]) * idet;
            ret[4] = (mat[0] * mat[8] - mat[6] * mat[2]) * idet;
            ret[5] = -(mat[0] * mat[5] - mat[3] * mat[2]) * idet;
            ret[6] = (mat[3] * mat[7] - mat[6] * mat[4]) * idet;
            ret[7] = -(mat[0] * mat[7] - mat[6] * mat[1]) * idet;
            ret[8] = (mat[0] * mat[4] - mat[3] * mat[1]) * idet;
            return ret;
        }
        void zero() {
            mat[0] = 0.0;
            mat[3] = 0.0;
            mat[6] = 0.0;
            mat[1] = 0.0;
            mat[4] = 0.0;
            mat[7] = 0.0;
            mat[2] = 0.0;
            mat[5] = 0.0;
            mat[8] = 0.0;
        }
        void identity() {
            mat[0] = 1.0;
            mat[3] = 0.0;
            mat[6] = 0.0;
            mat[1] = 0.0;
            mat[4] = 1.0;
            mat[7] = 0.0;
            mat[2] = 0.0;
            mat[5] = 0.0;
            mat[8] = 1.0;
        }
        void rotate(const Vector3f &axis, float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            Vector3f v = axis;
            v.normalize();
            float xx = v.x * v.x;
            float yy = v.y * v.y;
            float zz = v.z * v.z;
            float xy = v.x * v.y;
            float yz = v.y * v.z;
            float zx = v.z * v.x;
            float xs = v.x * s;
            float ys = v.y * s;
            float zs = v.z * s;
            mat[0] = (1.0f - c) * xx + c;
            mat[3] = (1.0f - c) * xy - zs;
            mat[6] = (1.0f - c) * zx + ys;
            mat[1] = (1.0f - c) * xy + zs;
            mat[4] = (1.0f - c) * yy + c;
            mat[7] = (1.0f - c) * yz - xs;
            mat[2] = (1.0f - c) * zx - ys;
            mat[5] = (1.0f - c) * yz + xs;
            mat[8] = (1.0f - c) * zz + c;
        }
        void rotate(float x, float y, float z, float angle) {
            rotate(Vector3f(x, y, z), angle);
        }
        void rotate_x(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = 1.0;
            mat[3] = 0.0;
            mat[6] = 0.0;
            mat[1] = 0.0;
            mat[4] = c;
            mat[7] = -s;
            mat[2] = 0.0;
            mat[5] = s;
            mat[8] = c;
        }
        void rotate_y(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = c;
            mat[3] = 0.0;
            mat[6] = s;
            mat[1] = 0.0;
            mat[4] = 1.0;
            mat[7] = 0.0;
            mat[2] = -s;
            mat[5] = 0.0;
            mat[8] = c;
        }
        void rotate_z(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = c;
            mat[3] = -s;
            mat[6] = 0.0;
            mat[1] = s;
            mat[4] = c;
            mat[7] = 0.0;
            mat[2] = 0.0;
            mat[5] = 0.0;
            mat[8] = 1.0;
        }
        void scale(const Vector3f &v) {
            mat[0] = v.x;
            mat[3] = 0.0;
            mat[6] = 0.0;
            mat[1] = 0.0;
            mat[4] = v.y;
            mat[7] = 0.0;
            mat[2] = 0.0;
            mat[5] = 0.0;
            mat[8] = v.z;
        }
        void scale(float x, float y, float z) {
            scale(Vector3f(x, y, z));
        }
        void orthonormalize() {
            Vector3f x(mat[0], mat[1], mat[2]);
            Vector3f y(mat[3], mat[4], mat[5]);
            Vector3f z;
            x.normalize();
            z.cross(x, y);
            z.normalize();
            y.cross(z, x);
            y.normalize();
            mat[0] = x.x;
            mat[3] = y.x;
            mat[6] = z.x;
            mat[1] = x.y;
            mat[4] = y.y;
            mat[7] = z.y;
            mat[2] = x.z;
            mat[5] = y.z;
            mat[8] = z.z;
        }

        float mat[9];
    };

    /*****************************************************************************/
    /*                                                                           */
    /* Matrix4f                                                                  */
    /*                                                                           */

    /*****************************************************************************/

    struct Matrix4f {
        Matrix4f() {
            mat[0] = 1.0;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = 1.0;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = 1.0;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        Matrix4f(const Vector3f &v) {
            translate(v);
        }
        Matrix4f(float x, float y, float z) {
            translate(x, y, z);
        }
        Matrix4f(const Vector3f &axis, float angle) {
            rotate(axis, angle);
        }
        Matrix4f(float x, float y, float z, float angle) {
            rotate(x, y, z, angle);
        }
        Matrix4f(const Matrix3f &m) {
            mat[0] = m[0];
            mat[4] = m[3];
            mat[8] = m[6];
            mat[12] = 0.0;
            mat[1] = m[1];
            mat[5] = m[4];
            mat[9] = m[7];
            mat[13] = 0.0;
            mat[2] = m[2];
            mat[6] = m[5];
            mat[10] = m[8];
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        Matrix4f(const float *m) {
            mat[0] = m[0];
            mat[4] = m[4];
            mat[8] = m[8];
            mat[12] = m[12];
            mat[1] = m[1];
            mat[5] = m[5];
            mat[9] = m[9];
            mat[13] = m[13];
            mat[2] = m[2];
            mat[6] = m[6];
            mat[10] = m[10];
            mat[14] = m[14];
            mat[3] = m[3];
            mat[7] = m[7];
            mat[11] = m[11];
            mat[15] = m[15];
        }
        Matrix4f(const Matrix4f &m) {
            mat[0] = m[0];
            mat[4] = m[4];
            mat[8] = m[8];
            mat[12] = m[12];
            mat[1] = m[1];
            mat[5] = m[5];
            mat[9] = m[9];
            mat[13] = m[13];
            mat[2] = m[2];
            mat[6] = m[6];
            mat[10] = m[10];
            mat[14] = m[14];
            mat[3] = m[3];
            mat[7] = m[7];
            mat[11] = m[11];
            mat[15] = m[15];
        }
        Vector3f operator *(const Vector3f &v) const {
            Vector3f ret;
            ret[0] = mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2] + mat[12];
            ret[1] = mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2] + mat[13];
            ret[2] = mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2] + mat[14];
            return ret;
        }
        Vector4f operator *(const Vector4f &v) const {
            Vector4f ret;
            ret[0] = mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2] + mat[12] * v[3];
            ret[1] = mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2] + mat[13] * v[3];
            ret[2] = mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2] + mat[14] * v[3];
            ret[3] = mat[3] * v[0] + mat[7] * v[1] + mat[11] * v[2] + mat[15] * v[3];
            return ret;
        }
        Matrix4f operator *(float f)const {
            Matrix4f ret;
            ret[0] = mat[0] * f;
            ret[4] = mat[4] * f;
            ret[8] = mat[8] * f;
            ret[12] = mat[12] * f;
            ret[1] = mat[1] * f;
            ret[5] = mat[5] * f;
            ret[9] = mat[9] * f;
            ret[13] = mat[13] * f;
            ret[2] = mat[2] * f;
            ret[6] = mat[6] * f;
            ret[10] = mat[10] * f;
            ret[14] = mat[14] * f;
            ret[3] = mat[3] * f;
            ret[7] = mat[7] * f;
            ret[11] = mat[11] * f;
            ret[15] = mat[15] * f;
            return ret;
        }
        Matrix4f operator *(const Matrix4f &m) const {
            Matrix4f ret;
            ret[0] = mat[0] * m[0] + mat[4] * m[1] + mat[8] * m[2] + mat[12] * m[3];
            ret[1] = mat[1] * m[0] + mat[5] * m[1] + mat[9] * m[2] + mat[13] * m[3];
            ret[2] = mat[2] * m[0] + mat[6] * m[1] + mat[10] * m[2] + mat[14] * m[3];
            ret[3] = mat[3] * m[0] + mat[7] * m[1] + mat[11] * m[2] + mat[15] * m[3];
            ret[4] = mat[0] * m[4] + mat[4] * m[5] + mat[8] * m[6] + mat[12] * m[7];
            ret[5] = mat[1] * m[4] + mat[5] * m[5] + mat[9] * m[6] + mat[13] * m[7];
            ret[6] = mat[2] * m[4] + mat[6] * m[5] + mat[10] * m[6] + mat[14] * m[7];
            ret[7] = mat[3] * m[4] + mat[7] * m[5] + mat[11] * m[6] + mat[15] * m[7];
            ret[8] = mat[0] * m[8] + mat[4] * m[9] + mat[8] * m[10] + mat[12] * m[11];
            ret[9] = mat[1] * m[8] + mat[5] * m[9] + mat[9] * m[10] + mat[13] * m[11];
            ret[10] = mat[2] * m[8] + mat[6] * m[9] + mat[10] * m[10] + mat[14] * m[11];
            ret[11] = mat[3] * m[8] + mat[7] * m[9] + mat[11] * m[10] + mat[15] * m[11];
            ret[12] = mat[0] * m[12] + mat[4] * m[13] + mat[8] * m[14] + mat[12] * m[15];
            ret[13] = mat[1] * m[12] + mat[5] * m[13] + mat[9] * m[14] + mat[13] * m[15];
            ret[14] = mat[2] * m[12] + mat[6] * m[13] + mat[10] * m[14] + mat[14] * m[15];
            ret[15] = mat[3] * m[12] + mat[7] * m[13] + mat[11] * m[14] + mat[15] * m[15];
            return ret;
        }
        Matrix4f operator +(const Matrix4f &m) const {
            Matrix4f ret;
            ret[0] = mat[0] + m[0];
            ret[4] = mat[4] + m[4];
            ret[8] = mat[8] + m[8];
            ret[12] = mat[12] + m[12];
            ret[1] = mat[1] + m[1];
            ret[5] = mat[5] + m[5];
            ret[9] = mat[9] + m[9];
            ret[13] = mat[13] + m[13];
            ret[2] = mat[2] + m[2];
            ret[6] = mat[6] + m[6];
            ret[10] = mat[10] + m[10];
            ret[14] = mat[14] + m[14];
            ret[3] = mat[3] + m[3];
            ret[7] = mat[7] + m[7];
            ret[11] = mat[11] + m[11];
            ret[15] = mat[15] + m[15];
            return ret;
        }
        Matrix4f operator -(const Matrix4f &m) const {
            Matrix4f ret;
            ret[0] = mat[0] - m[0];
            ret[4] = mat[4] - m[4];
            ret[8] = mat[8] - m[8];
            ret[12] = mat[12] - m[12];
            ret[1] = mat[1] - m[1];
            ret[5] = mat[5] - m[5];
            ret[9] = mat[9] - m[9];
            ret[13] = mat[13] - m[13];
            ret[2] = mat[2] - m[2];
            ret[6] = mat[6] - m[6];
            ret[10] = mat[10] - m[10];
            ret[14] = mat[14] - m[14];
            ret[3] = mat[3] - m[3];
            ret[7] = mat[7] - m[7];
            ret[11] = mat[11] - m[11];
            ret[15] = mat[15] - m[15];
            return ret;
        }
        Matrix4f &operator *=(float f) {
            return *this = *this * f;
        }
        Matrix4f &operator *=(const Matrix4f &m) {
            return *this = *this * m;
        }
        Matrix4f &operator +=(const Matrix4f &m) {
            return *this = *this +m;
        }
        Matrix4f &operator -=(const Matrix4f &m) {
            return *this = *this -m;
        }
        operator float*() {
            return mat;
        }
        operator const float*() const {
            return mat;
        }
        float &operator [](int i) {
            return mat[i];
        }
        const float operator [](int i)const {
            return mat[i];
        }
        Matrix4f rotation() const {
            Matrix4f ret;
            ret[0] = mat[0];
            ret[4] = mat[4];
            ret[8] = mat[8];
            ret[12] = 0;
            ret[1] = mat[1];
            ret[5] = mat[5];
            ret[9] = mat[9];
            ret[13] = 0;
            ret[2] = mat[2];
            ret[6] = mat[6];
            ret[10] = mat[10];
            ret[14] = 0;
            ret[3] = 0;
            ret[7] = 0;
            ret[11] = 0;
            ret[15] = 1;
            return ret;
        }
        Matrix4f transpose() const {
            Matrix4f ret;
            ret[0] = mat[0];
            ret[4] = mat[1];
            ret[8] = mat[2];
            ret[12] = mat[3];
            ret[1] = mat[4];
            ret[5] = mat[5];
            ret[9] = mat[6];
            ret[13] = mat[7];
            ret[2] = mat[8];
            ret[6] = mat[9];
            ret[10] = mat[10];
            ret[14] = mat[11];
            ret[3] = mat[12];
            ret[7] = mat[13];
            ret[11] = mat[14];
            ret[15] = mat[15];
            return ret;
        }
        Matrix4f transpose_rotation() const {
            Matrix4f ret;
            ret[0] = mat[0];
            ret[4] = mat[1];
            ret[8] = mat[2];
            ret[12] = mat[12];
            ret[1] = mat[4];
            ret[5] = mat[5];
            ret[9] = mat[6];
            ret[13] = mat[13];
            ret[2] = mat[8];
            ret[6] = mat[9];
            ret[10] = mat[10];
            ret[14] = mat[14];
            ret[3] = mat[3];
            ret[7] = mat[7];
            ret[14] = mat[14];
            ret[15] = mat[15];
            return ret;
        }
        float det() const {
            float det;
            det = mat[0] * mat[5] * mat[10];
            det += mat[4] * mat[9] * mat[2];
            det += mat[8] * mat[1] * mat[6];
            det -= mat[8] * mat[5] * mat[2];
            det -= mat[4] * mat[1] * mat[10];
            det -= mat[0] * mat[9] * mat[6];
            return det;
        }
        Matrix4f inverse() const {
            Matrix4f ret;
            float idet = 1.0f / det();
            ret[0] = (mat[5] * mat[10] - mat[9] * mat[6]) * idet;
            ret[1] = -(mat[1] * mat[10] - mat[9] * mat[2]) * idet;
            ret[2] = (mat[1] * mat[6] - mat[5] * mat[2]) * idet;
            ret[3] = 0.0;
            ret[4] = -(mat[4] * mat[10] - mat[8] * mat[6]) * idet;
            ret[5] = (mat[0] * mat[10] - mat[8] * mat[2]) * idet;
            ret[6] = -(mat[0] * mat[6] - mat[4] * mat[2]) * idet;
            ret[7] = 0.0;
            ret[8] = (mat[4] * mat[9] - mat[8] * mat[5]) * idet;
            ret[9] = -(mat[0] * mat[9] - mat[8] * mat[1]) * idet;
            ret[10] = (mat[0] * mat[5] - mat[4] * mat[1]) * idet;
            ret[11] = 0.0;
            ret[12] = -(mat[12] * ret[0] + mat[13] * ret[4] + mat[14] * ret[8]);
            ret[13] = -(mat[12] * ret[1] + mat[13] * ret[5] + mat[14] * ret[9]);
            ret[14] = -(mat[12] * ret[2] + mat[13] * ret[6] + mat[14] * ret[10]);
            ret[15] = 1.0;
            return ret;
        }
        void zero() {
            mat[0] = 0.0;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = 0.0;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = 0.0;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 0.0;
        }
        void identity() {
            mat[0] = 1.0;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = 1.0;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = 1.0;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void rotate(const Vector3f &axis, float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            Vector3f v = axis;
            v.normalize();
            float xx = v.x * v.x;
            float yy = v.y * v.y;
            float zz = v.z * v.z;
            float xy = v.x * v.y;
            float yz = v.y * v.z;
            float zx = v.z * v.x;
            float xs = v.x * s;
            float ys = v.y * s;
            float zs = v.z * s;
            mat[0] = (1.0f - c) * xx + c;
            mat[4] = (1.0f - c) * xy - zs;
            mat[8] = (1.0f - c) * zx + ys;
            mat[12] = 0.0;
            mat[1] = (1.0f - c) * xy + zs;
            mat[5] = (1.0f - c) * yy + c;
            mat[9] = (1.0f - c) * yz - xs;
            mat[13] = 0.0;
            mat[2] = (1.0f - c) * zx - ys;
            mat[6] = (1.0f - c) * yz + xs;
            mat[10] = (1.0f - c) * zz + c;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void rotate(float x, float y, float z, float angle) {
            rotate(Vector3f(x, y, z), angle);
        }
        void rotate_x(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = 1.0;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = c;
            mat[9] = -s;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = s;
            mat[10] = c;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void rotate_y(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = c;
            mat[4] = 0.0;
            mat[8] = s;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = 1.0;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = -s;
            mat[6] = 0.0;
            mat[10] = c;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void rotate_z(float angle) {
            float rad = angle * FG_DEG2RAD;
            float c = cosf(rad);
            float s = sinf(rad);
            mat[0] = c;
            mat[4] = -s;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = s;
            mat[5] = c;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = 1.0;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void scale(const Vector3f &v) {
            mat[0] = v.x;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = v.y;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = v.z;
            mat[14] = 0.0;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void scale(float x, float y, float z) {
            scale(Vector3f(x, y, z));
        }
        void translate(const Vector3f &v) {
            mat[0] = 1.0;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = v.x;
            mat[1] = 0.0;
            mat[5] = 1.0;
            mat[9] = 0.0;
            mat[13] = v.y;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = 1.0;
            mat[14] = v.z;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void translate(float x, float y, float z) {
            translate(Vector3f(x, y, z));
        }
        void reflect(const Vector4f &plane) {
            float x = plane.x;
            float y = plane.y;
            float z = plane.z;
            float x2 = x * 2.0f;
            float y2 = y * 2.0f;
            float z2 = z * 2.0f;
            mat[0] = 1.0f - x * x2;
            mat[4] = -y * x2;
            mat[8] = -z * x2;
            mat[12] = -plane.w * x2;
            mat[1] = -x * y2;
            mat[5] = 1.0f - y * y2;
            mat[9] = -z * y2;
            mat[13] = -plane.w * y2;
            mat[2] = -x * z2;
            mat[6] = -y * z2;
            mat[10] = 1.0f - z * z2;
            mat[14] = -plane.w * z2;
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = 0.0;
            mat[15] = 1.0;
        }
        void reflect(float x, float y, float z, float w) {
            reflect(Vector4f(x, y, z, w));
        }
        void perspective(float fov, float aspect, float znear, float zfar) {
            float y = tanf(fov * FG_DEG2RAD);
            float x = y * aspect;
            mat[0] = 1.0f / x;
            mat[4] = 0.0;
            mat[8] = 0.0;
            mat[12] = 0.0;
            mat[1] = 0.0;
            mat[5] = 1.0f / y;
            mat[9] = 0.0;
            mat[13] = 0.0;
            mat[2] = 0.0;
            mat[6] = 0.0;
            mat[10] = -(zfar + znear) / (zfar - znear);
            mat[14] = -(2.0f * zfar * znear) / (zfar - znear);
            mat[3] = 0.0;
            mat[7] = 0.0;
            mat[11] = -1.0;
            mat[15] = 0.0;
        }
        void look_at(const Vector3f &eye, const Vector3f &dir, const Vector3f &up) {
            Vector3f x, y, z;
            Matrix4f m0, m1;
            z = eye - dir;
            z.normalize();
            x.cross(up, z);
            x.normalize();
            y.cross(z, x);
            y.normalize();
            m0[0] = x.x;
            m0[4] = x.y;
            m0[8] = x.z;
            m0[12] = 0.0;
            m0[1] = y.x;
            m0[5] = y.y;
            m0[9] = y.z;
            m0[13] = 0.0;
            m0[2] = z.x;
            m0[6] = z.y;
            m0[10] = z.z;
            m0[14] = 0.0;
            m0[3] = 0.0;
            m0[7] = 0.0;
            m0[11] = 0.0;
            m0[15] = 1.0;
            m1.translate(-eye);
            *this = m0 * m1;
        }
        void look_at(const float *eye, const float *dir, const float *up) {
            look_at(Vector3f(eye), Vector3f(dir), Vector3f(up));
        }

        float mat[16];
    };
    inline Matrix3f::Matrix3f(const Matrix4f &m) {
        mat[0] = m[0];
        mat[3] = m[4];
        mat[6] = m[8];
        mat[1] = m[1];
        mat[4] = m[5];
        mat[7] = m[9];
        mat[2] = m[2];
        mat[5] = m[6];
        mat[8] = m[10];
    }

    /*****************************************************************************/
    /*                                                                           */
    /* Quaterionf                                                                */
    /*                                                                           */

    /*****************************************************************************/

    struct Quaterionf {
        Quaterionf() : x(0), y(0), z(0), w(1) { }
        Quaterionf(const Vector3f &dir, float angle) {
            set(dir, angle);
        }
        Quaterionf(float x, float y, float z, float angle) {
            set(x, y, z, angle);
        }
        Quaterionf(const Matrix3f &m) {
            float trace = m[0] + m[4] + m[8];
            if(trace > 0.0) {
                float s = sqrtf(trace + 1.0f);
                q[3] = 0.5f * s;
                s = 0.5f / s;
                q[0] = (m[5] - m[7]) * s;
                q[1] = (m[6] - m[2]) * s;
                q[2] = (m[1] - m[3]) * s;
            } else {
                static int next[3] = {1, 2, 0};
                int i = 0;
                if(m[4] > m[0]) i = 1;
                if(m[8] > m[3 * i + i]) i = 2;
                int j = next[i];
                int k = next[j];
                float s = sqrtf(m[3 * i + i] - m[3 * j + j] - m[3 * k + k] + 1.0f);
                q[i] = 0.5f * s;
                if(s != 0) s = 0.5f / s;
                q[3] = (m[3 * j + k] - m[3 * k + j]) * s;
                q[j] = (m[3 * i + j] + m[3 * j + i]) * s;
                q[k] = (m[3 * i + k] + m[3 * k + i]) * s;
            }
        }
        operator float*() {
            return (float*)&x;
        }
        operator const float*() const {
            return (float*)&x;
        }
        float &operator [](int i) {
            return ((float*)&x)[i];
        }
        const float operator [](int i)const {
            return ((float*)&x)[i];
        }
        Quaterionf operator *(const Quaterionf &q) const {
            Quaterionf ret;
            ret.x = w * q.x + x * q.x + y * q.z - z * q.y;
            ret.y = w * q.y + y * q.w + z * q.x - x * q.z;
            ret.z = w * q.z + z * q.w + x * q.y - y * q.x;
            ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
            return ret;
        }
        void set(const Vector3f &dir, float angle) {
            float length = dir.length();
            if(length != 0.0) {
                length = 1.0f / length;
                float sinangle = sinf(angle * FG_DEG2RAD / 2.0f);
                x = dir[0] * length * sinangle;
                y = dir[1] * length * sinangle;
                z = dir[2] * length * sinangle;
                w = cosf(angle * FG_DEG2RAD / 2.0f);
            } else {
                x = y = z = 0.0;
                w = 1.0;
            }
        }
        void set(float x, float y, float z, float angle) {
            set(Vector3f(x, y, z), angle);
        }
        void slerp(const Quaterionf &q0, const Quaterionf &q1, float t) {
            float k0, k1, cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
            Quaterionf q;
            if(cosomega < 0.0) {
                cosomega = -cosomega;
                q.x = -q1.x;
                q.y = -q1.y;
                q.z = -q1.z;
                q.w = -q1.w;
            } else {
                q.x = q1.x;
                q.y = q1.y;
                q.z = q1.z;
                q.w = q1.w;
            }
            if(1.0 - cosomega > 1e-6) {
                float omega = acosf(cosomega);
                float sinomega = sinf(omega);
                k0 = sinf((1.0f - t) * omega) / sinomega;
                k1 = sinf(t * omega) / sinomega;
            } else {
                k0 = 1.0f - t;
                k1 = t;
            }
            x = q0.x * k0 + q.x * k1;
            y = q0.y * k0 + q.y * k1;
            z = q0.z * k0 + q.z * k1;
            w = q0.w * k0 + q.w * k1;
        }
        Matrix3f to_matrix() const {
            Matrix3f ret;
            float x2 = x + x;
            float y2 = y + y;
            float z2 = z + z;
            float xx = x * x2;
            float yy = y * y2;
            float zz = z * z2;
            float xy = x * y2;
            float yz = y * z2;
            float xz = z * x2;
            float wx = w * x2;
            float wy = w * y2;
            float wz = w * z2;
            ret[0] = 1.0f - (yy + zz);
            ret[3] = xy - wz;
            ret[6] = xz + wy;
            ret[1] = xy + wz;
            ret[4] = 1.0f - (xx + zz);
            ret[7] = yz - wx;
            ret[2] = xz - wy;
            ret[5] = yz + wx;
            ret[8] = 1.0f - (xx + yy);
            return ret;
        }

        union {

            struct {
                float x, y, z, w;
            };
            float q[4];
        };
    };
    #endif /* FG_USING_GLM */



    #ifdef FG_MATH_GLM_VECTOR_MASK
    typedef Vector2b Vec2b;
    typedef Vector3b Vec3b;
    typedef Vector4b Vec4b;

    typedef Vector2u Vec2u;
    typedef Vector3u Vec3u;
    typedef Vector4u Vec4u;

    typedef Vector2i Vec2i;
    typedef Vector3i Vec3i;
    typedef Vector4i Vec4i;

    typedef Vector2f Vec2f;
    typedef Vector3f Vec3f;
    typedef Vector4f Vec4f;

    typedef Vector2d Vec2d;
    typedef Vector3d Vec3d;
    typedef Vector4d Vec4d;

    #endif /* FG_MATH_GLM_VECTOR_MASK */

    #if defined(FG_MATH_GLM_MATRIX_MASK)

    typedef Matrix2f Mat2f;
    typedef Matrix3f Mat3f;
    typedef Matrix4f Mat4f;

    typedef Matrix2d Mat2d;
    typedef Matrix3d Mat3d;
    typedef Matrix4d Mat4d;
    #endif /* FG_MATH_GLM_MATRIX_MASK */

    #ifdef FG_MATH_GLM_QUAT_MASK
    typedef Quaternionf Quatf;
    typedef Quaterniond Quatd;
    #endif /* FG_MATH_GLM_QUAT_MASK */

}; /* namespace fg; */

    #undef FG_INC_MATHLIB_BLOCK
#endif /* FG_INC_MATHLIB */
