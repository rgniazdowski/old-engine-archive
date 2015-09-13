/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SHADER_MANAGER
    #define FG_INC_GFX_SHADER_MANAGER
    #define FG_INC_GFX_SHADER_MANAGER_BLOCK

    #ifdef FG_INC_GFX_STD_INC_BLOCK
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderManager inside of Gfx Standard Include header."
    #endif

    #include "GFX/fgGfxStdInc.h"
    #include "fgManagerBase.h"
    #include "Resource/fgDataManagerBase.h"

    #include "Util/fgHandleManager.h"
    #include "Util/fgTag.h"
    #include "Util/fgDirent.h"
    #include "fgGfxShaderProgram.h"
    #include "fgGfxUniformUpdater.h"

namespace fg {
    namespace gfx {
        class CShaderManager;
    } // namespace gfx
} // namespace fg

    #define FG_TAG_SHADER_MANAGER_NAME  "GfxShaderManager"
//#define FG_TAG_MANAGER_BASE_ID        20 //#FIXME - something automatic maybe?
    #define FG_TAG_SHADER_MANAGER       FG_TAG_TYPE(fg::gfx::CShaderManager)
//FG_TAG_TEMPLATE(fgResourceManager, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CShaderManager, FG_TAG_SHADER_MANAGER_NAME);

    #define FG_MANAGER_GFX_SHADER   0x00000002

namespace fg {
    namespace gfx {
        /// Special handle type for manager base
        typedef FG_TAG_SHADER_MANAGER ShaderManagerTag;

