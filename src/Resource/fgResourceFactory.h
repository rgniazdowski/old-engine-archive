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
    #include "Util/fgAbstractFactory.h"  

namespace fg {
    namespace resource {

        /**
         *
         */
        class CResourceFactory : public util::CAbstractFactory<ResourceType, CResource> {
        public:
            typedef util::CAbstractFactory<ResourceType, CResource> base_type;
            typedef CResourceFactory self_type;
            typedef CResourceFactory type;

        public:
            /**
             * Default empty constructor for Resource Factory object
             */
            CResourceFactory();
            /**
             * Destructor for Resource Factory object
             */
            virtual ~CResourceFactory();

        }; // class CResourceFactory

    } // namespace resource
} // namespace fg

    #undef FG_INC_RESOURCE_FACTORY_BLOCK
#endif /* FG_INC_RESOURCE_FACTORY */
