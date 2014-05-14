/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include <cstdlib>
#include <cmath>
#include <cstring>

#include "fgPsFlashEffect.h"
/*
void FlashEffect::calculate(void) 
{
	if(m_active)
	{
		if(m_fade_direction == IN) {
			m_alpha += 1.0f/m_duration_ms * FG_HardwareState->DT2();
			if(m_alpha > 1.0f)
				m_active = false;
		} else if(m_fade_direction == OUT) {
			m_alpha -= 1.0f/m_duration_ms * FG_HardwareState->DT2();
			if(m_alpha < 0.0f)
				m_active = false;
		} else if(m_fade_direction == NONE) {
			if( FG_HardwareState->TS() - int64(m_time_ms) >= int64(m_duration_ms) )
				m_active = false;
		}
		m_color.a = m_alpha;
	}
}
*/