/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_SCRIPT_SUBSYSTEM
    #define FG_INC_SCRIPT_SUBSYSTEM
    #define FG_INC_SCRIPT_SUBSYSTEM_BLOCK

    #if defined(FG_INC_GUI_WIDGET_BLOCK)
        #error "FG_GUI_WIDGETBLOCK is defined: Do not include ScriptSubsystem header inside of Widget header"
    #endif

    #if defined(FG_INC_GUI_MAIN_BLOCK)
        #error "FG_GUI_MAINBLOCK is defined: Do not include ScriptSubsystem header inside of GuiMain header"
    #endif

    #include "fgBuildConfig.h"
    #include "fgManagerBase.h"
    #include "Util/fgMemory.h"
    #include "Util/fgBTreeMap.h"
    #include "Util/fgTag.h"

    #define FG_MANAGER_SCRIPT       0x00004000
    #define FG_SUBSYSTEM_SCRIPT     0x00004000

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif
// Metatables info
    #include "fgScriptMT.h"
    #include "fgLog.h"

    #if !defined(FG_USING_LUA) && !defined(FG_USING_LUA_PLUS) && !defined(FG_LUA_STATE_TYPEDEF_HAX)
        #define FG_LUA_STATE_TYPEDEF_HAX

struct lua_State {
    void *_ptr;
};
    #endif

    #include "Resource/fgManagedObject.h"
    #include "Event/fgCallback.h"

namespace fg {
    namespace script {
        class CScriptSubsystem;
    } // namespace script
} // namespace fg

    #define FG_TAG_SCRIPT_MANAGER_NAME  "ScriptSubsystem"
    #define FG_TAG_SCRIPT_SUBSYSTEM_NAME FG_TAG_SCRIPT_MANAGER_NAME
//#define FG_TAG_MANAGER_BASE_ID        20 //#FIXME - something automatic maybe?
    #define FG_TAG_SCRIPT_MANAGER       FG_TAG_TYPE(fg::script::CScriptSubsystem)
    #define FG_TAG_SCRIPT_SUBSYSTEM     FG_TAG_SCRIPT_MANAGER
//FG_TAG_TEMPLATE(fgScriptSubsystem, FG_TAG_SCRIPT_MANAGER_NAME, FG_TAG_SCRIPT_MANAGER_ID);
FG_TAG_TEMPLATE_ID_AUTO(fg::script::CScriptSubsystem, FG_TAG_SCRIPT_SUBSYSTEM_NAME);

namespace fg {

    namespace script {

        /// Special handle type for script subsystem
        typedef FG_TAG_SCRIPT_SUBSYSTEM ScriptSubsystemTag;
        //typedef FG_TAG_SCRIPT_SUBSYSTEM fgScriptSubsystemTag;

        /// Every 60s call global GC request
        const unsigned int DEFAULT_GC_INTERVAL = 5000;

        /**
         * 
         */
        class CScriptSubsystem : public fg::base::CManager {
        public:
            ///
            typedef fg::base::CManager base_type;
            ///
            typedef ScriptSubsystemTag tag_type;

        private:

            struct SUserDataObject {
    #if defined(FG_USING_LUA_PLUS)
                ///
                LuaPlus::LuaObject obj;
                ///
                fgBool isBound;
                /**
                 * 
                 */
                SUserDataObject() : obj(), isBound(FG_FALSE) { }
                /**
                 * 
                 * @param _obj
                 * @param _isBound
                 */
                SUserDataObject(LuaPlus::LuaObject &_obj, fgBool _isBound = FG_FALSE) :
                isBound(_isBound) {
                    obj = _obj;
                }
    #else
    #endif
            };
            ///
            typedef util::btree_map<uintptr_t, SUserDataObject> UserDataObjectMap;
            ///
            typedef UserDataObjectMap::iterator UserDataObjectMapItor;

            /**
             * This enum correspond to ones in fgScriptMT/Metatables - just managers
             */
            enum {
                EMPTY_MT_MGR = 0,

                //
                // FG main namespaces
                //
                FG_NAMESPACE,
                FG_GFX_NAMESPACE,
                FG_GUI_NAMESPACE,
                FG_SFX_NAMESPACE,
                //
                // Main managers
                //
                EVENT_MGR,
                RESOURCE_MGR,
                SHADER_MGR,
                SCENE2D_MGR,
                SCENE3D_MGR,
                PARTICLE_MGR,
                GUI_MAIN,
                WIDGET_MGR,
                STYLE_MGR,
                SOUND_MGR,
                GAME_MAIN_MGR,

                NUM_MGR_METATABLES
            };

