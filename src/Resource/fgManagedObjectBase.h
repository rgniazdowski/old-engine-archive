/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

#ifndef _FG_MANAGED_OBJECT_BASE_H_
    #define _FG_MANAGED_OBJECT_BASE_H_

    #include "fgBool.h"
    #include <string>

/**
 * 
 */
template<typename HandleType>
class fgManagedObjectBase {
public:
    /**
     * Default empty constructor for resource base object
     */
    fgManagedObjectBase() : m_nameTag(), m_isManaged(FG_FALSE) { }

    /**
     * Default empty destructor for resource base object
     */
    virtual ~fgManagedObjectBase() {}
    
public:
    /**
     * Set resource name (string TAG/ID)
     * @param name
     */
    inline void setName(const char *name) {
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

protected:
    /// Name of the data, string ID
    std::string m_nameTag;
    /// Unique handle number
    HandleType m_handle;
    /// Is this data currently managed inside of any kind manager?
    fgBool m_isManaged;
};

#endif /* _FG_MANAGED_OBJECT_BASE_H_ */


