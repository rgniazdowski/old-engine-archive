/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXBoundingVolume.h
 * Author: vigilant
 *
 * Created on January 14, 2015, 5:53 PM
 */

#ifndef FG_INC_GFX_BOUNDING_VOLUME
    #define FG_INC_GFX_BOUNDING_VOLUME
    #define FG_INC_GFX_BOUNDING_VOLUME_BLOCK

    #include "fgGFXAABoundingBox.h"

namespace fg {
    namespace gfx {

        ///
        template <class ValueType> struct SBoundingVolume2DT;
        ///
        template <class ValueType> struct SBoundingVolume3DT;

        /**
         *
         */
        template <class TValueType>
        struct SBoundingVolume2DT : SAABoundingBox2DT<TValueType> {
            ///
            typedef SBoundingVolume2DT<TValueType> type;
            ///
            typedef SBoundingVolume2DT<TValueType> self_type;
            ///
            typedef typename Vector2T<TValueType>::type vec_type;
            ///
            typedef SAABoundingBox2DT<TValueType> base_type;
            ///
            typedef typename base_type::size_type size_type;
            ///
            typedef typename base_type::value_type value_type;
            ///
            typedef typename base_type::vector_type vector_type;

            ///
            vec_type center;
            ///
            vec_type extent;
            ///
            value_type radius;
            /**
             * 
             */
            SBoundingVolume2DT() : base_type() { }
            /**
             * 
             * @param _min
             * @param _max
             */
            SBoundingVolume2DT(const vec_type& _min, const vec_type& _max) :
            base_type(_min, _max) { }
            /**
             * 
             * @param aabb
             */
            SBoundingVolume2DT(base_type const& aabb) : base_type() {
                this->invalidate();
                this->merge(aabb);
            }
            /**
             * 
             * @param aabb
             */
            SBoundingVolume2DT(self_type const& aabb) {
                this->min = aabb.min;
                this->max = aabb.max;
                this->refresh();
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(base_type const& a,
                                            base_type const& b) {
                base_type::merge(a, b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(self_type const& a,
                                            self_type const& b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox2DT<TValueType> const& a,
                                            SBoundingBox2DT<TValueType> const& b) {
                base_type::merge(a, b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(base_type const& a) {
                base_type::merge(a);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(self_type const& a) {
                // Should zero? nope!
                this->min.x = fg::math::min(this->min.x, a.min.x);
                this->min.y = fg::math::min(this->min.y, a.min.y);
                this->max.x = fg::math::max(this->max.x, a.max.x);
                this->max.y = fg::math::max(this->max.y, a.max.y);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox2DT<TValueType> const& a) {
                base_type::merge(a);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const base_type* aaboxes,
                                     const size_type count = 1) {
                base_type::merge(aaboxes, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const self_type* aaboxes,
                                     const size_type count = 1) {
                if(!count || !aaboxes)
                    return (*this);
                for(int i = 0; i < count; i++) {
                    this->merge(aaboxes[i]);
                }
                this->refresh();
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
                base_type::merge(boxes, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param data
             * @param count
             * @return 
             */
            virtual self_type& setBoundsFromData(vector_type *data, const size_type count = 1) {
                base_type::setBoundsFromData(data, count);
                this->refresh();
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
                AABBHelper::setBoundsFromData((*this), data, stride, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             */
            virtual inline void zero(void) {
                this->min.x = (value_type)0;
                this->min.y = (value_type)0;
                this->max.x = (value_type)0;
                this->max.y = (value_type)0;
                this->center.x = (value_type)0;
                this->center.y = (value_type)0;
                this->extent.x = (value_type)0;
                this->extent.y = (value_type)0;
                this->radius = (value_type)0;
            }
            /**
             * 
             */
            virtual inline void refresh(void) {
                center = 0.5f * (this->min + this->max);
                extent = 0.5f * (this->max - this->min);
                radius = 0.0f;
                radius = math::max(radius, extent.x);
                radius = math::max(radius, extent.y);
            }
            /**
             * 
             */
            virtual inline void invalidate(void) {
                this->zero();
                this->min.x = FLT_MAX;
                this->min.y = FLT_MAX;
            }
            /**
             * 
             * @return 
             */
            inline vector_type getCenter(void) {
                center = 0.5f * (this->min + this->max);
                radius = 0.0f;
                radius = math::max(radius, extent.x);
                radius = math::max(radius, extent.y);
                return center;
            }
            /**
             * 
             * @return 
             */
            inline vector_type getExtent(void) {
                extent = 0.5f * (this->max - this->min);
                radius = 0.0f;
                radius = math::max(radius, extent.x);
                radius = math::max(radius, extent.y);
                return extent;
            }
            /**
             * 
             * @param m
             */
            virtual void transform(typename Matrix3T<TValueType>::type const& m) {
                base_type::transform(m);
                this->refresh();
            }

            ////////////////////////////////////////////////////////////////////
            using base_type::test;
            /**
             * 
             * @param box
             * @return 
             */
            virtual fgBool test(const self_type& box) {
                // needs to return true if 'box' is completely inside of 'this' box
                if(box.min.x < this->min.x || box.max.x > this->max.x) {
                    return FG_FALSE;
                }
                if(box.min.y < this->min.y || box.max.y > this->max.y) {
                    return FG_FALSE;
                }
            }
        };

        ///
        typedef SBoundingVolume2DT<float> BoundingVolume2Df;
        ///
        typedef SBoundingVolume2DT<int> BoundingVolume2Di;
        /// 
        typedef SBoundingVolume2DT<unsigned int> BoundingVolume2Du;
        /// 
        typedef SBoundingVolume2DT<double> BoundingVolume2Dd;

        /**
         *
         */
        template <class TValueType>
        struct SBoundingVolume3DT : SAABoundingBox3DT<TValueType> {
            ///
            typedef SBoundingVolume3DT<TValueType> type;
            ///
            typedef SBoundingVolume3DT<TValueType> self_type;
            ///
            typedef typename Vector3T<TValueType>::type vec_type;
            ///
            typedef SAABoundingBox3DT<TValueType> base_type;
            ///
            typedef typename base_type::size_type size_type;
            ///
            typedef typename base_type::value_type value_type;
            ///
            typedef typename base_type::vector_type vector_type;

            ///
            vec_type center;
            ///
            vec_type extent;
            ///
            value_type radius;
            /**
             * 
             */
            SBoundingVolume3DT() : base_type() { }
            /**
             * 
             * @param _min
             * @param _max
             */
            SBoundingVolume3DT(const vec_type& _min, const vec_type& _max) : base_type() { }
            /**
             * 
             * @param aabb
             */
            SBoundingVolume3DT(base_type const& aabb) : base_type() {
                this->invalidate();
                this->merge(aabb);
            }
            /**
             * 
             * @param aabb
             */
            SBoundingVolume3DT(self_type const& aabb) {
                this->min = aabb.min;
                this->max = aabb.max;
                this->refresh();
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(base_type const& a,
                                            base_type const& b) {
                base_type::merge(a, b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(self_type const& a,
                                            self_type const& b) {
                this->invalidate();
                this->merge(a);
                this->merge(b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @param b
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox3DT<TValueType> const& a,
                                            SBoundingBox3DT<TValueType> const& b) {
                base_type::merge(a, b);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(base_type const& a) {
                base_type::merge(a);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(self_type const& a) {
                // Should zero? nope!
                this->min.x = fg::math::min(this->min.x, a.min.x);
                this->min.y = fg::math::min(this->min.y, a.min.y);
                this->min.z = fg::math::min(this->min.z, a.min.z);
                this->max.x = fg::math::max(this->max.x, a.max.x);
                this->max.y = fg::math::max(this->max.y, a.max.y);
                this->max.z = fg::math::max(this->max.z, a.max.z);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param a
             * @return 
             */
            virtual inline self_type& merge(SBoundingBox3DT<TValueType> const& a) {
                base_type::merge(a);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const base_type* aaboxes,
                                     const size_type count = 1) {
                base_type::merge(aaboxes, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param aaboxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const self_type* aaboxes,
                                     const size_type count = 1) {
                if(!count || !aaboxes)
                    return (*this);
                //this->zero(); // nope
                for(size_type i = 0; i < count; i++) {
                    this->merge(aaboxes[i]);
                }
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param boxes
             * @param count
             * @return 
             */
            virtual self_type& merge(const SBoundingBox3DT<TValueType>* boxes,
                                     const size_type count = 1) {
                base_type::merge(boxes, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param data
             * @param count
             * @return 
             */
            virtual self_type& setBoundsFromData(vector_type* data,
                                                 const size_type count = 1) {
                base_type::setBoundsFromData(data, count);
                this->refresh();
                return (*this);
            }
            /**
             * 
             * @param data
             * @param stride
             * @param count
             * @return 
             */
            virtual inline self_type& setBoundsFromData(const void* data,
                                                        const size_type stride,
                                                        const size_type count = 1) {
                AABBHelper::setBoundsFromData((*this), data, stride, count);
                this->refresh();
                return (*this);
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
                this->center.x = (value_type)0;
                this->center.y = (value_type)0;
                this->center.z = (value_type)0;
                this->extent.x = (value_type)0;
                this->extent.y = (value_type)0;
                this->extent.z = (value_type)0;
                this->radius = (value_type)0;
            }
            /**
             * 
             */
            virtual inline void refresh(void) {
                center = 0.5f * (this->min + this->max);
                extent = 0.5f * (this->max - this->min);
                radius = 0.0f;
                radius = math::max(radius, math::pow(extent.z * extent.z + extent.x * extent.x + extent.y * extent.y, 1.0f/2.0f));
//                radius = math::max(radius, math::sqrt(extent.z * extent.z + extent.x * extent.x));
                //radius = math::max(radius, math::sqrt(extent.z * extent.z + extent.y * extent.y));
                //radius = math::max(radius, math::sqrt(extent.y * extent.y + extent.x * extent.x));
            }
            /**
             * 
             */
            virtual inline void invalidate(void) {
                this->zero();
                this->min.x = FLT_MAX;
                this->min.y = FLT_MAX;
                this->min.z = FLT_MAX;
            }
            /**
             *
             */
            virtual inline fgBool isValid(void) const {
                size_type n = this->length();
                for(size_type i = 0; i < n; i++) {
                    if((*this)[i] == FLT_MAX) {
                        return FG_FALSE;
                    }
                }
                return FG_TRUE;
            }
            /**
             * 
             * @return 
             */
            inline vector_type getCenter(void) {
                center = 0.5f * (this->min + this->max);
                return center;
            }
            /**
             * 
             * @return 
             */
            inline vector_type getExtent(void) {
                extent = 0.5f * (this->max - this->min);
                return extent;
            }
            /**
             * 
             * @param m
             */
            virtual void transform(typename Matrix4T<TValueType>::type const& m) {
                base_type::transform(m);
                this->refresh();
            }

            ////////////////////////////////////////////////////////////////////

            using base_type::test;
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

        ///
        typedef SBoundingVolume3DT<float> BoundingVolume3Df;
        ///
        typedef SBoundingVolume3DT<int> BoundingVolume3Di;
        /// 
        typedef SBoundingVolume3DT<unsigned int> BoundingVolume3Du;
        /// 
        typedef SBoundingVolume3DT<double> BoundingVolume3Dd;

    };
};

    #undef FG_INC_GFX_BOUNDING_VOLUME_BLOCK
#endif	/* FG_INC_GFX_BOUNDING_VOLUME */
