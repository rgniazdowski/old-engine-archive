/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgScriptCallback.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 5:41 PM
 */

#ifndef FG_INC_SCRIPT_CALLBACK
    #define FG_INC_SCRIPT_CALLBACK
    #define FG_INC_SCRIPT_CALLBACK_BLOCK

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_SCRIPT_MTBLOCK is defined: Do not include ScriptCallback header inside of ScriptMetatables header"
    #endif

    #include "fgBuildConfig.h"
    #include "Event/fgCallback.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #if !defined(FG_USING_LUA) && !defined(FG_USING_LUA_PLUS) && !defined(FG_LUA_STATE_TYPEDEF_HAX)
        #define FG_LUA_STATE_TYPEDEF_HAX

struct lua_State {
    void *_ptr;
};
    #endif

    #include "Util/fgMemory.h"
    #include "GUI/fgGuiCallback.h"
    #include "GFX/Scene/fgGfxSceneCallback.h"

namespace fg {
    namespace script {

        /**
         * 
         */
        class CScriptCallback : public virtual fg::event::CFunctionCallback {
        public:
            // The base type for Script Callback
            typedef fg::event::CFunctionCallback base_type;
    #if defined(FG_USING_LUA_PLUS)
            typedef LuaPlus::LuaFunctionVoid function_type;
    #else
            typedef void function_type; // #ERROR
    #endif /* FG_USING_LUA_PLUS */

            enum CallbackType {
                SCRIPT,
                EVENT_CALLBACK,
                GUI_CALLBACK,
                SCENE_CALLBACK,
                SCENE_TRIGGER_CALLBACK,
                INVALID
            };

        public:
            /**
             * 
             */
            CScriptCallback() :
            m_luaState(NULL),
            m_script(),
            m_function(NULL),
            m_type(INVALID),
            m_argc(0) {
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
            }
            /**
             * 
             * @param function
             */
    #if defined(FG_USING_LUA_PLUS)
            CScriptCallback(lua_State *L,
                            const LuaPlus::LuaObject& function,
                            unsigned short int _argc = 1,
                            const CallbackType _type = EVENT_CALLBACK) :
            m_luaState(L),
            m_script(),
            m_function(NULL),
            m_type(_type),
            m_argc(_argc) {
                // Will use simple malloc because there's no need to call destructor
                // on this type
                m_function = fgMalloc<function_type>();
                *m_function = function_type(function);
            }
    #endif /* FG_USING_LUA_PLUS */
            /**
             * 
             * @param L
             * @param info
             * @param _type
             */
            CScriptCallback(lua_State *L,
                            const char *info,
                            const unsigned short int _argc = 1,
                            CallbackType _type = EVENT_CALLBACK);
            /**
             * 
             */
            virtual ~CScriptCallback() {
                m_luaState = NULL;
                if(m_function) {
                    fgFree(m_function);
                }
                m_function = NULL;
                m_script.clear();
            }
            /**
             * 
             * @param L
             */
            void setState(lua_State *L) {
                m_luaState = L;
            }
            /**
             * 
             * @param function
             */
    #if defined(FG_USING_LUA_PLUS)
            void setFunction(const LuaPlus::LuaObject& function) {
                if(!m_function) {
                    m_function = fgMalloc<function_type>();
                }
                if(!function.GetCState())
                    return;
                if(!m_luaState)
                    m_luaState = function.GetCState();
                *m_function = function_type(function);
                if(m_type == INVALID)
                    m_type = EVENT_CALLBACK;
            }
    #endif /* FG_USING_LUA_PLUS */
            /**
             * 
             * @param script
             */
            void setScript(const char *script) {
                if(!script)
                    return;
                if(strlen(script) < 1)
                    return;
                m_script = script;
                m_type = SCRIPT;
            }
            /**
             * 
             * @param type
             */
            void setType(const CallbackType type) {
                if(type != INVALID)
                    m_type = type;
            }
            /**
             * 
             * @return 
             */
            CallbackType getType(void) const {
                return m_type;
            }
            /**
             * 
             * @param argc
             */
            void setArgC(const unsigned short int argc) {
                m_argc = argc;
            }
            /**
             * 
             * @return 
             */
            unsigned short int getArgC(void) const {
                return m_argc;
            }
            /**
             * 
             * @return 
             */
            virtual fgBool Call(void);
            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList *argv);
            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void *pSystemData);
            
