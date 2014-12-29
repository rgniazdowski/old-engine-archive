/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_CONFIG_WRITER
    #define FG_INC_CONFIG_WRITER

    #include "fgFile.h"

    #include "fgConfigStruct.h"

class fgConfigWriter : protected fg::util::DataFile {
protected:
public:
    fgConfigWriter();
    virtual ~fgConfigWriter();

    fgBool save(const char *filePath, fgCfgTypes::sectionMap &sectionMap);
};

#endif /* FG_INC_CONFIG_WRITER */
