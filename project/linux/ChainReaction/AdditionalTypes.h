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
 * File:   AdditionalTypes.h
 * Author: vigilant
 *
 * Created on July 22, 2015, 3:33 PM
 */

#ifndef FG_INC_ADDITIONAL_TYPES
    #define FG_INC_ADDITIONAL_TYPES
    #define FG_INC_ADDITIONAL_TYPES_BLOCK

    #include "fgBool.h"
    #include "fgVector.h"    

namespace fg {

    /**
     *
     */
    enum RotationDirection {
        /// The block does not rotate (it's static)
        NO_ROTATION = 0,
        /// The block is rotating left (-x)
        LEFT = 1,
        /// The block is rotating right(+x)
        RIGHT = 2,
        /// The block is rotating up (-y)
        UP = 3,
        /// The block is rotating down (+y)
        DOWN = 4,
        /// The block is rotating up and left (-x-y)
        UP_LEFT = 5,
        /// The block is rotating up and right (+x-y)
        UP_RIGHT = 6,
        /// The block is rotating down and left (-x+y)
        DOWN_LEFT = 7,
        /// The block is rotating down and right (+x+y)
        DOWN_RIGHT = 8,
        /// Automatic rotation (detect)
        AUTO_ROTATION = 9,
        /// Opposite rotation
        OPPOSITE_ROTATION = 10
    };

    /**
     *
     */
    enum VColor : unsigned int {
        /// No color, empty block/cell
        INVALID_COLOR = 0,
        /// Black color
        BLACK = 1,
        /// White color
        WHITE = 2,
        /// Gray color
        GRAY = 3,
        ///
        RED = 4,
        ///
        GREEN = 5,
        ///
        BLUE = 6,
        ///
        CYAN = 7,
        ///
        MAGENTA = 8,
        ///
        YELLOW = 9,
        ///
        NUM_COLORS = 10
    };
    /**
     * 
     * @param color
     * @return
     */
    inline const char* getColorName(VColor color) {
        const char* returnValue = "invalid";
        switch(color) {
            case BLACK:
                returnValue = "black";
                break;
            case WHITE:
                returnValue = "white";
                break;
            case GRAY:
                returnValue = "gray";
                break;
            case RED:
                returnValue = "red";
                break;
            case GREEN:
                returnValue = "green";
                break;
            case BLUE:
                returnValue = "blue";
                break;
            case CYAN:
                returnValue = "cyan";
                break;
            case MAGENTA:
                returnValue = "magenta";
                break;
            case YELLOW:
                returnValue = "yellow";
                break;
        };
        return returnValue;
    }
    /**
     * 
     * @param rotation
     * @return
     */
    inline const char* getRotationName(RotationDirection rotation) {
        const char* returnValue = "invalid";
        switch(rotation) {
            case NO_ROTATION:
                returnValue = "no rotation";
                break;
            case LEFT:
                returnValue = "left";
                break;
            case RIGHT:
                returnValue = "right";
                break;
            case UP:
                returnValue = "up";
                break;
            case DOWN:
                returnValue = "down";
                break;
            case UP_LEFT:
                returnValue = "up-left";
                break;
            case UP_RIGHT:
                returnValue = "up-right";
                break;
            case DOWN_LEFT:
                returnValue = "down-left";
                break;
            case DOWN_RIGHT:
                returnValue = "down-right";
                break;
            case AUTO_ROTATION:
                returnValue = "auto";
                break;
            case OPPOSITE_ROTATION:
                returnValue = "opposite";
                break;
        };
        return returnValue;
    }

