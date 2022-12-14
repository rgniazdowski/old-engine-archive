/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PARTICLE
    #define FG_INC_PARTICLE
    #define FG_INC_PARTICLE_BLOCK

    #include "GFX/fgGfxTypes.h"
    #include "GFX/fgGfxBoundingBox.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SParticle {
            /// Current position of the single particle in 3D space
            /// Current size of the particle
            /// Position and size is stored in special bounding box
            BoundingBox3Df bbox;
            /// Velocity of a particle (per second)
            Vector3f velocity;
            /// Actual rotation in 3 angles, given in radians 
            Vector3f rotation;
            /// Angular velocity (per second), given in radians
            Vector3f angularVelocity;
            /// Current life of the particle (if equal to zero the particle will be deleted)
            float life;
            /// Speed of dying
            float fadeSpeed;
            /// Time to live (milliseconds), setting the value for TTL changes the life and fade speed values - needs to be set via function
            int ttl;
            /// Time of creation
            unsigned long int spawnTime;
            /// Color of the particle, stored as float for better precision
            Color4f color;
            /// Texture index - this is not texture ID from GFX subsystem
            /// used for binding - it is more of index of the texture in 
            /// the particle texture sheet (many images in one file, tiled)
            unsigned int texIndex;
            /// Burning parameter - used for transition between additive and modulate blending
            float burn;
            /// Pointer to additional data structure (if any is needed)
            void *data;
            /**
             * 
             */
            SParticle() { }
            /**
             * 
             * @param inColor
             */
            void setColor(const Color4f& inColor) {
                color = inColor;
            }
            /**
             * 
             * @param r
             * @param g
             * @param b
             * @param a
             */
            void setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
                color.r = (float)r / 255.0f;
                color.g = (float)g / 255.0f;
                color.b = (float)b / 255.0f;
                color.a = (float)a / 255.0f;
            }
            /**
             * 
             * @param r
             * @param g
             * @param b
             * @param a
             */
            void setColor(const float r, const float g, const float b, const float a) {
                color.r = r;
                color.g = g;
                color.b = b;
                color.a = a;
            }
            /**
             * 
             * @param _ttl
             */
            void setTTL(const int _ttl) {
                // _ttl stores the time to live in milliseconds
                // It will be easier to just store TTL and every
                // frame decrement the ttl with the DT time
                // However life value adjusted for range <0,X> 
                // is useful for some scaling effects
                // This also means that fadeSpeed/life need
                // to be stored as float values
                if(ttl) {
                    ttl = _ttl;
                    life = 1000.0f;
                    fadeSpeed = life / ttl * 1000.0f;
                } else {
                    ttl = 0;
                    life = 1000.0f;
                    fadeSpeed = 0.0f;
                }
            }
            /**
             * 
             * @param _life
             * @param _fadeSpeed
             */
            void setLife(const float _life, const float _fadeSpeed) {
                life = _life;
                fadeSpeed = _fadeSpeed;
                if(fadeSpeed > 0.0f) {
                    ttl = life / fadeSpeed;
                } else {
                    ttl = 0;
                }
            }
        }; // struct SParticle
        
    } // namespace gfx
} // namespace fg

    #undef FG_INC_PARTICLE_BLOCK
#endif /* FG_INC_PARTICLE */
