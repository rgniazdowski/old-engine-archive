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
 * File:   ChainReaction.h
 * Author: vigilant
 *
 * Created on May 4, 2015, 3:18 PM
 */

#ifndef FG_INC_CHAIN_REACTION
    #define FG_INC_CHAIN_REACTION
    #define FG_INC_CHAIN_REACTION_BLOCK

    #include "fgManagerBase.h"
    #include "fgTypes.h"
    #include "fgPluginResource.h"
    #include "CLevelVis.h"
    
    //                                0x00010000
    #define FG_MANAGER_CHAIN_REACTION 0x01100000

extern "C" {
    fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
    fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
}

namespace fg {
    class CEngineMain;

    namespace gfx {
        class CDrawingBatch;
    }

    namespace game {
        class CGrid;
        class CGameMain;
    }

    /**
     *
     */
    class CChainReaction : public ::fg::base::CManager {
        friend fgBool ::fgInitPluginFunction_CHAINREACTION(::fg::CPluginResource::SInternalInfo* info);
        friend fgBool ::fgExitPluginFunction_CHAINREACTION(::fg::CPluginResource::SInternalInfo* info);
    public:
        typedef ::fg::base::CManager base_type;
        typedef CChainReaction self_type;
        typedef CChainReaction type;

    public:
        /**
         *
         * @param pEngineMain
         * @param pPluginInfo
         */
        CChainReaction(::fg::CEngineMain* pEngineMain = NULL,
                       ::fg::CPluginResource::SInternalInfo* pPluginInfo = NULL);
        /**
         *
         */
        virtual ~CChainReaction();

    public:
        /**
         *
         */
        virtual void clear(void);
        /**
         *
         * @return
         */
        virtual fgBool destroy(void);
        /**
         *
         * @return
         */
        virtual fgBool initialize(void);

        

    public:
        /**
         *
         */
        void registerCallbacks(void);
        /**
         *
         */
        void unregisterCallbacks(void);

    public:
        /**
         *
         * @return
         */
        ::fg::CEngineMain* getEngineMain(void) {
            return m_pEngineMain;
        }
        /**
         *
         * @return
         */
        game::CGrid* getGameGrid(void) const {
            return m_grid;
        }
        /**
         *
         * @return
         */
        CLevelVis* getLevelVis(void) const {
            return m_levelVis;
        }
    private:
        /**
         *
         * @param system
         * @param user
         * @return
         */
        static fgBool updateHandler(void* system, void* user);
        /**
         *
         * @param system
         * @param user
         * @return
         */
        static fgBool preRenderHandler(void* system, void* user);
        /**
         *
         * @param system
         * @param user
         * @return
         */
        static fgBool renderHandler(void* system, void* user);

        /**
         *
         * @param pEngineMain
         */
        void setEngineMain(::fg::CEngineMain* pEngineMain);
        /**
         *
         * @param pPluginInfo
         */
        void setPluginInfo(::fg::CPluginResource::SInternalInfo* pPluginInfo) {
            m_pPluginInfo = pPluginInfo;
        }

    private:
        ///
        ::fg::CPluginResource::SInternalInfo* m_pPluginInfo;
        ///
        ::fg::CEngineMain* m_pEngineMain;
        ///
        game::CGrid* m_grid;
        ///
        CLevelVis* m_levelVis;
        ///
        event::CFunctionCallback* m_updateCallback;
        ///
        event::CFunctionCallback* m_preRenderCallback;
        ///
        event::CFunctionCallback* m_renderCallback;
        ///
        gfx::SMaterial* m_materialBlack;
        ///
        gfx::SMaterial* m_materialWhite;

    }; // class CChainReaction

} // namespace fg


    #undef FG_INC_CHAIN_REACTION_BLOCK
#endif	/* FG_INC_CHAIN_REACTION */
