/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MANAGER_BASE
    #define FG_INC_MANAGER_BASE

    #include "fgBool.h"

typedef unsigned int fgManagerType;

    #define FG_MANAGER_INVALID      0x00000000
    #define FG_MANAGER_BASE         0x00000000

namespace fg {
    namespace base {

        /**
         *
         */
        class CManager {
        public:
            /**
             * 
             */
            CManager() :
            m_init(FG_FALSE),
            m_managerType(FG_MANAGER_INVALID) { }
            /**
             * 
             */
            virtual ~CManager() { }

        protected:
            /**
             * 
             */
            virtual void clear(void) = 0;

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void) = 0;
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void) = 0;
            /**
             * 
             * @return 
             */
            fgManagerType getManagerType(void) const {
                return m_managerType;
            }
            /**
             * 
             * @return 
             */
            fgBool isInit(void) const {
                return m_init;
            }

        protected:
            /// Is manager initialized successfully
            fgBool m_init;
            /// Current manager type (set by the most derived class))
            fgManagerType m_managerType;
        };

    };
};

#endif /* FG_INC_MANAGER_BASE */
