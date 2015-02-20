/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXSceneNode.h"
#include "fgGFXSceneManager.h"
#include "GFX/fgGFXDrawCall.h"

using namespace fg;

/**
 * 
 * @param nodeType
 * @param pParent
 */
gfx::CSceneNode::CSceneNode(SceneNodeType nodeType,
                            self_type *pParent) :
base_type(), // fgManagedObjectBase init
drawable_type(DRAWABLE_SCENENODE), // fgGfxDrawable init
m_nodeType(nodeType), // Current node type
m_pTreeNode(NULL),
m_pParent(pParent), // Pointer to the parent node
m_collisionBody(NULL),
m_children(), // Children set
m_stateFlags(StateFlags::NONE),
m_scale(1.0f, 1.0f, 1.0f),
m_modelMat(), // model matrix init
m_aabb(), // axis-aligned bounding box - this one will be transformed
m_drawCall(NULL) // DrawCall for this node - it cannot be managed
{
    setCollidable(FG_TRUE);
    // Draw call is only initialized when Node Custom type is specialized
    if(m_nodeType == SCENE_NODE_CUSTOM) {
        m_drawCall = new CDrawCall();
    } else {
        m_drawCall = NULL;
    }
    if(pParent) {
        if(!m_pManager) {
            m_pManager = pParent->getManager();
        }
    }
}

/**
 * 
 */
gfx::CSceneNode::~CSceneNode() {
    if(m_drawCall)
        delete m_drawCall;
    m_drawCall = NULL;
    m_pParent = NULL;
    m_pTreeNode = NULL;
    // Need to signal the managing object that this node is going to be removed
    // Manager needs to destroy/release the managed children objects
    // .. .. .. 
    while(!m_children.empty()) {
        ChildrenVecItor it = m_children.begin();
        if(it == m_children.end())
            break;
        if(!(*it)) {
            m_children.erase(it);
        } else {
            CSceneNode *pChild = const_cast<CSceneNode *>(*it);
            destroyChild(pChild);
        }
        // can also make scene manager bind special callbacks to the managed objects...
        // oh yes yes #FIXME - managed callback for destroy action
    }
    m_pManager = NULL;
    m_children.clear();
    m_aabb.invalidate();
    if(m_collisionBody) {
        delete m_collisionBody;
        m_collisionBody = NULL;
    }
}

/**
 * 
 */
void gfx::CSceneNode::refreshGfxInternals(void) {
   if(!m_pManager)
       return;
   if(m_pManager->getManagerType() != FG_MANAGER_SCENE) {
       return;
   }
   // ?? #FIXME
}

/**
 * 
 * @param pNode
 * @return 
 */
fgBool gfx::CSceneNode::checkCollisionSphere(const CSceneNode* pNode) const {
    if(!pNode)
        return FG_FALSE;
    if(!pNode->isCollidable() || !this->isCollidable())
        return FG_FALSE;
    const Vector3f &self_center = m_aabb.center;
    const Vector3f &obj_center = pNode->getRefBoundingVolume().center;
    const Vector3f delta = obj_center - self_center;
    const float radius = m_aabb.radius + pNode->getRefBoundingVolume().radius;
    const float r2 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    const float radius2 = radius * radius;
    if(r2 > radius2) {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * 
 */
void gfx::CSceneNode::draw(void) {
    if(!isVisible())
        return;
    if(m_drawCall) {
        m_drawCall->draw(m_modelMat);
    }
    ChildrenVecItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it)) {
            continue;
        }
        if(m_drawCall != (*it)->getDrawCall()) {
            (*it)->draw(m_modelMat);
        }
    }
}

/**
 * Draw with relative 2D position
 * @param relPos
 */
