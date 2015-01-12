/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSFXMusicResource.h"
#include "Util/fgFile.h"
#include "fgLog.h"

/**
 * 
 */
fg::sfx::CMusicResource::CMusicResource() :
CResource(),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_MUSIC;
    m_baseType = base::T_MUSIC;
}

/**
 * 
 * @param path
 */
fg::sfx::CMusicResource::CMusicResource(const char *path) :
CResource(path),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_MUSIC;
    m_baseType = base::T_MUSIC;
}

/**
 * 
 * @param path
 */
fg::sfx::CMusicResource::CMusicResource(std::string& path) :
CResource(path),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = FG_RESOURCE_MUSIC;
    m_baseType = base::T_MUSIC;
}

/**
 * 
 */
void fg::sfx::CMusicResource::clear(void) {
    CResource::clear();
    m_resType = FG_RESOURCE_MUSIC;
    m_musData = NULL;
    m_rawData = NULL;
    m_isPaused = FG_FALSE;
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_baseType = base::T_MUSIC;
}

/**
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 * @return 
 */
fgBool fg::sfx::CMusicResource::create(void) {
    if(m_isReady)
        return FG_TRUE;
    if(getFilePath(m_quality).empty()) {
        FG_LOG_ERROR("SFX: Music file path is empty on create");
        // #TODO error handling / reporting
        return FG_FALSE;
    }
#if defined(FG_USING_SDL_MIXER)
    m_musData = Mix_LoadMUS(getFilePathStr(m_quality));    
    if(!m_musData) {
        FG_LOG_DEBUG("SFX: Failed to load music file: '%s'", getFilePathStr(m_quality));
        m_isReady = FG_FALSE;
    } else {
        FG_LOG_DEBUG("SFX: Successfully loaded music file: '%s'", getFilePathStr(m_quality));
        Mix_VolumeMusic(m_volume);
        m_isReady = FG_TRUE;
    }
#elif defined(FG_USING_MARMALADE) && defined(FG_USING_MARMALADE_AUDIO)
    // Check if the file exists
    // Please note that because loading/playing music with Marmalade API
    // the music file must be a RegularFile - cannot be inside the Zip #NOZIP
    if(fg::util::CRegularFile::exists(getFilePathStr(m_quality))) {
        // The file exists so it should be loadable by the s3eAudio API
        m_isReady = FG_TRUE;
    }
#endif
    return m_isReady;
}

/**
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void fg::sfx::CMusicResource::destroy(void) {
    dispose();
    m_musData = NULL;
    m_isReady = FG_FALSE;
    fg::sfx::CMusicResource::clear();
}

/**
 * Reloads any data, recreates the resource (refresh)
 * @return 
 */
fgBool fg::sfx::CMusicResource::recreate(void) {
    if(m_isReady) {
        dispose();
    }
    return create();
}

/**
 * Dispose completely of the all loaded data, free all memory
 */
void fg::sfx::CMusicResource::dispose(void) {
#if defined(FG_USING_SDL_MIXER)
    setVolume(0);
    stop();
    if(m_musData) {
        Mix_FreeMusic(m_musData);
    }
#elif defined(FG_USING_MARMALADE)
    //stop();
#endif
    m_musData = NULL;
    m_isReady = FG_FALSE;
}

/**
 * Check if resource is disposed (not loaded yet or disposed after)
 * @return 
 */
