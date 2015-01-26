/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgPsParticleEmitter.h
 * Author: vigilant
 *
 * Created on October 24, 2014, 4:30 PM
 */

#ifndef FG_INC_PS_PARTICLE_EMITTER
    #define FG_INC_PS_PARTICLE_EMITTER
    #undef FG_INC_PS_PARTICLE_EMITTER_BLOCK

    #include "fgVector.h"
    #include "GFX/Scene/fgGFXSceneNode.h"
    #include "fgPsParticleEffect.h"

namespace fg {
    namespace gfx {

        /**
         * 
         */
        class CParticleEmitter : public CSceneNode {
        public:
            /// Base type of the ParticleEmitter
            typedef fg::gfx::CSceneNode base_type;
            /// Vector type definition for holding Particle Effects
            typedef fg::CVector<CParticleEffect *> particleEffects;
            /// Iterator for the ParticleEffects vector
            typedef particleEffects::iterator particleEffectsItor;
            /// Vector type holding Particles
            typedef fg::CVector<SParticle> particleData;
            /// Iterator for the Particles vector
            typedef particleData::iterator particleDataItor;

        private:
            /// Pointers to the particle effects to which
            /// this particle emitter is bound
            particleEffects m_effects;
            /// Origin of the emitter (world space)
            Vector3f m_origin;
            /// Particle data used for manipulation, drawing
            particleData m_particles;
            /// Current number of particles in the emitter
            unsigned int m_numParticles;
            /// Maximum number of the particles for this emitter 
            unsigned int m_maxCount;

        public:
            /**
             * 
             */
            CParticleEmitter(CParticleEffect *pParticleEffect = NULL);

            /**
             * 
             */
            virtual ~CParticleEmitter();
            /**
             * 
             * @param maxCount
             */
            void setMaxCount(const unsigned int maxCount) {
                if(maxCount) {
                    m_particles.reserve(maxCount);
                    m_particles.resize(maxCount);
                    m_maxCount = maxCount;
                }
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getMaxCount(void) const {
                return m_maxCount;
            }
            /**
             * 
             * @return 
             */
            inline CParticleEffect* getParticleEffect(void) const {
                if(m_effects.size())
                    return m_effects.back();
                return NULL;
            }
            /**
             * 
             * @return 
             */
            inline particleData& getParticleData(void) {
                return m_particles;
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getParticleCount(void) const {
                return m_numParticles;
            }

            /**
             * 
             * @param which
             */
            void removeParticle(const unsigned int which);

            /**
             * 
             * @param count
             */
            void addParticles(const unsigned int count, const Vector3f& customOrigin);

            /**
             * 
             * @param pParticleEffect
             * @return
             */
            fgBool setupFromParticleEffect(CParticleEffect *pParticleEffect);

            /**
             * 
             */
            virtual void calculate(void);

        };
    };
};

    #undef FG_INC_PS_PARTICLE_EMITTER_BLOCK
#endif	/* FG_INC_PS_PARTICLE_EMITTER */
