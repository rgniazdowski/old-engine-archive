#ifndef FG_INC_MATH_QUATERNION
    #define FG_INC_MATH_QUATERNION
    #define FG_INC_MATH_QUATERNION_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)

        #include "glm/gtc/quaternion.hpp"
        #include "glm/gtx/quaternion.hpp"

        #if !defined(FG_MATH_GLM_QUAT_MASK)
            #define FG_MATH_GLM_QUAT_MASK
typedef glm::quat Quaternionf;
typedef glm::dquat Quaterniond;

            #if !defined(FG_MATH_GLM_QUAT_TEMPLATE_MASK)
                #if 0 // #FIXME - requires C++11

template<typename T>
struct QuatertionT {
    typedef glm::detail::tquat<T, glm::defaultp> type;
};
                #else
template<typename T>
using QuaternionT = glm::detail::tquat<T, glm::defaultp>;
                #endif /* FG_USING_ */
            #endif /* !defined(FG_MATH_GLM_QUAT_TEMPLATE_MASK) */

typedef Quaternionf Quatf;
typedef Quaterniond Quatd;

        #endif /* !defined(FG_MATH_GLM_QUAT_MASK) */

    #endif /* defined(FG_USING_GLM) */

    #if !defined(FG_USING_GLM)
    #endif /* !defined(FG_USING_GLM) */

    #undef FG_INC_MATH_QUATERNION_BLOCK
#endif /* FG_INC_MATH_QUATERNION */
