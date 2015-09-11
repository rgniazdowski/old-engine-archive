/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgGfxShape.cpp
 * Author: vigilant
 * 
 * Created on September 10, 2015, 11:15 AM
 */

#include "fgGfxShape.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::SShape::SShape() : name(), material(NULL), mesh(NULL) { }
//------------------------------------------------------------------------------

gfx::SShape::~SShape() {
    destroy();
}
//------------------------------------------------------------------------------

void gfx::SShape::updateAABB(void) {
    if(mesh)
        mesh->updateAABB();
}
//------------------------------------------------------------------------------

fgBool gfx::SShape::isSoA(void) const {
    if(mesh)
        return mesh->isSoA();
    else
        return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::SShape::isAoS(void) const {
    if(mesh)
        return mesh->isAoS();
    else
        return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::SShape::isSkinned(void) const {
    if(mesh)
        return mesh->isSkinnedMesh();
    else
        return FG_FALSE;
}
//------------------------------------------------------------------------------

gfx::SSkinnedMesh* gfx::SShape::getSkinnedMesh(void) {
    if(!mesh)
        return NULL;
    if(!mesh->isSkinnedMesh())
        return NULL;
    // use up-cast and then down-cast
    if(mesh->isAoS())
        return static_cast<SSkinnedMesh*>(static_cast<SSkinnedMeshAoS*>(mesh));
    else if(mesh->isSoA())
        return static_cast<SSkinnedMesh*>(static_cast<SSkinnedMeshSoA*>(mesh));
    return NULL;
}
//------------------------------------------------------------------------------

gfx::SMeshAoS* gfx::SShape::getMeshAoS(void) {
    if(!mesh)
        return NULL;
    if(mesh->isAoS())
        return static_cast<SMeshAoS*>(mesh);
    return NULL;
}
//------------------------------------------------------------------------------

gfx::SMeshSoA* gfx::SShape::getMeshSoA(void) {
    if(!mesh)
        return NULL;
    if(mesh->isSoA())
        return static_cast<SMeshSoA*>(mesh);
    return NULL;
}
//------------------------------------------------------------------------------

fgGFXuint gfx::SShape::size(void) const {
    if(mesh)
        return mesh->size();
    else
        return 0;
}
//------------------------------------------------------------------------------

fgGFXsizei gfx::SShape::stride(void) const {
    if(mesh)
        return mesh->stride();
    else
        return 0;
}
//------------------------------------------------------------------------------

gfx::AttributeMask gfx::SShape::attribMask(void) const {
    if(mesh)
        return mesh->attribMask();
    else
        return ATTRIBUTE_ZERO_BIT;
}
//------------------------------------------------------------------------------

fgGFXuint gfx::SShape::components(void) const {
    if(mesh)
        return mesh->components();
    else
        return 0;
}
//------------------------------------------------------------------------------

fgBool gfx::SShape::empty(void) const {
    if(mesh)
        return (fgBool)mesh->empty();
    else
        return FG_TRUE;
}
//------------------------------------------------------------------------------

fgGFXvoid* gfx::SShape::front(void) const {
    if(mesh)
        return mesh->front();
    else
        return NULL;
}
//------------------------------------------------------------------------------

void gfx::SShape::destroy(void) {
    if(material)
        delete material;
    material = NULL;

    if(mesh)
        delete mesh;
    mesh = NULL;
    name.clear();
}
//------------------------------------------------------------------------------

void gfx::SShape::clear(void) {
    if(mesh)
        mesh->clear();
}
//------------------------------------------------------------------------------

size_t gfx::SShape::getDataSize(void) {
    size_t size = 0;
    size += name.length();
    size += sizeof (SShape);
    if(material)
        size += material->getDataSize();
    if(mesh)
        size += mesh->getDataSize();
    return size;
}
//------------------------------------------------------------------------------
