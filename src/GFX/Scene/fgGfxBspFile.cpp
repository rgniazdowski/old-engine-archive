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

    status = (fgBool)(checkTag() && status);

    if(status && m_mainHeader.hasBsp) {
        pBspTree = pBspCompiler->getBspTreePtr();
        status = readBspTree(pBspTree);
    }

    if(status && m_mainHeader.hasPortalProc) {
        pPortalProc = pBspCompiler->getPortalProcessorPtr();
        status = readPortalProcessor(pPortalProc);
    }

    if(status && m_mainHeader.hasPvsProc) {
        pPvsProc = pBspCompiler->getPvsProcessorPtr();
        status = readPvsProcessor(pPvsProc);
    }

    if(status && closeAfter) {
        status = close();
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CBspFile::prepareTag(void) {
    m_mainHeader.tag[0] = (unsigned char)('f' + 96);
    m_mainHeader.tag[1] = (unsigned char)('g' + 96);
    m_mainHeader.tag[2] = (unsigned char)('_' + 96);
    m_mainHeader.tag[3] = (unsigned char)('b' + 96);
    m_mainHeader.tag[4] = (unsigned char)('s' + 96);
    m_mainHeader.tag[5] = (unsigned char)('p' + 96);
}
//------------------------------------------------------------------------------

fgBool gfx::CBspFile::checkTag(void) {
    fgBool status = FG_FALSE;
    const char *tag = "fg_bsp";
    unsigned int cc = 0;
    if(m_mainHeader.tag[0] == (unsigned char)('f' + 96)) {
        for(unsigned int i = 0; i < 6; i++) {
            m_mainHeader.tag[i] -= 96;
            if(m_mainHeader.tag[i] == (unsigned char)tag[i])
                cc++;
            m_mainHeader.tag[i] += 96;
        }
    }
    if(cc == 6)
        status = FG_TRUE;
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
    status = (fgBool)(status && checkTag());
    status = (fgBool)(status && m_mainHeader.hasBsp);
    status = (fgBool)!!(m_mainHeader.numNodes > 0 && status);
    status = (fgBool)!!(m_mainHeader.numLeafs > 0 && status);
    status = (fgBool)!!(m_mainHeader.numPolygons > 0 && status);
    if(!status)
        return FG_FALSE;
    pBspTree->clear();
    pBspTree->setType((CBspTree::BspType)m_mainHeader.bspType);
    pBspTree->setBalance(m_mainHeader.balance);

    //--------------------------------------------------------------------------
    // READING NODES
    CBspTree::NodesVec& nodesVec = pBspTree->getNodes();
    const unsigned int numNodes = m_mainHeader.numNodes;
    nodesVec.reserve(numNodes);
    nodesVec.resize(numNodes);

    SBinDataVecChunkHeader nodesH;
    status = (fgBool)!!(this->read(&nodesH, sizeof (nodesH), 1));
    status = (fgBool)(status && nodesH.numChunks == numNodes);
    status = (fgBool)(status && nodesH.chunkType == ChunkType::BSP_NODES);
    for(unsigned int i = 0; i < numNodes && status; i++) {
        nodesVec[i] = NULL;
        CBspNode* pNode = new CBspNode(NULL, 0);
        if(!pNode) {
            status = FG_FALSE;
            break;
        }
        // this is not universal solution - will be screwed up
        // if the file will be saved by 32bit app and loaded by 64bit app
        // reason? The whole structure/class is being read/saved
        // there is pointer inside -> it's 4 or 8 bytes...
        status = (fgBool)!!(this->read(pNode, sizeof (CBspNode), 1));
        pNode->setBsp(pBspTree);
        nodesVec[i] = pNode;
    }
    //--------------------------------------------------------------------------
    // READING LEAFS
    CBspTree::LeafsVec& leafsVec = pBspTree->getLeafs();
    const unsigned int numLeafs = m_mainHeader.numLeafs;
    if(status) {
        leafsVec.reserve(numLeafs);
        leafsVec.resize(numLeafs);
        SBinDataVecChunkHeader leafsH;
        status = (fgBool)!!(this->read(&leafsH, sizeof (leafsH), 1));
        status = (status && leafsH.numChunks == numLeafs);
        status = (status && leafsH.chunkType == ChunkType::BSP_LEAFS);
    }
    for(unsigned int i = 0; i < numLeafs && status; i++) {
        CBspLeaf* pLeaf = new CBspLeaf(NULL, 0);
        if(!pLeaf) {
            status = FG_FALSE;
            break;
        }
        // will now read CBspLeaf - it's like a node with additional integers and
        // CVector<int> which needs to be read manually
        status = (fgBool)!!(this->read(static_cast<CBspNode*>(pLeaf), sizeof (CBspNode), 1));
        if(!status) {
            leafsVec[i] = NULL;
            delete pLeaf;
            continue;
        }
        this->read(&pLeaf->m_pvsIdx, sizeof (int), 1);
        this->read(&pLeaf->m_flags, sizeof (unsigned long int), 1);
        int numIdxs = 0;
        this->read(&numIdxs, sizeof (unsigned int), 1);
        if(numIdxs) {
            pLeaf->m_portalIdxes.reserve(numIdxs);
            pLeaf->m_portalIdxes.resize(numIdxs);
            status = (fgBool)!!(this->read(&pLeaf->m_portalIdxes.front(),
                                           sizeof (int), numIdxs)
                                == numIdxs);
        }
        pLeaf->setBsp(pBspTree);
        leafsVec[i] = pLeaf;
    }
    //--------------------------------------------------------------------------
    // READING POLYGONS
    CBspTree::PolygonsVec& polygons = pBspTree->getPolygons();
    const unsigned int numPolygons = m_mainHeader.numPolygons;
    if(status) {
        polygons.reserve(numPolygons);
        polygons.resize(numPolygons);
        SBinDataVecChunkHeader polysH;
        status = (fgBool)!!(this->read(&polysH, sizeof (polysH), 1));
        status = (status && polysH.numChunks == numPolygons);
        status = (status && polysH.chunkType == ChunkType::POLYGONS);
    }
    for(unsigned int i = 0; i < numPolygons && status; i++) {
        SPolygon& polygon = polygons[i];
        // Size to read from the polygon
        // It should be somehow guaranteed that CVertexData* pointer is last in the structure
        // Pragma pack?
        const unsigned int beginSize = sizeof (Planef) + sizeof (int) * 2 +
                sizeof (unsigned int) +
                sizeof (AABoundingBox3Df);
        status = (fgBool)!!(this->read(&polygon, beginSize, 1));
        if(!status)
            continue;
        SBinPolygonVertexDataHeader vertexDataH;
        status = (fgBool)!!(this->read(&vertexDataH, sizeof (SBinPolygonVertexDataHeader), 1));
        if(!status)
            continue;
        status = (vertexDataH.vertexStride == Vertex4v::stride());
        if(polygon.getVertexData() == NULL) {
            // this should not happen
            status = FG_FALSE;
            continue;
        }
        polygon.getVertexData()->reserve(vertexDataH.numVertices);
        polygon.getVertexData()->resize(vertexDataH.numVertices);

        status = (fgBool)!!(this->read(polygon.getVertexData()->front(),
                                       polygon.getVertexData()->stride(),
                                       vertexDataH.numVertices)
                            == (int)vertexDataH.numVertices);
    }
    //--------------------------------------------------------------------------
    // PLANES
    CBspTree::PlanesVec& planes = pBspTree->getPlanes();
    const unsigned int numPlanes = m_mainHeader.numPlanes;

    if(status) {
        planes.reserve(numPlanes);
        planes.resize(numPlanes);
        SBinDataVecChunkHeader planesH;
        status = (fgBool)!!(this->read(&planesH, sizeof (planesH), 1));
        status = (status && planesH.numChunks == numPlanes);
        status = (status && planesH.chunkType == ChunkType::PLANES);
    }
    for(unsigned int i = 0; i < numPlanes && status; i++) {
        Planef& plane = planes[i];
        // plane is just a Vec3f, float + enum (int)
        status = (fgBool)!!(this->read(&plane, sizeof (Planef), 1));
    }
    //--------------------------------------------------------------------------
    // MATERIALS - BINARY
    {
        CBspTree::MaterialsVec& materials = pBspTree->getMaterials();
        const unsigned int numMaterials = m_mainHeader.numMaterials;
        if(status) {
            materials.reserve(numMaterials);
            materials.resize(numMaterials);
            SBinDataVecChunkHeader materialsH;
            status = (fgBool)!!(this->read(&materialsH, sizeof (materialsH), 1));
            status = (status && materialsH.numChunks == numMaterials);
            status = (status && materialsH.chunkType == ChunkType::MATERIALS);
        }
        for(unsigned int i = 0; i < numMaterials && status; i++) {
            SMaterial& material = materials[i];
            const unsigned int beginSize = (unsigned int)SMaterial::getDataStrideTrivial();
            status = (fgBool)!!(this->read(&material, beginSize, 1));
            if(!status)
                continue;
            SBinMaterialInfoHeader matInfoH;
            status = (fgBool)!!(this->read(&matInfoH, sizeof (matInfoH), 1));
            if(!status)
                continue;
            const int strBufSize = 256;
            char str[strBufSize];
            memset(str, 0, strBufSize);
            if(matInfoH.nameLen) {
                this->read(str, sizeof (char), matInfoH.nameLen);
                material.name.clear();
                material.name.reserve(matInfoH.nameLen + 1);
                str[matInfoH.nameLen] = 0;
                material.name.append(str);
            }
            if(matInfoH.shaderNameLen) {
                this->read(str, sizeof (char), matInfoH.shaderNameLen);
                material.shaderName.clear();
                material.shaderName.reserve(matInfoH.shaderNameLen + 1);
                str[matInfoH.shaderNameLen] = 0;
                material.shaderName.append(str);
            }
            if(matInfoH.ambientTexNameLen) {
                this->read(str, sizeof (char), matInfoH.ambientTexNameLen);
                material.ambientTexName.clear();
                material.ambientTexName.reserve(matInfoH.ambientTexNameLen + 1);
                str[matInfoH.ambientTexNameLen] = 0;
                material.ambientTexName.append(str);
            }
            if(matInfoH.diffuseTexNameLen) {
                this->read(str, sizeof (char), matInfoH.diffuseTexNameLen);
                material.diffuseTexName.clear();
                material.diffuseTexName.reserve(matInfoH.diffuseTexNameLen + 1);
                str[matInfoH.diffuseTexNameLen] = 0;
                material.diffuseTexName.append(str);
            }
            if(matInfoH.specularTexNameLen) {
                this->read(str, sizeof (char), matInfoH.specularTexNameLen);
                material.specularTexName.clear();
                material.specularTexName.reserve(matInfoH.specularTexNameLen + 1);
                str[matInfoH.specularTexNameLen] = 0;
                material.specularTexName.append(str);
            }
            if(matInfoH.normalTexNameLen) {
                this->read(str, sizeof (char), matInfoH.normalTexNameLen);
                material.normalTexName.clear();
                material.normalTexName.reserve(matInfoH.normalTexNameLen + 1);
                str[matInfoH.normalTexNameLen] = 0;
                material.normalTexName.append(str);
            }
        }
    }

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
    status = m_mainHeader.hasPortalProc;
    SBinDataVecChunkHeader portalsH;
    if(status)
        status = (fgBool)!!(this->read(&portalsH, sizeof (portalsH), 1));
    if(status)
        status = (portalsH.chunkType == ChunkType::PORTALS);
    if(status)
        pPortalProc->clear();
    CPortalProcessor::PortalsVec& portals = pPortalProc->getPortals();
    if(status) {
        portals.reserve(portalsH.numChunks);
        portals.resize(portalsH.numChunks);
    }
    for(unsigned int i = 0; i < portalsH.numChunks && status; i++) {
        CPortal& portal = portals[i];
        // read the plane part
        status = (fgBool)!!(this->read(static_cast<Planef *>(&portal),
                                       sizeof (Planef), 1));
        if(!status)
            continue;
        this->read(&portal.m_idxThis, sizeof (int), 1);
        this->read(&portal.m_planeIdx, sizeof (int), 1);
        this->read(&portal.m_flags, sizeof (CPortal::StateFlags), 1);

        // now the Portal header - information about internal arrays
        SBinPortalVecDataHeader portalInfo;
        status = (fgBool)!!(this->read(&portalInfo, sizeof (portalInfo), 1));
        if(!status)
            continue;
        // vertexes
        portal.m_vertexes.reserve(portalInfo.numVertices + 1);
        portal.m_vertexes.resize(portalInfo.numVertices);
        status = (fgBool)!!(this->read(&portal.m_vertexes.front(),
                                       sizeof (Vector3f),
                                       portalInfo.numVertices)
                            == (int)portalInfo.numVertices);
        if(!status)
            continue;
        // sideLIdx
        portal.m_sideLIdx.reserve(portalInfo.numSideLIdx);
        portal.m_sideLIdx.resize(portalInfo.numSideLIdx);
        status = (fgBool)!!(this->read(&portal.m_sideLIdx.front(),
                                       sizeof (int),
                                       portalInfo.numSideLIdx)
                            == (int)portalInfo.numSideLIdx);
        if(!status)
            continue;
        // sideLIdxFinal
        portal.m_sideLIdxFinal.reserve(portalInfo.numSideLIdxFinal);
        portal.m_sideLIdxFinal.resize(portalInfo.numSideLIdxFinal);
        status = (fgBool)!!(this->read(&portal.m_sideLIdxFinal.front(),
                                       sizeof (int),
                                       portalInfo.numSideLIdxFinal)
                            == (int)portalInfo.numSideLIdxFinal);
        if(!status)
            continue;
    }
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
    if(status && numPortalsData == 0)
        return status; // do not save
    if(status) {
        // Additional info header
        SBinPvsProcessorHeader pvsH;
        pvsH.numLeafs = pPvsProc->getNumLeafs();
        pvsH.numPvs = pPvsProc->getNumPvs();
        pvsH.numPortVs = numPortalsData; // repeat
        status = (fgBool)!!(this->write(&pvsH, sizeof (pvsH), 1));
    }
    if(status && pPvsProc->getNumPvs() && pPvsProc->getPvs()) {
        // now will write the unsigned chars of the pvs
        status = (fgBool)!!(this->write(pPvsProc->getPvs(),
                                        sizeof (unsigned char),
                                        pPvsProc->getNumPvs())
                            == (int)pPvsProc->getNumPvs());
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
            return status;
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
    pPvsProc->setNumLeafs(pvsProcHeader.numLeafs);
    //pPvsProc->m_numLeafs = pvsProcHeader.numLeafs;
    //pvsProcHeader.numPortVs;
    if(status) {
        unsigned char *pvsVec = new unsigned char[pvsProcHeader.numPvs];
        if(!pvsVec)
            return FG_FALSE;

        // now will read the unsigned chars of the pvs
        status = (fgBool)!!(this->read(pvsVec,
                                       sizeof (unsigned char),
                                       pvsProcHeader.numPvs)
                            == (int)pvsProcHeader.numPvs);
        if(status)
            pPvsProc->setPvsArray(pvsVec, pvsProcHeader.numPvs);
    }
    CPvsProcessor::PPortalsDataVec& portalsData = pPvsProc->getPortalsData();
    if(status) {
        portalsData.reserve(pvsProcHeader.numPortVs);
        portalsData.resize(pvsProcHeader.numPortVs);
    }
    for(unsigned int i = 0; i < pvsProcHeader.numPortVs && status; i++) {
        portalsData[i] = NULL;
        int tmpSize;
        // will read PortalData info header
        SBinPortalDataInfoHeader portalDataH;
        // read the info header
        status = (fgBool)!!(this->read(&portalDataH,
                                       sizeof (portalDataH), 1));
        if(!status)
            break;
        SPortalData *portalData = new SPortalData(portalDataH.size);
        if(!portalData) {
            status = FG_FALSE;
            break;
        }
        portalData->possibleVisCount = portalDataH.possibleVisCount;
        unsigned char *bitBuffer = portalData->portArrPvs.buffer(tmpSize);
        if(!bitBuffer) {
            status = FG_FALSE;
            break;
        }
        // now can read the bit array storage (unsigned char)
        status = (fgBool)!!(this->read(bitBuffer,
                                       sizeof (unsigned char),
                                       portalDataH.sizeBitArray)
                            == (int)portalDataH.sizeBitArray);
        portalsData[i] = portalData;
    }
    return status;
}
//------------------------------------------------------------------------------
