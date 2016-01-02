/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_SFX_MANAGER
    #define FG_INC_SFX_MANAGER
    #define FG_INC_SFX_MANAGER_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"
    #include "fgManagerBase.h"

    #include "fgSFXSoundResource.h"
    #include "fgSFXMusicResource.h"

    #if !defined(FG_SFX_VOLUME_TYPE) || !defined(FG_SFX_VOLUME_TYPE_DECLARED)
        #define FG_SFX_VOLUME_TYPE_DECLARED
        #if defined(FG_USING_SDL_MIXER) || defined(FG_USING_SDL) || defined(FG_USING_SDL2)
            #define FG_SFX_VOLUME_TYPE unsigned short int
        #else
            #define FG_SFX_VOLUME_TYPE int
        #endif
    #endif

    #if !defined(FG_MANAGER_SOUND)
        #define FG_MANAGER_SOUND        0x00008000
    #endif

namespace fg {
    namespace sfx {

        /**
         * 
         */
        class CSfxManager : public fg::base::CManager {
        public:
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef FG_SFX_VOLUME_TYPE volume_type;

        private:
            ///
            volume_type m_sfxVolume;
            ///
            volume_type m_musVolume;  
            ///
            fg::base::CManager *m_pResourceMgr;

        public:
            /**
             * 
             */
            CSfxManager(fg::base::CManager *pResourceMgr = NULL);
            /**
             * 
             */
            virtual ~CSfxManager();

        protected:
            /**
             * 
             * @param volume
             */
            virtual void clear(void);

            /**
             * 
             * @param nameTag
             * @return 
             */
            fg::sfx::base::CAudio *get(const char *nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fg::sfx::base::CAudio *get(const std::string& nameTag);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fg::sfx::base::CAudio *get(const resource::ResourceHandle& soundHandle);
            
        public:
            /**
             * 
             * @param info
             * @return 
             */
            fg::sfx::base::CAudio *request(const char *info);
            /**
             * 
             * @param info
             * @return 
             */
            fg::sfx::base::CAudio *request(const std::string& info);

        public:
            /**
             * 
             * @param pResourceMgr
             */
            void setResourceManager(fg::base::CManager *pResourceMgr);
            /**
             * 
             * @return 
             */
            fg::base::CManager *getResourceManager(void) const {
                return m_pResourceMgr;
            }

        public:
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

        public:
            /**
             * 
             * @param volume
             */
            void setSfxVolume(volume_type volume);
            /**
             * 
             */
            void applySfxVolume();
            /**
             * 
             * @param volume
             */
            void setMusicVolume(volume_type volume);
            /**
             * 
             */
            void applyMusicVolume();
            /**
             * 
             * @return 
             */
            volume_type getSfxVolume(void) const {
                return m_sfxVolume;
            }
            /**
             * 
             * @return 
             */
            volume_type getMusicVolume(void) const {
                return m_musVolume;
            }

            /**
             * 
             */
            void stopAll(void);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool play(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool play(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool play(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool pause(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool pause(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool pause(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool resume(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool resume(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool resume(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool rewind(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool rewind(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool rewind(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool stop(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool stop(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool stop(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool isPlaying(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool isPlaying(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool isPlaying(const resource::ResourceHandle& soundHandle);

            /**
             * 
             * @param name
             * @return 
             */
            fgBool isPaused(const char *name);
            /**
             * 
             * @param name
             * @return 
             */
            fgBool isPaused(const std::string &name);
            /**
             * 
             * @param soundHandle
             * @return 
             */
            fgBool isPaused(const resource::ResourceHandle& soundHandle);

        }; // class CSfxManager

    } // namespace sfx
} // namespace fg


    #undef FG_INC_SFX_MANAGER_BLOCK
#endif /* FG_INC_SFX_MANAGER */
