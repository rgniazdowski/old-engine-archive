/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_STATUS
    #define FG_INC_STATUS
    #define FG_INC_STATUS_BLOCK

    #include "fgTypes.h"
    #include "fgErrno.h"
    #include "fgMessageCommon.h"
    #include "Util/fgTime.h"

    #include <cstdarg>

namespace fg {
    namespace msg {

        /*
         * Simple structure for returning more complex info.
         * It will store value similar to bool (to indicate error/success,
         * false/true status). Additionally there is a pointer to message 
         * structure holding error/message code and text.
         * Without code or text message the message structure will not be allocated.
         *
         * If status is managed it means that the pointer is held also in message subsystem,
         * so in status reporter the object should not be deleted (when clearing stack).
         */
        struct SStatus {
            /// Bit mask for holding status (success, error, warning)
            unsigned char mask;
            /// Message - contains indicator code (error code, etc.) and message text.
            SMessage *message;
            ///  Error code
            int errCode;
            // Timestamp (seconds)
            long timestamp;
            /**
             * 
             */
            SStatus() : mask(0), message(NULL), errCode(FG_ERRNO_OK) {
                timestamp = timesys::seconds();
            }
            /**
             * 
             * @param msg
             */
            SStatus(SMessage *msg) : mask(0), errCode(FG_ERRNO_OK) {
                mask = FG_SUCCESS;
                if(msg) {
                    errCode = msg->code();
                    if(msg->type == MSG_INFO)
                        mask = FG_SUCCESS;
                    else if(msg->type == MSG_WARNING || msg->type == MSG_DEBUG)
                        mask = FG_WARNING;
                    else if(msg->type == MSG_ERROR)
                        mask = FG_ERROR;
                }
                timestamp = timesys::seconds();
                message = msg;
            }

            // Default destructor
            ~SStatus() {
                message = NULL;
                // Do not free *message
                // overloaded assignment operators in fgStatus and fgMessage
                // take care of it (it's taking over the ownership)
                // Message from source will be cleared
            }

            // Assignment operator. If source has message allocated it will be
            // taken over by this fgStatus structure. Pointer in source will be deleted.
            // #FIXME - this wont be needed (I think) - need further testing
            //fgStatus& operator= (fgStatus source)
            //{
            //	if(this == &source)
            //		return *this;
            //	printf("fgStatus operator = with code %d | message: '%s'\n", source.code(), fgErrno::strError(source.errCode));
            //	errCode = source.errCode;
            //	mask = source.mask;
            //	isManaged = source.isManaged;
            //	if(source.message && !message) {
            //		message = new fgMessage();
            //		*message = *source.message;
            //		if(!source.isManaged) // #FIXME #ERROR possible
            //			source.clearMessage();
            //		//message = source.message;
            //	} else if(source.message) {
            //		*message = *source.message;
            //		if(!source.isManaged) // #FIXME #ERROR possible
            //			source.clearMessage();
            //	}
            //	else {
            //		message = NULL;
            //	}

            //	return *this;
            //}

            // Clear message contents (delete)
            void clearMessage(void) {
                if(message) {
                    delete message;
                    message = NULL;
                }
            }
            int code(void) const {
                if(message) {
                    return message->code();
                }
                return errCode;
            }
            fgBool hasMessage(void) const {
                if(message)
                    return FG_TRUE;
                return FG_FALSE;
            }

            // True if current status is success
            fgBool isSuccess(void) {
                return (fgBool)(mask == FG_SUCCESS);
            }

            // Check whether current status is warning (message)
            fgBool isWarning(void) {
                return (fgBool)(mask == FG_WARNING);
            }

            // Check whether current status is error
            fgBool isError(void) {
                return (fgBool)(mask == FG_ERROR);
            }

            // Set code for the current status (in message).
            // If message is NULL, it'll be allocated with new.
            SStatus *setCode(int _code = FG_ERRNO_OK) {
                if(message) {
                    message->setCode(_code);
                }
                errCode = _code;
                return this;
            }
            SStatus *setupMessage(MessageType _type = MSG_INFO, int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
                const char *msgData = NULL;
                char buf[BUFFER_MAX];
                if(fmt) {
                    va_list args;
                    va_start(args, fmt);
                    vsprintf(buf, fmt, args);
                    va_end(args);
                    msgData = buf;
                }
                switch(_type) {
                    case MSG_INFO:
                        mask = FG_SUCCESS;
                        break;
                    case MSG_WARNING:
                    case MSG_DEBUG:
                        mask = FG_WARNING;
                        break;
                    case MSG_ERROR:
                        mask = FG_ERROR;
                        break;
                    default:
                        break;
                };

                if(msgData) {
                    if(!message) {
                        message = new SMessage(_type, msgData);
                    } else {
                        message->data = msgData;
                        message->type = _type;
                    }
                }
                setCode(_code);
                timestamp = timesys::seconds();
                return this;
            }

            // Create (initialize) and return status with success.
            // If message (text) is passed  (not NULL) the message
            // struct will be initialized.
            SStatus *success(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
                const char *msgData = NULL;
                char buf[BUFFER_MAX];
                if(fmt) {
                    va_list args;
                    va_start(args, fmt);
                    vsprintf(buf, fmt, args);
                    va_end(args);
                    msgData = buf;
                }
                // #TODO - use va_args, message format string, sprintf, etc
                return setupMessage(MSG_INFO, _code, msgData);
            }

            // Create (initialize) and return status with warning.
            // If message (text) is passed  (not NULL) the message
            // struct will be initialized.
            SStatus *warning(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
                const char *msgData = NULL;
                char buf[BUFFER_MAX];
                if(fmt) {
                    va_list args;
                    va_start(args, fmt);
                    vsprintf(buf, fmt, args);
                    va_end(args);
                    msgData = buf;
                }
                return setupMessage(MSG_WARNING, _code, msgData);
            }

            // Create (initialize)  and return status with error.
            // If message (text) is passed (not NULL) the message
            // struct will be initialized.
            SStatus *error(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
                const char *msgData = NULL;
                char buf[BUFFER_MAX];
                if(fmt) {
                    va_list args;
                    va_start(args, fmt);
                    vsprintf(buf, fmt, args);
                    va_end(args);
                    msgData = buf;
                }
                return setupMessage(MSG_ERROR, _code, msgData);
            }

            // Create (initialize) and return debug status - this not an error in most cases.
            // If message (text) is passed (not NULL) the message struct will be initialized.
            SStatus *debug(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
                const char *msgData = NULL;
                char buf[BUFFER_MAX];
                if(fmt) {
                    va_list args;
                    va_start(args, fmt);
                    vsprintf(buf, fmt, args);
                    va_end(args);
                    msgData = buf;
                }
                return setupMessage(MSG_DEBUG, _code, msgData);
            }
            SStatus *setSuccess(void) {
                mask = FG_SUCCESS;
                if(message)
                    message->type = MSG_INFO;
                return this;
            }
            SStatus *setError(void) {
                mask = FG_ERROR;
                if(message)
                    message->type = MSG_ERROR;
                return this;
            }
            SStatus *setWarning(void) {
                mask = FG_WARNING;
                if(message)
                    message->type = MSG_WARNING;
                return this;
            }
            SStatus *setDebug(void) {
                mask = FG_WARNING;
                if(message)
                    message->type = MSG_DEBUG;
                return this;
            }
            void updateTimeStamp(void) {
                timestamp = timesys::seconds();
            }
        };
    };
};

    #undef FG_INC_STATUS_BLOCK
#endif /* FG_INC_STATUS */
