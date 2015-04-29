/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgPath.h"
#include "fgCommon.h"
#include "fgMemory.h"
#include "fgUnistd.h"

using namespace fg;

//------------------------------------------------------------------------------

const char* path::getAssetsPath(void) {
#if defined(FG_USING_PLATFORM_ANDROID)
    return "\0\0";
#elif defined(FG_USING_PLATFORM_WINDOWS)
    return ".\\";
#elif defined(FG_USING_PLATFORM_LINUX)
    return "./";
#endif
}
//------------------------------------------------------------------------------

fgBool path::changeCurrentWorkingDir(const char *newPath) {
    if(!newPath)
        return FG_FALSE;
    return chdir(newPath) < 0 ? FG_FALSE : FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool path::changeCurrentWorkingDir(const std::string& newPath) {
    if(newPath.empty())
        return FG_FALSE;
    return chdir(newPath.c_str()) < 0 ? FG_FALSE : FG_TRUE;
}
//------------------------------------------------------------------------------

char* path::getCurrentWorkingPath(char* buffer, size_t maxlen) {
    if(!buffer)
        return NULL;
    if(maxlen < 8)
        return NULL;
    getcwd(buffer, maxlen);
    return buffer;
}
//------------------------------------------------------------------------------

std::string path::getCurrentWorkingPath(void) {
    std::string curdir;
    getCurrentWorkingPath(curdir);
    return curdir;
}
//------------------------------------------------------------------------------

void path::getCurrentWorkingPath(std::string& output_path){
    output_path.clear();
    char buf[PATH_MAX];
    if(getcwd(buf, PATH_MAX)) {
        output_path.append(buf);
    }
}
//------------------------------------------------------------------------------

const char* path::fileExt(const char* path, fgBool fullExt) {
    if(!path) return NULL;
    path = path::fileName(path);
    const char* dot = NULL;
    if(fullExt == FG_TRUE)
        dot = strchr(path, '.');
    else
        dot = strrchr(path, '.');
    if(!dot || dot == path) return NULL;
    return dot + 1;
}
//------------------------------------------------------------------------------

const char* path::fileName(const char* path) {
    if(!path)
        return NULL;
    return (strrchr(path, '/') ? strrchr(path, '/') + 1 : strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path);
}
//------------------------------------------------------------------------------

void path::dirName(char* path) {
    const char* filename = path::fileName(path);
    if(!filename)
        return;
    int npath = strlen(path);
    int nfile = strlen(filename);
    int pos = npath - nfile;
    for(int i = pos; i < npath; i++)
        path[i] = 0;
}
//------------------------------------------------------------------------------

char* path::dirName(const char* path) {
    const char* filename = path::fileName(path);
    if(!filename)
        return NULL;
    int npath = strlen(path);
    int nfile = strlen(filename);
    int newlen = npath - nfile;
    char* buf = fgMalloc<char>(newlen + 1);
    strncpy(buf, path, newlen);
    buf[newlen] = 0;
    return buf;
}
//------------------------------------------------------------------------------

std::string path::dirName(std::string &path) {
    const char* filename = path::fileName(path.c_str());
    if(!filename)
        return path;
    return path.substr(0, path.length() - strlen(filename));
}
//------------------------------------------------------------------------------

std::string& path::dirName(std::string &path, std::string &dirpath) {
    dirpath = dirName(path);
    return dirpath;
}
//------------------------------------------------------------------------------

void path::split(std::string &path, std::string &dirpath, std::string &filename) {
    dirpath = dirName(path);
    const char* filename_c = path::fileName(path.c_str());
    if(!filename_c)
        filename.clear();
    else
        filename = filename_c;
}
//------------------------------------------------------------------------------

std::string& path::join(std::string &path,
                        const std::string &dirpath,
                        const std::string &filename) {
    // path - here is the result stored

    int dirlen = (int)dirpath.length();
    int filelen = (int)filename.length();
    path = dirpath;
    if(path[dirlen - 1] == FG_PATH_DELIMC || path[dirlen - 1] == FG_PATH_DELIM2C)
        path[dirlen - 1] = FG_PATH_DELIMC;
    else if(dirlen)
        path.append(path::DELIMITER);
    path.append(filename);
    return path;
}
//------------------------------------------------------------------------------

std::string path::join(const std::string &dirpath, const std::string &filename) {
    std::string path;
    path::join(path, dirpath, filename);
    return path;
}
//------------------------------------------------------------------------------

void path::join(std::string &path, CStringVector &parts) { }
//------------------------------------------------------------------------------
