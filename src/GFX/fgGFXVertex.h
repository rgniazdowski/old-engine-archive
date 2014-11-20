/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXVertex.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:24 PM
 */

#ifndef FG_INC_GFX_VERTEX
    #define	FG_INC_GFX_VERTEX

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #ifndef FG_INC_GFX_COLOR
        #include "fgGFXColor.h"
    #endif

    #if defined(FG_USING_GLM)

        #include "glm/vec2.hpp"
        #include "glm/vec3.hpp"
        #include "glm/vec4.hpp"

        #if !defined(FG_MATH_GLM_VECTOR_MASK)
            #define FG_MATH_GLM_VECTOR_MASK

            #if !defined(FG_MATH_GLM_VECTOR_TEMPLATE_MASK)
                #define FG_MATH_GLM_VECTOR_TEMPLATE_MASK
// #FIXME - This requires c++11
//typedef glm::detail::tvec1 fgVector1T;
template<typename T>
using fgVector2T = glm::detail::tvec2<T, glm::defaultp>;
//typedef glm::detail::tvec2<typename T, glm::precision P> fgVector2T<T, P>;
template<typename T>
using fgVector3T = glm::detail::tvec3<T, glm::defaultp>;
template<typename T>
using fgVector4T = glm::detail::tvec4<T, glm::defaultp>;
            #endif

typedef glm::bvec2 fgVector2b;
typedef glm::bvec3 fgVector3b;
typedef glm::bvec4 fgVector4b;

typedef glm::uvec2 fgVector2u;
typedef glm::uvec3 fgVector3u;
typedef glm::uvec4 fgVector4u;

typedef glm::ivec2 fgVector2i;
typedef glm::ivec3 fgVector3i;
typedef glm::ivec4 fgVector4i;

typedef glm::vec2 fgVector2f;
typedef glm::vec3 fgVector3f;
typedef glm::vec4 fgVector4f;

typedef glm::dvec2 fgVector2d;
typedef glm::dvec3 fgVector3d;
typedef glm::dvec4 fgVector4d;

        #endif /* FG_MATH_GLM_VECTOR_MASK */

        #if defined(FG_MATH_GLM_VECTOR_MASK)
typedef fgVector2b fgVec2b;
typedef fgVector3b fgVec3b;
typedef fgVector4b fgVec4b;

typedef fgVector2u fgVec2u;
typedef fgVector3u fgVec3u;
typedef fgVector4u fgVec4u;

typedef fgVector2i fgVec2i;
typedef fgVector3i fgVec3i;
typedef fgVector4i fgVec4i;

typedef fgVector2f fgVec2f;
typedef fgVector3f fgVec3f;
typedef fgVector4f fgVec4f;

typedef fgVector2d fgVec2d;
typedef fgVector3d fgVec3d;
typedef fgVector4d fgVec4d;

            #if defined(FG_MATH_GLM_VECTOR_TEMPLATE_MASK)
//typedef fgVector1T fgVec1T;
// #FIXME #HAX
                #define fgVec2T fgVector2T
                #define fgVec3T fgVector3T
                #define fgVec4T fgVector4T
            #endif
        #endif /* FG_MATH_GLM_VECTOR_MASK */

    #else

    #endif /* FG_USING_GLM */

    #ifndef FG_INC_GFX_ATTRIB_BITS
        #include "fgGFXAttribBits.h"
    #endif

/*
 * Vertex4 - pos, norm, uv, color
 */
struct fgVertex4v {
    fgVector3f position; // location 0
    fgVector3f normal; // location 1
    fgVector2f uv; // location 2
    fgColor4f color; // location 3

    //
    static unsigned int size(void) {
        return 4;
    }

    //
    static unsigned int attribMask(void) {
        return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT | FG_GFX_COLOR_BIT;
    }
};

typedef fgVertex4v fgGfxVertex4v;

/*
 * Vertex3 - pos, norm, uv
 */
struct fgVertex3v {
    fgVector3f position;
    fgVector3f normal;
    fgVector2f uv;

    // #FIXME - change name 'size'
    static unsigned int size(void) {
        return 3;
    }

    //
    static unsigned int attribMask(void) {
        return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT;
    }
};

typedef fgVertex3v fgGfxVertex3v;

/*
 * Vertex2 - pos, uv
 */
struct fgVertex2v {
    fgVector3f position;
    fgVector2f uv;

    //
    static unsigned int size(void) {
        return 2;
    }

    //
    static unsigned int attribMask(void) {
        return FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT;
    }
};

typedef fgVertex2v fgGfxVertex2v;

    #include <cstdio>

inline void dumpVector(const fgVector3f & vec, const char *title) {
    printf("%s = { %.2f %.2f %.2f }\n", ( title ? title : "X"), vec.x, vec.y, vec.z);
}



#endif	/* FG_INC_GFX_VERTEX */

