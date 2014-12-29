/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgZipFile.cpp
 * Author: vigilant
 * 
 * Created on December 24, 2014, 1:23 AM
 */

#include "fgZipFile.h"
#include "fgStrings.h"
#include "fgMemory.h"
#include "fgPath.h"
#include <fstream>

/**
 * 
 */
fg::util::ZipFile::ZipFile() :
m_password(),
m_selectedFilePath(),
m_extractionPath(),
m_zipPath(),
m_filePaths(),
m_fileItor(),
m_currentFileID(0),
m_zf(NULL),
m_uf(NULL),
m_mode(Mode::READ) {
    memset(&m_zInfo, 0, sizeof (ZipFileInfo));
    memset(&m_zGlobalInfo, 0, sizeof (ZipGlobalInfo));
    memset(&m_zFilePos, 0, sizeof (ZipFilePos));
}

/**
 * 
 * @param filePath
 */
fg::util::ZipFile::ZipFile(const char* filePath) :
m_password(),
m_selectedFilePath(),
m_extractionPath(),
m_zipPath(),
m_filePaths(),
m_fileItor(),
m_currentFileID(0),
m_zf(NULL),
m_uf(NULL),
m_mode(Mode::READ) {
    memset(&m_zInfo, 0, sizeof (ZipFileInfo));
    memset(&m_zGlobalInfo, 0, sizeof (ZipGlobalInfo));
    memset(&m_zFilePos, 0, sizeof (ZipFilePos));
    if(filePath)
        setPath(filePath);
}

/**
 * 
 * @param filePath
 */
fg::util::ZipFile::ZipFile(const std::string& filePath) :
m_password(),
m_selectedFilePath(),
m_extractionPath(),
m_zipPath(),
m_filePaths(),
m_fileItor(),
m_currentFileID(0),
m_zf(NULL),
m_uf(NULL),
m_mode(Mode::READ) {
    memset(&m_zInfo, 0, sizeof (ZipFileInfo));
    memset(&m_zGlobalInfo, 0, sizeof (ZipGlobalInfo));
    memset(&m_zFilePos, 0, sizeof (ZipFilePos));
    setPath(filePath);
}

/**
 * 
 * @param orig
 */
fg::util::ZipFile::ZipFile(const ZipFile& orig) { }

/**
 * Default virtual destructor for the ZipFile object
 */
fg::util::ZipFile::~ZipFile() {
    m_filePath.clear();
    m_selectedFilePath.clear();
#if !defined(FG_USING_MARMALADE)
    m_selectedFilePath.shrink_to_fit();
    m_filePath.shrink_to_fit();
#endif
    m_filePaths.clear_optimised();
}

/**
 * 
 * @param mode
 */
void fg::util::ZipFile::setMode(FileMode mode) {
    m_modeFlags = mode; // File mode
    m_mode = Mode::READ; // ZipFile mode
    if(!!(m_modeFlags & FileMode::READ) && !(m_modeFlags & FileMode::UPDATE)) {
        m_mode = Mode::READ;
    } else if(!!(m_modeFlags & FileMode::WRITE) && !(m_modeFlags & FileMode::UPDATE)) {
        m_mode = Mode::WRITE;
    } else if(m_modeFlags & FileMode::READ_UPDATE ||
              m_modeFlags & FileMode::UPDATE ||
              m_modeFlags & FileMode::APPEND ||
              m_modeFlags & FileMode::APPEND_UPDATE ||
              m_modeFlags & FileMode::WRITE_UPDATE) {
        m_mode = Mode::UPDATE;
    }
    }
}

/**
 * 
 * @param filePath
 */
