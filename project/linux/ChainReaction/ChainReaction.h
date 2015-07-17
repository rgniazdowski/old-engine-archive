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
    #include "Event/fgEventDefinitions.h"
    #include "Event/fgCallback.h"

    #include "CLevelVis.h"

    #define FG_MANAGER_CHAIN_REACTION 0x01100000

extern "C" {
    fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
    fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
}

namespace fg {
    class CEngineMain;

    namespace gfx {
        class CGfxMain;
        class CDrawingBatch;
        class CSceneManager;
        class CSceneNode;
        class CSceneNodeObject;
    }

    namespace game {
        class CGrid;
        class CGameMain;
    }

    /**
     * Main class for the ChainReaction game plugin.
     * Hooks to the main loop and performs all operations required by the game -
     * based on the logic and design - plugin is more efficient than scripts.
     * Plugin is useful also for separation between the abstract engine code and
     * more detailed and focused game mechanics code (at least at this stage).
     */
    class CChainReaction : public ::fg::base::CManager {
        friend fgBool::fgInitPluginFunction_CHAINREACTION(::fg::CPluginResource::SInternalInfo* info);
        friend fgBool::fgExitPluginFunction_CHAINREACTION(::fg::CPluginResource::SInternalInfo* info);
    public:
        typedef ::fg::base::CManager base_type;
        typedef CChainReaction self_type;
        typedef CChainReaction type;

    public:
        constexpr static const float QUAD_HALF_SIZE = SQuadData::QUAD_HALF_SIZE;

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
         */
        void updateStep(void);
        /**
         * 
         */
        void preRenderStep(void);
        /**
         *
         */
        void renderStep(void);

    private:
        /**
         * 
         * @param argv
         * @return 
         */
        fgBool touchHandler(event::CArgumentList* argv);
        /**
         *
         * @param argv
         * @return
         */
        fgBool mouseHandler(event::CArgumentList* argv);

        /**
         *
         * @param swipeDir
         * @param pos
         * @param end
         * @param steps
         * @param pressed
         * @param released
         * @param id
         */
        void dragHandler(event::SSwipe::Direction swipeDir,
                         const Vec2i& pos, const Vec2i& end,
                         const Vec2i& steps, fgBool pressed,
                         fgBool released, unsigned int id);
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
        /// Pointer to the internal plugin info
        ::fg::CPluginResource::SInternalInfo* m_pPluginInfo;
        /// Pointer to the main FG engine instance (one per execution)
        ::fg::CEngineMain* m_pEngineMain;
        /// Pointer to the main GFX subsystem instance
        gfx::CGfxMain* m_pGfxMain;
        /// Pointer to the external scene manager (3D by default)
        gfx::CSceneManager* m_pSceneMgr;
        /// Game logic main object
        game::CGameMain* m_pGameMain;
        /// Game logic abstract grid
        game::CGrid* m_grid;
        /// Level visualization class - hooks with SceneManager
        CLevelVis* m_levelVis;
        /// Update (shot) callback object
        event::CFunctionCallback* m_updateCallback;
        /// Pre-render callback object
        event::CFunctionCallback* m_preRenderCallback;
        /// Render callback object
        event::CFunctionCallback* m_renderCallback;
        /// Touch callback object
        event::CFunctionCallback* m_touchCallback;
        /// Mouse callback object
        event::CFunctionCallback* m_mouseCallback;
        /// Material designed for the black quads
        gfx::SMaterial* m_materialBlack;
        /// Material designed for the white quads
        gfx::SMaterial* m_materialWhite;

        /**
         *
         */
        struct SDragging {
            ///
            Vec3f begin;
            ///
            Vec3f current;
            ///
            float length;
            ///
            Vec2i quadCoord;
            ///
            fgBool isValid;
            ///
            float zoomProp;
            ///
            SQuadData* pQuadData;
            ///
            gfx::CSceneNode* pNode;
            /**
             *
             */
            SDragging();
            /**
             *
             */
            ~SDragging();
            /**
             *
             */
            void invalidate(void);

        } m_drag; // struct SDragging
    }; // class CChainReaction

} // namespace fg


    #undef FG_INC_CHAIN_REACTION_BLOCK
#endif	/* FG_INC_CHAIN_REACTION */
