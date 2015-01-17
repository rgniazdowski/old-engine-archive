/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MESSAGE_SUBSYSTEM
    #define FG_INC_MESSAGE_SUBSYSTEM
    #define FG_INC_MESSAGE_SUBSYSTEM_BLOCK

    #include "fgCommon.h" 
    #include "fgSingleton.h"
    #include "fgStatus.h"
    #include "fgManagerBase.h"

    #include <stack>    
    #include "fgVector.h"
    #include "Util/fgRegularFile.h"

    #include "fgLog.h" 

namespace fg {
    namespace msg {

        /**
         *
         */
        class CMessageSubsystem : protected base::CManager, public CSingleton<CMessageSubsystem> {
            friend class CSingleton<CMessageSubsystem>;

        public:
            ///
            typedef base::CManager base_type;

        protected:
            ///
            typedef CVector<SStatus *> StatusVec;
            ///
            typedef StatusVec::iterator StatusVecItor;

        protected:
            /**
             * 
             */
            CMessageSubsystem();
            /**
             * 
             */
            virtual ~CMessageSubsystem();

        public:
            /**
             * 
             * @return 
             */
            fgBool initialize(void);
            /**
             * 
             */
            void clear(void);
            /**
             * 
             * @return 
             */
            fgBool destroy(void);

            /**
             * 
             * @param pathAll
             * @param pathError
             * @param pathDebug
             */
            void setLogPaths(const char *pathAll,
                             const char *pathError,
                             const char *pathDebug);
            /**
             * 
             * @param pathAll
             */
            void setLogAllPath(const char *pathAll);
            /**
             * 
             * @param pathError
             */
            void setLogErrorPath(const char *pathError);
            /**
             * 
             * @param pathDebug
             */
            void setLogDebugPath(const char *pathDebug);
            /**
             * 
             */
            void flushAll(void);

            /**
             * 
             * @param msg
             * @return 
             */
            fgBool pushMessage(SMessage *msg);
            /**
             * 
             * @param status
             * @return 
             */
            fgBool pushStatus(SStatus *status);

            /**
             * 
             * @return 
             */
            SStatus *getLastStatus(void);
            /**
             * 
             * @return 
             */
            SMessage *getLastMessage(void);
            /**
             * 
             * @return 
             */
            StatusVec const & getStatusVec(void) const {
                return m_statusVec;
            }

            /**
             * 
             * @param tagName
             * @param code
             * @param fmt     
             */
            void reportSuccess(const char *tagName,
                               int code = FG_ERRNO_OK,
                               const char *fmt = NULL, ...);
            /**
             * 
             * @param tagName
             * @param code
             * @param fmt     
             */
            void reportWarning(const char *tagName,
                               int code = FG_ERRNO_OK,
                               const char *fmt = NULL, ...);
            /**
             * 
             * @param tagName
             * @param code
             * @param fmt     
             */
            void reportError(const char *tagName,
                             int code = FG_ERRNO_OK,
                             const char *fmt = NULL, ...);
            /**
             * 
             * @param tagName
             * @param code
             * @param fmt     
             */
            void reportDebug(const char *tagName,
                             int code = FG_ERRNO_OK,
                             const char *fmt = NULL, ...);

        protected:
            /// Special vector containing pushed statuses
            StatusVec m_statusVec;
            /// File entry for logging all messages
            util::CRegularFile m_logAll;
            /// File entry for logging error messages
            util::CRegularFile m_logError;
            /// File entry for logging only debug messages
            util::CRegularFile m_logDebug;
        };
    };
};

// #FIXME - here we go again with the singletons... :)
    #define FG_MessageSubsystem fg::msg::CMessageSubsystem::getInstance()

    #undef FG_INC_MESSAGE_SUBSYSTEM_BLOCK
#endif /* FG_INC_MESSAGE_SUBSYSTEM */
