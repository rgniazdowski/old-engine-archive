/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_SFX_MUSIC_RESOURCE
    #define FG_INC_SFX_MUSIC_RESOURCE
    #define FG_INC_SFX_MUSIC_RESOURCE_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_mixer.h>
    #elif defined(FG_USING_SDL)
        #include <SDL/SDL.h>
        #include <SDL/SDL_mixer.h>
    #elif defined(FG_USING_MARMALADE)
//#error "TODO: Music/Audio support for Marmalade based build!"
//      #include "s3eFile.h"
        #ifdef FG_USING_MARMALADE_AUDIO
            #include "s3eAudio.h" // s3eAudio can play music files
        #endif /* FG_USING_MARMALADE_AUDIO */
    #endif

    #include "Resource/fgResource.h"

    #if defined(FG_USING_SDL_MIXER)
        #define FG_MUSIC_RESOURCE_DEFAULT_VOLUME MIX_MAX_VOLUME
    #elif defined(FG_USING_MARMALADE)
        #define FG_MUSIC_RESOURCE_DEFAULT_VOLUME 0 // #FIXME
    #endif

    #include "fgSFXAudioBase.h"
    #include "Resource/fgResourceFactoryTypes.h"

namespace fg {
    namespace resource {
        class CResource;
    };
    
    namespace sfx {

        /**
         * 
         */
        class CMusicResource : public fg::resource::CResource, public fg::sfx::base::CAudio {
        public:
            ///
            typedef fg::resource::CResource base_type;
            ///
            typedef CAudio base_audio_type;

        private:
    #if defined(FG_USING_SDL_MIXER)
            ///
            Mix_Music *m_musData;
    #elif defined(FG_USING_MARMALADE) // AUDIO / SOUND
            void *m_musData;
    #else
            void *m_musData;
    #endif
            ///
            unsigned char *m_rawData;

        public:
            /**
             * 
             */
            CMusicResource();
            /**
             * 
             * @param path
             */
            CMusicResource(const char *path);
            /**
             * 
             * @param path
             */
            CMusicResource(std::string& path);
            /**
             * 
             */
            virtual ~CMusicResource() {
                CMusicResource::destroy();
            }

            /**
             * 
             * @return 
             */
            FG_RESOURCE_FACTORY_CREATE_FUNCTION(CMusicResource)

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:

            /**
             * Create function loads/interprets data from file in ROM and place it in RAM memory.
             * @return 
             */
            virtual fgBool create(void);
            /**
             * Destroy all loaded data including additional metadata (called with destructor)
             */
            virtual void destroy(void);
            /**
             * Reloads any data, recreates the resource (refresh)
             * @return 
             */
            virtual fgBool recreate(void);
            /**
             * Dispose completely of the all loaded data, free all memory
             */
            virtual void dispose(void);
            /**
             * Check if resource is disposed (not loaded yet or disposed after)
             * @return 
             */
            virtual fgBool isDisposed(void) const;

        public:
            /**
             * 
             */
            virtual void play(void);
            /**
             * 
             */
            virtual void pause(void);
            /**
             * 
             */
            virtual void resume(void);
            /**
             * 
             */
            virtual void rewind(void);
            /**
             * 
             */
            virtual void stop(void);
            /**
             * 
             * @return 
             */
            virtual fgBool isPaused(void);
            /**
             * 
             * @return 
             */
            virtual fgBool isPlaying(void);

        public:
            /**
             * 
             * @param volume
             */
            void setVolume(FG_SFX_VOLUME_TYPE volume);
        };
        
        ///
        typedef CMusicResource CMusic;
    };
};

    #undef FG_INC_SFX_MUSIC_RESOURCE_BLOCK
#endif /* FG_INC_SFX_MUSIC_RESOURCE */
