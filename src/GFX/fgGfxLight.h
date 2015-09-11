/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_LIGHT
    #define FG_INC_GFX_LIGHT
    #define FG_INC_GFX_LIGHT_BLOCK

    #ifndef FG_INC_GFX_TYPES
        #include "fgGfxTypes.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SLight {
            typedef SLight self_type;
            typedef SLight type;
            ///
            Color4f ambient;
            ///
            Color4f diffuse;
            ///
            Color4f specular;
            /**
             *
             */
            SLight() : ambient(), diffuse(), specular() { }
            /**
             *
             * @param orig
             */
            SLight(const self_type& orig) {
                this->ambient = orig.ambient;
                this->diffuse = orig.diffuse;
                this->specular = orig.specular;
            }
            /**
             *
             * @param _ambient
             * @param _diffuse
             * @param _specular
             */
            SLight(const Color4f& _ambient,
                   const Color4f& _diffuse,
                   const Color4f& _specular) :
            ambient(_ambient),
            diffuse(_diffuse),
            specular(_specular) { }
            /**
             *
             */
            virtual ~SLight() {
                ambient = Color4f();
                diffuse = Color4f();
                specular = Color4f();
            }
        }; // struct SLight

        /**
         *
         */
        struct SDirectionalLight : public SLight {
            typedef SDirectionalLight self_type;
            typedef SDirectionalLight type;
            typedef SLight base_type;

            ///
            Vector3f direction;
            ///
            Vector3f halfPlane;
            /**
             *
             */
            SDirectionalLight() : base_type(), direction(), halfPlane() { }
            /**
             *
             * @param orig
             */
            SDirectionalLight(const self_type& orig) : base_type(orig) {
                this->direction = orig.direction;
                this->halfPlane = orig.halfPlane;
            }
            /**
             *
             * @param _direction
             * @param _halfPlane
             */
            SDirectionalLight(const Vec3f& _direction, const Vec3f& _halfPlane) :
            base_type(), direction(_direction), halfPlane(_halfPlane) { }
            /**
             *
             * @param _direction
             * @param _halfPlane
             * @param _ambient
             * @param _diffuse
             * @param _specular
             */
            SDirectionalLight(const Vec3f& _direction, const Vec3f& _halfPlane,
                              const Color4f& _ambient,
                              const Color4f& _diffuse,
                              const Color4f& _specular) : base_type(_ambient, _diffuse, _specular),
            direction(_direction), halfPlane(_halfPlane) { }
            /**
             *
             */
            virtual ~SDirectionalLight() {
                direction = Vector3f();
                halfPlane = Vector3f();
            }
        }; // struct SDirectionalLight
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_LIGHT_BLOCK
#endif
