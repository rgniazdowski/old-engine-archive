/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_RESOURCE_CONFIG
    #define FG_INC_RESOURCE_CONFIG

    #ifndef FG_INC_CONFIG
        #include "Util/fgConfig.h"
    #endif

    #ifndef FG_INC_RESOURCE
        #include "fgResource.h"
    #endif

typedef unsigned int fgResourceConfigType;

    #define FG_RES_CFG_INVALID              0
    #define FG_RES_CFG_RESOURCE             1
    #define FG_RES_CFG_RESOURCE_GROUP       2

namespace fg {
    namespace resource {

        /*
         * Resource header is used only for config files
         * This will provide fast and handy data
         */
        struct SResourceHeader {
            ///
            fg::CVector<Quality> qualities;
            ///
            fg::CStringVector paths;
            ///
            std::string name;
            ///
            std::string flags;
            ///
            std::string configPath;
            /// Priority of this resource
            ResourcePriority priority;
            /// Quality of the resource
            Quality quality;
            /// Resource type
            ResourceType resType;
            ///
            fgBool isConfig;
            /**
             * 
             */
            SResourceHeader() :
            qualities(),
            paths(),
            name(),
            flags(),
            configPath(),
            priority(ResourcePriority::LOW),
            quality(Quality::UNIVERSAL),
            resType(resource::INVALID),
            isConfig(FG_FALSE) { }
            /**
             * 
             */
            ~SResourceHeader() {
                paths.clear_optimised();
                qualities.clear_optimised();
                name.clear();
                flags.clear();
                configPath.clear();
            }
        };

        /**
         *
         */
        class CResourceConfig : public ::fg::util::CConfig {
        public:
            ///
            typedef CResourceConfig type;
            ///
            typedef ::fg::util::CConfig base_type;
            ///
            typedef std::map<std::string, SResourceHeader> ResourceHeaderMap;
            ///
            typedef ResourceHeaderMap::iterator ResourceHeaderMapItor;

        public:
            /**
             */
            CResourceConfig();
            /**
             * 
             * @param filePath
             */
            CResourceConfig(const char *filePath);
            /**
             * 
             */
            virtual ~CResourceConfig();

            /**
             * 
             * @param filePath
             * @return 
             */
            virtual fgBool load(const char *filePath = NULL);
            /**
             * 
             * @return 
             */
            ResourceType getResourceType(void) const {
                return m_header.resType;
            }
            /**
             * #UNUSED
             * @return 
             */
            fgResourceConfigType getConfigType(void) const {
                return m_cfgType;
            }

            /**
             * #FIXME - UNUSED
             * @return 
             */
            util::SCfgSection *getConfigSection(void);
            /**
             * 
             * @return 
             */
            SResourceHeader &getRefHeader(void) {
                return m_header;
            }
            /**
             * 
             * @param resName
             * @return 
             */
            SResourceHeader &getRefHeader(const char *resName);
            /**
             * 
             * @param resName
             * @return 
             */
            SResourceHeader &getRefHeader(const std::string & resName);
            /**
             * 
             * @return 
             */
            CStringVector &getRefResourceNames(void) {
                return m_resNames;
            }
            /**
             * 
             * @return 
             */
            ResourceHeaderMap &getRefHeaders(void) {
                return m_resources;
            }
            /**
             * 
             * @return 
             */
            CVector<Quality> &getRefQualities(void) {
                return m_header.qualities;
            }
            /**
             * 
             * @return 
             */
            CStringVector &getRefPaths(void) {
                return m_header.paths;
            }
            /**
             * 
             * @return 
             */
            ResourcePriority getPriority(void) const {
                return m_header.priority;
            }
            /**
             * 
             * @return 
             */
            std::string &getName(void) {
                return m_header.name;
            }

        protected:
            /**
             * 
             * @return 
             */
            fgBool parseData(void);

        private:
            ///
            SResourceHeader m_header;
            ///
            CStringVector m_resNames;
            ///
            fgResourceConfigType m_cfgType;
            ///
            ResourceHeaderMap m_resources;
        };
    };
};

#endif /* FG_INC_RESOURCE_CONFIG */

#undef	FG_INC_RESOURCE_CONFIGSAFE_
#define FG_INC_RESOURCE_CONFIGSAFE_
