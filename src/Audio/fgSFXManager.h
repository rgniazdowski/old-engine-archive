/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_SFX_MANAGER_H_
    #define _FG_SFX_MANAGER_H_

    #include "fgSingleton.h"
    #include "fgTypes.h"

// This class needs total refactoring to make it somehow compatible with ResourceManager

class fgSFXManager : public fgSingleton<fgSFXManager> {
    friend class fgSingleton<fgSFXManager>;
private:
    fgBool m_mp3;
    fgBool m_pcm;

public:
    /// Identifiers of SFX sounds. Every array obeys the order and indices

    enum {
        CLICK = 0, SPRING = 1, TURN_ON_DEVICE = 2, PLACED = 3, COMM_DEVICE = 4, DELIKATE = 5
    };

    enum {
        SFX_COUNT = 6
    };

private:
    /// Resources for SFX sounds
    static const char* m_sfxResources[ SFX_COUNT ];
    unsigned char* m_sfxBuffers[ SFX_COUNT ];
    int m_sfxBuffersSizes[ SFX_COUNT ];

public:
    /// Identifiers of MUSIC sounds. Every array obeys the order and indices

    enum {
        MUS_TRACK_AMBIENT1 = 0
    };

    enum {
        MUS_COUNT = 1
    };

    /// Resources for SFX sounds
    static const char* m_musResources[ MUS_COUNT ];

    float m_sfxVolume;
    float m_musVolume;

protected:
    fgSFXManager();
    ~fgSFXManager();

private:
    bool loadAudioFile(const char* name, unsigned char* & out_buffer, int & out_size);

public:
    /**
     * Load all SFX files
     */
    bool loadSfxFiles();

    /**
     * Load all MUS files
     */
    bool loadMusFiles();

    void setSfxVolume(float volume);

    void applySfxVolume();

    void play(int idx);

    void stopAll();

    void setMusVolume(float volume);

    void applyMusVolume();

    void playMus(int idx);

    void pauseMus(int idx);

    void stopMus(int idx);

    void rewindMus(int idx);
};

    #define FG_SFXManager fgSFXManager::getInstance()

#endif /* _AUDIO_H */