    #if defined(FG_USING_LUA_PLUS)
            /// Main global state for LUA
            static LuaPlus::LuaState *m_luaState;
            /// Globals table
            static LuaPlus::LuaObject m_globals;
            ///
            static LuaPlus::LuaObject m_fgObj;
            ///
            static UserDataObjectMap m_userDataObjectMap;
            /// Storage for metatables
            LuaPlus::LuaObject m_mgrMetatables[NUM_MGR_METATABLES];

    #else
            static void *m_luaState;
    #endif

            /// Pointer to the external gui main object
            static fg::base::CManager *m_pGuiMain;
            /// Pointer to the external event manager
            static fg::base::CManager *m_pEventMgr;
            /// Pointer to the external resource manager
            static fg::base::CManager *m_pResourceMgr;
            /// Pointer to the external shader manager
            static fg::base::CManager *m_pShaderMgr;
            /// Pointer to the external 2D Scene manager
            static fg::base::CManager *m_p2DSceneMgr;
            /// Pointer to the external 3D Scene manager
            static fg::base::CManager *m_p3DSceneMgr;
            /// Pointer to the external particle manager
            static fg::base::CManager *m_pParticleMgr;
            /// Pointer to the external widget manager
            static fg::base::CManager *m_pWidgetMgr;
            /// Pointer to the external style manager
            static fg::base::CManager *m_pStyleMgr;
            /// Pointer to the external sound manager
            static fg::base::CManager *m_pSoundMgr;
            /// Pointer to the external game main manager
            static fg::base::CManager *m_pGameMainMgr;

            ///
            static fgBool m_isBindingComplete;


            ///
            event::CFunctionCallback *m_cyclicGCCallback;

        public:
            /**
             * 
             */
            CScriptSubsystem();
            /**
             * 
             */
            virtual ~CScriptSubsystem();

        public:
            /**
             * 
             * @param pEventManager
             */
            inline void setEventManager(fg::base::CManager *pEventManager) {
                m_pEventMgr = pEventManager;
            }
            /**
             * 
             * @param pResourceManager
             */
            inline void setResourceManager(fg::base::CManager *pResourceManager) {
                m_pResourceMgr = pResourceManager;
            }
            /**
             * 
             * @param pShaderManager
             */
            inline void setShaderManager(fg::base::CManager *pShaderManager) {
                m_pShaderMgr = pShaderManager;
            }
            /**
             * 
             * @param p2DSceneManager
             */
            inline void set2DSceneManager(fg::base::CManager *p2DSceneManager) {
                m_p2DSceneMgr = p2DSceneManager;
            }
            /**
             * 
             * @param p3DSceneManager
             */
            inline void set3DSceneManager(fg::base::CManager *p3DSceneManager) {
                m_p3DSceneMgr = p3DSceneManager;
            }
            /**
             * 
             * @param pParticleSystem
             */
            inline void setParticleSystem(fg::base::CManager *pParticleSystem) {
                m_pParticleMgr = pParticleSystem;
            }
            /**
             * 
             * @param pGuiMain
             */
            inline void setGuiMain(fg::base::CManager *pGuiMain) {
                m_pGuiMain = pGuiMain;
            }
            /**
             * 
             * @param pWidgetManager
             */
            inline void setWidgetManager(fg::base::CManager *pWidgetManager) {
                m_pWidgetMgr = pWidgetManager;
            }
            /**
             * 
             * @param pStyleManager
             */
            inline void setStyleManager(fg::base::CManager *pStyleManager) {
                m_pStyleMgr = pStyleManager;
            }
            /**
             * 
             * @param pSoundManager
             */
            inline void setSoundManager(fg::base::CManager *pSoundManager) {
                m_pSoundMgr = pSoundManager;
            }
            /**
             * 
             * @param pGameMainManager
             */
            inline void setGameMainManager(fg::base::CManager *pGameMainManager) {
                m_pGameMainMgr = pGameMainManager;
            }

        protected:
            /**
             * 
             */
            virtual void clear(void);

            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static fgBool cyclicGCFunction(void *systemData, void *userData);

        public:
            /**
             * 
             * @return 
             */
            virtual fgBool destroy(void);
            /**
             * 
             * @return 
             */
            virtual fgBool initialize(void);

        public:
            /**
             * 
             * @param filePath
             * @return 
             */
            int executeFile(const char *filePath);
            /**
             * 
             * @param filePath
             * @return 
             */
            inline int executeFile(const std::string& filePath) {
                return executeFile(filePath.c_str());
            }

