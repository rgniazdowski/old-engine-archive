/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgPath.h"
#include "fgCommon.h"
#include "fgMemory.h"

/**
 * 
 * @param path
 * @param fullExt
 * @return 
 */
const char *fg::path::fileExt(const char *path, fgBool fullExt) {
    if(!path) return NULL;
    path = fg::path::fileName(path);
    const char *dot = NULL;
    if(fullExt == FG_TRUE)
        dot = strchr(path, '.');
    else
        dot = strrchr(path, '.');
    if(!dot || dot == path) return NULL;
    return dot + 1;
}

/**
 * 
 * @param path
 * @return 
 */
const char* fg::path::fileName(const char* path) {
    if(!path)
        return NULL;
    return (strrchr(path, '/') ? strrchr(path, '/') + 1 : strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path);
}

/**
 * 
 * @param path
 */
void fg::path::dirName(char *path) {
    const char* filename = fg::path::fileName(path);
    if(!filename)
        return;
    int npath = strlen(path);
    int nfile = strlen(filename);
    int pos = npath - nfile;
    for(int i = pos; i < npath; i++)
        path[i] = 0;
}

/**
 * 
 * @param path
 * @return 
 */
char *fg::path::dirName(const char *path) {
    const char* filename = fg::path::fileName(path);
    if(!filename)
        return NULL;
    int npath = strlen(path);
    int nfile = strlen(filename);
    int newlen = npath - nfile;
    char *buf = fgMalloc<char>(newlen + 1);
    strncpy(buf, path, newlen);
    buf[newlen] = 0;
    return buf;
}

/**
 * 
 * @param path
 * @return 
 */
std::string fg::path::dirName(std::string &path) {
    const char* filename = fg::path::fileName(path.c_str());
    if(!filename)
        return path;
    return path.substr(0, path.length() - strlen(filename));
}

/**
 * 
 * @param path
 * @param dirpath
 * @return 
 */
std::string& fg::path::dirName(std::string &path, std::string &dirpath) {
    dirpath = dirName(path);
    return dirpath;
}

/**
 * 
 * @param path
 * @param dirpath
 * @param filename
 */
void fg::path::split(std::string &path, std::string &dirpath, std::string &filename) {
    dirpath = dirName(path);
    const char* filename_c = fg::path::fileName(path.c_str());
    if(!filename_c)
        filename.clear();
    else
        filename = filename_c;
}

/**
 * 
 * @param path
 * @param dirpath
 * @param filename
 * @return 
 */
std::string& fg::path::join(std::string &path,
                            const std::string &dirpath, 
                            const std::string &filename) {
    // path - here is the result stored

    int dirlen = (int)dirpath.length();
    int filelen = (int)filename.length();
    path = dirpath;
    if(path[dirlen - 1] == FG_PATH_DELIMC || path[dirlen - 1] == FG_PATH_DELIM2C)
        path[dirlen - 1] = FG_PATH_DELIMC;
    else if(dirlen)
        path.append(FG_PATH_DELIM);
    path.append(filename);
    return path;
}

/**
 * 
 * @param dirpath
 * @param filename
 * @return 
 */
std::string fg::path::join(const std::string &dirpath, const std::string &filename) {
    std::string path;
    fg::path::join(path, dirpath, filename);
    return path;
}

/**
 * 
 * @param path
 * @param parts
 */
void fg::path::join(std::string &path, CStringVector &parts) { }
