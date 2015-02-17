/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSkyBox.h
 * Author: vigilant
 *
 * Created on January 26, 2015, 7:16 PM
 */

#ifndef FG_INC_GFX_SKYBOX
    #define FG_INC_GFX_SKYBOX
    #define FG_INC_GFX_SKYBOX_BLOCK

    #include "GFX/fgGFXDrawable.h"
    #include "GFX/fgGFXTextureID.h"

namespace fg {
    namespace gfx {

        class CShaderProgram;
        class CMVPMatrix;

        /**
         *
         */
        class CSceneSkyBox : public CDrawable {
        public:
            ///
            typedef fg::gfx::CDrawable base_type;
            ///
            typedef CSceneSkyBox type;
            ///
            typedef CSceneSkyBox self_type;
            
        public:
            /**
             *
             */
            enum SkyBoxType {
                SKYBOX_CUBE,
                SKYBOX_DOME,
                SKYBOX_FLAT
            };
            
        public:
            /**
             * 
             */
            CSceneSkyBox();
            /**
             * 
             * @param orig
             */
            CSceneSkyBox(const CSceneSkyBox& orig);
            /**
             * 
             */
            virtual ~CSceneSkyBox();

        public:
            /**
             * 
             */
            virtual void draw(void);
            /**
             * Draw with relative 2D position
             * @param relPos
             */
            virtual void draw(const Vec2f& relPos);
            /**
             * Draw with relative 3D position
             * @param relPos
             */
            virtual void draw(const Vec3f& relPos);
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat);

        public:
            /**
             * 
             * @param skyBoxScale
             */
            inline void setScale(float skyBoxScale) {
                m_skyBoxScale = skyBoxScale;
            }
            /**
             * 
             * @return 
             */
            inline float getScale(void) const {
                return m_skyBoxScale;
            }
            /**
             * 
             * @param position
             */
            inline void setPosition(const Vector3f& position) {
                m_pos = position;
            }
            /**
             * 
             * @return 
             */
            inline Vector3f& getPosition(void) {
                return m_pos;
            }
            /**
             * 
             * @return 
             */
            inline Vector3f const& getPosition(void) const {
                return m_pos;
            }
            /**
             * Sets the texture pointer
             * @param textureID
             */
            void setTexture(const STextureID& textureID) {
                m_textureID = textureID;
            }
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID& getTexture(void) {
                return m_textureID;
            }
            /**
             * Returns the texture ID reference
             * @return 
             */
            STextureID const& getTexture(void) const {
                return m_textureID;
            }
            /**
             * 
             * @param pProgram
             */
            void setShaderProgram(CShaderProgram *pProgram = NULL) {
                m_program = pProgram;
            }
            /**
             * Returns the currently used shader program for this draw call
             * @return 
             */
            CShaderProgram* getShaderProgram(void) const {
                return m_program;
            }
            /**
             * Sets the pointer to given MVP matrix
             * @param MVP
             */
            void setMVP(CMVPMatrix *MVP = NULL) {
                m_MVP = MVP;
            }
            /**
             * Returns the pointer to currently used MVP matrix
             * @return 
             */
            CMVPMatrix * getMVP(void) const {
                return m_MVP;
            }

        private:
            ///
            float m_skyBoxScale;
            ///
            Vector3f m_pos;
            ///
            STextureID m_textureID;
            ///
            CShaderProgram *m_program;
            ///
            CMVPMatrix *m_MVP;
        };

    };
};

    #undef FG_INC_GFX_SKYBOX_BLOCK
#endif	/* FG_INC_GFX_SKYBOX */
