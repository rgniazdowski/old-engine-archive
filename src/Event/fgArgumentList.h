/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_ARGUMENT_LIST
    #define FG_INC_ARGUMENT_LIST

    #include "fgTypes.h"

    #define FG_ARGUMENT_DEFAULT_COUNT	8
    #define FG_ARGUMENT_MAX_STRING	256 // #FIXME

/**
 *
 */
enum fgArgumentType {
    // Integer
    FG_ARGUMENT_INTEGER,
    // Double number
    FG_ARGUMENT_DOUBLE,
    // Float number
    FG_ARGUMENT_FLOAT,
    // Char string array
    FG_ARGUMENT_STRING,
    // Void* pointer to any kind of data
    FG_ARGUMENT_POINTER,
    // Pointer to allocated structure, structure needs to be allocated by 'malloc' and freed using the 'free' function
    FG_ARGUMENT_TEMP_POINTER,
    // No argument
    FG_ARGUMENT_NONE
};

/*
 *
 */
struct fgArgument {
    ///
    fgArgumentType type;

    union {
        ///
        int int_val;
        ///
        double double_val;
        ///
        float float_val;
        ///
        char string[FG_ARGUMENT_MAX_STRING];
        ///
        void *custom_pointer;
    };
    /**
     * 
     */
    fgArgument() : type(FG_ARGUMENT_NONE), int_val(0) { }
    /**
     * 
     */
    void reset(void) {
        type = FG_ARGUMENT_NONE;
        int_val = 0;
    }
};

/**
 *
 */
class fgArgumentList {
private:
    ///
    fgVector<fgArgument> m_argv;
    ///
    int m_argc;
    ///
    int m_maxArgs;
    ///
    int m_currentArg;
    ///
    fgArgument m_emptyArgument;
    
public:
    /**
     * 
     */
    fgArgumentList();
    /**
     * 
     * @param _max
     */
    fgArgumentList(int _max);

    /**
     * 
     */
    virtual ~fgArgumentList();

    /**
     * 
     * @param _max
     */
    void setMaxArgumentCount(int _max);
    /**
     * 
     * @return 
     */
    int getMaxArgumentCount();

    /**
     * 
     * @param _type
     * @param _value
     */
    void pushArgument(fgArgumentType _type, void *_value);
    /**
     * 
     * @param int_val
     */
    void pushArgument(int int_val);
    /**
     * 
     * @param double_val
     */
    void pushArgument(double double_val);
    /**
     * 
     * @param float_val
     */
    void pushArgument(float float_val);
    /**
     * 
     * @param string
     */
    void pushArgument(const char *string);
    /**
     * 
     * @param custom_pointer
     */
    void pushArgument(void *custom_pointer);

    /**
     * 
     * @return 
     */
    int getArgumentCount();

    /**
     * 
     */
    void reset();
    /**
     * 
     * @return 
     */
    fgBool isThereNextArgument();

    /**
     * 
     * @param _type
     * @return 
     */
    void *getNextArgumentValue(fgArgumentType *_type = NULL);
    /**
     * 
     * @param ID
     * @param _type
     * @return 
     */
    void *getArgumentValueByID(int ID, fgArgumentType *_type = NULL);

    /**
     * 
     * @return 
     */
    fgArgument getNextArgumentStruct();
    /**
     * 
     * @param ID
     * @return 
     */
    fgArgument getArgumentStructByID(int ID);

    /**
     * 
     * @return 
     */
    int getCurrentID();

    /**
     * 
     */
    void clearArguments();
    
    /**
     * 
     * @param i
     * @return 
     */
    inline fgArgument &operator [](int i) {
        m_emptyArgument.reset();
        if((int)m_argv.size() > i)
            return m_argv[i];
        else
            return m_emptyArgument;
    }
    /**
     * 
     * @param i
     * @return 
     */
    inline const fgArgument operator [](int i)const {
        if((int)m_argv.size() > i)
            return m_argv[i];
        else
            return m_emptyArgument;
    }
};


#endif /* FG_INC_ARGUMENT_LIST */
