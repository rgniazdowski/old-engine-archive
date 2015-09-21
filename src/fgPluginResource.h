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
 * File:   fgPluginResource.h
 * Author: vigilant
 *
 * Created on May 4, 2015, 10:34 AM
 */

#ifndef FG_INC_PLUGIN_RESOURCE
    #define FG_INC_PLUGIN_RESOURCE
    #define FG_INC_PLUGIN_RESOURCE_BLOCK

    #include "Resource/fgResource.h"

namespace fg {

    class CEngineMain;

    /**
     *
     */
    class CPluginResource : public ::fg::resource::CResource {
    public:
        typedef CPluginResource self_type;
        typedef CPluginResource type;
        typedef ::fg::resource::CResource base_type;

        struct SInternalInfo;

    #if __cplusplus > 199711L
        ///
        using InitPluginFunction = fgBool(*)(SInternalInfo*);
        ///
        using ExitPluginFunction = fgBool(*)(SInternalInfo*);
    #else
        ///
        typedef fgBool(*InitPluginFunction)(SInternalInfo*);
        ///
        typedef fgBool(*ExitPluginFunction)(SInternalInfo*);
    #endif

        struct SInternalInfo {
            ::fg::CEngineMain *pEngineMain;
            void* pPluginData;

            SInternalInfo() : pEngineMain(NULL), pPluginData(NULL) {

            }

            virtual ~SInternalInfo() {
                pPluginData = NULL;
                pEngineMain = NULL;
            }
        }; // struct SInternalInfo

    public:
        /**
         *
         */
        CPluginResource();
        /**
         *
         * @param path
         */
        CPluginResource(const char *path);
        /**
         *
         * @param path
         */
        CPluginResource(const std::string& path);

        /**
         *
         */
        virtual ~CPluginResource();

    protected:
        /**
         *
         */
        virtual void clear(void);

    public:
        /**
         * Create function loads/interprets data from file in ROM and place it in RAM memory.
         * @return
         */
        virtual fgBool create(void);
        /**
         * Destroy all loaded data including additional metadata (called with destructor)
         */
        virtual void destroy(void);
        /**
         * Reloads any data, recreates the resource (refresh)
         * @return
         */
        virtual fgBool recreate(void);
        /**
         * Dispose completely of the all loaded data, free all memory
         */
        virtual void dispose(void);
        /**
         * Check if resource is disposed (not loaded yet or disposed after)
         * @return
         */
        virtual fgBool isDisposed(void) const;

    public:
        /**
         *
         * @param internalInfo
         */
        void setInternalInfo(const SInternalInfo& internalInfo) {
            if(!internalInfo.pEngineMain)
                return;
            m_internalInfo = internalInfo;
        }
        /**
         * 
         * @param pEngineMain
         */
        void setInternalInfo(CEngineMain* pEngineMain) {
            if(pEngineMain) {
                m_internalInfo.pEngineMain = pEngineMain;
            }
        }
        /**
         *
         * @return
         */
        SInternalInfo& getInternalInfo(void) {
            return m_internalInfo;
        }
        /**
         *
         * @return
         */
        SInternalInfo const& getInternalInfo(void) const {
            return m_internalInfo;
        }

    private:
        /// Internal plugin info structure
        SInternalInfo m_internalInfo;
        /// Initialization status
        fgBool m_pluginInitStatus;
        /// Name of the function for plugin initialization
        std::string m_initFuncName;
        /// Name of the function for plugin exit procedures
        std::string m_exitFuncName;
        /// The library handle
        void *m_libHandle;
        /// Pointer to the initialization function
        InitPluginFunction m_initFuncHandle;
        /// Pointer to the exit function
        ExitPluginFunction m_exitFuncHandle;
    }; // class CPluginResource

    typedef CPluginResource CPlugin;

} // namespace fg

    #undef FG_INC_PLUGIN_RESOURCE_BLOCK
#endif	/* FG_INC_PLUGIN_RESOURCE */
