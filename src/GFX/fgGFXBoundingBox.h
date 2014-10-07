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

template <class BoxType, class VecType, class DataType>
struct fgBoundingBox
{
	VecType pos;
	VecType size;

	fgBoundingBox() :
		pos(),
		size()
	{
	}

	fgBoundingBox(const VecType &_pos, const VecType &_size) :
		pos(_pos),
		size(_size)
	{
	}

	DataType left(void) const {
		return this->pos.x;
	}

	DataType right(void) const {
		return this->pos.x+this->size.x;
	}

	DataType top(void) const {
		return this->pos.y;
	}

	DataType bottom(void) const {
		return this->pos.y+this->size.y;
	}

	DataType width(void) const {
		return this->size.x;
	}

	DataType height(void) const {
		return this->size.y;
	}

	BoxType &setLeft(DataType left) {
        this->pos.x = left;
		return (*this);
    }

    BoxType &setRight(DataType right) {
		this->size.x = right - this->pos.x;
		return (*this);
    }

    BoxType &setTop(DataType top) {
        this->pos.y = top;
		return (*this);
    }

    BoxType &setBottom(DataType back) {
		this->size.y = back - this->pos.y;
		return (*this);
    }

    BoxType &setWidth(DataType width) {
		this->size.x = width;
		return (*this);
    }

    BoxType &setHeight(DataType height) {
		this->size.y = height;
		return (*this);
    }

	virtual fgBool test(const VecType& vec) const
	{
		return this->test(vec.x, vec.y);
	}

	virtual fgBool test(const DataType x, const DataType y) const
	{
		if (x > this->pos.x && x < (this->pos.x + this->size.x))
		{
			if (y > this->pos.y && y < (this->pos.y + this->size.y))
			{
				return FG_TRUE;
			}
		}
		return FG_FALSE;
	}

	virtual fgBool test(const DataType x, const DataType y, const DataType z) const
	{
		return this->test(x, y);
	}

};

template <class DataType>
/*
 *
 */
struct fgBoundingBox2D : fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2 <DataType, glm::precision::defaultp> , DataType>
{
	typedef fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2 <DataType, glm::precision::defaultp> , DataType> baseType;
	typedef glm::detail::tvec2<DataType, glm::precision::defaultp> vecType;

	fgBoundingBox2D() : fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2 <DataType, glm::precision::defaultp> , DataType>()
	{
	}

	fgBoundingBox2D(const vecType &_pos, const vecType &_size) :
		fgBoundingBox<fgBoundingBox2D<DataType>, glm::detail::tvec2 <DataType, glm::precision::defaultp> , DataType>(_pos, _size)
	{
	}

	fgBoundingBox2D &merge(const fgBoundingBox2D &a, const fgBoundingBox2D &b)
	{
		this->pos = a.pos;
		this->size = a.size;
		if (a.pos.x + a.size.x < b.pos.x + b.size.x)
			this->size.x = b.pos.x + b.size.x - a.pos.x;
        if (a.pos.y + a.size.y < b.pos.y + b.size.y)
            this->size.y = b.pos.y + b.size.y - a.pos.y;
		return (*this);
	}

	fgBoundingBox2D &merge(const fgBoundingBox2D &a)
	{
		if (this->pos.x + this->size.x < a.pos.x + a.size.x)
			this->size.x = a.pos.x + a.size.x - this->pos.x;
        if (this->pos.y + this->size.y < a.pos.y + a.size.y)
            this->size.y = a.pos.y + a.size.y - this->pos.y;
		return (*this);
	}
};

typedef fgBoundingBox2D<float>			fgBoundingBox2Df;
typedef fgBoundingBox2D<int>			fgBoundingBox2Di;
typedef fgBoundingBox2D<unsigned int>	fgBoundingBox2Du;
typedef fgBoundingBox2D<double>			fgBoundingBox2Dd;

template <class DataType>
/*
 *
 */
struct fgBoundingBox3D : fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::precision::defaultp> , DataType>
{
	typedef fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::precision::defaultp> , DataType> baseType;
	typedef glm::detail::tvec3<DataType, glm::precision::defaultp> vecType;

	fgBoundingBox3D() : fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::precision::defaultp> , DataType>()
	{
	}

	fgBoundingBox3D(const vecType &_pos, const vecType &_size) :
		fgBoundingBox<fgBoundingBox3D<DataType>, glm::detail::tvec3 <DataType, glm::precision::defaultp> , DataType>(_pos, _size)
	{
	}

	DataType front(void) const {
		return this->pos.z;
	}

	DataType back(void) const {
		return this->pos.z-this->size.z; // #FIXME
	}

	DataType depth(void) const {
		return this->size.z;
	}

	fgBoundingBox3D &setFront(DataType front) {
        this->pos.z = front;
		return (*this);
    }

	fgBoundingBox3D &setBack(DataType back) {
		this->size.z = back + this->pos.z; // #FIXME
		return (*this);
    }

	fgBoundingBox3D &setDepth(DataType depth) {
		this->size.z = depth;
		return (*this);
	}

	fgBoundingBox3D &merge(const fgBoundingBox3D &a, const fgBoundingBox3D &b)
	{
		this->pos = a.pos;
		this->size = a.size;

		if (a.pos.x + a.size.x < b.pos.x + b.size.x)
			this->size.x = b.pos.x + b.size.x - a.pos.x;
        if (a.pos.y + a.size.y < b.pos.y + b.size.y)
            this->size.y = b.pos.y + b.size.y - a.pos.y;
		if (a.pos.z + a.size.z < b.pos.z + b.size.z)
            this->size.z = b.pos.z + b.size.z - a.pos.z;
		return (*this);
	}

	fgBoundingBox3D &merge(const fgBoundingBox3D &a)
	{
		if (this->pos.x + this->size.x < a.pos.x + a.size.x)
			this->size.x = a.pos.x + a.size.x - this->pos.x;
        if (this->pos.y + this->size.y < a.pos.y + a.size.y)
            this->size.y = a.pos.y + a.size.y - this->pos.y;
		if (this->pos.z + this->size.z < a.pos.z + a.size.z)
            this->size.z = a.pos.z + a.size.z - this->pos.z;
		return (*this);
	}

	virtual fgBool test(const vecType& vec) const
	{
		return this->test(vec.x, vec.y, vec.z);
	}
	
	virtual fgBool test(const DataType x, const DataType y) const
	{
		return baseType::test(x, y);
	}

	virtual fgBool test(const DataType x, const DataType y, const DataType z) const
	{
		if (x > this->pos.x && x < (this->pos.x + this->size.x))
		{
			if (y > this->pos.y && y < (this->pos.y + this->size.y))
			{
				if (z > this->pos.z && z < (this->pos.z + this->size.z))
				{
					return FG_TRUE;
				}
			}
		}
		return FG_FALSE;
	}
};

typedef fgBoundingBox3D<float>			fgBoundingBox3Df;
typedef fgBoundingBox3D<int>			fgBoundingBox3Di;
typedef fgBoundingBox3D<unsigned int>	fgBoundingBox3Du;
typedef fgBoundingBox3D<double>			fgBoundingBox3Dd;

#endif /* _FG_GFX_BOUNDING_BOX_H_ */
