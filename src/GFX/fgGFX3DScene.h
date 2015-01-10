/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE_BLOCK

    #include "fgGFXSceneManager.h"

namespace fg {

    namespace gfx {

/**
 *
 */
class CScene3D : public fg::gfx::CSceneManager {
public:
    ///
    typedef fg::gfx::CSceneManager base_type;
    
private:

public:
    /**
     * 
     */
    CScene3D();
    /**
     * 
     */
    virtual ~CScene3D();

public:

    /**
     * 
     */
    virtual void sortCalls(void);

    /**
     * 
     */
    virtual void render(void);

    /**
     * 
     * @param pModelRes
     * @param nameTag
     * @return 
     */
    CSceneNode *addFromModel(CModelResource *pModelRes, const std::string& nameTag);
    /**
     * 
     * @param modelNameTag
     * @param nameTag
     * @return 
     */
    CSceneNode *addFromModel(const std::string& modelNameTag, const std::string& nameTag);
    /**
     * 
     * @param modelNameTag
     * @param nameTag
     * @return 
     */
    CSceneNode *addFromModel(const char *modelNameTag, const char *nameTag);
};
    };
};

    #undef FG_INC_GFX_3D_SCENE_BLOCK
#endif /* FG_INC_GFX_3D_SCENE */
