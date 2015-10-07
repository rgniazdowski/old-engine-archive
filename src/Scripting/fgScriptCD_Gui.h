/* 
 * File:   fgScriptCD_Gui.h
 * Author: vigilant
 *
 * Created on October 6, 2015, 9:18 PM
 */

#ifndef FG_INC_SCRIPT_CD_GUI
    #define FG_INC_SCRIPT_CD_GUI
    #define FG_INC_SCRIPT_CD_GUI_BLOCK

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_INC_SCRIPT_MT_BLOCK is defined: Do not include ScriptCD header inside of ScriptMetatables header"
    #endif

    #if defined(FG_INC_EVENT_DEFINITIONS_BLOCK)
        #error "FG_INC_EVENT_DEFINITIONS_BLOCK is defined: Do not include ScriptCD header inside of EventDefinitions header"
    #endif

    #include "fgBuildConfig.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
        #if defined(FG_DEBUG)
            #include "fgLog.h"
        #endif
        #include "fgScriptMT.h"
        #include "GUI/fgGuiWidget.h"

namespace LPCD {

    /***************************************************************************
     * fgGuiWidget pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gui::CWidget *> {
        static inline void Push(lua_State* L, const fg::gui::CWidget * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            if(!value) {
                obj.SetMetatable(fgScriptMT->getMetatable(fg::script::CMetatables::GUI_WIDGET_MT_ID).metaObj);
                return;
            }
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            const unsigned short int metaID =
                    fgScriptMT->getMetatableIDFromWidgetType(value->getType());
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type[%s]",
                         value, (uintptr_t)value,
                         value->getNameStr(), value->getTypeNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            const unsigned int widgetType =
                    fgScriptMT->getWidgetTypeFromMetatableID(metaEnum);
            return (widgetType != fg::gui::WIDGET_UNKNOWN);
        }
        static inline fg::gui::CWidget * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gui::CWidget *pWidget = (fg::gui::CWidget *)state->UnBoxPointer(idx);
            return pWidget;
        }
    };

    template<> struct Type<fg::gui::CWidget *&> : public Type<fg::gui::CWidget *> {
    };

    template<> struct Type<const fg::gui::CWidget *&> : public Type<fg::gui::CWidget *> {
    };

    //--------------------------------------------------------------------------
    // FG GUI STYLE STRUCTURES
    //--------------------------------------------------------------------------

    /***************************************************************************
     * fgGuiStyleContent pointer parameter *
     **************************************************************************/

