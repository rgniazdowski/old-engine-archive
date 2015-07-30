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
 * File:   CLevelDataHolder.h
 * Author: vigilant
 *
 * Created on July 23, 2015, 8:47 AM
 */

#ifndef FG_INC_LEVEL_DATA_HOLDER
    #define FG_INC_LEVEL_DATA_HOLDER
    #define FG_INC_LEVEL_DATA_HOLDER_BLOCK

    #include "GameLogic/fgGrid.h"
    #include "CLevelFile.h"
    #include "SBlockData.h"

    #include "fgVector.h"    
    #include "Event/fgCallback.h"

namespace fg {

    /**
     *
     */
    class CLevelDataHolder {
    public:
        typedef CLevelDataHolder self_type;
        typedef CLevelDataHolder type;

    public:
        typedef CVector<SBlockData*> BlockDataVec;
        typedef BlockDataVec::iterator BlockDataVecItor;
        typedef BlockDataVec::const_iterator BlockDataVecConstItor;
        // System data is always set to SActionInfo
        typedef fgBool(*CallbackFuncPtr)(void* systemData, void* userData);
        ///
        typedef CallbackFuncPtr callback_type;

        static const unsigned short NUM_ACTIONS = 5;

        /**
         *
         */
        enum InternalActionType {
            ///
            ACTION_BLOCK_ADDED = 0,
            ///
            ACTION_BLOCK_MOVED = 1,
            ///
            ACTION_BLOCK_DESTROYED = 2,
            ///
            ACTION_GRID_CLEARED = 3,
            ///
            ACTION_LEVEL_DATA_DESTROYED = 4,
            ///
            ACTION_INVALID = 5,
        };

        /**
         *
         */
        struct SActionInfo {
            ///
            InternalActionType actionType;
            ///
            SBlockData* pOriginal;
            ///
            SBlockData* pNew;
            /**
             *
             */
            SActionInfo() : actionType(ACTION_INVALID), pOriginal(NULL), pNew(NULL) { }
            /**
             *
             * @param _actionType
             */
            SActionInfo(InternalActionType _actionType) :
            actionType(_actionType), pOriginal(NULL), pNew(NULL) { }
            /**
             *
             */
            ~SActionInfo() {
                clear();
                actionType = ACTION_INVALID;
            }
            void clear(void) {
                pNew = NULL;
                pOriginal = NULL;
            }
        };

    public:
        /**
         *
         * @param pGrid
         * @param pLvlFile
         */
        CLevelDataHolder(game::CGrid* pGrid = NULL, CLevelFile* pLvlFile = NULL);
        /**
         *
         * @param orig
         */
        CLevelDataHolder(const CLevelDataHolder& orig);
        /**
         * 
         */
        virtual ~CLevelDataHolder();

    public:
        /**
         *
         * @param actionType
         * @param pCallback
         * @param pUserData
         * @return
         */
        fgBool registerCallback(InternalActionType actionType,
                                CallbackFuncPtr pCallback,
                                void* pUserData = NULL);
        /**
         *
         * @param pCallback
         * @param actionType
         * @return
         */
        fgBool isRegistered(CallbackFuncPtr pCallback,
                            InternalActionType actionType = ACTION_INVALID);

        /**
         *
         * @param pCallback
         * @return
         */
        fgBool removeCallback(CallbackFuncPtr pCallback);

        /**
         *
         */
        void clearCallbacks(void);

    protected:
        /**
         * 
         * @param actionType
         * @param pOriginal
         * @param pNew
         * @return
         */
        fgBool internalCall(InternalActionType actionType,
                            SBlockData* pOriginal,
                            SBlockData* pNew = NULL);
        /**
         *
         * @return
         */
        fgBool prepareAllBlocks(void);
        /**
         *
         * @return
         */
        fgBool destroyAllBlocks(void);
        /**
         *
         * @return
         */
        SBlockData* requestBlockData(void);
        /**
         *
         * @param pBlock
         */
        void addToFree(SBlockData* pBlock);

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
         * @param index
         * @return 
         */
        int destroyBlock(unsigned int index);
        /**
         * 
         * @param pBlockData
         * @return 
         */
        int destroyBlock(SBlockData* pBlockData);
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
         * 
         */
        void clear(void);

