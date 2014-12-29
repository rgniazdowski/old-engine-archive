/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTypes.h"
#include "fgCommon.h"
#include "fgLog.h"
#include "fgDirent.h"
#include "fgPath.h"
#include "fgStrings.h"
#include "fgZipFile.h"

/*
 *
 */
fgDirent::fgDirent() :
m_dirPath(),
m_fileNames(),
m_fileIt(),
#ifdef FG_USING_MARMALADE
m_fileList(NULL),
#else
m_curDir(NULL),
m_curEntry(NULL),
#endif
m_isRecursive(FG_FALSE) {
    m_fileIt = m_fileNames.end();
}

/*
 * Default constructor with the specified directory path
 * Please note that this constructor will also call the
 * read directory function.
 */
fgDirent::fgDirent(const char *dirPath) {
    m_isRecursive = FG_FALSE;
    readDirectory(dirPath, FG_FALSE);
}

/*
 * Default constructor with the specified directory path
 * Please note that this constructor will also call the
 * read directory function.
 */
fgDirent::fgDirent(const std::string &dirPath) {
    m_isRecursive = FG_FALSE;
    readDirectory(dirPath, FG_FALSE);
}

/*
 *
 */
fgDirent::~fgDirent() {
#ifdef FG_USING_MARMALADE
    // ?
#else
    // ?
#endif
    m_dirPath.clear();
    m_fileNames.clear_optimised();
}

/**
 * 
 * @param fileName
 * @param filePath
 * @param recursive
 * @return 
 */
fgBool fgDirent::internal_readZipFile(const std::string& fileName,
                                      const std::string& filePath,
                                      fgBool recursive) {
    // If the current file is a zip file and the listing trigger is
    // active - append full zip listing into file names/paths vector
    fg::util::ZipFile zip(filePath);
    zip.open();
    fgStringVector &zipFileList = zip.getFileList();
    int nZipFiles = zipFileList.size();
    for(int i = 0; i < nZipFiles; i++) {
        // Need to check here if the path inside of the zip does not
        // point to a directory - such path has a ending delimeter
        std::string filePathInZip;
        // Join the paths
        if(recursive) {
            fgPath::join(filePathInZip, filePath, zipFileList[i]);
        } else {
            fgPath::join(filePathInZip, fileName, zipFileList[i]);
        }
        std::string dirInZipName;
        // If the path has an ending delimeter the dirName function
        // will return the same string - no changes
        fgPath::dirName(filePathInZip, dirInZipName);
        int fn = filePathInZip.size();
        int dn = dirInZipName.size();
        char dc = dirInZipName[dn - 1];
        char fc = filePathInZip[fn - 1];
        // Check whether path has the ending delimeter - it's not so accurate
        if(!(dn == fn && (dc == '/' || dc == '\\') && (fc == '/' || fc == '\\')))
            m_fileNames.push_back(filePathInZip);
    }
    zip.close();
    return (fgBool)(!!nZipFiles);
}

/**
 * Reads the directory content creating a list
 * with file names in it (or file paths) - paths to directories are ignored
 * @param recursive
 * @param listZipFiles
 * @return 
 */
