/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgDirent.h"
#include "fgCommon.h" // #FIXME
#include "fgTypes.h"
#include "fgZipFile.h"
#include "fgStrings.h"
#include "fgPath.h"
#include "fgLog.h"
#include "fgRegularFile.h"
#include "fgMemory.h"

using namespace fg;

//------------------------------------------------------------------------------

#if !defined(FG_USING_ANDROID)

void CDirent_loadAssetsListInternal(CStringVector& outputList,
                                    const std::string& relativePath,
                                    fgBool isRecursive) {

    util::CRegularFile assetsListFile;
    outputList.clear();
    ///assetsListFile.open("assets_list", "r");
    char* fileData = assetsListFile.load("assets_list");
    if(!fileData) {
        return;
    }

    std::string dirPath;
    CStringVector dirVec;
    strings::split(relativePath, ';', dirVec);
    int ndirs = dirVec.size();
    std::string fileData2 = fileData;
    CStringVector tmpList;
    strings::split(fileData2, '\n', tmpList);
    int n = tmpList.size();

    for(int idir = 0; idir < ndirs; idir++) {
        dirPath = dirVec[idir];

        std::string relFixedPath;
        unsigned int skip = 0;
        if(dirPath[0] == '.') {
            skip = 1;
            if(dirPath[1] == FG_PATH_DELIMC || dirPath[1] == FG_PATH_DELIM2C)
                skip = 2;
            relFixedPath = dirPath.substr(skip);
        } else {
            relFixedPath = dirPath;
        }
        skip = relFixedPath.length();
        if(skip && relFixedPath[skip - 1] != path::DELIMITER_CHAR) {
            relFixedPath.push_back(path::DELIMITER_CHAR);
            skip++;
        }

        for(int i = 0; i < n; i++) {
            std::string newPath;
            tmpList[i] = strings::trim(tmpList[i]);
            const char *secondPart = NULL;
            fgBool starts = FG_FALSE;
            if(tmpList[i].length() > skip)
                secondPart = tmpList[i].c_str() + skip + 1;
            if((starts = strings::startsWith(tmpList[i], relFixedPath)) || !skip) {
                newPath = tmpList[i];
            }
            if(strings::containsChars(secondPart, "/\\")) {
                if(!isRecursive)
                    newPath.clear();
            }
            if(newPath.length())
                outputList.push_back(newPath);
        }
    }
    fgFree(fileData);
}
#endif

//------------------------------------------------------------------------------
util::CDirent::CDirent() :
m_dirPath(),
m_filePaths(),
m_fileIt(),
#if 1
m_curDir(NULL),
m_curEntry(NULL),
#endif
m_isRecursive(FG_FALSE) {
    m_fileIt = m_filePaths.end();
}

//------------------------------------------------------------------------------
util::CDirent::CDirent(const char *dirPath) {
    m_isRecursive = FG_FALSE;
    readDir(dirPath, FG_FALSE);
}
//------------------------------------------------------------------------------

util::CDirent::CDirent(const std::string &dirPath) {
    m_isRecursive = FG_FALSE;
    readDir(dirPath, FG_FALSE);
}
//------------------------------------------------------------------------------

util::CDirent::~CDirent() {
    m_dirPath.clear();
    m_filePaths.clear_optimised();
}
//------------------------------------------------------------------------------

fgBool util::CDirent::internal_readZipFile(const std::string& fileName,
                                           const std::string& filePath,
                                           fgBool recursive) {
    // If the current file is a zip file and the listing trigger is
    // active - append full zip listing into file names/paths vector
    util::CZipFile zip(filePath);
    zip.open();
    CStringVector &zipFileList = zip.getFileList();
    int nZipFiles = zipFileList.size();
    for(int i = 0; i < nZipFiles; i++) {
        // Need to check here if the path inside of the zip does not
        // point to a directory - such path has a ending delimeter
        std::string filePathInZip;
        // Join the paths
        if(recursive) {
            path::join(filePathInZip, filePath, zipFileList[i]);
        } else {
            path::join(filePathInZip, fileName, zipFileList[i]);
        }
        std::string dirInZipName;
        // If the path has an ending delimeter the dirName function
        // will return the same string - no changes
        path::dirName(filePathInZip, dirInZipName);
        int fn = filePathInZip.size();
        int dn = dirInZipName.size();
        char dc = dirInZipName[dn - 1];
        char fc = filePathInZip[fn - 1];
        // Check whether path has the ending delimeter - it's not so accurate
        if(!(dn == fn && (dc == '/' || dc == '\\') && (fc == '/' || fc == '\\')))
            m_filePaths.push_back(filePathInZip);
    }
    zip.close();
    return (fgBool)(!!nZipFiles);
}
//------------------------------------------------------------------------------

