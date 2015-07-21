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
        typedef CVector<SQuadData*> QuadDataVec;
        typedef QuadDataVec::iterator QuadDataVecItor;

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
        fgBool prepareQuads(void);

    public:
        /**
         *
         * @param x
         * @param y
         * @param color
         * @return
         */
        SQuadData* insertNewQuad(unsigned short x,
                                 unsigned short y,
                                 SQuadData::QuadColor color);

        /**
         *
         * @param x
         * @param y
         * @return
         */
        int destroyQuad(unsigned short x, unsigned short y);

        /**
         * This function will move the selected quad to the new position
         * If the target exists - it will be replaced
         * @param original
         * @param newX
         * @param newY
         * @return
         */
        SQuadData* moveQuadToNewPlace(SQuadData* original,
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
                                          SQuadData::QuadColor color);
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
        SQuadData* getQuadData(unsigned short x, unsigned short y);
        /**
         *
         * @param x
         * @param y
         * @return
         */
        int getQuadDataIndex(unsigned short x, unsigned short y);
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
         * @param pMaterialBlack
         */
        void setMaterialBlack(gfx::SMaterial* pMaterialBlack) {
            m_pMaterialBlack = pMaterialBlack;
        }
        /**
         *
         * @return
         */
        gfx::SMaterial* getMaterialBlack(void) const {
            return m_pMaterialBlack;
        }
        /**
         *
         * @param pMaterialWhite
         */
        void setMaterialWhite(gfx::SMaterial* pMaterialWhite) {
            m_pMaterialWhite = pMaterialWhite;
        }
        /**
         *
         * @return
         */
        gfx::SMaterial* getMaterialWhite(void) const {
            return m_pMaterialWhite;
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
        void setUserDisturbance(SQuadData* pQuadData);
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
        QuadDataVec& getFinishedQuads(void) {
            return m_finishedQuads;
        }
        /**
         *
         * @return
         */
        QuadDataVec const& getFinishedQuads(void) const {
            return m_finishedQuads;
        }
        /**
         *
         * @return
         */
        QuadDataVec& getRotatingQuads(void) {
            return m_rotatingQuads;
        }
        /**
         * 
         * @return
         */
        QuadDataVec const& getRotatingQuads(void) const {
            return m_rotatingQuads;
        }
        /**
         *
         * @return
         */
        QuadDataVec& getOrphanQuads(void) {
            return m_orphanQuads;
        }
        /**
         * 
         * @return
         */
        QuadDataVec const& getOrphanQuads(void) const {
            return m_orphanQuads;
        }
        /**
         *
         * @return
         */
        fgBool areAllReactionVectorsEmpty(void) const {
            return (fgBool)(m_finishedQuads.empty() &&
                    m_rotatingQuads.empty() &&
                    m_orphanQuads.empty() &&
                    m_additionalQuads.empty() &&
                    m_emergeQuads.empty() &&
                    m_duplicates.empty());
        }

        //----------------------------------------------------------------------
    private:
        typedef CVector<CLevelFile::SQuadInfo> QuadInfoVec;
        typedef QuadInfoVec::iterator QuadInfoVecItor;
        typedef CLevelFile::SQuadInfo QuadInfo;

        typedef CVector<Vector2i> DuplicateInfoVec;
        typedef DuplicateInfoVec::iterator DuplicateInfoVecItor;
        
        /**
         *
         */
        struct SCoverInfo {
            typedef SQuadData::QuadColor QuadColor;
            typedef SQuadData::RotationDirection RotationDirection;

            /// X grid coordinate
            unsigned short x;
            /// Y grid coordinate
            unsigned short y;
            /// by which color this position was covered
            QuadColor color;
            /// the covering quad was rotating in this direction
            RotationDirection direction;
            /**
             *
             */
            SCoverInfo() : x(0), y(0),
            color(QuadColor::EMPTY), direction(RotationDirection::STATIC) { }
            /**
             *
             * @param _x
             * @param _y
             */
            SCoverInfo(unsigned short _x, unsigned short _y) : x(_x), y(_y),
            color(QuadColor::EMPTY), direction(RotationDirection::STATIC) { }
            /**
             *
             * @param _x
             * @param _y
             * @param _color
             */
            SCoverInfo(unsigned short _x,
                       unsigned short _y,
                       QuadColor _color) : x(_x), y(_y), color(_color),
            direction(RotationDirection::STATIC) { }
            /**
             *
             * @param _x
             * @param _y
             * @param _color
             * @param _direction
             */
            SCoverInfo(unsigned short _x,
                       unsigned short _y,
                       QuadColor _color,
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
                color = QuadColor::EMPTY;
                direction = RotationDirection::STATIC;
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
                if(color == QuadColor::EMPTY)
                    return FG_FALSE;
                if(direction == RotationDirection::STATIC ||
                        direction == RotationDirection::OPPOSITE ||
                        direction == RotationDirection::AUTO)
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

    private:
        /// Pointer to the main game grid 
        game::CGrid* m_pGrid;
        /// Pointer to the level file containing positions and colors of the quads
        CLevelFile* m_pLevelFile;
        /// Pointer to the external Scene Manager
        gfx::CSceneManager* m_pSceneMgr;
        /// Pointer to the node that is selected and dragged (main animation)
        gfx::CSceneNode* m_pDraggedNode;
        /// External pointer to the black material (designed for black quads)
        gfx::SMaterial* m_pMaterialBlack;
        /// External pointer to the white material
        gfx::SMaterial* m_pMaterialWhite;
        /// Quads info/data special vector - stores all required information
        QuadDataVec m_quadsData;
        /// Stores all quads that finished rotating (cover any neighbour)
        /// Need to check if those quads cause any rule breaking (disturbance)
        QuadDataVec m_finishedQuads;
        /// Stores all quads that are currently being rotated
        QuadDataVec m_rotatingQuads;
        /// Stores all quads that are orphaned (have no neighbours)
        /// These are scaled down gradually (then removed)
        QuadDataVec m_orphanQuads;
        /// Stores info on quads that need to be added later
        QuadInfoVec m_additionalQuads;
        /// Stores all quads that need to be animated as emerging (scaling up)
        QuadDataVec m_emergeQuads;
        /// Stores positions where more than one quad rotated into
        DuplicateInfoVec m_duplicates;
        /// Stores positions and other info (like color & direction) of covered quads
        CoverInfoVec m_coveredQuads;
        /// Scale (size) of a single quad object
        float m_scale;
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
