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

#ifndef _FG_GFX_SCENE_NODE_OBJECT_H_
    #define	_FG_GFX_SCENE_NODE_OBJECT_H_
    #define _FG_GFX_SCENE_NODE_OBJECT_H_BLOCK_

    #ifndef _FG_GFX_SCENE_NODE_H_
        #include "fgGFXSceneNode.h"
    #endif
    #ifndef _FG_GFX_DRAW_CALL_H_
        #include "fgGFXDrawCall.h"
    #endif
    #ifndef _FG_GFX_MODEL_RESOURCE_H_
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

    #undef _FG_GFX_SCENE_NODE_OBJECT_H_BLOCK_
#endif	/* _FG_GFX_SCENE_NODE_OBJECT_H_ */