        /**
         *
         * @return
         */
        fgBool restart(void);
        /**
         * 
         * @param blocks
         * @return 
         */
        fgBool restartFrom(const BlockInfoVec& blocks);
        /**
         *
         * @return
         */
        inline fgBool setup(void) {
            return restart();
        }

        /**
         * 
         * @param index
         * @return
         */
        SBlockData* at(unsigned int index);
        /**
         *
         * @return
         */
        fgBool isEmpty(void) const {
            return (fgBool)!!(m_blocksData.empty());
        }
        /**
         * 
         * @return 
         */
        unsigned int getMaximumBlocksCount(void);
        /**
         *
         * @return
         */
        BlockDataVec& getBlocks(void) {
            return m_blocksData;
        }
        /**
         *
         * @return
         */
        BlockDataVec const& getBlocks(void) const {
            return m_blocksData;
        }
        /**
         * 
         * @return 
         */
        unsigned int getBlocksCount(void) const {
            return m_blocksData.size();
        }
        /**
         * 
         * @param blockInfoVec
         * @return 
         */
        int appendTo(BlockInfoVec& blockInfoVec);

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
         * @return
         */
        LevelType getLevelType(void) const {
            if(!m_pLevelFile)
                return LevelType::LEVEL_INVALID;
            return m_pLevelFile->getLevelType();

        }
        /**
         * 
         * @return
         */
        BlockType getBlockType(void) const {
            if(m_pLevelFile) {
                return getBlockTypeFromLevelType(m_pLevelFile->getLevelType());
            } else if(m_blocksData.size()) {
                return m_blocksData[0]->getType();
            } else {
                return BlockType::BLOCK_INVALID;
            }
        }
        /**
         *
         * @return
         */
        int getLevelIndex(void) const {
            if(!m_pLevelFile)
                return -1;
            return m_pLevelFile->getLevelIndex();
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
    public:
        /**
         *
         * @param levelType
         * @return
         */
        static BlockType getBlockTypeFromLevelType(LevelType levelType) {
            if(levelType == LEVEL_QUADS)
                return BlockType::BLOCK_QUAD;
            if(levelType == LEVEL_HEXAGONS)
                return BlockType::BLOCK_HEXAGON;
            return BlockType::BLOCK_INVALID;
        }

    #if defined(DEBUG) || defined(FG_DEBUG)
        void dump(void);
        void dumpGrid(void);
    #endif
    
    private:

        /**
         *
         */
        struct SCallbackData {
            ///
            SActionInfo action;
            ///
            CallbackFuncPtr callback;
            ///
            void* userData;
            /**
             *
             */
            SCallbackData() : action(), userData(NULL), callback(NULL) { }
            /**
             *
             * @param pCallback
             * @param pUserData
             */
            SCallbackData(InternalActionType actionType, CallbackFuncPtr pCallback, void* pUserData) :
            action(),
            callback(pCallback),
            userData(pUserData) {
                action.actionType = actionType;
            }
            /**
             * 
             */
            ~SCallbackData() {
                clear();
            }
            /**
             * 
             * @return
             */
            fgBool call(void) {
                if(!callback)
                    return FG_FALSE;
                return callback((void*)&action, userData);
            }
            /**
             * 
             */
            void clear(void) {
                callback = NULL;
                userData = NULL;
                action.clear();
            }
        }; // struct SCallbackData

        typedef CVector<SCallbackData> CallbacksVec;
        typedef CallbacksVec::iterator CallbacksVecItor;

        ///
        CallbacksVec m_actionCallbacks[NUM_ACTIONS];

    private:
        /// Pointer to the main game grid
        game::CGrid* m_pGrid;
        /// Pointer to the level file containing positions and colors of the quads
        CLevelFile* m_pLevelFile;
        /// Quads info/data special vector - stores all required information
        BlockDataVec m_blocksData;
        /// This is allocated based on current level file
        BlockDataVec m_allBlocksData;
        ///
        CVector<int> m_freeSlots;
        ///
        fgBool m_isPrintMessages;
    }; // class CLevelDataHolder

} // namespace fg

    #undef FG_INC_LEVEL_DATA_HOLDER_BLOCK
#endif	/* FG_INC_LEVEL_DATA_HOLDER */
