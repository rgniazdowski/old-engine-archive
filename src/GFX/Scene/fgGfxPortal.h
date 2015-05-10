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
 * File:   fgGfxPortal.h
 * Author: vigilant
 *
 * Created on May 10, 2015, 12:07 PM
 */

#ifndef FG_INC_GFX_PORTAL
    #define FG_INC_GFX_PORTAL
    #define FG_INC_GFX_PORTAL_BLOCK

    #ifndef FG_INC_TYPES
        #include "fgTypes.h"
    #endif
    #ifndef FG_INC_GFX_PLANE
        #include "GFX/fgGfxPlane.h"
    #endif
    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

namespace fg {
    namespace gfx {

        class CPortal;
        class CPortalProcessor;
        class CBspNode;
        class CBspLeaf;

        /**
         *
         */
        class CPortal : public Planef {
        public:
            ///
            typedef CPortal self_type;
            ///
            typedef CPortal type;
            ///
            typedef Planef base_type;

        public:

            enum RelPos {
                ON_PLANE,
                ON_FRONT,
                ON_BACK,
                ON_SPLIT
            };

            enum StateFlags {
                NONE = 0x00,
                INITIAL = 0x01,
                DUPLICATED = 0x02,
                REVERSED = 0x04,
                DELETED = 0x08
            };

        public:
            /**
             *
             */
            CPortal();
            /**
             *
             */
            virtual ~CPortal();
            /**
             *
             * @param pPortProc
             */
            CPortal(CPortalProcessor* pPortProc);
            /**
             *
             * @param r
             */
            CPortal(const CPortal& r);

            /**
             *
             * @param flags
             * @param toggle
             */
            void setFlag(const StateFlags flags, const fgBool toggle = FG_TRUE);
            /**
             *
             */
            void reverse(void);
            /**
             *
             * @param other
             * @return
             */
            CPortal& operator =(const CPortal& other);
            /**
             *
             * @return
             */
            Vector3f getCenter(void) const;
            /**
             *
             */
            void calcNormal(void);
            /**
             * 
             * @param plane
             * @return
             */
            RelPos classify(Planef& plane);
            /**
             *
             * @param other
             */
            void copyProperties(CPortal& other);
            /**
             *
             * @param idx
             */
            void addSideLeafIdx(int idx) {
                m_sideLIdx.push_back(idx);
            }
            /**
             *
             * @param plane
             * @param a
             * @param b
             */
            void split(Planef& plane,
                       CPortal& a,
                       CPortal& b);
            /**
             *
             * @return
             */
            CBspLeaf* getBackLeaf(void);
            /**
             *
             * @return
             */
            CBspLeaf* getFrontLeaf(void);
            /**
             *
             * @return
             */
            Planef& getPlane(void);
            /**
             *
             * @return
             */
            Planef const& getPlane(void) const;
            /**
             *
             */
            inline void clear(void) {
                m_vertexes.clear();
            }

        public:
            ///
            int m_idxThis;
            ///
            int m_planeIdx; // index in planes index of the BSP wich ortal belons too
            ///
            StateFlags m_flags;
            ///
            CVector<Vector3f> m_vertexes;
            ///
            CVector<int> m_sideLIdx;
            ///
            CVector<int> m_sideLIdxFinal;
            ///
            CPortalProcessor* m_pPortProc;
        };

        FG_ENUM_FLAGS(CPortal::StateFlags);
        inline void CPortal::setFlag(const StateFlags flags, const fgBool toggle) {
            if(toggle) {
                m_flags |= flags;
            } else {
                m_flags |= flags;
                m_flags ^= flags;
            }
        }
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PORTAL_BLOCK
#endif	/* FG_INC_GFX_PORTAL */

