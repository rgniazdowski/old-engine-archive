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
 * File:   fgGfxBspFile.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 7:22 PM
 */

#ifndef FG_GFX_BSP_FILE
    #define FG_GFX_BSP_FILE
    #define FG_GFX_BSP_FILE_BLOCK

    #include "fgBool.h"
    #include "Util/fgFile.h"
    #include "fgGfxBspTree.h"
    #include "fgGfxBspCompiler.h"

namespace fg {
    namespace gfx {

        struct SPolygon;
        class CBspTree;
        class CBspCompiler;
        class CPortalProcessor;
        class CPvsProcessor;

        /**
         *
         */
        class CBspFile : protected ::fg::util::CFile {
        public:
            typedef CBspFile self_type;
            typedef CBspFile type;
            typedef ::fg::util::CFile base_type;

        private:
            ///
            static const unsigned int CHAR_OFFSET = 96;

            /**
             *
             */
            struct SBinMainHeader {
                unsigned char tag[6];
                fgBool hasBsp;
                fgBool hasPortalProc;
                fgBool hasPvsProc;
                int bspType;
                int balance;
                int numNodes;
                int numLeafs;
                int numPolygons;
                int numPlanes;
                int numMaterials;
            };

            enum class ChunkType : unsigned char {
                INVALID = 0,
                NONE = 0,
                BSP_NODES,
                BSP_LEAFS,
                POLYGONS,
                PLANES,
                MATERIALS,
                PORTALS,
                BSP_PVS_PROC,
                PORTAL_DATA
            };

            struct SBinDataVecChunkHeader {
                ChunkType chunkType;
                /// Number of the elements ahead of the given type
                unsigned int numChunks;
            };

            struct SBinPolygonVertexDataHeader {
                /// Vertex2v/3v/4v - values 2 or 3 or 4 - default 4
                unsigned int vertexType;
                ///
                unsigned int vertexStride;
                /// Number of elements in CVertexData 
                unsigned int numVertices;
            };

            struct SBinPortalVecDataHeader {
                /// number of elements in Vector3f vector
                unsigned int numVertices;
                /// size of an int vector
                unsigned int numSideLIdx;
                /// size of an int vector
                unsigned int numSideLIdxFinal;
            };

            struct SBinPortalDataInfoHeader {
                unsigned int size;
                unsigned int possibleVisCount;
                // size of the bit array - next chunk with no name
                //-> raw bit array storage (unsigned chars)
                unsigned int sizeBitArray;
            };

            struct SBinPvsProcessorHeader {
                unsigned int numLeafs;
                /// number of elements in unsigned char array (dynamic)
                unsigned int numPvs;
                /// SBinPortalDataInfoHeader vector + overhead
                unsigned int numPortVs;
            };

            struct SBinMaterialInfoHeader {
                unsigned int nameLen;
                unsigned int shaderNameLen;
                unsigned int ambientTexNameLen;
                unsigned int diffuseTexNameLen;
                unsigned int specularTexNameLen;
                unsigned int normalTexNameLen;
            };

        public:
            /**
             *
             */
            CBspFile();
            /**
             *
             */
            virtual ~CBspFile();

        public:
            /**
             *
             * @param filePath
             */
            void setPath(const char *filePath) {
                if(!filePath)
                    return;
                base_type::setPath(filePath);
            }
            /**
             * 
             * @param filePath
             */
            void setPath(const std::string & filePath) {
                base_type::setPath(filePath);
            }
        public:
            /**
             * 
             * @param pBspTree
             * @return
             */
            fgBool save(const CBspTree* pBspTree, fgBool closeAfter = FG_TRUE);
            /**
             *
             * @param pBspTree
             * @return
             */
            fgBool load(CBspTree* pBspTree, fgBool closeAfter = FG_TRUE);

            /**
             *
             * @param pBspCompiler
             * @return
             */
            fgBool save(const CBspCompiler* pBspCompiler, fgBool closeAfter = FG_TRUE);
            /**
             *
             * @param pBspCompiler
             * @return
             */
            fgBool load(CBspCompiler* pBspCompiler, fgBool closeAfter = FG_TRUE);

        private:
            typedef CVector<SPolygon> PolygonsVec;
            typedef PolygonsVec::iterator PolygonsVecItor;

            /**
             *
             */
            void zeroHeader(void);
            /**
             *
             */
            void prepareTags(void);
            /**
             *
             * @return
             */
            fgBool checkTag(void);

            /**
             * Check whether or not the secondary binary file tag is for polygons
             * @return  FG_TRUE if the current tag is for polygons,
             *          FG_FALSE otherwise.
             */
            fgBool checkPolygonsTag(void);

            /**
             * 
             * @param output
             * @return
             */
            fgBool readPolygonsBinary(PolygonsVec& output);
            /**
             *
             * @param output
             * @return
             */
            fgBool readPolygonsText(PolygonsVec& output);

            /**
             *
             * @return
             */
            fgBool readPolygonsHelper(PolygonsVec& output);

            /**
             *
             * @param pBspTree
             * @return
             */
            fgBool writeBspTree(const CBspTree* pBspTree);
            /**
             *
             * @param pBspTree
             * @return
             */
            fgBool readBspTree(CBspTree* pBspTree);

            /**
             *
             * @param pPortalProc
             * @return
             */
            fgBool writePortalProcessor(const CPortalProcessor* pPortalProc);
            /**
             * 
             * @param pPortalProc
             * @return
             */
            fgBool readPortalProcessor(CPortalProcessor* pPortalProc);

            /**
             * 
             * @param pPvsProc
             * @return
             */
            fgBool writePvsProcessor(const CPvsProcessor* pPvsProc);
            /**
             *
             * @param pPvsProc
             * @return
             */
            fgBool readPvsProcessor(CPvsProcessor* pPvsProc);

        private:
            constexpr static const unsigned char FG_BINARY_TAG[9] = {
                                                           (unsigned char)('f' + CHAR_OFFSET),
                                                           (unsigned char)('g' + CHAR_OFFSET),
                                                           (unsigned char)('_' + CHAR_OFFSET),
                                                           (unsigned char)('b' + CHAR_OFFSET),
                                                           (unsigned char)('i' + CHAR_OFFSET),
                                                           (unsigned char)('n' + CHAR_OFFSET),
                                                           (unsigned char)('a' + CHAR_OFFSET),
                                                           (unsigned char)('r' + CHAR_OFFSET),
                                                           (unsigned char)('y' + CHAR_OFFSET)
            };
            ///
            SBinMainHeader m_mainHeader;
            /// fg_binary
            unsigned char m_bfTag[9];
            ///
            fgBool m_isBinary;
            ///
            fgBool m_isPolygonsText;

        };
    } // namespace gfx
} // namespace fg
    #undef FG_GFX_BSP_FILE_BLOCK
#endif	/* FGGFXBSPFILE_H */
