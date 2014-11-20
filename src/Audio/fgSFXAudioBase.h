/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgSFXAudioBase.h
 * Author: vigilant
 *
 * Created on November 8, 2014, 1:37 PM
 */

#ifndef FG_INC_SFX_AUDIO_BASE
    #define FG_INC_SFX_AUDIO_BASE
    #define FG_INC_SFX_AUDIO_BASE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if !defined(FG_SFX_VOLUME_TYPE) || !defined(FG_SFX_VOLUME_TYPE_DECLARED)
        #define FG_SFX_VOLUME_TYPE_DECLARED
        #if defined(FG_USING_SDL_MIXER) || defined(FG_USING_SDL) || defined(FG_USING_SDL2)
            #define FG_SFX_VOLUME_TYPE unsigned short int
        #elif defined(FG_USING_MARMALADE)
            #define FG_SFX_VOLUME_TYPE float
        #endif
    #endif

/**
 * 
 */
class fgAudioBase {
public:
    /**
     * 
     */
    fgAudioBase() : m_volume(0),
    m_isPaused(FG_FALSE),
    m_isPlaying(FG_FALSE) { }
    /**
     * 
     */
    virtual ~fgAudioBase() { }
protected:
    ///
    FG_SFX_VOLUME_TYPE m_volume;
    ///
    fgBool m_isPaused;
    ///
    fgBool m_isPlaying;

public:
    virtual void play(void) = 0;
    /**
     * 
     */
    virtual void pause(void) = 0;
    /**
     * 
     */
    virtual void resume(void) = 0;
    /**
     * 
     */
    virtual void rewind(void) = 0;
    /**
     * 
     */
    virtual void stop(void) = 0;
    /**
     * 
     */
    virtual void halt(void) {
        stop();
    };
    /**
     * 
     * @return 
     */
    virtual fgBool isPaused(void) = 0;
    /**
     * 
     * @return 
     */
    virtual fgBool isPlaying(void) = 0;

public:
    /**
     * 
     * @param volume
     */
    virtual void setVolume(FG_SFX_VOLUME_TYPE volume) = 0;
    /**
     * 
     * @return 
     */
    FG_SFX_VOLUME_TYPE getVolume(void) const {
        return m_volume;
    }
};

    #undef FG_INC_SFX_AUDIO_BASE_BLOCK
#endif	/* FG_INC_SFX_AUDIO_BASE */

