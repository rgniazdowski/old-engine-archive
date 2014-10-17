/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXVertexData.h"
#include "fgGFXPlatform.h"
#include "Util/fgMemory.h"

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData2v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride()*this->size(), fgVertexData2v::front());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData2v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData2v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}


/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData3v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride()*this->size(), fgVertexData3v::front());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData3v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData3v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}


/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride()*this->size(), fgVertexData4v::front());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}
