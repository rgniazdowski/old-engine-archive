/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgSFXManager.h"

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>

#ifdef FG_USING_MARMALADE
#include "s3eFile.h"
#ifdef FG_USING_MARMALADE_SOUND
#include "s3eSound.h"
#endif // FG_USING_MARMALADE_SOUND
#ifdef FG_USING_MARMALADE_AUDIO
#include "s3eAudio.h"
#endif // FG_USING_MARMALADE_AUDIO
#endif // FG_USING_MARMALADE

#include "fgLog.h"

#define SNDDIR "sound/"

const char* fgSFXManager::m_sfxResources[ fgSFXManager::SFX_COUNT ] = {SNDDIR"c.raw", SNDDIR"s.raw", SNDDIR"tod.raw", SNDDIR"p.raw", SNDDIR"m.raw", SNDDIR"d.raw"};
const char* fgSFXManager::m_musResources[ fgSFXManager::MUS_COUNT ] = {SNDDIR"m1.mp3"};

template <>
bool fgSingleton<fgSFXManager>::instanceFlag = false;

template <>
fgSFXManager *fgSingleton<fgSFXManager>::instance = NULL;

/**
 * Private destructor
 */
fgSFXManager::~fgSFXManager() {

    stopAll();
#ifdef FG_USING_MARMALADE_AUDIO
    s3eAudioStop();
#endif // FG_USING_MARMALADE_AUDIO

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

    memset(m_sfxBuffers, 0, sizeof (m_sfxBuffers));
    memset(m_sfxBuffersSizes, 0, sizeof (m_sfxBuffersSizes));
#ifdef FG_USING_MARMALADE_AUDIO
    m_mp3 = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3);
    if(m_mp3) {
        FG_LOG::PrintDebug("MP3 codec supported");
    } else {
        FG_LOG::PrintError("No MP3 support!");
    }
    m_pcm = (fgBool)s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_PCM);
    if(m_pcm) {
        FG_LOG::PrintDebug("PCM codec supported");
    } else {
        FG_LOG::PrintError("No PCM support!");
    }
#endif // FG_USING_MARMALADE_AUDIO
}

/**
 * Loads given file into memory
 */
bool fgSFXManager::loadAudioFile(const char* name, unsigned char* & out_buffer, int & out_size) {
#ifdef FG_USING_MARMALADE_AUDIO // #FIXME

    out_buffer = NULL;
    out_size = 0;

    s3eFile* fileHandle = s3eFileOpen(name, "rb");
    if(NULL == fileHandle) {
        FG_LOG::PrintError("Unable to open audio file '%s', error code: %d", name, s3eFileGetError());
        return false;
    }

    int fileSize = s3eFileGetSize(fileHandle);
    unsigned char* buffer = new unsigned char[fileSize + 1];
    buffer[fileSize] = '\0';
    memset(buffer, 0, fileSize);

    int objectsRead = s3eFileRead(buffer, fileSize, 1, fileHandle);
    s3eFileClose(fileHandle);

    if(objectsRead != 1) {
        FG_LOG::PrintError("Should read %d bytes of an sound file, read %d instead!", fileSize, objectsRead * fileSize);
        delete [] buffer;
        return false;
    }

    FG_LOG::PrintDebug("Read %d bytes of '%s', buffer = %p", fileSize, name, buffer);

    out_buffer = buffer;
    out_size = fileSize;
#endif // FG_USING_MARMALADE_AUDIO
    return true;
}

bool fgSFXManager::loadSfxFiles() {
    for(int i = 0; i < SFX_COUNT; i++) {
        if(false == loadAudioFile(m_sfxResources[i], m_sfxBuffers[i], m_sfxBuffersSizes[i])) {
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
#ifdef FG_USING_MARMALADE_SOUND
    s3eResult result = s3eSoundSetInt(S3E_SOUND_VOLUME, int(m_sfxVolume * S3E_SOUND_MAX_VOLUME * 0.9f));
    if(S3E_RESULT_SUCCESS != result) {
        FG_LOG::PrintError("Error when setting the sfx volume: %d", result);
    }
#endif // FG_USING_MARMALADE_SOUND
}

void fgSFXManager::play(int idx) {
#ifdef FG_USING_MARMALADE_SOUND

    int channel = s3eSoundGetFreeChannel();
    s3eSoundChannelPlay(channel, (int16*)m_sfxBuffers[idx], m_sfxBuffersSizes[idx] / 2, 1, 0);
    // Check for error
    s3eSoundError err = s3eSoundGetError();
    if(err != S3E_SOUND_ERR_NONE) {
        FG_LOG::PrintError("playSFX(%d) on channel[%d] error[%d]: %s", idx, channel, err, s3eSoundGetErrorString());
    }
#endif // FG_USING_MARMALADE_SOUND
}

void fgSFXManager::stopAll() {
#ifdef FG_USING_MARMALADE_SOUND
    s3eSoundStopAllChannels();
#endif // FG_USING_MARMALADE_SOUND
}

bool fgSFXManager::loadMusFiles() {
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
#ifdef FG_USING_MARMALADE_AUDIO
    s3eResult result = s3eAudioSetInt(S3E_AUDIO_VOLUME, int(m_musVolume * S3E_AUDIO_MAX_VOLUME * 0.85f));
#endif // FG_USING_MARMALADE_AUDIO
}

void fgSFXManager::playMus(int idx) {
#ifdef FG_USING_MARMALADE_AUDIO
    s3eAudioStatus status = (s3eAudioStatus)s3eAudioGetInt(S3E_AUDIO_STATUS);

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
        FG_LOG::PrintError("playMus(%d) error[%d]: %s (also status is: %d)", idx, err, s3eAudioGetErrorString(), status);
    }
#endif // FG_USING_MARMALADE_AUDIO
}

void fgSFXManager::pauseMus(int idx) {
#ifdef FG_USING_MARMALADE_AUDIO
    s3eAudioPause();

    // Check for error
    s3eAudioError err = s3eAudioGetError();
    if(err != S3E_AUDIO_ERR_NONE) {
        FG_LOG::PrintError("pauseMus(%d) error[%d]: %s", idx, err, s3eAudioGetErrorString());
    }
#endif // FG_USING_MARMALADE_AUDIO
}

void fgSFXManager::stopMus(int idx) {
#ifdef FG_USING_MARMALADE_AUDIO
    s3eAudioStop();
#endif // FG_USING_MARMALADE_AUDIO
}

void fgSFXManager::rewindMus(int idx) {
    playMus(idx);
}
