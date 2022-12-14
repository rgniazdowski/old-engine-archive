/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgSFXSoundResource.h"
#include "fgLog.h"
#include "Util/fgStrings.h"
#include "Util/fgMemory.h"
#include "Util/fgFile.h"

using namespace fg;
//------------------------------------------------------------------------------

sfx::CSoundResource::CSoundResource() :
CResource(),
CAudio(base::T_SOUND),
m_chunkData(NULL),
m_soundData(NULL),
m_channel(0),
m_header() {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::SOUND;
    m_baseType = base::T_SOUND;
}
//------------------------------------------------------------------------------

sfx::CSoundResource::CSoundResource(const char *path) :
CResource(path),
CAudio(base::T_SOUND),
m_chunkData(NULL),
m_soundData(NULL),
m_channel(0),
m_header() {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::SOUND;
    m_baseType = base::T_SOUND;
}
//------------------------------------------------------------------------------

sfx::CSoundResource::CSoundResource(const std::string& path) :
CResource(path),
CAudio(base::T_SOUND),
m_chunkData(NULL),
m_soundData(NULL),
m_channel(0),
m_header() {
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_resType = resource::SOUND;
    m_baseType = base::T_SOUND;
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::clear(void) {
    base_type::clear();
    m_resType = resource::SOUND;
    m_chunkData = NULL;
    m_soundData = NULL;
    m_isPaused = FG_FALSE;
    m_volume = FG_SOUND_RESOURCE_DEFAULT_VOLUME;
    m_channel = 0;
    m_baseType = base::T_SOUND;
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::loadRawData(void) {
    if(getFilePath(m_quality).empty())
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::loadWavData(void) {
    if(getFilePath(m_quality).empty())
        return FG_FALSE;
    fg::util::DataFile wavFile;
    if(!wavFile.open(getFilePathStr(m_quality), fg::util::DataFile::Mode::BINARY | fg::util::DataFile::Mode::READ)) {
        FG_LOG_ERROR("SFX: Unable to open WAV file: '%s'", getFilePathStr(m_quality));
        return FG_FALSE;
    }
    SWAVHeader wavHeader;
    SWAVChunkHeader dataChunkHeader;

    wavFile.read(&wavHeader, (int)wavHeader.size(), 1);
    if(strncmp(wavHeader.waveID, "WAVE", 4) != 0) {
        //if(!fgStrings::isEqual(wavHeader.waveID, "WAVE")) {
        FG_LOG_ERROR("SFX: WAV file is not valid, missing 'WAVE' format ID: '%s'", getFilePathStr(m_quality));
        wavFile.close();
        return FG_FALSE;
    }

    // Check for existence of fmt chunk
    if(strncmp(wavHeader.subChunkFmtID, "fmt", 3) != 0) {
        //if(!fgStrings::isEqual(wavHeader.subChunkFmtID, "fmt")) {
        FG_LOG_ERROR("SFX: WAV file format chunk malformed: '%s'", getFilePathStr(m_quality));
        wavFile.close();
        return FG_FALSE;
    }

    if(wavHeader.audioFormat != 1) {
        FG_LOG_ERROR("SFX: WAV file is not in PCM format: '%s'", getFilePathStr(m_quality));
        wavFile.close();
        return FG_FALSE;
    }
    m_size = 0;
    //m_soundData = NULL; // #FIXME
    int offset = (int)wavFile.getPosition();
    void *temp = fgMalloc<void>(wavHeader.chunkSize);
    do {
        wavFile.read(&dataChunkHeader, (int)dataChunkHeader.size(), 1);

        if(strncmp(dataChunkHeader.chunkDataID, "data", 4) == 0) {
            //if(fgStrings::isEqual(dataChunkHeader.chunkDataID, "data")) {
            if(m_soundData == NULL)
                m_soundData = fgMalloc<unsigned char>(dataChunkHeader.subChunkDataSize);
            else
                m_soundData = fgRealloc<unsigned char>(m_soundData, (m_size + dataChunkHeader.subChunkDataSize));
            wavFile.read(m_soundData + m_size, 1, dataChunkHeader.subChunkDataSize);
            m_size += dataChunkHeader.subChunkDataSize;
        } else {
            wavFile.read(temp, 1, dataChunkHeader.subChunkDataSize);
        }
        offset = (int)wavFile.getPosition();
    } while(offset < wavHeader.chunkSize);

    fgFree(temp);
    wavFile.close();

    m_header.audioFormat = wavHeader.audioFormat;
    m_header.bitsPerSample = wavHeader.bitsPerSample;
    m_header.numChannels = wavHeader.numChannels;
    m_header.sampleRate = wavHeader.sampleRate;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::create(void) {
    if(m_isReady)
        return FG_TRUE;
    if(getFilePath(m_quality).empty()) {
        FG_LOG_ERROR("SFX: Sound/chunk file path is empty on create");
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    const char *path = getFilePathStr(m_quality);

#if defined(FG_USING_SDL_MIXER)
    if(!strings::endsWith(path, ".wav", FG_FALSE)) {
        FG_LOG_ERROR("SFX: Sound/chunk file extension is not valid (.WAV): '%s'", path);
        return FG_FALSE;
    }
    // Still need to use the custom wav loading procedure - it's because of loading
    // wav files from zip archives - need to create some automatic SDL_RWops wrapper
    // Also have in mind that at some point when FGEngine will not use Marmalade,
    // but SDL2 instead (meaning for mobile platforms) - ZipFile/RegularFile/DataFile and ZLIB
    // custom built library will need to use low level SDL IO functions - need 
    // to bind it transparently #WAV #SDL2 #MOBILE #SDL_RWOPS
    if(loadWavData()) {
        Uint16 format;
        int channels;
        int frequency;
        //AUDIO_U8        0x0008  /**< Unsigned 8-bit samples */
        //AUDIO_S8        0x8008  /**< Signed 8-bit samples */
        //AUDIO_U16LSB    0x0010  /**< Unsigned 16-bit samples */
        //AUDIO_S16LSB    0x8010  /**< Signed 16-bit samples */
        //AUDIO_U16MSB    0x1010  /**< As above, but big-endian byte order */
        //AUDIO_S16MSB    0x9010  /**< As above, but big-endian byte order */
        Uint16 wave_format;
        int wave_channels;
        int wave_frequency;
        if(m_header.bitsPerSample == 8)
            wave_format = AUDIO_U8;
        else if(m_header.bitsPerSample == 16)
            wave_format = AUDIO_S16;
        else if(m_header.bitsPerSample == 32)
            wave_format = AUDIO_S32;
        wave_channels = m_header.numChannels;
        wave_frequency = m_header.sampleRate;
        Mix_QuerySpec(&frequency, &format, &channels);
        SDL_AudioCVT wavecvt;
        /* Build the audio converter and create conversion buffers */
        if(wave_format != format ||
           wave_channels != channels ||
           wave_frequency != frequency) {
            if(SDL_BuildAudioCVT(&wavecvt,
                                 wave_format, wave_channels, wave_frequency,
                                 format, channels, frequency) < 0) {
                FG_LOG_ERROR("SFX: SDL2: Failed to initialize audio converter");
                fgFree(m_soundData);
                m_soundData = NULL;
                return FG_FALSE;
            }
            int samplesize = ((wave_format & 0xFF) / 8) * wave_channels;
            wavecvt.len = m_size & ~(samplesize - 1);
            wavecvt.buf = (Uint8 *)SDL_calloc(1, wavecvt.len * wavecvt.len_mult);
            if(wavecvt.buf == NULL) {
                SDL_SetError("Out of memory");
                FG_LOG_ERROR("SFX: SDL2: Failed to allocate conversion buffer");
                fgFree(m_soundData);
                m_soundData = NULL;
                return FG_FALSE;
            }
            SDL_memcpy(wavecvt.buf, m_soundData, m_size);
            fgFree(m_soundData);
            m_soundData = NULL;

            /* Run the audio converter */
            if(SDL_ConvertAudio(&wavecvt) < 0) {
                SDL_free(wavecvt.buf);
                FG_LOG_ERROR("SFX: SDL2: Failed to convert audio data for: '%s'", path);
                return FG_FALSE;
            }
            m_chunkData = Mix_QuickLoad_RAW(wavecvt.buf, wavecvt.len_cvt);
            if(!m_chunkData) {
                SDL_free(wavecvt.buf);
                FG_LOG_ERROR("SFX: SDL2: Failed to initialize chunk(RAW) audio data for: '%s'", path);
                return FG_FALSE;
            }
        }
    }
    if(!m_chunkData) {
        m_isReady = FG_FALSE;
    } else {
        FG_LOG_DEBUG("SFX: Successfully loaded sound/chunk file: '%s'", path);
        Mix_VolumeChunk(m_chunkData, m_volume);
        m_isReady = FG_TRUE;
    }
#endif
    return m_isReady;
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::destroy(void) {
    dispose();
    m_chunkData = NULL;
    m_isReady = FG_FALSE;
    sfx::CSoundResource::clear();
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::recreate(void) {
    if(m_isReady) {
        dispose();
    }
    return create();
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::dispose(void) {
#if defined(FG_USING_SDL_MIXER)
    setVolume(0);
    stop();
    if(m_chunkData) {
        Mix_FreeChunk(m_chunkData);
    }
#endif
    if(m_soundData) {
        fgFree(m_soundData, FG_FALSE);
    }
    m_soundData = NULL;
    m_chunkData = NULL;
    m_isReady = FG_FALSE;
    m_channel = 0;
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::isDisposed(void) const {
#if 1
    if(!m_chunkData || !m_isReady) {
        return FG_TRUE;
    }
#endif
    return FG_FALSE;
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::play(void) {
    if(!m_isReady)
        return;
    FG_LOG_DEBUG("SFX: Playing sound: name[%s]", getNameStr());
#if defined(FG_USING_SDL_MIXER)
    if(m_chunkData) {
        //int Mix_PlayChannelTimed(int channel, Mix_Chunk *chunk, int loops, int ticks);
        m_channel = Mix_PlayChannel(-1, m_chunkData, 0);
        m_isPlaying = FG_TRUE;
        m_isPaused = FG_FALSE;
    }
#endif
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::pause(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(!Mix_Paused(m_channel) && isPlaying()) {
        Mix_Pause(m_channel);
    }
    m_isPaused = FG_TRUE;
#endif
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::resume(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(isPaused() && Mix_Playing(m_channel))
        Mix_Resume(m_channel);
    if(Mix_Playing(m_channel))
        m_isPlaying = FG_TRUE;
#endif
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::rewind(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    stop();
    play();
#endif
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::stop(void) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(Mix_Playing(m_channel))
        Mix_HaltChannel(m_channel);
    m_channel = 0;
    m_isPlaying = FG_FALSE;
    m_isPaused = FG_FALSE;
#endif
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::isPaused(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPaused = (fgBool)Mix_Paused(m_channel);
#endif    
    return m_isPaused;
}
//------------------------------------------------------------------------------

fgBool sfx::CSoundResource::isPlaying(void) {
    if(!m_isReady)
        return FG_FALSE;
#if defined(FG_USING_SDL_MIXER)
    m_isPlaying = (fgBool)Mix_Playing(m_channel);
#endif
    return m_isPlaying;
}
//------------------------------------------------------------------------------

void sfx::CSoundResource::setVolume(FG_SFX_VOLUME_TYPE volume) {
    if(!m_isReady)
        return;
#if defined(FG_USING_SDL_MIXER)
    if(volume <= MIX_MAX_VOLUME) {
        if(m_chunkData)
            Mix_VolumeChunk(m_chunkData, volume);
        //if(isPlaying())
        //    Mix_Volume(m_channel, volume); // ? ? 
    }
#endif 
    m_volume = volume;
}
//------------------------------------------------------------------------------

int sfx::CSoundResource::getCurrentChannel(void) {
    if(!m_isReady) {
        m_channel = 0;
    } else if(!isPlaying() && !isPaused()) {
        m_channel = 0;
    }
    return m_channel;
}
//------------------------------------------------------------------------------
