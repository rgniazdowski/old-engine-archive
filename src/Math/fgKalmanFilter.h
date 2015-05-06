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
 * KalmanFilter.h
 *
 *  Created on: 12-06-2012
 *      Author: sgniazdowski
 */

#ifndef FG_INC_MATH_KALMAN_FILTER
    #define FG_INC_MATH_KALMAN_FILTER
    #define FG_INC_MATH_KALMAN_FILTER_BLOCK

namespace fg {

    namespace math {

        /**
         *
         */
        struct SKalmanState {
            /// Process noise covariance
            float q;
            /// Measurement noise covariance
            float r;
            /// Value
            float x;
            /// Estimation error covariance
            float p;
            /// Kalman gain
            float k;
            /**
             *
             */
            SKalmanState() : q(0.0f), r(0.0f), x(0.0f), p(0.0f), k(0.0f) { }
        };

        /**
         *
         */
        class CKalmanFilter {
        public:
            typedef CKalmanFilter self_type;
            typedef CKalmanFilter type;

        public:
            /**
             *
             */
            CKalmanFilter() : m_state() { }
            /**
             *
             */
            ~CKalmanFilter() { }

        public:
            /**
             *
             * @param q
             * @param r
             * @param p
             * @param intialValue
             */
            void init(float q, float r, float p, float intialValue);
            /**
             *
             * @param measurement
             */
            void update(float measurement);
            /**
             * Get estimated value
             * @return Value as float
             */
            float value(void) const {
                return float(m_state.x);
            }
        private:
            ///
            SKalmanState m_state;
        };

        /**
         * Integrates three KalmanFilters
         */
        class CTripleKalman {
        public:
            typedef CTripleKalman self_type;
            typedef CTripleKalman type;

        public:

            enum {
                FIRST = 1, SECOND = 2, THRID = 3
            };
            /**
             *
             * @param data_x
             * @param data_y
             * @param data_z
             */
            void update(float data_x, float data_y, float data_z);
            /**
             *
             * @param which
             * @param data
             */
            void update_one(int which, float data);
            /**
             *
             * @return
             */
            CKalmanFilter& getX(void) {
                return fx;
            }
            /**
             *
             * @return
             */
            CKalmanFilter& getY(void) {
                return fy;
            }
            /**
             *
             * @return
             */
            CKalmanFilter& getZ(void) {
                return fz;
            }
            /**
             *
             * @return
             */
            CKalmanFilter const& getX(void) const {
                return fx;
            }
            /**
             *
             * @return
             */
            CKalmanFilter const& getY(void) const {
                return fy;
            }
            /**
             *
             * @return
             */
            CKalmanFilter const& getZ(void) const {
                return fz;
            }

        private:
            ///
            CKalmanFilter fx;
            ///
            CKalmanFilter fy;
            ///
            CKalmanFilter fz;
        };
    } // namespace math
} // namespace fg

    #undef FG_INC_MATH_KALMAN_FILTER_BLOCK
#endif /* FG_INC_MATH_KALMAN_FILTER */
