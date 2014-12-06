/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_SHADER_MANAGER
    #define FG_INC_GFX_SHADER_MANAGER

    #ifdef FG_INC_GFX_STD_INC_BLOCK__
        #error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderManager inside of Gfx Standard Include header."
    #endif

    #include "GFX/fgGFXStdInc.h"
    #include "fgManagerBase.h"
    #include "Resource/fgDataManagerBase.h"

    #include "Util/fgHandleManager.h"
    #include "Util/fgTag.h"
    #include "Util/fgDirent.h"
    #include "fgGFXShaderProgram.h"

class fgGfxShaderManager;

    #define FG_TAG_SHADER_MANAGER_NAME  "GfxShaderManager"
//#define FG_TAG_MANAGER_BASE_ID        20 //#FIXME - something automatic maybe?
    #define FG_TAG_SHADER_MANAGER       FG_TAG_TYPE(fgGfxShaderManager)

//FG_TAG_TEMPLATE(fgResourceManager, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fgGfxShaderManager, FG_TAG_SHADER_MANAGER_NAME);

// Special handle type for manager base
typedef FG_TAG_SHADER_MANAGER fgGfxShaderManagerTag;

    #define FG_MANAGER_GFX_SHADER   0x00000002

/**
 *
 */
class fgGfxShaderManager : public fgDataManagerBase<fgGfxShaderProgram*, fgGfxShaderHandle, fgGfxShaderManagerTag> {
public:
    typedef fgDataManagerBase<fgGfxShaderProgram*, fgGfxShaderHandle, fgGfxShaderManagerTag> base_type;
    typedef fgGfxShaderProgram data_type;
    typedef fgGfxShaderProgram* data_type_ptr;
    typedef fgGfxShaderHandle handle_type;
    typedef fgGfxShaderManagerTag tag_type;
    
protected:
    typedef hmDataVec smProgramVec;
    typedef hmDataVec::iterator smProgramVecItor;
    
public:
    /**
     * Default constructor for the shader manager object
     */
    fgGfxShaderManager();
    /**
     * Default destructor for the shader manager object
     */
    virtual ~fgGfxShaderManager();

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
     * This will make all gfx IDs invalid (free gfx side data)
     * @return 
     */
    fgBool allReleaseGFX(void);

    /**
     * 
     * @param pProgram
     * @return 
     */
    fgBool isProgramUsed(fgGfxShaderProgram *pProgram);
    /**
     * 
     * @param spUniqueID
     * @return 
     */
    fgBool isProgramUsed(fgGfxShaderHandle spUniqueID);
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
    fgBool useProgram(fgGfxShaderProgram *pProgram);
    /**
     * 
     * @param spUniqueID
     * @return 
     */
    fgBool useProgram(fgGfxShaderHandle spUniqueID);
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
    virtual fgBool insert(fgGfxShaderProgram *pProgram, const std::string& nameTag);

    /**
     * Insert the specified shader program into the manager
     * @param pProgram
     * @return 
     */
    virtual fgBool insertProgram(fgGfxShaderProgram *pProgram);

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
    virtual fgGfxShaderProgram *request(const std::string& info);
    /**
     * 
     * @param info
     * @return 
     */
    virtual fgGfxShaderProgram *request(const char *info);

    /**
     * 
     * @return 
     */
    fgGfxShaderProgram *getCurrentProgram(void) const;
    
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
    fgGfxShaderProgram *m_currentProgram;
    ///
    fgDirent *m_shadersDir;
    ///
    std::string m_shadersPath;
    ///
    fgBool m_isPreloadDone;
};

#endif /* FG_INC_GFX_SHADER_MANAGER */