fgBool fgDirent::readDirectory(fgBool recursive, fgBool listZipFiles) {
#ifdef FG_USING_MARMALADE
    m_fileList = NULL;
#else
    m_curDir = NULL;
    m_curEntry = NULL;
#endif /* FG_USING_MARMALADE */

    m_fileNames.clear_optimised();
    fgStringVector dirStack;
    std::string fileName;
    std::string dirPath;
    fgStringVector dirVec;
    fgStrings::split(m_dirPath, ';', dirVec);
    int ndirs = dirVec.size();

    for(int idir = 0; idir < ndirs; idir++) {
        dirPath = dirVec[idir];

        const char *fileExt = fgStrings::stristr(dirPath, ".zip");
        if(!fileExt)
            fileExt = fgStrings::stristr(dirPath, ".pk3");
        if(fileExt) {
            // dir path points to a zip file
            internal_readZipFile(dirPath, dirPath, FG_FALSE);
        } else {
            dirStack.push_back(dirPath);
        }

        while(!dirStack.empty()) {
            std::string filePath;
            std::string curDir = dirStack.back();
            dirStack.pop_back();

#if defined(FG_USING_MARMALADE)
            char fileNameStr[FG_FILE_NAME_MAX];
            m_fileList = s3eFileListDirectory(curDir.c_str());
            if(!m_fileList)
                continue;

            while(S3E_RESULT_SUCCESS == s3eFileListNext(m_fileList, fileNameStr, FG_FILE_NAME_MAX - 1)) {
                fileName = fileNameStr;
#else
            struct stat fileInfo;
            m_curDir = opendir(curDir.c_str());
            if(!m_curDir) {
                FG_LOG_DEBUG("fg::util::dirent: Unable to open directory: '%s'", curDir.c_str());
                continue;
            }

            while((m_curEntry = readdir(m_curDir)) != NULL) {
                fileName = m_curEntry->d_name;
#endif /* FG_USING_MARMALADE */
                if(fileName.empty())
                    continue;
                // Skip special file names - also dotfiles
                //if(fileName.compare(".") == 0 || fileName.compare("..") == 0)
                if(fileName[0] == '.' || fileName.compare("fgprivate") == 0)
                    continue;

                // Create the full path to the file - join paths
                fgPath::join(filePath, curDir, fileName);
                fgBool isDir = FG_FALSE;
                fgBool isZip = FG_FALSE;
#if defined(FG_USING_MARMALADE)
                // Check if the path points to a directory
                isDir = (fgBool)s3eFileGetFileInt(filePath.c_str(), S3E_FILE_ISDIR);
#else
                // Check if the path points to a directory
                if(lstat(filePath.c_str(), &fileInfo) < 0)
                    continue;
                isDir = (fgBool)S_ISDIR(fileInfo.st_mode);
#endif /* FG_USING_MARMALADE */
                // Check whether the file points to the zip file
                // Paths within the zip file listing are always recursive - 
                // the appended list will always contain all files within a zip file
                const char *fileExt = fgStrings::stristr(filePath, ".zip");
                if(!fileExt)
                    fileExt = fgStrings::stristr(filePath, ".pk3");
                if(fileExt)
                    isZip = FG_TRUE; // path points to a zip file

                if(recursive) {
                    if(isDir) {
                        // throw the path to a directory onto the stack for next read
                        dirStack.push_back(filePath);
                    } else {
                        // push the path into vector
                        m_fileNames.push_back(filePath);
                    }
                } else {
                    if(!isDir) {
                        // It's not a directory so push it into the list
                        m_fileNames.push_back(fileName);
                    }
                }

                if(isZip && listZipFiles) {
                    internal_readZipFile(fileName, filePath, recursive);
                }

            } // while(readdir/fileListNext)
            curDir.clear();
            fileName.clear();
#if defined(FG_USING_MARMALADE)
            s3eFileListClose(m_fileList);
#else
            closedir(m_curDir);
#endif /* FG_USING_MARMALADE */
        } // while(!dirStack.empty())
    } // for(...) -> split dir path by ';'
    rewind();
    m_isRecursive = recursive;
    if(!m_fileNames.empty())
        return FG_TRUE;
    return FG_FALSE;
}

/*
 * Reads the specified directory content creating
 * a list of file names
 * @param dirPath
 * @param recursive
 * @param listZipFiles
 * @return 
 */
fgBool fgDirent::readDirectory(const char *dirPath,
                               fgBool recursive,
                               fgBool listZipFiles) {
    if(dirPath)
        m_dirPath = dirPath;
    if((dirPath && strlen(dirPath) == 0) || !dirPath) {
#if defined FG_USING_PLATFORM_WINDOWS
        m_dirPath = ".\\";
#else
        m_dirPath = "./";
#endif
    }
    return readDirectory(recursive, listZipFiles);
}

/**
 * Reads the specified directory content creating
 * a list of file names
 * @param dirPath
 * @param recursive
 * @param listZipFiles
 * @return 
 */
fgBool fgDirent::readDirectory(const std::string &dirPath,
                               fgBool recursive,
                               fgBool listZipFiles) {
    if(!dirPath.empty()) {
        m_dirPath = dirPath;
    } else {
#if defined FG_USING_PLATFORM_WINDOWS
        m_dirPath = ".\\";
#else
        m_dirPath = "./";
#endif
    }
    return readDirectory(recursive, listZipFiles);
}

/**
 * Return the next file name
 * @return 
 */
const char *fgDirent::getNextFile(void) {
    if(m_fileIt == m_fileNames.end()) {
        m_fileIt = m_fileNames.begin();
        if(m_fileIt != m_fileNames.end())
            return (*m_fileIt).c_str();
        return NULL;
    }
    m_fileIt++;
    if(m_fileIt == m_fileNames.end())
        return NULL;

    return (*m_fileIt).c_str();
}

/**
 * 
 * @param path
 * @return 
 */
std::string &fgDirent::getNextFilePath(std::string &path) {
    const char *filename = fgDirent::getNextFile();
    path.clear();
    if(filename && !m_isRecursive) {
        // #FIXME - this will cause error if fgDirent was not recursive and
        // did not store file paths by default - if fgDirent was called with
        // many directories to list -> FUBAR :(
        fgPath::join(path, m_dirPath, std::string(filename));
    } else if(filename && m_isRecursive) {
        // with the recursive mode, this array always stores paths (relative)
        path = filename;
    }
    return path;
}

/**
 * 
 * @param output
 * @param basePath
 * @param patterns
 * @param deep
 * @return 
 */
std::string &fgDirent::searchForFile(std::string &output,
                                     const std::string &basePath,
                                     const std::string &patterns,
                                     const fgBool deep) {
    std::string searchPath;
    if(!basePath.empty()) {
        searchPath = basePath;
    } else {
#if defined FG_USING_PLATFORM_WINDOWS
        searchPath = ".\\";
#else
        searchPath = "./";
#endif
    }
    if(searchPath[0] != '.') {
        if(searchPath[0] == '/' || searchPath[0] == '\\')
            searchPath.insert(searchPath.begin(), 1, '.');
        else
            searchPath.insert(0, "./");
    }
    if(searchPath[searchPath.length() - 1] != '/' && searchPath[searchPath.length() - 1] != '\\')
        searchPath.append("/");
    output.clear();
    fgBool stop = FG_FALSE;
    std::string foundPath;
    const char *subPath;
    fgStringVector patternVec;
    fgStrings::split(patterns, ';', patternVec);
    do {
        if(getNextFilePath(foundPath).empty())
            stop = FG_TRUE;
        if(!stop && fgStrings::startsWith(foundPath, searchPath)) {
            subPath = foundPath.c_str() + searchPath.length();
            // If the found subpath contains delimeters - skip if deep trigger is not active
            if(!deep && fgStrings::containsChars(subPath, "/\\"))
                continue;
            if(patternVec.empty())
                output = foundPath;
            for(int i = 0; i < (int)patternVec.size(); i++) {
                std::string &pattern = patternVec[i];
                if(pattern.length()) {
                    const char *filename = fgPath::fileName(subPath);
                    if(pattern[0] == '*') {
                        if(fgStrings::endsWith(filename, (pattern.c_str() + 1), FG_FALSE)) {
                            output = foundPath;
                        }
                    } else if(pattern[pattern.length() - 1] == '*') {
                        std::string _tmp = pattern.substr(0, pattern.length() - 1);
                        if(fgStrings::startsWith(filename, _tmp.c_str(), FG_FALSE)) {
                            output = foundPath;
                        }
                    } else {
                        if(pattern.compare(filename) == 0) {
                            output = foundPath;
                        }
                    }
                } else {
                    output = foundPath;
                }
            }
        }
    } while(!stop && output.empty());
    return output;
}

/*
 * This function rewinds to the beginning the file pointer (in the list)
 */
fgBool fgDirent::rewind(void) {
    m_fileIt = m_fileNames.end();
    if(!m_fileNames.size())
        return FG_FALSE;
    return FG_TRUE;
}

/*
 *
 */
void fgDirent::clearList(void) {
    m_isRecursive = FG_FALSE;
#ifdef FG_USING_MARMALADE
    m_fileList = NULL;
#endif
    m_fileNames.clear_optimised();
    m_fileIt = m_fileNames.end();
}

/*
 *
 */
fgStringVector &fgDirent::getRefFiles(void) {
    return m_fileNames;
}