fgBool fg::sfx::CMusicResource::isDisposed(void) const {
    if(!m_isReady) {
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 */
void fg::sfx::CMusicResource::play(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(m_musData)
        Mix_PlayMusic(m_musData, 1);
#elif defined(FG_USING_MARMALADE_AUDIO)
    if(getFilePath(m_quality).empty())
        return;
    s3eAudioStatus status = (s3eAudioStatus)s3eAudioGetInt(S3E_AUDIO_STATUS);

    if(S3E_AUDIO_PAUSED == status) {
        // This approach allows for mismatch between
        // paused track and parameter idx
        s3eAudioResume();
    } else if(S3E_AUDIO_PLAYING == status) {
        s3eAudioStop();
        s3eAudioPlay(getFilePathStr(m_quality), 1);
    } else {
        s3eAudioPlay(getFilePathStr(m_quality), 1);
    }

    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_LOG_ERROR("SFX: play music error[%d]: %s (status is: %d)", err, s3eAudioGetErrorString(), status);
    }
#endif
}

/**
 * 
 */
void fg::sfx::CMusicResource::pause(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(!Mix_PausedMusic())
        Mix_PauseMusic();
    m_isPaused = FG_TRUE;
#elif defined(FG_USING_MARMALADE_AUDIO)
    if(isPlaying()) {
        s3eAudioPause();
    } else {
        m_isPaused = FG_FALSE;
        return;
    }

    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_LOG_ERROR("SFX: pause music error[%d]: %s", err, s3eAudioGetErrorString());
    } else {
        m_isPaused = FG_TRUE;
    }
    //if(s3eAudioGetInt(S3E_AUDIO_STATUS) == S3E_AUDIO_PAUSED)
    //m_isPaused = FG_TRUE;
#endif
}

/**
 * 
 */
void fg::sfx::CMusicResource::resume(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    Mix_ResumeMusic();
    if(Mix_PlayingMusic())
        m_isPlaying = FG_TRUE;
#elif defined(FG_USING_MARMALADE_AUDIO)
    s3eAudioStatus status = (s3eAudioStatus)s3eAudioGetInt(S3E_AUDIO_STATUS);

    if(S3E_AUDIO_PAUSED == status) {
        // This approach allows for mismatch between
        // paused track and parameter idx
        s3eAudioResume();
        m_isPlaying = FG_TRUE;
    } else if(S3E_AUDIO_STOPPED == status) {
        s3eAudioPlay(getFilePathStr(m_quality), 0);
        m_isPlaying = FG_TRUE;
    }
#endif
}

/**
 * 
 */
void fg::sfx::CMusicResource::rewind(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_PlayingMusic())
        Mix_RewindMusic();
#elif defined(FG_USING_MARMALADE_AUDIO)
    if(getFilePath(m_quality).empty())
        return;
    s3eAudioStop();
    s3eAudioPlay(getFilePathStr(m_quality), 0);
    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_LOG_ERROR("pauseMus error[%d]: %s", err, s3eAudioGetErrorString());
    } else {
        m_isPlaying = FG_TRUE;
        m_isPaused = FG_FALSE;
    }
#endif
}

/**
 * 
 */
void fg::sfx::CMusicResource::stop(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
#elif defined(FG_USING_MARMALADE_AUDIO) && defined(FG_USING_MARMALADE)
    s3eAudioStop();
#endif
    m_isPlaying = FG_FALSE;
    m_isPaused = FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool fg::sfx::CMusicResource::isPaused(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPaused = (fgBool)Mix_PausedMusic();
#elif defined(FG_USING_MARMALADE_AUDIO)
    s3eAudioStatus status = (s3eAudioStatus)s3eAudioGetInt(S3E_AUDIO_STATUS);
    m_isPaused = (fgBool)(status == S3E_AUDIO_PAUSED);
#endif    
    return m_isPaused;
}

/**
 * 
 * @return 
 */
fgBool fg::sfx::CMusicResource::isPlaying(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPlaying = (fgBool)Mix_PlayingMusic();
#elif defined(FG_USING_MARMALADE_AUDIO)
    m_isPlaying = s3eAudioIsPlaying();
#endif
    return m_isPlaying;
}

/**
 * 
 * @param volume
 */
void fg::sfx::CMusicResource::setVolume(FG_SFX_VOLUME_TYPE volume) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(volume <= MIX_MAX_VOLUME)
        Mix_VolumeMusic(volume);
#elif defined(FG_USING_MARMALADE) // SOUND/AUDIO
    
#endif 
    m_volume = volume;
}
