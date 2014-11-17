/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_BOUNDING_BOX_H_
    #define _FG_GFX_BOUNDING_BOX_H_
    #define _FG_GFX_BOUNDING_BOX_H_BLOCK_

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #include "fgGFXVertex.h"

    #include <cmath>

// Forward declaration for plain bounding box 2D
template <class ValueType> struct fgBoundingBox2DT;
// Forward declaration for plain bounding box 3D
template <class ValueType> struct fgBoundingBox3DT;

/**
 * This is basic bounding box - mainly used in 2D / GUI. Depending on the usage
 * it can also represent bounding box as center position and half-extent vectors
 * In GUI the upper-left corner is represented as the position vector.
 */
template <class BoxType, class VecType, class ValueType>
struct fgBoundingBoxT {
    ///
    typedef fgBoundingBoxT<BoxType, VecType, ValueType> self_type;
    /// Typedef for the value type - float/int/double in vector
    typedef ValueType value_type;
    /// Typedef for the vector type - anything, needs to have 3 values - x,y,z
    typedef VecType vector_type;
    /// Bounding box type - the extended type
    typedef BoxType box_type;
    /// Type used for indexing
    typedef unsigned int size_type;

    union {
        /// Position vector - depends on the usage
        VecType pos;
        /// Center position - used together with half-extent
        VecType center;
        /// Could have here some min/max (aabb?)
        VecType min;
    };

    union {
        /// Size vector - depends on the usage
        VecType size;
        /// Half-extent vector
        VecType extent;
        /// This is for compatibility with AABB type
        VecType max;
    };
    /**
     * Overloaded assignment operator - needs to be implemented
     * because of the use of union with complex types
     * @param other
     * @return 
     */
    self_type & operator =(const self_type & other) {
        if(this != &other) // protect against invalid self-assignment
        {
            this->pos = other.pos;
            this->size = other.size;
        }
        // by convention, always return *this
        return (*this);
    }
    /**
     * 
     */
    fgBoundingBoxT() :
    pos(),
    size() { }
    /**
     * Overloaded copy constructor - needs to be implemented
     * explicitly because of the union containing complex types
     * @param other
     */
    fgBoundingBoxT(const self_type & other) {
        this->pos = other.pos;
        this->size = other.size;
    }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBoxT(const VecType &_pos, const VecType &_size) :
    pos(_pos),
    size(_size) { }
    /**
     * 
     * @return 
     */
    virtual size_type length(void) const {
        return this->pos.length() + this->size.length();
    }
    /**
     * Overloaded array operator - used for simplicity
     * Allows array-like access to values. For 2D bounding box max length
     * is 4 elements (x,y,w,h) or equivalent. This is safe
     * @param i
     * @return 
     */
    value_type & operator [](size_type i) {
        if(i >= (size_type)this->length())
            i = 0;
        if(i >= (size_type)this->pos.length()) {
            i -= this->pos.length();
            return this->size[i];
        } else {
            return this->pos[i];
        }
    }
    /**
     * 
     * @param i
     * @return 
     */
    value_type const & operator [](size_type i)const {
        if(i >= (size_type)this->length())
            i = 0;
        if(i >= (size_type)this->pos.length()) {
            i -= this->pos.length();
            return this->size[i];
        } else {
            return this->pos[i];
        }
    }
    /**
     * 
     */
    virtual void zero(void) {
        // This zeroes the internal data
        memset(&this->pos, 0, sizeof (vector_type));
        memset(&this->size, 0, sizeof (vector_type));
    }
    /**
     * 
     * @return 
     */
    value_type left(void) const {
        return this->pos.x;
    }
    /**
     * 
     * @return 
     */
    value_type right(void) const {
        return this->pos.x + this->size.x;
    }
    /**
     * 
     * @return 
     */
    value_type top(void) const {
        return this->pos.y;
    }
    /**
     * 
     * @return 
     */
    value_type bottom(void) const {
        return this->pos.y + this->size.y;
    }
    /**
     * 
     * @return 
     */
    value_type width(void) const {
        return this->size.x;
    }
    /**
     * 
     * @return 
     */
    value_type height(void) const {
        return this->size.y;
    }
    /**
     * 
     * @param left
     * @return 
     */
    box_type &setLeft(value_type left) {
        this->pos.x = left;
        return (*this);
    }
    /**
     * 
     * @param right
     * @return 
     */
    box_type &setRight(value_type right) {
        this->size.x = right - this->pos.x;
        return (*this);
    }
    /**
     * 
     * @param top
     * @return 
     */
    box_type &setTop(value_type top) {
        this->pos.y = top;
        return (*this);
    }
    /**
     * 
     * @param back
     * @return 
     */
    box_type &setBottom(value_type back) {
        this->size.y = back - this->pos.y;
        return (*this);
    }
    /**
     * 
     * @param width
     * @return 
     */
    box_type &setWidth(value_type width) {
        this->size.x = width;
        return (*this);
    }
    /**
     * 
     * @param height
     * @return 
     */
    box_type &setHeight(value_type height) {
        this->size.y = height;
        return (*this);
    }
    /**
     * 
     * @param vec
     * @return 
     */
    virtual inline fgBool test(const vector_type& vec) const {
        return this->test(vec.x, vec.y);
    }
    /**
     * 
     * @param x
     * @param y
     * @return 
     */
    virtual inline fgBool test(const value_type x, const value_type y) const {
        if(x > this->pos.x && x < (this->pos.x + this->size.x)) {
            if(y > this->pos.y && y < (this->pos.y + this->size.y)) {
                return FG_TRUE;
            }
        }
        return FG_FALSE;
    }
    /**
     * 
     * @param x
     * @param y
     * @param z
     * @return 
     */
    virtual inline fgBool test(const value_type x, const value_type y, const value_type z) const {
        return this->test(x, y);
    }
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    virtual box_type &merge(const box_type &a, const box_type &b) = 0;
    /**
     * 
     * @param a
     * @return 
     */
    virtual box_type &merge(const box_type &a) = 0;
    
