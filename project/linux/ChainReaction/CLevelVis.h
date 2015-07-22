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
 * File:   CLevelVis.h
 * Author: vigilant
 *
 * Created on July 16, 2015, 2:13 PM
 */

#ifndef FG_INC_LEVEL_VIS
    #define FG_INC_LEVEL_VIS
    #define FG_INC_LEVEL_VIS_BLOCK

    #include "CLevelFile.h"
    #include "SQuadData.h"

    #include "fgVector.h"

    #include "Math/fgMathLib.h"

namespace fg {

    namespace gfx {
        class CSceneManager;
        class CSceneNode;
        class CSceneNodeMesh;
        struct SMaterial;
    }

    /**
     * 
     */
    class CLevelVis {
    public:
        typedef CLevelVis self_type;
        typedef CLevelVis type;

    public:
        typedef CVector<SBlockData*> BlockDataVec;
        typedef BlockDataVec::iterator BlockDataVecItor;

    public:
        /**
         *
         */
        CLevelVis(game::CGrid* pGrid = NULL, CLevelFile* pLvlFile = NULL);
        /**
         *
         * @param orig
         */
        CLevelVis(const CLevelVis& orig);
        /**
         *
         */
        virtual ~CLevelVis();

    protected:
        /**
         * 
         * @return 
         */
        fgBool prepareBlocks(void);

    public:
        /**
         *
         * @param x
         * @param y
         * @param color
         * @return
         */
        SBlockData* insertNewBlock(unsigned short x,
                                   unsigned short y,
                                   VColor color);

        /**
         *
         * @param x
         * @param y
         * @return
         */
        int destroyBlock(unsigned short x, unsigned short y);

        /**
         * This function will move the selected quad to the new position
         * If the target exists - it will be replaced
         * @param original
         * @param newX
         * @param newY
         * @return
         */
        SBlockData* moveBlockToNewPlace(SBlockData* original,
                                        unsigned short newX,
                                        unsigned short newY);

        /**
         * Creates the new scene node with proper size, scale, position and material.
         * The node is NOT being inserted into the scene manager.
         * @param x
         * @param y
         * @param color
         * @return
         */
        gfx::CSceneNode* prepareSceneNode(unsigned short x,
                                          unsigned short y,
                                          VColor color);
        /**
         *
         */
        fgBool restart(void);
        /**
         * 
         */
        inline fgBool setup(void) {
            return restart();
        }
        /**
         *
         */
        void clear(void);

    public:
        /**
         * 
         */
        void preRender(void);

        //----------------------------------------------------------------------
    public:
        /**
         *
         * @param x
         * @param y
         * @return
         */
        SBlockData* getBlockData(unsigned short x, unsigned short y);
        /**
         *
         * @param x
         * @param y
         * @return
         */
        int getBlockDataIndex(unsigned short x, unsigned short y);
        /**
         *
         * @param pLvlFile
         */
        void setLevelFile(CLevelFile* pLvlFile);
        /**
         *
         * @return
         */
        CLevelFile* getLevelFile(void) const {
            return m_pLevelFile;
        }
        /**
         * 
         * @param pSceneMgr
         */
        void setSceneManager(gfx::CSceneManager* pSceneMgr) {
            m_pSceneMgr = pSceneMgr;
        }
        /**
         *
         * @return
         */
        gfx::CSceneManager* getSceneManager(void) {
            return m_pSceneMgr;
        }
        /**
         *
         * @param pGrid
         */
        void setGrid(game::CGrid* pGrid) {
            m_pGrid = pGrid;
        }
        /**
         *
         * @return
         */
        game::CGrid* getGrid(void) const {
            return m_pGrid;
        }
        /**
         * 
         * @param scale
         */
        void setScale(float scale) {
            if(scale < 0.0f)
                scale = 1.0f;
            m_scale = scale;
        }
        /**
         *
         * @param x
         * @param y
         */
        float getScale(void) const {
            return m_scale;
        }
        /**
         * 
         * @param speed
         */
        void setSpeed(float speed) {
            if(speed < 0.0f)
                speed = 1.0f;
            if(speed > 10.0f)
                speed = 10.0f;
            m_speed = speed;
        }
        /**
         *
         * @param x
         * @param y
         */
        float getSpeed(void) const {
            return m_speed;
        }

