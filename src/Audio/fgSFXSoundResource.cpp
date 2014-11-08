/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSFXSoundResource.h"
#include "fgLog.h"
#include "Util/fgStrings.h"

/**
 * 
 */
fgSoundResource::fgSoundResource() :
fgResource(),
fgAudioBase(),
m_chunkData(NULL),
m_rawData(NULL),
m_channel(0) {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_SOUND;
}

/**
 * 
 * @param path
 */
fgSoundResource::fgSoundResource(const char *path) :
fgResource(path),
fgAudioBase(),
m_chunkData(NULL),
m_rawData(NULL),
m_channel(0) {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_SOUND;
}

/**
 * 
 * @param path
 */
fgSoundResource::fgSoundResource(std::string& path) :
fgResource(path),
fgAudioBase(),
m_chunkData(NULL),
m_rawData(NULL),
m_channel(0) {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_SOUND;
}

/**
 * 
 */
void fgSoundResource::clear(void) {
    fgResource::clear();
    m_resType = FG_RESOURCE_SOUND;
    m_chunkData = NULL;
    m_rawData = NULL;
    m_isPaused = FG_FALSE;
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_channel = 0;
}

fgBool fgSoundResource::loadRawData(void) {
    if(getFilePath(m_quality).empty())
        return FG_FALSE;
#if defined(FG_USING_MARMALADE_SOUND)
    m_rawData = NULL;
    m_size = 0;
    // fgFile? anyone?
    s3eFile* fileHandle = s3eFileOpen(getFilePathStr(m_quality), "rb");
    if(NULL == fileHandle) {
        FG_LOG_ERROR("SFX: Unable to open audio file '%s', error code: %d", getFilePathStr(m_quality), s3eFileGetError());
        return false;
    }

    int fileSize = s3eFileGetSize(fileHandle);
    unsigned char* buffer = new unsigned char[fileSize + 1];
    buffer[fileSize] = '\0';
    memset(buffer, 0, fileSize);

    int objectsRead = s3eFileRead(buffer, fileSize, 1, fileHandle);
    s3eFileClose(fileHandle);

    if(objectsRead != 1) {
        FG_LOG_ERROR("SFX: Should read %d bytes of an sound file, read %d instead!", fileSize, objectsRead * fileSize);
        delete [] buffer;
        return false;
    }

    FG_LOG_DEBUG("SFX: Read %d bytes of '%s', buffer = %p", fileSize, getFilePathStr(m_quality), buffer);

    m_rawData = buffer;
    m_size = fileSize;
#endif
    return FG_TRUE;
}

/**
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 * @return 
 */
