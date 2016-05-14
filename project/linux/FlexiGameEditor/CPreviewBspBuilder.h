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
    #include "Util/fgBTreeMap.h"

    #include "GFX/fgGfxPolygon.h"

    #include "CPreviewModeBase.h"
    #include "CBspMaterialsEditDialog.h"
    // Panels
    #include "CBspPreviewBottomPanel.h"
    #include "CBspPreviewLeftPanel.h"

class wxWindow;
class wxFrame;

class CBspMaterialsEditDialog;

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

        class CDrawCall;
        class CDrawingBatch;

        class CVertexData;
        struct SMaterial;
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

        public:

            /**
             *
             */
            struct SPolygonHolder {
                ///
                gfx::SPolygon polygon;
                ///
                gfx::CDrawCall *drawCall;
                ///
                fgBool isSelected;

                /**
                 *
                 */
                SPolygonHolder();
                /**
                 *
                 */
                ~SPolygonHolder();
                /**
                 *
                 */
                void render(const fgBool drawBox = FG_FALSE);

                /**
                 *
                 * @param rayEye
                 * @param rayDir
                 * @param intersectionPoint
                 * @param bothSides
                 * @return
                 */
                fgBool rayIntersect(const Vec3f& rayEye,
                                    const Vec3f& rayDir,
                                    Vec3f& intersectionPoint,
                                    const fgBool bothSides = FG_FALSE);
                /**
                 *
                 * @return
                 */
                inline unsigned int size(void) const {
                    polygon.size();
                }
                /**
                 *
                 * @return
                 */
                inline gfx::CVertexData* getVertexData(void) const {
                    return polygon.getVertexData();
                }
                /**
                 *
                 */
                void refreshDrawCall(void);
                /**
                 *
                 * @param pMaterial
                 */
                void setMaterial(const gfx::SMaterial* pMaterial);
            }; // struct SPolygonHolder

            typedef CVector<SPolygonHolder*> PolygonsVec;
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

                /// Multiple selection of polygons
                PICK_SELECTION_GROUP = 0x0008,
                /// Toggle mode for polygon selection
                PICK_SELECTION_TOGGLE = 0x0010,
                /// Whether or not the group selection uses selection box
                PICK_SELECTION_BOX = 0x0020,

                /// Mouse position (based on pick selection and ray intersection)
                /// will be snapped to grid
                SNAP_TO_GRID = 0x0040,
                /// When drawing polygons they will be snapped to closest
                /// available polygon/edge (size will be also adjusted)
                SNAP_TO_POLYGON = 0x0080,

                /// Set to true when the polygon is currently being drawn
                ACTION_POLYGON_DRAW = 0x0100,
                /// Set when the polygon is being resized (while adding)
                ACTION_POLYGON_RESIZE = 0x0200,
                /// Polygon resizing is proportional (1:1 default)
                RESIZE_PROPORTIONAL = 0x0400,

                /// Mouse was pressed (should be set in only one frame)
                MOUSE_PRESSED = 0x1000,
                /// Mouse is currently down (still pressed)
                MOUSE_DOWN = 0x2000,
                /// Mouse is currently moving
                MOUSE_MOTION = 0x4000,
                /// Mouse is currently released
                MOUSE_RELEASED = 0x8000,
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
            CPreviewBspBuilder(wxWindow* pParent, fg::CEngineMain** pEngineMainOrig);

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

            /**
             * 
             * @param pMaterial
             */
            void refreshMaterial(gfx::SMaterial* pMaterial);

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
                if(toggle) {
                    setFlag(MODE_POLYGON_SELECT, FG_FALSE);
                    setFlag(MODE_POINT_EDIT, FG_FALSE);
                }
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
                setFlag(MODE_POLYGON_SELECT, toggle);
                if(toggle) {
                    setFlag(MODE_POLYGON_ADD, FG_FALSE);
                    setFlag(MODE_POINT_EDIT, FG_FALSE);
                }
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
                if(toggle) {
                    setFlag(MODE_POLYGON_SELECT, FG_FALSE);
                    setFlag(MODE_POLYGON_ADD, FG_FALSE);
                }
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
            inline void setPickSelectionGroup(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_GROUP, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionGroup(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_GROUP);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionToggle(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_TOGGLE, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionToggle(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_TOGGLE);
            }
            /**
             *
             * @param toggle
             */
            inline void setPickSelectionBox(const fgBool toggle = FG_TRUE) {
                setFlag(PICK_SELECTION_BOX, toggle);
            }
            /**
             *
             * @return
             */
            inline fgBool isPickSelectionBox(void) const {
                return (fgBool)!!(m_stateFlags & PICK_SELECTION_BOX);
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
             * @param begin
             * @param end
             * @param polygon
             */
            void createPolygonQuad(const Vec3f& begin,
                                   const Vec3f& end,
                                   gfx::SPolygon& polygon,
                                   const fgBool uvTiled = FG_FALSE);
            /**
             *
             * @param begin
             * @param end
             * @param polygon
             */
            void updatePolygonQuad(const Vec3f& begin,
                                   const Vec3f& end,
                                   gfx::SPolygon& polygon,
                                   const fgBool uvTiled = FG_FALSE);
            /**
             *
             * @param event
             */
            void OnContextItemSelected(wxCommandEvent& event);

            //------------------------------------------------------------------

        protected:

            /**
             *
             */
            struct SPickedPolygonInfo {

                union {
                    fgBool picked;
                    fgBool result;
                };
                ///
                float timeStamp;
                ///
                SPolygonHolder* pPolygon;
                ///
                Vector3f baryPosition;
                ///
                Vector3f intersectionPosition;

                /**
                 *
                 */
                struct SOnScreen {
                    ///
                    gfx::AABB2Di box;
                    ///
                    Vector2i center;
                    ///
                    int radius;
                    /**
                     *
                     */
                    SOnScreen() : box(), center(), radius() {
                        box.invalidate();
                    }
                } onScreen;
                /**
                 *
                 */
                SPickedPolygonInfo() : result(FG_FALSE),
                timeStamp(-1.0f),
                pPolygon(NULL),
                baryPosition(),
                intersectionPosition(),
                onScreen() {
                    onScreen.box.invalidate();
                }
                /**
                 *
                 */
                void clear(void) {
                    timeStamp = -1.0f;
                    pPolygon = NULL;
                    onScreen.box.invalidate();
                    onScreen.radius = 0;
                    onScreen.center.x = 0;
                    onScreen.center.y = 0;
                    baryPosition = Vec3f();
                    intersectionPosition = Vec3f();
                }
            };

            typedef util::btree_map<unsigned long int, SPickedPolygonInfo> PickedPolygonsInfoMap;
            typedef PickedPolygonsInfoMap::iterator PickedPolygonsInfoMapItor;

            /**
             *
             */
            struct SPolygonSelection {
                ///
                Vector2i pickPos;
                ///
                Vector2i pickPosBegin;
                ///
                gfx::AABB2Di pickBox;
                ///
                Vector3f rayEye;
                ///
                Vector3f rayDir;
                ///
                Vector3f groundIntersectionPoint[2];
                ///
                float pickBegin;
                ///
                fgBool shouldUnselect;
                ///
                fgBool shouldCheck;
                ///
                fgBool isToggle;
                ///
                fgBool isGroup;
                ///
                fgBool checkBox;
                ///
                SPolygonHolder* lastSelectedPolygon;
                ///
                CVector<SPolygonHolder*> selectedPolygons;
                ///
                CVector<Vector3f> projectedPoints;
                ///
                PickedPolygonsInfoMap pickedPolygonsInfo;
                ///
                gfx::CMVPMatrix* pMVP;
                /**
                 *
                 */
                SPolygonSelection();
                /**
                 *
                 */
                ~SPolygonSelection();
                /**
                 * 
                 * @param mvp
                 * @param camera
                 * @param stateFlags
                 */
                void init(const gfx::CCamera& camera,
                          StateFlags stateFlags);
                /**
                 *
                 * @param stateFlags
                 */
                void end(StateFlags stateFlags);
                /**
                 *
                 * @param mvp
                 * @param camera
                 */
                void updateRay(const gfx::CCamera& camera);
                /**
                 *
                 * @param pPolygon
                 * @param pickInfo
                 * @param mvp
                 * @return
                 */
                fgBool isPicked(SPolygonHolder* pPolygon,
                                SPickedPolygonInfo& pickInfo);

                /**
                 *
                 * @param pBspPreview
                 * @param pPolygon
                 * @return
                 */
                fgBool fullCheck(CPreviewBspBuilder* pBspPreview,
                                 SPolygonHolder* pPolygon,
                                 unsigned int polygonIndex);

            } m_polygonSelection;

        protected:

            /**
             * 
             * @param systemData
             * @param userData
             * @return
             */
            static fgBool preRenderHandler(void* systemData, void* userData);
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
            gfx::SMaterial* m_currentMaterial;
            ///
            gfx::SMaterial* m_internalMaterial;
            ///
            gfx::SMaterial* m_selectionMaterial;
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
            event::CFunctionCallback* m_preRenderShotCB;
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

            /// Pointer to the main frame - parent window
            wxWindow* m_pMainFrame;

            /// Special internal dialog for showing material options
            CBspMaterialsEditDialog* m_materialsEditDialog;
            ///
            CBspPreviewLeftPanel* m_bspLeftPanel;
            ///
            CBspPreviewBottomPanel* m_bspBottomPanel;

        public:
            static const long idMenuFreeLook;
            static const long idMenuLeft;
            static const long idMenuRight;
            static const long idMenuTop;
            static const long idMenuBottom;
            static const long idMenuFront;
            static const long idMenuBack;
            static const long idMenuGridProperties;
            static const long idMenuMaterials;

            static const long idMenuCheckModePolySelection;
            static const long idMenuCheckSnapToGrid;
            static const long idMenuCheckSnapToPolygon;

            static const long idMenuFirst;
            static const long idMenuLast;
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
