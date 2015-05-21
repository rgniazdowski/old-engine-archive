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
 * File:   CPreviewBspBuilder.h
 * Author: vigilant
 *
 * Created on May 14, 2015, 2:17 AM
 */

#ifndef FG_INC_PREVIEW_BSP_BUILDER
    #define FG_INC_PREVIEW_BSP_BUILDER
    #define FG_INC_PREVIEW_BSP_BUILDER_BLOCK

    #include "fgVector.h"
    #include "Event/fgArgumentList.h"
    #include "Event/fgCallback.h"

    #include "GFX/fgGfxPolygon.h"

    #include "CPreviewModeBase.h"

namespace fg {
    namespace gfx {
        class CBspFile;
        class CBspCompiler;
        class CBspNode;
        class CBspLeaf;

        class CCamera;
        class CCameraAnimation;
        class CSceneManager;
        class CScene3D;

        class CDrawingBatch;
    }
    namespace resource {
        class CResourceManager;
        class CResource;
    }
    namespace gui {
        class CGuiMain;
        class CDrawer;
    }
    namespace editor {
        /**
         *
         */
        class CPreviewBspBuilder : public CPreviewModeBase {
        public:
            typedef CPreviewBspBuilder self_type;
            typedef CPreviewBspBuilder type;
            typedef CPreviewModeBase base_type;

            typedef CVector<gfx::SPolygon> PolygonsVec;
            typedef PolygonsVec::iterator PolygonsVecItor;
            typedef PolygonsVec::const_iterator PolygonsVecConstItor;

        public:

            /**
             * Special enum state flags for toggling various editing modes
             */
            enum StateFlags {
                /// No state flags are currently activated
                NONE = 0x0000,
                /// Mode for adding polygon; it will have default initial size
                /// (height) and its position will depend on the grid parameters
                MODE_POLYGON_ADD = 0x0001,
                /// Mode for selecting polygons via mouse - when one polygon is
                /// selected it can be edited
                MODE_POLYGON_SELECT = 0x0002,
                /// Edition of points
                MODE_POINT_EDIT = 0x0004,

                /// Mouse position (based on pick selection and ray intersection)
                /// will be snapped to grid
                SNAP_TO_GRID = 0x0008,
                /// When drawing polygons they will be snapped to closest
                /// available polygon/edge (size will be also adjusted)
                SNAP_TO_POLYGON = 0x0010,

                /// Set to true when the polygon is currently being drawn
                ACTION_POLYGON_DRAW = 0x0020,
                /// Set when the polygon is being resized (while adding)
                ACTION_POLYGON_RESIZE = 0x0040,
                /// Polygon resizing is proportional (1:1 default)
                RESIZE_PROPORTIONAL = 0x0080,

                /// Mouse was pressed (should be set in only one frame)
                MOUSE_PRESSED = 0x0100,
                /// Mouse is currently down (still pressed)
                MOUSE_DOWN = 0x0200,
                ///
                MOUSE_MOTION = 0x0400,
                ///
                MOUSE_RELEASED = 0x0800,                
            };

            enum PreviewSide {
                FREE_LOOK = 0,
                LEFT = 1,
                RIGHT = 2,
                TOP = 3,
                BOTTOM = 4,
                FRONT = 5,
                BACK = 6
            };
            //------------------------------------------------------------------

        public:
            /**
             *
             * @param pEngineMainOrig
             */
            CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig);

            /**
             *
             */
            virtual ~CPreviewBspBuilder();

            /**
             *
             * @param toggle
             * @return
             */
            virtual fgBool activate(fgBool toggle = FG_FALSE);
            /**
             *
             */
            virtual void refreshInternals(void);

            //------------------------------------------------------------------