        /**
         *
         */
        class CShaderManager :
        public resource::CDataManagerBase<CShaderProgram*, ShaderHandle, ShaderManagerTag> {
        public:
            typedef resource::CDataManagerBase<CShaderProgram*, ShaderHandle, ShaderManagerTag> base_type;
            typedef base_type shader_program_data_manager_type;

            typedef CShaderManager self_type;
            typedef CShaderManager type;
            typedef CShaderProgram data_type;
            typedef CShaderProgram* data_type_ptr;
            typedef ShaderHandle handle_type;
            typedef ShaderManagerTag tag_type;

        protected:
            typedef resource::CDataManagerBase<CShader*, ShaderHandle, ShaderManagerTag> shader_data_manager_type;

            /**
             *
             */
            class CShaderObjectManager : public shader_data_manager_type {
                friend class CShaderManager;
            public:
                typedef shader_data_manager_type base_type;
                typedef CShaderObjectManager self_type;
                typedef CShaderObjectManager type;

                typedef CShader data_type;
                typedef CShader* data_type_ptr;
                typedef ShaderHandle handle_type;
                typedef ShaderManagerTag tag_type; // ?

            protected:
                typedef DataVec ShaderVec;
                typedef DataVecItor ShaderVecItor;

            public:
                /**
                 *
                 */
                CShaderObjectManager(CShaderManager* pShaderMgr);
                /**
                 *
                 */
                virtual ~CShaderObjectManager();

            protected:
                /**
                 *
                 */
                void clear(void);

            public:
                /**
                 *
                 * @return
                 */
                fgBool destroy(void);
                /**
                 *
                 * @return
                 */
                fgBool initialize(void);

                /**
                 *
                 * @param pShader
                 * @param nameTag
                 * @return
                 */
                fgBool insert(CShader* pShader, const std::string& nameTag);
                /**
                 *
                 * @param pShader
                 * @return
                 */
                fgBool insertShader(CShader* pShader);
                /**
                 *
                 * @param rhUniqueID
                 * @return
                 */
                fgBool remove(const ShaderHandle& rhUniqueID);
                /**
                 *
                 * @param nameTag
                 * @return
                 */
                fgBool remove(const std::string& nameTag);
                /**
                 *
                 * @param nameTag
                 * @return
                 */
                fgBool remove(const char *nameTag);
                /**
                 * 
                 * @param pShader
                 * @return
                 */
                fgBool remove(CShader* pShader);
                /**
                 *
                 * @param info
                 * @return
                 */
                CShader* request(const std::string& info);
                /**
                 * 
                 * @param info
                 * @return
                 */
                CShader* request(const char* info);
                /**
                 *
                 * @param usageMask
                 * @return
                 */
                CShader* request(shaders::UsageMask usageMask);

                /**
                 *
                 * @param filePath
                 * @return
                 */
                CShader* getShaderByPath(const std::string& filePath);
                /**
                 *
                 * @param filePath
                 * @return
                 */
                CShader* getShaderByPath(const char* filePath);

            private:
                /// Shader program manager
                CShaderManager* m_pShaderMgr;
            }; // protected class CShaderObjectManager
            //------------------------------------------------------------------

        protected:
            ///
            typedef DataVec ProgramVec;
            ///
            typedef DataVecItor ProgramVecItor;

        public:

            /**
             *
             */
            enum StateFlags {
                /// Empty flags
                NO_FLAGS = 0x0000,
                /// Is pre-caching of shaders done?
                PRELOAD_DONE = 0x0001,
                /// Should shaders be linked before using?
                LINK_ON_USE = 0x0002,
                /// Should shaders be linked when requesting?
                LINK_ON_REQUEST = 0x0004,
                /// Should shader be set to current after request?
                USE_ON_REQUEST = 0x0008,
                /// Whether or not to automatically set data for specific uniforms
                /// when switching shader programs
                UNIFORM_AUTO_UPDATE = 0x0010,
            }; // enum StateFlags

        public:
            /**
             * Default constructor for the shader manager object
             */
            CShaderManager();
            /**
             * Destructor for the shader manager object
             */
            virtual ~CShaderManager();

        protected:
            /**
             * 
             */
            void clear(void);

        public:
            /**
             * Destroy the shader manager and all managed data
             * (destructors called - every handle becomes invalid)
             * @return 
             */
            fgBool destroy(void);

            /**
             * Initialize the shader manager
             * @return 
             */
            fgBool initialize(void);

            /**
             * Pre load / pre cache the required shaders
             * @return 
             */
            fgBool preLoadShaders(void);

            /**
             * This will compile all shader programs (no linking will occur)
             * @return 
             */
            fgBool compileShaders(fgBool recentOnly = FG_FALSE);

            /**
             * This will link all shader programs (compile will occur if needed)
             * @return 
             */
            fgBool linkShaders(fgBool recentOnly = FG_FALSE);

            /**
             * This will make all gfx IDs invalid (free gfx side data)
             * @return
             */
            fgBool allReleaseGFX(void);

            //------------------------------------------------------------------

            /**
             * 
             * @param strVec
             * @return
             */
            fgBool getShaderNames(CStringVector& strVec);

            /**
             * 
             * @param pProgram
             * @return 
             */
            fgBool isProgramUsed(CShaderProgram* pProgram);
            /**
             * 
             * @param spUniqueID
             * @return 
             */
            fgBool isProgramUsed(ShaderHandle spUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool isProgramUsed(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool isProgramUsed(const char* nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pProgram
             * @return 
             */
            fgBool useProgram(CShaderProgram* pProgram);
            /**
             * 
             * @param spUniqueID
             * @return 
             */
            fgBool useProgram(ShaderHandle spUniqueID);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool useProgram(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool useProgram(const char* nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param pProgram
             * @param nameTag
             * @return 
             */
            virtual fgBool insert(CShaderProgram* pProgram, const std::string& nameTag);

            /**
             * Insert the specified shader program into the manager
             * @param pProgram
             * @return 
             */
            virtual fgBool insertProgram(CShaderProgram* pProgram);

            /**
             *
             * @param pProgram
             * @return
             */
            virtual fgBool remove(CShaderProgram* pProgram);
            /**
             *
             * @param rhUniqueID
             * @return
             */
            virtual fgBool remove(const ShaderHandle& rhUniqueID);
            /**
             *
             * @param nameTag
             * @return
             */
            virtual fgBool remove(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return
             */
            virtual fgBool remove(const char *nameTag);

            //------------------------------------------------------------------

            using base_type::isManaged;
            using base_type::remove;
            using base_type::destroyData;

            /**
             *
             * @param pShader
             * @return
             */
            virtual fgBool insertShader(CShader* pShader);

            /**
             * 
             * @param filePath
             * @return
             */
            virtual CShader* getShaderByPath(const std::string& filePath);
            /**
             *
             * @param filePath
             * @return
             */
            virtual CShader* getShaderByPath(const char* filePath);

            /**
             *
             * @param pShader
             * @return
             */
            virtual fgBool isManaged(CShader* pShader);

            /**
             *
             * @param pShader
             * @return
             */
            virtual fgBool remove(CShader* pShader);

            /**
             *
             * @param pShader
             * @return
             */
            virtual fgBool destroyData(CShader*& pShader);
            /**
             *
             * @param dhUniqueID
             * @return
             */
            virtual CShader* getShader(const ShaderHandle& dhUniqueID);
            /**
             *
             * @param nameTag
             * @return
             */
            virtual CShader* getShader(const std::string& nameTag);
            /**
             *
             * @param nameTag
             * @return
             */
            virtual CShader* getShader(const char* nameTag);

            //------------------------------------------------------------------

            /**
             * 
             * @param path
             */
            void setShadersPath(const std::string& path);
            /**
             * 
             * @param path
             */
            void setShadersPath(const char* path);

            /**
             * 
             * @param info
             * @return 
             */
            virtual CShaderProgram* request(const std::string& info);
            /**
             * 
             * @param info
             * @return 
             */
            virtual CShaderProgram* request(const char* info);
            /**
             *
             * @param usageMask
             * @return
             */
            virtual CShaderProgram* request(shaders::UsageMask usageMask);

            /**
             * This will just set the internal pointer, no additional operations
             * This is intended for internal use inside of the shader program
             * @param pProgram
             */
            void setInternalCurrentProgram(CShaderProgram* pProgram);

            /**
             * 
             * @return 
             */
            CShaderProgram* getCurrentProgram(void) const;

            /**
             * 
             * @return
             */
            CUniformUpdater* getUniformUpdater(void) {
                return &m_uniformUpdater;
            }

            //------------------------------------------------------------------

        protected:            
            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
        public:
            /**
             * 
             * @return 
             */
            fgBool isPreloadDone(void) const {
                return (fgBool)!!(m_stateFlags & PRELOAD_DONE);
            }
            /**
             *
             * @return
             */
            fgBool isLinkOnRequest(void) const {
                return (fgBool)!!(m_stateFlags & LINK_ON_REQUEST);
            }
            /**
             *
             * @return
             */
            fgBool isLinkOnUse(void) const {
                return (fgBool)!!(m_stateFlags & LINK_ON_USE);
            }
            /**
             * 
             * @return 
             */
            fgBool isUseOnRequest(void) const {
                return (fgBool)!!(m_stateFlags & USE_ON_REQUEST);
            }
            /**
             * 
             * @return 
             */
            fgBool isUniformAutoUpdate(void) const {
                return (fgBool)!!(m_stateFlags & UNIFORM_AUTO_UPDATE);
            }
            /**
             * 
             * @param toggle
             */
            void setLinkOnRequest(fgBool toggle = FG_TRUE) {
                setFlag(LINK_ON_REQUEST, toggle);
            }
            /**
             *
             * @param toggle
             */
            void setLinkOnUse(fgBool toggle = FG_TRUE) {
                setFlag(LINK_ON_USE, toggle);
            }
            /**
             * 
             * @param toggle
             */
            void setUseOnRequest(fgBool toggle = FG_TRUE) {
                setFlag(USE_ON_REQUEST, toggle);
            }
            /**
             * 
             * @param toggle
             */
            void setUniformAutoUpdate(fgBool toggle = FG_TRUE) {
                setFlag(UNIFORM_AUTO_UPDATE, toggle);
            }
            //------------------------------------------------------------------

        private:
            /// Current shader object manager instance
            CShaderObjectManager m_shaderObjectsHolder;
            /// Internal uniform automatic updater
            CUniformUpdater m_uniformUpdater;
            /// Pointer to shader program object which is being currently used
            /// For double checking - after GFX suspend/resume program ID
            /// will become invalid, need to set this pointer to NULL on suspend
            CShaderProgram* m_currentProgram;
            /// Dirent instance for searching shaders
            util::CDirent* m_shadersDir;
            /// Current shader search path
            std::string m_shadersPath;
            /// Current flags of the shader manager
            StateFlags m_stateFlags;
        }; // class CShaderManager

        FG_ENUM_FLAGS(CShaderManager::StateFlags);

        //----------------------------------------------------------------------
        inline void CShaderManager::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_MANAGER_BLOCK
#endif /* FG_INC_GFX_SHADER_MANAGER */
