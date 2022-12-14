/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_DIRENT
    #define FG_INC_DIRENT
    #define FG_INC_DIRENT_BLOCK

    #include "fgBuildConfig.h"
    #include "fgTypes.h"

    #if 1
        #include <cstdio>
        #include <dirent.h>
        #include <sys/stat.h>
    #endif

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

namespace fg {
    namespace util {

        /**
         * Simple class for reading directory contents
         * uses dirent.h which is available for linux and windows
         * Initial version just outputs file names - in the future
         * there will be a specialized structure with all the possible
         * info (like from stat for example)...
         * 
         * With special toggle it will also read and list contents of the zip file
         * Header for this class is not in conflict with ZipFile - however there is also
         * no need to include/use Dirent inside of the ZipFile. Dirent uses ZipFile uses
         * ZipFile only internally inside of the read contents function.
         */
        class CDirent {
        public:
            /**
             * Default empty constructor
             */
            CDirent();

            /**
             * Constructor with the specified directory path
             * Please note that this constructor will also call the
             * read directory function - however not recursively.
             * @param dirPath
             * @return 
             */
            CDirent(const char *dirPath);
            /**
             * Constructor with the specified directory path
             * Please note that this constructor will also call the
             * read directory function - however not recursively.
             * @param dirPath
             * @return 
             */
            CDirent(const std::string &dirPath);
            /**
             * Destructor for the Dirent object
             */
            virtual ~CDirent();

        private:
            /**
             * 
             * @param fileName
             * @param filePath
             * @param recursive
             * @return 
             */
            fgBool internal_readZipFile(const std::string& fileName,
                                        const std::string& filePath,
                                        fgBool recursive = FG_FALSE);

        public:

            /**
             * Reads the directory that was specified earlier. If additional option is 
             * specified it will read the directory recursively - the difference is that 
             * now querying for next file in the list will always return the full path 
             * to it. The file list will not contain names of the folders (just file paths)
             * @param recursive
             * @param listZipFiles
             * @return 
             */
            fgBool readDir(fgBool recursive = FG_FALSE,
                           fgBool listZipFiles = FG_FALSE);
            /**
             * Reads the specified directory creating the list of files
             * to be processed later
             * @param dirPath
             * @param recursive
             * @param listZipFiles
             * @return 
             */
            fgBool readDir(const char *dirPath,
                           fgBool recursive,
                           fgBool listZipFiles);
            /**
             * Reads the specified directory creating the list of files
             * to be processed later
             * @param dirPath
             * @param recursive
             * @param listZipFiles
             * @return 
             */
            fgBool readDir(const std::string &dirPath,
                           fgBool recursive = FG_FALSE,
                           fgBool listZipFiles = FG_FALSE);

            /**
             * Returns the next file name
             * @return 
             */
            const char *getNextFile(void);

            /**
             * Returns the path (full) to the next file
             * @param path
             * @return 
             */
            std::string &getNextFilePath(std::string &path);

            /**
             * Returns the path to the next file which matches the criteria
             * @param output
             * @param basePath
             * @param pattern
             * @param deep
             * @return 
             */
            std::string &searchForFile(std::string &output,
                                       const std::string &basePath,
                                       const std::string &pattern,
                                       const fgBool deep = FG_FALSE);

            /**
             * Returns all loaded files (directory listing)
             * @return 
             */
            fg::CStringVector &getRefFiles(void);

            /**
             * This function rewinds to the beginning the file pointer (in the list)
             * @return 
             */
            fgBool rewind(void);

            /**
             * Clears all the loaded data (file list will be empty)
             */
            void clearList(void);

        protected:
            /// The whole path to the directory
            std::string m_dirPath;
            /// List/vector with the file names in the specified directory #FIXME
            fg::CStringVector m_filePaths;
            /// iterator to the element in the string vector (file path/name)
            fg::CStringVector::iterator m_fileIt;

    #if 1
            /// Currently opened directory
            DIR *m_curDir;
            /// Special structure for traversing the directory
            struct dirent *m_curEntry;
    #endif
            /// Was the directory read recursively?
            fgBool m_isRecursive;

        }; // class CDirent
    } // namespace util
} // namespace fg

    #undef FG_INC_DIRENT_BLOCK
#endif /* FG_INC_DIRENT */
