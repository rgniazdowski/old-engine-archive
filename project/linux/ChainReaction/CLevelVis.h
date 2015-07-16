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
         * @param x
         * @param y
         * @return
         */
        SQuadData* getQuadData(unsigned short x, unsigned short y);
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

        void setMaterialBlack(gfx::SMaterial* pMaterialBlack) {
            m_pMaterialBlack = pMaterialBlack;
        }

        gfx::SMaterial* getMaterialBlack(void) const {
            return m_pMaterialBlack;
        }

        void setMaterialWhite(gfx::SMaterial* pMaterialWhite) {
            m_pMaterialWhite = pMaterialWhite;
        }

        gfx::SMaterial* getMaterialWhite(void) const {
            return m_pMaterialWhite;
        }

    private:
        ///
        game::CGrid* m_pGrid;
        ///
        CLevelFile* m_pLevelFile;
        ///
        gfx::CSceneManager* m_pSceneMgr;
        ///
        gfx::SMaterial* m_pMaterialBlack;
        ///
        gfx::SMaterial* m_pMaterialWhite;
        ///
        QuadDataVec m_quadsData;
        ///
        float m_scale;
    }; // class CLevelVis
} // namespace fg

    #undef FG_INC_LEVEL_VIS_BLOCK
#endif	/* FG_INC_LEVEL_VIS */
