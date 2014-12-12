/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgManagedObjectBase.h
 * Author: vigilant
 *
 * Created on October 24, 2014, 5:17 PM
 */

#ifndef FG_INC_MANAGED_OBJECT_BASE
    #define FG_INC_MANAGED_OBJECT_BASE
    #define FG_INC_MANAGED_OBJECT_BASE_BLOCK

    #include "fgManagerBase.h"
    #include "fgBool.h"
    #include <string>
    #include <cstdio>

/**
 * 
 */
template<typename HandleType>
class fgManagedObjectBase {
public:
    typedef HandleType handle_type;
    // System data is always set to (void *)this
    typedef fgBool(*callbackPtr)(void *systemData, void *userData);
    typedef callbackPtr callback_type;
    
public:
    /**
     * Default empty constructor for managed base object
     */
    fgManagedObjectBase() : m_pManager(NULL), m_nameTag(), m_isManaged(FG_FALSE) { }
    /**
     * Default empty destructor for managed base object
     */
    virtual ~fgManagedObjectBase() {
        // Now call the special destructor callbacks
        int n = m_onDestructorCallbacks.size();
        for(int i = 0; i < n; i++) {
            callbackData &info = m_onDestructorCallbacks[i];
            if(info.callback) {
                info.callback((void *)this, (void *)info.userData);
                info.callback = NULL;
                info.userData = NULL;
            }
        }
        m_onDestructorCallbacks.clear_optimised();
        //m_onDestructorCallbacks.resize(0);
    }

public:
    /**
     * 
     * @param pCallback
     * @param pUserData
     * @return 
     */
    fgBool registerOnDestruct(callbackPtr pCallback, void *pUserData = NULL) {
        if(!pCallback)
            return FG_FALSE;
        int n = m_onDestructorCallbacks.size();
        // Check for duplicates
        for(int i = 0; i < n; i++) {
            callbackData &info = m_onDestructorCallbacks[i];
            if(info.callback == pCallback)
                return FG_FALSE;
        }
        callbackData callbackInfo(pCallback, pUserData);
        m_onDestructorCallbacks.push_back(callbackInfo);
        return FG_TRUE;
    }
    /**
     * Set resource name (string TAG/ID)
     * @param name
     */
    inline void setName(const char *name) {
        if(name)
            m_nameTag = name;
    }
    /**
     * 
     * @param name
     */
    inline void setName(const std::string& name) {
        m_nameTag = name;
    }
    /**
     * Get reference to resource name string
     * @return 
     */
    inline std::string& getName(void) {
        return m_nameTag;
    }
    /**
     * 
     * @return 
     */
    inline std::string const & getName(void) const {
        return m_nameTag;
    }
    /**
     * 
     * @return 
     */
    inline const char* getNameStr(void) const {
        return m_nameTag.c_str();
    }
    /**
     * Return the data handle ID
     * @return 
     */
    inline HandleType getHandle(void) const {
        return m_handle;
    }
    /**
     * Set the data handle ID 
     * @param handle
     */
    inline void setHandle(const HandleType handle) {
        m_handle = handle;
    }
    /**
     * Gets the reference to the data handle
     * @return Reference to the data handle
     */
    inline HandleType& getRefHandle(void) {
        return m_handle;
    }
    /**
     * 
     * @return 
     */
    inline HandleType const & getRefHandle(void) const {
        return m_handle;
    }
    /**
     * 
     * @param toggle
     */
    inline void setManaged(fgBool toggle = FG_TRUE) {
        m_isManaged = toggle;
    }
    /**
     * 
     * @return 
     */
    inline fgBool isManaged(void) const {
        return m_isManaged;
    }
    /**
     * 
     * @return 
     */
    inline fgManagerBase *getManager(void) const {
        return m_pManager;
    }
    /**
     * 
     * @param pManager
     */
    inline void setManager(fgManagerBase *pManager) {
        m_pManager = pManager;
    }

protected:
    ///
    fgManagerBase *m_pManager;
    /// Name of the data, string ID
    std::string m_nameTag;
    /// Unique handle number
    HandleType m_handle;
    /// Is this data currently managed inside of any kind manager?
    fgBool m_isManaged;
    
private:

    /**
     *
     */
    struct callbackData {
        ///
        callbackPtr callback;
        ///
        void *userData;
        /**
         * 
         */
        callbackData() : userData(NULL), callback(NULL) { }
        /**
         * 
         * @param pUserData
         * @param pCallback
         */
        callbackData(callbackPtr pCallback, void *pUserData) :
        callback(pCallback),
        userData(pUserData) { }
    };

    typedef fgVector<callbackData> callbackVec;
    typedef typename callbackVec::iterator callbackVecItor;
    /// Callbacks to call when the destructor is called
    callbackVec m_onDestructorCallbacks;
};

    #undef FG_INC_MANAGED_OBJECT_BASE_BLOCK
#endif /* FG_INC_MANAGED_OBJECT_BASE */
