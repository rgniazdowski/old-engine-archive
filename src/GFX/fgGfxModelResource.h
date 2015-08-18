/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MODEL_RESOURCE
    #define FG_INC_GFX_MODEL_RESOURCE
    #define FG_INC_GFX_MODEL_RESOURCE_BLOCK

    #ifndef FG_INC_TYPES
        #include "fgTypes.h"
    #endif
    #ifndef FG_INC_GFX_MODEL_TYPES
        #include "fgGfxModelTypes.h"
    #endif
    #ifndef FG_INC_RESOURCE
        #include "Resource/fgResource.h"
    #endif

    #if defined(FG_USING_ASSIMP)
namespace Assimp {
    class Importer;
}
    #endif

namespace fg {
    namespace resource {
        class CResource;
    };

    namespace gfx {

        /**
         *
         */
        enum ModelType {
            /// Invalid / not selected file format
            MODEL_INVALID = 0x000,
            /// Custom 3d model file format (flexi obj - binary)
            MODEL_CUSTOM = 0x0F0,
            /// Custom 3d model file format (flexi obj - binary)
            MODEL_FLEXI_OBJ = 0x0F0,
            /// 3DS - Autodesk 3ds Max 3D
            MODEL_3DS = 0x0F1,
            /// OBJ - Wavefront Technologies
            MODEL_OBJ = 0x0F2,
            /// BLEND - Blender file database
            MODEL_BLEND = 0x0F3,
            /// DAE - COLLADA
            MODEL_DAE = 0x0F4,
            /// DXF - AutoCAD, Drawing Exchange Format
            /// CAD data file format developed by Autodesk
            MODEL_DXF = 0x0F5,
            /// FBX - Autodesk exchange - exchange format, in particular for 
            /// inter-operability between Autodesk products and other Digital
            /// content creation (DCC) software packages
            MODEL_FBX = 0x0F6,
            /// LWO - Lightwave object - LightWave high-end software file format
            MODEL_LWO = 0x0F7,
            /// OFF - Object File Format 
            MODEL_OFF = 0x0F8,
            /// X - DirectX 3D Model
            MODEL_X = 0x0F9,
            /// Built-in data - from static memory (compiled with vertices or
            /// auto-generated with some algorithm)
            MODEL_BUILTIN = 0x0FA
        };

        /*
         * Class definition for Model Resource
         * This resource loads various types of models
         * Provides functions also for generation of VBOs
         */
        class CModelResource : public resource::CResource {
        public:
            ///
            typedef fg::resource::CResource base_type;
            ///
            typedef CModelResource self_type;
            ///
            typedef CModelResource type;

            /// Type definition for vector holding model shapes
            typedef CVector<SShape *> ShapesVec;
            /// Type definition for special vector iterator
            typedef ShapesVec::iterator ShapesVecItor;

        public:

            /**
             *
             */
            enum ModelFlags {
                /// Empty flags - none set
                NO_FLAGS = 0x0000,
                /// Does this model contain animations?
                ANIMATED = 0x0001,
                /// Is this model rigged? (bone information)
                RIGGED = 0x0002,
                /// Does this model have any kind of material? (excluding the override)
                HAS_MATERIALS = 0x0004,
                /// Is data interleaved (soa or aos?)
                INTERLEAVED = 0x0008,
                /// Is model textured?
                TEXTURED = 0x0010,
                /// is model multitextured?
                MULTITEXTURED = 0x0020
            };

        public:
            /**
             * 
             */
            CModelResource();
            /**
             * 
             * @param path
             */
            CModelResource(const char *path);
            /**
             * 
             * @param path
             */
            CModelResource(std::string& path);
            /**
             * 
             */
            virtual ~CModelResource();

            FG_RESOURCE_FACTORY_CREATE_FUNCTION(CModelResource)

        protected:
            /**
             * Clears the class data, this actually does not free allocated memory,
             * just resets base class attributes
             */
            virtual void clear(void);

            /**
             * 
             * @return 
             */
            fgBool refreshInternalData(void);

        public:
            /**
             * Create function loads/interprets data from file in ROM and place it in RAM memory.
             * @return 
             */
            virtual fgBool create(void);
            /**
             * Destroy all loaded data including additional metadata (called with destructor)
             */
            virtual void destroy(void);
            /**
             * Reloads any data, recreates the resource (refresh)
             * @return 
             */
            virtual fgBool recreate(void);
            /**
             * Dispose completely of the all loaded data, free all memory
             */
            virtual void dispose(void);
            /**
             * Checks if resource is disposed (not loaded yet or disposed after)
             * @return  FG_TRUE if resource is disposed, FG_FALSE otherwise
             */
            virtual fgBool isDisposed(void) const;

