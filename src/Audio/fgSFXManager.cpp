/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSFXManager.h"

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>

#include "fgLog.h"
#include "Resource/fgResourceManager.h"

/**
 * 
 */
fgSFXManager::~fgSFXManager() {
    fgSFXManager::destroy();
}

/**
 * 
 */
fgSFXManager::fgSFXManager(fg::base::Manager *pResourceMgr) :
m_sfxVolume(0),
m_musVolume(0),
m_pResourceMgr(NULL) {
    setResourceManager(pResourceMgr);
    m_managerType = FG_MANAGER_SOUND;
    m_init = FG_FALSE;
}

/**
 * 
 */
void fgSFXManager::clear() {
    m_managerType = FG_MANAGER_SOUND;
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgAudioBase *fgSFXManager::get(const char *nameTag) {
    if(!nameTag)
        return NULL;
    return get(std::string(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgAudioBase *fgSFXManager::get(const std::string& nameTag) {
    if(!m_pResourceMgr)
        return NULL;
    fgResource *pResource = static_cast<fgResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pResource)
        return NULL;
    fgAudioBase *pAudio = NULL;
    if(pResource->getResourceType() == FG_RESOURCE_MUSIC) {
        fgMusicResource *music = static_cast<fgMusicResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(music);
    } else if(pResource->getResourceType() == FG_RESOURCE_SOUND) {
        fgSoundResource *sound = static_cast<fgSoundResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(sound);
    }    
    return pAudio;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgAudioBase *fgSFXManager::get(const fgResourceHandle& soundHandle) {
    if(!m_pResourceMgr)
        return NULL;
    fgResource *pResource = static_cast<fgResourceManager *>(m_pResourceMgr)->get(soundHandle);
    if(!pResource)
        return NULL;
    fgAudioBase *pAudio = NULL;
    if(pResource->getResourceType() == FG_RESOURCE_MUSIC) {
        fgMusicResource *music = static_cast<fgMusicResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(music);
    } else if(pResource->getResourceType() == FG_RESOURCE_SOUND) {
        fgSoundResource *sound = static_cast<fgSoundResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(sound);
    }
    return pAudio;
}

/**
 * 
 * @param info
 * @return 
 */
fgAudioBase *fgSFXManager::request(const char *info) {
    return request(std::string(info));
}

/**
 * 
 * @param info
 * @return 
 */
fgAudioBase *fgSFXManager::request(const std::string& info) {
    if(!m_pResourceMgr)
        return NULL;
    fgResource *pResource = static_cast<fgResourceManager *>(m_pResourceMgr)->request(info);
    if(!pResource)
        return NULL;
    fgAudioBase *pAudio = NULL;
    if(pResource->getResourceType() == FG_RESOURCE_MUSIC) {
        fgMusicResource *music = static_cast<fgMusicResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(music);
    } else if(pResource->getResourceType() == FG_RESOURCE_SOUND) {
        fgSoundResource *sound = static_cast<fgSoundResource *>(pResource);
        pAudio = static_cast<fgAudioBase *>(sound);
    }
    return pAudio;
}

/**
 * 
 * @param pResourceMgr
 */
void fgSFXManager::setResourceManager(fg::base::Manager *pResourceMgr) {
    if(pResourceMgr) {
        if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
            m_pResourceMgr = pResourceMgr;
    }
}

/**
 * 
 * @return 
 */
fgBool fgSFXManager::initialize(void) {
    if(m_init)
        return FG_TRUE;
    m_managerType = FG_MANAGER_SOUND;
#if defined(FG_USING_SDL_MIXER)
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        FG_LOG_ERROR("SFX: SDL Init audio failed: '%s'", SDL_GetError());
        m_init = FG_FALSE;
        return m_init;
    }
    int mixflags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;
    Mix_Init(mixflags);
    // parameters settings
    int frequency = 22050;
    int channels = 2;
    if(Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, 4096) != 0) {
        FG_LOG_ERROR("SFX: Mix_OpenAudio: '%s'", Mix_GetError());
        m_init = FG_FALSE;
        return m_init;
    } else {
        FG_LOG_DEBUG("SFX: Successfully initialized audio: frequency[%d], channels[%d]", frequency, channels);
        m_init = FG_TRUE;
    }
    // #FIXME - check for errors
#elif defined(FG_USING_MARMALADE_AUDIO)
    m_sfxVolume = 0.5f;
    m_musVolume = 0.5f;

    m_mp3 = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3);
    if(m_mp3) {
        FG_LOG_DEBUG("SFX: MP3 codec supported");
    } else {
        FG_LOG_ERROR("SFX: No MP3 support!");
    }
    m_pcm = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_PCM);
    if(m_pcm) {
        FG_LOG_DEBUG("SFX: PCM codec supported");
    } else {
        FG_LOG_ERROR("SFX: No PCM support!");
    }
    if(m_mp3 && m_pcm) {
        m_init = FG_TRUE;
    } else {
        FG_LOG_ERROR("SFX: Failed to initialize Sound Manager");
    }
#endif
    return m_init;
}

