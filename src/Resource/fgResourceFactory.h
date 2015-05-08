/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_RESOURCE_FACTORY
    #define FG_INC_RESOURCE_FACTORY
    #define FG_INC_RESOURCE_FACTORY_BLOCK

    #include "fgResource.h"
    #include "fgResourceFactoryTypes.h"

    #include <map>


namespace fg {
    namespace resource {

        /**
         *
         */
        class CResourceFactory {
        public:
            ///
            typedef std::map<ResourceType, CreateResourceFunction> factoryMap;
            ///
            typedef std::pair<ResourceType, CreateResourceFunction> factoryPair;
            ///
            typedef factoryMap::iterator factoryMapItor;
            ///
            typedef factoryMap::const_iterator factoryMapConstItor;

        public:
            /**
             * Default empty constructor for Resource Factory object
             */
            CResourceFactory();
            /**
             * Destructor for Resource Factory object
             */
            virtual ~CResourceFactory();

            /**
             * Clear all registered resource creators
             */
            void clear(void);

            /**
             * Register resource create function based on resource type
             * @param type
             * @param function
             * @return 
             */
            fgBool registerResource(const ResourceType type, CreateResourceFunction function);

            /**
             * Call specific create function for given resource
             * @param type
             * @return 
             */
            CResource* createResource(const ResourceType type);

            /**
             * Check if given resource type constructor/create function is registered in factory
             * @param type
             * @return 
             */
            fgBool isRegistered(const ResourceType type);

        private:
            /// Map storing create functions for given resource types
            factoryMap m_factoryMap;
        };

    };
};
    #undef FG_INC_RESOURCE_FACTORY_BLOCK
#endif /* FG_INC_RESOURCE_FACTORY */
