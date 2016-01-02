/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgSFXManager.h"

#include "Resource/fgResourceManager.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

sfx::CSfxManager::~CSfxManager() {
    CSfxManager::destroy();
}
//------------------------------------------------------------------------------

sfx::CSfxManager::CSfxManager(fg::base::CManager *pResourceMgr) :
m_sfxVolume(0),
m_musVolume(0),
m_pResourceMgr(NULL) {
    setResourceManager(pResourceMgr);
    m_managerType = FG_MANAGER_SOUND;
    m_init = FG_FALSE;
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::clear() {
    m_managerType = FG_MANAGER_SOUND;
}
//------------------------------------------------------------------------------

sfx::base::CAudio *sfx::CSfxManager::get(const char* nameTag) {
    if(!nameTag)
        return NULL;
    return get(std::string(nameTag));
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

sfx::base::CAudio *sfx::CSfxManager::get(const resource::ResourceHandle& soundHandle) {
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
//------------------------------------------------------------------------------

sfx::base::CAudio *sfx::CSfxManager::request(const char* info) {
    return request(std::string(info));
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

void sfx::CSfxManager::setResourceManager(fg::base::CManager *pResourceMgr) {
    if(pResourceMgr) {
        // fgSfxManager
        if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
            m_pResourceMgr = pResourceMgr;
    }
}
//------------------------------------------------------------------------------

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
#endif
    return m_init;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::destroy(void) {
    if(!m_init)
        return FG_FALSE;
    stopAll();
#if defined(FG_USING_SDL_MIXER)
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif /* FG_USING_SDL_MIXER */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::setSfxVolume(CSfxManager::volume_type volume) {
    m_sfxVolume = volume;
#if defined(FG_USING_SDL_MIXER)
    if(m_sfxVolume > MIX_MAX_VOLUME)
        m_sfxVolume = MIX_MAX_VOLUME;
#endif /* FG_USING_SDL_MIXER */
    applySfxVolume();
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::applySfxVolume(void) {
#if defined(FG_USING_SDL_MIXER)
    Mix_Volume(-1, (int)m_sfxVolume);
#endif /* FG_USING_SDL_MIXER */
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::stopAll(void) {
#if defined(FG_USING_SDL_MIXER)
    // Stop playback on all channels
    Mix_HaltChannel(-1);
#endif /* FG_USING_SDL_MIXER */
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::setMusicVolume(CSfxManager::volume_type volume) {
    m_musVolume = volume;
#if defined(FG_USING_SDL_MIXER)
    if(m_musVolume > MIX_MAX_VOLUME)
        m_musVolume = MIX_MAX_VOLUME;
#endif /* FG_USING_SDL_MIXER */
    applyMusicVolume();
}
//------------------------------------------------------------------------------

void sfx::CSfxManager::applyMusicVolume() {
#if defined(FG_USING_SDL_MIXER)
    Mix_VolumeMusic(m_musVolume);
#endif /* FG_USING_SDL_MIXER */
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::play(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::play(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::play(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->play();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::pause(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::pause(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::pause(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->pause();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::resume(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::resume(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::resume(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->resume();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::rewind(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::rewind(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::rewind(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->rewind();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::stop(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::stop(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::stop(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->stop();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPlaying(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPlaying(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPlaying(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPlaying();
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPaused(const char* name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    return pAudio->isPaused();
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPaused(const std::string& name) {
    base::CAudio *pAudio = request(name);
    if(!pAudio)
        return FG_FALSE;
    pAudio->isPaused();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSfxManager::isPaused(const resource::ResourceHandle& soundHandle) {
    base::CAudio *pAudio = get(soundHandle);
    if(!pAudio)
        return FG_FALSE;
    pAudio->isPaused();
    return FG_TRUE;
}
//------------------------------------------------------------------------------
