/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgScriptCD.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 4:45 PM
 */

#ifndef _FG_SCRIPT_CD_H_
    #define _FG_SCRIPT_CD_H_
    #define _FG_SCRIPT_CD_H_BLOCK_  

    #if defined(_FG_SCRIPT_MT_H_BLOCK_)
        #error "FG_SCRIPT_MT_H_BLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(_FG_EVENT_DEFINITIONS_H_BLOCK_)
        #error "FG_EVENT_DEFINITIONS_H_BLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #ifndef _FG_GFX_TYPES_H_
        #include "GFX/fgGFXTypes.h"
    #endif

    #ifndef _FG_SCRIPT_MT_H_
        #include "fgScriptMT.h"
    #endif

    #ifndef _FG_GUI_WIDGET_H_
        #include "GUI/fgGuiWidget.h"
    #endif

    #ifndef _FG_EVENT_DEFINITIONS_H_
        #include "Event/fgEventDefinitions.h"
    #endif

    #include "fgLog.h"

class fgScriptSubsystem;

/**
 * 
 */
class fgScriptCD {
    friend class fgScriptSubsystem;
private:
    /**
     * 
     */
    fgScriptCD() { }
    /**
     *
     */
    ~fgScriptCD() { }

private:

};

////////////////////////////////////////////////////////////////////////////////

    #if defined(FG_USING_LUA_PLUS)

namespace LPCD {

    /***************************************************************************
     * FG VECTOR 2I
     **************************************************************************/

    template<> struct Type<fgVector2i> {
        static inline void Push(lua_State* L, const fgVector2i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector2i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR2I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR2I_MT_ID)];
        }
        static inline fgVector2i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector2i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector2i&> : public Type<fgVector2i> {
    };

    template<> struct Type<const fgVector2i&> : public Type<fgVector2i> {
    };

    /***************************************************************************
     * FG VECTOR 2F
     **************************************************************************/

    template<> struct Type<fgVector2f> {
        static inline void Push(lua_State* L, const fgVector2f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector2f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR2F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR2F_MT_ID)];
        }
        static inline fgVector2f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgVector2f* ptr = (fgVector2f *)state->UnBoxPointer(idx);
            return *ptr;
        }
    };

    template<> struct Type<fgVector2f&> : public Type<fgVector2f> {
    };

    template<> struct Type<const fgVector2f&> : public Type<fgVector2f> {
    };

    /***************************************************************************
     * FG VECTOR 3I
     **************************************************************************/

    template<> struct Type<fgVector3i> {
        static inline void Push(lua_State* L, const fgVector3i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector3i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR3I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR3I_MT_ID)];
        }
        static inline fgVector3i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector3i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3i&> : public Type<fgVector3i> {
    };

    template<> struct Type<const fgVector3i&> : public Type<fgVector3i> {
    };

    /***************************************************************************
     * FG VECTOR 3F
     **************************************************************************/

    template<> struct Type<fgVector3f> {
        static inline void Push(lua_State* L, const fgVector3f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector3f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR3F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR3F_MT_ID)];
        }
        static inline fgVector3f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector3f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3f&> : public Type<fgVector3f> {
    };

    template<> struct Type<const fgVector3f&> : public Type<fgVector3f> {
    };

    /***************************************************************************
     * FG VECTOR 4I
     **************************************************************************/

    template<> struct Type<fgVector4i> {
        static inline void Push(lua_State* L, const fgVector4i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector4i]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR4I_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR4I_MT_ID)];
        }
        static inline fgVector4i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector4i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector4i&> : public Type<fgVector4i> {
    };

    template<> struct Type<const fgVector4i&> : public Type<fgVector4i> {
    };

    /***************************************************************************
     * FG VECTOR 4F
     **************************************************************************/

    template<> struct Type<fgVector4f> {
        static inline void Push(lua_State* L, const fgVector4f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector4f]", ptr, (uintptr_t)ptr);
        #endif
            obj.SetMetatable(state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR4F_MT_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::VECTOR4F_MT_ID)];
        }
        static inline fgVector4f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector4f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector4f&> : public Type<fgVector4f> {
    };

    template<> struct Type<const fgVector4f&> : public Type<fgVector4f> {
    };
}

