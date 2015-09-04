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

namespace fg {
    namespace gfx {
        class CShaderManager;
    };
};

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
                CShaderObjectManager();
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
            }; // protected class CShaderObjectManager

        protected:
            ///
            typedef DataVec ProgramVec;
            ///
            typedef DataVecItor ProgramVecItor;

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

            //------------------------------------------------------------------
            /**
             * 
             * @return 
             */
            fgBool isPreloadDone(void) const {
                return m_isPreloadDone;
            }
            /**
             *
             * @return
             */
            fgBool isLinkOnRequest(void) const {
                return m_isLinkOnRequest;
            }
            /**
             *
             * @return
             */
            fgBool isLinkOnUse(void) const {
                return m_isLinkOnUse;
            }
            /**
             * 
             * @param toggle
             */
            void setLinkOnRequest(fgBool toggle = FG_TRUE) {
                m_isLinkOnRequest = toggle;
            }
            /**
             *
             * @param toggle
             */
            void setLinkOnUse(fgBool toggle = FG_TRUE) {
                m_isLinkOnUse = toggle;
            }

            //------------------------------------------------------------------

        private:
            ///
            CShaderObjectManager m_shaderObjectsHolder;
            /// Pointer to shader program object which is being currently used
            /// For double checking - after GFX suspend/resume program ID
            /// will become invalid, need to set this pointer to NULL on suspend
            CShaderProgram* m_currentProgram;
            ///
            util::CDirent* m_shadersDir;
            ///
            std::string m_shadersPath;
            ///
            fgBool m_isPreloadDone;
            /// Should shaders be linked on request?
            fgBool m_isLinkOnRequest;
            /// Should shaders be linked on get/dereference?
            fgBool m_isLinkOnUse;
        }; // class CShaderManager

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_MANAGER_BLOCK
#endif /* FG_INC_GFX_SHADER_MANAGER */
