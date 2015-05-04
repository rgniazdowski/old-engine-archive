/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_SFX_SOUND_RESOURCE
    #define FG_INC_SFX_SOUND_RESOURCE
    #define FG_INC_SFX_SOUND_RESOURCE_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_mixer.h>
    #elif defined(FG_USING_SDL)
        #include <SDL/SDL.h>
        #include <SDL/SDL_mixer.h>
    #elif defined(FG_USING_MARMALADE)
//#warning "TODO: Music/Audio support for Marmalade based build!"
        #include "s3eFile.h"
        #if defined(FG_USING_MARMALADE_SOUND)
            #include "s3eSound.h"
        #endif /* FG_USING_MARMALADE_SOUND */
    #endif

    #include "Resource/fgResource.h"

    #if defined(FG_USING_SDL_MIXER)
        #define FG_SOUND_RESOURCE_DEFAULT_VOLUME MIX_MAX_VOLUME
    #elif defined(FG_USING_MARMALADE)
        #define FG_SOUND_RESOURCE_DEFAULT_VOLUME 0 // #FIXME
    #else
        #define FG_SOUND_RESOURCE_DEFAULT_VOLUME 0 // #FIXME
    #endif

    #include "fgSFXAudioBase.h"
    #include "Resource/fgResourceFactoryTypes.h"
    #include <stdlib.h>

namespace fg {
    namespace resource {
        class CResource; 
    };
    namespace sfx {
        /*
         * 
         * Offset  Size  Name             Description
         * 
         * The canonical WAVE format starts with the RIFF header:
         * 
         * 0         4   ChunkID          Contains the letters "RIFF" in ASCII form
         *                                (0x52494646 big-endian form).
         * 4         4   ChunkSize        36 + SubChunk2Size, or more precisely:
         *                                4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
         *                                This is the size of the rest of the chunk 
         *                                following this number.  This is the size of the 
         *                                entire file in bytes minus 8 bytes for the
         *                                two fields not included in this count:
         *                                ChunkID and ChunkSize.
         * 8         4   Format           Contains the letters "WAVE"
         *                                (0x57415645 big-endian form).
         * 
         * The "WAVE" format consists of two subchunks: "fmt " and "data":
         * The "fmt " subchunks describes the sound data's format:
         * 
         * 12        4   Subchunk1ID      Contains the letters "fmt "
         *                                (0x666d7420 big-endian form).
         * 16        4   Subchunk1Size    16 for PCM.  This is the size of the
         *                                rest of the Subchunk which follows this number.
         * 20        2   AudioFormat      PCM = 1 (i.e. Linear quantization)
         *                                Values other than 1 indicate some 
         *                                form of compression.
         * 22        2   NumChannels      Mono = 1, Stereo = 2, etc.
         * 24        4   SampleRate       8000, 44100, etc.
         * 28        4   ByteRate         == SampleRate * NumChannels * BitsPerSample/8
         * 32        2   BlockAlign       == NumChannels * BitsPerSample/8
         *                                The number of bytes for one sample including
         *                                all channels. I wonder what happens when
         *                                this number isn't an integer?
         * 34        2   BitsPerSample    8 bits = 8, 16 bits = 16, etc.
         *           2   ExtraParamSize   if PCM, then doesn't exist
         *           X   ExtraParams      space for extra parameters
         * 
         * The "data" subchunks contains the size of the data and the actual sound:
         * 
         * 36        4   Subchunk2ID      Contains the letters "data"
         *                                (0x64617461 big-endian form).
         * 40        4   Subchunk2Size    == NumSamples * NumChannels * BitsPerSample/8
         *                                This is the number of bytes in the data.
         *                                You can also think of this as the size
         *                                of the read of the subchunk following this 
         *                                number.
         * 44        *   Data             The actual sound data.
         *         
         */

        /**
         *
         */
        struct SWAVHeader {
            ///
            char riffID[4];
            ///
            int chunkSize;
            ///
            char waveID[4];
            ///
            char subChunkFmtID[4];
            ///
            int subChunkFmtSize;
            ///
            short int audioFormat;
            ///
            short int numChannels;

            ///
            int sampleRate;
            ///
            int byteRate;
            ///
            short int blockAlign;
            ///
            short int bitsPerSample;
            /**
             * 
             */
            SWAVHeader() :
            chunkSize(0),
            subChunkFmtSize(0),
            audioFormat(0),
            numChannels(0),
            sampleRate(0),
            byteRate(0),
            blockAlign(0),
            bitsPerSample(0) {
                memset(riffID, 0, sizeof (riffID));
                memset(waveID, 0, sizeof (waveID));
                memset(subChunkFmtID, 0, sizeof (subChunkFmtID));
            }
            /**
             * 
             * @return 
             */
            static size_t size(void) {
                return sizeof (SWAVHeader);
            }
        };

        /**
         *
         */
        struct SWAVChunkHeader {
            ///
            char chunkDataID[4];
            ///
            int subChunkDataSize;
            // unsigned char * m_data;
            /**
             * 
             */
            SWAVChunkHeader() : subChunkDataSize(0) {
                memset(chunkDataID, 0, sizeof (chunkDataID));
            }
            /**
             * 
             * @return 
             */
            static size_t size(void) {
                return sizeof (SWAVChunkHeader);
            }
        };

        /**
         *
         */
        struct SSoundHeader {
            int sampleRate;
            int numChannels;
            int audioFormat;
            int bitsPerSample;
            /**
             *
             */
            SSoundHeader() :
            sampleRate(0),
            numChannels(1),
            audioFormat(0),
            bitsPerSample(0) { }
            /**
             * 
             * @return 
             */
            static size_t size(void) {
                return sizeof (SSoundHeader);
            }
        };

        /**
         * 
         */
        class CSoundResource : public fg::resource::CResource, public fg::sfx::base::CAudio {
        public:
            ///
            typedef fg::resource::CResource base_type;
            ///
            typedef CAudio base_audio_type;

        private:
    #if defined(FG_USING_SDL_MIXER)
            ///
            Mix_Chunk *m_chunkData;
    #elif defined(FG_USING_MARMALADE) // AUDIO / SOUND
            void *m_chunkData;
    #else
            void *m_chunkData;
    #endif
            ///
            unsigned char *m_soundData;
            ///
            int m_channel;
            ///
            SSoundHeader m_header;

        protected:
            /**
             * 
             * @return 
             */
            fgBool loadRawData(void);
            /**
             * 
             * @return 
             */
            fgBool loadWavData(void);

        public:
            /**
             * 
             */
            CSoundResource();
            /**
             * 
             * @param path
             */
            CSoundResource(const char *path);
            /**
             * 
             * @param path
             */
            CSoundResource(const std::string& path);
            /**
             * 
             */
            virtual ~CSoundResource() {
                CSoundResource::destroy();
            }

            /**
             * 
             * @return
             */
            FG_RESOURCE_FACTORY_CREATE_FUNCTION(CSoundResource);


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

            /**
             * 
             * @return 
             */
            int getCurrentChannel(void);
        };
        ///
        typedef CSoundResource CSound;
    };
};

    #undef FG_INC_SFX_SOUND_RESOURCE_BLOCK
#endif /* FG_INC_SFX_SOUND_RESOURCE */
