/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/* 
 * File:   fgHashFunc.h
 * Author: vigilant
 *
 * Created on November 7, 2014, 7:29 AM
 */

#ifndef _FG_HASHFUNC_H_
    #define _FG_HASHFUNC_H_
    #define _FG_HASHFUNC_H_BLOCK_

    #include <string>
/**
 * 
 */
class fgHashFunc {
public:
    typedef unsigned int return_type;
private:
    /**
     * 
     */
    fgHashFunc();
    /**
     * 
     * @param orig
     */
    fgHashFunc(const fgHashFunc& orig);
    /**
     * 
     */
    virtual ~fgHashFunc();

public:
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int RS(const std::string& str) {
        if(str.empty())
            return 0;
        return RS(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int JS(const std::string& str) {
        if(str.empty())
            return 0;
        return JS(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int PJW(const std::string& str) {
        if(str.empty())
            return 0;
        return PJW(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int ELF(const std::string& str) {
        if(str.empty())
            return 0;
        return ELF(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int BKDR(const std::string& str) {
        if(str.empty())
            return 0;
        return BKDR(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int SDBM(const std::string& str) {
        if(str.empty())
            return 0;
        return SDBM(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int DJB(const std::string& str) {
        if(str.empty())
            return 0;
        return DJB(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int DEK(const std::string& str) {
        if(str.empty())
            return 0;
        return DEK(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int BP(const std::string& str) {
        if(str.empty())
            return 0;
        return BP(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int FNV(const std::string& str) {
        if(str.empty())
            return 0;
        return FNV(str.c_str());
    }
    /**
     * 
     * @param str
     * @return 
     */
    static inline unsigned int AP(const std::string& str) {
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
    static unsigned int RS(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int JS(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int PJW(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int ELF(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int BKDR(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int SDBM(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int DJB(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int DEK(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int BP(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int FNV(const char *str);
    /**
     * 
     * @param str
     * @return 
     */
    static unsigned int AP(const char *str);
};

    #undef _FG_HASHFUNC_H_BLOCK_
#endif	/* _FG_HASHFUNC_H_ */
