/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgParticleSystem.h
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#ifndef FG_INC_PARTICLE_SYSTEM
    #define FG_INC_PARTICLE_SYSTEM
    #define FG_INC_PARTICLE_SYSTEM_BLOCK

    #include "fgBool.h"
    #include "fgPsParticleEffect.h"
    #include "fgPsParticleEmitter.h"
    #include "Util/fgTag.h"

namespace fg {
    namespace gfx {
        class CParticleSystem;
    };
};

    #define FG_TAG_PARTICLE_SYSTEM_NAME     "ParticleSystem"
    #define FG_TAG_PARTICLE_SYSTEM          FG_TAG_TYPE(fg::gfx::CParticleSystem)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CParticleSystem, FG_TAG_PARTICLE_SYSTEM_NAME);

    #define FG_MANAGER_PARTICLE     0x00000800

namespace fg {

    namespace gfx {

        /// Tag type for ParticleSystem
        typedef FG_TAG_PARTICLE_SYSTEM ParticleSystemTag;

        /**
         *
         */
        class CParticleSystem : public fg::base::CManager {
        public:
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef CParticleSystem self_type;
            ///
            typedef CParticleSystem type;
            ///
            typedef CVector<CParticleEmitter *> EmittersVec;
            ///
            typedef EmittersVec::iterator EmittersVecItor;

        private:
            /// Pointer to the external resource manager
            fg::base::CManager *m_pResourceMgr;
            /// Pointer to the external scene manager
            fg::base::CManager *m_pSceneMgr;
            /// Emitters vector
            EmittersVec m_emitters;

        public:
            /**
             * 
             */
            CParticleSystem(fg::base::CManager *pResourceMgr = NULL,
                            fg::base::CManager *pSceneMgr = NULL);
            /**
             * 
             */
            virtual ~CParticleSystem();

        protected:
            /**
             * 
             */
            virtual void clear(void);

            /**
             * 
             * @param pEmitter
             * @return 
             */
            fgBool isEmitterInTheArray(CParticleEmitter *pEmitter);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            fgBool isEmitterInTheArray(const std::string& emitterNameTag);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            fgBool isEmitterInTheArray(const char *emitterNameTag);
            
            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static fgBool managedObjectDestructorCallback(void *systemData, void *userData);
            
            /**
             * 
             * @param args
             * @return 
             */
            fgBool sceneClearedCallback(CSceneNode* pNodeA, CSceneNode* pNodeB);

        public:
            /**
             * 
             * @param pResourceMgr
             */
            inline void setResourceManager(fg::base::CManager *pResourceMgr) {
                m_pResourceMgr = pResourceMgr;
            }
            /**
             * 
             * @return 
             */
            inline fg::base::CManager *getResourceManager(void) const {
                return m_pResourceMgr;
            }
            /**
             * 
             * @param pSceneMgr
             */
            void setSceneManager(fg::base::CManager *pSceneMgr);
            /**
             * 
             * @return 
             */
            inline fg::base::CManager *getSceneManager(void) const {
                return m_pSceneMgr;
            }

        public:
            /**
             * 
             * @param pEmitter
             * @return 
             */
            fgBool isEmitterInTheScene(const CParticleEmitter *pEmitter);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            fgBool isEmitterInTheScene(const std::string& emitterNameTag);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            fgBool isEmitterInTheScene(const char *emitterNameTag);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            CParticleEmitter *getParticleEmitter(const std::string& emitterNameTag);

            /**
             * 
             * @param emitterNameTag
             * @return 
             */
            CParticleEmitter *getParticleEmitter(const char *emitterNameTag);

            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

            /**
             * 
             * @param dhUniqueID
             * @param pData
             * @param nameTag
             * @return 
             */
            virtual fgBool insert(CParticleEffect* pEffect, const std::string& nameTag);

            /**
             * 
             * @param shUniqueID
             * @param pStyle
             * @return 
             */
            virtual fgBool insertParticleEffect(CParticleEffect *pEffect);

            /**
             * 
             * @param info
             * @return 
             */
            virtual CParticleEffect* request(const std::string& info);
            /**
             * 
             * @param info
             * @return 
             */
            virtual CParticleEffect* request(const char *info);

            /**
             * 
             * @param particleEffectNameTag
             * @param particleEmitterNameTag
             * @param emitterOrigin
             * @return 
             */
            virtual CParticleEmitter* insertParticleEmitter(const std::string& particleEffectNameTag,
                                                            const std::string& particleEmitterNameTag,
                                                            const Vector3f& emitterOrigin);

            /**
             * 
             * @param particleEffectNameTag
             * @param particleEmitterNameTag
             * @param emitterOrigin
             * @return 
             */
            virtual CParticleEmitter* insertParticleEmitter(const char *particleEffectNameTag,
                                                            const char *particleEmitterNameTag,
                                                            const Vector3f& emitterOrigin);

            /**
             * 
             * @param pParticleEmitter
             * @param particleEffectNameTag
             * @return 
             */
            virtual fgBool insertParticleEmitter(const CParticleEmitter* pParticleEmitter,
                                                 const std::string& particleEffectNameTag);

            /**
             * 
             */
            virtual void calculate(void);

            ////////////////////////////////////////////////////////////////////

        public:
            /**
             * 
             * @param particleEmitterNameTag
             * @param numParticles
             * @param origin
             */
            void addParticles(const std::string& emitterNameTag,
                              unsigned int numParticles,
                              const Vector3f& origin);

            /**
             * 
             * @param particleEmitterNameTag
             * @param numParticles
             * @param origin
             */
            void addParticles(const char* emitterNameTag,
                              unsigned int numParticles,
                              const Vector3f& origin);

            /**
             * 
             * @param particleEmitterNameTag
             * @param numParticles
             * @param x
             * @param y
             * @param z
             */
            void addParticles(const std::string& emitterNameTag,
                              unsigned int numParticles,
                              float x, float y, float z);

            /**
             * 
             * @param particleEmitterNameTag
             * @param numParticles
             * @param x
             * @param y
             * @param z
             */
            void addParticles(const char* emitterNameTag,
                              unsigned int numParticles,
                              float x, float y, float z);

        };
    };
};

    #undef FG_INC_PARTICLE_SYSTEM_BLOCK
#endif /* FG_INC_PARTICLE_SYSTEM */
