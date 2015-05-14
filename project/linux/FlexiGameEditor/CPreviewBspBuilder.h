/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   CPreviewBspBuilder.h
 * Author: vigilant
 *
 * Created on May 14, 2015, 2:17 AM
 */

#ifndef FG_INC_PREVIEW_BSP_BUILDER
    #define FG_INC_PREVIEW_BSP_BUILDER
    #define FG_INC_PREVIEW_BSP_BUILDER_BLOCK

    #include "Event/fgArgumentList.h"
    #include "Event/fgCallback.h"

    #include "CPreviewModeBase.h"

/**
 *
 */
class CPreviewBspBuilder : public CPreviewModeBase {
public:
    typedef CPreviewBspBuilder self_type;
    typedef CPreviewBspBuilder type;
    typedef CPreviewModeBase base_type;

public:
    /**
     *
     * @param pEngineMainOrig
     */
    CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig);

    /**
     *
     */
    virtual ~CPreviewBspBuilder();

    /**
     *
     * @param toggle
     * @return
     */
    virtual fgBool activate(fgBool toggle = FG_FALSE);
    /**
     * 
     */
    virtual void refreshInternals(void);

protected:
    static fgBool engineInit(void* systemData, void* userData);
    static fgBool engineDestroy(void* systemData, void* userData);

    static fgBool displayHandler(void* systemData, void* userData);
    static fgBool updateHandler(void* systemData, void* userData);
    static fgBool renderHandler(void* systemData, void* userData);

    fgBool mouseHandler(fg::event::CArgumentList* argv);
    fgBool keyboardHandler(fg::event::CArgumentList* argv);

    /**
     *
     * @return
     */
    virtual fgBool registerCallbacks(void);
    /**
     *
     * @return
     */
    virtual fgBool unregisterCallbacks(void);

private:
    /// Special callback called once in every display (pre-render) frame.
    /// Here can add additional things to the drawing batch.
    fg::event::CFunctionCallback* m_displayShotCB;
    /// Special callback called once in every update frame.
    fg::event::CFunctionCallback* m_updateShotCB;
    /// Special callback called once in every render frame.
    /// Can call rendering functions inside (gl).
    fg::event::CFunctionCallback* m_renderShotCB;
    /// Handler function callback object for any mouse event (move, clicks).
    fg::event::CFunctionCallback* m_mouseHandlerCB;
    /// Handler for any keyboard event - up and down keys.
    /// This is events are thrown only once when key state is changing.
    fg::event::CFunctionCallback* m_keyboardHandlerCB;
};

    #undef FG_INC_PREVIEW_BSP_BUILDER_BLOCK
#endif	/* FG_INC_PREVIEW_BSP_BUILDER */
