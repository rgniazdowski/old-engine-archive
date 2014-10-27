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

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if defined(FG_USING_GLM)
        #include "glm/vec2.hpp"
        #include "glm/vec3.hpp"
    #endif

    #include <cmath>

//
template <class DataType> struct fgBoundingBox2D;
//
template <class DataType> struct fgBoundingBox3D;

template <class BoxType, class VecType, class DataType>
/**
 *
 */
struct fgBoundingBox {
    typedef fgBoundingBox<BoxType, VecType, DataType> type;
    typedef DataType value_type;
    typedef VecType vector_type;
    typedef BoxType box_type;
    typedef int size_type;

    VecType pos;
    VecType size;
    /**
     * 
     */
    fgBoundingBox() :
    pos(),
    size() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBox(const VecType &_pos, const VecType &_size) :
    pos(_pos),
    size(_size) { }
    /**
     * 
     * @return 
     */
    virtual int length(void) const {
        return this->pos.length() + this->size.length();
    }
    /**
     * 
     * @param i
     * @return 
     */
    DataType & operator [](int i) {
        if(i > this->length())
            i = 0;
        if(i >= this->pos.length()) {
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
    DataType const & operator [](int i)const {
        if(i > this->length())
            i = 0;
        if(i >= this->pos.length()) {
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
        this->pos.x = (DataType)0;
        this->pos.y = (DataType)0;
        this->size.x = (DataType)0;
        this->size.y = (DataType)0;
    }
    /**
     * 
     * @return 
     */
    DataType left(void) const {
        return this->pos.x;
    }
    /**
     * 
     * @return 
     */
    DataType right(void) const {
        return this->pos.x + this->size.x;
    }
    /**
     * 
     * @return 
     */
    DataType top(void) const {
        return this->pos.y;
    }
    /**
     * 
     * @return 
     */
    DataType bottom(void) const {
        return this->pos.y + this->size.y;
    }
    /**
     * 
     * @return 
     */
    DataType width(void) const {
        return this->size.x;
    }
    /**
     * 
     * @return 
     */
    DataType height(void) const {
        return this->size.y;
    }
    /**
     * 
     * @param left
     * @return 
     */
    BoxType &setLeft(DataType left) {
        this->pos.x = left;
        return (*this);
    }
    /**
     * 
     * @param right
     * @return 
     */
    BoxType &setRight(DataType right) {
        this->size.x = right - this->pos.x;
        return (*this);
    }
    /**
     * 
     * @param top
     * @return 
     */
    BoxType &setTop(DataType top) {
        this->pos.y = top;
        return (*this);
    }
    /**
     * 
     * @param back
     * @return 
     */
    BoxType &setBottom(DataType back) {
        this->size.y = back - this->pos.y;
        return (*this);
    }
    /**
     * 
     * @param width
     * @return 
     */
    BoxType &setWidth(DataType width) {
        this->size.x = width;
        return (*this);
    }
    /**
     * 
     * @param height
     * @return 
     */
    BoxType &setHeight(DataType height) {
        this->size.y = height;
        return (*this);
    }
    /**
     * 
     * @param vec
     * @return 
     */
    virtual fgBool test(const VecType& vec) const {
        return this->test(vec.x, vec.y);
    }
    /**
     * 
     * @param x
     * @param y
     * @return 
     */
    virtual fgBool test(const DataType x, const DataType y) const {
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
    virtual fgBool test(const DataType x, const DataType y, const DataType z) const {
        return this->test(x, y);
    }

};

template <class DataType>
/**
 *
 */
struct fgBoundingBox2D : fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2<DataType, glm::defaultp>, DataType> {
    //
    typedef fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2<DataType, glm::defaultp>, DataType> baseType;
    //
    typedef glm::detail::tvec2<DataType, glm::defaultp> vecType;
    /**
     * 
     */
    fgBoundingBox2D() :
    fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2<DataType, glm::defaultp>, DataType>() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBox2D(const vecType &_pos, const vecType &_size) :
    fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2<DataType, glm::defaultp>, DataType>(_pos, _size) { }
    #if 0
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    fgBoundingBox2D &merge(const fgBoundingBox2D &a, const fgBoundingBox2D &b) {
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
    fgBoundingBox2D &merge(const fgBoundingBox2D &a) {
        if(this->pos.x + this->size.x < a.pos.x + a.size.x)
            this->size.x = a.pos.x + a.size.x - this->pos.x;
        if(this->pos.y + this->size.y < a.pos.y + a.size.y)
            this->size.y = a.pos.y + a.size.y - this->pos.y;
        return (*this);
    }
    #endif
    fgBoundingBox2D &merge(const fgBoundingBox2D &a, const fgBoundingBox2D &b) {
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
    fgBoundingBox2D &merge(const fgBoundingBox2D &a) {
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
     */
    virtual void zero(void) {
        this->pos.x = (DataType)0;
        this->pos.y = (DataType)0;
        this->size.x = (DataType)0;
        this->size.y = (DataType)0;
    }
};

//
typedef fgBoundingBox2D<float> fgBoundingBox2Df;
//
typedef fgBoundingBox2D<int> fgBoundingBox2Di;
//
typedef fgBoundingBox2D<unsigned int> fgBoundingBox2Du;
//
typedef fgBoundingBox2D<double> fgBoundingBox2Dd;

template <class DataType>
/**
 *
 */
struct fgBoundingBox3D :
fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3<DataType, glm::defaultp>, DataType> {
    //
    typedef fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3<DataType, glm::defaultp>, DataType> baseType;
    //
    typedef glm::detail::tvec3<DataType, glm::defaultp> vecType;
    /**
     * 
     */
    fgBoundingBox3D() :
    fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::defaultp>, DataType>() { }
    /**
     * 
     * @param _pos
     * @param _size
     */
    fgBoundingBox3D(const vecType &_pos, const vecType &_size) :
    fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::defaultp>, DataType>(_pos, _size) { }
    /**
     * 
     */
    virtual void zero(void) {
        this->pos.x = (DataType)0;
        this->pos.y = (DataType)0;
        this->pos.z = (DataType)0;
        this->size.x = (DataType)0;
        this->size.y = (DataType)0;
        this->size.z = (DataType)0;
    }
    /**
     * 
     * @return 
     */
    DataType front(void) const {
        return this->pos.z;
    }
    /**
     * 
     * @return 
     */
    DataType back(void) const {
        return this->pos.z - this->size.z; // #FIXME
    }
    /**
     * 
     * @return 
     */
    DataType depth(void) const {
        return this->size.z;
    }
    /**
     * 
     * @param front
     * @return 
     */
    fgBoundingBox3D &setFront(DataType front) {
        this->pos.z = front;
        return (*this);
    }
    /**
     * 
     * @param back
     * @return 
     */
    fgBoundingBox3D &setBack(DataType back) {
        this->size.z = back + this->pos.z; // #FIXME
        return (*this);
    }
    /**
     * 
     * @param depth
     * @return 
     */
    fgBoundingBox3D &setDepth(DataType depth) {
        this->size.z = depth;
        return (*this);
    }
    /**
     * 
     * @param a
     * @param b
     * @return 
     */
    fgBoundingBox3D &merge(const fgBoundingBox3D &a, const fgBoundingBox3D &b) {
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
    fgBoundingBox3D &merge(const fgBoundingBox3D &a) {
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
     * @param vec
     * @return 
     */
    virtual fgBool test(const vecType& vec) const {
        return this->test(vec.x, vec.y, vec.z);
    }
    /**
     * 
     * @param x
     * @param y
     * @return 
     */
    virtual fgBool test(const DataType x, const DataType y) const {
        return baseType::test(x, y);
    }
    /**
     * 
     * @param x
     * @param y
     * @param z
     * @return 
     */
    virtual fgBool test(const DataType x, const DataType y, const DataType z) const {
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

//
typedef fgBoundingBox3D<float> fgBoundingBox3Df;
//
typedef fgBoundingBox3D<int> fgBoundingBox3Di;
//
typedef fgBoundingBox3D<unsigned int> fgBoundingBox3Du;
//
typedef fgBoundingBox3D<double> fgBoundingBox3Dd;

#endif /* _FG_GFX_BOUNDING_BOX_H_ */
