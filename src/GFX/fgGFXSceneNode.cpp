/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXSceneNode.h"
#include "fgGFXDrawCall.h"
#include "fgGFXSceneManager.h"

fgGfxSceneNode::fgGfxSceneNode(fgGfxSceneNodeType nodeType,
                               self_type *pParent) :
base_type(), // fgManagedObjectBase init
drawable_type(FG_GFX_DRAWABLE_SCENENODE), // fgGfxDrawable init
m_nodeType(nodeType), // Current node type
m_pParent(pParent), // Pointer to the parent node
m_children(), // Children set
m_isVisible(FG_TRUE), // Is this node visible?
m_modelMat(), // model matrix init
m_aabb(), // axis-aligned bounding box - this one will be transformed
m_drawCall(NULL) // DrawCall for this node - it cannot be managed
{
    // Draw call is only initialized when Node Custom type is specialized
    if(m_nodeType == FG_GFX_SCENE_NODE_CUSTOM) {
        m_drawCall = new fgGfxDrawCall();
    }
}

/**
 * 
 */
fgGfxSceneNode::~fgGfxSceneNode() {
    if(m_drawCall)
        delete m_drawCall;
    m_drawCall = NULL;
    m_pParent = NULL;
    // Need to signal the managing object that this node is going to be removed
    // Manager needs to destroy/release the managed children objects
    // .. .. .. 
    while(!m_children.empty()) {
        childrenSetItor it = m_children.begin();
        if(it == m_children.end())
            break;
        if(!(*it)) {
            m_children.erase(it);
        } else {
            fgGfxSceneNode *pChild = const_cast<fgGfxSceneNode *>(*it);
            destroyChild(pChild);
        }
        // can also make scene manager bind special callbacks to the managed objects...
        // oh yes yes
    }
    m_pManager = NULL;
    m_children.clear();
    m_aabb.invalidate();
}

/**
 * 
 */
void fgGfxSceneNode::draw(void) {
    if(!m_isVisible)
        return;
    if(m_drawCall) {
        m_drawCall->draw(m_modelMat);
    }
    childrenSetItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        (*it)->draw(m_modelMat);
    }
}

/**
 * Draw with relative 2D position
 * @param relPos
 */
void fgGfxSceneNode::draw(const fgVec2f& relPos) {
    if(!m_isVisible)
        return;
    if(m_drawCall) {
        m_drawCall->draw(relPos);
    }
    childrenSetItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        (*it)->draw(relPos);
    }
}

/**
 * Draw with relative 3D position
 * @param relPos
 */
void fgGfxSceneNode::draw(const fgVec3f& relPos) {
    if(!m_isVisible)
        return;
    if(m_drawCall) {
        m_drawCall->draw(relPos);
    }
    childrenSetItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        (*it)->draw(relPos);
    }
}

/**
 * Draw with given model matrix
 * @param modelMat
 */
void fgGfxSceneNode::draw(const fgMatrix4f& modelMat) {
    if(!m_isVisible)
        return;
    if(m_drawCall) {
        m_drawCall->draw(modelMat);
    }
    childrenSetItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        (*it)->draw(modelMat);
    }
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool fgGfxSceneNode::addChild(fgGfxSceneNode *pChild) {
    if(!pChild)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    std::pair<childrenSetItor, bool> result = m_children.insert(pChild);
    if(result.second)
        status = FG_TRUE;
    return status;
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool fgGfxSceneNode::removeChild(fgGfxSceneNode *pChild) {
    if(!pChild || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    childrenSetItor it = m_children.find(pChild);
    if(it == m_children.end()) {
        status = FG_FALSE;
    } else {
        m_children.erase(it);
        // This is required so the scene manager wont call again this function
        // to remove the child from it's parent
        pChild->setParent(NULL);
        if(m_pManager) {
            if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                static_cast<fgGfxSceneManager *>(m_pManager)->remove(pChild);
            }
        }
    }
    return status;
}

/**
 * 
 * @param childName
 * @return 
 */
fgGfxSceneNode *fgGfxSceneNode::removeChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    fgGfxSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    childrenSetItor it = m_children.end();
    fgBool managerValid = FG_FALSE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            managerValid = FG_TRUE;
            pChild = static_cast<fgGfxSceneManager *>(m_pManager)->get(childName);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                // 2. method - with removal it's required to update iterator
                it = m_children.find(pChild);
                if(it != m_children.end()) {
                    secondCheck = FG_FALSE;
                }
            }
        } else {
            secondCheck = FG_TRUE;
        }
    }
    if(secondCheck) {
        it = m_children.begin();
        childrenSetItor end = m_children.end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            if((*it)->getName().compare(childName)) {
                pChild = (*it);
                break;
            }
        }
    }
    if(pChild) {
        // The child is found
        if(it != m_children.end()) {
            pChild->setParent(NULL);
            m_children.erase(it);
            // Scene node has access to manager - this will change when
            // scene manager will register special callbacks inside of a node
            // Removal will still remain here. However deletion not. Deletion
            // will be automatic (on object destructor scene mgr callback is fired)
            if(managerValid) {
                static_cast<fgGfxSceneManager *>(m_pManager)->remove(pChild);
            }
        }
    }
    return pChild;
}

/**
 * 
 * @param childName
 * @return 
 */
