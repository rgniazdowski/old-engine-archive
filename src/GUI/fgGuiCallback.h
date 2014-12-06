/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_CALLBACK
    #define FG_INC_GUI_CALLBACK

    #include "Event/fgCallback.h"

class fgGuiWidget;
class fgGuiMain;
typedef fgBool(*fgGuiWidgetEventHandlerFunc) (fgGuiMain *guiMain, fgGuiWidget *widget);

/**
 *
 */
class fgGuiCallback : public virtual fgFunctionCallback {
public:
    typedef fgFunctionCallback base_type;
public:
    fgGuiCallback(fgGuiMain *pGuiMain = NULL) {
        fgFunctionCallback::setFunction((fgFunctionCallback::fgFunction)NULL);
        m_guiMainPtr = pGuiMain;
    }
    virtual ~fgGuiCallback() {
        m_guiMainPtr = NULL;
    }

    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiWidget *pWidget) = 0;

    /**
     * 
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiMain *pGuiMain, fgGuiWidget *pWidget) = 0;
    
    /**
     * 
     * @param pGuiMain
     */
    void setGuiMain(fgGuiMain *pGuiMain) {
        m_guiMainPtr = pGuiMain;
    }
    
    /**
     * 
     * @return 
     */
    fgGuiMain *getGuiMain(void) const {
        return m_guiMainPtr;
    }

protected:
    ///
    fgGuiMain *m_guiMainPtr;
};

template < class Class >
/*
 *
 */
class fgGuiClassCallback : public fgGuiCallback {
public:
    typedef fgGuiCallback base_type;
    typedef fgBool(Class::*fgGuiMethod)(fgGuiMain *guiMain, fgGuiWidget *widget);
    typedef fgGuiMethod callback_type;

    /**
     * 
     * @param pClassInstance
     * @param pMethod
     */
    fgGuiClassCallback(Class* pClassInstance, fgGuiMethod pMethod) :
    fgGuiCallback(NULL) {
        m_pClassInstance = pClassInstance;
        m_guiMethod = pMethod;
    }
    /**
     * 
     * @param pClassInstance
     * @param pGuiMain
     * @param pMethod
     */
    fgGuiClassCallback(Class* pClassInstance, fgGuiMain *pGuiMain, fgGuiMethod pMethod) :
    fgGuiCallback(pGuiMain) {
        m_pClassInstance = pClassInstance;
        m_guiMethod = pMethod;
    }
    /**
     * 
     */
    virtual ~fgGuiClassCallback() {
        m_pClassInstance = NULL;
        m_guiMethod = NULL;
    }

    /**
     * 
     * @param pClassInstance
     */
    void setClassInstance(Class* pClassInstance) {
        if(pClassInstance)
            m_pClassInstance = pClassInstance;
    }

    /**
     * 
     * @param method
     */
    void setGuiMethod(fgGuiMethod method) {
        m_pClassInstance = NULL;
        m_guiMethod = method;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool Call(void) {
        if(m_guiMethod != NULL && m_pClassInstance != NULL)
            return (m_pClassInstance->*m_guiMethod)(NULL, NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(fgArgumentList *argv) {
        if(m_guiMethod != NULL && m_pClassInstance != NULL) {
            // If argument list is given then maybe should check for existence
            // of STRUCT parameters ?
            //return (m_classInstance->*m_guiMethod)(argv);
            return FG_FALSE;
        }
        return FG_FALSE;
    }
    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiWidget *pWidget) {
        if(m_guiMethod != NULL && m_pClassInstance != NULL && m_guiMainPtr != NULL)
            return (m_pClassInstance->*m_guiMethod)(m_guiMainPtr, pWidget);
        return FG_FALSE;
    }
    /**
     * 
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiMain *pGuiMain, fgGuiWidget *pWidget) {
        if(m_guiMethod != NULL && m_pClassInstance != NULL)
            return (m_pClassInstance->*m_guiMethod)(pGuiMain, pWidget);
        return FG_FALSE;
    }

    /**
     * 
     * @param pClassInstance
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    fgBool Call(Class *pClassInstance, fgGuiMain *pGuiMain = NULL, fgGuiWidget *pWidget = NULL) {
        if(m_guiMethod != NULL && pClassInstance != NULL)
            return (pClassInstance->*m_guiMethod)(pGuiMain, pWidget);
        return FG_FALSE;
    }

    /**
     * 
     * @return 
     */
    inline fgGuiMethod & getGuiMethod(void) {
        return m_guiMethod;
    }

    /**
     * 
     * @return 
     */
    inline fgGuiMethod const & getGuiMethod(void) const {
        return m_guiMethod;
    }

private:
    /// 
    Class* m_pClassInstance;
    ///
    fgGuiMethod m_guiMethod;
};

/**
 * GuiFunctionCallback is similar to fgPlainFunctionCallback
 * here you have (fgGuiMain *guiMain, fgGuiWidget *widget)
 * in plain function: (void *systemData, void *userData)
 * However the system data is *widget... and userData: guiMain
 * So the usage is almost interchangeable - however not recommended
 */
class fgGuiFunctionCallback : public fgGuiCallback {
public:
    typedef fgGuiCallback base_type;
    typedef fgBool(*fgGuiFunction)(fgGuiMain *guiMain, fgGuiWidget *widget);
    typedef fgGuiFunction callback_type;

    /**
     * 
     * @param function
     */
    fgGuiFunctionCallback(fgGuiFunction pFunction) :
    fgGuiCallback(NULL) {
        m_guiFunction = pFunction;
    }
    /**
     * 
     * @param guiMain
     * @param function
     */
    fgGuiFunctionCallback(fgGuiMain *pGuiMain, fgGuiFunction pFunction) :
    fgGuiCallback(pGuiMain) {
        m_guiFunction = pFunction;
    }

    /**
     * 
     */
    virtual ~fgGuiFunctionCallback() {
        m_guiFunction = NULL;
    }

    /**
     * 
     * @param function
     */
    void setGuiFunction(fgGuiFunction pFunction) {
        m_guiFunction = pFunction;
    }

    /**
     * 
     * @return 
     */
    virtual fgBool Call(void) {
        if(m_guiFunction != NULL)
            return m_guiFunction(m_guiMainPtr, NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param pSystemData
     * @return 
     */
    virtual fgBool Call(void *pSystemData) {
        // This is for compatibility - fgFunctionCallback provides the
        // *(void *pSystemData) Call() function version however it is 
        // empty
        if(m_guiFunction != NULL) {
            if(!pSystemData) {
                return m_guiFunction(m_guiMainPtr, NULL);
            } else {
                fgGuiWidget *pWidget = (fgGuiWidget *)pSystemData;
                //if(pWidget->isManaged())
                    return m_guiFunction(m_guiMainPtr, pWidget);
            }

        }
        return FG_FALSE;
    }
    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiWidget *pWidget) {
        if(m_guiFunction != NULL)
            return m_guiFunction(m_guiMainPtr, pWidget);
        return FG_FALSE;
    }
    /**
     * 
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiMain *pGuiMain, fgGuiWidget *pWidget) {
        if(m_guiFunction != NULL)
            return m_guiFunction(pGuiMain, pWidget);
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiFunction & getGuiFunction(void) {
        return m_guiFunction;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiFunction const & getGuiFunction(void) const {
        return m_guiFunction;
    }

private:
    ///
    fgGuiFunction m_guiFunction;
};

#endif /* FG_INC_GUI_CALLBACK */
