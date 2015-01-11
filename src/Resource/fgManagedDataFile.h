/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MANAGED_DATA_FILE
    #define FG_INC_MANAGED_DATA_FILE
    #define FG_INC_MANAGED_DATA_BLOCK

    #include "fgManagedObject.h"
    #include <map>
    #include <string>

    #define FG_FILE_QUALITY_MAPPING_TEXT "FileQualityMap"

namespace fg {
    namespace resource {

        /**
         * This is the base class for  data  objects  that are meant
         * to be handle in DataManager. It's for data that is loaded
         * from disk/storage. It's  also  designed  to hold multiple 
         * file paths depending  on the  MapKey type.  In most cases
         * the ID refers  to  the used  quality level throughout the 
         * project.  Quality  depends on some  explicit  settings or
         * device hardware  on which the program is being  executed.
         */
        template<typename THandleType, typename TMapKeyType>
        class CManagedDataFile : public CManagedObject<THandleType> {
        public:
            ///
            typedef std::map<TMapKeyType, std::string> fileMapping;
            ///
            typedef typename fileMapping::iterator fileMappingItor;
            ///
            typedef THandleType handle_type;
            ///
            typedef TMapKeyType map_key_type;
            ///
            typedef CManagedObject<THandleType> base_type;

        public:
            /**
             * Default constructor for resource base object
             */
            CManagedDataFile() : m_defaultID((TMapKeyType) - 1) {
                m_filePath.clear();
                m_fileMapping.clear();
            }
            /**
             * Destructor for resource base object
             */
            virtual ~CManagedDataFile() {
                m_filePath.clear();
                m_fileMapping.clear();
            }
        public:
            /**
             * 
             * @param path
             */
            virtual void setFilePath(const char *path) {
                if(!path)
                    return;
                m_filePath = path;
                m_fileMapping[m_defaultID] = path;
            }
            /**
             * Set file path for this data
             * @param path
             */
            virtual void setFilePath(const std::string& path) {
                m_filePath = path;
                m_fileMapping[m_defaultID] = path;
            }
            /**
             * Get reference to data file path string
             * @return 
             */
            inline std::string& getFilePath(void) {
                return m_filePath;
            }
            /**
             * Get reference to data file path string
             * @return 
             */
            inline const std::string& getFilePath(void) const {
                return m_filePath;
            }
            /**
             * Gets data file path 
             * @return  Data file path as C-like string (char array)
             */
            inline const char* getFilePathStr(void) const {
                return m_filePath.c_str();
            }
            /**
             * 
             * @return 
             */
            inline fileMapping& getFileMapping(void) {
                return m_fileMapping;
            }
            /**
             * 
             * @return 
             */
            inline unsigned int getFilesCount(void) const {
                return m_fileMapping.size();
            }
            /**
             * Set file path to this resource
             * @param path
             * @param id
             */
            virtual void setFilePath(const char *path, TMapKeyType id) {
                if(!path)
                    return;
                m_fileMapping[id] = path;
                if(id == m_defaultID)
                    m_filePath = path;
                else if(m_filePath.empty())
                    m_filePath = path;
            }
            /**
             * 
             * @param path
             * @param id
             */
            virtual void setFilePath(std::string& path, TMapKeyType id) {
                m_fileMapping[id] = path;
                if(id == m_defaultID)
                    m_filePath = path;
                else if(m_filePath.empty())
                    m_filePath = path;
            }
            /**
             * 
             * @param id
             * @return 
             */
            inline std::string getFilePath(TMapKeyType id) const {
                // this lazy cast is ok - non-const version does not modify anything
                return (const_cast<CManagedDataFile<THandleType, TMapKeyType>*>(this)->getFilePath(id));
            }
            /**
             * 
             * @param id
             * @return 
             */
            inline std::string& getFilePath(TMapKeyType id) {
                if(m_fileMapping.find(id) == m_fileMapping.end()) {
                    return m_filePath;
                }
                return m_fileMapping[id];
            }
            /**
             * 
             * @param id
             * @return 
             */
            inline const char* getFilePathStr(TMapKeyType id) {
                if(m_fileMapping.find(id) == m_fileMapping.end()) {
                    return m_filePath.c_str();
                }
                return m_fileMapping[id].c_str();
            }
            /**
             * 
             * @param id
             */
            inline void setDefaultID(TMapKeyType id) {
                m_defaultID = id;
            }

        protected:
            /// File mapping
            fileMapping m_fileMapping;
            /// File path as separate string (by default this is for universal quality)
            std::string m_filePath;
            /// Default ID to write to
            TMapKeyType m_defaultID;
        };
    };
};
    #undef FG_INC_MANAGED_DATA_BLOCK
#endif /* FG_INC_MANAGED_DATA */
