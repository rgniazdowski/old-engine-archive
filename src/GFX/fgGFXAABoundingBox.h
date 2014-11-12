/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXAABoundingBox.h
 * Author: vigilant
 *
 * Created on November 11, 2014, 6:52 PM
 */

#ifndef _FG_GFX_AA_BOUNDING_BOX_H_
    #define _FG_GFX_AA_BOUNDING_BOX_H_
    #define _FG_GFX_AA_BOUNDING_BOX_H_BLOCK_

    #if defined(_FG_GFX_BOUNDING_BOX_H_BLOCK_)
        #error "FG_GFX_BOUNDING_BOX_H_BLOCK is defined. Do not include AA Bounding Box header inside of a regular Bounding Box header!"
    #endif

    #ifndef _FG_GFX_BOUNDING_BOX_H_
        #include "fgGFXBoundingBox.h"
    #endif

//
template <class ValueType> struct fgAABoundingBox2DT;
//
template <class ValueType> struct fgAABoundingBox3DT;

/**
 *
 */
template <class ValueType>
struct fgAABoundingBox2DT : fgBoundingBoxT<fgAABoundingBox2DT<ValueType>, fgVector2T<ValueType>, ValueType> {
    typedef fgAABoundingBox2DT<ValueType> self_type;
    ///
    typedef fgVector2T<ValueType> vec_type;
    ///
    typedef fgBoundingBoxT<self_type, vec_type, ValueType> base_type;
    ///
    typedef typename base_type::size_type size_type;
    ///
    typedef typename base_type::value_type value_type;
    ///
    typedef typename base_type::vector_type vector_type;
    /**
     * 
     */
    fgAABoundingBox2DT() :
    base_type() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgAABoundingBox2DT(const vec_type &_pos, const vec_type &_size) :
    base_type(_pos, _size) { }
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    self_type &merge(const self_type &a, const self_type &b) {
        this->zero();

        this->min.x = glm::min(this->min.x, a.min.x);
        this->min.y = glm::min(this->min.y, a.min.y);
        this->max.x = glm::max(this->max.x, a.max.x);
        this->max.y = glm::max(this->max.y, a.max.y);

        this->min.x = glm::min(this->min.x, b.min.x);
        this->min.y = glm::min(this->min.y, b.min.y);
        this->max.x = glm::max(this->max.x, b.max.x);
        this->max.y = glm::max(this->max.y, b.max.y);

        return (*this);
    }
    /**
     * 
     * @param a
     * @return 
     */
    virtual self_type &merge(const self_type &a) {
        // Should zero? nope!

        this->min.x = glm::min(this->min.x, a.min.x);
        this->min.y = glm::min(this->min.y, a.min.y);
        this->max.x = glm::max(this->max.x, a.max.x);
        this->max.y = glm::max(this->max.y, a.max.y);

        return (*this);
    }
    /**
     * 
     * @param aaboxes
     * @param count
     * @return 
     */
    virtual self_type &merge(const self_type *aaboxes, const size_type count = 1) {
        if(!count || !aaboxes)
            return (*this);
        this->zero();
        for(int i = 0; i < count; i++) {
            this->min.x = glm::min(this->min.x, aaboxes[i].min.x);
            this->min.y = glm::min(this->min.y, aaboxes[i].min.y);
            this->max.x = glm::max(this->max.x, aaboxes[i].max.x);
            this->max.y = glm::max(this->max.y, aaboxes[i].max.y);
        }
        return (*this);
    }
    
    /**
     * 
     * @param data
     * @param count
     * @return 
     */
    virtual self_type &setBoundsFromData(vector_type *data, const size_type count = 1) {
        if(!data || !count)
            return (*this);
        this->zero();
        for(int i = 0; i < count; i++) {
            this->min.x = glm::min(this->min.x, data[i].x);
            this->min.y = glm::min(this->min.y, data[i].y);
            this->max.x = glm::max(this->max.x, data[i].x);
            this->max.y = glm::max(this->max.y, data[i].y);
        }
        return (*this);
    }
    
    /**
     * 
     */
    virtual void zero(void) {
        this->pos.x = (value_type)0;
        this->pos.y = (value_type)0;
        this->size.x = (value_type)0;
        this->size.y = (value_type)0;
    }
};

/// Basic axis-aligned bounding box 2D with float data type
typedef fgAABoundingBox2DT<float> fgAABoundingBox2Df;
/// Basic axis-aligned bounding box 2D with integer data type
typedef fgAABoundingBox2DT<int> fgAABoundingBox2Di;
// Basic axis-aligned bounding box 2D with unsigned integer data type
typedef fgAABoundingBox2DT<unsigned int> fgAABoundingBox2Du;
// Basic axis-aligned bounding box 2D with double precision data type
typedef fgAABoundingBox2DT<double> fgAABoundingBox2Dd;

typedef fgAABoundingBox2Df fgAABB2Df;
typedef fgAABoundingBox2Di fgAABB2Di;
typedef fgAABoundingBox2Du fgAABB2Du;
typedef fgAABoundingBox2Dd fgAABB2Dd;

