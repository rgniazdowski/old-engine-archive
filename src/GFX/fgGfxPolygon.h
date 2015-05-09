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
 * File:   fgGfxPolygon.h
 * Author: vigilant
 *
 * Created on May 9, 2015, 10:35 AM
 */

#ifndef FG_INC_GFX_POLYGON
    #define FG_INC_GFX_POLYGON
    #define FG_INC_GFX_POLYGON_BLOCK

    #include "GFX/fgGfxAABoundingBox.h"
    #include "GFX/fgGfxVertexData.h"
    #include "GFX/fgGfxPlane.h"

    #define SPLITTER_POLY	0x2

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CPolygon : public Planef {
        public:
            typedef Planef base_type;
            typedef CPolygon self_type;
            typedef CPolygon type;

        public:

            enum RelPos {
                ON_PLANE,
                ON_FRONT,
                ON_BACK,
                ON_SPLIT
            };

        public:
            ///
            int m_planeIdx;
            ///
            AABoundingBox3Df m_bbox;
            ///
            CVertexData *m_vertexData;
            ///
            unsigned int m_flags;

        public:
            /**
             *
             */
            CPolygon(unsigned int reserve = 4);
            /**
             *
             */
            virtual ~CPolygon();
            /**
             *
             * @param p
             */
            CPolygon(const CPolygon& p);
            /**
             *
             */
            void clear(void);
            /**
             *
             * @param points
             * @param pPoints
             * @param pBrush
             */
            void create(int points, Vector3f* pPoints);
            /**
             *
             * @param points
             * @param pPoints
             * @param pBrush
             */
            void create(int points, Vertex4v* pPoints);
            /**
             *
             */
            void recalculate(void);

            /**
             *
             * @param pi
             * @return
             */
            fgBool doesContainPoint(Vector3f& pi);
            /**
             *
             * @param p
             */
            void copyProperties(CPolygon& p);
            //fgBool IntersectsPoly(CPolygon& p2);
            /**
             *
             */
            void sortVertexes(void);
            /**
             *
             * @param plane
             * @return
             */
            RelPos classify(base_type& plane);
            /**
             *
             * @param point
             * @return
             */
            int classify(Vector3f& point);
            /**
             *
             * @param plane
             * @param a
             * @param b
             * @param bAnyway
             */
            void split(base_type& plane, CPolygon& a, CPolygon& b, fgBool bAnyway = 0);
            /**
             *
             * @return
             */
            Vector3f getCenter(void) const;
            /**
             *
             * @param plane
             * @param pout
             */
            void clip(CPolygon& plane, CPolygon& pout);
            /**
             *
             * @return
             */
            fgBool isSplitter(void) {
                return (m_flags & SPLITTER_POLY);
            }
            /**
             *
             */
            void setSplitter(void) {
                m_flags |= SPLITTER_POLY;
            }
            /**
             *
             * @param p
             * @return
             */
            CPolygon& operator =(const CPolygon& p);

            /**
             *
             */
            void calcNormal(void);
            /**
             *
             * @param p
             * @return
             */
            fgBool operator ==(const CPolygon& p);
        };

    }
}

    #undef FG_INC_GFX_POLYGON_BLOCK
#endif	/* FG_INC_GFX_POLYGON */

