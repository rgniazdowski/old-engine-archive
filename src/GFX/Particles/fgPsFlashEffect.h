/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#undef _FG_PS_FLASH_EFFECT_
#ifdef _FG_PS_FLASH_EFFECT_
//#define _FG_PS_FLASH_EFFECT_
// #FIXME #DEPRECATED
#include "IwGx.h"
#include "s3eTimer.h"

#include "fgCommon.h"
#include "Hardware/fgHardwareState.h"

/**
 *
 */
class FlashEffect
{
private:
	CIwColour m_color;
	Direction m_fade_direction;
	bool m_active;
	int m_duration_ms;
	uint64 m_time_ms;
	float m_alpha;
public:
	FlashEffect() : m_fade_direction(NONE), m_active(false), m_duration_ms(0), m_time_ms(0) {
        m_color.Set( 0, 0, 0, 255 );
    }
	~FlashEffect() { }

	void setColor( const CIwColour & color ) {
		m_color = color;
	}

	CIwColour & color()	{
		return m_color;
	}

	int duration() {
		return m_duration_ms;
	}

	void setDirection(Direction fade_dir) {
		m_fade_direction = fade_dir;
	}

	Direction direction() {
		return m_fade_direction;
	}

	float alpha(void) {
		return m_alpha;
	}

	void setAlpha(float alpha) {
		m_alpha = alpha;
	}

	bool active(void) {
		return m_active;
	}

	virtual void setActive(Direction fade_dir, int duration_ms)
	{
		m_active = true;
		m_fade_direction = fade_dir;
		m_duration_ms = duration_ms;
		if(m_fade_direction == IN) {
			m_alpha = 0.0f;
		} else {
			m_alpha = 1.0f;
		}
		m_time_ms = FG_HardwareState->TS();
	}

	void setFadeOut(int duration_ms) {
		setActive(OUT, duration_ms);
	}
	void setFadeIn(int duration_ms) {
		setActive(IN, duration_ms);
	}
	void setStatic(int duration_ms) {
		setActive(NONE, duration_ms);
	}

	virtual void init(void) { }
	virtual void calculate(void);
	virtual void draw(void) { };
};

#endif
