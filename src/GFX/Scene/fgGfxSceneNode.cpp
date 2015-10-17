/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxSceneNode.h"
#include "fgGfxSceneManager.h"
#include "GFX/fgGfxDrawCall.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNode::CSceneNode(SceneNodeType nodeType,
                            self_type* pParent) :
base_type(), // fgManagedObjectBase init
animated_type(),
spatial_type(),
m_nodeType(nodeType), // Current node type
m_nodeTypeMask(nodeType),
m_nodeTraits(fg::traits::ANIMATED | fg::traits::SPATIAL),
m_children(), // Children vector
m_stateFlags(StateFlags::NO_FLAGS),
m_pParent(pParent), // Pointer to the parent node
m_modelMat(), // model matrix init
m_finalModelMat() {
    setActive(FG_TRUE);
    setCollidable(FG_FALSE);
    setAutoScale(FG_FALSE);

    if(pParent) {
        if(!m_pManager) {
            // copy manager pointer
            // if parent is managed then the child will be managed later
            m_pManager = pParent->getManager();
            // do not copy isManaged flag ... this needs to be done by the manager object
        }
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNode::CSceneNode(const CSceneNode& orig) : base_type(orig) {
    if(this != &orig) {
        this->m_nodeType = orig.m_nodeType;
        this->m_pTreeNode = NULL;
        this->m_pParent = NULL;
        //this->m_children; // ?? ?? 
        this->m_stateFlags = orig.m_stateFlags;
        this->m_scale = orig.m_scale;
        this->m_modelMat = orig.m_modelMat;
        this->m_aabb = orig.m_aabb;
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNode::~CSceneNode() {
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
            CSceneNode* pChild = const_cast<CSceneNode *>(*it);
            destroyChild(pChild);
        }
        // can also make scene manager bind special callbacks to the managed objects...
        // oh yes yes #FIXME - managed callback for destroy action
    }
    m_pManager = NULL;
    m_children.clear();
    m_aabb.invalidate();
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::refreshDrawableFlag(void) {
    setFlag(DRAWABLE_CHILDREN, FG_FALSE);
    ChildrenVecItor it = m_children.begin();
    ChildrenVecItor end = m_children.end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        if((*it)->hasTraits(fg::traits::DRAWABLE)) {
            setFlag(DRAWABLE_CHILDREN, FG_TRUE);
            break;
        }
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    if(!pObj)
        status = FG_FALSE;
    if(status) {
        switch(trait) {
            case fg::traits::ANIMATED:
                *pObj = static_cast<traits::CAnimated*>(this);
                break;
                //case traits::DRAWABLE:
                //   * pObj = static_cast<traits::CDrawable*>(this);
                //    break;
            case fg::traits::SPATIAL:
                *pObj = static_cast<traits::CSpatialObject*>(this);
                break;
            default:
                break;
        }
    } else if(pObj) {
        *pObj = NULL;
    }

    return status;
}
//------------------------------------------------------------------------------

int gfx::CSceneNode::queryChildrenTraits(const fg::traits::SceneNode trait,
                                         ChildrenVec& output,
                                         fgBool shouldClear) {
    if(trait == fg::traits::NO_NODE_TRAITS)
        return 0;
    if(!hasChildren())
        return 0;
    if(shouldClear)
        output.clear();
    int found = 0;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int i = 0; i < nChildren; i++) {
        CSceneNode* pChild = getChildByIndex(i);
        if(pChild->hasTraits(trait)) {
            output.push_back(pChild);
            found++;
            found += pChild->queryChildrenTraits(trait, output, FG_FALSE);
        }
    }
    return found;
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::refreshGfxInternals(void) {
    if(!m_pManager)
        return;
    if(m_pManager->getManagerType() != FG_MANAGER_SCENE) {
        return;
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setVisible(const fgBool toggle, const fgBool recursive) {
    setFlag(VISIBLE, toggle);
    if(!recursive) {
        return;
    }
    unsigned int n = m_children.size();
    for(unsigned int i = 0; i < n; i++) {
        CSceneNode* pChild = m_children[i];
        if(!pChild) {
            m_children.remove(i, n);
            continue;
        }
        // go down the tree and set visible flag
        pChild->setVisible(toggle, recursive);
    }
    // TODO - non recursive version (use stack)
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setPosition(const Vec3f& position) {
    m_modelMat[3].x = position.x;
    m_modelMat[3].y = position.y;
    m_modelMat[3].z = position.z;
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setPosition(float x, float y, float z) {
    m_modelMat[3].x = x;
    m_modelMat[3].y = y;
    m_modelMat[3].z = z;
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::rotate(float angle, const Vec3f& axis) {
    m_modelMat = math::rotate(m_modelMat, angle, axis);
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::rotate(float angle, float x, float y, float z) {    
    m_modelMat = math::rotate(m_modelMat, angle, Vec3f(x, y, z));    
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setRotation(float angle, const Vec3f& axis) {    
    const Vector4f translation = m_modelMat[3];
    m_modelMat = math::rotate(Matrix4f(), angle, axis);
    m_modelMat[3] = translation;    
    // ignore scaling - when rotating - need to preserve whole translation
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setRotation(float angle, float x, float y, float z) {
    const Vector4f translation = m_modelMat[3];
    m_modelMat = math::rotate(Matrix4f(), angle, Vec3f(x, y, z));    
    m_modelMat[3] = translation;
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setHalfSize(const Vector3f& halfSize) {
    m_aabb.min = -halfSize;
    m_aabb.max = halfSize;
    m_aabb.refresh();
    m_aabb.radius = math::length(halfSize);
    m_aabb.transform(m_finalModelMat, m_scale);
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::setRadius(float radius) {
    if(radius < 0.0f)
        radius *= -1.0f;
    // This will be set where there is no collision body
    // It is not necessary with the collision body (physics)
    // because the nodes internal AABB will be updated in update(*) function
    //float a = (2.0f* radius) / M_SQRT2;
    float a = math::sqrt(radius * radius / 3.0f);
    m_aabb.min = -Vector3f(a, a, a);
    m_aabb.max = Vector3f(a, a, a);
    m_aabb.radius = radius;
    m_aabb.refresh();
    m_aabb.transform(m_finalModelMat, m_scale);
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::checkCollisionSphere(const CSceneNode* pNode) const {
    if(!pNode)
        return FG_FALSE;
    if(!pNode->isCollidable() || !this->isCollidable())
        return FG_FALSE;
    const Vector3f &self_center = m_aabb.center;
    const Vector3f &obj_center = pNode->getBoundingVolume().center;
    const Vector3f delta = obj_center - self_center;
    const float radius = m_aabb.radius + pNode->getBoundingVolume().radius;
    const float r2 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    const float radius2 = radius* radius;
    if(r2 > radius2) {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::checkCollisionAABB(const CSceneNode* pNode) const {
    if(!pNode)
        return FG_FALSE;
    if(!pNode->isCollidable() || !this->isCollidable())
        return FG_FALSE;
    return m_aabb.test(pNode->getBoundingVolume());
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::updateAABB(void) {
    // Note: the bounding volume of the scene node is bigger
    // it holds info for aabb after transformation (by model matrix)
    // and radius of the sphere that contains the transformed aabb
    // this is not the most optimal value
    //
    // sphere radius should be taken from aabb of the model/mesh/collision box
    //
#if 0
    if(m_collisionBody) {
        if(m_collisionBody->getBodyType() == physics::BODY_BOX) {
            Vector3f &extent = m_collisionBody->getCollisionBox()->halfSize;
            m_aabb.min = -extent;
            m_aabb.max = extent;
            if(isAutoScale()) {
                m_scale = extent * 2.0f;
            }
            //m_aabb.radius = math::sqrt(extent.x* extent.x + extent.y* extent.y + extent.z* extent.z);
        } else if(m_collisionBody->getBodyType() == physics::BODY_SPHERE) {
            float radius = m_collisionBody->getCollisionSphere()->radius;
            float tmp = math::sqrt((radius * radius) / 3.0f);
            Vector3f extent = Vector3f(tmp, tmp, tmp);
            m_aabb.radius = radius;
            m_aabb.min = -extent;
            m_aabb.max = extent;
            if(isAutoScale()) {
                m_scale = Vector3f(radius, radius, radius);
            }
            // The collision body is a sphere - so it is guaranteed that even
            // with model transform the radius does not change
        }
        m_modelMat = math::scale(m_modelMat, m_scale);
    } else {
        // #FUBAR - no reset performed
        // m_aabb.transform(m_modelMat);
    }
#endif
}
//------------------------------------------------------------------------------

void gfx::CSceneNode::animate(float delta) { }
//------------------------------------------------------------------------------

void gfx::CSceneNode::update(float delta) {
    // The collision body is present
    // Need to update the scene node model matrix based on the one
    // from the physics subsystem (CollisionBody/RigidBody)
    //if(m_collisionBody) {
    // This will also call calculateInternals() for the underlying
    // collision primitive (box/sphere/custom/...)
    //    m_collisionBody->integrate(delta);
    //    m_collisionBody->getGLTransform(math::value_ptr(m_modelMat));
    //}
    if(getParent()) {
        m_finalModelMat = getParent()->getFinalModelMatrix() * m_modelMat;
    } else {
        m_finalModelMat = m_modelMat;
    }
    animate(delta);
    // The base version of the updateAABB will update it depending on the collision body
    // if no collision body is present - the transformation wont be valid,
    // so it does nothing... - this way this function can be called at the end of
    // any derived version (extend)
    updateAABB();
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::addChild(CSceneNode* pChild) {
    if(!pChild)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    if(m_children.find(pChild) != -1)
        status = FG_FALSE; // duplicate, do not add...
    if(status) {
        if(pChild->hasTraits(fg::traits::DRAWABLE))
            setFlag(DRAWABLE_CHILDREN, FG_TRUE);
        m_children.push_back(pChild);
        pChild->setParent(this);
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::removeChild(CSceneNode* pChild) {
    if(!pChild) {
        return FG_FALSE;
    }
    if(m_children.empty()) {
        setFlag(DRAWABLE_CHILDREN, FG_FALSE);
        return FG_FALSE;
    }
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
    if(m_children.empty()) {
        setFlag(DRAWABLE_CHILDREN, FG_FALSE);
    }
    return status;
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::removeChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    CSceneNode* pChild = NULL;
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
    if(m_children.empty()) {
        setFlag(DRAWABLE_CHILDREN, FG_FALSE);
    } else if(pChild && pChild->hasTraits(fg::traits::DRAWABLE)) {
        refreshDrawableFlag();
    }
    return pChild;
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::removeChild(const char* childName) {
    if(!childName || m_children.empty())
        return NULL;
    if(!*childName)
        return NULL;
    return removeChild(std::string(childName));
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::destroyChild(CSceneNode*& pChild) {
    if(!pChild)
        return FG_FALSE;
    if(m_children.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    fgBool managerValid = FG_FALSE;
    ChildrenVecItor it = m_children.findItor(pChild);
    const fgBool isDrawable = pChild->hasTraits(fg::traits::DRAWABLE);
    if(it == m_children.end()) {
        status = FG_FALSE;
    } else {
        m_children.erase(it);
        // This is required so the scene manager wont call again this function
        // to remove the child from it's parent
        pChild->setParent(NULL);
        if(m_pManager) { // #FIXME
            if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                managerValid = static_cast<CSceneManager *>(m_pManager)->destroyNode(pChild);
            }
        }
        if(!managerValid) {
            delete pChild;
            pChild = NULL;
        }
    }
    if(status && isDrawable) {
        refreshDrawableFlag();
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::destroyChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return FG_FALSE;
    CSceneNode* pChild = NULL;
    fgBool secondCheck = FG_TRUE;
    ChildrenVecItor it = m_children.end();
    fgBool managerValid = FG_FALSE, isDrawable = FG_FALSE;
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
        isDrawable = pChild->hasTraits(fg::traits::DRAWABLE);
        // The child is found
        if(it != m_children.end()) {
            pChild->setParent(NULL);
            m_children.erase(it);
            fgBool destroyStatus = FG_FALSE;
            // Scene node has access to manager - this will change when
            // scene manager will register special callbacks inside of a node
            // However deletion not. Deletion will be automatic (on object destructor
            // scene mgr callback is fired)
            if(managerValid) {
                // #FIXME
                destroyStatus = static_cast<CSceneManager *>(m_pManager)->destroyNode(pChild);
            }
            if(!destroyStatus) {
                // the destroyNode function failed, need to delete manually
                delete pChild;
                pChild = NULL;
            }
            status = FG_TRUE;
        }
    }
    if(status && isDrawable) {
        refreshDrawableFlag();
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::destroyChild(const char* childName) {
    if(!childName)
        return FG_FALSE;
    if(!*childName)
        return FG_FALSE;
    return destroyChild(std::string(childName));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::getChild(const gfx::CSceneNode::handle_type& childHandle) {
    if(childHandle.isNull() || m_children.empty())
        return NULL;
    CSceneNode* pChild = NULL;
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
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::getChild(const std::string& childName) {
    if(childName.empty() || m_children.empty())
        return NULL;
    CSceneNode* pChild = NULL;
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
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::getChild(const char *childName) {
    return getChild(std::string(childName));
}
//------------------------------------------------------------------------------

gfx::CSceneNode* gfx::CSceneNode::getChildByIndex(const unsigned int index) {
    if(!getChildrenCount())
        return NULL;
    if(index >= getChildrenCount())
        return NULL;
    CSceneNode* pChild = m_children[index];
    return pChild;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::hasChild(CSceneNode* pChild) {
    if(!pChild || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    int it = m_children.find(pChild);
    if(it != -1)
        status = FG_TRUE;
    return status;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::hasChild(const std::string& childName) {
    if(m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(getChild(childName))
        status = FG_TRUE;
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNode::hasChild(const char* childName) {
    if(!childName || m_children.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    if(getChild(childName))
        status = FG_TRUE;
    return status;
}
//------------------------------------------------------------------------------
