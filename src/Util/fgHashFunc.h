/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 ******************************************************************************/
/* 
 * File:   fgHashFunc.h
 * Author: vigilant
 *
 * Created on November 7, 2014, 7:29 AM
 */

#ifndef FG_INC_HASHFUNC
    #define FG_INC_HASHFUNC
    #define FG_INC_HASHFUNC_BLOCK

    #include <string>

namespace fg {
    namespace util {

        namespace hash {
            typedef unsigned int return_type;
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int RS(const std::string& str) {
                if(str.empty())
                    return 0;
                return RS(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int JS(const std::string& str) {
                if(str.empty())
                    return 0;
                return JS(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int PJW(const std::string& str) {
                if(str.empty())
                    return 0;
                return PJW(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int ELF(const std::string& str) {
                if(str.empty())
                    return 0;
                return ELF(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int BKDR(const std::string& str) {
                if(str.empty())
                    return 0;
                return BKDR(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int SDBM(const std::string& str) {
                if(str.empty())
                    return 0;
                return SDBM(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int DJB(const std::string& str) {
                if(str.empty())
                    return 0;
                return DJB(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int DEK(const std::string& str) {
                if(str.empty())
                    return 0;
                return DEK(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int BP(const std::string& str) {
                if(str.empty())
                    return 0;
                return BP(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int FNV(const std::string& str) {
                if(str.empty())
                    return 0;
                return FNV(str.c_str());
            }
            /**
             *
             * @param str
             * @return
             */
            inline unsigned int AP(const std::string& str) {
                if(str.empty())
                    return 0;
                return AP(str.c_str());
            }

            ////////////////////////////////////////////////////////////////////////////

            /**
             *
             * @param str
             * @return
             */
            unsigned int RS(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int JS(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int PJW(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int ELF(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int BKDR(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int SDBM(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int DJB(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int DEK(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int BP(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int FNV(const char *str);
            /**
             *
             * @param str
             * @return
             */
            unsigned int AP(const char *str);
        } // namespace hash
    } // namespace util
} // namespace fg

    #undef FG_INC_HASHFUNC_BLOCK
#endif	/* FG_INC_HASHFUNC */
