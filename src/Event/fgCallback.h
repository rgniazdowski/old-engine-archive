/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CALLBACK_H_
    #define _FG_CALLBACK_H_

    #include "fgTypes.h"
    #include "fgArgumentList.h"

/**
 *
 */
class fgFunctionCallback {
public:
    // This is function pointer (to global or static member function)
    typedef fgBool(*fgFunction)(fgArgumentList *argv);
    /**
     * 
     */
    fgFunctionCallback() : m_function(NULL) { }
    /**
     * 
     * @param function
     */
    fgFunctionCallback(fgFunction function) {
        m_function = function;
    }
    /**
     * 
     */
    virtual ~fgFunctionCallback() {
        m_function = NULL;
    }
    /**
     * 
     * @param function
     */
    void setFunction(fgFunction function) {
        m_function = function;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool Call(void) {
        if(m_function != NULL)
            return m_function(NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(fgArgumentList *argv) {
        if(m_function != NULL)
            return m_function(argv);
        return FG_FALSE;
    }
    /**
     * 
     * @param pSystemData
     * @return 
     */
    virtual fgBool Call(void *pSystemData) {
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    inline fgFunction & getFunction(void) {
        return m_function;
    }
    /**
     * 
     * @return 
     */
    inline fgFunction const & getFunction(void) const {
        return m_function;
    }

private:
    ///
    fgFunction m_function;

};

/**
 *
 */
class fgPlainFunctionCallback : public fgFunctionCallback {
public:
    // This is function pointer (to global or static member function)
    typedef fgBool(*fgPlainFunction)(void *systemData, void *userData);
    /**
     * 
     */
    fgPlainFunctionCallback() :
    fgFunctionCallback(),
    m_plainFunction(NULL),
    m_pUserData(NULL) { }
    /**
     * 
     * @param function
     */
    fgPlainFunctionCallback(fgPlainFunction pPlainFunction, void *pUserData = NULL) {
        m_plainFunction = pPlainFunction;
        m_pUserData = pUserData;
    }
    /**
     * 
     */
    virtual ~fgPlainFunctionCallback() {
        m_plainFunction = NULL;
        m_pUserData = NULL;
    }
    /**
     * 
     * @param function
     */
    void setFunction(fgPlainFunction pPlainFunction) {
        m_plainFunction = pPlainFunction;
    }
    /**
     * 
     * @param pUserData
     */
    void setUserData(void *pUserData) {
        m_pUserData = pUserData;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool Call(void) {
        if(m_plainFunction != NULL)
            return m_plainFunction(NULL, m_pUserData);
        return FG_FALSE;
    }
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(fgArgumentList *pArgv) {
        // #FIXME - this is for compatibility with other functions
        if(m_plainFunction != NULL)
            return m_plainFunction(NULL, NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(void *pSystemData) {
        if(m_plainFunction != NULL)
            return m_plainFunction(pSystemData, m_pUserData);
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    inline fgPlainFunction & getPlainFunction(void) {
        return m_plainFunction;
    }
    /**
     * 
     * @return 
     */
    inline fgPlainFunction const & getPlainFunction(void) const {
        return m_plainFunction;
    }
private:
    ///
    fgPlainFunction m_plainFunction;
    ///
    void *m_pUserData;
};

/**
 *
 */
template < class Class >
class fgClassCallback : public fgFunctionCallback {
public:
    typedef fgBool(Class::*fgClassMethod)(fgArgumentList *argv);
    /**
     * 
     * @param class_instance
     * @param method
     */
    fgClassCallback(Class* pClassInstance, fgClassMethod pMethod) :
    fgFunctionCallback(),
    m_pClassInstance(pClassInstance),
    m_method(pMethod) { }
    /**
     * 
     */
    virtual ~fgClassCallback() {
        m_pClassInstance = NULL;
        m_method = NULL;
    }
    /**
     * 
     * @param method
     */
    void setMethod(fgClassMethod pMethod) {
        m_pClassInstance = NULL;
        m_method = pMethod;
    }
    /**
     * 
     * @param class_instance
     */
    void setClass(Class* class_instance) {
        m_pClassInstance = class_instance;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool Call(void) {
        if(m_method != NULL && m_pClassInstance != NULL)
            return (m_pClassInstance->*m_method)(NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(fgArgumentList *argv) {
        if(m_method != NULL && m_pClassInstance != NULL)
            return (m_pClassInstance->*m_method)(argv);
        return FG_FALSE;
    }
    /**
     * 
     * @param class_instance
     * @return 
     */
    fgBool Call(Class *class_instance) {
        if(m_method != NULL && class_instance != NULL)
            return (class_instance->*m_method)(NULL);
        return FG_FALSE;
    }
    /**
     * 
     * @param class_instance
     * @param argv
     * @return 
     */
    fgBool Call(Class *class_instance, fgArgumentList *argv) {
        if(m_method != NULL && class_instance != NULL)
            return (class_instance->*m_method)(argv);
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    inline fgClassMethod & getMethod(void) {
        return m_method;
    }
    /**
     * 
     * @return 
     */
    inline fgClassMethod const & getMethod(void) const {
        return m_method;
    }

private:
    /// 
    Class* m_pClassInstance;
    ///
    fgClassMethod m_method;
};

#endif /* _FG_CALLBACK_H_ */