        public:
            /**
             *
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
            /**
             *
             * @return
             */
            StateFlags getStateFlags(void) const {
                return m_stateFlags;
            }
            /**
             *
             * @param toggle
             */
            inline void setModePolygonAdd(const fgBool toggle = FG_TRUE) {
                setFlag(MODE_POLYGON_ADD, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isModePolygonAdd(void) const {
                return (fgBool)!!(m_stateFlags & MODE_POLYGON_ADD);
            }
            /**
             *
             * @param toggle
             */
            inline void setModePolygonSelect(const fgBool toggle = FG_TRUE) {
                setFlag(MODE_POLYGON_ADD, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isModePolygonSelect(void) const {
                return (fgBool)!!(m_stateFlags & MODE_POLYGON_SELECT);
            }
            /**
             *
             * @param toggle
             */
            inline void setModePointEdit(const fgBool toggle = FG_TRUE) {
                setFlag(MODE_POINT_EDIT, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isModePointEdit(void) const {
                return (fgBool)!!(m_stateFlags & MODE_POINT_EDIT);
            }
            /**
             *
             * @param toggle
             */
            inline void setSnapToGrid(const fgBool toggle = FG_TRUE) {
                setFlag(SNAP_TO_GRID, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isSnapToGrid(void) const {
                return (fgBool)!!(m_stateFlags & SNAP_TO_GRID);
            }
            /**
             *
             * @param toggle
             */
            inline void setSnapToPolygon(const fgBool toggle = FG_TRUE) {
                setFlag(SNAP_TO_POLYGON, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isSnapToPolygon(void) const {
                return (fgBool)!!(m_stateFlags & SNAP_TO_POLYGON);
            }
            /**
             *
             * @param toggle
             */
            inline void setActionPolygonDraw(const fgBool toggle = FG_TRUE) {
                setFlag(ACTION_POLYGON_DRAW, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isActionPolygonDraw(void) const {
                return (fgBool)!!(m_stateFlags & ACTION_POLYGON_DRAW);
            }
            /**
             *
             * @param toggle
             */
            inline void setActionPolygonResize(const fgBool toggle = FG_TRUE) {
                setFlag(ACTION_POLYGON_RESIZE, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isActionPolygonResize(void) const {
                return (fgBool)!!(m_stateFlags & ACTION_POLYGON_RESIZE);
            }
            /**
             *
             * @param toggle
             */
            inline void setResizeProportional(const fgBool toggle = FG_TRUE) {
                setFlag(RESIZE_PROPORTIONAL, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isResizeProportional(void) const {
                return (fgBool)!!(m_stateFlags & RESIZE_PROPORTIONAL);
            }
            /**
             *
             * @return
             */
            inline fgBool isMousePressed(void) const {
                return (fgBool)!!(m_stateFlags & MOUSE_PRESSED);
            }
            /**
             *
             * @return
             */
            inline fgBool isMouseDown(void) const {
                return (fgBool)!!(m_stateFlags & MOUSE_DOWN);
            }
            /**
             *
             * @return
             */
            inline fgBool isMouseMotion(void) const {
                return (fgBool)!!(m_stateFlags & MOUSE_MOTION);
            }
            /**
             *
             * @return
             */
            inline fgBool isMouseReleased(void) const {
                return (fgBool)!!(m_stateFlags & MOUSE_RELEASED);
            }
        protected:
            /**
             *
             * @param toggle
             */
            inline void setMousePressed(const fgBool toggle = FG_TRUE) {
                setFlag(MOUSE_PRESSED, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setMouseDown(const fgBool toggle = FG_TRUE) {
                setFlag(MOUSE_DOWN, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setMouseMotion(const fgBool toggle = FG_TRUE) {
                setFlag(MOUSE_MOTION, toggle);
            }
            /**
             *
             * @param toggle
             */
            inline void setMouseReleased(const fgBool toggle = FG_TRUE) {
                setFlag(MOUSE_RELEASED, toggle);
            }
        public:
            //------------------------------------------------------------------

            /**
             * 
             * @param previewSide
             */
            void activatePreviewSide(PreviewSide previewSide);

            /**
             *
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool engineInit(void* systemData, void* userData);
            /**
             *
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool engineDestroy(void* systemData, void* userData);

        public:
            /**
             *
             * @param polygon
             */
            static void createPolygonQuad(gfx::SPolygon& polygon);
            /**
             *
             * @param begin
             * @param end
             * @param polygon
             */
            void createPolygonQuad(const Vec3f& begin,
                                   const Vec3f& end,
                                   gfx::SPolygon& polygon);
            /**
             *
             * @param begin
             * @param end
             * @param polygon
             */
            void updatePolygonQuad(const Vec3f& begin,
                                   const Vec3f& end,
                                   gfx::SPolygon& polygon);
            /**
             *
             * @param event
             */
            void OnContextItemSelected(wxCommandEvent& event);

            //------------------------------------------------------------------

        protected:

            /**
             * 
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool displayHandler(void* systemData, void* userData);
            /**
             *
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool updateHandler(void* systemData, void* userData);
            /**
             *
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool renderHandler(void* systemData, void* userData);

            /**
             *
             * @param argv
             * @return
             */
            fgBool mouseHandler(fg::event::CArgumentList* argv);
            /**
             *
             * @param argv
             * @return
             */
            fgBool keyboardHandler(fg::event::CArgumentList* argv);

            /**
             *
             * @return
             */
            virtual fgBool registerCallbacks(void);
            /**
             *
             * @return
             */
            virtual fgBool unregisterCallbacks(void);

        private:
            ///
            PolygonsVec m_polygons;
            ///
            gfx::SPolygon* m_currentPolygon;
            ///
            PreviewSide m_previewSide;
            ///
            gfx::CBspCompiler* m_bspCompiler;
            ///
            gfx::CBspFile* m_bspFile;
            ///
            gfx::CSceneManager* m_p3DScene;
            ///
            gfx::CCameraAnimation* m_pCamera;
            ///
            resource::CResourceManager* m_pResourceMgr;
            ///
            gui::CGuiMain* m_pGuiMain;
            ///
            gui::CDrawer* m_pGuiDrawer;

            ///
            StateFlags m_stateFlags;

            ///
            float m_minCamDistance;

            /// Special callback called once in every display (pre-render) frame.
            /// Here can add additional things to the drawing batch.
            event::CFunctionCallback* m_displayShotCB;
            /// Special callback called once in every update frame.
            event::CFunctionCallback* m_updateShotCB;
            /// Special callback called once in every render frame.
            /// Can call rendering functions inside (gl).
            event::CFunctionCallback* m_renderShotCB;
            /// Handler function callback object for any mouse event (move, clicks).
            event::CFunctionCallback* m_mouseHandlerCB;
            /// Handler for any keyboard event - up and down keys.
            /// This is events are thrown only once when key state is changing.
            event::CFunctionCallback* m_keyboardHandlerCB;

        public:
            static const long idBspPreviewFreeLook;
            static const long idBspPreviewLeft;
            static const long idBspPreviewRight;
            static const long idBspPreviewTop;
            static const long idBspPreviewBottom;
            static const long idBspPreviewFront;
            static const long idBspPreviewBack;
        }; // class CPreviewBspBuilder

        FG_ENUM_FLAGS(CPreviewBspBuilder::StateFlags);
        /**
         *
         * @param flags
         * @param toggle
         */
        inline void CPreviewBspBuilder::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_stateFlags |= flags;
            } else {
                m_stateFlags |= flags;
                m_stateFlags ^= flags;
            }
        }

    } // namespace editor
} // namespace fg

    #undef FG_INC_PREVIEW_BSP_BUILDER_BLOCK
#endif	/* FG_INC_PREVIEW_BSP_BUILDER */
