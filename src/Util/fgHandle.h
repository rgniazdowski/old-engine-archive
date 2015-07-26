/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/**
 * Portions Copyright (C) Scott Bilas, 2000
 */

#ifndef FG_INC_HANDLE
    #define FG_INC_HANDLE
    #define FG_INC_HANDLE_BLOCK

    #include "fgCommon.h"

    #ifndef FG_RAW_HANDLE_TYPE
        #define FG_RAW_HANDLE_TYPE unsigned int
    #endif

// Type of the raw handle
typedef FG_RAW_HANDLE_TYPE fgRawHandle;
// Type of the index number (part of handle ID)
typedef FG_RAW_HANDLE_TYPE fgRawIndex;
// Type of the magic number
typedef FG_RAW_HANDLE_TYPE fgRawMagic;

    #ifndef FG_INVALID_HANDLE
// All bits filled defines an invalid resource handle
        #define FG_INVALID_HANDLE               0xFFFFFFFFUL
        #define FG_IS_INVALID_HANDLE(_rh)       ( _rh.isNull() )
        #define FG_IS_VALID_HANDLE(_rh)         ( !_rh.isNull() )
    #endif

namespace fg {
    namespace util {

        /**
         * The TagType parameter has to be one of fgTag template
         */
        template <typename TagType>
        class CHandle {
        public:
            typedef CHandle<TagType> self_type;
            typedef CHandle<TagType> type;
            typedef CHandle<TagType>& self_ref;
            typedef TagType tag_type;
        private:

            enum {
                /// Size to use for index bit field
                MAX_BITS_INDEX = 16,
                /// Size to use for magic bit field
                MAX_BITS_MAGIC = 16,

                /// Size to compare against for asserting dereferences
                MAX_INDEX = (1 << MAX_BITS_INDEX) - 1,
                /// Size to compare against for asserting dereferences
                MAX_MAGIC = (1 << MAX_BITS_MAGIC) - 1,
            };

            union {

                struct {
                    // index into resource array
                    fgRawIndex m_index : MAX_BITS_INDEX;
                    // magic number to check
                    fgRawMagic m_magic : MAX_BITS_MAGIC;
                };
                fgRawHandle m_handle;
            };

        public:
            /**
             * Default constructor for Handle object
             */
            CHandle() : m_handle(FG_INVALID_HANDLE) { }
            /**
             *
             * @param handle
             */
            CHandle(fgRawHandle handle) : m_handle(handle) { }
            /**
             * 
             * @param index
             * @param magic
             */
            CHandle(fgRawIndex index, fgRawMagic magic) : m_index(index),
            m_magic(magic) { }
            /**
             *
             */
            virtual ~CHandle() {
                this->m_handle = FG_INVALID_HANDLE;
            }
            /**
             *
             * @param other
             * @return
             */
            self_ref operator =(self_type other) {
                this->m_handle = other.m_handle;
                return *this;
            }
            /**
             * 
             * @param other_handle
             * @return
             */
            self_ref operator =(fgRawHandle other_handle) {
                this->m_handle = other_handle;
                return *this;
            }
            /**
             * Reset the handle (becomes invalid)
             */
            void reset(void) {
                this->m_handle = FG_INVALID_HANDLE;
            }
            /**
             * 
             * @param source
             */
            void copyFrom(const CHandle<TagType>& source) {
                this->m_handle = source.getHandle();
            }

            /**
             * Init handle with given index
             * @param index
             * @return
             */
            fgBool init(fgRawIndex index);
            /**
             * Get the index part of the handle
             * @return
             */
            fgRawIndex getIndex(void) const {
                return m_index;
            }
            /**
             * Get the magic part of the handle
             * @return
             */
            fgRawMagic getMagic(void) const {
                return m_magic;
            }
            /**
             * Return the handle ID number
             * @return
             */
            fgRawHandle getHandle(void) const {
                return m_handle;
            }
            /**
             * Check if handle is null
             * @return
             */
            fgBool isNull(void) const {
                return (fgBool)(m_handle == FG_INVALID_HANDLE);
            }
            /**
             * Return the handle ID number
             * @return
             */
            operator fgRawHandle(void) const {
                return m_handle;
            }
            /**
             * 
             * @return
             */
            static const char *getTagName(void) {
                return TagType::name();
            }
        }; // class CHandle
    } // namespace util
} // namespace fg
//------------------------------------------------------------------------------
template <typename TagType>
fgBool fg::util::CHandle<TagType>::init(fgRawIndex index) {
    if(!isNull()) {
        // Don't allow reassignment
        return FG_FALSE;
    }
    if(index > MAX_INDEX) {
        // Verify range
        return FG_FALSE;
    }

    static fgRawMagic s_autoMagic = 0;
    if(++s_autoMagic >= MAX_MAGIC) {
        s_autoMagic = 1;
    }

    m_index = index;
    m_magic = s_autoMagic;
    return FG_TRUE;
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator !=(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() != r.getHandle());
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator ==(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() == r.getHandle());
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator >(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() > r.getHandle());
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator <(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() < r.getHandle());
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator >=(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() >= r.getHandle());
}

//------------------------------------------------------------------------------
template <typename TagType>
inline bool operator <=(const fg::util::CHandle<TagType>& l, const fg::util::CHandle<TagType>& r) {
    return ( l.getHandle() <= r.getHandle());
}
//------------------------------------------------------------------------------

    #undef FG_INC_HANDLE_BLOCK
#endif /* FG_INC_HANDLE */
