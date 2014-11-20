/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

/**
 *
 */
class fgGfx3DScene : public fgGfxSceneManager {
private:

public:
    //
    fgGfx3DScene();
    //
    virtual ~fgGfx3DScene();

public:

    //
    virtual void sortCalls(void);

    //
    virtual void render(void);

    //
    fgGfxSceneNode *addFromModel(fgGfxModelResource *pModelRes, const std::string& nameTag);
};

    #undef FG_INC_GFX_3D_SCENE_BLOCK
#endif /* FG_INC_GFX_3D_SCENE */