        /**
         *
         * @param x
         * @param y
         */
        void getSize(unsigned short& x, unsigned short& y);
        /**
         *
         * @param x
         * @param y
         */
        void getSize(unsigned short* x, unsigned short* y);
        /**
         * 
         * @param pMaterial
         * @param color
         */
        void setMaterial(gfx::SMaterial* pMaterial, VColor color) {
            unsigned int index = (unsigned int)color;
            if(index >= (unsigned int)VColor::NUM_COLORS)
                return;
            m_pMaterials[index] = pMaterial;
        }
        /**
         * 
         * @param color
         * @return 
         */
        gfx::SMaterial* getMaterial(VColor color = VColor::BLACK) {
            unsigned int index = (unsigned int)color;
            if(index >= (unsigned int)VColor::NUM_COLORS)
                return NULL;
            return m_pMaterials[index];
        }
        /**
         * 
         * @param pMaterialBlack
         */
        void setMaterialBlack(gfx::SMaterial* pMaterialBlack) {
            m_pMaterial.black = pMaterialBlack;
        }
        /**
         *
         * @return
         */
        gfx::SMaterial* getMaterialBlack(void) const {
            return m_pMaterial.black;
        }
        /**
         *
         * @param pMaterialWhite
         */
        void setMaterialWhite(gfx::SMaterial* pMaterialWhite) {
            m_pMaterial.white = pMaterialWhite;
        }
        /**
         *
         * @return
         */
        gfx::SMaterial* getMaterialWhite(void) const {
            return m_pMaterial.white;
        }
        /**
         *
         * @param position
         */
        void setDraggedCoord(const Vec2i& coord) {
            m_draggedCoord = coord;
        }
        /**
         *
         * @param x
         * @param y
         */
        void setDraggedCoord(int x, int y) {
            m_draggedCoord.x = x;
            m_draggedCoord.y = y;
        }
        /**
         *
         * @return
         */
        Vector2i& getDraggedCoord(void) {
            return m_draggedCoord;
        }
        /**
         *
         * @return
         */
        Vector2i const& getDraggedCoord(void) const {
            return m_draggedCoord;
        }
        /**
         *
         * @param pGrabbedNode
         */
        void setDraggedNode(gfx::CSceneNode* pDraggedNode) {
            m_pDraggedNode = pDraggedNode;
        }
        /**
         *
         * @return
         */
        gfx::CSceneNode* getDraggedNode(void) const {
            return m_pDraggedNode;
        }
        //----------------------------------------------------------------------
    public:

        /**
         *
         * @param pQuadData
         */
        void setUserDisturbance(SBlockData* pBlockData);
        /**
         *
         * @param toggle
         */
        void setChainReaction(fgBool toggle = FG_TRUE) {
            m_isChainReaction = toggle;
        }
        /**
         *
         * @return
         */
        fgBool isChainReaction(void) const {
            return m_isChainReaction;
        }
        /**
         * 
         * @param toggle
         */
        void setStepping(fgBool toggle = FG_TRUE) {
            m_isStepping = toggle;
            if(!toggle)
                m_isStepOn = FG_FALSE;
        }
        /**
         *
         * @return
         */
        fgBool isStepping(void) const {
            return m_isStepping;
        }
        /**
         *
         * @param toggle
         */
        void setStepOn(fgBool toggle = FG_TRUE) {
            m_isStepOn = toggle;
        }
        /**
         *
         * @return
         */
        fgBool isStepOn(void) const {
            return m_isStepOn;
        }
        /**
         *
         * @return
         */
        BlockDataVec& getFinishedBlocks(void) {
            return m_finishedBlocks;
        }
        /**
         *
         * @return
         */
        BlockDataVec const& getFinishedBlocks(void) const {
            return m_finishedBlocks;
        }
        /**
         *
         * @return
         */
        BlockDataVec& getRotatingBlocks(void) {
            return m_rotatingBlocks;
        }
        /**
         * 
         * @return
         */
        BlockDataVec const& getRotatingBlocks(void) const {
            return m_rotatingBlocks;
        }
        /**
         *
         * @return
         */
        BlockDataVec& getOrphanBlocks(void) {
            return m_orphanBlocks;
        }
        /**
         * 
         * @return
         */
        BlockDataVec const& getOrphanBlocks(void) const {
            return m_orphanBlocks;
        }
        /**
         *
         * @return
         */
        fgBool areAllReactionVectorsEmpty(void) const {
            return (fgBool)(m_finishedBlocks.empty() &&
                    m_rotatingBlocks.empty() &&
                    m_orphanBlocks.empty() &&
                    m_additionalBlocks.empty() &&
                    m_emergeBlocks.empty() &&
                    m_duplicates.empty());
        }

