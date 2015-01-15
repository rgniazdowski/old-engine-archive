/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_MESSAGE_COMMON
    #define FG_INC_MESSAGE_COMMON
    #define FG_INC_MESSAGE_COMMON_BLOCK

    #include "fgBool.h"
    #include "fgErrno.h"

namespace fg {
    namespace msg {

        ///
        const unsigned int BUFFER_MAX = 512;
        
        /**
         * Enum for the common message types
         */
        enum MessageType {
            MSG_INVALID = -1,
            MSG_INFO = 0,
            MSG_WARNING = 1,
            MSG_ERROR = 2,
            MSG_DEBUG = 3,
            MSG_NUM_TYPES = 5
        };

        /**
         *
         */
        struct SMessageSubBase {
            ///
            MessageType type;
            ///
            int code;
        };

        /**
         * Structure for the info message
         */
        struct SInfo : SMessageSubBase {
        };

        /**
         * Structure for the warning message
         */
        struct SWarning : SMessageSubBase {
            ///
            fgBool serious;
        };

        /**
         * Structure for the error message
         */
        struct SError : SMessageSubBase {
            ///
            fgBool critical;
        };

        /**
         * Structure for the debug message
         */
        struct SDebug : SMessageSubBase {
            ///
            fgBool critical;
        };

        /**
         * Main structure for any type of message (and message code)
         * When returning this kind of object - via fgStatus struct
         * for example - it should be newly allocated and then 
         * disposed by the function retrieving it. Or it can be thrown
         * onto some kind of stack (message log/history/console)
         */
        struct SMessage {

            union {
                /// The type of the message
                MessageType type;
                /// Info part of the message
                SInfo info;
                /// Warning part of the message
                SWarning warning;
                /// Error part
                SError error;
                /// Debug part (type, code)
                SDebug debug;
            };
            /// Message data (text)
            std::string data;
            /**
             * Default constructor for message object
             */
            SMessage() : type(MSG_INFO) {
                info.code = FG_ERRNO_OK;
                warning.serious = FG_FALSE;
            }
            /**
             * Default destructor for message object
             */
            virtual ~SMessage() {
                data.clear();
            }
            /**
             * 
             * @param _type
             * @param _code
             */
            SMessage(MessageType _type, int _code) : type(_type) {
                info.code = FG_ERRNO_OK;
                warning.serious = FG_FALSE;
            }
            /**
             * 
             * @param _type
             * @param _code
             * @param _critical
             */
            SMessage(MessageType _type, int _code, fgBool _critical) :
            type(_type) {
                info.code = _code;
                warning.serious = _critical; // this will also set similar flag in error/debug - union
            }
            /**
             * 
             * @param _type
             * @param _data
             */
            SMessage(MessageType _type, const char *_data) :
            type(_type) {
                info.code = FG_ERRNO_OK;
                warning.serious = FG_FALSE;
                if(_data)
                    data = _data;
            }
            /**
             * 
             * @param _type
             * @param _data
             * @param _code
             */
            SMessage(MessageType _type, const char *_data, int _code) :
            type(_type) {
                info.code = _code;
                warning.serious = FG_FALSE;
                if(_data)
                    data = _data;
            }
            /**
             * 
             * @param _type
             * @param _data
             * @param _code
             * @param _critical
             */
            SMessage(MessageType _type, const char *_data, int _code, fgBool _critical) :
            type(_type) {
                info.code = _code;
                warning.serious = _critical;
                if(_data)
                    data = _data;
            }
            /**
             * 
             * @param _data
             */
            SMessage(const char *_data) :
            type(MSG_INFO) {
                info.code = FG_ERRNO_OK;
                warning.serious = FG_FALSE;
                if(_data)
                    data = _data;
            }
            /**
             * 
             * @param _data
             * @param _code
             */
            SMessage(const char *_data, int _code) :
            type(MSG_INFO) {
                info.code = _code;
                warning.serious = FG_FALSE;
                if(_data)
                    data = _data;
            }
            /**
             * 
             * @param _data
             * @param _code
             * @param _critical
             */
            SMessage(const char *_data, int _code, fgBool _critical) :
            type(MSG_INFO) {
                info.code = _code;
                warning.serious = _critical;
                if(_data)
                    data = _data;
            }
            /**
             * Set the code for the message (returns pointer to this)
             * @param _code
             * @return 
             */
            SMessage *setCode(int _code) {
                info.code = _code;
                return this;
            }
            /**
             * Get the message code (error code/etc)
             * @return 
             */
            int code(void) const {
                return info.code;
            }
        };
    };
};

    #undef FG_INC_MESSAGE_COMMON_BLOCK
#endif /* FG_INC_MESSAGE_COMMON */
