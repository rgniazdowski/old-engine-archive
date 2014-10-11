/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFontBuiltIn.h"

/*
 *
 */
fgFontBuiltInResource::fgFontBuiltInResource() : 
	fgFontResource(),
	m_rawFontData(NULL)
{
	m_fontType = FG_FONT_TYPE_STB_BUILTIN;
	m_resType = FG_RESOURCE_FONT;
}

/*
 *
 */
fgFontBuiltInResource::fgFontBuiltInResource(fgFontBuiltInRawData *rawFontData) : 
	fgFontResource(),
	m_rawFontData(rawFontData)
{
	m_fontType = FG_FONT_TYPE_STB_BUILTIN;
	m_resType = FG_RESOURCE_FONT;
}

/*
 *
 */
void fgFontBuiltInResource::clear(void)
{
	fgFontResource::clear();
	m_rawData = NULL;
	m_fontType = FG_FONT_TYPE_STB_BUILTIN;
}

/*
 *
 */
fgBool fgFontBuiltInResource::create(void)
{
	FG_LOG::PrintDebug("fgFontBuiltInResource::create();");
	if(!m_rawFontData)
		return FG_FALSE;
	if(!m_rawFontData->xPtr || 
		!m_rawFontData->yPtr || 
		!m_rawFontData->wPtr || 
		!m_rawFontData->hPtr || 
		!m_rawFontData->sPtr || 
		!m_rawFontData->tPtr || 
		!m_rawFontData->aPtr || 
		!m_rawFontData->bitsPtr || 
		!m_rawFontData->width || 
		!m_rawFontData->heightPOW2 || 
		!m_rawFontData->numChars) {
			return FG_FALSE;
	}
	if(!m_info.charInfo) {
		m_info.charInfo = fgMalloc<fgFontCharInfo>(m_rawFontData->numChars);
	}
	m_info.numChars = m_rawFontData->numChars;
	m_info.firstChar = m_rawFontData->firstChar;
	m_width = m_rawFontData->width;
	m_height = m_rawFontData->heightPOW2;
	m_components = 4;

	unsigned int i, j;
	if(!m_rawData) {
		m_rawData = new unsigned char[m_height * m_width * m_components];
		unsigned char *data = m_rawData;
		unsigned int *bits = m_rawFontData->bitsPtr;
		unsigned int bitpack = *bits++, numbits = 32;
		memset(m_rawData, 0, m_height * m_width * m_components);

		for (j=1; j < m_rawFontData->height-1; ++j) {
			for (i=1; i < m_rawFontData->width-1; ++i) {
				unsigned int idx = j*m_rawFontData->width*m_components+(i-1)*m_components;
				unsigned int value;
				if (numbits==0) bitpack = *bits++, numbits=32;
				value = bitpack & 1;
				bitpack >>= 1, --numbits;
				if (value) {
					if (numbits < 3) bitpack = *bits++, numbits = 32;
					data[idx + 0] = (unsigned char)((bitpack & 7) * 0x20 + 0x1f);
					data[idx + 1] = data[idx];
					data[idx + 2] = data[idx];
					data[idx + 3] = 255;
					bitpack >>= 3, numbits -= 3;
				} else {
					data[idx] = 0;
				}
			}
		}
	}

	// Build font description
	if (m_info.charInfo != NULL) {
		float recip_width = 1.0f / m_rawFontData->width;
		float recip_height = 1.0f / m_rawFontData->heightPOW2;
		for (i=0; i < m_rawFontData->numChars; ++i) {
			
			// pad characters so they bilerp from empty space around each character
#if 0
			m_info.charInfo[i].s0 = (m_rawFontData->sPtr[i]) * recip_width;
			m_info.charInfo[i].t0 = (m_rawFontData->tPtr[i]) * recip_height;
			m_info.charInfo[i].s1 = (m_rawFontData->sPtr[i] + m_rawFontData->wPtr[i]) * recip_width;
			m_info.charInfo[i].t1 = (m_rawFontData->tPtr[i] + m_rawFontData->hPtr[i]) * recip_height;
			m_info.charInfo[i].x0 = m_rawFontData->xPtr[i];
			m_info.charInfo[i].y0 = m_rawFontData->yPtr[i];
			m_info.charInfo[i].x1 = m_rawFontData->xPtr[i] + m_rawFontData->wPtr[i];
			m_info.charInfo[i].y1 = m_rawFontData->yPtr[i] + m_rawFontData->hPtr[i];
			
			m_info.charInfo[i].s0f = (m_rawFontData->sPtr[i] - 0.5f) * recip_width;
			m_info.charInfo[i].t0f = (m_rawFontData->tPtr[i] - 0.5f) * recip_height;
			m_info.charInfo[i].s1f = (m_rawFontData->sPtr[i] + m_rawFontData->wPtr[i] + 0.5f) * recip_width;
			m_info.charInfo[i].t1f = (m_rawFontData->tPtr[i] + m_rawFontData->hPtr[i] + 0.5f) * recip_height;
			m_info.charInfo[i].x0f = m_rawFontData->xPtr[i] - 0.5f;
			m_info.charInfo[i].y0f = m_rawFontData->yPtr[i] - 0.5f;
			m_info.charInfo[i].x1f = m_rawFontData->xPtr[i] + m_rawFontData->wPtr[i] + 0.5f;
			m_info.charInfo[i].y1f = m_rawFontData->yPtr[i] + m_rawFontData->hPtr[i] + 0.5f;
#endif
			/////// PROPER
			m_info.charInfo[i].uv1i.x = (m_rawFontData->sPtr[i]) * recip_width;
			m_info.charInfo[i].uv1i.y = 1.0f - ((m_rawFontData->tPtr[i]) * recip_height);
			m_info.charInfo[i].uv2i.x = (m_rawFontData->sPtr[i] + m_rawFontData->wPtr[i]) * recip_width;
			m_info.charInfo[i].uv2i.y = 1.0f - ((m_rawFontData->tPtr[i] + m_rawFontData->hPtr[i]) * recip_height);
			m_info.charInfo[i].p0i.x = m_rawFontData->xPtr[i];
			m_info.charInfo[i].p0i.y = m_rawFontData->yPtr[i];
			m_info.charInfo[i].p1i.x = m_rawFontData->xPtr[i] + m_rawFontData->wPtr[i];
			m_info.charInfo[i].p1i.y = m_rawFontData->yPtr[i] + m_rawFontData->hPtr[i];

			m_info.charInfo[i].uv1f.x = (m_rawFontData->sPtr[i] - 0.5f) * recip_width;
			m_info.charInfo[i].uv1f.y = 1.0f - ((m_rawFontData->tPtr[i] - 0.5f) * recip_height);
			m_info.charInfo[i].uv2f.x = (m_rawFontData->sPtr[i] + m_rawFontData->wPtr[i] + 0.5f) * recip_width;
			m_info.charInfo[i].uv2f.y = 1.0f - ((m_rawFontData->tPtr[i] + m_rawFontData->hPtr[i] + 0.5f) * recip_height);
			m_info.charInfo[i].p0f.x = m_rawFontData->xPtr[i] - 0.5f;
			m_info.charInfo[i].p0f.y = m_rawFontData->yPtr[i] - 0.5f;
			m_info.charInfo[i].p1f.x = m_rawFontData->xPtr[i] + m_rawFontData->wPtr[i] + 0.5f;
			m_info.charInfo[i].p1f.y = m_rawFontData->yPtr[i] + m_rawFontData->hPtr[i] + 0.5f;

			if((int)m_info.charInfo[i].p1f.y > m_step)
				m_step = (int)m_info.charInfo[i].p1f.y;

			m_info.charInfo[i].stepi = (m_rawFontData->aPtr[i]+8)>>4;
			m_info.charInfo[i].stepf = m_rawFontData->aPtr[i]/16.0f;
		}
	}
	m_fontType = FG_FONT_TYPE_STB_BUILTIN;
	return FG_TRUE;
}

/*
 *
 */
void fgFontBuiltInResource::destroy(void)
{
	fgFontResource::destroy();
	m_rawFontData = NULL;
}

/*
 *
 */
fgBool fgFontBuiltInResource::recreate(void)
{
	fgFontBuiltInResource::dispose();
	return fgFontBuiltInResource::create();
}

/*
 *
 */
void fgFontBuiltInResource::dispose(void)
{
	fgFontResource::dispose();
}

/*
 *
 */
fgBool fgFontBuiltInResource::isDisposed(void) const
{
	return fgFontResource::isDisposed();
}

/*
 *
 */
void fgFontBuiltInResource::setBuiltInRawFontData(fgFontBuiltInRawData *rawFontData)
{
	if(!rawFontData)
		return;
	m_rawFontData = rawFontData;
}
