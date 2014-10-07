/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_DRAWING_BATCH_H_
#define _FG_GFX_DRAWING_BATCH_H_

#include "fgGFXDrawCall.h"
#include "fgGFXLayer.h"

#include <queue>
#include <deque>

/*
 *
 */
class fgGfxDrawingBatch : public fgGfxLayer
{
private:
	typedef std::priority_queue<fgGfxDrawCall*, std::deque<fgGfxDrawCall*>, fgPtrGreater<fgGfxDrawCall*> > batchPriorityQueue;

	//
	batchPriorityQueue			m_priorityBatch;

	//
	fgVector<fgGfxDrawCall *>	m_drawCalls;

	//
	fgManagerBase *m_shaderMgr;

public:
	// 
	fgGfxDrawingBatch();
	// 
	virtual ~fgGfxDrawingBatch();

	//
	fgManagerBase *getShaderManager(void) const;
	//
	virtual void setShaderManager(fgManagerBase *shaderMgr);

	//
	fgGfxDrawCall *createDrawCall(int &index, fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
	//
	fgGfxDrawCall *getDrawCall(int index);
	//
	fgGfxDrawCall *getLastDrawCall(void);
	//
	int appendDrawCall(fgGfxDrawCall* drawCall, fgBool check = FG_TRUE);
	//
	fgGfxDrawCall *removeDrawCall(int index);
	//
	fgBool removeDrawCall(fgGfxDrawCall *drawCall);
	//
	fgBool deleteDrawCall(int index);
	//
	fgBool deleteDrawCall(fgGfxDrawCall*& drawCall);

	//
	virtual void flush(void);

	//
	virtual void sortCalls(void);

	//
	virtual void render(void);

};

#endif /* _FG_GFX_DRAWING_BATCH_H_ */
