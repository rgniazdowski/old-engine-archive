/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_SFX_SOUND_RESOURCE_H_
    #define _FG_SFX_SOUND_RESOURCE_H_
    #define _FG_SFX_SOUND_RESOURCE_H_BLOCK_

    #include "fgBuildConfig.h"

    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_mixer.h>
    #elif defined(FG_USING_SDL)
        #include <SDL/SDL.h>
        #include <SDL/SDL_mixer.h>
    #elif defined(FG_USING_MARMALADE)
        #warning "TODO: Music/Audio support for Marmalade based build!"
        #include "s3eFile.h"
        #ifdef FG_USING_MARMALADE_SOUND
            #include "s3eSound.h"
        #endif /* FG_USING_MARMALADE_SOUND */
    #endif

    #include "Resource/fgResource.h"

    #if defined(FG_USING_SDL_MIXER)
        #define FG_SOUND_RESOURCE_DEFAULT_VOLUME MIX_MAX_VOLUME
    #elif defined(FG_USING_MARMALADE)
        #define FG_SOUND_RESOURCE_DEFAULT_VOLUME 0 // #FIXME
    #endif

    #include "fgSFXAudioBase.h"
    #include "Resource/fgResourceFactoryTypes.h"

/**
 * 
 */
class fgSoundResource : public fgResource, public fgAudioBase {
public:
    typedef fgResource base_type;
    typedef fgAudioBase base_audio_type;
private:
    #if defined(FG_USING_SDL_MIXER)
    ///
    Mix_Chunk *m_chunkData;
    #elif defined(FG_USING_MARMALADE) // AUDIO / SOUND
    #else
    void *m_chunkData;
    #endif
    ///
    unsigned char *m_rawData;
    ///
    int m_channel;

protected:
    fgBool loadRawData(void);

public:
    /**
     * 
     */
    fgSoundResource();
    /**
     * 
     * @param path
     */
    fgSoundResource(const char *path);
    /**
     * 
     * @param path
     */
    fgSoundResource(std::string& path);
    /**
     * 
     */
    virtual ~fgSoundResource() {
        fgSoundResource::destroy();
    }

    FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgSoundResource);


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

    #undef _FG_SFX_SOUND_RESOURCE_H_BLOCK_
#endif /* _FG_SFX_SOUND_RESOURCE_H_ */