fgBool fgSoundResource::create(void) {
    if(m_isReady)
        return FG_TRUE;
    if(getFilePath(m_quality).empty()) {
        FG_LOG_ERROR("SFX: Sound/chunk file path is empty on create");
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    const char *path = getFilePathStr(m_quality);

#if defined(FG_USING_SDL_MIXER)
    if(!fgStrings::endsWith(path, ".wav", FG_FALSE)) {
        FG_LOG_ERROR("SFX: Sound/chunk file extension is not valid (.WAV): '%s'", path);
        return FG_FALSE;
    }
    m_chunkData = Mix_LoadWAV(path);
    if(!m_chunkData) {
        FG_LOG_DEBUG("SFX: Failed to load sound/chunk file: '%s'", path);
        m_isReady = FG_FALSE;
    } else {
        FG_LOG_DEBUG("SFX: Successfully loaded sound/chunk file: '%s'", path);
        Mix_VolumeChunk(m_chunkData, m_volume);
        m_isReady = FG_TRUE;
    }
#elif defined(FG_USING_MARMALADE_SOUND)
    // This only support .raw files for now...
    if(loadRawData()) {
        m_isReady = FG_TRUE;
    }
#else
#endif
    return m_isReady;
}

/**
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void fgSoundResource::destroy(void) {
    dispose();
    m_chunkData = NULL;
    m_isReady = FG_FALSE;
    fgSoundResource::clear();
}

/**
 * Reloads any data, recreates the resource (refresh)
 * @return 
 */
fgBool fgSoundResource::recreate(void) {
    if(m_isReady) {
        dispose();
    }
    return create();
}

/**
 * Dispose completely of the all loaded data, free all memory
 */
void fgSoundResource::dispose(void) {
#if defined(FG_USING_SDL_MIXER)
    setVolume(0);
    stop();
    if(m_chunkData) {
        Mix_FreeChunk(m_chunkData);
    }
#elif defined(FG_USING_MARMALADE_SOUND)
#endif
    m_chunkData = NULL;
    m_isReady = FG_FALSE;
    m_channel = 0;
}

/**
 * Check if resource is disposed (not loaded yet or disposed after)
 * @return 
 */
fgBool fgSoundResource::isDisposed(void) const {
    if(!m_chunkData || !m_isReady) {
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 */
void fgSoundResource::play(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(m_chunkData) {
        //int Mix_PlayChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ticks);
        m_channel = Mix_PlayChannel(-1, m_chunkData, 0);
        m_isPlaying = FG_TRUE;
        m_isPaused = FG_FALSE;
    }
#elif defined(FG_USING_MARMALADE_SOUND)
    if(m_rawData) {
        m_channel = s3eSoundGetFreeChannel();
        s3eSoundChannelPlay(channel, (int16*)m_rawData, m_size / 2, 1, 0);
        // Check for error
        s3eSoundError err = s3eSoundGetError();
        if(err != S3E_SOUND_ERR_NONE) {
            FG_LOG_ERROR("SFX: name[%s] on channel[%d] error[%d]: %s", m_nameTag.c_str(), m_channel, err, s3eSoundGetErrorString());
        } else {
            m_isPlaying = FG_TRUE;
            m_isPaused = FG_FALSE;
        }
    }
#endif
}

/**
 * 
 */
void fgSoundResource::pause(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(!Mix_Paused(m_channel) && isPlaying()) {
        Mix_Pause(m_channel);
    }
    m_isPaused = FG_TRUE;
#elif defined(FG_USING_MARMALADE_SOUND)
    // 	s3eSoundChannelGetInt (int channel, s3eSoundChannelProperty property)
    if(isPlaying() && !isPaused()) {
        s3eSoundChannelPause(m_channel);
    }
    m_isPaused = FG_TRUE;
#endif
}

/**
 * 
 */
void fgSoundResource::resume(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(isPaused() && Mix_Playing(m_channel))
        Mix_Resume(m_channel);
    if(Mix_Playing(m_channel))
        m_isPlaying = FG_TRUE;
#elif defined(FG_USING_MARMALADE_SOUND)
    if(isPaused()) {
        s3eSoundChannelResume(m_channel);
        // Check for error
        s3eSoundError err = s3eSoundGetError();
        if(err != S3E_SOUND_ERR_NONE) {
            FG_LOG_ERROR("SFX: name[%s] on channel[%d] error[%d]: %s", m_nameTag.c_str(), m_channel, err, s3eSoundGetErrorString());
        }
    }
#endif
}

/**
 * 
 */
void fgSoundResource::rewind(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    stop();
    play();
#elif defined(FG_USING_MARMALADE_SOUND)
    stop();
    play();
#endif
}

/**
 * 
 */
void fgSoundResource::stop(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_Playing(m_channel))
        Mix_HaltChannel(m_channel);
    m_channel = 0;
    m_isPlaying = FG_FALSE;
    m_isPaused = FG_FALSE;
#elif defined(FG_USING_MARMALADE_SOUND)
    if(isPlaying() && !isPaused()) {
        s3eSoundChannelStop(m_channel);
        m_isPlaying = FG_FALSE;
        m_isPaused = FG_FALSE;
    }
#endif
}

/**
 * 
 * @return 
 */
fgBool fgSoundResource::isPaused(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPaused = (fgBool)Mix_Paused(m_channel);
#elif defined(FG_USING_MARMALADE_SOUND)
    //s3eSoundChannelGetInt (int channel, s3eSoundChannelProperty property)
    m_isPaused = (fgBool)s3eSoundChannelGetInt(m_channel, S3E_CHANNEL_PAUSED);
#endif    
    return m_isPaused;
}

/**
 * 
 * @return 
 */
fgBool fgSoundResource::isPlaying(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPlaying = (fgBool)Mix_Playing(m_channel);
#elif defined(FG_USING_MARMALADE_SOUND)
    m_isPlaying = (fgBool)s3eSoundChannelGetInt(m_channel, S3E_CHANNEL_STATUS);
#endif
    return m_isPlaying;
}

/**
 * 
 * @param volume
 */
void fgSoundResource::setVolume(unsigned short int volume) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(volume <= MIX_MAX_VOLUME) {
        if(m_chunkData)
            Mix_VolumeChunk(m_chunkData, volume);
        //if(isPlaying())
        //    Mix_Volume(m_channel, volume); // ? ? 
    }
#elif defined(FG_USING_MARMALADE_SOUND) // SOUND/AUDIO
    s3eResult result = s3eSoundSetInt(m_channel, S3E_CHANNEL_VOLUME, int(m_sfxVolume * S3E_SOUND_MAX_VOLUME * 0.9f));
    if(S3E_RESULT_SUCCESS != result) {
        FG_LOG_ERROR("Error when setting the SFX[%s] volume: %d", getNameStr(), result);
    }
#endif 
    m_volume = volume;
}

/**
 * 
 * @return 
 */
int fgSoundResource::getCurrentChannel(void) {
    if(!m_isReady) {
        m_channel = 0;
    } else if(!isPlaying() && !isPaused()) {
        m_channel = 0;
    }
    return m_channel;
}
