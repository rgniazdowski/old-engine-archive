/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXPlane.h
 * Author: vigilant
 *
 * Created on November 13, 2014, 6:55 AM
 */

#ifndef _FG_GFX_PLANE_H_
    #define _FG_GFX_PLANE_H_
    #define _FG_GFX_PLANE_H_BLOCK_

    #include "fgGFXVertex.h"
    #include "Math/fgMathLib.h"

/**
 *
 */
template<class ValueType>
struct fgPlaneT {
    typedef fgPlaneT<ValueType> self_type;
    typedef fgVector3T<ValueType> vector_type;
    typedef ValueType value_type;

    ///
    vector_type n;
    ///
    vector_type p;
    ///
    value_type d;
    /**
     * 
     * @param v1
     * @param v2
     * @param v3
     */
    fgPlaneT(const vector_type &v1, const vector_type &v2, const vector_type &v3) {
        set(v1, v2, v3);
    }
    /**
     * 
     * @param other
     */
    fgPlaneT(const self_type& other) {
        this->n = other.n;
        this->p = other.p;
        this->d = other.d;
    }
    /**
     * 
     */
    fgPlaneT() : n(), p(), d(0) { }
    /**
     * 
     */
    ~fgPlaneT() { }

public:
    /**
     * 
     * @param v1
     * @param v2
     * @param v3
     */
    void set(const vector_type &v1, const vector_type &v2, const vector_type &v3) {
        vector_type aux1, aux2;

        aux1 = v1 - v2;
        aux2 = v3 - v2;

        this->n = aux2 * aux1;

        //normal.normalize();
        //normalize(n);
        this->n = fgMath::normalize(this->n);
        this->p = v2;
        this->d = -glm::dot(this->n, this->p);
        //d = -(normal.innerProduct(point));
    }
    /**
     * 
     * @param normal
     * @param point
     */
    void set(const vector_type &normal, const vector_type &point) {
        //this->n.copy(normal);
        //this->normal.normalize();
        this->n = glm::normalize(normal);
        this->p = point;
        this->d = -glm::dot(this->n, this->p);
    }
    /**
     * 
     * @param _a
     * @param _b
     * @param _c
     * @param _d
     */
    void setCoefficients(const float _a, const float _b, const float _c, const float _d) {
        // set the normal vector
        n = vector_type(_a, _b, _c);
        //compute the lenght of the vector
        float l = glm::length(n);
        // normalize the vector
        n = vector_type(_a / l, _b / l, _c / l);
        // and divide d by th length as well
        this->d = d / l;
    }
    /**
     * 
     * @param _p
     * @return 
     */
    float distance(const vector_type &_p) {
        return (d + glm::dot(n, _p));
        //return (d + normal.innerProduct(p));
    }

};

///
typedef fgPlaneT<int> fgPlanei;
///
typedef fgPlaneT<float> fgPlanef;
///
typedef fgPlaneT<unsigned int> fgPlaneu;
///
typedef fgPlaneT<double> fgPlaned;

    #undef _FG_GFX_PLANE_H_BLOCK_
#endif	/* _FG_GFX_PLANE_H_ */

