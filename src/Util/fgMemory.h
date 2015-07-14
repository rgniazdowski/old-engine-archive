/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MEMORY
    #define FG_INC_MEMORY
    #define FG_INC_MEMORY_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include <cstring>

    #ifdef FG_USING_MARMALADE

        #include "s3eMemory.h"

        #define fgMalloc_sys_	s3eMalloc
        #define fgFree_sys_	s3eFree
        #define fgRealloc_sys_	s3eRealloc

// FIXME need more wrappers for marmalade's heap memory handling

    #else

        #include <malloc.h>

        #define fgMalloc_sys_	malloc
        #define fgFree_sys_	free
        #define fgRealloc_sys_	realloc

    #endif

/*
 * This is a special template function for allocating memory.
 * The size argument differs from the standard implementation.
 * Instead of size there is count which specifies number of 
 * copies. Size = Count * sizeof(Type)
 */
template<class Type>
inline Type *fgMalloc(const int count = 1, const fgBool clear = FG_TRUE, Type *unused = NULL) {
    if(count <= 0)
        return NULL;
    size_t size = count * sizeof (Type);
    Type *data = (Type *)fgMalloc_sys_(size);
    if(!data)
        return NULL;
    if(clear) {
        memset((void *)data, 0, size);
    }
    return data;
}

template <> inline void *fgMalloc<void>(const int count , const fgBool clear, void *unused) {
    if(count <= 0)
        return NULL;
    size_t size = count;
    void *data = (void *)fgMalloc_sys_(size);
    if(!data)
        return NULL;
    if(clear) {
        memset(data, 0, size);
    }
    return data;
}

template<class Type>
inline Type *fgRealloc(Type *inptr, const int count = 1, const fgBool clear = FG_TRUE) {
    if(count <= 0)
        return NULL;
    size_t size = count * sizeof (Type);
    Type *data = (Type *)fgRealloc_sys_(inptr, size);
    if(!data)
        return NULL;
    if(clear) {
        memset((void *)data, 0, size);
    }
    return data;
}

template <> inline void *fgRealloc<void>(void *inptr, const int count, const fgBool clear) {
    if(count <= 0)
        return NULL;
    size_t size = count;
    void *data = (void *)fgRealloc_sys_(inptr, size);
    if(!data)
        return NULL;
    if(clear) {
        memset(data, 0, size);
    }
    return data;
}

inline void fgFree(void *& item, const int size = -1, const fgBool clear = FG_FALSE) {
    if(!item)
        return;

    if(clear && size > 0) {
        memset(item, 0, (size_t)size);
    }

    fgFree_sys_(item);

    item = NULL;
}

template<class Type>
inline void fgFree(Type *& item, const fgBool clear = FG_FALSE) {
    if(!item)
        return;
    size_t size = sizeof (Type);
    if(clear && size > 0) {
        memset(item, 0, size);
    }

    fgFree_sys_((void *)item);

    item = NULL;
}

    //#define fgRealloc fgRealloc_sys_

    #undef FG_INC_MEMORY_BLOCK
#endif /* FG_INC_MEMORY */
    