            /**
             *
             */
            function_type* getScriptFunction(void) const {
                return m_function;
            }

        private:
    #if defined(FG_USING_LUA_PLUS) || defined(FG_USING_LUA)
            ///
            lua_State *m_luaState;
    #else
            void *m_luaState;
    #endif /* LUA_PLUS / LUA */
            ///
            std::string m_script;
            ///
            function_type *m_function;
            ///
            CallbackType m_type;
            ///
            unsigned short int m_argc;
        };

        /**
         *
         */
        class CScriptGuiCallback : public CScriptCallback, public fg::gui::CGuiCallback {
        public:
            ///
            typedef CScriptGuiCallback self_type;
            ///
            typedef CScriptGuiCallback type;

        public:
            /**
             * 
             */
            CScriptGuiCallback(fg::gui::CGuiMain *pGuiMain = NULL) :
            CScriptCallback(),
            fg::gui::CGuiCallback(pGuiMain) {
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
            }
            /**
             * 
             * @param function
             */
    #if defined(FG_USING_LUA_PLUS)
            CScriptGuiCallback(fg::gui::CGuiMain *pGuiMain, lua_State *L,
                               const LuaPlus::LuaObject& function,
                               unsigned short int _argc = 1) :
            CScriptCallback(L, function, _argc, GUI_CALLBACK),
            fg::gui::CGuiCallback(pGuiMain) {
                // Just to be sure - no harm done
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
            }
    #endif /* FG_USING_LUA_PLUS */
    
            
            /**
             * 
             * @param L
             * @param info
             * @param _type
             */
            CScriptGuiCallback(fg::gui::CGuiMain *pGuiMain, lua_State *L,
                               const char *info,
                               const unsigned short int _argc = 1);

            /**
             * 
             * @return 
             */
            virtual fgBool Call(void);

            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList *argv);

            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void *pSystemData);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(fg::gui::CWidget *pWidget);

            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(fg::gui::CGuiMain *pGuiMain, fg::gui::CWidget *pWidget);
        };

        /**
         *
         */
        class CScriptSceneCallback : public CScriptCallback, public fg::gfx::CSceneCallback {
        public:
            ///
            typedef CScriptSceneCallback self_type;
            ///
            typedef CScriptSceneCallback type;

        public:
            /**
             * 
             */
            CScriptSceneCallback() :
            CScriptCallback(),
            fg::gfx::CSceneCallback() {
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
            }
            /**
             * 
             * @param function
             */
    #if defined(FG_USING_LUA_PLUS)
            CScriptSceneCallback(lua_State *L,
                               const LuaPlus::LuaObject& function,
                               unsigned short int _argc = 1) :
            CScriptCallback(L, function, _argc, SCENE_CALLBACK),
            fg::gfx::CSceneCallback() {
                // Just to be sure - no harm done
                fg::event::CFunctionCallback::setFunction((fg::event::CFunctionCallback::Function)NULL);
            }
    #endif /* FG_USING_LUA_PLUS */
            /**
             * 
             * @param L
             * @param info
             * @param _type
             */
            CScriptSceneCallback(lua_State *L,
                               const char *info,
                               const unsigned short int _argc = 1);

            /**
             * 
             * @return 
             */
            virtual fgBool Call(void);

            /**
             * 
             * @param argv
             * @return 
             */
            virtual fgBool Call(fg::event::CArgumentList *argv);

            /**
             * 
             * @param pSystemData
             * @return 
             */
            virtual fgBool Call(void *pSystemData);

            /**
             * 
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(fg::gfx::CSceneNode* pNodeA);

            /**
             * 
             * @param pGuiMain
             * @param pWidget
             * @return 
             */
            virtual fgBool Call(fg::gfx::CSceneNode* pNodeA, fg::gfx::CSceneNode* pNodeB);
        };
    };
};

    #undef FG_INC_SCRIPT_CALLBACK_BLOCK
#endif	/* FG_INC_SCRIPT_CALLBACK */
