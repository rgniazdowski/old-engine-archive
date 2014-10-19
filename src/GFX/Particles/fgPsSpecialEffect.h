/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_PS_SPECIAL_EFFECT_H_
    #define _FG_PS_SPECIAL_EFFECT_H_

/**
 *
 */
class SpecialEffect {
private:

public:
    SpecialEffect() { };
    virtual ~SpecialEffect() { };

    virtual void calculate(void) = 0;
    virtual void draw(void) = 0;
};

#endif
