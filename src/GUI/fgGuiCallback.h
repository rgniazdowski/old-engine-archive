/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_CALLBACK_H_
    #define _FG_GUI_CALLBACK_H_

    #include "Event/fgCallback.h"

class fgGuiWidget;
class fgGuiMain;
typedef fgBool(*fgGuiWidgetEventHandlerFunc) (fgGuiMain *guiMain, fgGuiWidget *widget);

/*
 *
 */
class fgGuiCallback : public fgFunctionCallback {
public:
    fgGuiCallback(fgGuiMain *guiMain = NULL) {
        m_guiMainPtr = guiMain;
    }
    virtual ~fgGuiCallback() {
        m_guiMainPtr = NULL;
    }

    //
    virtual fgBool Call(fgGuiWidget *widget) = 0;

    //
    virtual fgBool Call(fgGuiMain *guiMain, fgGuiWidget *widget) = 0;

protected:
    //
    fgGuiMain *m_guiMainPtr;
};

template < class Class >
/*
 *
 */
class fgGuiClassCallback : public fgGuiCallback {
public:
    typedef fgBool(Class::*fgGuiMethod)(fgGuiMain *guiMain, fgGuiWidget *widget);

    // 
    fgGuiClassCallback(Class* class_instance, fgGuiMethod method) :
    fgGuiCallback(NULL) {
        m_classInstance = class_instance;
        m_guiMethod = method;
    }

    // 
    fgGuiClassCallback(Class* class_instance, fgGuiMain *guiMain, fgGuiMethod method) :
    fgGuiCallback(guiMain) {
        m_classInstance = class_instance;
        m_guiMethod = method;
    }

    //
    virtual ~fgGuiClassCallback() {
        m_classInstance = NULL;
        m_guiMethod = NULL;
    }

    //
    void setClassInstance(Class* class_instance) {
        if(class_instance)
            m_classInstance = class_instance;
    }

    //
    void setGuiMethod(fgGuiMethod method) {
        m_classInstance = NULL;
        m_guiMethod = method;
    }

    // 
    virtual fgBool Call(void) {
        if(m_guiMethod != NULL && m_classInstance != NULL)
            return (m_classInstance->*m_guiMethod)(NULL, NULL);
        return FG_FALSE;
    }

    // 
    virtual fgBool Call(fgArgumentList *argv) {
        if(m_guiMethod != NULL && m_classInstance != NULL) {
            // If argument list is given then maybe should check for existence
            // of STRUCT parameters ?
            //return (m_classInstance->*m_guiMethod)(argv);
            return FG_TRUE;
        }
        return FG_FALSE;
    }

    //
    virtual fgBool Call(fgGuiWidget *widget) {
        if(m_guiMethod != NULL && m_classInstance != NULL && m_guiMainPtr != NULL)
            return (m_classInstance->*m_guiMethod)(m_guiMainPtr, widget);
        return FG_FALSE;
    }

    //
    virtual fgBool Call(fgGuiMain *guiMain, fgGuiWidget *widget) {
        if(m_guiMethod != NULL && m_classInstance != NULL)
            return (m_classInstance->*m_guiMethod)(guiMain, widget);
        return FG_FALSE;
    }

    //
    fgBool Call(Class *class_instance, fgGuiMain *guiMain = NULL, fgGuiWidget *widget = NULL) {
        if(m_guiMethod != NULL && class_instance != NULL)
            return (class_instance->*m_guiMethod)(guiMain, widget);
        return FG_FALSE;
    }

    //
    inline fgGuiMethod & getGuiMethod(void) {
        return m_guiMethod;
    }
    
    //
    inline const fgGuiMethod & getGuiMethod(void) const {
        return m_guiMethod;
    }
    
private:
    // 
    Class* m_classInstance;
    // 
    fgGuiMethod m_guiMethod;
};

/*
 *
 */
class fgGuiFunctionCallback : public fgGuiCallback {
public:
    typedef fgBool(*fgGuiFunction)(fgGuiMain *guiMain, fgGuiWidget *widget);

    // 
    fgGuiFunctionCallback(fgGuiFunction function) :
    fgGuiCallback(NULL) {
        m_guiFunction = function;
    }

    // 
    fgGuiFunctionCallback(fgGuiMain *guiMain, fgGuiFunction function) :
    fgGuiCallback(guiMain) {
        m_guiFunction = function;
    }

    //
    virtual ~fgGuiFunctionCallback() {
        m_guiFunction = NULL;
    }

    //
    void setGuiFunction(fgGuiFunction function) {
        m_guiFunction = function;
    }

    // 
    virtual fgBool Call(void) {
        if(m_guiFunction != NULL)
            return m_guiFunction(m_guiMainPtr, NULL);
        return FG_FALSE;
    }

    //
    virtual fgBool Call(fgGuiWidget *widget) {
        if(m_guiFunction != NULL)
            return m_guiFunction(m_guiMainPtr, widget);
        return FG_FALSE;
    }

    //
    virtual fgBool Call(fgGuiMain *guiMain, fgGuiWidget *widget) {
        if(m_guiFunction != NULL)
            return m_guiFunction(guiMain, widget);
        return FG_FALSE;
    }

    //
    inline fgGuiFunction & getGuiFunction(void) {
        return m_guiFunction;
    }
    
    //
    inline const fgGuiFunction & getGuiFunction(void) const {
        return m_guiFunction;
    }
    
private:
    // 
    fgGuiFunction m_guiFunction;
};

#endif /* _FG_GUI_CALLBACK_H_ */