    template<> struct Type<fg::gui::CStyleContent *> {
        static inline void Push(lua_State* L, const fg::gui::CStyleContent * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_CONTENT_MT_ID;
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::CStyleContent]",
                         value, (uintptr_t)value);
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_CONTENT_MT_ID);
        }
        static inline fg::gui::CStyleContent * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fg::gui::CStyleContent *pStyleContent =
                    (fg::gui::CStyleContent *)state->UnBoxPointer(idx);
            return pStyleContent;
        }
    };

    template<> struct Type<fg::gui::CStyleContent *&> : public Type<fg::gui::CStyleContent *> {
    };

    template<> struct Type<const fg::gui::CStyleContent *&> : public Type<fg::gui::CStyleContent *> {
    };

    /***************************************************************************
     * FG GUI SIZE STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SSize> {
        static inline void Push(lua_State* L, const fg::gui::SSize& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SSize]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_SIZE_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_SIZE_MT_ID);
        }
        static inline fg::gui::SSize Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SSize*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SSize&> : public Type<fg::gui::SSize> {
    };

    template<> struct Type<const fg::gui::SSize&> : public Type<fg::gui::SSize> {
    };

    /***************************************************************************
     * FG GUI BACKGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBackground> {
        static inline void Push(lua_State* L, const fg::gui::SBackground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SBackground]",
                         ptr, (uintptr_t)ptr);
            //FG_LOG_DEBUG("Script: LPCD Push: type[fgGuiBackground], color[%.2f %.2f %.2f %.2f]", value.color.r, value.color.g, value.color.b, value.color.a);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_BACKGROUND_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_BACKGROUND_MT_ID);
        }
        static inline fg::gui::SBackground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBackground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBackground&> : public Type<fg::gui::SBackground> {
    };

    template<> struct Type<const fg::gui::SBackground&> : public Type<fg::gui::SBackground> {
    };

    /***************************************************************************
     * FG GUI FOREGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SForeground> {
        static inline void Push(lua_State* L, const fg::gui::SForeground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SForeground]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_FOREGROUND_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_FOREGROUND_MT_ID);
        }
        static inline fg::gui::SForeground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SForeground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SForeground&> : public Type<fg::gui::SForeground> {
    };

    template<> struct Type<const fg::gui::SForeground&> : public Type<fg::gui::SForeground> {
    };

    /***************************************************************************
     * FG GUI MARGIN STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SMargin> {
        static inline void Push(lua_State* L, const fg::gui::SMargin& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SMargin]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_MARGIN_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_MARGIN_MT_ID);
        }
        static inline fg::gui::SMargin Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SMargin*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SMargin&> : public Type<fg::gui::SMargin> {
    };

    template<> struct Type<const fg::gui::SMargin&> : public Type<fg::gui::SMargin> {
    };

    /***************************************************************************
     * FG GUI PADDING STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SPadding> {
        static inline void Push(lua_State* L, const fg::gui::SPadding& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SPadding]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_PADDING_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_PADDING_MT_ID);
        }
        static inline fg::gui::SPadding Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SPadding*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SPadding&> : public Type<fg::gui::SPadding> {
    };

    template<> struct Type<const fg::gui::SPadding&> : public Type<fg::gui::SPadding> {
    };

    /***************************************************************************
     * FG GUI BORDER INFO STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBorderGroup> {
        static inline void Push(lua_State* L, const fg::gui::SBorderGroup& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SBorderGroup]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID =
                    fg::script::CMetatables::GUI_STYLE_BORDER_INFO_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_BORDER_INFO_MT_ID);
        }
        static inline fg::gui::SBorderGroup Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBorderGroup*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBorderGroup&> : public Type<fg::gui::SBorderGroup> {
    };

    template<> struct Type<const fg::gui::SBorderGroup&> : public Type<fg::gui::SBorderGroup> {
    };

    /***************************************************************************
     * FG GUI BORDER STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SBorder> {
        static inline void Push(lua_State* L, const fg::gui::SBorder& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SGuiBorder]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::GUI_STYLE_BORDER_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_BORDER_MT_ID);
        }
        static inline fg::gui::SBorder Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SBorder*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SBorder&> : public Type<fg::gui::SBorder> {
    };

    template<> struct Type<const fg::gui::SBorder&> : public Type<fg::gui::SBorder> {
    };

    /***************************************************************************
     * FG GUI POSITION STRUCTURE
     **************************************************************************/

    template<> struct Type<fg::gui::SPosition> {
        static inline void Push(lua_State* L, const fg::gui::SPosition& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type[gui::SPosition]",
                         ptr, (uintptr_t)ptr);
        #endif
            const unsigned short int metaID = fg::script::CMetatables::GUI_STYLE_POSITION_MT_ID;
            obj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            if(!obj.IsUserdata())
                return false;
            const int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
            return (metaEnum == (int)fg::script::CMetatables::GUI_STYLE_POSITION_MT_ID);
        }
        static inline fg::gui::SPosition Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fg::gui::SPosition*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fg::gui::SPosition&> : public Type<fg::gui::SPosition> {
    };

    template<> struct Type<const fg::gui::SPosition&> : public Type<fg::gui::SPosition> {
    };

    //--------------------------------------------------------------------------

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

        #define FG_CONV_CD_TYPE fg::gui::CWidget::EventState

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned int> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned int>::Push(L, static_cast<unsigned int>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned int>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::Unit

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SBorder::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SBorder::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SBackground::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SMargin::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SPadding::Which

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::Align

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SPosition::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

        #define FG_CONV_CD_TYPE fg::gui::SSize::Style

    template<> struct Type<FG_CONV_CD_TYPE> : public Type<unsigned char> {
        static inline void Push(lua_State* L, FG_CONV_CD_TYPE value) {
            Type<unsigned char>::Push(L, static_cast<unsigned char>(value));
        }
        static inline FG_CONV_CD_TYPE Get(lua_State* L, int idx) {
            return (FG_CONV_CD_TYPE)Type<unsigned char>::Get(L, idx);
        }
    };

    template<> struct Type<FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

    template<> struct Type<const FG_CONV_CD_TYPE &> : public Type<FG_CONV_CD_TYPE> {
    };

        #undef FG_CONV_CD_TYPE

    //--------------------------------------------------------------------------

} // namespace LPCD

    #endif /* FG_USING_LUA_PLUS */

    #undef FG_INC_SCRIPT_CD_GUI_BLOCK
#endif	/* FG_INC_SCRIPT_CD_GUI */
