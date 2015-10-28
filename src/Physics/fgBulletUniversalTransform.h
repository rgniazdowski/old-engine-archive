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
 * File:   fgBulletUniversalTransform.h
 * Author: vigilant
 *
 * Created on October 11, 2015, 11:34 PM
 */

#ifndef FG_INC_BULLET_UNIVERSAL_TRANSFORM
    #define FG_INC_BULLET_UNIVERSAL_TRANSFORM
    #define FG_INC_BULLET_UNIVERSAL_TRANSFORM_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_USING_BULLET)
        #include "fgBulletMaskTypes.h"
        #include "fgBulletHelper.h"
        #include "LinearMath/btTransform.h"

namespace fg {
    namespace physics {

        /**
         *
         */
        struct SBulletUniTransform : public math::SUniversalTransform {
            typedef math::SUniversalTransform base_type;
            typedef SBulletUniTransform self_type;
            typedef SBulletUniTransform type;
        public:
            /**
             *
             * @param _pTransform
             */
            SBulletUniTransform(btTransform* _pTransform = NULL) : pTransform(_pTransform) { }
            /**
             * 
             */
            virtual ~SBulletUniTransform() {
                pTransform = NULL;
            }
            //------------------------------------------------------------------
            /**
             *
             * @param inMatrix
             */
            virtual void setTransform(const Matrix4f& inMatrix) {
                if(!pTransform)
                    return;
                pTransform->setFromOpenGLMatrix(math::value_ptr(inMatrix));
            }
            /**
             *
             * @param outMatrix
             */
            virtual void getTransform(Matrix4f& outMatrix) const {
                if(!pTransform)
                    return;
                bullet_helper::copyMatrix4x4(outMatrix, *pTransform);
            }
            /**
             *
             * @param outTranslation
             */
            virtual void getTranslation(Vector3f& outTranslation) const {
                if(!pTransform)
                    return;
                const btVector3& translation = pTransform->getOrigin();
                outTranslation.x = translation.x();
                outTranslation.y = translation.y();
                outTranslation.z = translation.z();
            }
            /// Pointer to external bullet transform instance
            btTransform* pTransform;

        }; // struct SBulletUniTransform

    } // namespace physics

} // namespace fg

    #endif /* FG_USING_BULLET */

    #undef FG_INC_BULLET_UNIVERSAL_TRANSFORM_BLOCK
#endif	/* FG_INC_BULLET_UNIVERSAL_TRANSFORM */