        protected:
            /**
             * Determines the model type identifier from the file extension
             * @param path  Path to check for file extension
             * @return      FG_TRUE if the path pointed to valid 3d model file,
             *              FG_FALSE otherwise
             */
            fgBool setModelTypeFromFilePath(std::string &path);
            /**
             * Determines the model type identifier from the file extension,
             * it uses the currently set path for the resource (based on the quality)
             * @return      FG_TRUE if the path pointed to valid 3d model file,
             *              FG_FALSE otherwise
             */
            fgBool setModelTypeFromFilePath(void) {
                if(getFilePath(base_type::m_quality).empty())
                    return FG_FALSE;
                return setModelTypeFromFilePath(getFilePath(base_type::m_quality));
            }

            /**
             * Helper function for loading the proper .OBJ model file
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadWavefrontObj(void);
            /**
             * Helper function for loading custom internal FlexiGame model file
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadFlexiObject(void);
            /**
             * Helper function for loading 3DS model file (Autodesk 3ds Max 3D)
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadAutodesk3ds(void);
            /**
             * Helper function for loading Blender file database
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadBlender(void);
            /**
             * Helper function for loading Collada model file
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadCollada(void);
            /**
             * Helper function for loading AutoCAD .DXF file
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadAutoCAD(void);
            /**
             * Helper function for loading Autodesk exchange file
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadAutodeskExchange(void);
            /**
             * Helper function for loading Lightwave object
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadLightwaveObject(void);
            /**
             * Helper function for loading .OFF model (Object File Format)
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadObjectFile(void);
            /**
             * Helper function for loading .X model (DirectX)
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadDirectXModel(void);

    #if defined(FG_USING_ASSIMP)
            /**
             * General helper function for loading models using Assimp library
             * @return  FG_TRUE if the load was successful, FG_FALSE otherwise
             */
            fgBool internal_loadUsingAssimp(void);
    #endif

            /**
             * 
             * @param flags
             * @param toggle
             */
            void setFlag(const ModelFlags flags, const fgBool toggle = FG_TRUE);

        public:
            /**
             * 
             * @param modelType
             */
            void setModelType(ModelType modelType) {
                m_modelType = modelType;
            }
            /**
             *
             * @param shape
             */
            void addShape(SShape *shape);
            /**
             * 
             * @param mesh
             * @param name
             */
            SShape* addShape(SMeshBase *pMesh, const char *name);
            /**
             *
             * @param mesh
             * @param name
             */
            SShape* addShape(SMeshBase *pMesh, const std::string& name);

        public:
            /**
             * Returns the reference to the shapes array
             * @return  Reference to the shapes array
             */
            ShapesVec& getRefShapes(void) {
                return m_shapes;
            }
            /**
             * Returns the reference to the shapes array
             * @return  Reference to the shapes array
             */
            ShapesVec const& getRefShapes(void) const {
                //return (const_cast<fgDataObjectBase<HandleType, MapKeyType>*>(this)->getFilePath(id));
                //return (const_cast<fgGfxModelResource *>(this)->getRefShapes());
                return m_shapes;
            }
            /**
             * 
             * @return 
             */
            AABoundingBox3Df& getRefAABB(void) {
                return m_aabb;
            }
            /**
             * 
             * @return 
             */
            AABoundingBox3Df const& getRefAABB(void) const {
                return m_aabb;
            }

            /**
             * 
             */
            void updateAABB(void);

            /**
             * Generates the GFX buffers (VBO) from the model data, this is for all shapes
             * in the model. Also depending functions will be called for any kind of data
             * (AoS/SoA/Triangles/TriangleStrip)
             * @return      FG_TRUE if the buffers were generated successfully, FG_FALSE
             *              otherwise
             */
            fgBool genBuffers(void);

            /**
             * Deletes/releases the GFX buffers (VBO)
             * @return      FG_TRUE if the buffers were released successfully, FG_FALSE
             *              otherwise. In most cases FG_FALSE will be returned if the 
             *              model data was not even loaded or the buffers were not valid
             */
            fgBool deleteBuffers(void);

