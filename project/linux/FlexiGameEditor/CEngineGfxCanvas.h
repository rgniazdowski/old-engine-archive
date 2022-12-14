/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_ENGINE_GFX_PANEL
    #define FG_INC_ENGINE_GFX_PANEL
    #define FG_INC_ENGINE_GFX_PANEL_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include "GFX/fgGfxGL.h"

    #include "Event/fgEventDefinitions.h"
    #include "Scripting/fgScriptSubsystem.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #include "wx/wx.h"
    #include "wx/glcanvas.h"
#pragma GCC diagnostic pop

namespace fg {
    class CEngineMain;
}

class CRenderTimer;
class CEngineGfxCanvas;

/**
 *
 */
class CRenderTimer : public wxTimer {
public:
    typedef CRenderTimer self_type;
    typedef CRenderTimer type;
    typedef wxTimer base_type;

private:
    ///
    CEngineGfxCanvas* m_gfxCanvas;
    ///
    float m_fps;

public:
    /**
     * 
     * @param gfxCanvas
     * @param fps
     */
    CRenderTimer(CEngineGfxCanvas* gfxCanvas, float fps = 60.0f);

    /**
     *
     */
    void Notify(void);
    /**
     *
     */
    void start(void);
    /**
     * 
     */
    inline void stop(void) {
        base_type::Stop();
    }
    /**
     *
     * @return
     */
    inline float getFps(void) const {
        return m_fps;
    }
    /**
     *
     * @param fps
     */
    inline void setFps(float fps) {
        m_fps = fps;
        if(m_fps < 5.0f) {
            m_fps = 5.0f;
        }
    }
    /**
     * 
     * @param fps
     */
    inline void setFpsAndRestart(float fps) {
        setFps(fps);
        Stop();
        start();
    }
};

namespace fg {
    namespace event {
        class CFunctionCallback;
    }
}

/**
 *
 */
class CEngineGfxCanvas : public wxGLCanvas {
public:
    typedef CEngineGfxCanvas self_type;
    typedef CEngineGfxCanvas type;
    typedef wxGLCanvas base_type;

    // System data is always set to (void *)this
    typedef fgBool(*CallbackFuncPtr)(void *systemData, void *userData);
    ///
    typedef CallbackFuncPtr callback_type;

public:

    enum InternalCallbackType {
        INVALID_CALLBACK = -1,
        ENGINE_INITIALIZED = 0,
        ENGINE_DESTROYED = 1,
        NUM_ENGINE_CB_TYPES = 2
    };

private:
    ///
    wxGLContext* m_context;
    ///
    fgBool m_paint;
    ///
    fgBool m_appInit;
    ///
    fgBool m_isInitializing;
    /// Is exit activated?
    fgBool m_isExit;
    ///
    fgBool m_isSuspend;
    ///
    fgBool m_canInitialize;
    ///
    fgBool m_isFrameFreeze;
    /// Game main class - this is for initialization procedures
    /// contains also functions for handling events, drawing, etc #TODO
    /// Needs refactoring, some level of merging within main module or
    /// changing name to fgApplication - or extending fgApplication class
    /// #TODO - support threads
    fg::CEngineMain* m_engineMain;
    /// Pointer to pointer to game main object - by this we can update pointer
    /// in the main wx app/frame
    fg::CEngineMain** m_engineMainOrig;
    ///
    fg::event::CFunctionCallback* m_onSwapCallback;
    ///
    wxWindow* m_parentFrame;
    ///
    int m_argc;
    ///
    char *m_argv[2];
    ///
    wxPoint m_screenSize;

    /**
     *
     */
    struct CallbackData {
        ///
        CallbackFuncPtr callback;
        ///
        void *userData;
        /**
         *
         */
        CallbackData() : userData(NULL), callback(NULL) { }
        /**
         *
         * @param pUserData
         * @param pCallback
         */
        CallbackData(CallbackFuncPtr pCallback, void *pUserData) :
        callback(pCallback),
        userData(pUserData) { }
    };

    ///
    typedef fg::CVector<CallbackData> CallbacksVec;
    ///
    typedef typename CallbacksVec::iterator CallbacksVecItor;
    /// 
    CallbacksVec m_onEngineCallbacks[NUM_ENGINE_CB_TYPES];

    unsigned int executeCallbacks(InternalCallbackType cbType);

public:
    /**
     *
     */
    CEngineGfxCanvas(wxWindow* parent, int* args, fg::CEngineMain **engineMainOrig);
    /**
     *
     */
    virtual ~CEngineGfxCanvas();

