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

    #ifndef FG_INC_GFX_AA_BOUNDING_BOX
        #include "GFX/fgGfxAABoundingBox.h"
    #endif
    #include "GFX/fgGfxVertexData.h"
    #include "GFX/fgGfxPlane.h"

    #define SPLITTER_POLY	0x2

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SPolygon : public Planef {
            ///
            typedef Planef base_type;
            ///
            typedef SPolygon self_type;
            ///
            typedef SPolygon type;

            enum RelPos {
                ON_PLANE,
                ON_FRONT,
                ON_BACK,
                ON_SPLIT
            };

            ///
            int planeIdx;
            ///
            int materialIdx;
            ///
            AABoundingBox3Df bbox;
            ///
            unsigned int flags;

        private:
            ///
            CVertexData* vertexData;

        public:
            /**
             *
             */
            SPolygon(unsigned int reserve = 4);
            /**
             *
             */
            virtual ~SPolygon();
            /**
             *
             * @param p
             */
            SPolygon(const SPolygon& p);
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
            void copyProperties(SPolygon& p);
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
            void split(base_type& plane, SPolygon& a, SPolygon& b, fgBool bAnyway = 0);
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
            void clip(SPolygon& plane, SPolygon& pout);
            /**
             *
             * @return
             */
            fgBool isSplitter(void) {
                return (flags & SPLITTER_POLY);
            }
            /**
             *
             */
            void setSplitter(void) {
                flags |= SPLITTER_POLY;
            }
            /**
             *
             * @param p
             * @return
             */
            SPolygon& operator =(const SPolygon& p);

            /**
             *
             */
            void calcNormal(void);
            /**
             *
             * @param p
             * @return
             */
            fgBool operator ==(const SPolygon& p);

        public:
            /**
             * 
             * @return
             */
            CVertexData* getVertexData(void) const {
                return vertexData;
            }
            /**
             *
             * @return
             */
            unsigned int getVertexDataStride(void) const {
                if(!vertexData)
                    return 0;
                return (unsigned int)vertexData->stride();
            }
            /**
             * 
             * @return
             */
            unsigned int size(void) const {
                if(!vertexData)
                    return 0;
                return (unsigned int)vertexData->size();
            }
        };

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_POLYGON_BLOCK
#endif	/* FG_INC_GFX_POLYGON */

