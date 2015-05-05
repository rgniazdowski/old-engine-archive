/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_CONFIG_WRITER
    #define FG_INC_CONFIG_WRITER
    #define FG_INC_CONFIG_WRITER_BLOCK

    #include "fgFile.h"

    #include "fgConfigStruct.h"

namespace fg {
    namespace util {

        /**
         * 
         */
        class CConfigWriter : protected DataFile {
        protected:
        public:
            /**
             * 
             */
            CConfigWriter();
            /**
             * 
             */
            virtual ~CConfigWriter();

            /**
             * 
             * @param filePath
             * @param sectionMap
             * @return 
             */
            fgBool save(const char *filePath, config::SectionMap &sectionMap);
        };
    };
};

    #undef FG_INC_CONFIG_WRITER_BLOCK
#endif /* FG_INC_CONFIG_WRITER */
