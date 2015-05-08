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
 * File:   fgFastCmp.h
 * Author: vigilant
 *
 * Created on December 12, 2014, 8:44 AM
 */

#ifndef FG_INC_FAST_CMP
    #define FG_INC_FAST_CMP
    #define FG_INC_FAST_CMP_BLOCK

#include "fgBuildConfig.h"

#if defined(FG_USING_MARMALADE)
    #include "s3eTypes.h"
#else
    #include <cstdint>
#endif
    #include "fgBool.h"

namespace fg {
    namespace util {

        /**
         *
         */
        class CFastCmp {
        public:
            ///
            typedef uint64_t data_type;
            ///
            typedef uint64_t data_type_64;
            ///
            typedef uint32_t data_type_32;
            ///
            typedef uint16_t data_type_16;
            ///
            typedef uint8_t data_type_8;
            ///
            typedef uint8_t size_type;

            /**
             *
             */
            enum DataSize {
                CMP_DATA_64,
                CMP_DATA_32,
                CMP_DATA_16
            };

        public:
            /**
             * 
             */
            CFastCmp(const size_type numParts = 2, const DataSize dataSize = CMP_DATA_32);
            /**
             * 
             * @param orig
             */
            CFastCmp(const CFastCmp& orig);
            /**
             * 
             */
            virtual ~CFastCmp();

            /**
             * 
             * @param partID
             * @param partValue
             */
            void setPart(size_type partID, data_type_32 partValue);
            /**
             * 
             * @return 
             */
            inline fgBool isValid(void) const {
                return (fgBool)(m_maxBits != 0);
            }
            /**
             * 
             */
            inline void clear(void) {
                m_data = (data_type)0;
            }
            /**
             * 
             * @param numParts
             * @param dataSize
             */
            void reset(const size_type numParts = 2, const DataSize dataSize = CMP_DATA_32);
            /**
             * 
             * @return 
             */
            inline size_type getMaxBits(void) const {
                return m_maxBits;
            }
            /**
             * 
             * @return 
             */
            inline size_type getNumParts(void) const {
                return m_numParts;
            }
            /**
             * 
             * @return 
             */
            inline size_type getNumPartBits(void) const {
                return m_numPartBits;
            }
            /**
             * 
             * @return 
             */
            inline data_type getData(void) const {
                return m_data;
            }
            /**
             * 
             * @return 
             */
            inline data_type_32 getData32(void) const {
                return m_data32;
            }
            /**
             * 
             * @return 
             */
            inline data_type_16 getData16(void) const {
                return m_data16;
            }
            /**
             * 
             * @param rawPartID
             * @return 
             */
            inline data_type_8 getRawDataPart(size_type rawPartID) {
                if(rawPartID >= DATA_MAX_RAW_PARTS)
                    rawPartID = DATA_MAX_RAW_PARTS - 1;
                return m_dataVec[rawPartID];
            }
        public:
            static inline bool less(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data < b.m_data;
            }
            
            static inline bool less_eq(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data <= b.m_data;
            }
            
            static inline bool greater(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data > b.m_data;
            }
            
            static inline bool greater_eq(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data >= b.m_data;
            }
            
            static inline bool less32(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data32 < b.m_data32;
            }
            
            static inline bool less_eq32(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data32 <= b.m_data32;
            }
            
            static inline bool greater32(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data32 > b.m_data32;
            }
            
            static inline bool greater_eq32(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data32 >= b.m_data32;
            }
            
            static inline bool less16(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data16 < b.m_data16;
            }
            
            static inline bool less_eq16(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data16 <= b.m_data16;
            }
            
            static inline bool greater16(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data16 > b.m_data16;
            }
            
            static inline bool greater_eq16(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data16 >= b.m_data16;
            }
            
            static inline bool equal(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data == b.m_data;
            }
            
            static inline bool equal32(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data32 == b.m_data32;
            }
            
            static inline bool equal16(const CFastCmp &a, const CFastCmp &b) {
                return a.m_data16 == b.m_data16;
            }
            
        public:
            operator data_type() const {
                return m_data;
            }
            
            operator data_type_32() const {
                return m_data32;
            }
            
            operator data_type_16() const {
                return m_data16;
            }            
            
        public:
            ///
            static const size_type DATA_MAX_RAW_PARTS = 8;
            ///
            static const size_type DATA_MAX_BITS = 64;

        private:
            ///
            data_type_8 m_numParts;
            ///
            data_type_8 m_maxBits;
            ///
            data_type_8 m_numPartBits;

            /**
             *
             */
            union {
                ///
                data_type m_data;
                ///
                data_type_64 m_data64;
                ///
                data_type_32 m_data32;
                ///
                data_type_16 m_data16;
                ///
                data_type_8 m_data8;
                ///
                data_type_8 m_dataVec[DATA_MAX_RAW_PARTS];
            };
        };
    } // namespace util
} // namespace fg

    #undef FG_INC_FAST_CMP_BLOCK
#endif	/* FG_INC_FAST_CMP */
