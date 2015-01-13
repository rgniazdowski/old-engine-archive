/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSFXManager.h"

#include "Resource/fgResourceManager.h"
#include "fgLog.h"

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>

using namespace fg;

/**
 * 
 */
sfx::CSfxManager::~CSfxManager() {
    CSfxManager::destroy();
}

/**
 * 
 */
sfx::CSfxManager::CSfxManager(fg::base::CManager *pResourceMgr) :
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
void sfx::CSfxManager::clear() {
    m_managerType = FG_MANAGER_SOUND;
}

/**
 * 
 * @param nameTag
 * @return 
 */
sfx::base::CAudio *sfx::CSfxManager::get(const char *nameTag) {
    if(!nameTag)
        return NULL;
    return get(std::string(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
sfx::base::CAudio *sfx::CSfxManager::get(const std::string& nameTag) {
    if(!m_pResourceMgr)
        return NULL;
    resource::CResource *pResource = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pResource)
        return NULL;
    base::CAudio *pAudio = NULL;
    if(pResource->getResourceType() == resource::MUSIC) {
        sfx::CMusic *music = static_cast<sfx::CMusic*>(pResource);
        pAudio = static_cast<base::CAudio *>(music);
    } else if(pResource->getResourceType() == resource::SOUND) {
        sfx::CSound *sound = static_cast<sfx::CSound*>(pResource);
        pAudio = static_cast<base::CAudio *>(sound);
    }
    return pAudio;
}

/**
 * 
 * @param soundHandle
 * @return 
 */
sfx::base::CAudio *sfx::CSfxManager::get(const fgResourceHandle& soundHandle) {
    if(!m_pResourceMgr)
        return NULL;
    resource::CResource *pResource = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(soundHandle);
    if(!pResource)
        return NULL;
    sfx::base::CAudio *pAudio = NULL;
    if(pResource->getResourceType() == resource::MUSIC) {
        sfx::CMusic *music = static_cast<sfx::CMusic *>(pResource);
        pAudio = static_cast<base::CAudio *>(music);
    } else if(pResource->getResourceType() == resource::SOUND) {
        sfx::CSound *sound = static_cast<sfx::CSound *>(pResource);
        pAudio = static_cast<base::CAudio *>(sound);
    }
    return pAudio;
}

/**
 * 
 * @param info
 * @return 
 */
sfx::base::CAudio *sfx::CSfxManager::request(const char *info) {
    return request(std::string(info));
}

/**
 * 
 * @param info
 * @return 
 */
sfx::base::CAudio *sfx::CSfxManager::request(const std::string& info) {
    if(!m_pResourceMgr)
        return NULL;
    resource::CResource *pResource = static_cast<resource::CResourceManager *>(m_pResourceMgr)->request(info);
    if(!pResource)
        return NULL;
    sfx::base::CAudio *pAudio = NULL;
    if(pResource->getResourceType() == resource::MUSIC) {
        // Need two step casting because the AudioBase is virtual
        sfx::CMusic* music = static_cast<sfx::CMusic *>(pResource);
        pAudio = static_cast<sfx::base::CAudio *>(music);
    } else if(pResource->getResourceType() == resource::SOUND) {
        // Need two step casting because the AudioBase is virtual
        sfx::CSound *sound = static_cast<sfx::CSound *>(pResource);
        pAudio = static_cast<sfx::base::CAudio *>(sound);
    }
    return pAudio;
}

/**
 * 
 * @param pResourceMgr
 */
void sfx::CSfxManager::setResourceManager(fg::base::CManager *pResourceMgr) {
    if(pResourceMgr) {
        // fgSfxManager
        if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
            m_pResourceMgr = pResourceMgr;
    }
}

/**
 * 
 * @return 
 */
fgBool sfx::CSfxManager::initialize(void) {
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
fgBool sfx::CSfxManager::destroy(void) {
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
void sfx::CSfxManager::setSfxVolume(CSfxManager::volume_type volume) {
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
void sfx::CSfxManager::applySfxVolume(void) {
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
void sfx::CSfxManager::stopAll(void) {
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
void sfx::CSfxManager::setMusicVolume(CSfxManager::volume_type volume) {
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
void sfx::CSfxManager::applyMusicVolume() {
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
fgBool sfx::CSfxManager::play(const char *name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::play(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::play(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
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
fgBool sfx::CSfxManager::pause(const char *name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::pause(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::pause(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
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
fgBool sfx::CSfxManager::resume(const char *name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::resume(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::resume(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
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
fgBool sfx::CSfxManager::rewind(const char *name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::rewind(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::rewind(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
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
fgBool sfx::CSfxManager::stop(const char *name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::stop(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::stop(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
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
fgBool sfx::CSfxManager::isPlaying(const char *name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool sfx::CSfxManager::isPlaying(const std::string &name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param soundHandle
 * @return 
 */
fgBool sfx::CSfxManager::isPlaying(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool sfx::CSfxManager::isPaused(const char *name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPaused();
}

/**
 * 
 * @param name
 * @return 
 */
fgBool sfx::CSfxManager::isPaused(const std::string &name) {
    base::CAudio *pAudio = request(name);
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
fgBool sfx::CSfxManager::isPaused(const fgResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->isPaused();
    return FG_TRUE;
}
