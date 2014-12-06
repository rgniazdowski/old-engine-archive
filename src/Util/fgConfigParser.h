/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_CONFIG_PARSER
    #define FG_INC_CONFIG_PARSER

    #include "fgStatus.h"
    #include "fgFile.h"

    #include "fgConfigStruct.h"

    // #FIXME - special tag type for config parser !

/**
 *
 */
class fgConfigParser : protected fgFile {
protected:
    /// Loaded file size
    unsigned int m_fileSize;
    /// Data buffer
    char *m_fileBuffer;
    
public:
    /**
     * Default constructor for config parser object
     */
    fgConfigParser();

    /**
     * Default destructor for config parser object
     */
    virtual ~fgConfigParser();

    /**
     * Split section name
     * @param fullSectionName
     * @param sectionName
     * @param subSectionName
     * @return 
     */
    static fgBool splitSectionName(std::string &fullSectionName,
                                   std::string &sectionName,
                                   std::string &subSectionName);

    /**
     * Load config and store all parameters in given section map
     * @param filePath
     * @param sectionMap
     * @return 
     */
    fgBool load(const char *filePath, fgCfgTypes::sectionMap &sectionMap);

    /**
     * Parse data and store parameters in given section map (reference)
     * @param data
     * @param sectionMap
     * @return 
     */
    fgBool parseData(const char *data, fgCfgTypes::sectionMap &sectionMap);

    /**
     * Free all data of the config
     */
    void freeData(void);

    /**
     * Return the file size (in bytes)
     * @return 
     */
    unsigned int getFileSize(void) const {
        return m_fileSize;
    }
    
};

#endif /* FG_INC_CONFIG_PARSER */
