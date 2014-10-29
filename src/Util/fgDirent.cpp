/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgDirent.h"
#include "fgPath.h"
#include "fgStrings.h"

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

/*
 * Reads the directory content creating a list
 * with file names in it
 */
fgBool fgDirent::readDirectory(fgBool recursive) {
#ifdef FG_USING_MARMALADE
    m_fileList = NULL;
#else
    m_curDir = NULL;
    m_curEntry = NULL;
#endif
    m_fileNames.clear_optimised();
    fgStringVector dirStack;
    std::string fileName;
    dirStack.push_back(m_dirPath);
    do {
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
        if(!m_curDir)
            continue;

        while((m_curEntry = readdir(m_curDir)) != NULL) {
            fileName = m_curEntry->d_name;
#endif
            if(fileName.compare(".") == 0 || fileName.compare("..") == 0)
                continue;
            if(recursive) {
                fgPath::join(filePath, curDir, fileName);
                printf("%s\n", filePath.c_str());
                fgBool isDir = FG_FALSE;
#if defined(FG_USING_MARMALADE)
                isDir = (fgBool)s3eFileGetFileInt(filePath.c_str(), S3E_FILE_ISDIR);
#else
                if(lstat(filePath.c_str(), &fileInfo) < 0)
                    continue;
                isDir = (fgBool)S_ISDIR(fileInfo.st_mode);
#endif
                if(isDir) {
                    dirStack.push_back(filePath);
                } else {
                    m_fileNames.push_back(filePath);
                }
            } else {
                m_fileNames.push_back(fileName);
                printf("%s\n", fileName.c_str());
            }
        }
        curDir.clear();
        fileName.clear();
#if defined(FG_USING_MARMALADE)
        s3eFileListClose(m_fileList);
#else
        closedir(m_curDir);
#endif
    } while(!dirStack.empty());
    rewind();
    m_isRecursive = recursive;
    if(!m_fileNames.empty())
        return FG_TRUE;
    return FG_FALSE;
}

/*
 * Reads the specified directory content creating
 * a list of file names
 */
fgBool fgDirent::readDirectory(const char *dirPath, fgBool recursive) {
    if(dirPath)
        m_dirPath = dirPath;
    if((dirPath && strlen(dirPath) == 0) || !dirPath) {
#if defined FG_USING_PLATFORM_WINDOWS
        m_dirPath = ".\\";
#else
        m_dirPath = "./";
#endif
    }
    return readDirectory(recursive);
}

/*
 * Reads the specified directory content creating
 * a list of file names
 */
fgBool fgDirent::readDirectory(const std::string &dirPath, fgBool recursive) {
    if(!dirPath.empty()) {
        m_dirPath = dirPath;
    } else {
#if defined FG_USING_PLATFORM_WINDOWS
        m_dirPath = ".\\";
#else
        m_dirPath = "./";
#endif
    }
    return readDirectory(recursive);
}

/*
 * Return the next file name
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

/*
 */
std::string &fgDirent::getNextFilePath(std::string &path) {
    const char *filename = fgDirent::getNextFile();
    path.clear();
    if(filename && !m_isRecursive) {
        fgPath::join(path, m_dirPath, std::string(filename));
    } else if(filename && m_isRecursive) {
        // with the recursive mode, this array always stores paths (relative)
        path = filename;
    }
    return path;
}

/*
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
            if(!deep && fgStrings::contains(subPath, "/\\"))
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
