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
 * File:   fgGFXAABoundingBox.h
 * Author: vigilant
 *
 * Created on November 11, 2014, 6:52 PM
 */

#ifndef FG_INC_GFX_AA_BOUNDING_BOX
    #define FG_INC_GFX_AA_BOUNDING_BOX
    #define FG_INC_GFX_AA_BOUNDING_BOX_BLOCK

    #if defined(FG_INC_GFX_BOUNDING_BOX_BLOCK)
        #error "FG_GFX_BOUNDING_BOXBLOCK is defined. Do not include AA Bounding Box header inside of a regular Bounding Box header!"
    #endif

    #include "GFX/fgGfxBoundingBox.h"
    #include "fgBool.h"

    #include <cfloat>

namespace fg {
    namespace gfx {
        ///
        template <class ValueType> struct SAABoundingBox2DT;
        ///
        template <class ValueType> struct SAABoundingBox3DT;

        /**
         * 
         */
        class AABBHelper {
        private:
            /**
             * 
             */
            AABBHelper() { }
            /**
             * 
             */
            ~AABBHelper() { }

        public:
            /**
             * 
             * @param bbox
             * @param data
             * @param stride
             * @param count
             * @return 
             */
            template <class TBoxType>
            static TBoxType &setBoundsFromData(TBoxType& bbox, const void *data,
                                               const typename TBoxType::size_type stride,
                                               const typename TBoxType::size_type count = 1) {
                if(!data || !count || !stride)
                    return bbox;
                // need to reset
                //
                typedef typename TBoxType::value_type value_type;
                typedef typename TBoxType::size_type size_type;
                bbox.invalidate();
                uintptr_t offset = (uintptr_t)data;
                size_type innerMax = bbox.length() / 2;
                for(size_type i = 0; i < count; i++) {
                    const void *cur = (const void *)(offset + i * stride);
                    value_type *values = (value_type *)cur;
                    for(size_type j = 0; j < innerMax; j++) {
                        value_type& minVal = bbox[j];
                        value_type& maxVal = bbox[j + innerMax];
                        value_type checkVal = *(values + j); // offset + sizeof(value_type)*j
                        maxVal = math::max(maxVal, checkVal);
                        minVal = math::min(minVal, checkVal);
                    }
                }
                return bbox;
            }
        };

        /**
         *
         */
        template <class TBoxType, class TVecType, class TValueType>
        struct SAABoundingBoxT {
            ///
            typedef SAABoundingBoxT<TBoxType, TVecType, TValueType> self_type;
            /// Typedef for the value type - float/int/double in vector
            typedef TValueType value_type;
            /// Typedef for the vector type - anything, needs to have 3 values - x,y,z
            typedef TVecType vector_type;
            /// Bounding box type - the extended type
            typedef TBoxType box_type;
            /// Type used for indexing
            typedef unsigned int size_type;

