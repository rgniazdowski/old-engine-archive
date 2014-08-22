/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgSFXManager.h"

#include <cstring>
#include "s3eFile.h"
#include "s3eSound.h"
#include "s3eAudio.h"

#include "../fgCommon.h"
#include "../fgLog.h"
#include "../Hardware/fgDeviceQuery.h"

#define SNDDIR "sound/"

// #FIXME

const char* fgSFXManager::m_sfxResources[ fgSFXManager::SFX_COUNT ] = { SNDDIR"c.raw", SNDDIR"s.raw", SNDDIR"tod.raw", SNDDIR"p.raw", SNDDIR"m.raw", SNDDIR"d.raw" };
const char* fgSFXManager::m_musResources[ fgSFXManager::MUS_COUNT ] = { SNDDIR"m1.mp3" };

template <>
bool fgSingleton<fgSFXManager>::instanceFlag = false;

template <>
fgSFXManager *fgSingleton<fgSFXManager>::instance = NULL;

/**
 * Private destructor
 */
fgSFXManager::~fgSFXManager() {

    stopAll();
    s3eAudioStop();

	for(int i = 0; i < SFX_COUNT; i++) {
        if(m_sfxBuffers[i] && m_sfxBuffersSizes[i]) {
            delete [] m_sfxBuffers[i];
        }
    }
}

/**
 * Private constructor
 */
fgSFXManager::fgSFXManager() {
    m_sfxVolume = 0.5f;
    m_musVolume = 0.5f;

    memset(m_sfxBuffers, 0, sizeof(m_sfxBuffers));
    memset(m_sfxBuffersSizes, 0, sizeof(m_sfxBuffersSizes));
	m_mp3 = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3);
    if(m_mp3) {
        FG_WriteLog("MP3 codec supported");
    } else {
        FG_ErrorLog("No MP3 support!");
    }
	m_pcm = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_PCM);
    if(m_pcm) {
        FG_WriteLog("PCM codec supported");
    } else {
        FG_ErrorLog("No PCM support!");
    }
}

/**
  * Loads given file into memory
  */
bool fgSFXManager::loadAudioFile(const char* name, unsigned char* & out_buffer, int & out_size) {

    out_buffer = NULL;
    out_size = 0;

    s3eFile* fileHandle = s3eFileOpen(name, "rb");
    if(NULL == fileHandle) {
        FG_ErrorLog("Unable to open audio file '%s', error code: %d", name, s3eFileGetError());
        return false;
    }

    int fileSize = s3eFileGetSize(fileHandle);
    unsigned char* buffer = new unsigned char[fileSize+1];
    buffer[fileSize] = '\0';
    memset(buffer, 0, fileSize);

    int objectsRead = s3eFileRead(buffer, fileSize, 1, fileHandle);
    s3eFileClose(fileHandle);

    if ( objectsRead != 1 ) {
        FG_ErrorLog("Should read %d bytes of an sound file, read %d instead!", fileSize, objectsRead * fileSize);
        delete [] buffer;
        return false;
    }

    FG_WriteLog("Read %d bytes of '%s', buffer = %p", fileSize, name, buffer);

    out_buffer = buffer;
    out_size = fileSize;
	return true;
}

bool fgSFXManager::loadSfxFiles()
{
	for(int i = 0; i < SFX_COUNT; i++) {
		if( false == loadAudioFile( m_sfxResources[i], m_sfxBuffers[i], m_sfxBuffersSizes[i]) ) {
			return false;
		}
	}
	return true;
}

void fgSFXManager::setSfxVolume(float volume) {
	m_sfxVolume = volume;
    if(m_sfxVolume < 0.0f)
        m_sfxVolume = 0.01f;
    if(m_sfxVolume > 1.0f)
        m_sfxVolume = 1.0f;

    applySfxVolume();
}

void fgSFXManager::applySfxVolume() {
    s3eResult result = s3eSoundSetInt(S3E_SOUND_VOLUME, int(m_sfxVolume * S3E_SOUND_MAX_VOLUME * 0.9f));
    if(S3E_RESULT_SUCCESS != result) {
        FG_ErrorLog("Error when setting the sfx volume: %d", result );
    }
}

void fgSFXManager::play(int idx) {
    int channel = s3eSoundGetFreeChannel();
    s3eSoundChannelPlay(channel, (int16*) m_sfxBuffers[idx], m_sfxBuffersSizes[idx] / 2, 1, 0);
    // Check for error
    s3eSoundError err = s3eSoundGetError();
    if(err != S3E_SOUND_ERR_NONE) {
        FG_ErrorLog("playSFX(%d) on channel[%d] error[%d]: %s", idx, channel, err, s3eSoundGetErrorString());
    }
}

void fgSFXManager::stopAll() {
    s3eSoundStopAllChannels();
}

bool fgSFXManager::loadMusFiles()
{
    // No music files are being in fact loaded
    // - play directly from file
	return true;
}

void fgSFXManager::setMusVolume(float volume) {
	m_musVolume = volume;
    if(m_musVolume < 0.0f)
        m_musVolume = 0.01f;
    if(m_musVolume > 1.0f)
        m_musVolume = 1.0f;

    applyMusVolume();
}

void fgSFXManager::applyMusVolume() {
    s3eResult result = s3eAudioSetInt( S3E_AUDIO_VOLUME, int(m_musVolume * S3E_AUDIO_MAX_VOLUME * 0.85f));
}

void fgSFXManager::playMus(int idx) {
    s3eAudioStatus status = (s3eAudioStatus) s3eAudioGetInt(S3E_AUDIO_STATUS);

    if(S3E_AUDIO_PAUSED == status) {
        // This approach allows for mismatch between
        // paused track and parameter idx
       	s3eAudioResume();
    } else if(S3E_AUDIO_PLAYING == status) {
        s3eAudioStop();
        s3eAudioPlay(m_musResources[idx], 0);
    } else {
        s3eAudioPlay(m_musResources[idx], 0);        
    }

    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_ErrorLog("playMus(%d) error[%d]: %s (also status is: %d)", idx, err, s3eAudioGetErrorString(), status);
    }
}

void fgSFXManager::pauseMus(int idx) {
    s3eAudioPause();

    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_ErrorLog("pauseMus(%d) error[%d]: %s", idx, err, s3eAudioGetErrorString());
    }
}

void fgSFXManager::stopMus(int idx) {
    s3eAudioStop();
}

void fgSFXManager::rewindMus(int idx) {
    playMus(idx);
}
