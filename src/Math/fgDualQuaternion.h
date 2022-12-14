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
 * File:   fgDualQuaternion.h
 * Author: vigilant
 *
 * Created on September 8, 2015, 1:15 PM
 */

#ifndef FG_INC_MATH_DUAL_QUATERNION
    #define FG_INC_MATH_DUAL_QUATERNION
    #define FG_INC_MATH_DUAL_QUATERNION_BLOCK

    #include "fgVector3.h"
    #include "fgVector4.h"
    #include "fgMatrix3.h"
    #include "fgMatrix4.h"
    #include "fgQuaternion.h"

namespace fg {

    template <typename T, math::precision P>
    struct DualQuaternionT {
        typedef DualQuaternionT<T, P> self_type;
        typedef DualQuaternionT<T, P> type;
        typedef T value_type;
        typedef QuaternionT<T> quat_type;
        typedef math::detail::tvec3<T, P> vec_type;
        typedef math::detail::tvec3<T, P> vec3_type;
        typedef math::detail::tvec4<T, P> vec4_type;
        typedef math::detail::tmat3x3<T, P> mat3_type;
        typedef math::detail::tmat4x4<T, P> mat4_type;
        //----------------------------------------------------------------------
        /**
         *
         */
        DualQuaternionT() : q0(), qe() {
            initializeFrom(quat_type(1.0f, 0.0f, 0.0f, 0.0f),
                           vec3_type(0.0f, 0.0f, 0.0f));
        }
        /**
         * 
         * @param dq
         */
        DualQuaternionT(const self_type& dq) {
            this->q0 = dq.q0;
            this->qe = dq.qe;
        }
        /**
         *
         * @param _q0
         * @param _qe
         */
        DualQuaternionT(const quat_type& _q0, const quat_type& _qe) :
        q0(_q0), qe(_qe) {
            this->q0 = math::normalize(q0);
        }
        /**
         *
         * @param _q
         * @param v
         */
        DualQuaternionT(const quat_type& _q, const vec3_type& v) : q0(), qe() {
            initializeFrom(_q, v);
        }
        /**
         *
         * @param _q
         * @param v
         */
        DualQuaternionT(const quat_type& _q, const vec4_type& v) {
            initializeFrom(_q, vec3_type(v.x, v.y, v.z));
        }
        /**
         *
         * @param mat
         */
        DualQuaternionT(const mat4_type& mat) {            
            initializeFrom(math::toQuat(mat), vec3_type(mat[3].x, mat[3].y, mat[3].z));
        }
        /**
         *
         * @param mat
         */
        DualQuaternionT(const mat3_type& mat) {
            initializeFrom(math::toQuat(mat), vec3_type(0, 0, 0));
        }
        /**
         *
         * @param q
         * @param t
         */
        void initializeFrom(const quat_type& q, const vec3_type& t) {            
            this->q0 = math::normalize(q);            
            this->qe = (quat_type(0, t) * this->q0) * 0.5f;
        }
        /**
         *
         * @param mat
         */
        void initializeFrom(const mat3_type& mat) {
            initializeFrom(math::toQuat(mat), vec3_type(0, 0, 0));
        }
        /**
         * 
         * @param mat
         */
        void initializeFrom(const mat4_type& mat) {            
            initializeFrom(math::toQuat(mat), vec3_type(mat[3].x, mat[3].y, mat[3].z));
        }
        //----------------------------------------------------------------------
        /**
         *
         * @return
         */
        inline constexpr unsigned int length(void) const {
            return 8;
        }
        /**
         *
         * @param i
         * @return
         */
        inline T & operator [](unsigned int i) {
            if(i >= 0 && i < (unsigned int)q0.length()) {
                return q0[i];
            } else if(i >= (unsigned int)q0.length() && i<this->length()) {
                return qe[i - q0.length()];
            }
            return q0[0];
        }
        /**
         *
         * @param i
         * @return
         */
        inline T const & operator [](unsigned i)const {
            if(i >= 0 && i < (unsigned int)q0.length()) {
                return q0[i];
            } else if(i >= (unsigned int)q0.length() && i<this->length()) {
                return qe[i - q0.length()];
            }
            return q0[0];
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @param t
         */
        inline void getTranslation(vec3_type& t) const {
            T n = math::length(q0);
            // translation vector from dual quaternion part:
            t.x = ((value_type)2.0) * (-qe.w * q0.x + qe.x * q0.w - qe.y * q0.z + qe.z * q0.y) / n;
            t.y = ((value_type)2.0) * (-qe.w * q0.y + qe.x * q0.z + qe.y * q0.w - qe.z * q0.x) / n;
            t.z = ((value_type)2.0) * (-qe.w * q0.z - qe.x * q0.y + qe.y * q0.x + qe.z * q0.w) / n;
        }
        /**
         * 
         * @param t
         */
        inline void getTranslation(vec4_type& t) const {
            T n = math::length(q0);
            // translation vector from dual quaternion part:
            t.x = ((value_type)2.0) * (-qe.w * q0.x + qe.x * q0.w - qe.y * q0.z + qe.z * q0.y) / n;
            t.y = ((value_type)2.0) * (-qe.w * q0.y + qe.x * q0.z + qe.y * q0.w - qe.z * q0.x) / n;
            t.z = ((value_type)2.0) * (-qe.w * q0.z - qe.x * q0.y + qe.y * q0.x + qe.z * q0.w) / n;
            t.w = value_type(0.0);
        }        
        //----------------------------------------------------------------------
        /**
         *
         * @param v
         * @return
         */
        inline vec3_type transform(const vec3_type& v) const {
            // As the dual quaternions may be the results from a
            // linear blending we have to normalize it :
            value_type norm = math::length(q0);
            quat_type qblend_0 = q0 / norm;
            quat_type qblend_e = qe / norm;

            // Translation from the normalized dual quaternion equals :
            // 2.f * qblend_e * conjugate(qblend_0)
            vec3_type v0 = vec3_type(qblend_0.x, qblend_0.y, qblend_0.z);
            vec3_type ve = vec3_type(qblend_e.x, qblend_e.y, qblend_e.z);
            vec3_type trans = (ve * qblend_0.w - v0 * qblend_e.w + math::cross(v0, ve)) * value_type(2.0);
            // Rotate
            return math::rotate(qblend_0, v) + trans;
        }
        /**
         * 
         * @param v
         * @return 
         */
        inline vec4_type transform(const vec4_type& v) const {
            vec3_type rv3 = transform(vec3_type(v.x, v.y, v.z));
            return vec4_type(rv3.x, rv3.y, rv3.z, (value_type)0.0);
        }
        //----------------------------------------------------------------------
        /**
         *
         */
        inline void normalize(void) {
            value_type n = math::length(this->q0);
            this->q0 /= n;
            this->qe /= n;
        }
        /**
         *
         * @param v
         * @return
         */
        inline vec3_type rotate(const vec3_type& v) const {            
            return math::rotate(math::normalize(this->q0), v);
        }
        /**
         *
         * @param v
         * @return
         */
        inline vec4_type rotate(const vec4_type& v) const {            
            return math::rotate(math::normalize(this->q0), v);
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        mat4_type toMat4(void) const {
            // rotation matrix from non-dual part
            mat4_type mat = math::toMat4(this->q0);
            getTranslation(mat[3]);
            return mat;
        }
        /**
         * 
         * @return 
         */
        mat3_type toMat3(void) const {            
            return math::toMat3(this->q0);
        }
        /**
         * 
         * @param outMat
         */
        void toMat4(mat4_type& outMat) const {
            outMat = math::toMat4(this->q0);
            getTranslation(outMat[3]);
        }
        /**
         * 
         * @param outMat
         */
        void toMat3(mat3_type& outMat) const {
            outMat = math::toMat3(this->q0);
        }
        //----------------------------------------------------------------------
        /**
         *
         * @param in
         * @return
         */
        inline self_type& operator +=(const self_type& in) {
            this->q0 += in.q0;
            this->qe += in.qe;
            return *this;
        }
        /**
         *
         * @param in
         * @return
         */
        inline self_type& operator -=(const self_type& in) {
            this->q0 -= in.q0;
            this->qe -= in.qe;
            return *this;
        }
        /**
         *
         * @param s
         * @return
         */
        inline self_type& operator *=(const T s) {
            this->q0 *= s;
            this->qe *= s;
            return *this;
        }
        /**
         *
         * @param s
         * @return
         */
        inline self_type& operator /=(const T s) {
            this->q0 /= s;
            this->qe /= s;
            return *this;
        }
        //----------------------------------------------------------------------
    public:
        // Real part
        quat_type q0;
        // Dual part
        quat_type qe;
    }; // struct DualQuaternionT

    //--------------------------------------------------------------------------
    /**
     *
     * @param dq1
     * @param dq2
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator +(DualQuaternionT<T, P> const& dq1,
            DualQuaternionT<T, P> const& dq2) {
        DualQuaternionT<T, P> result = dq1;
        result += dq2;
        return result;
    }
    /**
     *
     * @param dq1
     * @param dq2
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator -(DualQuaternionT<T, P> const& dq1,
            DualQuaternionT<T, P> const& dq2) {
        DualQuaternionT<T, P> result = dq1;
        result -= dq2;
        return result;
    }
    /**
     *
     * @param dq
     * @param s
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator *(DualQuaternionT<T, P> const& dq, T const& s) {
        DualQuaternionT<T, P> result = dq;
        result *= s;
        return result;
    }
    /**
     *
     * @param s
     * @param dq
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator *(T const& s, DualQuaternionT<T, P> const& dq) {
        DualQuaternionT<T, P> result = dq;
        result *= s;
        return result;
    }
    /**
     * 
     * @param lhs
     * @param rhs
     * @return 
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator *(DualQuaternionT<T, P> const& lhs,
            DualQuaternionT<T, P> const& rhs) {
        return DualQuaternionT<T, P>(rhs.q0 * lhs.q0,
                rhs.qe * lhs.q0 + rhs.q0 * lhs.qe);
    }
    /**
     *
     * @param dq
     * @param s
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator /(DualQuaternionT<T, P> const& dq, T const& s) {
        DualQuaternionT<T, P> result = dq;
        result /= s;
        return result;
    }
    /**
     *
     * @param s
     * @param dq
     * @return
     */
    template<typename T, math::precision P>
    inline DualQuaternionT<T, P> operator /(T const& s, DualQuaternionT<T, P> const& dq) {
        DualQuaternionT<T, P> result = dq;
        result /= s;
        return result;
    }
    /**
     *
     * @param dq
     * @param v
     * @return
     */
    template<typename T, math::precision P>
    inline math::detail::tvec3<T, P> operator *(DualQuaternionT<T, P> const& dq,
            math::detail::tvec3<T, P> const& v) {
        return dq.transform(v);
    }
    /**
     *
     * @param dq
     * @param v
     * @return
     */
    template<typename T, math::precision P>
    inline math::detail::tvec4<T, P> operator *(DualQuaternionT<T, P> const& dq,
            math::detail::tvec4<T, P> const& v) {
        return dq.transform(v);
    }
    //--------------------------------------------------------------------------
} // namespace fg

namespace glm {
    /**
     *
     * @param dq
     * @return
     */
    template<typename T, precision P>
    inline detail::tmat3x3<T, P> toMat3(fg::DualQuaternionT<T, P> const& dq) {
        return dq.toMat3();
    }
    /**
     *
     * @param dq
     * @return
     */
    template<typename T, precision P>
    inline detail::tmat4x4<T, P> toMat4(fg::DualQuaternionT<T, P> const& dq) {
        return dq.toMat4();

    }
    /**
     *
     * @param dq
     * @param v
     * @return
     */
    template<typename T, precision P>
    inline detail::tvec3<T, P> rotate(fg::DualQuaternionT<T, P> const& dq,
                                      detail::tvec3<T, P> const& v) {
        return dq.rotate(v);
    }
    /**
     *
     * @param dq
     * @param v
     * @return
     */
    template<typename T, precision P>
    inline detail::tvec4<T, P> rotate(fg::DualQuaternionT<T, P> const& dq,
                                      detail::tvec4<T, P> const& v) {
        return dq.rotate(v);
    }
    /**
     *
     * @param dq
     * @param angle
     * @param axis
     * @return
     */
    template<typename T, precision P>
    inline fg::DualQuaternionT<T, P> rotate(fg::DualQuaternionT<T, P> const& dq,
                                            T const& angle,
                                            detail::tvec3<T, P> const& axis) {
        fg::DualQuaternionT<T, P> result = dq;
        result.q0 = glm::rotate(result.q0, angle, axis);
        return result;
    }
    /**
     *
     * @param dq
     * @return
     */
    template<typename T, precision P>
    inline T const * value_ptr(fg::DualQuaternionT<T, P> const& dq) {
        return &(dq[0]);
    }
    /**
     *
     * @param dq
     * @return
     */
    template<typename T, precision P>
    inline T * value_ptr(fg::DualQuaternionT<T, P>& dq) {
        return &(dq[0]);
    }

} // namespace math
namespace fg {
    typedef DualQuaternionT<float, math::precision::defaultp> DualQuaternionf;
    typedef DualQuaternionT<double, math::precision::defaultp> DualQuaterniond;

} // namespace fg

    #undef FG_INC_MATH_DUAL_QUATERNION_BLOCK
#endif /* FG_INC_MATH_DUAL_QUATERNION */
