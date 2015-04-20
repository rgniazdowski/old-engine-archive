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
 * Game Programming Gems: Vol 6, General Programming
 * Gem:    BSP Techniques
 * Author: Octavian Marius Chincisan
 */
#ifndef __GEOMETRY_H__
    #define __GEOMETRY_H__

    #include "fgGfxBspTypes.h"
    #include "fgVector.h"

    #include "GFX/fgGfxAABoundingBox.h"
    #include "GFX/fgGfxVertexData.h"

    #define SPLITTER_POLY	0x2
    #define POLY_DELETED	0x8
    #define POLY_BT_ISSPLITER	0x10
    #define POLY_PORTAL0        0x20
    #define POLY_PORTAL1        0x40
    #define POLY_PROCESSED      0x80
    #define POLY_HIDDEN         0x100
    #define POLY_DIRTY          0x800
    #define POLY_SELECTED       0x2000
    #define BRSH_SOLID          0x1
    #define BRSH_REV            0x2
    #define BRSH_DIRTY          0x8
    #define BRSH_TERRAIN        0x10

    #include "GFX/fgGfxPlane.h"

//class __declspec(novtable) Poly : public Plane {
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

#endif // !__GEOMETRY_H__