////////////////////////////////////////////////////////////////////////////////

namespace LPCD {

    template<> struct Type<std::string> {
        static inline void Push(lua_State* L, const std::string& value) {
            lua_pushstring(L, value.c_str());
        }
        static inline bool Match(lua_State* L, int idx) {
            return lua_type(L, idx) == LUA_TSTRING;
        }
        static inline std::string Get(lua_State* L, int idx) {
            return lua_tostring(L, idx);
        }
    };

    template<> struct Type<std::string&> : public Type<std::string> {
    };

    template<> struct Type<const std::string&> : public Type<std::string> {
    };

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgResource pointer parameter *
     **************************************************************************/

    template<> struct Type<fgResource *> {
        static inline void Push(lua_State* L, const fgResource * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            // #FIXME - some checking if the pointer isn't null (!)
            fgScriptMT::METAID metaID = fgScriptMT::getMetatableIDFromResourceType(value->getResourceType());
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s]", value, (uintptr_t)value, value->getNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result;// = (obj.GetMetatable() == state->GetRegistry()[fgScriptMetatables::getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar. No, really fucked up
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgResource * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgResource *pResource = (fgResource *)state->UnBoxPointer(idx);
            return pResource;
        }
    };

    template<> struct Type<fgResource *&> : public Type<fgResource *> {
    };

    template<> struct Type<const fgResource *&> : public Type<fgResource *> {
    };

    /***************************************************************************
     * fgGuiWidget pointer parameter *
     **************************************************************************/

    template<> struct Type<fgGuiWidget *> {
        static inline void Push(lua_State* L, const fgGuiWidget * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fgScriptMT::METAID metaID = fgScriptMT::getMetatableIDFromWidgetType(value->getType());
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type_name[%s]", value, (uintptr_t)value, value->getNameStr(), value->getTypeNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result;// = (obj.GetMetatable() == state->GetRegistry()[fgScriptMetatables::getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID)]);
            // This is fubar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgGuiWidget * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgGuiWidget *pWidget = (fgGuiWidget *)state->UnBoxPointer(idx);
            return pWidget;
        }
    };

    template<> struct Type<fgGuiWidget *&> : public Type<fgGuiWidget *> {
    };

    template<> struct Type<const fgGuiWidget *&> : public Type<fgGuiWidget *> {
    };

    ////////////////////////////////////////////////////////////////////////////
    // FG GUI STYLE STRUCTURES
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgGuiStyleContent pointer parameter *
     **************************************************************************/

    template<> struct Type<fgGuiStyleContent *> {
        static inline void Push(lua_State* L, const fgGuiStyleContent * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fgScriptMT::METAID metaID = fgScriptMT::GUI_STYLE_CONTENT_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiStyleContent]", value, (uintptr_t)value);
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_CONTENT_MT_ID)]);
            // This is fubar
            //result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgGuiStyleContent * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgGuiStyleContent *pStyleContent = (fgGuiStyleContent *)state->UnBoxPointer(idx);
            return pStyleContent;
        }
    };

    template<> struct Type<fgGuiStyleContent *&> : public Type<fgGuiStyleContent *> {
    };

    template<> struct Type<const fgGuiStyleContent *&> : public Type<fgGuiStyleContent *> {
    };

    /***************************************************************************
     * FG GUI SIZE STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiSize> {
        static inline void Push(lua_State* L, const fgGuiSize& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiSize]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_SIZE_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_SIZE_MT_ID)];
        }
        static inline fgGuiSize Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiSize*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiSize&> : public Type<fgGuiSize> {
    };

    template<> struct Type<const fgGuiSize&> : public Type<fgGuiSize> {
    };

    /***************************************************************************
     * FG GUI BACKGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBackground> {
        static inline void Push(lua_State* L, const fgGuiBackground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBackground]", ptr, (uintptr_t)ptr);
            //FG_LOG_DEBUG("Script: LPCD Push: type_name[fgGuiBackground], color[%.2f %.2f %.2f %.2f]", value.color.r, value.color.g, value.color.b, value.color.a);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BACKGROUND_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BACKGROUND_MT_ID)];
        }
        static inline fgGuiBackground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBackground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBackground&> : public Type<fgGuiBackground> {
    };

    template<> struct Type<const fgGuiBackground&> : public Type<fgGuiBackground> {
    };

    /***************************************************************************
     * FG GUI FOREGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiForeground> {
        static inline void Push(lua_State* L, const fgGuiForeground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiForeground]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_FOREGROUND_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_FOREGROUND_MT_ID)];
        }
        static inline fgGuiForeground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiForeground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiForeground&> : public Type<fgGuiForeground> {
    };

    template<> struct Type<const fgGuiForeground&> : public Type<fgGuiForeground> {
    };

    /***************************************************************************
     * FG GUI MARGIN/PADDING STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiMargin> {
        static inline void Push(lua_State* L, const fgGuiMargin& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiMargin]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_MARGIN_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_MARGIN_MT_ID)];
        }
        static inline fgGuiMargin Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiMargin*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiMargin&> : public Type<fgGuiMargin> {
    };

    template<> struct Type<const fgGuiMargin&> : public Type<fgGuiMargin> {
    };

    /***************************************************************************
     * FG GUI BORDER INFO STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBorderInfo> {
        static inline void Push(lua_State* L, const fgGuiBorderInfo& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBorderInfo]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_INFO_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_INFO_MT_ID)];
        }
        static inline fgGuiBorderInfo Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBorderInfo*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBorderInfo&> : public Type<fgGuiBorderInfo> {
    };

    template<> struct Type<const fgGuiBorderInfo&> : public Type<fgGuiBorderInfo> {
    };

    /***************************************************************************
     * FG GUI BORDER STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBorder> {
        static inline void Push(lua_State* L, const fgGuiBorder& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBorder]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_MT_ID)];
        }
        static inline fgGuiBorder Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBorder*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBorder&> : public Type<fgGuiBorder> {
    };

    template<> struct Type<const fgGuiBorder&> : public Type<fgGuiBorder> {
    };

    /***************************************************************************
     * FG GUI POSITION STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiPosition> {
        static inline void Push(lua_State* L, const fgGuiPosition& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiPosition]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_POSITION_MT_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_POSITION_MT_ID)];
        }
        static inline fgGuiPosition Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiPosition*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiPosition&> : public Type<fgGuiPosition> {
    };

    template<> struct Type<const fgGuiPosition&> : public Type<fgGuiPosition> {
    };

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

    template<> struct Type<fgGuiUnitType> : public Type<int> {
        static inline fgGuiUnitType Get(lua_State* L, int idx) {
            return (fgGuiUnitType)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiUnitType&> : public Type<fgGuiUnitType> {
    };

    template<> struct Type<const fgGuiUnitType&> : public Type<fgGuiUnitType> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiBorderStyle> : public Type<int> {
        static inline fgGuiBorderStyle Get(lua_State* L, int idx) {
            return (fgGuiBorderStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBorderStyle&> : public Type<fgGuiBorderStyle> {
    };

    template<> struct Type<const fgGuiBorderStyle&> : public Type<fgGuiBorderStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiBorderWhich> : public Type<int> {
        static inline fgGuiBorderWhich Get(lua_State* L, int idx) {
            return (fgGuiBorderWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBorderWhich&> : public Type<fgGuiBorderWhich> {
    };

    template<> struct Type<const fgGuiBorderWhich&> : public Type<fgGuiBorderWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiBackgroundStyle> : public Type<int> {
        static inline fgGuiBackgroundStyle Get(lua_State* L, int idx) {
            return (fgGuiBackgroundStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBackgroundStyle&> : public Type<fgGuiBackgroundStyle> {
    };

    template<> struct Type<const fgGuiBackgroundStyle&> : public Type<fgGuiBackgroundStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiMarginWhich> : public Type<int> {
        static inline fgGuiMarginWhich Get(lua_State* L, int idx) {
            return (fgGuiMarginWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiMarginWhich&> : public Type<fgGuiMarginWhich> {
    };

    template<> struct Type<const fgGuiMarginWhich&> : public Type<fgGuiMarginWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiPaddingWhich> : public Type<int> {
        static inline fgGuiPaddingWhich Get(lua_State* L, int idx) {
            return (fgGuiPaddingWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiPaddingWhich&> : public Type<fgGuiPaddingWhich> {
    };

    template<> struct Type<const fgGuiPaddingWhich&> : public Type<fgGuiPaddingWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiAlign> : public Type<int> {
        static inline fgGuiAlign Get(lua_State* L, int idx) {
            return (fgGuiAlign)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiAlign&> : public Type<fgGuiAlign> {
    };

    template<> struct Type<const fgGuiAlign&> : public Type<fgGuiAlign> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiPositionStyle> : public Type<int> {
        static inline fgGuiPositionStyle Get(lua_State* L, int idx) {
            return (fgGuiPositionStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiPositionStyle&> : public Type<fgGuiPositionStyle> {
    };

    template<> struct Type<const fgGuiPositionStyle&> : public Type<fgGuiPositionStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiSizeStyle> : public Type<int> {
        static inline fgGuiSizeStyle Get(lua_State* L, int idx) {
            return (fgGuiSizeStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiSizeStyle&> : public Type<fgGuiSizeStyle> {
    };

    template<> struct Type<const fgGuiSizeStyle&> : public Type<fgGuiSizeStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

    template<> struct Type<fgEventType> : public Type<int> {
        static inline fgEventType Get(lua_State* L, int idx) {
            return (fgEventType)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgEventType&> : public Type<fgEventType> {
    };

    template<> struct Type<const fgEventType&> : public Type<fgEventType> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgSwipeDirection> : public Type<int> {
        static inline fgSwipeDirection Get(lua_State* L, int idx) {
            return (fgSwipeDirection)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgSwipeDirection&> : public Type<fgSwipeDirection> {
    };

    template<> struct Type<const fgSwipeDirection&> : public Type<fgSwipeDirection> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgPinchDirection> : public Type<int> {
        static inline fgPinchDirection Get(lua_State* L, int idx) {
            return (fgPinchDirection)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgPinchDirection&> : public Type<fgPinchDirection> {
    };

    template<> struct Type<const fgPinchDirection&> : public Type<fgPinchDirection> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgResourceStatus> : public Type<int> {
        static inline fgResourceStatus Get(lua_State* L, int idx) {
            return (fgResourceStatus)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgResourceStatus&> : public Type<fgResourceStatus> {
    };

    template<> struct Type<const fgResourceStatus&> : public Type<fgResourceStatus> {
    };

    /***************************************************************************
     * fgEvent pointer parameter * (this is union parameter) - only passed as *
     **************************************************************************/

    template<> struct Type<fgEvent *> {
        static inline void Push(lua_State* L, const fgEvent * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_MAIN_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgEvent].union", value, (uintptr_t)value);
        #endif
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_MAIN_MT_ID)]);
            // This is fubar
            //result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgEvent* Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgEvent *pEventUnion = (fgEvent *)state->UnBoxPointer(idx);
            return pEventUnion;
        }
    };

    template<> struct Type<fgEvent *&> : public Type<fgEvent *> {
    };

    template<> struct Type<const fgEvent *&> : public Type<fgEvent *> {
    };

    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * EVENT: fgTouchEvent - structure
     **************************************************************************/

    template<> struct Type<fgTouchEvent> {
        static inline void Push(lua_State* L, const fgTouchEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgTouchEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_TOUCH_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_TOUCH_MT_ID)];
        }
        static inline fgTouchEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgTouchEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgTouchEvent&> : public Type<fgTouchEvent> {
    };

    template<> struct Type<const fgTouchEvent&> : public Type<fgTouchEvent> {
    };

    /***************************************************************************
     * EVENT: fgMouseEvent - structure
     **************************************************************************/

    template<> struct Type<fgMouseEvent> {
        static inline void Push(lua_State* L, const fgMouseEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgMouseEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_MOUSE_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_MOUSE_MT_ID)];
        }
        static inline fgMouseEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgMouseEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgMouseEvent&> : public Type<fgMouseEvent> {
    };

    template<> struct Type<const fgMouseEvent&> : public Type<fgMouseEvent> {
    };

    /***************************************************************************
     * EVENT: fgSwipeEvent - structure
     **************************************************************************/

    template<> struct Type<fgSwipeEvent> {
        static inline void Push(lua_State* L, const fgSwipeEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgSwipeEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_SWIPE_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_MT_ID)];
        }
        static inline fgSwipeEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgSwipeEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgSwipeEvent&> : public Type<fgSwipeEvent> {
    };

    template<> struct Type<const fgSwipeEvent&> : public Type<fgSwipeEvent> {
    };

    /***************************************************************************
     * EVENT: fgSwipePinchEvent - structure
     **************************************************************************/

    template<> struct Type<fgSwipePinchEvent> {
        static inline void Push(lua_State* L, const fgSwipePinchEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgSwipePinchEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_SWIPE_PINCH_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_PINCH_MT_ID)];
        }
        static inline fgSwipePinchEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgSwipePinchEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgSwipePinchEvent&> : public Type<fgSwipePinchEvent> {
    };

    template<> struct Type<const fgSwipePinchEvent&> : public Type<fgSwipePinchEvent> {
    };

    /***************************************************************************
     * EVENT: fgSwipeRotateEvent - structure
     **************************************************************************/

    template<> struct Type<fgSwipeRotateEvent> {
        static inline void Push(lua_State* L, const fgSwipeRotateEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgSwipeRotateEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_SWIPE_ROTATE_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_ROTATE_MT_ID)];
        }
        static inline fgSwipeRotateEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgSwipeRotateEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgSwipeRotateEvent&> : public Type<fgSwipeRotateEvent> {
    };

    template<> struct Type<const fgSwipeRotateEvent&> : public Type<fgSwipeRotateEvent> {
    };

    /***************************************************************************
     * EVENT: fgKeyEvent - structure
     **************************************************************************/

    template<> struct Type<fgKeyEvent> {
        static inline void Push(lua_State* L, const fgKeyEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgKeyEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_KEY_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_KEY_MT_ID)];
        }
        static inline fgKeyEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgKeyEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgKeyEvent&> : public Type<fgKeyEvent> {
    };

    template<> struct Type<const fgKeyEvent&> : public Type<fgKeyEvent> {
    };

    /***************************************************************************
     * EVENT: fgResourceEvent - structure
     **************************************************************************/

    template<> struct Type<fgResourceEvent> {
        static inline void Push(lua_State* L, const fgResourceEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgResourceEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_RESOURCE_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_RESOURCE_MT_ID)];
        }
        static inline fgResourceEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgResourceEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgResourceEvent&> : public Type<fgResourceEvent> {
    };

    template<> struct Type<const fgResourceEvent&> : public Type<fgResourceEvent> {
    };

    /***************************************************************************
     * EVENT: fgVertexStreamEvent - structure
     **************************************************************************/

    template<> struct Type<fgVertexStreamEvent> {
        static inline void Push(lua_State* L, const fgVertexStreamEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVertexStreamEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_VERTEX_STREAM_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_VERTEX_STREAM_MT_ID)];
        }
        static inline fgVertexStreamEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVertexStreamEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVertexStreamEvent&> : public Type<fgVertexStreamEvent> {
    };

    template<> struct Type<const fgVertexStreamEvent&> : public Type<fgVertexStreamEvent> {
    };

    /***************************************************************************
     * EVENT: fgCameraEvent - structure
     **************************************************************************/

    template<> struct Type<fgCameraEvent> {
        static inline void Push(lua_State* L, const fgCameraEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgCameraEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_CAMERA_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_CAMERA_MT_ID)];
        }
        static inline fgCameraEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgCameraEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgCameraEvent&> : public Type<fgCameraEvent> {
    };

    template<> struct Type<const fgCameraEvent&> : public Type<fgCameraEvent> {
    };

    /***************************************************************************
     * EVENT: fgSoundEvent - structure
     **************************************************************************/

    template<> struct Type<fgSoundEvent> {
        static inline void Push(lua_State* L, const fgSoundEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgSoundEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_SOUND_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_SOUND_MT_ID)];
        }
        static inline fgSoundEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgSoundEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgSoundEvent&> : public Type<fgSoundEvent> {
    };

    template<> struct Type<const fgSoundEvent&> : public Type<fgSoundEvent> {
    };

    /***************************************************************************
     * EVENT: fgMenuChangedEvent - structure
     **************************************************************************/

    template<> struct Type<fgMenuChangedEvent> {
        static inline void Push(lua_State* L, const fgMenuChangedEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgMenuChangedEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_MENU_CHANGED_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_MENU_CHANGED_MT_ID)];
        }
        static inline fgMenuChangedEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgMenuChangedEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgMenuChangedEvent&> : public Type<fgMenuChangedEvent> {
    };

    template<> struct Type<const fgMenuChangedEvent&> : public Type<fgMenuChangedEvent> {
    };

    /***************************************************************************
     * EVENT: fgWidgetEvent - structure
     **************************************************************************/

    template<> struct Type<fgWidgetEvent> {
        static inline void Push(lua_State* L, const fgWidgetEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgWidgetEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_WIDGET_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_WIDGET_MT_ID)];
        }
        static inline fgWidgetEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgWidgetEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgWidgetEvent&> : public Type<fgWidgetEvent> {
    };

    template<> struct Type<const fgWidgetEvent&> : public Type<fgWidgetEvent> {
    };

    /***************************************************************************
     * EVENT: fgSensorsEvent - structure
     **************************************************************************/

    template<> struct Type<fgSensorsEvent> {
        static inline void Push(lua_State* L, const fgSensorsEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgSensorsEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_SENSORS_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_SENSORS_MT_ID)];
        }
        static inline fgSensorsEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgSensorsEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgSensorsEvent&> : public Type<fgSensorsEvent> {
    };

    template<> struct Type<const fgSensorsEvent&> : public Type<fgSensorsEvent> {
    };

    /***************************************************************************
     * EVENT: fgControllerDeviceEvent - structure
     **************************************************************************/

    template<> struct Type<fgControllerDeviceEvent> {
        static inline void Push(lua_State* L, const fgControllerDeviceEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgControllerDeviceEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_CONTROLLER_DEVICE_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_DEVICE_MT_ID)];
        }
        static inline fgControllerDeviceEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgControllerDeviceEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgControllerDeviceEvent&> : public Type<fgControllerDeviceEvent> {
    };

    template<> struct Type<const fgControllerDeviceEvent&> : public Type<fgControllerDeviceEvent> {
    };

    /***************************************************************************
     * EVENT: fgControllerButtonEvent - structure
     **************************************************************************/

    template<> struct Type<fgControllerButtonEvent> {
        static inline void Push(lua_State* L, const fgControllerButtonEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgControllerButtonEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_CONTROLLER_BUTTON_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_BUTTON_MT_ID)];
        }
        static inline fgControllerButtonEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgControllerButtonEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgControllerButtonEvent&> : public Type<fgControllerButtonEvent> {
    };

    template<> struct Type<const fgControllerButtonEvent&> : public Type<fgControllerButtonEvent> {
    };

    /***************************************************************************
     * EVENT: fgControllerAxisEvent - structure
     **************************************************************************/

    template<> struct Type<fgControllerAxisEvent> {
        static inline void Push(lua_State* L, const fgControllerAxisEvent& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgControllerAxisEvent]", ptr, (uintptr_t)ptr);
        #endif
            fgScriptMT::METAID metaID = fgScriptMT::EVENT_CONTROLLER_AXIS_MT_ID;
            const char *metatableName = fgScriptMT::getMetatableName(metaID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_AXIS_MT_ID)];
        }
        static inline fgControllerAxisEvent Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgControllerAxisEvent*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgControllerAxisEvent&> : public Type<fgControllerAxisEvent> {
    };

    template<> struct Type<const fgControllerAxisEvent&> : public Type<fgControllerAxisEvent> {
    };

    ////////////////////////////////////////////////////////////////////////////
}

    #endif /* FG_USING_LUA_PLUS */

////////////////////////////////////////////////////////////////////////////////




    #undef _FG_SCRIPT_CD_H_BLOCK_
#endif	/* _FG_SCRIPT_CD_H_ */

