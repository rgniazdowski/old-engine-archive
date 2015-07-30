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
 * File:   CLevelSolver.h
 * Author: vigilant
 *
 * Created on July 23, 2015, 8:27 AM
 */

#ifndef FG_INC_LEVEL_SOLVER
    #define FG_INC_LEVEL_SOLVER
    #define FG_INC_LEVEL_SOLVER_BLOCK

    #include "CLevelDataHolder.h"
    #include "Math/fgMathLib.h"

namespace fg {

    /**
     *
     */
    class CLevelSolver {
    public:
        typedef CLevelSolver self_type;
        typedef CLevelSolver type;

    public:
        typedef CLevelDataHolder::BlockDataVec BlockDataVec;
        typedef BlockDataVec::iterator BlockDataVecItor;

        /**
         *
         */
        enum StateFlags {
            /// No internal flags activated
            NO_FLAGS = 0x0000,
            /// Special flag - if TRUE the chain reaction begun and blocks are rotating
            CHAIN_REACTION = 0x0001,
            /// Special flag - chain reaction will perform one rotation wave per step
            STEPPING = 0x0002,
            /// Should perform one step now? - this will be set to false automatically
            STEP_ON = 0x0004,
            /// Is level solver currently simulating? This is used to find solution
            /// by using brute-force algorithm (without visuals and with instant chain-reaction)
            SIMULATION = 0x0008,
            ///
            INSTANT_BALANCE = 0x0010
        };

    public:
        /**
         *
         */
        CLevelSolver(CLevelDataHolder* pLevelDataHolder = NULL);
        /**
         *
         * @param orig
         */
        CLevelSolver(const CLevelSolver& orig);
        /**
         * 
         */
        virtual ~CLevelSolver();

    public:
        /**
         *
         */
        void update(float elapsed = 1.0f);
        /**
         * 
         */
        inline void balance(float elapsed = 1.0f) {
            update(elapsed);
        }
        /**
         * 
         * @return
         */
        fgBool solve(void) {
            return FG_FALSE;
        }

        /**
         *
         */
        void clear(void);

    public:
        /**
         * 
         * @param flags
         * @param toggle
         */
        void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
        /**
         *
         * @param scale
         */
        void setScale(float scale) {
            m_scale = scale;
        }
        /**
         * 
         * @return 
         */
        float getScale(void) const {
            return m_scale;
        }
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
            setFlag(CHAIN_REACTION, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isChainReaction(void) const {
            return (fgBool)!!(m_stateFlags & CHAIN_REACTION);
        }
        /**
         * 
         * @param toggle
         */
        void setStepping(fgBool toggle = FG_TRUE) {
            setFlag(STEPPING, toggle);
            if(!toggle)
                setFlag(STEP_ON, FG_FALSE);
        }
        /**
         *
         * @return
         */
        fgBool isStepping(void) const {
            return (fgBool)!!(m_stateFlags & STEPPING);
        }
        /**
         *
         * @param toggle
         */
        void setStepOn(fgBool toggle = FG_TRUE) {
            setFlag(STEP_ON, toggle);
        }
        /**
         *
         * @return
         */
        fgBool isStepOn(void) const {
            return (fgBool)!!(m_stateFlags & STEP_ON);
        }
        /**
         *
         * @param toggle
         */
        void setSimulation(fgBool toggle = FG_TRUE) {
            setFlag(SIMULATION, toggle);
        }
        /**
         * 
         * @return 
         */
        fgBool isSimulation(void) const {
            return (fgBool)!!(m_stateFlags & INSTANT_BALANCE);
        }
        /**
         * 
         * @param toggle
         */
        void setInstantBalance(fgBool toggle = FG_TRUE) {
            setFlag(INSTANT_BALANCE, toggle);
        }
        /**
         * 
         * @return
         */
        fgBool isInstantBalance(void) const {
            return (fgBool)!!(m_stateFlags & INSTANT_BALANCE);
        }
        /**
         * 
         * @param pDataHolder
         */
        void setLevelDataHolder(CLevelDataHolder* pDataHolder) {
            this->clear();
            m_pLevelData = pDataHolder;
        }
        /**
         * 
         * @return
         */
        CLevelDataHolder* getLevelDataHolder(void) const {
            return m_pLevelData;
        }
        /**
         *
         * @return
         */
        CLevelFile* getLevelFile(void) const {
            if(!m_pLevelData)
                return NULL;
            return m_pLevelData->getLevelFile();
        }
        /**
         * 
         * @return
         */
        LevelType getLevelType(void) const {
            if(!m_pLevelData)
                return LevelType::LEVEL_INVALID;
            return m_pLevelData->getLevelType();
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

        /**
         *
         * @param blockType
         * @param x
         * @param y
         * @param newX
         * @param newY
         */
        static void getCoveringCoord(BlockType blockType,
                                     RotationDirection direction,
                                     unsigned int x, unsigned int y,
                                     unsigned short& newX, unsigned short& newY);

        //----------------------------------------------------------------------
    private:
        typedef SBlockInfo BlockInfo;

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

        typedef CVector<SNeighbourInfo> NeighbourInfoVec;
        typedef NeighbourInfoVec::iterator NeighbourInfoVecItor;

    private:
        ///
        CLevelDataHolder* m_pLevelData;
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
        ///
        StateFlags m_stateFlags;
        ///
        float m_scale;
    }; // class CLevelSolver

    FG_ENUM_FLAGS(CLevelSolver::StateFlags);
    /**
     *
     * @param flags
     * @param toggle
     */
    inline void CLevelSolver::setFlag(const StateFlags flags, const fgBool toggle) {
        if(toggle) {
            m_stateFlags |= flags;
        } else {
            m_stateFlags |= flags;
            m_stateFlags ^= flags;
        }
    }

} // namespace fg

    #undef FG_INC_LEVEL_SOLVER_BLOCK
#endif	/* FG_INC_LEVEL_SOLVER */