void fg::util::ZipFile::setPath(const char *filePath) {
    // This will determine whether or not the specified file points to a valid 
    // ZipFile (based on the extension) and also set the relative path to inner
    // compressed file (if any is specified). This means that this supports paths
    // like: "data/textures.zip/castle/flag.tga"
    if(!filePath)
        return;
    const char *ext = fgStrings::stristr(filePath, ".zip");
    if(!ext)
        ext = fgStrings::stristr(filePath, ".pk3");
    if(!ext) {
        // Probably not a valid Zip file
        m_filePath.clear();
        return;
    }
    if(ext) {
        int extlen = strlen(ext);
        if(extlen > 4) {
            // This means that there is something more in the path
            //unsigned int fplen = ((uintptr_t)ext)-((uintptr_t)filePath);
            m_zipPath = filePath;
            m_zipPath.resize(m_zipPath.size() - extlen + 4);
#if !defined(FG_USING_MARMALADE)
            m_zipPath.shrink_to_fit();
#endif
            // Full path to the file within the zip file - it cointains also the
            // name of the zip archive
            m_filePath = filePath;
            // Relative path to the selected file in the archive
            // Checking for a valid path is in open functions
            m_selectedFilePath = (ext + 5);
        } else {
            // the extension fits
            m_zipPath = filePath;
            m_filePath = m_zipPath;
            m_selectedFilePath.clear();
        }
    }
}

/**
 * 
 * @param filePath
 */
void fg::util::ZipFile::setPath(const std::string & filePath) {
    if(filePath.empty())
        return;
    setPath(filePath.c_str());
}

/**
 * Check whether currently selected file is a directory
 * @return 
 */
