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
 * File:   fgGfxUniformUpdater.h
 * Author: vigilant
 *
 * Created on September 13, 2015, 10:51 PM
 */

#ifndef FG_INC_GFX_UNIFORM_UPDATER
    #define FG_INC_GFX_UNIFORM_UPDATER
    #define FG_INC_GFX_UNIFORM_UPDATER_BLOCK

    #include "fgGfxShaderDefs.h"

namespace fg {
    namespace gfx {

        class CShaderManager;
        class CShaderProgram;
        class CMVPMatrix;
        class CMVMatrix;

        struct SDirectionalLight;
        struct SMaterial;

        /**
         *
         */
        class CUniformUpdater {
            friend class CShaderManager;
        public:
            typedef CUniformUpdater self_type;
            typedef CUniformUpdater type;

        private:

            /**
             *
             */
            struct SUniformValue {
                typedef SUniformValue self_type;

                /// Type of the Uniform to set
                shaders::UniformType type;
                /// Pointer to data that needs to be set
                void* data;
                /// Size of the data in bytes
                unsigned int size;
                /// Count of the elements (if holding array of structures or such)
                unsigned int count;
                /// Size of a single element (mainly for structures);
                unsigned int stride;

                /**
                 *
                 */
                SUniformValue();
                /**
                 *
                 * @param uniformType
                 */
                SUniformValue(shaders::UniformType uniformType);
                /**
                 *
                 * @param orig
                 */
                SUniformValue(const SUniformValue& orig);
                /**
                 *
                 */
                ~SUniformValue();

                /**
                 *
                 */
                void release(void);
                /**
                 *
                 * @param bytes
                 */
                void resize(unsigned int bytes);
                /**
                 *
                 * @param matrix
                 * @param index
                 */
                void copy(const Matrix4f& matrix, unsigned int index = 0);
                /**
                 *
                 * @param matrix
                 * @param index
                 */
                void copy(const Matrix3f& matrix, unsigned int index = 0);
                /**
                 *
                 * @param matrix
                 * @param index
                 */
                void copy(const Matrix2f& matrix, unsigned int index = 0);
                /**
                 *
                 * @param vector
                 * @param index
                 */
                void copy(const Vector4f& vector, unsigned int index = 0);
                /**
                 *
                 * @param vector
                 * @param index
                 */
                void copy(const Vector3f& vector, unsigned int index = 0);
                /**
                 *
                 * @param vector
                 * @param index
                 */
                void copy(const Vector2f& vector, unsigned int index = 0);
                /**
                 *
                 * @param data
                 * @param count
                 * @param index
                 */
                void copy(const float* data, unsigned int count, unsigned int index = 0);
                /**
                 *
                 * @param dirLight
                 * @param index
                 */
                void copy(const SDirectionalLight& dirLight, unsigned int index = 0);
                /**
                 *
                 * @param material
                 * @param index
                 */
                void copy(const SMaterial& material, unsigned int index = 0);
            }; // struct SUniformUpdateValue

            typedef CVector<SUniformValue> UniformValueVec;
            typedef CVector<shaders::UniformType> UniformTypeVec;

            ///
            UniformValueVec m_uniformValues;
            ///
            UniformTypeVec m_uniformUpdateList;

        private:
            /**
             *
             */
            CUniformUpdater();
            /**
             *
             * @param orig
             */
            CUniformUpdater(const CUniformUpdater& orig);
            /**
             * 
             */
            virtual ~CUniformUpdater();

        public:
            /**
             *
             * @param uniformType
             */
            void disable(shaders::UniformType uniformType);
            /**
             *
             * @param uniformType
             */
            void enable(shaders::UniformType uniformType);
            /**
             *
             * @param matrix
             * @param index
             */
            void update(CMVPMatrix* matrix,
                        unsigned int index = 0);
            /**
             *
             * @param matrix
             * @param index
             */
            void update(CMVMatrix* matrix,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param matrix
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Matrix4f& matrix,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param matrix
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Matrix3f& matrix,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param matrix
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Matrix2f& matrix,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param light
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const SDirectionalLight& light,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param material
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const SMaterial& material,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param v0
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        fgGFXfloat v0,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param vector
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Vector4f& vector,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param vector
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Vector3f& vector,
                        unsigned int index = 0);
            /**
             *
             * @param uniformType
             * @param vector
             * @param index
             */
            void update(shaders::UniformType uniformType,
                        const Vector2f& vector,
                        unsigned int index = 0);
            //------------------------------------------------------------------
        private:
            /**
             *
             */
            void updateUniforms(CShaderProgram* pProgram);
        }; // class CUniformUpdater

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_UNIFORM_UPDATER_BLOCK
#endif	/* FG_INC_GFX_UNIFORM_UPDATER */
