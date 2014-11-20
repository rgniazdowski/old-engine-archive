/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/**
 * Portions Copyright (C) Scott Bilas, 2000
 */

#ifndef FG_INC_HANDLE
    #define FG_INC_HANDLE

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

/*
 * The TagType parameter has to be one of fgTag template
 */
template <typename TagType>
class fgHandle {
public:
    typedef TagType tag_type;
private:

    enum {
        // Size to use for index bit field
        FG_HANDLE_MAX_BITS_INDEX = 16,
        // Size to use for magic bit field
        FG_HANDLE_MAX_BITS_MAGIC = 16,

        // Size to compare against for asserting dereferences
        FG_HANDLE_MAX_INDEX = (1 << FG_HANDLE_MAX_BITS_INDEX) - 1,
        // Size to compare against for asserting dereferences
        FG_HANDLE_MAX_MAGIC = (1 << FG_HANDLE_MAX_BITS_MAGIC) - 1,
    };

    union {

        struct {
            // index into resource array
            fgRawIndex m_index : FG_HANDLE_MAX_BITS_INDEX;
            // magic number to check
            fgRawMagic m_magic : FG_HANDLE_MAX_BITS_MAGIC;
        };
        fgRawHandle m_handle;
    };

public:
    // Default constructor for Handle object
    fgHandle() : m_handle(FG_INVALID_HANDLE) { }

    // Reset the handle (becomes invalid)
    void reset(void) {
        m_handle = FG_INVALID_HANDLE;
    }
    /**
     * 
     * @param source
     */
    void copyFrom(const fgHandle<TagType>& source) {
        this->m_handle = source.getHandle();
        this->m_magic = source.getMagic();
        this->m_index = source.getIndex();
    }

    // Init handle with given index
    fgBool init(fgRawIndex index);

    // Get the index part of the handle
    fgRawIndex getIndex(void) const {
        return m_index;
    }
    // Get the magic part of the handle
    fgRawMagic getMagic(void) const {
        return m_magic;
    }
    // Return the handle ID number
    fgRawHandle getHandle(void) const {
        return m_handle;
    }
    // Check if handle is null
    fgBool isNull(void) const {
        return (fgBool)(m_handle == FG_INVALID_HANDLE);
    }
    // Return the handle ID number
    operator fgRawHandle(void) const {
        return m_handle;
    }
    //
    static const char *getTagName(void) {
        return TagType::name();
    }
};
/*
 *
 */
template <typename TagType>
fgBool fgHandle<TagType>::init(fgRawIndex index) {
    if(!isNull()) {
        // Don't allow reassignment
        return FG_FALSE;
    }
    if(index > FG_HANDLE_MAX_INDEX) {
        // Verify range
        return FG_FALSE;
    }

    static fgRawMagic s_autoMagic = 0;
    if(++s_autoMagic >= FG_HANDLE_MAX_MAGIC) {
        s_autoMagic = 1;
    }

    m_index = index;
    m_magic = s_autoMagic;
    return FG_TRUE;
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator !=(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() != r.getHandle());
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator ==(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() == r.getHandle());
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator >(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() > r.getHandle());
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator <(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() < r.getHandle());
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator >=(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() >= r.getHandle());
}
/**
 * 
 * @param l
 * @param r
 * @return 
 */
template <typename TagType>
inline bool operator <=(fgHandle <TagType> l, fgHandle <TagType> r) {
    return ( l.getHandle() <= r.getHandle());
}

#endif /* FG_INC_HANDLE */