    //--------------------------------------------------------------------------

    /**
     *
     * @return
     */
    fgBool initProgram(void);
    /**
     *
     */
    void closeProgram(void);

    /**
     *
     * @return
     */
    fgBool displayAndRender(void);
    /**
     *
     * @return
     */
    fgBool update(void);

    //--------------------------------------------------------------------------
    /**
     *
     * @param pCallback
     * @param pUserData
     * @return
     */
    fgBool registerCallback(InternalCallbackType cbType,
                            CallbackFuncPtr pCallback,
                            void* pUserData = NULL);
    /**
     *
     * @param pCallback
     * @return
     */
    fgBool isRegistered(CallbackFuncPtr pCallback,
                        InternalCallbackType cbType = INVALID_CALLBACK);

    /**
     * 
     * @param pCallback
     * @param cbType
     * @return
     */
    fgBool removeCallback(CallbackFuncPtr pCallback, InternalCallbackType cbType = INVALID_CALLBACK);
    //--------------------------------------------------------------------------

    /**
     * 
     * @param pSystemData
     * @param pUserData
     * @return
     */
    static fgBool OnGfxWindowSwapBuffer(void* pSystemData, void *pUserData);

    /**
     *
     * @param event
     */
    void OnPaint(wxPaintEvent& event);

    void OnMouseMoved(wxMouseEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseWheelMoved(wxMouseEvent& event);
    void OnMouseReleased(wxMouseEvent& event);
    void OnMouseLeftWindow(wxMouseEvent& event);
    void OnKeyPressed(wxKeyEvent& event);
    void OnKeyReleased(wxKeyEvent& event);    
    void OnCloseEvent(wxCloseEvent& event);

    /**
     *
     * @param event
     */
    void OnIdle(wxIdleEvent& event);
    /**
     *
     * @param event
     */
    void OnResized(wxSizeEvent& event);

    //--------------------------------------------------------------------------
public:
    /**
     * 
     * @return 
     */
    inline fg::event::CFunctionCallback* getOnSwapCallback(void) const {
        return m_onSwapCallback;
    }
    /**
     *
     * @return
     */
    inline fg::event::CFunctionCallback*& getRefOnSwapCallback(void) {
        return m_onSwapCallback;
    }
    /**
     *
     * @return
     */
    inline int getWidth(void) {
        return GetSize().x;
    }
    /**
     *
     * @return
     */
    inline int getHeight(void) {
        return GetSize().y;
    }
    /**
     *
     * @param engineMainOrig
     */
    inline void setEngineMainOriginal(fg::CEngineMain **engineMainOrig) {
        m_engineMainOrig = engineMainOrig;
    }
    /**
     *
     * @return
     */
    inline fg::CEngineMain* getEngineMain(void) const {
        if(!m_engineMainOrig)
            return NULL;
        return *m_engineMainOrig;
    }
    /**
     *
     * @return
     */
    inline fgBool isSuspend(void) const {
        return m_isSuspend;
    }
    /**
     *
     * @return
     */
    inline fgBool isExit(void) const {
        return m_isExit;
    }
    /**
     *
     * @return
     */
    inline fgBool isPaintReady(void) const {
        return m_paint;
    }
    /**
     *
     * @return
     */
    inline fgBool isInitialized(void) const {
        return m_appInit;
    }
    /**
     *
     * @return
     */
    inline fgBool canInitialize(void) const {
        return m_canInitialize;
    }
    /**
     *
     * @return
     */
    inline fgBool isFrameFreeze(void) const {
        return m_isFrameFreeze;
    }
    /**
     * 
     * @param toggle
     */
    inline void setExit(fgBool toggle = FG_TRUE) {
        m_isExit = toggle;
    }
    /**
     *
     * @param toggle
     */
    inline void setInitializeFlag(fgBool toggle = FG_TRUE) {
        m_canInitialize = toggle;
    }
    /**
     *
     * @param toggle
     */
    inline void setFrameFreeze(fgBool toggle = FG_TRUE) {
        m_isFrameFreeze = toggle;
    }
    /**
     *
     * @param toggle
     */
    inline void setSuspend(fgBool toggle = FG_TRUE) {
        m_isSuspend = toggle;
    }

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_ENGINE_GFX_PANEL_BLOCK
#endif /* FG_INC_ENGINE_GFX_PANEL */