        //----------------------------------------------------------------------
    private:
        typedef CVector<CLevelFile::SBlockInfo> BlockInfoVec;
        typedef BlockInfoVec::iterator BlockInfoVecItor;
        typedef CLevelFile::SBlockInfo BlockInfo;

        typedef CVector<Vector2i> DuplicateInfoVec;
        typedef DuplicateInfoVec::iterator DuplicateInfoVecItor;

        /**
         *
         */
        struct SCoverInfo {
            /// X grid coordinate
            unsigned short x;
            /// Y grid coordinate
            unsigned short y;
            /// by which color this position was covered
            VColor color;
            /// the covering quad was rotating in this direction
            RotationDirection direction;
            /**
             *
             */
            SCoverInfo() : x(0), y(0),
            color(VColor::INVALID_COLOR), direction(RotationDirection::NO_ROTATION) { }
            /**
             *
             * @param _x
             * @param _y
             */
            SCoverInfo(unsigned short _x, unsigned short _y) : x(_x), y(_y),
            color(VColor::INVALID_COLOR), direction(RotationDirection::NO_ROTATION) { }
            /**
             *
             * @param _x
             * @param _y
             * @param _color
             */
            SCoverInfo(unsigned short _x,
                       unsigned short _y,
                       VColor _color) : x(_x), y(_y), color(_color),
            direction(RotationDirection::NO_ROTATION) { }
            /**
             *
             * @param _x
             * @param _y
             * @param _color
             * @param _direction
             */
            SCoverInfo(unsigned short _x,
                       unsigned short _y,
                       VColor _color,
                       RotationDirection _direction) : x(_x), y(_y), color(_color),
            direction(_direction) { }
            /**
             *
             */
            virtual ~SCoverInfo() {
                zero();
            }
            /**
             *
             */
            void zero(void) {
                x = 0;
                y = 0;
                color = VColor::INVALID_COLOR;
                direction = RotationDirection::NO_ROTATION;
            }
            /**
             * 
             */
            inline void clear(void) {
                zero();
            }
            /**
             * 
             * @return 
             */
            fgBool isValid(void) const {
                if(color == VColor::INVALID_COLOR)
                    return FG_FALSE;
                if(direction == RotationDirection::NO_ROTATION ||
                        direction == RotationDirection::OPPOSITE_ROTATION ||
                        direction == RotationDirection::AUTO_ROTATION)
                    return FG_FALSE;

                return FG_TRUE;
            }
            /**
             *
             * @param other
             * @return
             */
            inline bool operator ==(const SCoverInfo& other) const {
                bool result = (this->x == other.x);
                result = (result && this->y == other.y);
                result = (result && this->color == other.color);
                return (result && this->direction == other.direction);
            }
        }; // struct SCoverInfo

        typedef CVector<SCoverInfo> CoverInfoVec;
        typedef CoverInfoVec::iterator CoverInfoVecItor;

        /**
         *
         */
        struct SNeighbourInfo {
            ///
            SBlockData* ptr;
            ///
            RotationDirection direction;
            /**
             *
             */
            SNeighbourInfo() : ptr(NULL), direction(NO_ROTATION) { }
            /**
             *
             * @param _ptr
             * @param _direction
             */
            SNeighbourInfo(SBlockData* _ptr,
                           RotationDirection _direction = NO_ROTATION) :
            ptr(_ptr), direction(_direction) { }
            /**
             *
             */
            ~SNeighbourInfo() {
                clear();
            }
            /**
             *
             */
            void clear(void) {
                ptr = NULL;
                direction = NO_ROTATION;
            }
            /**
             * 
             * @return 
             */
            fgBool isValid(void) const {
                fgBool status = (fgBool)!!(ptr != NULL);
                status = (fgBool)!!(status && direction != NO_ROTATION);
                status = (fgBool)!!(status && direction != AUTO_ROTATION);
                status = (fgBool)!!(status && direction != OPPOSITE_ROTATION);
                return status;
            }
            /**
             *
             * @param other
             * @return
             */
            inline bool operator ==(const SNeighbourInfo& other) const {
                return (bool)(this->ptr == other.ptr && this->direction == other.direction);
            }
        }; // SNeighbourInfo