/**
 * 
 * @return 
 */
fgBool fgSFXManager::destroy(void) {
    if(!m_init)
        return FG_FALSE;
    stopAll();
#if defined(FG_USING_SDL_MIXER)
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
#elif defined(FG_USING_MARMALADE_AUDIO)
    s3eAudioStop();
#endif /* FG_USING_MARMALADE_AUDIO */
    return FG_TRUE;
}

/**
 * 
 * @param volume
 */
void fgSFXManager::setSfxVolume(fgSFXManager::volume_type volume) {
    m_sfxVolume = volume;
#if defined(FG_USING_MARMALADE)
    if(m_sfxVolume < 0.0f)
        m_sfxVolume = 0.01f;
    if(m_sfxVolume > 1.0f)
        m_sfxVolume = 1.0f;
#elif defined(FG_USING_SDL_MIXER)
    if(m_sfxVolume > MIX_MAX_VOLUME)
        m_sfxVolume = MIX_MAX_VOLUME;
#endif

    applySfxVolume();
}

/**
 * 
 */
void fgSFXManager::applySfxVolume(void) {
#if defined(FG_USING_MARMALADE_SOUND)
    s3eResult result = s3eSoundSetInt(S3E_SOUND_VOLUME, int(m_sfxVolume * S3E_SOUND_MAX_VOLUME * 0.9f));
    if(S3E_RESULT_SUCCESS != result) {
        FG_LOG_ERROR("Error when setting the sfx volume: %d", result);
    }
#elif defined(FG_USING_SDL_MIXER)
    Mix_Volume(-1, (int)m_sfxVolume);
#endif /* FG_USING_MARMALADE_SOUND */
}

/**
 * 
 */
void fgSFXManager::stopAll(void) {
#if defined(FG_USING_MARMALADE_SOUND)
    s3eSoundStopAllChannels();
#elif defined(FG_USING_SDL_MIXER)
    // Stop playback on all channels
    Mix_HaltChannel(-1);
#endif // FG_USING_MARMALADE_SOUND */
}

/**
 * 
 * @param volume
 */
void fgSFXManager::setMusicVolume(fgSFXManager::volume_type volume) {
    m_musVolume = volume;
#if defined(FG_USING_MARMALADE)
    if(m_musVolume < 0.0f)
        m_musVolume = 0.01f;
    if(m_musVolume > 1.0f)
        m_musVolume = 1.0f;
#elif defined(FG_USING_SDL_MIXER)
    if(m_musVolume > MIX_MAX_VOLUME)
        m_musVolume = MIX_MAX_VOLUME;
#endif
    applyMusicVolume();
}

/**
 * 
 */
void fgSFXManager::applyMusicVolume() {
#if defined(FG_USING_MARMALADE_AUDIO)
    s3eResult result = s3eAudioSetInt(S3E_AUDIO_VOLUME, int(m_musVolume * S3E_AUDIO_MAX_VOLUME * 0.85f));
#elif defined(FG_USING_SDL_MIXER)
    Mix_VolumeMusic(m_musVolume);
#endif /* FG_USING_MARMALADE_AUDIO */
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::play(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::play(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::play(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::pause(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::pause(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::pause(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::resume(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::resume(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::resume(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::rewind(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::rewind(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::rewind(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::stop(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::stop(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::stop(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::isPlaying(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::isPlaying(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::isPlaying(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::isPaused(const char *name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPaused();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool fgSFXManager::isPaused(const std::string &name) {
    fgAudioBase *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->isPaused();
    return FG_TRUE;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool fgSFXManager::isPaused(const fgResourceHandle& soundHandle) {
    fgAudioBase *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->isPaused();
    return FG_TRUE;
}