fgBool util::CDirent::readDir(fgBool recursive, fgBool listZipFiles) {
#if 1
    m_curDir = NULL;
    m_curEntry = NULL;
#endif

    m_filePaths.clear_optimised();
#if defined(FG_USING_PLATFORM_ANDROID)
    /* THIS IS ANDROID SPECIFIC CODE - it's a little complicated */
    CStringVector outputList;
    // ANDROID SPECIFIC
    CDirent_loadAssetsListInternal(outputList, m_dirPath, recursive);
    unsigned int n = outputList.size();
    for(unsigned int i = 0; i < n; i++) {
        const std::string& filePath = outputList[i];
        const char *fileExt = strings::stristr(filePath, ".zip");
        if(!fileExt)
            fileExt = strings::stristr(filePath, ".pk3");
        if(fileExt) {
            // file path points to a zip file
            internal_readZipFile(filePath, filePath, FG_FALSE);
        } else {
            m_filePaths.push_back(filePath);
        }
    }
#else /* CODE BELOW IS FOR LINUX / WINDOWS / OSX */
    CStringVector dirStack;
    std::string fileName;
    std::string dirPath;
    CStringVector dirVec;
    strings::split(m_dirPath, ';', dirVec);
    int ndirs = dirVec.size();

    for(int idir = 0; idir < ndirs; idir++) {
        dirPath = dirVec[idir];

        const char *fileExt = strings::stristr(dirPath, ".zip");
        if(!fileExt)
            fileExt = strings::stristr(dirPath, ".pk3");
        if(fileExt) {
            // dir path points to a zip file
            internal_readZipFile(dirPath, dirPath, FG_FALSE);
        } else {
            dirStack.push_back(dirPath);
        }

        ////////////////////////////////////////////////////////////////////////
        /// Go through directory stack
        while(!dirStack.empty()) {
            std::string filePath;
            std::string curDir = dirStack.back();
            dirStack.pop_back();
            FG_LOG_DEBUG("util::dirent: Opening directory for reading: '%s'", curDir.c_str());
#if 1
            struct stat fileInfo;
            m_curDir = opendir(curDir.c_str());
            if(!m_curDir) {
                FG_LOG_DEBUG("util::dirent: Unable to open directory: '%s'", curDir.c_str());
                continue;
            }

            while((m_curEntry = readdir(m_curDir)) != NULL) {
                fileName = m_curEntry->d_name;
#endif
                if(fileName.empty())
                    continue;
                // Skip special file names - also dotfiles
                //if(fileName.compare(".") == 0 || fileName.compare("..") == 0)
                if(fileName[0] == '.' || fileName.compare("fgprivate") == 0)
                    continue;

                // Create the full path to the file - join paths
                path::join(filePath, curDir, fileName);
                fgBool isDir = FG_FALSE;
                fgBool isZip = FG_FALSE;
#if 1
                // Check if the path points to a directory
                if(lstat(filePath.c_str(), &fileInfo) < 0)
                    continue;
                isDir = (fgBool)S_ISDIR(fileInfo.st_mode);
#endif
                // Check whether the file points to the zip file
                // Paths within the zip file listing are always recursive - 
                // the appended list will always contain all files within a zip file
                const char *fileExt = strings::stristr(filePath, ".zip");
                if(!fileExt)
                    fileExt = strings::stristr(filePath, ".pk3");
                if(fileExt)
                    isZip = FG_TRUE; // path points to a zip file

                if(recursive) {
                    if(isDir) {
                        // throw the path to a directory onto the stack for next read
                        dirStack.push_back(filePath);
                    } else {
                        // push the path into vector
                        m_filePaths.push_back(filePath);
                    }
                } else if(!isDir) {
                    // It's not a directory so push it into the list
                    m_filePaths.push_back(filePath);
                }

                if(isZip && listZipFiles) {
                    internal_readZipFile(fileName, filePath, recursive);
                }

            } // while(readdir/fileListNext)
            curDir.clear();
            fileName.clear();
#if 1
            closedir(m_curDir);
#endif
        } // while(!dirStack.empty())
    } // for(...) -> split dir path by ';'
#endif /* FG_USING_PLATFORM_ANDROID */
    rewind();
    m_isRecursive = recursive;
    if(!m_filePaths.empty())
        return FG_TRUE;
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool util::CDirent::readDir(const char *dirPath,
                              fgBool recursive,
                              fgBool listZipFiles) {
    if(dirPath)
        m_dirPath = dirPath;
    if((dirPath && strlen(dirPath) == 0) || !dirPath) {
        m_dirPath = path::getAssetsPath();
    }
    return readDir(recursive, listZipFiles);
}
//------------------------------------------------------------------------------

fgBool util::CDirent::readDir(const std::string &dirPath,
                              fgBool recursive,
                              fgBool listZipFiles) {
    if(!dirPath.empty()) {
        m_dirPath = dirPath;
    } else {
        m_dirPath = path::getAssetsPath();
    }
    return readDir(recursive, listZipFiles);
}
//------------------------------------------------------------------------------

const char *util::CDirent::getNextFile(void) {
    if(m_fileIt == m_filePaths.end()) {
        m_fileIt = m_filePaths.begin();
        if(m_fileIt != m_filePaths.end())
            return (*m_fileIt).c_str();
        return NULL;
    }
    m_fileIt++;
    if(m_fileIt == m_filePaths.end())
        return NULL;

    return (*m_fileIt).c_str();
}
//------------------------------------------------------------------------------

std::string &util::CDirent::getNextFilePath(std::string &path) {
    const char *filename = util::CDirent::getNextFile();
    path.clear();
#if 0
    if(filename && !m_isRecursive) {
        // #FIXME - this will cause error if fgDirent was not recursive and
        // did not store file paths by default - if fgDirent was called with
        // many directories to list -> FUBAR :(
        path::join(path, m_dirPath, std::string(filename));
    } else if(filename && m_isRecursive) {
        // with the recursive mode, this array always stores paths (relative)
        path = filename;
    }
#endif
    if(filename)
        path = filename;
    return path;
}

std::string &util::CDirent::searchForFile(std::string &output,
                                          const std::string &basePath,
                                          const std::string &patterns,
                                          const fgBool deep) {
    std::string searchPath;
    if(!basePath.empty()) {
        searchPath = basePath;
    } else {
        // The default search path
        searchPath = path::getAssetsPath();
    }
#if 0
    if(searchPath[0] != '.') {
        if(searchPath[0] == '/' || searchPath[0] == '\\')
            searchPath.insert(searchPath.begin(), 1, '.');
        else
            searchPath.insert(0, "./");
    }
#endif
#if defined(FG_USING_PLATFORM_ANDROID)
    /* Need to fix this path for android - cannot begin with ./ 
     * also it would be good to move such things to some fg::path::* functions
     * The below part and others are used quite a lot #FIXME #CODEREPEAT
     */
    if(searchPath[0] == '.') {
        int skip = 1;
        if(searchPath[1] == FG_PATH_DELIMC || searchPath[1] == FG_PATH_DELIM2C)
            skip = 2;
        searchPath = searchPath.substr(skip);
    }
#endif /* FG_USING_PLATFORM_ANDROID */
    if(searchPath.length() && searchPath[searchPath.length() - 1] != '/' && searchPath[searchPath.length() - 1] != '\\')
        searchPath.append(path::DELIMITER);
    output.clear();
    fgBool stop = FG_FALSE;
    std::string foundPath;
    const char *subPath;
    CStringVector patternVec;
    strings::split(patterns, ';', patternVec);
    do {
        if(getNextFilePath(foundPath).empty())
            stop = FG_TRUE;
        if(!stop && (strings::startsWith(foundPath, searchPath) || searchPath.empty())) {
            subPath = foundPath.c_str() + searchPath.length();
            // If the found subpath contains delimeters - skip if deep trigger is not active
            if(!deep && strings::containsChars(subPath, "/\\"))
                continue;
            if(patternVec.empty())
                output = foundPath;
            for(int i = 0; i < (int)patternVec.size(); i++) {
                std::string &pattern = patternVec[i];
                if(pattern.length()) {
                    const char *filename = path::fileName(subPath);
                    if(pattern[0] == '*') {
                        if(strings::endsWith(filename, (pattern.c_str() + 1), FG_FALSE)) {
                            output = foundPath;
                        }
                    } else if(pattern[pattern.length() - 1] == '*') {
                        std::string _tmp = pattern.substr(0, pattern.length() - 1);
                        if(strings::startsWith(filename, _tmp.c_str(), FG_FALSE)) {
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
//------------------------------------------------------------------------------

fgBool util::CDirent::rewind(void) {
    m_fileIt = m_filePaths.end();
    if(!m_filePaths.size())
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void util::CDirent::clearList(void) {
    m_isRecursive = FG_FALSE;
    m_filePaths.clear_optimised();
    m_fileIt = m_filePaths.end();
}
//------------------------------------------------------------------------------

CStringVector &util::CDirent::getRefFiles(void) {
    return m_filePaths;
}
//------------------------------------------------------------------------------
