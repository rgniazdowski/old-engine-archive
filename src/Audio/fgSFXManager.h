/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_SFX_MANAGER_H_
#define _FG_SFX_MANAGER_H_

#include "../fgSingleton.h"

// This class needs total refactoring to make it somehow compatible with ResourceManager

class fgSFXManager : public fgSingleton<fgSFXManager> {
	friend class fgSingleton<fgSFXManager>;
private:
    /// Is mp3 codec supported
    bool m_mp3;

    /// Is pcm codec supported
    bool m_pcm;

public:
	/// Identifiers of SFX sounds. Every array obeys the order and indices
	enum { CLICK = 0, SPRING = 1, TURN_ON_DEVICE = 2, PLACED = 3, COMM_DEVICE = 4, DELIKATE = 5 };
	enum { SFX_COUNT = 6 };

private:
	/// Resources for SFX sounds
	static const char* m_sfxResources[ SFX_COUNT ];
    unsigned char* m_sfxBuffers[ SFX_COUNT ];
    int m_sfxBuffersSizes[ SFX_COUNT ];

public:
	/// Identifiers of MUSIC sounds. Every array obeys the order and indices
	enum { MUS_TRACK_AMBIENT1 = 0 };
	enum { MUS_COUNT = 1 };

	/// Resources for SFX sounds
	static const char* m_musResources[ MUS_COUNT ];

    /// Sfx volume 0.0-1.0f
    float m_sfxVolume;
    /// Music volume 0.0-1.0f
    float m_musVolume;

public:
    //
    // MARK: -
    // MARK: Initializers & destroyers
    //

    /**
     * Private constructor
     */
	fgSFXManager();

    /**
     * Private destructor
     */
	~fgSFXManager();

private:
    /// Load given audio file (pointed to by idx)
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

	//
	// MARK: SFX
	//

    /// Sets SFX volume
	void setSfxVolume(float volume);

    /// Apply volume to device
    void applySfxVolume();

	/// Plays the sound
	void play(int idx);

    /// Stops given sound
	void stopAll();

	//
	// MARK: Music
	//

    /// Sets music volume
	void setMusVolume(float volume);

    /// Applies the volume
    void applyMusVolume();

	/// Plays the music
	void playMus(int idx);

	/// Pauses given music
	void pauseMus(int idx);

	/// Stops given music
	void stopMus(int idx);

    /// Rewinds the music instance to the start of the sound
	void rewindMus(int idx);
};

#define FG_SFXManager fgSFXManager::getInstance()

#endif /* _AUDIO_H */

