/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgZipFile.h
 * Author: vigilant
 *
 * Created on December 24, 2014, 1:23 AM
 */

#ifndef FG_INC_ZIP_FILE
    #define FG_INC_ZIP_FILE
    #define FG_INC_ZIP_FILE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgFileBase.h"

    #if defined(FG_USING_MARMALADE)
        #include "zlib_128/zlib.h"
        #include "zlib_128/contrib/minizip/unzip.h"
        #include "zlib_128/contrib/minizip/zip.h"
    #else
        #include "unzip.h"
        #include "zip.h"        
    #endif /* defined FG_USING_MARMALADE */

namespace fg {
    namespace util {

        /**
         * This is a special  class  wrapper  for  zip/unzip operations based on 
         * MiniZip library (Zlib contrib). Various operations will be available,
         * the most  important ones are  reading the  archive, listing the files
         * and opening the files inside the archive in similar (almost seamless)
         * way as  opening regular files  on a drive.  This  will be achieved by 
         * using special pathnames (eg. data/pack.zip/textures/flag.png).
         * 
         * This class will be using custom build MiniZip static library - latest
         * version available  from git repository.  For now (XII.14) the MiniZip
         * library supports AES encryption, I/O buffering, PKWARE disk spanning.
         * 
         */
        class CZipFile : public fg::util::base::CFile {
        public:
            ///
            typedef fg::util::base::CFile::Mode FileMode;

        public:

            /**
             *
             */
            enum class Mode {
                /* No mode has been specified, illegal (initial) state */
                NONE,
                /* This zip file is opened only for reading - manipulation will 
                 * be similar to a plain file. Any writing operations will fail 
                 */
                READ,
                /* Zip file is opened for extraction, files will be written to
                 * selected location */
                EXTRACT,
                /* Zip file is opened for writing (adding at the end), new files
                 * will be added */
                WRITE,
                /* Zip file is opened for update (similar to writing), new files
                 * can be added, some can be updated */
                UPDATE,
                /* Special mode for creating a new, empty zip file container */
                CREATE
            };

        private:
            /// Used password for decoding the encrypted Zip file
            std::string m_password;
            /// Currently selected file inside of the Zip - relative path
            std::string m_selectedFilePath;
            /// Currently selected output (extraction) path
            std::string m_extractionPath;
            /// This path will point to the zip file location - without the internal
            /// path to the compressed file within the zip.
            std::string m_zipPath;
            /// List/vector with the file paths (relative) in the specified Zip
            CStringVector m_filePaths;
            /// Iterator to the element in the string vector (file paths)
            CStringVector::iterator m_fileItor;
            /// Number (ID) of the currently selected file (in Zip)
            int m_currentFileID;

            /**
             * This union is for structures containing information about the 
             * currently selected/open file inside of the Zip.
             */
            union ZipFileInfo {
                ///
                unz_file_info64 unz64;
                ///
                unz_file_info unz;
                ///
                zip_fileinfo zip;
            } m_zInfo;

            /**
             * This union is for structures containing information about the Zip.
             */
            union ZipGlobalInfo {
                ///
                unz_global_info64 unz64;
                ///
                unz_global_info unz;
            } m_zGlobalInfo;

            /**
             * 
             */
            union ZipFilePos {
                ///
                unz64_file_pos unz64;
                ///
                unz_file_pos unz;
            } m_zFilePos;
            /// Special zip handle used when creating the new archive (MiniZip)
            zipFile m_zf;
            /// Special zip handle used for unzipping (reading) the existing Zip
            unzFile m_uf;
            /// Enumeration for currently selected ZipFile handling mode
            Mode m_mode;

        private:
            /**
             * File selection function for internal use
             * @param id
             * @return 
             */
            fgBool private_selectFile(const int id);
            /**
             * 
             * @return 
             */
            fgBool private_updateCurrentFileInfo(void);
            
        public:
            /**
             * Default empty constructor for the ZipFile
             */
            CZipFile();

            /**
             * 
             * @param filePath
             */
            CZipFile(const char *filePath);

            /**
             * 
             * @param filePath
             */
            CZipFile(const std::string& filePath);

            /**
             * 
             * @param orig
             */
            CZipFile(const CZipFile& orig);

            /**
             * Default virtual destructor for the ZipFile object
             */
            virtual ~CZipFile();

            /******************************************************************/
            
            /**
             * 
             * @param password
             */
            void setPassword(const char *password) {
                if(password)
                    m_password = password;
            }
            /**
             * 
             * @param password
             */
            void setPassword(const std::string& password) {
                m_password = password;
            }
            /**
             * 
             * @return 
             */
            const char *getPasswordStr(void) const {
                return m_password.c_str();
            }
            /**
             * 
             * @return 
             */
            std::string &getPassword(void) {
                return m_password;
            }
            /**
             * 
             * @return 
             */
            std::string const & getPassword(void) const {
                return m_password;
            }
            