            ///
            vector_type min;
            ///
            vector_type max;
            /**
             * Overloaded assignment operator - needs to be implemented
             * because of the use of union with complex types
             * @param other
             * @return 
             */
            self_type& operator =(const self_type& other) {
                if(this != &other) // protect against invalid self-assignment
                {
                    this->min = other.min;
                    this->max = other.max;
                }
                // by convention, always return *this
                return (*this);
            }
            /**
             * 
             */
            SAABoundingBoxT() :
            min(),
            max() { }
            /**
             * Overloaded copy constructor - needs to be implemented
             * explicitly because of the union containing complex types
             * @param other
             */
            SAABoundingBoxT(const self_type& other) : min(), max() {
                this->min = other.min;
                this->max = other.max;
            }
            /**
             * 
             * @param _min
             * @param _size
             */
            SAABoundingBoxT(const TVecType &_min, const TVecType &_max) :
            min(_min),
            max(_max) { }
            /**
             *
             */
            virtual ~SAABoundingBoxT() { }
            /**
             * 
             * @return 
             */
            virtual size_type length(void) const {
                return this->min.length() + this->max.length();
            }
            /**
             * Overloaded array operator - used for simplicity
             * Allows array-like access to values. For 2D bounding box max length
             * is 4 elements (x,y,w,h) or equivalent. This is safe
             * @param i
             * @return 
             */
            value_type& operator [](size_type i) {
                if(i >= (size_type)this->length())
                    i = 0;
                if(i >= (size_type)this->min.length()) {
                    i -= this->min.length();
                    return this->max[i];
                } else {
                    return this->min[i];
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
                if(i >= (size_type)this->min.length()) {
                    i -= this->min.length();
                    return this->max[i];
                } else {
                    return this->min[i];
                }
            }
            /**
             * 
             */
            virtual void zero(void) {
                // This zeroes the internal data
                memset(&this->min, 0, sizeof (vector_type));
                memset(&this->max, 0, sizeof (vector_type));
            }
            /**
             * 
             * @return 
             */
            value_type left(void) const {
                return this->min.x;
            }
            /**
             * 
             * @return 
             */
            value_type right(void) const {
                return this->max.x;
            }
            /**
             * 
             * @return 
             */
            value_type top(void) const {
                return this->max.y;
            }
            /**
             * 
             * @return 
             */
            value_type bottom(void) const {
                return this->min.y;
            }
            /**
             * 
             * @return 
             */
            value_type width(void) const {
                return this->max.x - this->min.x;
            }
            /**
             * 
             * @return 
             */
            value_type height(void) const {
                return this->max.y - this->min.y;
            }
            /**
             * 
             * @param left
             */
            self_type& setLeft(value_type left) {
                this->min.x = left;
                return (*this);
            }
            /**
             * 
             * @param right
             */
            self_type& setRight(value_type right) {
                this->max.x = right;
                return (*this);
            }
            /**
             * 
             * @param top
             */
            self_type& setTop(value_type top) {
                this->max.y = top;
                return (*this);
            }
            /**
             * 
             * @param back
             */
            self_type& setBottom(value_type back) {
                this->min.y = back;
                return (*this);
            }
            /**
             * 
             * @param width
             */
            self_type& setWidth(value_type width) {
                this->max.x = this->min.x + width;
                return (*this);
            }
            /**
             * 
             * @param height
             */
            self_type& setHeight(value_type height) {
                this->max.y = this->min.y + height;
                return (*this);
            }
            /**
             * 
             * @param vec
             * @return 
             */
            inline fgBool test(const vector_type& vec) const {
                return this->test(vec.x, vec.y);
            }
            /**
             * 
             * @param x
             * @param y
             * @return 
             */
            inline fgBool test(const value_type x,
                               const value_type y) const {
                if(x > this->min.x && x < this->max.x) {
                    if(y > this->min.y && y < this->max.y) {
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
            inline fgBool test(const value_type x,
                               const value_type y,
                               const value_type z) const {
                return this->test(x, y);
            }
            /**
             * 
             * @param center
             * @param radius
             * @return 
             */
            fgBool test(const vector_type& center, const value_type radius) const {
                // needs to return true if 'sphere' is completely inside of 'this' box
                if(center - radius < this->min)
                    return FG_FALSE;
                if(center + radius > this->max)
                    return FG_FALSE;
                return FG_TRUE;
            }
            /**
             * 
             * @param box
             * @return 
             */
            fgBool test(const box_type& box) const {
                // needs to return true if 'box' is completely inside of 'this' box
                if(box.min.x < this->min.x || box.max.x > this->max.x) {
                    return FG_FALSE;
                }
                if(box.min.y < this->min.y || box.max.y > this->max.y) {
                    return FG_FALSE;
                }
                return FG_TRUE;
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual box_type& merge(const box_type& a,
                                    const box_type& b) = 0;
            /**
             * 
             * @param a
             * @return 
             */
            virtual box_type& merge(const box_type& a) = 0;

            /**
             * 
             * @param v
             * @return
             */
            virtual box_type& merge(const vector_type& v) = 0;

            /**
             * 
             * @param data
             * @param count
             * @return 
             */
            virtual box_type& setBoundsFromData(vector_type *data,
                                                const size_type count = 1) = 0;
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
        template <class TValueType>
        struct SAABoundingBox2DT : SAABoundingBoxT<SAABoundingBox2DT<TValueType>, typename Vector2T<TValueType>::type, TValueType> {
            ///
            typedef SAABoundingBox2DT<TValueType> type;
            ///
            typedef SAABoundingBox2DT<TValueType> self_type;
            ///
            typedef typename Vector2T<TValueType>::type vec_type;
            ///
            typedef SAABoundingBoxT<self_type, vec_type, TValueType> base_type;
            ///
            typedef typename base_type::size_type size_type;
            ///
            typedef typename base_type::value_type value_type;
            ///
            typedef typename base_type::vector_type vector_type;
            /**
             * 
             */
            SAABoundingBox2DT() :
            base_type() { }
            /**
             * 
             * @param _min
             * @param _size
             */
            SAABoundingBox2DT(const vec_type& _min,
                              const vec_type& _max) :
            base_type(_min, _max) { }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(self_type const &a,
                                            self_type const &b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                return (*this);
            }
            /**
             * 
             * @param v
             * @return 
             */
            virtual inline self_type& merge(const vec_type& v) {
                this->min.x = math::min(this->min.x, v.x);
                this->min.y = math::min(this->min.y, v.y);
                this->max.x = math::max(this->max.x, v.x);
                this->max.y = math::max(this->max.y, v.y);
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox2DT<TValueType> const &a,
                                            SBoundingBox2DT<TValueType> const &b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(self_type const &a) {
                // Should zero? nope!
                this->min.x = math::min(this->min.x, a.min.x);
                this->min.y = math::min(this->min.y, a.min.y);
                this->max.x = math::max(this->max.x, a.max.x);
                this->max.y = math::max(this->max.y, a.max.y);
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox2DT<TValueType> const &a) {
                // Should zero? nope!
                this->min.x = math::min(this->min.x, a.pos.x);
                this->min.y = math::min(this->min.y, a.pos.y);
                this->max.x = math::max(this->max.x, a.pos.x + a.size.x);
                this->max.y = math::max(this->max.y, a.pos.y + a.size.y);
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const self_type *aaboxes,
                                     const size_type count = 1) {
                if(!count || !aaboxes)
                    return (*this);
                //this->zero(); // NOPE
                for(size_type i = 0; i < count; i++) {
                    this->merge(aaboxes[i]);
                }
                return (*this);
            }
            /**
             * 
             * @param boxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const SBoundingBox2DT<TValueType> *boxes,
                                     const size_type count = 1) {
                if(!count || !boxes)
                    return (*this);
                //this->zero(); // NOPE
                for(size_type i = 0; i < count; i++) {
                    this->merge(boxes[i]);
                }
                return (*this);
            }
            /**
             * 
             * @param data
             * @param count
             * @return 
             */
            virtual self_type& setBoundsFromData(vector_type *data,
                                                 const size_type count = 1) {
                if(!data || !count)
                    return (*this);
                this->invalidate();
                for(size_type i = 0; i < count; i++) {
                    this->min.x = math::min(this->min.x, data[i].x);
                    this->min.y = math::min(this->min.y, data[i].y);
                    this->max.x = math::max(this->max.x, data[i].x);
                    this->max.y = math::max(this->max.y, data[i].y);
                }
                return (*this);
            }
            /**
             * 
             * @param data
             * @param stride
             * @param count
             * @return 
             */
            virtual inline self_type& setBoundsFromData(const void *data,
                                                        const size_type stride,
                                                        const size_type count = 1) {
                return AABBHelper::setBoundsFromData((*this), data, stride, count);
            }
            /**
             * 
             */
            virtual inline void zero(void) {
                this->min.x = (value_type)0;
                this->min.y = (value_type)0;
                this->max.x = (value_type)0;
                this->max.y = (value_type)0;
            }
            /**
             * 
             */
            virtual inline void invalidate(void) {
                ;
                this->max.x = (std::numeric_limits<value_type>::max() / (value_type)(4)) * (value_type)(-1);
                this->max.y = (std::numeric_limits<value_type>::max() / (value_type)(4)) * (value_type)(-1);
                this->min.x = std::numeric_limits<value_type>::max();
                this->min.y = std::numeric_limits<value_type>::max();
            }
            /**
             * 
             * @return 
             */
            inline vector_type getCenter(void) const {
                //center = 0.5 * (min + max);
                //extent = 0.5 * (max - min);
                return 0.5f * (this->min + this->max);
            }
            /**
             * 
             * @return 
             */
            inline vector_type getExtent(void) const {
                return 0.5f * (this->max - this->min);
            }
            /**
             * 
             * @param normal
             * @return 
             */
            virtual inline vector_type getVertexP(const vector_type& normal) const {
                vector_type result = this->min;

                if(normal.x >= 0)
                    result.x = this->max.x;

                if(normal.y >= 0)
                    result.y = this->max.y;

                return result;
            }
            /**
             * 
             * @param normal
             * @return 
             */
            virtual inline vector_type getVertexN(const vector_type& normal) const {
                vector_type result = this->max;

                if(normal.x >= 0)
                    result.x = this->min.x;

                if(normal.y >= 0)
                    result.y = this->min.y;

                return result;
            }
            /**
             * 
             * @param m
             */
            virtual void transform(typename Matrix3T<TValueType>::type const & m) {
                vector_type translation(m[2]);
                vector_type oldmin, oldmax;
                value_type a, b;
                int i, j;
                // Copy box A into min and max array.
                oldmin = this->min;
                oldmax = this->max;
                // Begin at T.
                this->min = translation;
                this->max = translation;
                // Find extreme points by considering product of 
                // min and max with each component of M.
                for(j = 0; j < 2; j++) { // #FIXME 2 or 3 max? que paso?
                    for(i = 0; i < 2; i++) {
                        a = m[i][j] * oldmin[i];
                        b = m[i][j] * oldmax[i];
                        if(a < b) {
                            this->min[j] += a;
                            this->max[j] += b;
                        } else {
                            this->min[j] += b;
                            this->max[j] += a;
                        }
                    }
                }
            }
        };

        /// Basic axis-aligned bounding box 2D with float data type
        typedef SAABoundingBox2DT<float> AABoundingBox2Df;
        /// Basic axis-aligned bounding box 2D with integer data type
        typedef SAABoundingBox2DT<int> AABoundingBox2Di;
        // Basic axis-aligned bounding box 2D with unsigned integer data type
        typedef SAABoundingBox2DT<unsigned int> AABoundingBox2Du;
        // Basic axis-aligned bounding box 2D with double precision data type
        typedef SAABoundingBox2DT<double> AABoundingBox2Dd;

        ///
        typedef AABoundingBox2Df AABB2Df;
        ///
        typedef AABoundingBox2Di AABB2Di;
        ///
        typedef AABoundingBox2Du AABB2Du;
        ///
        typedef AABoundingBox2Dd AABB2Dd;

        ////////////////////////////////////////////////////////////////////////////////
        // AA 3D BOUNDING BOX
        ////////////////////////////////////////////////////////////////////////////////

        /**
         *
         */
        template <class TValueType>
        struct SAABoundingBox3DT : SAABoundingBoxT<SAABoundingBox3DT<TValueType>, typename Vector3T<TValueType>::type, TValueType> {
            ///
            typedef SAABoundingBox3DT<TValueType> self_type;
            ///
            typedef self_type type;
            ///
            typedef typename Vector3T<TValueType>::type vec_type;
            ///
            typedef SAABoundingBoxT<self_type, vec_type, TValueType> base_type;
            ///
            typedef typename base_type::size_type size_type;
            ///
            typedef typename base_type::value_type value_type;
            ///
            typedef typename base_type::vector_type vector_type;
            /**
             * 
             */
            SAABoundingBox3DT() :
            base_type() { }
            /**
             * 
             * @param _min
             * @param _size
             */
            SAABoundingBox3DT(const vec_type& _min, const vec_type& _size) :
            base_type(_min, _size) { }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(self_type const &a,
                                            self_type const &b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox3DT<TValueType> const &a,
                                            SBoundingBox3DT<TValueType> const &b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(self_type const &a) {
                // Should zero? nope!
                this->min.x = math::min(this->min.x, a.min.x);
                this->min.y = math::min(this->min.y, a.min.y);
                this->min.z = math::min(this->min.z, a.min.z);
                this->max.x = math::max(this->max.x, a.max.x);
                this->max.y = math::max(this->max.y, a.max.y);
                this->max.z = math::max(this->max.z, a.max.z);
                return (*this);
            }
            /**
             *
             * @param v
             * @return
             */
            virtual inline self_type& merge(const vec_type& v) {
                this->min.x = math::min(this->min.x, v.x);
                this->min.y = math::min(this->min.y, v.y);
                this->min.z = math::min(this->min.z, v.z);
                this->max.x = math::max(this->max.x, v.x);
                this->max.y = math::max(this->max.y, v.y);
                this->max.z = math::max(this->max.z, v.z);
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox3DT<TValueType> const &a) {
                // Should zero? nope!
                this->min.x = math::min(this->min.x, a.pos.x);
                this->min.y = math::min(this->min.y, a.pos.y);
                this->min.z = math::min(this->min.z, a.pos.z);
                this->max.x = math::max(this->max.x, a.pos.x + a.size.x);
                this->max.y = math::max(this->max.y, a.pos.y + a.size.y);
                this->max.z = math::max(this->max.z, a.pos.z + a.size.z);
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const self_type *aaboxes, const size_type count = 1) {
                if(!count || !aaboxes)
                    return (*this);
                for(size_type i = 0; i < count; i++) {
                    this->merge(aaboxes[i]);
                }
                return (*this);
            }
            /**
             * 
             * @param boxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const SBoundingBox3DT<TValueType> *boxes,
                                     const size_type count = 1) {
                if(!count || !boxes)
                    return (*this);
                for(size_type i = 0; i < count; i++) {
                    this->merge(boxes[i]);
                }
                return (*this);
            }
            /**
             * 
             * @param data
             * @param count
             * @return 
             */
            virtual self_type& setBoundsFromData(vector_type *data,
                                                 const size_type count = 1) {
                if(!data || !count)
                    return (*this);
                this->invalidate();
                for(size_type i = 0; i < count; i++) {
                    this->min.x = math::min(this->min.x, data[i].x);
                    this->min.y = math::min(this->min.y, data[i].y);
                    this->min.z = math::min(this->min.z, data[i].z);
                    this->max.x = math::max(this->max.x, data[i].x);
                    this->max.y = math::max(this->max.y, data[i].y);
                    this->max.z = math::max(this->max.z, data[i].z);
                }
                return (*this);
            }
            /**
             * 
             * @param data
             * @param stride
             * @param count
             * @return 
             */
            virtual inline self_type& setBoundsFromData(const void *data,
                                                        const size_type stride,
                                                        const size_type count = 1) {
                return AABBHelper::setBoundsFromData((*this), data, stride, count);
            }
            /**
             *  
             */
            virtual inline void zero(void) {
                this->min.x = (value_type)0;
                this->min.y = (value_type)0;
                this->min.z = (value_type)0;
                this->max.x = (value_type)0;
                this->max.y = (value_type)0;
                this->max.z = (value_type)0;
            }
            /**
             * 
             */
            virtual inline void invalidate(void) {
                this->max.x = -10000.0f; //(FLT_MAX / 4.0f) * (-1.0f);
                this->max.y = -10000.0f; //(FLT_MAX / 4.0f) * (-1.0f);
                this->max.z = -10000.0f; //(FLT_MAX / 4.0f) * (-1.0f);
                this->min.x = std::numeric_limits<value_type>::max();
                this->min.y = std::numeric_limits<value_type>::max();
                this->min.z = std::numeric_limits<value_type>::max();
            }
            /**
             *
             */
            virtual inline fgBool isValid(void) const {
                size_type n = this->length();
                for(size_type i = 0; i < n; i++) {
                    if((*this)[i] == std::numeric_limits<value_type>::max()) {
                        return FG_FALSE;
                    }
                }
                return FG_TRUE;
            }
            /**
             * 
             * @return 
             */
            inline vector_type getCenter(void) const {
                return 0.5f * (this->min + this->max);
            }
            /**
             * 
             * @return 
             */
            inline vector_type getExtent(void) const {
                return 0.5f * (this->max - this->min);
            }
            /**
             * 
             * @param normal
             * @return 
             */
            virtual inline vector_type getVertexP(const vector_type& normal) const {
                vector_type result = this->min;

                if(normal.x >= 0)
                    result.x = this->max.x;

                if(normal.y >= 0)
                    result.y = this->max.y;

                if(normal.z >= 0)
                    result.z = this->max.z;

                return result;
            }
            /**
             * 
             * @param normal
             * @return 
             */
            virtual inline vector_type getVertexN(const vector_type& normal) const {
                vector_type result = this->max;
                if(normal.x >= 0)
                    result.x = this->min.x;

                if(normal.y >= 0)
                    result.y = this->min.y;

                if(normal.z >= 0)
                    result.z = this->min.z;

                return result;
            }
            /**
             * 
             * @param m
             */
            virtual void transform(typename Matrix4T<TValueType>::type const & m) {
                vector_type translation(m[3]);
                vector_type oldmin, oldmax;
                value_type a, b;
                int i, j;
                // Copy box A into min and max array.
                oldmin = this->min;
                oldmax = this->max;
                // Begin at T.
                this->min = translation;
                this->max = translation;
                // Find extreme points by considering product of 
                // min and max with each component of M.
                for(j = 0; j < 3; j++) {
                    for(i = 0; i < 3; i++) {
                        a = m[i][j] * oldmin[i];
                        b = m[i][j] * oldmax[i];
                        if(a < b) {
                            this->min[j] += a;
                            this->max[j] += b;
                        } else {
                            this->min[j] += b;
                            this->max[j] += a;
                        }
                    }
                }
            }

            using base_type::test;
            /**
             * 
             * @param vec
             * @return 
             */
            inline fgBool test(const vector_type& vec) const {
                return this->test(vec.x, vec.y, vec.z);
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             * @return 
             */
            inline fgBool test(const value_type x,
                               const value_type y,
                               const value_type z) const {
                if(x > this->min.x && x < this->max.x) {
                    if(y > this->min.y && y < this->max.y) {
                        if(z > this->min.z && z < this->max.z) {
                            return FG_TRUE;
                        }
                    }
                }
                return FG_FALSE;
            }
            /**
             * 
             * @param center
             * @param radius
             * @return 
             */
            fgBool test(const vector_type& center, const value_type radius) const {
                // needs to return true if 'sphere' is completely inside of 'this' box
                if(center - radius < this->min)
                    return FG_FALSE;
                if(center + radius > this->max)
                    return FG_FALSE;
                return FG_TRUE;
            }
            /**
             * 
             * @param center
             * @param extent
             * @return 
             */
            fgBool test(const vector_type& center, const vector_type& extent) const {
                // needs to return true if 'sphere' is completely inside of 'this' box
                if(center.x - extent.x < this->min.x ||
                        center.x + extent.x > this->max.x)
                    return FG_FALSE;
                if(center.y - extent.y < this->min.y ||
                        center.y + extent.y > this->max.y)
                    return FG_FALSE;
                if(center.z - extent.z < this->min.z ||
                        center.z + extent.z > this->max.z)
                    return FG_FALSE;

                return FG_TRUE;
            }
            /**
             * 
             * @param box
             * @return 
             */
            fgBool test(const self_type& box) const {
                // needs to return true if 'box' is completely inside of 'this' box
                if(box.min.x < this->min.x || box.max.x > this->max.x) {
                    return FG_FALSE;
                }
                if(box.min.y < this->min.y || box.max.y > this->max.y) {
                    return FG_FALSE;
                }
                if(box.min.z < this->min.z || box.max.z > this->max.z) {
                    return FG_FALSE;
                }
                return FG_TRUE;
            }
        };

        /// Basic axis-aligned bounding box 3D with float data type
        typedef SAABoundingBox3DT<float> AABoundingBox3Df;
        /// Basic axis-aligned bounding box 3D with integer data type
        typedef SAABoundingBox3DT<int> AABoundingBox3Di;
        // Basic axis-aligned bounding box 3D with unsigned integer data type
        typedef SAABoundingBox3DT<unsigned int> AABoundingBox3Du;
        // Basic axis-aligned bounding box 3D with double precision data type
        typedef SAABoundingBox3DT<double> AABoundingBox3Dd;

        ///
        typedef AABoundingBox3Df AABB3Df;
        ///
        typedef AABoundingBox3Di AABB3Di;
        ///
        typedef AABoundingBox3Du AABB3Du;
        ///
        typedef AABoundingBox3Dd AABB3Dd;
    };
};

    #undef FG_INC_GFX_AA_BOUNDING_BOX_BLOCK
#endif	/* FG_INC_GFX_AA_BOUNDING_BOX */
