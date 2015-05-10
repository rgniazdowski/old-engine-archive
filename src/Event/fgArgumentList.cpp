/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgArgumentList.h"
#include "Util/fgMemory.h"

using namespace fg;

//------------------------------------------------------------------------------

event::CArgumentList::CArgumentList() :
m_argv(),
m_maxArgs(FG_ARGUMENT_DEFAULT_COUNT),
m_currentArg(-1),
m_emptyArgument() {
    m_emptyArgument.reset();    
}
//------------------------------------------------------------------------------

event::CArgumentList::CArgumentList(unsigned int max) :
m_argv(),
m_maxArgs(max),
m_currentArg(-1),
m_emptyArgument() {    
    m_emptyArgument.reset();    
}
//------------------------------------------------------------------------------

event::CArgumentList::~CArgumentList() {
    clear();
}
//------------------------------------------------------------------------------

void event::CArgumentList::setMaxCount(unsigned int max) {
    m_maxArgs = max;
}
//------------------------------------------------------------------------------

unsigned int event::CArgumentList::getMaxCount(void) const {
    return m_maxArgs;
}
//------------------------------------------------------------------------------

void event::CArgumentList::push(event::SArgument::Type type, void *value) {
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
            snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, "%s", (char *)value);
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
//------------------------------------------------------------------------------

void event::CArgumentList::push(int int_val) {
    event::SArgument new_argument;
    if(m_argv.size() >= m_maxArgs)
        return;
    new_argument.type = SArgument::Type::ARG_INTEGER;
    new_argument.int_val = int_val;
    m_argv.push_back(new_argument);
}
//------------------------------------------------------------------------------

void event::CArgumentList::push(double double_val) {
    SArgument new_argument;
    if(m_argv.size() >= m_maxArgs)
        return;
    new_argument.type = SArgument::Type::ARG_DOUBLE;
    new_argument.double_val = double_val;
    m_argv.push_back(new_argument);
}
//------------------------------------------------------------------------------

void event::CArgumentList::push(float float_val) {
    SArgument new_argument;
    if(m_argv.size() >= m_maxArgs)
        return;
    new_argument.type = SArgument::Type::ARG_FLOAT;
    new_argument.float_val = float_val;
    m_argv.push_back(new_argument);
}
//------------------------------------------------------------------------------

void event::CArgumentList::push(const char *string) {
    SArgument new_argument;
    if(m_argv.size() >= m_maxArgs)
        return;
    new_argument.type = SArgument::Type::ARG_STRING;
    snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, "%s", (char *)string);
    m_argv.push_back(new_argument);
}
//------------------------------------------------------------------------------

void event::CArgumentList::push(void *custom_pointer) {
    SArgument new_argument;
    if(m_argv.size() >= m_maxArgs)
        return;
    new_argument.type = SArgument::Type::ARG_POINTER;
    new_argument.custom_pointer = custom_pointer;
    m_argv.push_back(new_argument);
}
//------------------------------------------------------------------------------

int event::CArgumentList::getCount(void) const {
    return m_argv.size();
}
//------------------------------------------------------------------------------

void event::CArgumentList::reset(void) {
    m_currentArg = -1; // FIXME
}
//------------------------------------------------------------------------------

void* event::CArgumentList::getNextValue(SArgument::Type* type) {
    m_currentArg = m_currentArg + 1;
    if(m_currentArg >= getCount()) {
        //	ArgumentList::Reset();
        m_currentArg = getCount();
        if(type != NULL)
            *type = SArgument::Type::ARG_NONE;
        return NULL;
    }

    return event::CArgumentList::getValueByID(m_currentArg, type);
}
//------------------------------------------------------------------------------

void* event::CArgumentList::getValueByID(int ID, SArgument::Type *type) {
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
//------------------------------------------------------------------------------

event::SArgument& event::CArgumentList::getNextStruct(void) {
    m_currentArg = m_currentArg + 1;
    if(m_currentArg >= getCount()) {
        m_currentArg = getCount();
        m_emptyArgument.reset();
        return m_emptyArgument;
    }
    return m_argv[m_currentArg];
}
//------------------------------------------------------------------------------

event::SArgument& event::CArgumentList::getStructByID(int ID) {
    if(ID >= 0 && ID < getCount()) {
        return m_argv[ID];
    } else {
        m_emptyArgument.reset();
        return m_emptyArgument;
    }
}
//------------------------------------------------------------------------------

event::SArgument const& event::CArgumentList::getStructByID(int ID) const {
    if(ID >= 0 && ID < getCount()) {
        return m_argv[ID];
    } else {
        return m_emptyArgument;
    }
}
//------------------------------------------------------------------------------

fgBool event::CArgumentList::isNext(void) const {
    if((m_currentArg + 1) >= getCount())
        return FG_FALSE;
    else
        return FG_TRUE;
}
//------------------------------------------------------------------------------

int event::CArgumentList::getCurrentID(void) const {
    return m_currentArg;
}
//------------------------------------------------------------------------------

void event::CArgumentList::clear(void) {
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
    m_argv.clear_optimised();
    reset();
}
//------------------------------------------------------------------------------
