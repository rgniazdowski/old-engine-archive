/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgSFXMusicResource.h"
#include "Util/fgFile.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

sfx::CMusicResource::CMusicResource() :
CResource(),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::MUSIC;
    m_baseType = base::T_MUSIC;
}
//------------------------------------------------------------------------------

sfx::CMusicResource::CMusicResource(const char *path) :
CResource(path),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::MUSIC;
    m_baseType = base::T_MUSIC;
}
//------------------------------------------------------------------------------

sfx::CMusicResource::CMusicResource(const std::string& path) :
CResource(path),
CAudio(base::T_MUSIC),
m_musData(NULL),
m_rawData(NULL) {
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::MUSIC;
    m_baseType = base::T_MUSIC;
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::clear(void) {
    base_type::clear();
    m_resType = resource::MUSIC;
    m_musData = NULL;
    m_rawData = NULL;
    m_isPaused = FG_FALSE;
    m_volume = FG_MUSIC_RESOURCE_DEFAULT_VOLUME;
    m_baseType = base::T_MUSIC;
}
//------------------------------------------------------------------------------

fgBool sfx::CMusicResource::create(void) {
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
#endif
    return m_isReady;
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::destroy(void) {
    dispose();
    m_musData = NULL;
    m_isReady = FG_FALSE;
    sfx::CMusicResource::clear();
}
//------------------------------------------------------------------------------

fgBool sfx::CMusicResource::recreate(void) {
    if(m_isReady) {
        dispose();
    }
    return create();
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::dispose(void) {
#if defined(FG_USING_SDL_MIXER)
    setVolume(0);
    stop();
    if(m_musData) {
        Mix_FreeMusic(m_musData);
    }
#endif
    m_musData = NULL;
    m_isReady = FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool sfx::CMusicResource::isDisposed(void) const {
    if(!m_isReady) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::play(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(m_musData)
        Mix_PlayMusic(m_musData, 1);
#endif
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::pause(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(!Mix_PausedMusic())
        Mix_PauseMusic();
    m_isPaused = FG_TRUE;
#endif
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::resume(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    Mix_ResumeMusic();
    if(Mix_PlayingMusic())
        m_isPlaying = FG_TRUE;
#endif
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::rewind(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_PlayingMusic())
        Mix_RewindMusic();
#endif
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::stop(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
#endif
    m_isPlaying = FG_FALSE;
    m_isPaused = FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool sfx::CMusicResource::isPaused(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPaused = (fgBool)Mix_PausedMusic();
#endif    
    return m_isPaused;
}
//------------------------------------------------------------------------------

fgBool sfx::CMusicResource::isPlaying(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPlaying = (fgBool)Mix_PlayingMusic();
#endif
    return m_isPlaying;
}
//------------------------------------------------------------------------------

void sfx::CMusicResource::setVolume(FG_SFX_VOLUME_TYPE volume) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(volume <= MIX_MAX_VOLUME)
        Mix_VolumeMusic(volume);
#endif 
    m_volume = volume;
}
//------------------------------------------------------------------------------
