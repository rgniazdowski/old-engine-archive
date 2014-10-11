/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_SINGLETON_H_
#define _FG_SINGLETON_H_

template<typename Class>
class fgSingleton {
private:
    static bool instanceFlag;
    static Class *instance;

protected:

    fgSingleton() {
    }

public:

    static Class *getInstance() {
        if (!instanceFlag || !instance) {
            if (!instance)
                instance = new Class();
            instanceFlag = true;
            return instance;
        } else {
            return instance;
        }
    }

    static void deleteInstance() {
        if (instanceFlag || instance) {
            instanceFlag = false;
            if (instance)
                delete instance;
            instance = 0;
        }
    }

    ~fgSingleton() {
        instanceFlag = false;
    }
};

#endif /* _FG_SINGLETON_H_ */
