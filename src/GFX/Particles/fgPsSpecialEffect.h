/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_PS_SPECIAL_EFFECT
    #define FG_INC_PS_SPECIAL_EFFECT

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
