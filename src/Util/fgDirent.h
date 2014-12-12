/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_DIRENT
    #define FG_INC_DIRENT

    #include "fgCommon.h"

    #ifdef FG_USING_MARMALADE
        #include "s3eFile.h"
    #else
        #include <cstdio>
        #include <dirent.h>
        #include <sys/stat.h>
    #endif

// #TODO - need to decide should I use everywhere stl string,
// standard char array or my own wrapper - time will show 
// which will be more crossplatform friendly
    #include <string>

/* WINDOWS/LINUX solution using dirent.h 
DIR *dir;
struct dirent *ent;
if ((dir = opendir ("c:\\src\\")) != NULL) {
  // print all the files and directories within directory
  while ((ent = readdir (dir)) != NULL) {
    printf ("%s\n", ent->d_name);
  }
  closedir (dir);
} else {
  // could not open directory
  perror ("");
  return EXIT_FAILURE;
}
 */

/*
 * Simple class for reading directory contents
 * uses dirent.h which is available for linux and windows
 * Initial version just outputs file names - in the future
 * there will be a specialized structure with all the possible
 * info (like from stat for example)...
 */
class fgDirent {
public:
    // Default empty constructor
    fgDirent();

    // Default constructor with the specified directory path
    // Please note that this constructor will also call the
    // read directory function - however not recursively.
    fgDirent(const char *dirPath);
    fgDirent(const std::string &dirPath);

    // The default deconstructor
    ~fgDirent();

    // Reads the directory that was specified earlier
    // If additional option is specified it will
    // read the directory recursively - the difference is 
    // that now quering for next file in the list will always
    // return the full path to it. The file list will not contain
    // names of the folders (just file paths)
    fgBool readDirectory(fgBool recursive = FG_FALSE);
    // Reads the specified directory creating the list of files
    // to be processed later
    fgBool readDirectory(const char *dirPath, fgBool recursive);
    // Reads the specified directory creating the list of files
    // to be processed later
    fgBool readDirectory(const std::string &dirPath, fgBool recursive = FG_FALSE);

    // Returns the next file name
    const char *getNextFile(void);

    // Returns the path (full) to the next file
    std::string &getNextFilePath(std::string &path);

    // Returns the path to the next file which matches the criteria
    std::string &searchForFile(std::string &output,
                               const std::string &basePath,
                               const std::string &pattern,
                               const fgBool deep = FG_FALSE);

    // Returns all loaded files (directory listing)
    fgStringVector &getRefFiles(void);

    // This function rewinds to the beginning the file pointer (in the list)
    fgBool rewind(void);

    // Clears all the loaded data (file list will be empty)
    void clearList(void);
protected:
    // The whole path to the directory
    std::string m_dirPath;

    // List/vector with the file names in the specified directory #FIXME
    fgStringVector m_fileNames;
    // iterator to the element in the string vector (file path/name)
    fgStringVector::iterator m_fileIt;
    #ifdef FG_USING_MARMALADE
    // Marmalade specific structure for reading directory contents
    s3eFileList *m_fileList;
    #else
    DIR *m_curDir;
    struct dirent *m_curEntry;
    #endif
    fgBool m_isRecursive;
};

#endif