    /**
     * 
     * @param data
     * @param count
     * @return 
     */
    virtual box_type &setBoundsFromData(vector_type *data, const size_type count = 1) = 0;
    
    /**
     * 
     */
    virtual void invalidate(void) { 
        this->zero();
    }
    /**
     * 
     * @return 
     */
    virtual inline fgBool isValid(void) const {
        return FG_TRUE;
    }
};

/**
 *
 */
template <class ValueType>
struct fgBoundingBox2DT : fgBoundingBoxT<fgBoundingBox2DT<ValueType>, fgVector2T<ValueType>, ValueType> {
    typedef fgBoundingBox2DT<ValueType> self_type;
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
    fgBoundingBox2DT() :
    base_type() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBox2DT(const vec_type &_pos, const vec_type &_size) :
    base_type(_pos, _size) { }
    #if 0
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    fgBoundingBox2DT &merge(const fgBoundingBox2DT &a, const fgBoundingBox2DT &b) {
        this->pos = a.pos;
        this->size = a.size;
        if(a.pos.x + a.size.x < b.pos.x + b.size.x)
            this->size.x = b.pos.x + b.size.x - a.pos.x;
        if(a.pos.y + a.size.y < b.pos.y + b.size.y)
            this->size.y = b.pos.y + b.size.y - a.pos.y;
        return (*this);
    }
    /**
     * 
     * @param a
     * @return 
     */
    fgBoundingBox2DT &merge(const fgBoundingBox2DT &a) {
        if(this->pos.x + this->size.x < a.pos.x + a.size.x)
            this->size.x = a.pos.x + a.size.x - this->pos.x;
        if(this->pos.y + this->size.y < a.pos.y + a.size.y)
            this->size.y = a.pos.y + a.size.y - this->pos.y;
        return (*this);
    }
    #endif
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    virtual self_type &merge(const self_type &a, const self_type &b) {
        this->pos = a.pos;
        this->size = a.size;

        if(a.pos.x + a.size.x < b.pos.x + b.size.x)
            this->size.x = b.pos.x + b.size.x - a.pos.x;
        if(a.pos.y + a.size.y < b.pos.y + b.size.y)
            this->size.y = b.pos.y + b.size.y - a.pos.y;
        return (*this);
    }
    /**
     * 
     * @param a
     * @return 
     */
    virtual self_type &merge(const self_type &a) {
        //if(firstArea.X + firstArea.Z < secondArea.X + secondArea.Z)
        //    firstArea.Z = secondArea.X + secondArea.Z - firstArea.X;
        //
        //if(firstArea.Y + firstArea.W < secondArea.Y + secondArea.W)
        //    firstArea.W = secondArea.Y + secondArea.W - firstArea.Y;
        if(this->pos.x + this->size.x < a.pos.x + a.size.x)
            this->size.x = a.pos.x + a.size.x - this->pos.x;

        if(this->pos.y + this->size.y < a.pos.y + a.size.y)
            this->size.y = a.pos.y + a.size.y - this->pos.y;

        return (*this);
    }
    /**
     * 
     * @param data
     * @param count
     * @return 
     */
    virtual self_type &setBoundsFromData(vector_type *data, const size_type count = 1) {
        // need to implement
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

/// Basic bounding box 2D with float data type
typedef fgBoundingBox2DT<float> fgBoundingBox2Df;
/// Basic bounding box 2D with integer data type
typedef fgBoundingBox2DT<int> fgBoundingBox2Di;
// Basic bounding box 2D with unsigned integer data type
typedef fgBoundingBox2DT<unsigned int> fgBoundingBox2Du;
// Basic bounding box 2D with double precision data type
typedef fgBoundingBox2DT<double> fgBoundingBox2Dd;

typedef fgBoundingBox2Df fgBB2Df;
typedef fgBoundingBox2Di fgBB2Di;
typedef fgBoundingBox2Du fgBB2Du;
typedef fgBoundingBox2Dd fgBB2Dd;

/**
 *
 */
template <class ValueType>
struct fgBoundingBox3DT :
fgBoundingBoxT<fgBoundingBox3DT<ValueType>, fgVector3T<ValueType>, ValueType> {
    ///
    typedef fgBoundingBox3DT<ValueType> self_type;
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
    fgBoundingBox3DT() :
    base_type() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBox3DT(const vec_type &_pos, const vec_type &_size) :
    base_type(_pos, _size) { }
    /**
     * 
     */
    virtual void zero(void) {
        this->pos.x = (value_type)0;
        this->pos.y = (value_type)0;
        this->pos.z = (value_type)0;
        this->size.x = (value_type)0;
        this->size.y = (value_type)0;
        this->size.z = (value_type)0;
    }
    /**
     * 
     * @return 
     */
    value_type front(void) const {
        return this->pos.z;
    }
    /**
     * 
     * @return 
     */
    value_type back(void) const {
        return this->pos.z - this->size.z; // #FIXME
    }
    /**
     * 
     * @return 
     */
    value_type depth(void) const {
        return this->size.z;
    }
    /**
     * 
     * @param front
     * @return 
     */
    self_type &setFront(value_type front) {
        this->pos.z = front;
        return (*this);
    }
    /**
     * 
     * @param back
     * @return 
     */
    self_type &setBack(value_type back) {
        this->size.z = back + this->pos.z; // #FIXME
        return (*this);
    }
    /**
     * 
     * @param depth
     * @return 
     */
    self_type &setDepth(value_type depth) {
        this->size.z = depth;
        return (*this);
    }
    /**
     * 
     * @param a
     * @param b
     * @return 
     */ 
    virtual self_type &merge(const self_type &a, const self_type &b) {
        this->pos = a.pos;
        this->size = a.size;

        if(a.pos.x + a.size.x < b.pos.x + b.size.x)
            this->size.x = b.pos.x + b.size.x - a.pos.x;
        if(a.pos.y + a.size.y < b.pos.y + b.size.y)
            this->size.y = b.pos.y + b.size.y - a.pos.y;
        if(a.pos.z + a.size.z < b.pos.z + b.size.z)
            this->size.z = b.pos.z + b.size.z - a.pos.z;
        return (*this);
    }
    /**
     * 
     * @param a
     * @return 
     */
    virtual self_type &merge(const self_type &a) {
        //if(firstArea.X + firstArea.Z < secondArea.X + secondArea.Z)
        //    firstArea.Z = secondArea.X + secondArea.Z - firstArea.X;
        //
        //if(firstArea.Y + firstArea.W < secondArea.Y + secondArea.W)
        //    firstArea.W = secondArea.Y + secondArea.W - firstArea.Y;
        //if(this->pos.x > a.pos.x && a.pos.x > 0)
        //    this->pos.x = a.pos.x;
        //if(this->pos.y > a.pos.y && a.pos.y > 0)
        //    this->pos.y = a.pos.y;

        if(this->pos.x + this->size.x < a.pos.x + a.size.x) {
            this->size.x = a.pos.x + a.size.x - this->pos.x;
            //this->size.y += a.pos.x) + a.size.x) - (this->pos.x) + this->size.x));
        }

        if(this->pos.y + this->size.y < a.pos.y + a.size.y) {
            this->size.y = a.pos.y + a.size.y - this->pos.y;
            //this->size.y += a.pos.y) + a.size.y) - (this->pos.y) + this->size.y));
        }

        if(this->pos.z + this->size.z < a.pos.z + a.size.z) {
            this->size.z = a.pos.z + a.size.z - this->pos.z;
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
        // need to implement
        return (*this);
    }
    /**
     * 
     * @param vec
     * @return 
     */
    virtual inline fgBool test(const vec_type& vec) const {
        return this->test(vec.x, vec.y, vec.z);
    }
    /**
     * 
     * @param x
     * @param y
     * @return 
     */
    virtual inline fgBool test(const value_type x, const value_type y) const {
        return base_type::test(x, y);
    }
    /**
     * 
     * @param x
     * @param y
     * @param z
     * @return 
     */
    virtual inline fgBool test(const value_type x, const value_type y, const value_type z) const {
        if(x > this->pos.x && x < (this->pos.x + this->size.x)) {
            if(y > this->pos.y && y < (this->pos.y + this->size.y)) {
                if(z > this->pos.z && z < (this->pos.z + this->size.z)) {
                    return FG_TRUE;
                }
            }
        }
        return FG_FALSE;
    }
};

///
typedef fgBoundingBox3DT<float> fgBoundingBox3Df;
///
typedef fgBoundingBox3DT<int> fgBoundingBox3Di;
///
typedef fgBoundingBox3DT<unsigned int> fgBoundingBox3Du;
///
typedef fgBoundingBox3DT<double> fgBoundingBox3Dd;

typedef fgBoundingBox3Df fgBB3Df;
typedef fgBoundingBox3Di fgBB3Di;
typedef fgBoundingBox3Du fgBB3Du;
typedef fgBoundingBox3Dd fgBB3Dd;

    #undef _FG_GFX_BOUNDING_BOX_H_BLOCK_
#endif /* _FG_GFX_BOUNDING_BOX_H_ */