            /**
             * Set the file path
             * @param filePath
             */
            virtual void setPath(const char *filePath);
            /**
             * Set the file path
             * @param filePath
             */
            virtual void setPath(const std::string & filePath);
            /**
             * 
             * @param mode
             */
            virtual void setMode(Mode mode) {
                m_mode = mode;
            }
            /**
             * 
             * @return 
             */
            virtual void setMode(FileMode mode);
            /**
             * 
             * @return 
             */
            const char *getCurrentFileStr(void) const {
                return m_selectedFilePath.c_str();
            }
            /**
             * 
             * @return 
             */
            std::string& getCurrentFile(void) {
                return m_selectedFilePath;
            }
            /**
             * 
             * @return 
             */
            std::string const & getCurrentFile(void) const {
                return m_selectedFilePath;
            }
            /**
             * 
             * @return 
             */
            const char *getZipPathStr(void) const {
                return m_selectedFilePath.c_str();
            }
            /**
             * 
             * @return 
             */
            std::string& getZipPath(void) {
                return m_selectedFilePath;
            }
            /**
             * 
             * @return 
             */
            std::string const & getZipPath(void) const {
                return m_selectedFilePath;
            }
            /**
             * 
             * @return 
             */
            FileMode getFileMode(void) const {
                return m_modeFlags;
            }
            /**
             * 
             * @return 
             */
            Mode getMode(void) const {
                return m_mode;
            }
            
            /**
             * 
             * @return 
             */
            CStringVector & getFileList(void) {
                return m_filePaths;
            }
            /**
             * 
             * @return 
             */
            CStringVector const & getFileList(void) const {
                return m_filePaths;
            }
            
            /******************************************************************/
            
            /**
             * Check whether currently selected file is a directory
             * @return 
             */
            fgBool isCurrentFileDir(void);
            /**
             * 
             * @return 
             */
            fgBool goToNextFile(void);
            /**
             * 
             * @return 
             */
            fgBool goToPreviousFile(void);
            /**
             * 
             * @return 
             */
            fgBool goToFirstFile(void);

            /******************************************************************/

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
            virtual fgBool selectFile(const char *filePath);
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
            virtual fgBool selectFile(const std::string& filePath);

            /******************************************************************/

            /**
             * Open the ZipFile with already set options
             * @return 
             */
            virtual fgBool open(void);

            /**
             * Open the file with specified mode. This will have different effect,
             * based on the currently set path or selected file inside of the zip.
             * @param mode
             * @return 
             */
            virtual fgBool open(Mode mode);
            /**
             * Open the ZipFile (pointed to by path) with specified mode. 
             * @param filePath
             * @param mode
             * @return 
             */
            virtual fgBool open(const char *filePath, Mode mode);

            /**
             * Open the file with specified mode. It will use currently selected
             * ZipFile/file path. Action really  performed  depends  on the file 
             * path - actually used mode to  open the file may  differ  from the 
             * one passed in the  function.  This  function  is  used mainly for 
             * compatibility and transparency with util::File class. 
             * @param mode
             * @return 
             */
            virtual fgBool open(FileMode mode);
            /**
             * Open the file (pointed to by path)  with  specified  mode. Action
             * performed depends on the file path. Whenever  the  new ZipFile is 
             * opened - the inside structure (file list  with relative paths) is
             * buffered into StringVector.
             * @param filePath
             * @param mode
             * @return 
             */
            virtual fgBool open(const char *filePath, FileMode mode);

            /******************************************************************/

            /**
             * Close the file
             * @return 
             */
            virtual fgBool close(void);

            /**
             * Check if file is currently opened
             * @return 
             */
            virtual fgBool isOpen(void) const;

            /**
             * Check if file exists
             * @return 
             */
            virtual fgBool exists(void);

            /******************************************************************/

            /**
             * This will load the whole file into char *buffer
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual char *load(void);
            /**
             * This will load the whole file into char *buffer
             * @param filePath
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual char *load(const char *filePath);

            /**
             * Read from file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual int read(void *buffer, unsigned int elemsize, unsigned int elemcount);
            /**
             * Read string from the file
             * @param buffer
             * @param maxlen
             * @return 
             */
            virtual char *readString(char *buffer, unsigned int maxlen);
            /**
             * Write to the file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual int write(const void *buffer, unsigned int elemsize, unsigned int elemcount);
            /**
             * Print to the file
             * @param fmt
             * @return 
             */
            virtual int print(const char *fmt, ...);
            /**
             * Put given string into the file
             * @param str
             * @return 
             */
            virtual int puts(const char *str);

            /******************************************************************/

            /**
             * Check is it end of file
             * @return 
             */
            virtual fgBool isEOF(void);
            /**
             * Flush file buffers
             * @return 
             */
            virtual fgBool flush(void);

            /**
             *  Get (read) single character from file
             * @return 
             */
            virtual int getChar(void);
            /**
             * Put (write) single character to file
             * @param c
             * @return 
             */
            virtual int putChar(char c);
            /**
             * Get the file size (in bytes)
             * @return 
             */
            virtual int getSize(void);
            /**
             * Get the current position in the file
             * @return 
             */
            virtual long getPosition(void);

            /**
             * Sets the position in the currently open/selected file
             * @param offset
             * @param whence
             * @return 
             */
            virtual int setPosition(long offset, int whence);

        };
    };
};

    #undef FG_INC_ZIP_FILE_BLOCK
#endif	/* FG_INC_ZIP_FILE */
