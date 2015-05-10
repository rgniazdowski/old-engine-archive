/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GUI_CONTAINER
    #define FG_INC_GUI_CONTAINER
    #define FG_INC_GUI_CONTAINER_BLOCK

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

/* horizontal, vertical */
    #define FG_GUI_CONTAINER_PACK_METHOD
/* left, center, right, top, bottom | combined */
    #define FG_GUI_CONTAINER_PACK_ALIGN

enum fgGuiContainerPackMethod {
    FG_GUI_CONTAINER_PACK_FREE,
    FG_GUI_CONTAINER_PACK_HORIZONTAL,
    FG_GUI_CONTAINER_PACK_VERTICAL
};

enum fgGuiContainerPackAlign {
    FG_GUI_CONTAINER_PACK_ALIGN_NONE = 0,
    FG_GUI_CONTAINER_PACK_ALIGN_LEFT = 1 << 0,
    FG_GUI_CONTAINER_PACK_ALIGN_RIGHT = 1 << 1,
    FG_GUI_CONTAINER_PACK_ALIGN_TOP = 1 << 2,
    FG_GUI_CONTAINER_PACK_ALIGN_BOTTOM = 1 << 3,
    FG_GUI_CONTAINER_PACK_ALIGN_VCENTER = 1 << 4,
    FG_GUI_CONTAINER_PACK_ALIGN_HCENTER = 1 << 5,
    FG_GUI_CONTAINER_PACK_ALIGN_CENTER = FG_GUI_CONTAINER_PACK_ALIGN_HCENTER,
    FG_GUI_CONTAINER_PACK_ALIGN_MIDDLE = FG_GUI_CONTAINER_PACK_ALIGN_VCENTER + FG_GUI_CONTAINER_PACK_ALIGN_HCENTER
};
FG_ENUM_FLAGS(fgGuiContainerPackAlign);

    #include <map>

namespace fg {
    namespace gui {

        /**
         *
         */
        class CContainer : public ::fg::gui::CWidget {
        public:
            ///
            typedef CContainer self_type;
            ///
            typedef CContainer type;
            ///
            typedef CWidget base_type;
            ///
            typedef std::map<std::string, CWidget*> ChildrenMap;
            ///
            typedef ChildrenMap::iterator ChildrenMapItor;
            ///
            typedef CVector<CWidget*> ChildrenVec;
            ///
            typedef ChildrenVec::iterator ChildrenVecItor;

        protected:
            /// 
            ChildrenMap m_childrenMap;
            ///
            ChildrenVec m_children;
            ///
            fgGuiContainerPackMethod m_packMethod;
            ///
            fgGuiContainerPackAlign m_packAlign;

        private:
            ///
            fgBool m_drawChildren;

        protected:
            /**
             * 
             */
            virtual void setDefaults(void);

        public:
            /**
             * 
             */
            CContainer();
            /**
             * 
             */
            virtual ~CContainer();

            /**
             * 
             * @return 
             */
            FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(CContainer)

            /**
             * 
             * @param flags
             */
            virtual void setFlags(const std::string& flags);

            /**
             * 
             * @param guiLayer
             */
            virtual void display(CDrawer *guiLayer);

            using base_type::updateBounds;

            /**
             * 
             * @return 
             */
            virtual gfx::BoundingBox3Df updateBounds(void);
            /**
             * 
             */
            virtual void refresh(void);

            /**
             * 
             * @param pointerData
             * @return 
             */
            virtual EventState updateState(const event::SPointerData *pointerData);

            /**
             * 
             * @param nameTag
             * @return 
             */
            CWidget *getChild(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            CWidget *getChild(const char *nameTag);
            /**
             * 
             * @return 
             */
            ChildrenVec& getChildren(void);
            /**
             * 
             * @return 
             */
            ChildrenMap& getChildrenMap(void);

            /**
             * 
             * @param pWidget
             * @return 
             */
            fgBool addChild(CWidget *pWidget);
            /**
             * 
             * @param pWidget
             * @return 
             */
            fgBool removeChild(CWidget *pWidget);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool removeChild(const std::string& nameTag);
            /**
             * 
             * @param nameTag
             * @return 
             */
            fgBool removeChild(const char *nameTag);

        public:
            /**
             * 
             * @return 
             */
            fgBool isDrawChildren(void) const {
                return m_drawChildren;
            }
            /**
             * 
             * @param toggle
             * @return 
             */
            void setDrawChildren(fgBool toggle = FG_TRUE) {
                m_drawChildren = toggle;
            }
        };
    };
};

    #undef FG_INC_GUI_CONTAINER_BLOCK
#endif /* FG_INC_GUI_CONTAINER */
