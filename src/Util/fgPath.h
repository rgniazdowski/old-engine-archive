/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PATH
    #define FG_INC_PATH

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include "fgVector.h"
    #include <string>

    #if defined FG_USING_PLATFORM_WINDOWS
        #define FG_PATH_DELIM "\\"
        #define FG_PATH_DELIMC '\\'
        #define FG_PATH_DELIM2 "/"
        #define FG_PATH_DELIM2C '/'
    #else
        #define FG_PATH_DELIM "/"
        #define FG_PATH_DELIMC '/'
        #define FG_PATH_DELIM2 "\\"
        #define FG_PATH_DELIM2C '\\'
    #endif

class fgPath {
private:
    fgPath() { }
    ~fgPath() { }
public:
    // Return the file extension //fgPath::fileExt
    static const char* fileExt(const char *path, fgBool fullExt = FG_FALSE);

    // Return the file name in path //fgPath::fileName
    static const char* fileName(const char* path);

    // Retrieve the dirname in path - this will change the input string (fill last part with \0)
    static void dirName(char* path);
    // Retrieve the dirname in path - remember that this function allocates a new string
    static char *dirName(const char* path);
    //
    static std::string dirName(std::string &path);
    //
    static std::string& dirName(std::string &path, std::string &dir);

    // Split the path and save parts (dirname, filename) in input parameters
    static void split(std::string &path, std::string &dirpath, std::string &filename);

    // Join the path elements
    static std::string& join(std::string &path, const std::string &dirpath, const std::string &filename);

    static std::string join(const std::string &dirpath, const std::string &filename);

    // Join the path from parts
    static void join(std::string &path, fgStringVector &parts);
};

#endif /* FG_INC_PATH */