        public:
    #if defined(FG_USING_LUA_PLUS)
            /**
             * 
             * @return 
             */
            static LuaPlus::LuaState *getLuaState(void) {
                return m_luaState;
            }
    #endif
            /**
             * 
             * @return 
             */
            static lua_State *getCLuaState(void) {
    #if defined(FG_USING_LUA_PLUS)
                if(!m_luaState)
                    return (lua_State *)NULL;
                return m_luaState->GetCState();
    #else
                return (lua_State *)NULL;
    #endif
            }
    #if defined(FG_USING_LUA_PLUS)
            /**
             * 
             * @return 
             */
            static LuaPlus::LuaObject& getGlobals(void) {
                return m_globals;
            }
    #endif

        protected:
            /**
             * 
             * @param L
             * @return 
             */
            static int __isValid(lua_State*L);

            static int __destroy(lua_State* L);

            /**
             * 
             * @param state
             * @return 
             */
            template<class Type, CMetatables::METAID METATABLE_ID>
            static int simpleTypedMallocEvent(lua_State* L);

            /**
             * 
             * @param L
             * @return 
             */
            template<class Type>
            static int simpleTypedFreeGCEvent(lua_State* L);

            /**
             * 
             * @param state
             * @return 
             */
            template<class Type, CMetatables::METAID METATABLE_ID>
            static int simpleInPlaceTypedNewEvent(lua_State* L);

            /**
             * 
             * @param L
             * @return 
             */
            template<class Type>
            static int simpleInPlaceTypedGCEvent(lua_State* L);

            /**
             * 
             * @param L
             * @return 
             */
            static int simpleFreeGCEvent(lua_State* L);

