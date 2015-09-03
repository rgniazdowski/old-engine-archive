/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_SHADER_BASE
    #define FG_INC_GFX_SHADER_BASE
    #define FG_INC_GFX_SHADER_BASE_BLOCK

    #include "fgGfxShaderDefs.h"

    #include "Hardware/fgQualityTypes.h"
    #include "Resource/fgManagedDataFile.h"
    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"
    #include <map>

namespace fg {
    namespace gfx {
        /// Forward declaration for CShader
        class CShader;
        /// Forward declaration for CShaderProgram
        class CShaderProgram;
        /// Forward declaration for CShaderManager
        class CShaderManager;
    } // namespace gfx
} // namespace fg

    #define FG_TAG_GFX_SHADER_NAME	"GfxShader"
    #define FG_TAG_GFX_SHADER		FG_TAG_TYPE(fg::gfx::CShader)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CShader, FG_TAG_GFX_SHADER_NAME);

namespace fg {

    namespace resource {
        template<typename THandleType, typename TMapKeyType> class CManagedDataFile;
    };

    namespace gfx {

        /// Tag type for Shader
        typedef FG_TAG_GFX_SHADER ShaderTag;
        /// Special handle type for shader program
        typedef ::fg::util::CHandle<ShaderTag> ShaderHandle;

        namespace base {

            /**
             *
             */
            class CShader : public ::fg::resource::CManagedDataFile<ShaderHandle, Quality> {
                //friend class fg::gfx::CShader;
                friend class ::fg::gfx::CShaderProgram;
                friend class ::fg::gfx::CShaderManager;
            public:
                ///
                typedef CManagedDataFile<ShaderHandle, Quality> base_type;
                ///
                typedef ShaderTag tag_type;

            protected:
                ///
                typedef std::map<fgGFXenum, fgGFXint> ObjParamMap;
                ///
                typedef ObjParamMap::iterator ObjParamMapItor;

                /**
                 *
                 */
                enum ShaderBaseType {
                    BASE_TYPE_INVALID = 0,
                    BASE_TYPE_SHADER = 1,
                    BASE_TYPE_PROGRAM = 2
                }; // enum ShaderBaseType            

            public:
                /**
                 * 
                 */
                CShader();
                /**
                 * 
                 */
                virtual ~CShader();

                //--------------------------------------------------------------
                /**
                 * 
                 * @return 
                 */
                fgGFXuint getGfxID(void) const {
                    return m_gfxID;
                }
                /**
                 * 
                 * @return 
                 */
                fgGFXuint & getRefGfxID(void) {
                    return m_gfxID;
                }
                /**
                 * 
                 * @param pname
                 * @return 
                 */
                fgGFXint getParam(fgGFXenum pname) {
                    return m_params[pname];
                }
                /**
                 * 
                 * @return 
                 */
                const char *getLog(void) const {
                    return m_log;
                }
                /**
                 * 
                 */
                virtual void clearAll(void) = 0;

            protected:
                /**
                 * 
                 */
                void updateLog(void);
                /**
                 * 
                 */
                void updateParams(void);
                /**
                 * 
                 * @param pname
                 * @return 
                 */
                fgGFXint updateParam(fgGFXenum pname);

            protected:
                ///
                ObjParamMap m_params;
                ///
                char *m_log;
                ///
                fgGFXuint m_gfxID;
                ///
                ShaderBaseType m_baseType;

            }; // class CShader
        } // namespace base
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SHADER_BASE_BLOCK
#endif /*FG_INC_GFX_SHADER_BASE */
