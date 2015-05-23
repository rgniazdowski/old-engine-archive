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
            ///
            typedef fg::resource::CDataManagerBase<CShaderProgram*, ShaderHandle, ShaderManagerTag> base_type;
            ///
            typedef CShaderManager self_type;
            ///
            typedef CShaderProgram data_type;
            ///
            typedef CShaderProgram* data_type_ptr;
            ///
            typedef ShaderHandle handle_type;
            ///
            typedef ShaderManagerTag tag_type;

        protected:
            ///
            typedef DataVec ProgramVec;
            ///
            typedef DataVec::iterator ProgramVecItor;

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
             * Destroy the shader manager and all managed data (destructors called - every handle becomes invalid)
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
            fgBool compileShaders(void);

            /**
             * This will link all shader programs (compile will occur if needed)
             * @return 
             */
            fgBool linkShaders(void);

            /**
             * 
             * @param strVec
             * @return
             */
            fgBool getShaderNames(CStringVector& strVec);

            /**
             * This will make all gfx IDs invalid (free gfx side data)
             * @return 
             */
            fgBool allReleaseGFX(void);

            /**
             * 
             * @param pProgram
             * @return 
             */
            fgBool isProgramUsed(CShaderProgram *pProgram);
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
            fgBool isProgramUsed(const std::string &nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool isProgramUsed(const char *nameTag);

            /**
             * 
             * @param pProgram
             * @return 
             */
            fgBool useProgram(CShaderProgram *pProgram);
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
            fgBool useProgram(const std::string &nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool useProgram(const char *nameTag);

            /**
             * 
             * @param pProgram
             * @param nameTag
             * @return 
             */
            virtual fgBool insert(CShaderProgram *pProgram, const std::string& nameTag);

            /**
             * Insert the specified shader program into the manager
             * @param pProgram
             * @return 
             */
            virtual fgBool insertProgram(CShaderProgram *pProgram);

            /**
             * 
             * @param path
             */
            void setShadersPath(const std::string &path);
            /**
             * 
             * @param path
             */
            void setShadersPath(const char *path);

            /**
             * 
             * @param info
             * @return 
             */
            virtual CShaderProgram *request(const std::string& info);
            /**
             * 
             * @param info
             * @return 
             */
            virtual CShaderProgram *request(const char *info);

            /**
             * This will just set the internal pointer, no additional operations
             * This is intended for internal use inside of the shader program
             * @param pProgram
             */
            void setInternalCurrentProgram(CShaderProgram *pProgram);
            
            /**
             * 
             * @return 
             */
            CShaderProgram *getCurrentProgram(void) const;
            /**
             * 
             * @return 
             */
            fgBool isPreloadDone(void) const {
                return m_isPreloadDone;
            }

        private:
            /// Pointer to shader program object which is being currently used
            /// For double checking - after GFX suspend/resume program ID
            /// will become invalid, need to set this pointer to NULL on suspend
            CShaderProgram *m_currentProgram;
            ///
            util::CDirent *m_shadersDir;
            ///
            std::string m_shadersPath;
            ///
            fgBool m_isPreloadDone;
        };
    };
};

    #undef FG_INC_GFX_SHADER_MANAGER_BLOCK
#endif /* FG_INC_GFX_SHADER_MANAGER */
