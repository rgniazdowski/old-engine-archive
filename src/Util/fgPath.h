/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PATH
    #define FG_INC_PATH
    #define FG_INC_PATH_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include "fgVector.h"
    #include <string>

    #if defined( FG_USING_PLATFORM_WINDOWS)
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

namespace fg {
    namespace path {
        
        const char * const DELIMITER = FG_PATH_DELIM;
        const char DELIMITER_CHAR = FG_PATH_DELIMC;

        /**
         * This will return path to the root of assets directory (data)
         * 
         * @return  On android this function will return empty string
         *          On linux and windows returns relative path to the current directory
         */
        const char* getAssetsPath(void);

        /**
         *
         * @param newPath
         * @return
         */
        fgBool changeCurrentWorkingDir(const char *newPath);
        /**
         * 
         * @param newPath
         * @return 
         */
        fgBool changeCurrentWorkingDir(const std::string& newPath);

        /**
         *
         * @param buffer
         * @param maxlen
         * @return
         */
        char* getCurrentWorkingPath(char* buffer, size_t maxlen);

        /**
         *
         * @return
         */
        std::string getCurrentWorkingPath(void);

        /**
         * 
         * @param output_path
         */
        void getCurrentWorkingPath(std::string& output_path);

        /**
         * Return the file extension //fgPath::fileExt
         * @param path
         * @param fullExt
         * @return 
         */
        const char* fileExt(const char *path, fgBool fullExt = FG_FALSE);

        /**
         * Return the file name in path //fgPath::fileName
         * @param path
         * @return 
         */
        const char* fileName(const char* path);

        /**
         * Retrieve the dirname in path - this will change the input string (fill last part with \0)
         * @param path
         */
        void dirName(char* path);
        
        /**
         * Retrieve the dirname in path - remember that this function allocates a new string
         * @param path
         * @return 
         */
        char *dirName(const char* path);

        /**
         * 
         * @param path
         * @return 
         */
        std::string dirName(std::string &path);
        
        /**
         * 
         * @param path
         * @param dir
         * @return 
         */
        std::string& dirName(std::string &path, std::string &dir);

        /**
         * Split the path and save parts (dirname, filename) in input parameters
         * @param path
         * @param dirpath
         * @param filename
         */
        void split(std::string &path, std::string &dirpath, std::string &filename);

        /**
         * Join the path elements
         * @param path
         * @param dirpath
         * @param filename
         * @return 
         */
        std::string& join(std::string &path, const std::string &dirpath, const std::string &filename);
        /**
         * 
         * @param dirpath
         * @param filename
         * @return 
         */
        std::string join(const std::string &dirpath, const std::string &filename);

        // Join the path from parts
        void join(std::string &path, CStringVector &parts);
    };
};

    #undef FG_INC_PATH_BLOCK
#endif /* FG_INC_PATH */
