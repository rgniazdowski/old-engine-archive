/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_PS_SPECIAL_EFFECT_H_
#define _FG_PS_SPECIAL_EFFECT_H_

/**
 *
 */
class SpecialEffect
{
private:

public:
	SpecialEffect() {};
	~SpecialEffect() {};

	virtual void calculate(void) = 0;
	virtual void draw(void) = 0;
};

#endif