fgBool fg::util::ZipFile::isCurrentFileDir(void) {
    int sn = m_selectedFilePath.size();
    if(sn) {
        std::string dirname;
        fgPath::dirName(m_selectedFilePath, dirname);
        int dn = dirname.size();
        char dc = dirname[dn - 1];
        char sc = m_selectedFilePath[sn - 1];
        if(dn == sn && (dc == '/' || dc == '\\') && (sc == '/' || sc == '\\'))
            return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool fg::util::ZipFile::goToNextFile(void) {
    if(!isOpen())
        return FG_FALSE;
    m_currentFileID++;
    if(m_currentFileID >= (int)m_filePaths.size()) {
        return FG_FALSE;
    }
    return private_selectFile(m_currentFileID);
}

/**
 * 
 * @return 
 */
fgBool fg::util::ZipFile::goToPreviousFile(void) {
    if(!isOpen())
        return FG_FALSE;
    m_currentFileID--;
    if(m_currentFileID < 0) {
        return FG_FALSE;
    }
    return private_selectFile(m_currentFileID);
}

/**
 * 
 * @return 
 */
fgBool fg::util::ZipFile::goToFirstFile(void) {
    if(m_filePath.empty())
        return FG_FALSE;
    return selectFile(m_filePath.c_str());
}

/**
 * 
 * @return 
 */
fgBool fg::util::ZipFile::private_updateCurrentFileInfo(void) {
    fgBool status = FG_TRUE;
    if(!isOpen())
        status = FG_FALSE;
    if(status && m_mode == Mode::READ && m_uf) {
        char fileInZip[256];
        int err = unzGetCurrentFileInfo64(m_uf, &m_zInfo.unz64, fileInZip, 256, NULL, 0, NULL, 0);
        if(err != UNZ_OK) {
            // Something went wrong while getting info
            status = FG_FALSE;
        } else {
            if(m_password.empty()) {
                err = unzOpenCurrentFile(m_uf);
            } else {
                err = unzOpenCurrentFilePassword(m_uf, m_password.c_str());
            }
            if(err != UNZ_OK) {
                // Could not open the file
                m_selectedFilePath.clear();
                m_currentFileID = 0;
                status = FG_FALSE;
            } else {
                m_selectedFilePath = fileInZip;
            }
        }
    }
    if(status) {
        // Join the path to the file
        fgPath::join(m_filePath, m_zipPath, m_selectedFilePath);
    }
    return status;
}

/**
 * 
 * @param id
 * @return 
 */
fgBool fg::util::ZipFile::private_selectFile(const int id) {
    if(id < 0 || id >= (int)m_filePaths.size())
        return FG_FALSE;
    if(m_filePath.empty()) {
        return FG_FALSE;
    }
    if(!m_uf) {
        // The Zip file needs to be opened before selecting the file
        return FG_FALSE;
    }
    int err = UNZ_OK;
    err = unzCloseCurrentFile(m_uf);
    // Probably path points to the file inside of the Zip
    err = unzLocateFile(m_uf, m_filePaths[id].c_str(), NULL);
    if(err != UNZ_OK) {
        m_selectedFilePath.clear();
        m_currentFileID = 0;
        return FG_FALSE;
    }
    m_currentFileID = id;
    // Properly selected path
    //m_selectedFilePath = m_filePaths[id];
    return private_updateCurrentFileInfo();
    //return FG_TRUE;
}

/**
 * Selects the file inside of the ZipFile. By default the first file
 * is selected.
 * @param filePath  Relative path to the file inside the Zip. If the
 * path to the ZipFile is not set this function will fail. If the 
 * path points to the ZipFile (is not relative) the first file will
 * be selected.
 * @return          FG_TRUE on  success (valid  file  is  selected),
 *                  FG_FALSE otherwise (no  valid  Zip  specified or
 *                  the selected file does not exist in the Zip)
 */
fgBool fg::util::ZipFile::selectFile(const char *filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    if(m_filePath.empty()) {
        return FG_FALSE;
    }
    if(!m_uf) {
        // The Zip file needs to be opened before selecting the file
        return FG_FALSE;
    }
    int err = UNZ_OK;
    const char *ext = fgStrings::stristr(filePath, ".zip");
    if(!ext)
        ext = fgStrings::stristr(filePath, ".pk3");
    if(!ext) {
        err = unzCloseCurrentFile(m_uf);
        // Probably path points to the file inside of the Zip
        err = unzLocateFile(m_uf, filePath, NULL);
        if(err != UNZ_OK) {
            m_selectedFilePath.clear();
            m_currentFileID = 0;
            return FG_FALSE;
        }
        m_currentFileID = m_filePaths.find(std::string(filePath));
        // Properly selected path
        m_selectedFilePath = filePath;
    } else {
        // Check the path (the same as Zip) -> select the first file
        if(fgStrings::isEqual(m_zipPath.c_str(), filePath, FG_FALSE)) {
            err = unzCloseCurrentFile(m_uf);
            err = unzGoToFirstFile(m_uf);
            m_currentFileID = 0;
            if(err != UNZ_OK) {
                m_selectedFilePath.clear();
                return FG_FALSE;
            }
        }
    }
    private_updateCurrentFileInfo();
    return FG_TRUE;
}

/**
 * Selects the file inside of the ZipFile. By default the first file
 * is selected.
 * @param filePath  Relative path to the file inside the Zip. If the
 * path to the ZipFile is not set this function will fail. If the 
 * path points to the ZipFile (is not relative) the first file will
 * be selected.
 * @return          FG_TRUE on  success (valid  file  is  selected),
 *                  FG_FALSE otherwise (no  valid  Zip  specified or
 *                  the selected file does not exist in the Zip)
 */
fgBool fg::util::ZipFile::selectFile(const std::string& filePath) {
    return selectFile(filePath.c_str());
}

/**
 * Open the ZipFile with already set options
 * @return 
 */
fgBool fg::util::ZipFile::open(void) {
    if(m_mode == Mode::NONE || m_zipPath.empty())
        return FG_FALSE;
    // MAIN OPEN FUNCTION FOR ZIP
    // Here the magic happens
    int err = UNZ_OK;
    if(m_mode == Mode::READ || m_mode == Mode::EXTRACT) {
        if(m_uf) {
            unzCloseCurrentFile(m_uf);
            unzClose(m_uf);
        }
        m_uf = unzOpen64((void *)m_zipPath.c_str());
        if(m_uf == NULL) {
            // Failed to open file
            return FG_FALSE;
        }
        // Successfully opened file
        // Update global info
        err = unzGetGlobalInfo64(m_uf, &m_zGlobalInfo.unz64);
        if(err != UNZ_OK) {
            err = unzGetGlobalInfo(m_uf, &m_zGlobalInfo.unz);
            if(err != UNZ_OK) {

            }
        }

        {
            err = unzGoToFirstFile(m_uf);
            if(err != UNZ_OK) {
                return FG_FALSE;
            }
            // Clear current file list
            m_filePaths.clear_optimised();
            // Update the inner list of files
            unz_file_info64 file_info = {0};
            char fileInZip[256];
            do {
                err = unzGetCurrentFileInfo64(m_uf, &file_info, fileInZip, sizeof (fileInZip), NULL, 0, NULL, 0);
                if(err != UNZ_OK)
                    break;
                /* Display a '*' if the file is encrypted */
                //if((file_info.flag & 1) != 0)
                //    charCrypt = '*';
                int len = strlen(fileInZip);
                if(len) {
                    m_filePaths.push_back(std::string(fileInZip));
                }
                err = unzGoToNextFile(m_uf);
            } while(err == UNZ_OK);
        }
    }
    if(m_selectedFilePath.empty()) {
        // When passing the path to the main ZipFile (root)
        // The first file will be selected automatically.
        // It's important that after a successful call to open(), functions
        // for reading/writing can be called normally, without additional parameters.
        selectFile(m_filePath);
    } else {
        // If for now the selected file name is not empty
        // it means that it was set with (probably) setPath function
        selectFile(m_selectedFilePath);
    }
    return FG_TRUE;
}

/**
 * Open the file with specified mode. This will have different effect,
 * based on the currently set path or selected file inside of the zip.
 * @param mode
 * @return 
 */
fgBool fg::util::ZipFile::open(Mode mode) {
    if(mode == Mode::NONE)
        return FG_FALSE;
    this->setMode(mode);
    return open();
}

/**
 * Open the ZipFile (pointed to by path) with specified mode. 
 * @param filePath
 * @param mode
 * @return 
 */
fgBool fg::util::ZipFile::open(const char *filePath, Mode mode) {
    // This is open working with special mode
    if(!filePath || mode == Mode::NONE)
        return FG_FALSE;
    this->setPath(filePath);
    this->setMode(mode);
    return open();
}

/**
 * Open the file with specified mode. It will use currently selected
 * ZipFile/file path. Action really  performed  depends  on the file 
 * path - actually used mode to  open the file may  differ  from the 
 * one passed in the  function.  This  function  is  used mainly for 
 * compatibility and transparency with util::File class. 
 * @param mode
 * @return 
 */
fgBool fg::util::ZipFile::open(FileMode mode) {
    // Inception?
    if(m_filePath.empty() || mode == FileMode::NONE)
        return FG_FALSE;
    this->setMode(mode);
    return open();
}

/**
 * Open the file (pointed to by path)  with  specified  mode. Action
 * performed depends on the file path. Whenever  the  new ZipFile is 
 * opened - the inside structure (file list  with relative paths) is
 * buffered into StringVector.
 * @param filePath
 * @param mode
 * @return 
 */
fgBool fg::util::ZipFile::open(const char *filePath, FileMode mode) {
    if(!filePath || mode == FileMode::NONE)
        return FG_FALSE;
    this->setPath(filePath);
    this->setMode(mode);
    // Now need to recheck the FileMode - select the proper mode for Zip,
    // apply the paths...
    return open();
}

/**
 * Close the file
 * @return 
 */
fgBool fg::util::ZipFile::close(void) {
    if(!isOpen())
        return FG_TRUE;
    if(m_uf) {
        unzCloseCurrentFile(m_uf);
        unzClose(m_uf);
        m_uf = NULL;
    }
    if(m_zf) {
        zipCloseFileInZip(m_zf);
        zipClose(m_zf, NULL);
        m_zf = NULL;
    }
    memset(&m_zInfo, 0, sizeof (ZipFileInfo));
    memset(&m_zGlobalInfo, 0, sizeof (ZipGlobalInfo));
    m_selectedFilePath.clear();
    m_filePaths.clear_optimised();
    return FG_TRUE;
}

/**
 * Check if file is currently opened
 * @return 
 */
fgBool fg::util::ZipFile::isOpen(void) const {
    return (fgBool)(m_zf != NULL || m_uf != NULL);
}

/**
 * Check if file exists
 * @return 
 */
fgBool fg::util::ZipFile::exists(void) {
#if defined FG_USING_MARMALADE
    return (fgBool)s3eFileCheckExists(m_filePath.c_str());
#else
    std::ifstream fileCheck(m_filePath);
    return (fgBool)fileCheck.good();
#endif
}

/**
 * This will load the whole file into char *buffer
 * @return Newly allocated string representing the contents of the file
 *         There is a limit for how big this buffer can be. If it's
 *         exceeded a NULL pointer will be returned. The returned
 *         string buffer will be null-terminated ('\0' will be appended)
 */
char *fg::util::ZipFile::load(void) {
    char *data = NULL;
    fgBool status = FG_TRUE;
    unsigned int fileSize = 0;
    if(!isOpen() || m_selectedFilePath.empty()) {
        status = FG_FALSE;
    }
    if(!m_uf) {
        status = FG_FALSE;
    }
    if(status) {
        fileSize = (unsigned int)m_zInfo.unz64.uncompressed_size;
        if(!fileSize) {
            status = FG_FALSE;
        }
    }
    if(status) {
        data = fgMalloc<char>(fileSize + 1);
        if(!data) {
            status = FG_FALSE;
        } else {
            memset(data, 0, fileSize + 1);
        }
    }
    if(status) {
        // Reselect the current file - this will rewind the file to the beginning
        if(getPosition() != 0L)
            status = selectFile(m_selectedFilePath.c_str());
    }
    if(status) {
        int bytesRead = read((void *)data, 1, fileSize);
        if(bytesRead <= 0) {
            status = FG_FALSE;
            //fgFree((void *)data, fileSize, FG_TRUE);
            fgFree(data);
            data = NULL;
        }
    }
    return data;
}

/**
 * This will load the whole file into char *buffer
 * @param filePath
 * @return Newly allocated string representing the contents of the file
 *         There is a limit for how big this buffer can be. If it's
 *         exceeded a NULL pointer will be returned. The returned
 *         string buffer will be null-terminated ('\0' will be appended)
 */
char *fg::util::ZipFile::load(const char *filePath) {
    if(!filePath)
        return NULL;
    if(isOpen()) {
        close();
    }
    setPath(filePath);
    if(m_filePath.empty())
        return NULL;
    if(!open()) {
        return NULL;
    }
    return load();
}

/**
 * Read from file
 * @param buffer
 * @param elemsize
 * @param elemcount
 * @return 
 */
int fg::util::ZipFile::read(void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(!buffer || !elemsize || !elemcount || m_filePath.empty())
        return 0;
    if(m_mode == Mode::READ && !m_uf)
        return 0;
    if(m_selectedFilePath.empty()) {
        // Selected file path must be not empty
        // Empty path for selected file means that no file (in zip) is currently open
        return 0;
    }
    int err = UNZ_OK;
    unsigned int bytesToRead = elemsize * elemcount;
    int elemRead = unzReadCurrentFile(m_uf, buffer, bytesToRead);
    if(elemRead < 0) {
        // Error
        return -1;
    }
    return elemRead;
}

/**
 * Read string from the file
 * @param buffer
 * @param maxlen
 * @return 
 */
char *fg::util::ZipFile::readString(char *buffer, unsigned int maxlen) {
    if(!buffer || !maxlen)
        return NULL;
    if(!isOpen())
        return NULL;
    if(m_selectedFilePath.empty())
        return NULL;
    if(isEOF())
        return NULL;
    char c = 0;
    unsigned int pos = 0;
    int status = 0;
    if(m_uf) {
        do {
            status = read(&c, 1, 1);
            if(status > 0) {
                buffer[pos] = c;
                pos++;
                if(c == '\n') {
                    buffer[pos] = 0;
                    pos++;
                    status = -1;
                }
            } else if(!pos) {
                buffer[0] = 0;
                buffer = NULL;
            }
        } while(status > 0 && pos < maxlen);
    }
    return buffer;
}

/**
 * Write to the file
 * @param buffer
 * @param elemsize
 * @param elemcount
 * @return 
 */
int fg::util::ZipFile::write(void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(!buffer || !elemsize || !elemcount || m_filePath.empty())
        return 0;
    return 0;
}

/**
 * Print to the file
 * @param fmt
 * @return 
 */
int fg::util::ZipFile::print(const char *fmt, ...) {
    if(!fmt || !isOpen())
        return 0;
    if(m_mode != Mode::WRITE && m_mode != Mode::UPDATE)
        return 0;
    if(m_selectedFilePath.empty())
        return 0;

    return 0;
}

/**
 * Put given string into the file
 * @param str
 * @return 
 */
int fg::util::ZipFile::puts(const char *str) {
    if(!str || !isOpen())
        return 0;
    if(m_mode != Mode::WRITE && m_mode != Mode::UPDATE)
        return 0;
    if(m_selectedFilePath.empty())
        return 0;

    return 0;
}

/**
 * Check is it end of file
 * @return 
 */
fgBool fg::util::ZipFile::isEOF(void) {
    fgBool status = FG_FALSE;
    if(m_uf && !m_selectedFilePath.empty()) {
        if(unzeof(m_uf) == 1)
            status = FG_TRUE;
    }
    return status;
}

/**
 * Flush file buffers
 * @return 
 */
fgBool fg::util::ZipFile::flush(void) {
    return FG_FALSE;
}

/**
 *  Get (read) single character from file
 * @return 
 */
int fg::util::ZipFile::getChar(void) {
    int c = 0;
    if(m_mode == Mode::READ && m_uf && !m_selectedFilePath.empty()) {
        if(this->read((void *)&c, 1, 1) <= 0)
            c = 0;
    }
    return c;
}

/**
 * Put (write) single character to file
 * @param c
 * @return 
 */
int fg::util::ZipFile::putChar(char c) {
    return 0;
}

/**
 * Get the file size (in bytes)
 * @return 
 */
int fg::util::ZipFile::getSize(void) {
    int size = 0;
    //if(m_selectedFilePath.empty()) {
    // There is no current file selected
    // File info structure is invalid
    //return 0;
    //}
    if(m_uf && !m_selectedFilePath.empty())
        size = (int)m_zInfo.unz64.uncompressed_size;
    return size;
}

/**
 * Get the current position in the file
 * @return 
 */
long fg::util::ZipFile::getPosition(void) {
    long pos = 0L;
    if(m_uf)
        pos = (long)unztell(m_uf);
    //long int offset = (long int)unzGetOffset(m_uf);
    //long int tell = unztell(m_uf);
    //if(unzGetFilePos(m_uf, &m_zFilePos.unz) == UNZ_OK) {
    //printf("offset: %ld tell:%ld numoffile:%ld pos_in_zip_dir:%ld\n", offset, tell, m_zFilePos.unz.num_of_file, m_zFilePos.unz.pos_in_zip_directory);
    //}       
    return pos;
}

/**
 * Sets the position in the currently open/selected file
 * @param offset
 * @param whence
 * @return 
 */
int fg::util::ZipFile::setPosition(long offset, int whence) {
    return 0;
}
