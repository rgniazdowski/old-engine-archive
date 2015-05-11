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
 * File:   fgGfxBspFile.cpp
 * Author: vigilant
 * 
 * Created on May 10, 2015, 7:22 PM
 */

#include "fgGfxBspFile.h"
#include "fgGfxBspCompiler.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CBspFile::CBspFile() :
base_type() { }

//------------------------------------------------------------------------------

gfx::CBspFile::~CBspFile() {
    close();
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::save(const CBspTree* pBspTree, fgBool closeAfter) {
    fgBool status = FG_TRUE;
    if(!pBspTree) {
        status = FG_FALSE;
    }
    if(isOpen() && status) {
        status = close();
    }
    if(status) {
        status = open(Mode::BINARY | Mode::WRITE);
    }
    if(status) {
        prepareTag();
        m_mainHeader.hasBsp = FG_TRUE;
        m_mainHeader.hasPortalProc = FG_FALSE;
        m_mainHeader.hasPvsProc = FG_FALSE;
        m_mainHeader.bspType = (int)pBspTree->getBspType();
        m_mainHeader.balance = pBspTree->getBalance();
        m_mainHeader.numNodes = pBspTree->getNodes().size();
        m_mainHeader.numLeafs = pBspTree->getLeafs().size();
        m_mainHeader.numPolygons = pBspTree->getPolygons().size();
        m_mainHeader.numPlanes = pBspTree->getPlanes().size();
        m_mainHeader.numMaterials = pBspTree->getMaterials().size();
        status = (fgBool)!!(this->write(&m_mainHeader, sizeof (m_mainHeader), 1));
    }
    if(status) {
        status = writeBspTree(pBspTree);
    }
    if(status && closeAfter) {
        status = close();
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::load(CBspTree* pBspTree, fgBool closeAfter) {
    fgBool status = FG_TRUE;
    if(!pBspTree)
        status = FG_FALSE;
    if(isOpen() && status) {
        status = close();
    }
    if(status) {
        status = open(Mode::BINARY | Mode::READ);
    }
    if(status)
        status = (fgBool)!!(this->read(&m_mainHeader, sizeof (m_mainHeader), 1));

    if(status)
        status = checkTag();

    if(status && m_mainHeader.hasBsp)
        status = readBspTree(pBspTree);

    if(status && closeAfter) {
        status = close();
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::save(const CBspCompiler* pBspCompiler, fgBool closeAfter) {
    fgBool status = FG_TRUE;
    if(!pBspCompiler)
        status = FG_FALSE;
    if(isOpen() && status) {
        status = close();
    }
    if(status) {
        status = open(Mode::BINARY | Mode::WRITE);
    }

    const CBspTree* pBspTree = NULL;
    const CPvsProcessor* pPvsProc = NULL;
    const CPortalProcessor* pPortalProc = NULL;

    if(status) {
        prepareTag();
        pBspTree = &pBspCompiler->getBspTree();
        pPvsProc = &pBspCompiler->getPvsProcessor();
        pPortalProc = &pBspCompiler->getPortalProcessor();
        m_mainHeader.hasBsp = FG_TRUE;
        m_mainHeader.hasPortalProc = FG_TRUE;
        m_mainHeader.hasPvsProc = FG_TRUE;
        m_mainHeader.bspType = (int)pBspTree->getBspType();
        m_mainHeader.balance = pBspTree->getBalance();
        m_mainHeader.numNodes = pBspTree->getNodes().size();
        m_mainHeader.numLeafs = pBspTree->getLeafs().size();
        m_mainHeader.numPolygons = pBspTree->getPolygons().size();
        m_mainHeader.numPlanes = pBspTree->getPlanes().size();
        m_mainHeader.numMaterials = pBspTree->getMaterials().size();
        status = (fgBool)!!(this->write(&m_mainHeader, sizeof (m_mainHeader), 1));
    }

    if(status)
        status = writeBspTree(pBspTree);

    if(status)
        status = writePortalProcessor(pPortalProc);

    if(status)
        status = writePvsProcessor(pPvsProc);

    if(status && closeAfter) {
        status = close();
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::load(CBspCompiler* pBspCompiler, fgBool closeAfter) {
    fgBool status = FG_TRUE;
    if(!pBspCompiler)
        return FG_FALSE;
    if(isOpen() && status) {
        status = close();
    }
    if(status) {
        status = open(Mode::BINARY | Mode::READ);
    }
    CBspTree* pBspTree = NULL;
    CPvsProcessor* pPvsProc = NULL;
    CPortalProcessor* pPortalProc = NULL;

    if(status)
        status = (fgBool)!!(this->read(&m_mainHeader, sizeof (m_mainHeader), 1));

    if(status)
        status = checkTag();

    if(status && m_mainHeader.hasBsp)
        status = readBspTree(pBspTree);

    if(status && m_mainHeader.hasPortalProc)
        status = readPortalProcessor(pPortalProc);

    if(status && m_mainHeader.hasPvsProc);
    status = readPvsProcessor(pPvsProc);

    if(status && closeAfter) {
        status = close();
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CBspFile::prepareTag(void) {
    m_mainHeader.tag[0] = (char)('f' + 96);
    m_mainHeader.tag[1] = (char)('g' + 96);
    m_mainHeader.tag[2] = (char)('_' + 96);
    m_mainHeader.tag[3] = (char)('b' + 96);
    m_mainHeader.tag[4] = (char)('s' + 96);
    m_mainHeader.tag[5] = (char)('p' + 96);
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::checkTag(void) {
    fgBool status = FG_FALSE;
    if(m_mainHeader.tag[0] == (char)('f' + 96)) {
        for(unsigned int i = 0; i < 6; i++) {
            m_mainHeader.tag[i] -= 96;
        }
    }
    if(m_mainHeader.tag[0] == 'f') {
        if(strncmp(m_mainHeader.tag, "fg_bsp", 6) == 0)
            status = FG_TRUE;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::writeBspTree(const CBspTree* pBspTree) {
    fgBool status = FG_TRUE;
    if(!pBspTree)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(!(m_modeFlags & Mode::WRITE))
        status = FG_FALSE;

    // This function is for internal use only - 
    // the main header should be already written

    //--------------------------------------------------------------------------
    // NODES
    CBspTree::NodesVec const& nodesVec = pBspTree->getNodes();
    const unsigned int numNodes = nodesVec.size();
    if(!numNodes)
        status = FG_FALSE;
    if(status) {
        SBinDataVecChunkHeader nodesH;
        nodesH.chunkType = ChunkType::BSP_NODES;
        nodesH.numChunks = numNodes;
        status = (fgBool)!!(this->write(&nodesH, sizeof (nodesH), 1));
    }
    for(unsigned int i = 0; i < numNodes && status; i++) {
        CBspNode* pNode = nodesVec[i];
        if(!pNode) {
            status = FG_FALSE;
            break;
        }
        status = (fgBool)!!(this->write(pNode, sizeof (CBspNode), 1));
    }
    //--------------------------------------------------------------------------
    // LEAFS
    CBspTree::LeafsVec const& leafsVec = pBspTree->getLeafs();
    const unsigned int numLeafs = leafsVec.size();
    if(!numLeafs)
        status = FG_FALSE;
    if(status) {
        SBinDataVecChunkHeader leafsH;
        leafsH.chunkType = ChunkType::BSP_LEAFS;
        leafsH.numChunks = numLeafs;
        status = (fgBool)!!(this->write(&leafsH, sizeof (leafsH), 1));
    }
    for(unsigned int i = 0; i < numLeafs && status; i++) {
        CBspLeaf* pLeaf = leafsVec[i];
        if(!pLeaf) {
            status = FG_FALSE;
            break;
        }
        // will now write CBspLeaf - it's like a node with additional integers and
        // CVector<int> which needs to be saved/read manually
        status = (fgBool)!!(this->write(static_cast<CBspNode*>(pLeaf), sizeof (CBspNode), 1));
        if(!status)
            continue;

        this->write(&pLeaf->m_pvsIdx, sizeof (int), 1);
        this->write(&pLeaf->m_flags, sizeof (unsigned long int), 1);
        int numIdxs = pLeaf->m_portalIdxes.size();
        this->write(&numIdxs, sizeof (unsigned int), 1);
        if(numIdxs)
            this->write(&pLeaf->m_portalIdxes.front(), sizeof (int), numIdxs);
    }
    //--------------------------------------------------------------------------
    // POLYGONS
    CBspTree::PolygonsVec const& polygons = pBspTree->getPolygons();
    const unsigned int numPolygons = polygons.size();
    if(!numPolygons)
        status = FG_FALSE;
    if(status) {
        SBinDataVecChunkHeader polysH;
        polysH.chunkType = ChunkType::POLYGONS;
        polysH.numChunks = numPolygons;
        status = (fgBool)!!(this->write(&polysH, sizeof (polysH), 1));
    }
    for(unsigned int i = 0; i < numPolygons && status; i++) {
        const SPolygon& polygon = polygons[i];
        // Size to write from the polygon
        // It should be somehow guaranteed that CVertexData* pointer is last in the structure
        // Pragma pack?
        const unsigned int beginSize = sizeof (Planef) + sizeof (int) * 2 +
                sizeof (unsigned int) +
                sizeof (AABoundingBox3Df);
        status = (fgBool)!!(this->write(&polygon, beginSize, 1));
        if(!status)
            continue;
        SBinPolygonVertexDataHeader vertexDataH;
        vertexDataH.vertexType = 4; // #FIXME / #AUTO
        vertexDataH.vertexStride = polygon.getVertexData()->stride();
        if(polygon.getVertexData())
            vertexDataH.numVertices = polygon.getVertexData()->size();
        else
            vertexDataH.numVertices = 0;
        status = (fgBool)!!(this->write(&vertexDataH, sizeof (SBinPolygonVertexDataHeader), 1));
        if(!status)
            continue;
        status = (fgBool)!!(this->write(polygon.getVertexData()->front(),
                                        polygon.getVertexData()->stride(),
                                        polygon.getVertexData()->size()));
    }
    //--------------------------------------------------------------------------
    // PLANES
    CBspTree::PlanesVec const& planes = pBspTree->getPlanes();
    const unsigned int numPlanes = planes.size();
    if(!numPlanes)
        status = FG_FALSE;
    if(status) {
        SBinDataVecChunkHeader planesH;
        planesH.chunkType = ChunkType::PLANES;
        planesH.numChunks = numPlanes;
        status = (fgBool)!!(this->write(&planesH, sizeof (planesH), 1));
    }
    for(unsigned int i = 0; i < numPlanes && status; i++) {
        const Planef& plane = planes[i];
        // plane is just a Vec3f, float + enum (int)
        status = (fgBool)!!(this->write(&plane, sizeof (Planef), 1));
    }
    //--------------------------------------------------------------------------
    // MATERIALS - BINARY
    {
        CBspTree::MaterialsVec const& materials = pBspTree->getMaterials();
        const unsigned int numMaterials = materials.size();
        if(status) {
            SBinDataVecChunkHeader materialsH;
            materialsH.chunkType = ChunkType::MATERIALS;
            materialsH.numChunks = numMaterials;
            status = (fgBool)!!(this->write(&materialsH, sizeof (materialsH), 1));
        }
        for(unsigned int i = 0; i < numMaterials && status; i++) {
            const SMaterial& material = materials[i];
            const unsigned int beginSize = (unsigned int)SMaterial::getDataStrideTrivial();
            SBinMaterialInfoHeader matInfoH;
            status = (fgBool)!!(this->write(&material, beginSize, 1));
            if(!status)
                continue;
            matInfoH.nameLen = material.name.length();
            matInfoH.shaderNameLen = material.shaderName.length();
            matInfoH.ambientTexNameLen = material.ambientTexName.length();
            matInfoH.diffuseTexNameLen = material.diffuseTexName.length();
            matInfoH.specularTexNameLen = material.specularTexName.length();
            matInfoH.normalTexNameLen = material.normalTexName.length();
            status = (fgBool)!!(this->write(&matInfoH, sizeof (matInfoH), 1));
            if(!status)
                continue;
            this->write(material.name.c_str(), sizeof (char), matInfoH.nameLen);
            this->write(material.shaderName.c_str(), sizeof (char), matInfoH.shaderNameLen);
            this->write(material.ambientTexName.c_str(), sizeof (char), matInfoH.ambientTexNameLen);
            this->write(material.diffuseTexName.c_str(), sizeof (char), matInfoH.diffuseTexNameLen);
            this->write(material.specularTexName.c_str(), sizeof (char), matInfoH.specularTexNameLen);
            this->write(material.normalTexName.c_str(), sizeof (char), matInfoH.normalTexNameLen);
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::readBspTree(CBspTree* pBspTree) {
    fgBool status = FG_TRUE;
    if(!pBspTree)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(!(m_modeFlags & Mode::READ))
        status = FG_FALSE;
    // This function is for internal use only - 
    // the main header should already be read    

    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::writePortalProcessor(const CPortalProcessor* pPortalProc) {
    fgBool status = FG_TRUE;
    if(!pPortalProc)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(status && !(m_modeFlags & Mode::WRITE))
        status = FG_FALSE;

    CPortalProcessor::PortalsVec const& portals = pPortalProc->getPortals();
    const unsigned int numPortals = portals.size();
    if(status) {
        SBinDataVecChunkHeader portalsH;
        portalsH.chunkType = ChunkType::PORTALS;
        portalsH.numChunks = numPortals;
        status = (fgBool)!!(this->write(&portalsH, sizeof (portalsH), 1));
    }

    for(unsigned int i = 0; i < numPortals && status; i++) {
        const CPortal& portal = portals[i];
        // write the plane part
        status = (fgBool)!!(this->write(static_cast<const Planef *>(&portal),
                                        sizeof (Planef), 1));
        if(!status)
            continue;
        this->write(&portal.m_idxThis, sizeof (int), 1);
        this->write(&portal.m_planeIdx, sizeof (int), 1);
        this->write(&portal.m_flags, sizeof (CPortal::StateFlags), 1);
        // now the Portal header - information about internal arrays
        SBinPortalVecDataHeader portalInfo;
        portalInfo.numVertices = portal.m_vertexes.size();
        portalInfo.numSideLIdx = portal.m_sideLIdx.size();
        portalInfo.numSideLIdxFinal = portal.m_sideLIdxFinal.size();
        status = (fgBool)!!(this->write(&portalInfo, sizeof (portalInfo), 1));
        if(!status)
            continue;
        // vertexes
        status = (fgBool)!!(this->write(&portal.m_vertexes.front(),
                                        sizeof (Vector3f),
                                        portalInfo.numVertices)
                            == (int)portalInfo.numVertices);
        if(!status)
            continue;
        // sideLIdx
        status = (fgBool)!!(this->write(&portal.m_sideLIdx.front(),
                                        sizeof (int),
                                        portalInfo.numSideLIdx)
                            == (int)portalInfo.numSideLIdx);
        if(!status)
            continue;
        // sideLIdxFinal
        status = (fgBool)!!(this->write(&portal.m_sideLIdxFinal.front(),
                                        sizeof (int),
                                        portalInfo.numSideLIdxFinal)
                            == (int)portalInfo.numSideLIdxFinal);
        if(!status)
            continue;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::readPortalProcessor(CPortalProcessor* pPortalProc) {
    fgBool status = FG_TRUE;
    if(!pPortalProc)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(!(m_modeFlags & Mode::READ))
        status = FG_FALSE;

    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::writePvsProcessor(const CPvsProcessor* pPvsProc) {
    fgBool status = FG_TRUE;
    if(!pPvsProc)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(!(m_modeFlags & Mode::WRITE))
        status = FG_FALSE;

    CPvsProcessor::PPortalsDataVec const& portalsData = pPvsProc->getPortalsData();
    const unsigned int numPortalsData = portalsData.size();
    if(status) {
        SBinDataVecChunkHeader pvsH;
        pvsH.chunkType = ChunkType::BSP_PVS_PROC;
        pvsH.numChunks = numPortalsData;
        status = (fgBool)!!(this->write(&pvsH, sizeof (pvsH), 1));
    }
    if(status) {
        // Additional info header
        SBinPvsProcessorHeader pvsH;
        pvsH.numLeafs = pPvsProc->getNumLeafs();
        pvsH.numPvs = pPvsProc->getNumPvs();
        pvsH.numPortVs = numPortalsData; // repeat
        status = (fgBool)!!(this->write(&pvsH, sizeof (pvsH), 1));
    }
    if(status) {
        // now will write the unsigned chars of the pvs
        status = (fgBool)!!(this->write(pPvsProc->getPvs(),
                                        sizeof (unsigned char),
                                        pPvsProc->getNumPvs()));
    }
    for(unsigned int i = 0; i < numPortalsData && status; i++) {
        const SPortalData* portalData = portalsData[i];
        if(!portalData) {
            // this should not happen
            status = FG_FALSE;
            break;
        }
        int tmp;
        // will write PortalData info header
        SBinPortalDataInfoHeader portalDataH;
        portalDataH.size = portalData->size;
        portalDataH.possibleVisCount = portalData->possibleVisCount;
        portalDataH.sizeBitArray = portalData->portArrPvs.size();
        const unsigned char *bitBuffer = portalData->portArrPvs.buffer(tmp);
        if(!bitBuffer) {
            status = FG_FALSE;
            break;
        }
        // write info header
        status = (fgBool)!!(this->write(&portalDataH,
                                        sizeof (portalDataH), 1));

        if(!status)
            break;

        // now can write the bit array storage (unsigned char)
        status = (fgBool)!!(this->write(bitBuffer,
                                        sizeof (unsigned char),
                                        portalDataH.sizeBitArray)
                            == (int)portalDataH.sizeBitArray);
    }

    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::readPvsProcessor(CPvsProcessor* pPvsProc) {
    fgBool status = FG_TRUE;
    if(!pPvsProc)
        return FG_FALSE;
    if(!isOpen())
        status = FG_FALSE;
    if(!(m_modeFlags & Mode::READ))
        status = FG_FALSE;

    if(status) {
        SBinDataVecChunkHeader pvsH;
        status = (fgBool)!!(this->read(&pvsH, sizeof (pvsH), 1));
        if(pvsH.chunkType != ChunkType::BSP_PVS_PROC)
            status = FG_FALSE;
        if(!pvsH.numChunks)
            status = FG_FALSE;
    }
    SBinPvsProcessorHeader pvsProcHeader;
    if(status) {
        // now read additional header
        status = (fgBool)!!(this->read(&pvsProcHeader,
                                       sizeof (pvsProcHeader), 1));
    }
    if(status) {
        // now can clear out the destination pvs proc
        pPvsProc->clear();
    }
    //pPvsProc->m_numLeafs = pvsProcHeader.numLeafs;

    return status;
}
//------------------------------------------------------------------------------
