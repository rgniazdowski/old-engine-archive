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
 * File:   CLevelVisualization.h
 * Author: vigilant
 *
 * Created on July 16, 2015, 2:13 PM
 */

#ifndef FG_INC_LEVEL_VISUALIZATION
    #define FG_INC_LEVEL_VISUALIZATION
    #define FG_INC_LEVEL_VISUALIZATION_BLOCK

    #include "CLevelSolver.h"

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
    class CLevelVisualization {
    public:
        typedef CLevelVisualization self_type;
        typedef CLevelVisualization type;

    public:
        typedef CLevelFile::LevelType LevelType;
        typedef CLevelDataHolder::BlockDataVec BlockDataVec;
        typedef BlockDataVec::iterator BlockDataVecItor;

    public:
        /**
         *
         */
        CLevelVisualization(CLevelSolver* pLevelSolver);
        /**
         *
         * @param orig
         */
        CLevelVisualization(const CLevelVisualization& orig);
        /**
         *
         */
        virtual ~CLevelVisualization();

    protected:
        /**
         * 
         */
        void registerCallbacks(void);
        /**
         *
         */
        void unregisterCallbacks(void);

        static fgBool actionBlockAddedCallback(void* systemData, void* userData);
        static fgBool actionBlockMovedCallback(void* systemData, void* userData);
        static fgBool actionBlockDestroyedCallback(void* systemData, void* userData);
        static fgBool actionGridClearedCallback(void* systemData, void* userData);
        static fgBool actionLevelDataDestroyedCallback(void* systemData, void* userData);

    public:
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
         * @param pLevelSolver
         */
        void setLevelSolver(CLevelSolver* pLevelSolver);
        /**
         *
         * @return
         */
        CLevelSolver* getLevelSolver(void) const {
            return m_pLevelSolver;
        }
        /**
         * 
         * @return 
         */
        CLevelDataHolder* getLevelDataHolder(void) const {
            if(!m_pLevelSolver)
                return NULL;
            return m_pLevelSolver->getLevelDataHolder();
        }
        /**
         *
         * @return
         */
        CLevelFile* getLevelFile(void) const {
            if(!m_pLevelSolver)
                return NULL;
            return m_pLevelSolver->getLevelFile();
        }
        /**
         * 
         * @return
         */
        LevelType getLevelType(void) const {
            if(!m_pLevelSolver)
                return LevelType::INVALID_LEVEL;
            return m_pLevelSolver->getLevelType();
        }

        /**
         * 
         * @param scale
         */
        void setScale(float scale) {
            if(scale < 0.0f)
                scale = 1.0f;
            m_scale = scale;
            if(m_pLevelSolver)
                m_pLevelSolver->setScale(m_scale);
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
        
    private:
        ///
        CLevelSolver* m_pLevelSolver;
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
        
        /// Scale (size) of a single quad object
        float m_scale;
        /// Animation speed (1.0f - 100%/normal)
        float m_speed;
        /// Position on the game grid of the dragged (grabbed) quad (main action)
        Vector2i m_draggedCoord;
        
    }; // class CLevelVis

} // namespace fg

    #undef FG_INC_LEVEL_VISUALIZATION_BLOCK
#endif	/* FG_INC_LEVEL_VIS */
