/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSceneNodeObject.h
 * Author: vigilant
 *
 * Created on November 12, 2014, 6:08 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_OBJECT
    #define	FG_INC_GFX_SCENE_NODE_OBJECT
    #define FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK

    #ifndef FG_INC_GFX_SCENE_NODE
        #include "fgGFXSceneNode.h"
    #endif
    #ifndef FG_INC_GFX_DRAW_CALL
        #include "fgGFXDrawCall.h"
    #endif
    #ifndef FG_INC_GFX_MODEL_RESOURCE
        #include "fgGFXModelResource.h"
    #endif

/**
 * 
 */
class fgGfxSceneNodeObject : public fgGfxSceneNode {
public:
    typedef fgGfxSceneNode base_type;

private:
    fgGfxModel *m_pModel;

public:
    /**
     * 
     */
    fgGfxSceneNodeObject(fgGfxModel *pModel = NULL, fgGfxSceneNode *pParent = NULL);
    /**
     * 
     * @param orig
     */
    fgGfxSceneNodeObject(const fgGfxSceneNodeObject& orig);
    /**
     * 
     */
    virtual ~fgGfxSceneNodeObject();

public:
    /**
     * 
     * @param pModel
     */
    virtual void setModel(fgGfxModel *pModel);
    /**
     * 
     * @return 
     */
    fgGfxModel *getModel(void) const {
        return m_pModel;
    }
    /**
     * 
     */
    virtual inline void updateAABB(void) {
        // #FUBAR
        if(m_pModel) {
            m_aabb.min = m_pModel->getRefAABB().min;
            m_aabb.max = m_pModel->getRefAABB().max;
            m_aabb.transform(m_modelMat);
        }
    }
    /**
     * 
     * @param modelMat
     */
    virtual inline void updateAABB(const fgMatrix4f& modelMat) {
        if(m_pModel) {
            m_aabb.min = m_pModel->getRefAABB().min;
            m_aabb.max = m_pModel->getRefAABB().max;
            m_aabb.transform(modelMat);
        }
    }
};

    #undef FG_INC_GFX_SCENE_NODE_OBJECT_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_OBJECT */
