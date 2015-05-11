/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_STYLE_MANAGER
    #define FG_INC_GUI_STYLE_MANAGER
    #define FG_INC_GUI_STYLE_MANAGER_BLOCK

    #include "Resource/fgDataManagerBase.h"
    #include "fgGuiStyle.h"

    #define FG_MANAGER_GUI_STYLE    0x00000040

namespace fg {
    namespace gui {

        /**
         *
         */
        class CStyleManager : public fg::resource::CDataManagerBase<CStyle*, StyleHandle, StyleTag> {
        public:
            ///
            typedef CStyleManager self_type;
            ///
            typedef CStyleManager type;
            ///
            typedef CDataManagerBase<CStyle*, StyleHandle, StyleTag> base_type;

        protected:
            ///
            typedef DataVec StyleVec;
            ///
            typedef DataVecItor StyleVecItor;

        public:
            /**
             * 
             */
            CStyleManager();
            /**
             * 
             */
            virtual ~CStyleManager();

        protected:
            /**
             * 
             */
            virtual void clear(void);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

            /**
             * 
             * @param pStyle
             * @param nameTag
             * @return 
             */
            virtual fgBool insert(CStyle *pStyle, const std::string& nameTag);
            /**
             * 
             * @param shUniqueID
             * @param pStyle
             * @return 
             */
            virtual fgBool insertStyle(CStyle *pStyle);

            /**
             * 
             * @param info
             * @return 
             */
            virtual CStyle* request(const std::string& info);
            /**
             * 
             * @param info
             * @return 
             */
            virtual CStyle* request(const char *info);

            /**
             * 
             * @param path
             */
            void setStylesPath(const std::string &path);
            /**
             * 
             * @param path
             */
            void setStylesPath(const char *path);

        private:
            /// Current path to GUIs style path
            std::string m_stylesPath;
        };
    };
};

    #undef FG_INC_GUI_STYLE_MANAGER_BLOCK
#endif /* FG_INC_GUI_STYLE_MANAGER */
