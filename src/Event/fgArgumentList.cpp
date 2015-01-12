/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgArgumentList.h"
#include "Util/fgMemory.h"

#include <iostream>

#ifdef FG_USING_MARMALADE
#include "s3eMemory.h"
#endif

/*
 *
 */
fg::event::CArgumentList::CArgumentList() {
    reset();
    m_maxArgs = FG_ARGUMENT_DEFAULT_COUNT;
}

/*
 *
 */
fg::event::CArgumentList::CArgumentList(int max) {
    reset();
    m_maxArgs = max;
}

/*
 *
 */
fg::event::CArgumentList::~CArgumentList() {
    clear();
}

/*
 *
 */
void fg::event::CArgumentList::setMaxCount(int max) {
    m_maxArgs = max;
}

/*
 *
 */
int fg::event::CArgumentList::getMaxCount(void) {
    return m_maxArgs;
}

/*
 *
 */
void fg::event::CArgumentList::push(fg::event::SArgument::Type type, void *value) {
    SArgument new_argument;
    new_argument.reset();
    new_argument.type = type;
    switch(type) {
        case SArgument::Type::ARG_INTEGER:
            new_argument.int_val = *((int*)value);
            break;
        case SArgument::Type::ARG_DOUBLE:
            new_argument.double_val = *((double*)value);
            break;
        case SArgument::Type::ARG_FLOAT:
            new_argument.float_val = *((float*)value);
            break;
        case SArgument::Type::ARG_STRING:
            snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, (char *)value);
            break;
        case SArgument::Type::ARG_POINTER:
        case SArgument::Type::ARG_TMP_POINTER:
            new_argument.custom_pointer = value;
            break;
        default:
            new_argument.type = SArgument::Type::ARG_NONE;
            break;
    }

    if(new_argument.type == SArgument::Type::ARG_NONE)
        return;

    m_argv.push_back(new_argument);
}

/*
 *
 */
void fg::event::CArgumentList::push(int int_val) {
    fg::event::SArgument new_argument;
    if((m_argc + 1) > m_maxArgs)
        return;
    m_argc = m_argc + 1;
    new_argument.type = SArgument::Type::ARG_INTEGER;
    new_argument.int_val = int_val;
    m_argv.push_back(new_argument);
}

/*
 *
 */
void fg::event::CArgumentList::push(double double_val) {
    SArgument new_argument;
    if((m_argc + 1) > m_maxArgs)
        return;
    m_argc = m_argc + 1;
    new_argument.type = SArgument::Type::ARG_DOUBLE;
    new_argument.double_val = double_val;
    m_argv.push_back(new_argument);
}

/*
 *
 */
void fg::event::CArgumentList::push(float float_val) {
    SArgument new_argument;
    if((m_argc + 1) > m_maxArgs)
        return;
    m_argc = m_argc + 1;

    new_argument.type = SArgument::Type::ARG_FLOAT;
    new_argument.float_val = float_val;
    m_argv.push_back(new_argument);
}

/*
 *
 */
void fg::event::CArgumentList::push(const char *string) {
    SArgument new_argument;
    if((m_argc + 1) > m_maxArgs)
        return;
    m_argc = m_argc + 1;

    new_argument.type = SArgument::Type::ARG_STRING;
    snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, (char *)string);
    m_argv.push_back(new_argument);
}

/*
 *
 */
void fg::event::CArgumentList::push(void *custom_pointer) {
    SArgument new_argument;

    if((m_argc + 1) > m_maxArgs)
        return;
    m_argc = m_argc + 1;

    new_argument.type = SArgument::Type::ARG_POINTER;
    new_argument.custom_pointer = custom_pointer;
    m_argv.push_back(new_argument);
}

/*
 *
 */
int fg::event::CArgumentList::getCount() {
    m_argc = m_argv.size();
    return m_argc;
}

/*
 *
 */
void fg::event::CArgumentList::reset() {
    m_currentArg = -1; // FIXME
}

/*
 *
 */
void* fg::event::CArgumentList::getNextValue(SArgument::Type* type) {
    m_currentArg = m_currentArg + 1;
    if(m_currentArg >= getCount()) {
        //	ArgumentList::Reset();
        m_currentArg = getCount();
        if(type != NULL)
            *type = SArgument::Type::ARG_NONE;
        return NULL;
    }

    return fg::event::CArgumentList::getValueByID(m_currentArg, type);
}

/*
 *
 */
void* fg::event::CArgumentList::getValueByID(int ID, SArgument::Type *type) {
    if(ID >= 0 && ID < getCount()) {
        if(type != NULL)
            *type = m_argv[ID].type;
        switch(m_argv[ID].type) {
            case SArgument::Type::ARG_INTEGER:
                return (void *)(&m_argv[ID].int_val);
                break;
            case SArgument::Type::ARG_DOUBLE:
                return (void *)(&m_argv[ID].double_val);
                break;
            case SArgument::Type::ARG_FLOAT:
                return (void *)(&m_argv[ID].float_val);
                break;
            case SArgument::Type::ARG_STRING:
                return (void *)m_argv[ID].string;
                break;
            case SArgument::Type::ARG_POINTER:
            case SArgument::Type::ARG_TMP_POINTER:
                return m_argv[ID].custom_pointer;
                break;
            default:
                if(type != NULL)
                    *type = SArgument::Type::ARG_NONE;
                return NULL;
                break;
        }
    }
    if(type != NULL)
        *type = SArgument::Type::ARG_NONE;
    return NULL;
}

/*
 *
 */
fg::event::SArgument fg::event::CArgumentList::getNextStruct(void) {
    m_currentArg = m_currentArg + 1;
    if(m_currentArg >= getCount()) {
        //ArgumentList::Reset();
        m_currentArg = getCount();
        SArgument new_argument;
        new_argument.type = SArgument::Type::ARG_NONE;
        return new_argument;
    }
    return m_argv[m_currentArg];
}

/*
 *
 */
fg::event::SArgument fg::event::CArgumentList::getStructByID(int ID) {
    if(ID >= 0 && ID < getCount()) {
        return m_argv[ID];
    } else {
        SArgument new_argument;
        new_argument.type = SArgument::Type::ARG_NONE;
        return new_argument;
    }
}

/*
 *
 */
fgBool fg::event::CArgumentList::isNext(void) {
    if((m_currentArg + 1) >= getCount())
        return FG_FALSE;
    else
        return FG_TRUE;
}

/*
 *
 */
int fg::event::CArgumentList::getCurrentID(void) {
    return m_currentArg;
}

/*
 * This function  frees the memory  held by the  arguments (argv)
 * The rule is that when some value/structure/pointer is put into
 * the argument list it is being managed by the class, so it also
 * needs to be freed in this function.
 */
void fg::event::CArgumentList::clear(void) {
    reset();
    while(isNext()) {
        SArgument arg = getNextStruct();
        // ARGUMENT TEMP POINTER is a special kind of argument
        // it means that if it's past as a argument (pointer to struct / object)
        // it needs to be freed together with the argument list (argument list takes the ownership)
        // This still needs fixing because no destructor is called (free function instead)
        // That is deprecated. Handling allocator maybe?
        if(arg.type == SArgument::Type::ARG_TMP_POINTER) {
            if(arg.custom_pointer != NULL) {
                fgFree(arg.custom_pointer);
            }
        }
    }
    m_argv.clear();
    m_argc = 0;
    reset();
}