////////////////////////////////////////////////////////////////////////////////
// AA 3D BOUNDING BOX
////////////////////////////////////////////////////////////////////////////////

/**
 *
 */
template <class ValueType>
struct fgAABoundingBox3DT : fgBoundingBoxT<fgAABoundingBox3DT<ValueType>, fgVector3T<ValueType>, ValueType> {
    typedef fgAABoundingBox3DT<ValueType> self_type;
    ///
    typedef fgVector3T<ValueType> vec_type;
    ///
    typedef fgBoundingBoxT<self_type, vec_type, ValueType> base_type;
    ///
    typedef typename base_type::size_type size_type;
    ///
    typedef typename base_type::value_type value_type;
    ///
    typedef typename base_type::vector_type vector_type;
    
    /**
     * 
     */
    fgAABoundingBox3DT() :
    base_type() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgAABoundingBox3DT(const vec_type &_pos, const vec_type &_size) :
    base_type(_pos, _size) { }
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    virtual self_type &merge(const self_type &a, const self_type &b) {
        this->zero();

        this->min.x = glm::min(this->min.x, a.min.x);
        this->min.y = glm::min(this->min.y, a.min.y);
        this->min.z = glm::min(this->min.z, a.min.z);
        this->max.x = glm::max(this->max.x, a.max.x);
        this->max.y = glm::max(this->max.y, a.max.y);
        this->max.z = glm::max(this->max.z, a.max.z);


        this->min.x = glm::min(this->min.x, b.min.x);
        this->min.y = glm::min(this->min.y, b.min.y);
        this->min.z = glm::min(this->min.z, b.min.z);
        this->max.x = glm::max(this->max.x, b.max.x);
        this->max.y = glm::max(this->max.y, b.max.y);
        this->max.z = glm::max(this->max.z, b.max.z);

        return (*this);
    }
    /**
     * 
     * @param a
     * @return 
     */
    virtual self_type &merge(const self_type &a) {
        // Should zero? nope!

        this->min.x = glm::min(this->min.x, a.min.x);
        this->min.y = glm::min(this->min.y, a.min.y);
        this->min.z = glm::min(this->min.z, a.min.z);
        this->max.x = glm::max(this->max.x, a.max.x);
        this->max.y = glm::max(this->max.y, a.max.y);
        this->max.z = glm::max(this->max.z, a.max.z);

        return (*this);
    }
    /**
     * 
     * @param aaboxes
     * @param count
     * @return 
     */
    virtual self_type &merge(const self_type *aaboxes, const size_type count = 1) {
        if(!count || !aaboxes)
            return (*this);
        this->zero();
        for(int i = 0; i < count; i++) {
            this->min.x = glm::min(this->min.x, aaboxes[i].min.x);
            this->min.y = glm::min(this->min.y, aaboxes[i].min.y);
            this->min.z = glm::min(this->min.z, aaboxes[i].min.z);
            this->max.x = glm::max(this->max.x, aaboxes[i].max.x);
            this->max.y = glm::max(this->max.y, aaboxes[i].max.y);
            this->max.z = glm::max(this->max.z, aaboxes[i].max.z);
        }
        return (*this);
    }
    /**
     * 
     * @param data
     * @param count
     * @return 
     */
    virtual self_type &setBoundsFromData(vector_type *data, const size_type count = 1) {
        if(!data || !count)
            return (*this);
        this->zero();
        for(int i = 0; i < count; i++) {
            this->min.x = glm::min(this->min.x, data[i].x);
            this->min.y = glm::min(this->min.y, data[i].y);
            this->min.z = glm::min(this->min.z, data[i].z);
            this->max.x = glm::max(this->max.x, data[i].x);
            this->max.y = glm::max(this->max.y, data[i].y);
            this->max.z = glm::max(this->max.z, data[i].z);
        }
        return (*this);
    }
    /**
     *  
     */
    virtual void zero(void) {
        this->min.x = (value_type)0;
        this->min.y = (value_type)0;
        this->min.z = (value_type)0;
        this->max.x = (value_type)0;
        this->max.y = (value_type)0;
        this->max.z = (value_type)0;
    }
};

/// Basic axis-aligned bounding box 3D with float data type
typedef fgAABoundingBox3DT<float> fgAABoundingBox3Df;
/// Basic axis-aligned bounding box 3D with integer data type
typedef fgAABoundingBox3DT<int> fgAABoundingBox3Di;
// Basic axis-aligned bounding box 3D with unsigned integer data type
typedef fgAABoundingBox3DT<unsigned int> fgAABoundingBox3Du;
// Basic axis-aligned bounding box 3D with double precision data type
typedef fgAABoundingBox3DT<double> fgAABoundingBox3Dd;

typedef fgAABoundingBox3Df fgAABB3Df;
typedef fgAABoundingBox3Di fgAABB3Di;
typedef fgAABoundingBox3Du fgAABB3Du;
typedef fgAABoundingBox3Dd fgAABB3Dd;

    #undef _FG_GFX_AA_BOUNDING_BOX_H_BLOCK_
#endif	/* _FG_GFX_AA_BOUNDING_BOX_H_ */