fgGfxSceneNode *fgGfxSceneNode::removeChild(const char *childName) {
    if(!childName || m_children.empty())
        return NULL;
    if(!*childName)
        return NULL;
    return removeChild(std::string(childName));
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool fgGfxSceneNode::destroyChild(fgGfxSceneNode *&pChild) {
    if(!pChild)
        return FG_FALSE;
    if(m_children.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    fgBool managerValid = FG_FALSE;
    childrenSetItor it = m_children.find(pChild);
    if(it == m_children.end()) {
        status = FG_FALSE;
    } else {
        m_children.erase(it);
        // This is required so the scene manager wont call again this function
        // to remove the child from it's parent
        pChild->setParent(NULL);
        if(m_pManager) {
            if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                static_cast<fgGfxSceneManager *>(m_pManager)->destroyNode(pChild);
                managerValid = FG_TRUE;
            }
        }
        if(!managerValid) {
            delete pChild;
            pChild = NULL;
        }
    }
    return status;
}

/**
 * 
 * @param childName
 * @return 
 */
fgBool fgGfxSceneNode::destroyChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return FG_FALSE;
    fgGfxSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    childrenSetItor it = m_children.end();
    fgBool managerValid = FG_FALSE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            managerValid = FG_TRUE;
            pChild = static_cast<fgGfxSceneManager *>(m_pManager)->get(childName);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                // 2. method - with removal it's required to update iterator
                it = m_children.find(pChild);
                if(it != m_children.end()) {
                    secondCheck = FG_FALSE;
                }
            }
        }
    }
    if(secondCheck) {
        it = m_children.begin();
        childrenSetItor end = m_children.end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            if((*it)->getName().compare(childName)) {
                pChild = (*it);
                break;
            }
        }
    }
    fgBool status = FG_FALSE;
    if(pChild) {
        // The child is found
        if(it != m_children.end()) {
            pChild->setParent(NULL);
            m_children.erase(it);
            // Scene node has access to manager - this will change when
            // scene manager will register special callbacks inside of a node
            // However deletion not. Deletion will be automatic (on object destructor
            // scene mgr callback is fired)
            if(managerValid) {
                // #FIXME
                static_cast<fgGfxSceneManager *>(m_pManager)->destroyNode(pChild);
            } else {
                delete pChild;
                pChild = NULL;
            }
            status = FG_TRUE;
        }
    }
    return status;
}

/**
 * 
 * @param childName
 * @return 
 */
fgBool fgGfxSceneNode::destroyChild(const char *childName) {
    if(!childName)
        return FG_FALSE;
    if(!*childName)
        return FG_FALSE;
    return destroyChild(std::string(childName));
}

/**
 * 
 * @param childHandle
 * @return 
 */
fgGfxSceneNode* fgGfxSceneNode::getChild(const fgGfxSceneNode::handle_type& childHandle) {
    if(childHandle.isNull() || m_children.empty())
        return NULL;
    fgGfxSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            pChild = static_cast<fgGfxSceneManager *>(m_pManager)->get(childHandle);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                // 2. method
                if(false) {
                    childrenSetItor it = m_children.find(pChild);
                    if(it != m_children.end()) {
                        secondCheck = FG_FALSE;
                    }
                }
            }
        }
    }
    if(secondCheck) {
        childrenSetItor it = m_children.begin(), end = m_children.end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            if((*it)->getHandle() == childHandle) {
                pChild = (*it);
                break;
            }
        }
    }
    return pChild;
}

/**
 * 
 * @param childName
 * @return 
 */
fgGfxSceneNode* fgGfxSceneNode::getChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    fgGfxSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            pChild = static_cast<fgGfxSceneManager *>(m_pManager)->get(childName);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                // 2. method:
                if(false) {
                    childrenSetItor it = m_children.find(pChild);
                    if(it != m_children.end()) {
                        secondCheck = FG_FALSE;
                    }
                }
            }
        } else {
            secondCheck = FG_TRUE;
        }
    }
    if(secondCheck) {
        childrenSetItor it = m_children.begin(), end = m_children.end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            if((*it)->getName().compare(childName)) {
                pChild = (*it);
                break;
            }
        }
    }
    return pChild;
}

/**
 * 
 * @param childName
 * @return 
 */
fgGfxSceneNode* fgGfxSceneNode::getChild(const char *childName) {
    return getChild(std::string(childName));
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool fgGfxSceneNode::hasChild(fgGfxSceneNode *pChild) {
    if(!pChild || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    childrenSetItor it = m_children.find(pChild);
    if(it != m_children.end())
        status = FG_TRUE;
    return status;
}

/**
 * 
 * @param childHandle
 * @return 
 */
fgBool fgGfxSceneNode::hasChild(const fgGfxSceneNode::handle_type& childHandle) {
    if(childHandle.isNull() || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    childrenSetItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        if((*it)->getHandle() == childHandle) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}

/**
 * 
 * @param childName
 * @return 
 */
fgBool fgGfxSceneNode::hasChild(const std::string& childName) {
    if(m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(getChild(childName))
        status = FG_TRUE;
    return status;
}

/**
 * 
 * @param childName
 * @return 
 */
fgBool fgGfxSceneNode::hasChild(const char* childName) {
    if(!childName || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(getChild(childName))
        status = FG_TRUE;
    return status;
}