    struct SBlockData;

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
        virtual ~SNeighbourInfo() {
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
    typedef NeighbourInfoVec::const_iterator NeighbourInfoVecConstItor;

    /**
     *
     */
    struct SSize {
        ///
        unsigned short x;
        ///
        unsigned short y;
        /**
         *
         * @param _x
         * @param _y
         */
        SSize(unsigned short _x = 0, unsigned short _y = 0) : x(_x), y(_y) { }
        /**
         *
         * @param other
         */
        SSize(const SSize& other) {
            this->x = other.x;
            this->y = other.y;
        }
        /**
         *
         */
        virtual ~SSize() {
            zero();
        }
        /**
         *
         */
        void zero(void) {
            this->x = 0;
            this->y = 0;
        }
        /**
         * 
         * @param other
         * @return
         */
        SSize& operator =(const SSize& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }
        /**
         *
         * @param other
         * @return
         */
        inline bool operator ==(const SSize& other) const {
            return ((this->x == other.x) &&
                    (this->y == other.y));
        }
    }; // struct SSize

    typedef SSize SPosition;

    /**
     *
     */
    enum BlockType {
        BLOCK_QUAD = 0,
        BLOCK_HEXAGON = 1,
        BLOCK_OCTAGON = 2,
        NUM_BLOCK_TYPES = 3,
        BLOCK_INVALID = 100
    };

    /**
     *
     */
    enum LevelType {
        LEVEL_QUADS = 0,
        LEVEL_HEXAGONS = 1,
        LEVEL_OCTAGONS = 2,
        NUM_LEVEL_TYPES = 3,
        LEVEL_INVALID = 100,
    };

    /**
     *
     */
    struct SBlockInfo {
        ///
        VColor color;

        /**
         *
         */
        SPosition pos;
        /**
         *
         */
        SBlockInfo() : color(VColor::INVALID_COLOR) {
            pos.x = 0;
            pos.y = 0;
        }
        /**
         * 
         * @param x
         * @param y
         */
        SBlockInfo(unsigned short x, unsigned short y) : color(VColor::INVALID_COLOR) {
            pos.x = x;
            pos.y = y;
        }
        /**
         * 
         * @param _x
         * @param _y
         * @param _color
         */
        SBlockInfo(unsigned short _x,
                   unsigned short _y,
                   VColor _color) :
        color(_color) {
            pos.x = _x;
            pos.y = _y;
        }
        /**
         *
         */
        void zero(void) {
            color = VColor::INVALID_COLOR;
            pos.x = 0;
            pos.y = 0;
        }
        /**
         *
         * @param other
         * @return
         */
        inline bool operator ==(const SBlockInfo& other) const {
            return ((this->color == other.color) &&
                    (this->pos.x == other.pos.x) &&
                    (this->pos.y == other.pos.y));
        }
    }; // struct SBlockInfo

    ///
    typedef CVector<SBlockInfo> BlockInfoVec;
    ///
    typedef BlockInfoVec::iterator BlockInfoVecItor;
    ///
    typedef BlockInfoVec::const_iterator BlockInfoVecConstItor;

    struct SBlockData;

    /**
     *
     */
    struct SBlockMoveInfo {
        typedef SBlockMoveInfo self_type;
        typedef SBlockMoveInfo type;

        ///
        SPosition pos;
        ///
        SPosition target;
        ///
        RotationDirection moveDir;
        ///
        BlockType blockType;
        ///
        SBlockData *pData;
        /**
         * 
         * @param _blockType
         */
        SBlockMoveInfo(BlockType _blockType = BlockType::BLOCK_QUAD);

        /**
         *
         * @param _position
         * @param _moveDir
         * @param _blockType
         */
        SBlockMoveInfo(SPosition _position,
                       RotationDirection _moveDir,
                       BlockType _blockType = BlockType::BLOCK_QUAD);
        /**
         *
         */
        virtual ~SBlockMoveInfo();
        /**
         * 
         * @return
         */
        inline self_type* self(void) {
            return this;
        }

        /**
         *
         */
        virtual void clear(void);
        /**
         *
         * @param _moveDir
         */
        inline void reset(void) {
            this->clear();
        }
        /**
         *
         * @param _moveDir
         */
        void setDirection(RotationDirection _moveDir);
        /**
         *
         * @return
         */
        virtual fgBool isValid(void) const;
    }; // struct SBlockMoveInfo

    /**
     *
     */
    struct SBlockMoveStep : public SBlockMoveInfo {
    public:
        typedef SBlockMoveInfo base_type;
        typedef SBlockMoveStep self_type;
        typedef SBlockMoveStep type;
        typedef CVector<self_type*> internal_vector;
        typedef internal_vector StepsVec;
        typedef StepsVec::iterator StepsVecItor;
        typedef StepsVec::const_iterator StepsVecConstItor;
        typedef StepsVec::iterator Iterator;
        typedef StepsVec::value_type ElementType;
        typedef StepsVec::value_type ValueType;

        ///
        unsigned int moveIdx;
        ///
        unsigned int moveDepth;
        ///
        StepsVec steps;
        ///
        BlockInfoVec levelState;

    private:
        ///
        Iterator currentStep;

    public:

        /**
         * 
         * @param _blockType
         */
        SBlockMoveStep(BlockType _blockType = BlockType::BLOCK_QUAD);
        /**
         *
         * @param _position
         * @param _moveDir
         * @param _blockType
         */
        SBlockMoveStep(SPosition _position,
                       RotationDirection _moveDir,
                       BlockType _blockType = BlockType::BLOCK_QUAD);
        /**
         *
         */
        virtual ~SBlockMoveStep();
        /**
         * 
         * @return
         */
        fgBool isRoot(void) const {
            return (fgBool)!!(moveIdx == 0 && moveDepth == 0 && moveDir == NO_ROTATION);
        }
        /**
         *
         */
        void prepareAsRoot(void) {
            this->moveIdx = 0;
            this->moveDepth = 0;
            this->moveDir = NO_ROTATION;
            this->pData = NULL;
            this->pos.zero();
            this->target.zero();
        }
        /**
         * 
         * @param index
         * @return 
         */
        inline self_type* at(unsigned int index) {
            if(index >= this->count())
                return NULL;
            return this->steps[index];
        }
        /**
         * 
         * @param index
         * @return 
         */
        inline self_type const* at(unsigned int index) const {
            if(index >= this->count())
                return NULL;
            return this->steps[index];
        }
        /**
         *
         * @param index
         * @return
         */
        inline self_type*& operator [](unsigned int index) {
            return this->steps[index];
        }
        /**
         *
         * @param index
         * @return
         */
        inline self_type * const& operator [](unsigned int index)const {
            return this->steps[index];
        }
        /**
         * 
         * @return
         */
        inline self_type* self(void) {
            return this;
        }
        /**
         * 
         * @return
         */
        inline self_type& selfRef(void) {
            return (*this);
        }
        /**
         * 
         * @return 
         */
        inline self_type const& selfRef(void) const {
            return (*this);
        }

        /**
         *
         */
        virtual void clear(void);

        /**
         * 
         */
        void clearSteps(void);

        /**
         * 
         * @return
         */
        void rewind(void);
        /**
         *
         * @return
         */
        self_type* next(fgBool shouldClearPrevious = FG_FALSE);
        /**
         *
         * @return
         */
        self_type& nextRef(void);
        /**
         *
         * @return
         */
        self_type* current(void);
        /**
         * 
         * @return 
         */
        self_type& currentRef(void);
        /**
         *
         * @return
         */
        self_type const& currentRef(void) const;
        /**
         *
         * @return
         */
        fgBool isItorValid(void) const;
        /**
         * 
         * @return 
         */
        virtual fgBool isValid(void) const;
        /**
         *
         * @param _position
         * @param direction
         * @return
         */
        int addStep(SPosition _position, RotationDirection _moveDir);
        /**
         *
         * @return
         */
        inline unsigned int count(void) const {
            return (unsigned int)steps.size();
        }
        /**
         * 
         * @return 
         */
        fgBool isEmpty(void) const {
            return (fgBool)steps.empty();
        }

    #if defined(DEBUG)
        void dump(void);
    #endif
    }; // struct SBlockMoveStep

} // namespace fg

    #undef FG_INC_ADDITIONAL_TYPES_BLOCK
#endif	/* FG_INC_ADDITIONAL_TYPES */
