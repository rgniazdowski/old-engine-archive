/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_SFX_MANAGER
    #define FG_INC_SFX_MANAGER
    #define FG_INC_SFX_MANAGER_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"
    #include "fgManagerBase.h"

    #include "fgSFXSoundResource.h"
    #include "fgSFXMusicResource.h"

    #if !defined(FG_SFX_VOLUME_TYPE) || !defined(FG_SFX_VOLUME_TYPE_DECLARED)
        #define FG_SFX_VOLUME_TYPE_DECLARED
        #if defined(FG_USING_SDL_MIXER) || defined(FG_USING_SDL) || defined(FG_USING_SDL2)
            #define FG_SFX_VOLUME_TYPE unsigned short int
        #elif defined(FG_USING_MARMALADE)
            #define FG_SFX_VOLUME_TYPE float
        #endif
    #endif

    #if !defined(FG_MANAGER_SOUND)
        #define FG_MANAGER_SOUND        0x00008000
    #endif

/**
 * 
 */
class fgSFXManager : public fgManagerBase {
public:
    typedef fgManagerBase base_type;
    typedef FG_SFX_VOLUME_TYPE volume_type;
private:
    ///
    volume_type m_sfxVolume;
    ///
    volume_type m_musVolume;
    #if defined(FG_USING_MARMALADE)
    fgBool m_mp3;
    fgBool m_pcm;
    #endif /* FG_USING_MARMALADE */
    ///
    fgManagerBase *m_pResourceMgr;

public:
    /**
     * 
     */
    fgSFXManager(fgManagerBase *pResourceMgr = NULL);
    /**
     * 
     */
    virtual ~fgSFXManager();

protected:
    /**
     * 
     * @param volume
     */
    virtual void clear(void);

    /**
     * 
     * @param nameTag
     * @return 
     */
    fgAudioBase *get(const char *nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    fgAudioBase *get(const std::string& nameTag);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgAudioBase *get(const fgResourceHandle& soundHandle);
    /**
     * 
     * @param info
     * @return 
     */
    fgAudioBase *request(const char *info);
    /**
     * 
     * @param info
     * @return 
     */
    fgAudioBase *request(const std::string& info);

public:
    /**
     * 
     * @param pResourceMgr
     */
    void setResourceManager(fgManagerBase *pResourceMgr);
    /**
     * 
     * @return 
     */
    fgManagerBase *getResourceManager(void) const {
        return m_pResourceMgr;
    }

public:
    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void);

public:
    /**
     * 
     * @param volume
     */
    void setSfxVolume(volume_type volume);
    /**
     * 
     */
    void applySfxVolume();
    /**
     * 
     * @param volume
     */
    void setMusicVolume(volume_type volume);
    /**
     * 
     */
    void applyMusicVolume();
    /**
     * 
     * @return 
     */
    volume_type getSfxVolume(void) const {
        return m_sfxVolume;
    }
    /**
     * 
     * @return 
     */
    volume_type getMusicVolume(void) const {
        return m_musVolume;
    }

    /**
     * 
     */
    void stopAll(void);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool play(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool play(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool play(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool pause(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool pause(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool pause(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool resume(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool resume(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool resume(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool rewind(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool rewind(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool rewind(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool stop(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool stop(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool stop(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool isPlaying(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool isPlaying(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool isPlaying(const fgResourceHandle& soundHandle);

    /**
     * 
     * @param name
     * @return 
     */
    fgBool isPaused(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    fgBool isPaused(const std::string &name);
    /**
     * 
     * @param soundHandle
     * @return 
     */
    fgBool isPaused(const fgResourceHandle& soundHandle);

};


    #undef FG_INC_SFX_MANAGER_BLOCK
#endif /* FG_INC_SFX_MANAGER */