void gfx::CSceneNode::draw(const Vec2f& relPos) {
    if(!isVisible())
        return;
    if(m_drawCall) {
        m_drawCall->draw(relPos);
    }
    ChildrenVecItor it = m_children.begin(), end = m_children.end();
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
void gfx::CSceneNode::draw(const Vec3f& relPos) {
    if(!isVisible())
        return;
    if(m_drawCall) {
        m_drawCall->draw(relPos);
    }
    ChildrenVecItor it = m_children.begin(), end = m_children.end();
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
void gfx::CSceneNode::draw(const Matrix4f& modelMat) {
    if(!isVisible())
        return;
    if(m_drawCall) {
        m_drawCall->draw(modelMat);
    }
    ChildrenVecItor it = m_children.begin(), end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        (*it)->draw(modelMat);
    }
}
////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
void gfx::CSceneNode::updateAABB(void) {
    CSceneNode::updateAABB(m_modelMat); // Call the base version
}

/**
 * 
 * @param modelMat
 */
void gfx::CSceneNode::updateAABB(const Matrix4f& modelMat) {
    // Note: the bounding volume of the scene node is bigger
    // it holds info for aabb after transformation (by model matrix)
    // and radius of the sphere that contains the transformed aabb
    // this is not the most optimal value
    //
    // sphere radius should be taken from aabb of the model/mesh/collision box
    //
    if(m_collisionBody) {
        if(m_collisionBody->getBodyType() == physics::CCollisionBody::BOX) {
            Vector3f &extent = m_collisionBody->getCollisionBox()->halfSize;
            m_aabb.min = -extent;
            m_aabb.max = extent;
            m_aabb.transform(modelMat);
            if(isAutoScale()) {
                m_scale = extent * 2.0f;
                m_modelMat = math::scale(m_modelMat, m_scale);
            }
            //m_aabb.radius = math::sqrt(extent.x * extent.x + extent.y * extent.y + extent.z * extent.z);
        } else if(m_collisionBody->getBodyType() == physics::CCollisionBody::SPHERE) {
            float radius = m_collisionBody->getCollisionSphere()->radius;
            float tmp = math::sqrt((radius * radius) / 3.0f);
            Vector3f extent = Vector3f(tmp, tmp, tmp);
            m_aabb.radius = radius;
            m_aabb.min = -extent;
            m_aabb.max = extent;

            if(isAutoScale()) {
                m_scale = Vector3f(radius, radius, radius);
                m_modelMat = math::scale(m_modelMat, m_scale);
            }
            // The collision body is a sphere - so it is guaranteed that even
            // with model transform the radius does not change
        }
    } else {
        // #FUBAR - no reset performed
        // m_aabb.transform(m_modelMat);
    }
}

/**
 * 
 * @param delta
 */
void gfx::CSceneNode::update(float delta) {
    // The collision body is present 
    // Need to update the scene node model matrix based on the one
    // from the physics subsystem (CollisionBody/RigidBody)
    if(m_collisionBody) {
        m_collisionBody->getGLTransform(math::value_ptr(m_modelMat));
        // This will also call calculateInternals() for the underlying
        // collision primitive (box/sphere/custom/...)
        m_collisionBody->integrate(delta);
    }
    // The base version of the updateAABB will update it depending on the collision body
    // if no collision body is present - the transformation wont be valid,
    // so it does nothing... - this way this function can be called at the end of 
    // any derived version (extend)
    updateAABB();    
    // Scaling?
}

/**
 * 
 * @param bodyType
 */
void gfx::CSceneNode::activateCollisionBody(const physics::CCollisionBody::BodyType bodyType) {
    setCollisionBodyType(bodyType);
}

/**
 * 
 */
void gfx::CSceneNode::removeCollisionBody(void) {
    if(m_collisionBody) {
        delete m_collisionBody;
        m_collisionBody = NULL;
    }
}

/**
 * 
 * @param bodyType
 */
void gfx::CSceneNode::setCollisionBodyType(const physics::CCollisionBody::BodyType bodyType) {
    if(m_collisionBody) {
        m_collisionBody->setBodyType(bodyType);
    } else {
        m_collisionBody = new physics::CCollisionBody(bodyType);
    }
}

////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param pChild
 * @return 
 */
fgBool gfx::CSceneNode::addChild(CSceneNode *pChild) {
    if(!pChild)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    if(m_children.find(pChild) != -1)
        status = FG_FALSE; // duplicate, do not add...
    if(status) {
        m_children.push_back(pChild);
    }
    return status;
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool gfx::CSceneNode::removeChild(CSceneNode *pChild) {
    if(!pChild || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    ChildrenVecItor it = m_children.findItor(pChild);
    if(it == m_children.end()) {
        status = FG_FALSE;
    } else {
        m_children.erase(it);
        // This is required so the scene manager wont call again this function
        // to remove the child from it's parent
        pChild->setParent(NULL);
        if(m_pManager) {
            if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                static_cast<CSceneManager *>(m_pManager)->remove(pChild);
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
gfx::CSceneNode *gfx::CSceneNode::removeChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    CSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    ChildrenVecItor it = m_children.end();
    fgBool managerValid = FG_FALSE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            managerValid = FG_TRUE;
            pChild = static_cast<CSceneManager *>(m_pManager)->get(childName);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                // 2. method - with removal it's required to update iterator
                it = m_children.findItor(pChild);
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
        ChildrenVecItor end = m_children.end();
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
                static_cast<CSceneManager *>(m_pManager)->remove(pChild);
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
gfx::CSceneNode *gfx::CSceneNode::removeChild(const char *childName) {
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
fgBool gfx::CSceneNode::destroyChild(CSceneNode *&pChild) {
    if(!pChild)
        return FG_FALSE;
    if(m_children.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    fgBool managerValid = FG_FALSE;
    ChildrenVecItor it = m_children.findItor(pChild);
    if(it == m_children.end()) {
        status = FG_FALSE;
    } else {
        m_children.erase(it);
        // This is required so the scene manager wont call again this function
        // to remove the child from it's parent
        pChild->setParent(NULL);
        if(m_pManager && false) { // #FIXME
            if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                static_cast<CSceneManager *>(m_pManager)->destroyNode(pChild);
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
fgBool gfx::CSceneNode::destroyChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return FG_FALSE;
    CSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    ChildrenVecItor it = m_children.end();
    fgBool managerValid = FG_FALSE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            managerValid = FG_TRUE;
            pChild = static_cast<CSceneManager *>(m_pManager)->get(childName);
            if(pChild) {
                // Now this can be tricky. How to check if *this parent has this child?
                // Go through all children and check pointer? (set::find())?
                // Or check parent == this?
                // 1. method:
                if(pChild->getParent() == this) {
                    secondCheck = FG_FALSE;
                }
                
                // 2. method - with removal it's required to update iterator
                it = m_children.findItor(pChild);
                if(it != m_children.end()) {
                    secondCheck = FG_FALSE;
                }
            }
        }
    }
    if(secondCheck) {
        it = m_children.begin();
        ChildrenVecItor end = m_children.end();
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
                static_cast<CSceneManager *>(m_pManager)->destroyNode(pChild);
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
fgBool gfx::CSceneNode::destroyChild(const char *childName) {
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
gfx::CSceneNode* gfx::CSceneNode::getChild(const gfx::CSceneNode::handle_type& childHandle) {
    if(childHandle.isNull() || m_children.empty())
        return NULL;
    CSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            pChild = static_cast<CSceneManager *>(m_pManager)->get(childHandle);
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
                    int it = m_children.find(pChild);
                    if(it != -1) {
                        secondCheck = FG_FALSE;
                    }
                }
            }
        }
    }
    if(secondCheck) {
        ChildrenVecItor it = m_children.begin(), end = m_children.end();
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
gfx::CSceneNode* gfx::CSceneNode::getChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    CSceneNode *pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    // Can use manager pointer - kinda strange ?
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            pChild = static_cast<CSceneManager *>(m_pManager)->get(childName);
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
                    int it = m_children.find(pChild);
                    if(it != -1) {
                        secondCheck = FG_FALSE;
                    }
                }
            }
        } else {
            secondCheck = FG_TRUE;
        }
    }
    if(secondCheck) {
        ChildrenVecItor it = m_children.begin(), end = m_children.end();
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
gfx::CSceneNode* gfx::CSceneNode::getChild(const char *childName) {
    return getChild(std::string(childName));
}

/**
 * 
 * @param pChild
 * @return 
 */
fgBool gfx::CSceneNode::hasChild(CSceneNode *pChild) {
    if(!pChild || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    int it = m_children.find(pChild);
    if(it != -1)
        status = FG_TRUE;
    return status;
}

/**
 * 
 * @param childHandle
 * @return 
 */
fgBool gfx::CSceneNode::hasChild(const gfx::CSceneNode::handle_type& childHandle) {
    if(childHandle.isNull() || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    ChildrenVecItor it = m_children.begin(), end = m_children.end();
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
fgBool gfx::CSceneNode::hasChild(const std::string& childName) {
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
fgBool gfx::CSceneNode::hasChild(const char* childName) {
    if(!childName || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(getChild(childName))
        status = FG_TRUE;
    return status;
}