            //------------------------------------------------------------------
            /**
             * Gets the main override material of the model resource
             * @return      Pointer to the override material for all shapes
             */
            inline SMaterial* getMainMaterial(void) const {
                return m_materialOverride;
            }
            /**
             * Gets the specific model type identifier
             * @return  Unsigned int value indicating model type (based of file extension)
             */
            inline ModelType getModelType(void) const {
                return m_modelType;
            }
            /**
             * Returns whether the model contains animations
             * @return  FG_TRUE if the model contains animations, FG_FALSE otherwise.
             */
            inline fgBool isAnimated(void) const {
                return (fgBool)!!(m_modelFlags & ANIMATED);
            }
            /**
             * Returns whether the model is rigged
             * @return  FG_TRUE if the model is rigged for animation,
             *          FG_FALSE otherwise.
             */
            inline fgBool isRigged(void) const {
                return (fgBool)!!(m_modelFlags & RIGGED);
            }
            /**
             * Returns whether the model is multi-textured
             * @return  FG_TRUE if the model is multi-textured, FG_FALSE otherwise
             */
            inline fgBool isMultitextured(void) const {
                return (fgBool)!!(m_modelFlags & MULTITEXTURED);
            }
            /**
             * Returns whether model is textured
             * @return  FG_TRUE if the model has any kind of texture in it (and likely
             *          texture coordinates data), FG_FALSE otherwise
             */
            inline fgBool isTextured(void) const {
                return (fgBool)!!(m_modelFlags & TEXTURED);
            }
            /**
             * Returns whether the model has any kind of material
             * @return  FG_TRUE if the loaded model defined any kind of material,
             *          FG_FALSE otherwise. Note that when this function returns FG_FALSE,
             *          the main material (override) is still available and set to defaults
             */
            inline fgBool hasMaterial(void) const {
                return (fgBool)!!(m_modelFlags & HAS_MATERIALS);
            }
            /**
             * Returns whether the data in the model is interleaved
             * @return  FG_TRUE if the data is interleaved, FG_FALSE otherwise
             */
            inline fgBool isInterleaved(void) const {
                return (fgBool)!!(m_modelFlags & INTERLEAVED);
            }
            /**
             * Sets the data to be interleaved 
             * @param toggle    Boolean parameter to which the internal flag will be set.
             * @remarks         If the value was changed, the change in the data to take
             *                  effect requires explicit reload of the model file
             */
            inline void setInterleaved(fgBool toggle = FG_TRUE) {
                setFlag(INTERLEAVED, toggle);
            }
            /**
             * Number of vertices
             * @return 
             */
            inline fgGFXuint getNumVertices(void) const {
                return m_numVertices;
            }
            /**
             * Number of normals
             * @return 
             */
            inline fgGFXuint getNumNormals(void) const {
                return m_numNormals;
            }
            /**
             * Number of UVs - texture coords
             * @return 
             */
            inline fgGFXuint getNumUVs(void) const {
                return m_numUVs;
            }
            /**
             * Number of indices
             * @return 
             */
            inline fgGFXuint getNumIndices(void) const {
                return m_numIndices;
            }
            /**
             * Number of triangles
             * @return 
             */
            inline fgGFXuint getNumTriangles(void) const {
                return m_numTriangles;
            }
            /**
             * Number of all polygons in the model
             * @return 
             */
            inline fgGFXuint getNumPolygons(void) const {
                return m_numPolygons;
            }
            /**
             * Number of shapes used in the model
             * @return 
             */
            inline fgGFXuint getNumShapes(void) const {
                return m_numShapes;
            }
            /**
             * Get number of materials used by this model
             * @return 
             */
            inline fgGFXuint getNumMaterials(void) const {
                return m_numMaterials;
            }
            /**
             * Return pointer to the array holding specific info
             * @return 
             */
            inline const fgGFXuint* getNumData(void) const {
                return m_numData;
            }

        protected:
            /// Global material override definition
            SMaterial *m_materialOverride;
            /// Array holding all basic shapes of the model
            ShapesVec m_shapes;
            /// Main bounding box - it's for whole model (all shapes)
            AABoundingBox3Df m_aabb;
            /// Identifier of the model type - based on the input data file extension
            ModelType m_modelType;
            /// Model internal flags (on/off info)
            ModelFlags m_modelFlags;

            union {

                struct {

                    union {
                        /// Number of vertices in the model
                        fgGFXuint m_numVertices;
                        /// Number of points in the model
                        fgGFXuint m_numPoints;
                    };
                    /// Number of all normal coords in the model
                    fgGFXuint m_numNormals;
                    /// Number of all texture coords (in all meshes/shapes)
                    fgGFXuint m_numUVs;
                    /// Number of indices
                    fgGFXuint m_numIndices;
                    /// Number of triangles in all meshes
                    fgGFXuint m_numTriangles;
                    /// Number of all polygons
                    fgGFXuint m_numPolygons;
                    /// Number of shapes in the model
                    fgGFXuint m_numShapes;
                    /// Number of used materials
                    fgGFXuint m_numMaterials;
                }; // unnamed struct
                /// Special array containing all data (number of specific vertex data)
                fgGFXuint m_numData[8];
            }; // unnamed union

        protected:
    #if defined(FG_USING_ASSIMP)
            /// Importer instance - it's destroyed when the last ModelResource
            /// object is destroyed
            static ::Assimp::Importer* s_objImporter;
    #endif

        private:
            /// Internal count of CModelResource instances
            static int s_cmrInstanceCount;

        }; // class CModelResource

        FG_ENUM_FLAGS(CModelResource::ModelFlags);
        /**
         * 
         * @param flags
         * @param toggle
         */
        inline void CModelResource::setFlag(const ModelFlags flags, const fgBool toggle) {
            if(toggle) {
                m_modelFlags |= flags;
            } else {
                m_modelFlags |= flags;
                m_modelFlags ^= flags;
            }
        }

        typedef CModelResource CModel;
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_MODEL_RESOURCE_BLOCK
#endif /* FG_INC_GFX_MODEL_RESOURCE */