        typedef CVector<SNeighbourInfo> NeighbourInfoVec;
        typedef NeighbourInfoVec::iterator NeighbourInfoVecItor;

    private:
        /**
         * 
         * @param blockType
         * @param x
         * @param y
         * @param newX
         * @param newY
         */
        static void getCoveringCoord(SBlockData::BlockType blockType,
                                     RotationDirection direction,
                                     unsigned int x, unsigned int y,
                                     unsigned short& newX, unsigned short& newY);
    public:
        /**
         * 
         * @param levelType
         * @return
         */
        static SBlockData::BlockType getBlockTypeFromLevelType(CLevelFile::LevelType levelType) {
            if(levelType == CLevelFile::LEVEL_QUADS)
                return SBlockData::BlockType::QUAD;
            if(levelType == CLevelFile::LEVEL_HEXAGONS)
                return SBlockData::BlockType::HEXAGON;
            return SBlockData::BlockType::INVALID_BLOCK;
        }

    private:
        /// Pointer to the main game grid 
        game::CGrid* m_pGrid;
        /// Pointer to the level file containing positions and colors of the quads
        CLevelFile* m_pLevelFile;
        /// Pointer to the external Scene Manager
        gfx::CSceneManager* m_pSceneMgr;
        /// Pointer to the node that is selected and dragged (main animation)
        gfx::CSceneNode* m_pDraggedNode;

        union {

            /**
             *
             */
            struct {
                ///
                gfx::SMaterial* none; // 0
                /// External pointer to the black material (designed for black quads)
                gfx::SMaterial* black; // 1
                /// External pointer to the white material
                gfx::SMaterial* white; // 2
                /// External pointer to the gray material
                gfx::SMaterial* gray; // 3
                ///
                gfx::SMaterial* red; // 4
                ///
                gfx::SMaterial* green; // 5
                ///
                gfx::SMaterial* blue; // 6
				///
                gfx::SMaterial* cyan; // 7
				///
                gfx::SMaterial* yellow; // 8
				///
                gfx::SMaterial* magenta; // 9
            } m_pMaterial;
            gfx::SMaterial* m_pMaterials[VColor::NUM_COLORS];
        };
        /// Quads info/data special vector - stores all required information
        BlockDataVec m_blocksData;
        /// Stores all quads that finished rotating (cover any neighbour)
        /// Need to check if those quads cause any rule breaking (disturbance)
        BlockDataVec m_finishedBlocks;
        /// Stores all quads that are currently being rotated
        BlockDataVec m_rotatingBlocks;
        /// Stores all quads that are orphaned (have no neighbours)
        /// These are scaled down gradually (then removed)
        BlockDataVec m_orphanBlocks;
        /// Stores info on quads that need to be added later
        BlockInfoVec m_additionalBlocks;
        /// Stores all quads that need to be animated as emerging (scaling up)
        BlockDataVec m_emergeBlocks;
        /// Stores positions where more than one quad rotated into
        DuplicateInfoVec m_duplicates;
        /// Stores positions and other info (like color & direction) of covered quads
        CoverInfoVec m_coveredBlocks;
        /// Scale (size) of a single quad object
        float m_scale;
        /// Animation speed (1.0f - 100%/normal)
        float m_speed;
        /// Position on the game grid of the dragged (grabbed) quad (main action)
        Vector2i m_draggedCoord;
        /// Special flag - if TRUE the chain reaction begun and quads are rotating
        fgBool m_isChainReaction;
        /// Special flag - chain reaction will perform one rotation per step
        fgBool m_isStepping;
        /// Should perform one step now? - this will be set to false automatically
        fgBool m_isStepOn;
    }; // class CLevelVis

} // namespace fg

    #undef FG_INC_LEVEL_VIS_BLOCK
#endif	/* FG_INC_LEVEL_VIS */
