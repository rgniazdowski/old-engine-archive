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
 * File:   fgPsParticleEmitter.h
 * Author: vigilant
 *
 * Created on October 24, 2014, 4:30 PM
 */

#ifndef FG_INC_PS_PARTICLE_EMITTER
    #define FG_INC_PS_PARTICLE_EMITTER
    #undef FG_INC_PS_PARTICLE_EMITTER_BLOCK

    #include "fgVector.h"
    #include "GFX/Scene/fgGfxSceneNode.h"
    #include "fgPsParticleEffect.h"

namespace fg {
    namespace gfx {

        class CCamera;
        
        /**
         * 
         */
        class CParticleEmitter : public CSceneNode {
        public:
            /// Base type of the ParticleEmitter
            typedef fg::gfx::CSceneNode base_type;
            ///
            typedef CParticleEmitter self_type;
            ///
            typedef CParticleEmitter type;
            /// Vector type definition for holding Particle Effects
            typedef CVector<CParticleEffect *> ParticleEffects;
            /// Iterator for the ParticleEffects vector
            typedef ParticleEffects::iterator ParticleEffectsItor;
            /// Vector type holding Particles
            typedef CVector<SParticle> ParticleData;
            /// Iterator for the Particles vector
            typedef ParticleData::iterator ParticleDataItor;

        private:
            /// Pointers to the particle effects to which
            /// this particle emitter is bound
            ParticleEffects m_effects;
            /// Origin of the emitter (world space)
            Vector3f m_origin;
            /// Particle data used for manipulation, drawing
            ParticleData m_particles;
            /// Current number of particles in the emitter
            unsigned int m_numParticles;
            /// Maximum number of the particles for this emitter 
            unsigned int m_maxCount;
            /// Pointer to the camera, so the particles can be rotated properly
            CCamera *m_pCamera;

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
            inline ParticleData& getParticleData(void) {
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
             * @param pCamera
             */
            inline void setCamera(CCamera *pCamera) {
                m_pCamera = pCamera;
            }
            /**
             * 
             * @return 
             */
            inline CCamera *getCamera(void) const {
                return m_pCamera;
            }
            
            ////////////////////////////////////////////////////////////////////
            
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

            using base_type::draw;
            /**
             * 
             */
            virtual void draw(const Matrix4f& modelMat);

        }; // class CParticleEmitter

    } // namespace gfx
} // namespace fg

    #undef FG_INC_PS_PARTICLE_EMITTER_BLOCK
#endif	/* FG_INC_PS_PARTICLE_EMITTER */