            /**
             * 
             * @param L
             * @return 
             */
            template<class Type, CMetatables::METAID METATABLE_ID>
            static int managedObjectTypedNewEvent(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            template<class HandleType>
            static int managedObjectTypedGCEvent(lua_State* L);
            /**
             * 
             * @param L
             * @return 
             */
            static int managedResourceGCEvent(lua_State* L);
            /**
             * 
             * @param state
             * @return 
             */
            static int newResourceWrapper(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            static int addEventCallbackWrapper(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            static int addTimeoutCallbackWrapper(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            static int addCyclicCallbackWrapper(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            static int addWidgetCallbackWrapper(lua_State *L);

            /**
             * 
             * @param L
             * @return 
             */
            static int addSceneEventCallbackWrapper(lua_State *L);

            /**
             * 
             * @return 
             */
            static int addSceneTriggerCallbackWrapper(lua_State *L);

            /**
             * 
             * @param systemData
             * @param userData
             * @return 
             */
            static fgBool managedObjectDestructorCallback(void *systemData, void *userData);

        private:
            /**
             * 
             * @return 
             */
            fgBool registerConstants(void);
            /**
             * 
             * @return 
             */
            fgBool registerAdditionalTypes(void);
            /**
             * 
             * @return 
             */
            fgBool registerEventManager(void);
            /**
             * 
             * @return 
             */
            fgBool registerResourceManager(void);
            /**
             * 
             * @return
             */
            fgBool registerShaderManager(void);
    #if defined(FG_USING_LUA_PLUS)
            /**
             * 
             * @param metatable
             * @param sceneManager
             * @return 
             */
            fgBool registerSceneManager(LuaPlus::LuaObject &metatable,
                                        const unsigned short int metatableID,
                                        fg::base::CManager *sceneManager,
                                        const char *objectName);
    #else
    #endif /* FG_USING_LUA_PLUS */
            /**
             * 
             * @return
             */
            fgBool register2DSceneManager(void);
            /**
             * 
             * @return
             */
            fgBool register3DSceneManager(void);
            /**
             * 
             * @return 
             */
            fgBool registerPhysics(void);
            /**
             * 
             * @return
             */
            fgBool registerGameEntities(void);
            /**
             * 
             * @return
             */
            fgBool registerParticleSystem(void);
            /**
             * 
             * @return 
             */
            fgBool registerGuiMain(void);
            /**
             * 
             * @return
             */
            fgBool registerWidgetManager(void);
            /**
             * 
             * @return
             */
            fgBool registerStyleManager(void);
            /**
             * 
             * @return
             */
            fgBool registerSoundManager(void);
            /**
             * 
             * @return 
             */
            fgBool registerGameMainManager(void);
        };
    };
};
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fg::script::CMetatables::METAID METATABLE_ID>
int fg::script::CScriptSubsystem::managedObjectTypedNewEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    // Using new operator to create data
    Type *ptr = new Type();
    if(!ptr) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    LuaPlus::LuaObject newObj = state->BoxPointer(ptr);
    uintptr_t offset = (uintptr_t)ptr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple Typed New: ptr[%p], [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMT->getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        FG_LOG_DEBUG("Script: Simple Typed New: metatable will be empty");
    } else {
        //newObj.SetMetatable(state->GetRegistry()[metatableName]);
        newObj.SetMetatable(fgScriptMT->getMetatable(METATABLE_ID).metaObj);
        FG_LOG_DEBUG("Script: Simple Typed New: metatable: id[%d], name[%s]",
                     METATABLE_ID, metatableName);
        ptr->registerOnDestruct(&CScriptSubsystem::managedObjectDestructorCallback, NULL);

    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class HandleType>
int fg::script::CScriptSubsystem::managedObjectTypedGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Managed Object Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d],  HandleType[%s]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil,
                     HandleType::getTagName());

        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Managed Object Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    typedef fg::resource::CManagedObject<HandleType> object_type;
    object_type *pManagedObject = (object_type *)unboxed;
    uintptr_t offset = (uintptr_t)pManagedObject;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Managed Object Typed GC: pointer is not registered: ptr[%p], [offset: %lu], HandleType[%s]", unboxed, offset, HandleType::getTagName());
        return 0;
    }
    FG_LOG_DEBUG("Script: Managed Object Typed GC: name[%s], HandleType[%s], isManaged[%d], [offset: %lu]", pManagedObject->getNameStr(), HandleType::getTagName(), pManagedObject->isManaged(), offset);
    if(pManagedObject->isManaged() == FG_FALSE) {
        // Object is not managed in some manager
        // Can call destructors
        FG_LOG_DEBUG("Script: Managed Object Typed GC: Object is not managed, will be deleted name[%s], ptr[%p], offset[%lu]", pManagedObject->getNameStr(), pManagedObject, offset);
        delete pManagedObject;
        m_userDataObjectMap.erase(it);
    }
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fg::script::CMetatables::METAID METATABLE_ID>
int fg::script::CScriptSubsystem::simpleTypedMallocEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    // This will not check for any arguments...
    // Simple allocation via fgMalloc
    Type *ptr = fgMalloc<Type>();
    if(!ptr) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    new (ptr)Type();
    LuaPlus::LuaObject newObj = state->BoxPointer(ptr);
    uintptr_t offset = (uintptr_t)ptr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple Typed Malloc: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMT->getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        FG_LOG_DEBUG("Script: Simple Typed Malloc: metatable will be empty");
    } else {
        //newObj.SetMetatable(state->GetRegistry()[metatableName]);
        newObj.SetMetatable(fgScriptMT->getMetatable(METATABLE_ID).metaObj);
        FG_LOG_DEBUG("Script: Simple Typed Malloc: metatable: id[%d], name[%s]",
                     METATABLE_ID, metatableName);
    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type>
int fg::script::CScriptSubsystem::simpleTypedFreeGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Simple Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Simple Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Simple Typed GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: Simple Typed GC: calling destructor, freeing memory: ptr[%p], offset[%lu]", unboxed, offset);
    Type *ptrObj = (Type *)unboxed;
    ptrObj->~Type();
    fgFree<Type>(ptrObj, FG_TRUE);
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fg::script::CMetatables::METAID METATABLE_ID>
int fg::script::CScriptSubsystem::simpleInPlaceTypedNewEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    // This will not check for any arguments...
    // Simple allocation via fgMalloc
    //    new (ptr)Type();
    LuaPlus::LuaObject newObj = state->NewUserdata(sizeof (Type));
    void *ptr = newObj.GetUserdata();
    if(!ptr) {
        newObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
        return 1;
    }
    // Create constructor - creates object in specified memory holder (Lua side)
    new (ptr)Type();
    uintptr_t offset = (uintptr_t)ptr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple In Place Typed New: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMT->getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(fgScriptMT->getMetatable(CMetatables::EMPTY_MT_ID).metaObj);
    } else {
        //newObj.SetMetatable(state->GetRegistry()[metatableName]);
        newObj.SetMetatable(fgScriptMT->getMetatable(METATABLE_ID).metaObj);
        FG_LOG_DEBUG("Script: Simple In Place Typed New: metatable: id[%d], name[%s]",
                     METATABLE_ID, metatableName);
    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type>
int fg::script::CScriptSubsystem::simpleInPlaceTypedGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)

    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Simple Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Simple In Place Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Simple In Place Typed GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: Simple In Place Typed GC: calling destructor: ptr[%p], offset[%lu]", unboxed, offset);
    Type *ptrObj = (Type *)unboxed;
    ptrObj->~Type();
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

    #undef FG_INC_SCRIPT_SUBSYSTEM_BLOCK

#endif /* FG_INC_SCRIPT_SUBSYSTEM */
