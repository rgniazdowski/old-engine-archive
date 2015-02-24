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
 * File:   fgFile.h
 * Author: vigilant
 *
 * Created on December 27, 2014, 12:51 PM
 */

#ifndef FG_INC_FILE
    #define FG_INC_FILE
    #define FG_INC_FILE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgFileBase.h"
    #include "fgRegularFile.h"
    #include "fgZipFile.h"

namespace fg {
    namespace util {

        /**
         * This is special wrapper for file operations
         * This class contains two objects - RegularFile & ZipFile
         * Selection depends on the selected path
         */
        class CFile : public fg::util::base::CFile {
        public:
            ///
            typedef fg::util::CFile self_type;
            ///
            typedef fg::util::base::CFile base_type;
            ///
            typedef fg::util::CRegularFile::tag_type tag_type;
            ///
            typedef fg::util::base::CFile::Mode Mode;
            ///
            typedef fg::util::base::CFile::Mode FileMode;
            ///
            typedef fg::util::CZipFile::Mode ZipMode;

        private:

            enum DataMode {
                ZIP, REGULAR
            };

        private:
            /// Object for managing Zip files and files within the Zip
            CZipFile m_zip;
            /// Object for managing regular files (plain, on disk/ROM)
            CRegularFile m_regular;
            /// Pointer to the base type, is never NULL
            base_type *m_file;
            /// Current mode in which this object operates on - ZIP or REGULAR
            /// Depends on the selected path - path can point to ZIP or REGULAR
            /// or a REGULAR file inside of a ZIP file.
            DataMode m_mode;

        public:
            /**
             * Default constructor for File object
             */
            CFile();

            /**
             * Constructor for File object with parameter (file path)
             * @param filePath
             */
            CFile(const char *filePath);
            
            /**
             * 
             * @param orig
             */
            CFile(const CFile &orig);

            /**
             * Destructor, closes the file, frees up all buffers
             */
            virtual ~CFile();

            /******************************************************************/
            /**
             * Get the C standard mode for fopen
             * @param mode
             * @return 
             */
            static inline const char *modeStr(Mode mode) {
                return CRegularFile::modeStr(mode);
            }

            /******************************************************************/
            /**
             * Return the file path (C string)
             * @return 
             */
            virtual inline const char *getPath(void) const {
                return m_file->getPath();
            }
            /**
             * Set file open mode
             * @param mode
             */
            virtual inline void setMode(Mode mode) {
                if(m_mode == ZIP)
                    m_zip.setMode(mode);
                else
                    m_regular.setMode(mode);
                m_modeFlags = mode;
            }

            /**
             * Set the file path, this will also determine the internal mode based
             * on the  file selected - path  can  point to both regular file and
             * files inside of the zip archives.
             * @param filePath
             */
            virtual void setPath(const char *filePath);
            /**
             * Set the file path, this will also determine the internal mode based
             * on the  file selected - path  can  point to both regular file and
             * files inside of the zip archives.
             * @param filePath
             */
            virtual void setPath(const std::string & filePath);

            /******************************************************************/

            using fg::util::base::CFile::open;
            /**
             * Open the file with already set options
             * @return 
             */
            virtual inline fgBool open(void) {
                return m_file->open();
            }
            /**
             * Open the file with specified mode
             * @param mode
             * @return 
             */
            virtual inline fgBool open(Mode mode) {
                m_modeFlags = mode;
                return m_file->open(mode);
            }
            /**
             * Open the file (pointed to by path) with specified mode
             * @param filePath
             * @param mode
             * @return 
             */
            virtual inline fgBool open(const char *filePath, Mode mode) {
                if(!filePath)
                    return FG_FALSE;
                this->setPath(filePath);
                m_modeFlags = mode;
                return m_file->open(mode);
            }

            /******************************************************************/
            /**
             * Close the file
             * @return 
             */
            virtual inline fgBool close(void) {
                return m_file->close();
            }
            /**
             * Check if file is currently opened
             * @return 
             */
            virtual inline fgBool isOpen(void) const {
                return m_file->isOpen();
            }

            /**
             * Check if file exists
             * @return 
             */
            virtual inline fgBool exists(void) {
                return m_file->exists();
            }

            /******************************************************************/

            using fg::util::base::CFile::load;
            /**
             * This will load the whole file into char *buffer
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual inline char *load(void) {
                return m_file->load();
            }

            /**
             * This will load the whole file into char *buffer
             * @param filePath
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual char *load(const char *filePath) {
                if(!filePath)
                    return FG_FALSE;
                this->setPath(filePath);
                return m_file->load(filePath);
            }
            /**
             * Read from file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual inline int read(void *buffer, unsigned int elemsize, unsigned int elemcount) {
                return m_file->read(buffer, elemsize, elemcount);
            }
            /**
             * Read string from the file
             * @param buffer
             * @param maxlen
             * @return 
             */
            virtual inline char *readString(char *buffer, unsigned int maxlen) {
                return m_file->readString(buffer, maxlen);
            }
            /**
             * Write to the file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual inline int write(void *buffer, unsigned int elemsize, unsigned int elemcount) {
                return m_file->write(buffer, elemsize, elemcount);
            }
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
            virtual inline int puts(const char *str) {
                return m_file->puts(str);
            }

            /******************************************************************/
            /**
             * Check is it end of file
             * @return 
             */
            virtual inline fgBool isEOF(void) {
                return m_file->isEOF();
            }
            /**
             * Flush file buffers
             * @return 
             */
            virtual inline fgBool flush(void) {
                return m_file->flush();
            }
            /**
             *  Get (read) single character from file
             * @return 
             */
            virtual inline int getChar(void) {
                return m_file->getChar();
            }
            /**
             * Put (write) single character to file
             * @param c
             * @return 
             */
            virtual inline int putChar(char c) {
                return m_file->putChar(c);
            }
            /**
             * Get the file size (in bytes)
             * @return 
             */
            virtual inline int getSize(void) {
                return m_file->getSize();
            }
            /**
             * Get the current position in the file
             * @return 
             */
            virtual inline long getPosition(void) {
                return m_file->getPosition();
            }
            /**
             * Sets the position in the currently open/selected file
             * @param offset
             * @param whence
             * @return 
             */
            virtual inline int setPosition(long offset, int whence) {
                return m_file->setPosition(offset, whence);
            }
            
            /**
             * Return the stdio FILE standard pointer
             * @return 
             */
            FILE *getFilePtr(void) const {
                return m_regular.getFilePtr();
            }
        };

        /// The higher file class alias - data file
        typedef CFile DataFile;
    };
};

    #undef FG_INC_FILE_BLOCK
#endif	/* FG_INC_FILE */
