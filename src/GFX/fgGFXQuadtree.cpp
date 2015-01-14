/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXQuadtree.h"

using namespace fg;

/**
 * 
 */
gfx::CQuadtree::CQuadtree() {
 }

/**
 * 
 */
gfx::CQuadtree::~CQuadtree() {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
}

/**
 * Insert the given object (sceneNode - logical) into the tree given by treeNode
 * Returns the depth of the node the object was placed in.
 * @param sceneNode
 * @param treeNode
 * @return 
 */
int gfx::CQuadtree::insert(CSceneNode* sceneNode, SQuadTNode* treeNode) {
    if(!sceneNode)
        return -1;

    if(!treeNode) {
        if(!m_root) {
            m_root = new SQuadTNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        treeNode = m_root;
    }
    
    int i, j;

    // Check child nodes to see if object fits in one of them.
    if(treeNode->depth + 1 < (int)m_maxDepth) {
        float halfSize = m_worldSize.x / (float)(2 << treeNode->depth);
        float quarterSize = halfSize / 2.0f;
        float offset = quarterSize;

        for(j = 0; j < 2; j++) {
            for(i = 0; i < 2; i++) {
                float cx = treeNode->center.x + ((i == 0) ? -offset : offset);
                float cy = treeNode->center.y + ((j == 0) ? -offset : offset);

                if(fitsInBox(sceneNode, Vector2f(cx, cy), quarterSize)) {
                    // Recurse into this node.
                    if(treeNode->child[j][i] == NULL) {
                        treeNode->child[j][i] = new SQuadTNode(treeNode, Vector2f(cx, cy), treeNode->depth + 1);
                    }
                    return insert(sceneNode, treeNode->child[j][i]);
                }
            }
        }
    }
    // Keep object in this node.
    if(!treeNode->objects.contains(sceneNode)) {
        treeNode->objects.push_back(sceneNode);
    }
    return treeNode->depth;
}

/**
 * 
 * @param sceneNode
 * @param treeNode
 * @param halfExtent
 * @return 
 */
fgBool gfx::CQuadtree::fitsInBox(const CSceneNode* sceneNode,
                                 SQuadTNode* treeNode,
                                 const float halfExtent) {
    if(!sceneNode || !treeNode)
        return FG_FALSE;

    // nope, it needs to check if the bounding volume of scene node can fit inside
    // the Quadtree Node (center+halfExtents)
    //sceneNode->getRefBoundingVolume().test(treeNode->center, halfExtent);
    return fitsInBox(sceneNode, treeNode->center, halfExtent);
}

/**
 * 
 * @param sceneNode
 * @param center
 * @param halfExtent
 * @return 
 */
fgBool gfx::CQuadtree::fitsInBox(const CSceneNode* sceneNode,
                                 const Vector3f& center,
                                 const float halfExtent) {
    if(!sceneNode)
        return FG_FALSE;

    const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;
    float r = sceneNode->getRefBoundingVolume().radius;

    if(objpos.x - r < center.x - halfExtent ||
       objpos.x + r > center.x + halfExtent ||
       objpos.y - r < center.y - halfExtent ||
       objpos.y + r > center.y + halfExtent ||
       objpos.z - r < center.z - halfExtent ||
       objpos.z + r > center.z + halfExtent) {
        return FG_FALSE;
    } else {
        return FG_TRUE;
    }
}

/**
 * 
 * @param sceneNode
 * @param center
 * @param halfExtent
 * @return 
 */
fgBool gfx::CQuadtree::fitsInBox(const CSceneNode* sceneNode,
                                 const Vector2f& center,
                                 const float halfExtent) {
    if(!sceneNode)
        return FG_FALSE;

    const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;
    float r = sceneNode->getRefBoundingVolume().radius;

    if(objpos.x - r < center.x - halfExtent ||
       objpos.x + r > center.x + halfExtent ||
       objpos.y - r < center.y - halfExtent ||
       objpos.y + r > center.y + halfExtent) {
        return FG_FALSE;
    } else {
        return FG_TRUE;
    }
}
