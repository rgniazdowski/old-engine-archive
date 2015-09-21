/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#ifndef FG_INC_RESOURCE
    #define FG_INC_RESOURCE
    #define FG_INC_RESOURCE_BLOCK

    #include "Hardware/fgQualityTypes.h"

    #include <string>
    #include <ctime>
    #include <cstring>

    #include "fgManagerBase.h"
    #include "fgManagedDataFile.h"
    #include "Util/fgHandle.h"
    #include "Util/fgTag.h"

namespace fg {
    namespace resource {
        class CResourceManager;
        class CResourceGroup;
        class CResource;
    };
};

    #define FG_TAG_RESOURCE_NAME        "Resource"
    #define FG_TAG_RESOURCE             FG_TAG_TYPE(fg::resource::CResource)
FG_TAG_TEMPLATE_ID_AUTO(fg::resource::CResource, FG_TAG_RESOURCE_NAME);

////////////////////////////////////////////////////////////////////////////////

    #define FG_RESOURCE_INVALID_TEXT            "Invalid"
    #define FG_RESOURCE_SOUND_TEXT              "Sound"
    #define FG_RESOURCE_MUSIC_TEXT              "Music"
    #define FG_RESOURCE_3D_MODEL_TEXT           "3DModel"
    #define FG_RESOURCE_TEXTURE_TEXT            "Texture"
    #define FG_RESOURCE_FONT_TEXT               "Font"
    #define FG_RESOURCE_SAVE_FILE_TEXT          "SaveFile"
    #define FG_RESOURCE_GUI_STRUCTURE_SHEET_TEXT    "GuiStructureSheet" // #FIXME
    #define FG_RESOURCE_GUI_STYLE_SHEET_TEXT        "GuiStyleSheet" // #FIXME
    #define FG_RESOURCE_SHADER_TEXT             "Shader" // #FIXME
    #define FG_RESOURCE_SCENE_TEXT              "Scene"
    #define FG_RESOURCE_SCRIPT_TEXT             "Script"
    #define FG_RESOURCE_GROUP_TEXT              "ResourceGroup"
    #define FG_RESOURCE_VARIA_TEXT              "Varia"
    #define FG_RESOURCE_BINARY_TEXT             "Binary"
    #define FG_RESOURCE_LIBRARY_TEXT            "Library"
    #define FG_RESOURCE_PLUGIN_TEXT             "Plugin"
    #define FG_RESOURCE_CUSTOM_TEXT             "Custom"
    #define FG_RESOURCE_ZIP_PACK_TEXT           "ZipPack"
    #define FG_RESOURCE_PARTICLE_EFFECT_TEXT    "ParticleEffect"

////////////////////////////////////////////////////////////////////////////////

    #define FG_RESOURCE                         0x0BBB
    #define FG_RESOURCE_TEXT                    "Resource"

////////////////////////////////////////////////////////////////////////////////
/*
 *
 */

// ## ### #FIXME ## ## ## !! ! ! ! ! 

// Text (string version) for the resource low priority enum
    #define FG_RES_PRIORITY_LOW_TEXT            "low"
// Text (string version) for the resource medium priority enum
    #define FG_RES_PRIORITY_MEDIUM_TEXT         "medium"
// Text (string version) for the resource high priority enum
    #define FG_RES_PRIORITY_HIGH_TEXT           "high"
// Text (string version_ for the resource invalid priority enum
    #define FG_RES_PRIORITY_INVALID_TEXT        "invalid"

namespace fg {

    namespace resource {

        ///
        typedef FG_TAG_RESOURCE ResourceTag;
        ///
        typedef fg::util::CHandle<ResourceTag> ResourceHandle;

        /**
         * Enumeration for resource priority (low, medium, high)
         */
        enum class ResourcePriority : char {
            ///
            INVALID = ((char)(-1)),

            ///
            LOW = 0,
            ///
            MEDIUM = 1,
            ///
            HIGH = 2,

            ///
            RESERVED1 = 3,
            ///
            RESERVED2 = 4,
            ///
            RESERVED3 = 5
        };

        /// Enum type holding all possible resource types in the game engine
        typedef unsigned int ResourceType;

        /// Auto resource type
        const ResourceType AUTO = 0x0000;
        /// Invalid resource type
        const ResourceType INVALID = 0x0000;

        /// Sound resource
        const ResourceType SOUND = 0x0AB0;
        /// Music resource
        const ResourceType MUSIC = 0x0AB1;
        /// Model resource - any type
        const ResourceType MODEL3D = 0x0AB2;
        /// Texture resource
        const ResourceType TEXTURE = 0x0AB3;
        /// Font resource
        const ResourceType FONT = 0x0AB4;
        /// Game save file - automation 
        const ResourceType SAVE_FILE = 0x0AB5;
        /// GUI structure sheet - unused for now
        const ResourceType GUI_STRUCTURE_SHEET = 0x0AB6; // #FIXME
        /// GUI style sheet resource - unused for now
        const ResourceType GUI_STYLE_SHEET = 0x0AB7; // #FIXME
        /// Shader resource - unused for now
        const ResourceType SHADER = 0x0AB8; // #FIXME
        /// Scene definition resource
        const ResourceType SCENE = 0x0AB9;
        /// Script resource
        const ResourceType SCRIPT = 0x0ABA;
        /// Resource group
        const ResourceType GROUP = 0x0ABB;
        /// Varia resource
        const ResourceType VARIA = 0x0ABC;
        /// Binary resource
        const ResourceType BINARY = 0x0ABD;
        /// Library resource
        const ResourceType LIBRARY = 0x0ABE;
        /// Plugin resource
        const ResourceType PLUGIN = 0x0ABF;
        /// Custom resource type - reserved
        const ResourceType CUSTOM = 0x0AC0;
        /// Special resource - zip pack
        const ResourceType ZIP_PACK = 0x0AC1;
        /// Particle effect resource - loaded from file
        const ResourceType PARTICLE_EFFECT = 0x0AC2;

        /// Number of all basic resource types (without built-in)
        const ResourceType NUM_RESOURCE_BASIC_TYPES = (ZIP_PACK - SOUND);

        /// Reserved resource type
        const ResourceType RESERVED1 = 0x0ACA;
        /// Reserved resource type
        const ResourceType RESERVED2 = 0x0ACB;
        /// Reserved resource type
        const ResourceType RESERVED3 = 0x0ACC;
        /// Reserved resource type
        const ResourceType RESERVED4 = 0x0ACD;
        /// Reserved resource type
        const ResourceType RESERVED5 = 0x0ACE;
        /// Reserved resource type
        const ResourceType RESERVED6 = 0x0ACF;

        /// Number of all resource types - built in
        const ResourceType NUM_RESOURCE_TYPES = (RESERVED6 - SOUND);
        /**
         * 
         * @param resourceType
         * @return 
         */
        inline const char* getResourceTypeName(ResourceType resourceType) {
            const char* returnText = FG_RESOURCE_INVALID_TEXT;
            switch(resourceType) {
                case SOUND:
                    returnText = FG_RESOURCE_SOUND_TEXT;
                    break;
                case MUSIC:
                    returnText = FG_RESOURCE_MUSIC_TEXT;
                    break;
                case MODEL3D:
                    returnText = FG_RESOURCE_3D_MODEL_TEXT;
                    break;
                case TEXTURE:
                    returnText = FG_RESOURCE_TEXTURE_TEXT;
                    break;
                case FONT:
                    returnText = FG_RESOURCE_FONT_TEXT;
                    break;
                case SAVE_FILE:
                    returnText = FG_RESOURCE_SAVE_FILE_TEXT;
                    break;
                case GUI_STRUCTURE_SHEET:
                    // #FIXME
                    returnText = FG_RESOURCE_GUI_STRUCTURE_SHEET_TEXT;
                    break;
                case GUI_STYLE_SHEET:
                    // #FIXME
                    returnText = FG_RESOURCE_GUI_STYLE_SHEET_TEXT;
                    break;
                case SHADER:
                    // #FIXME
                    returnText = FG_RESOURCE_SHADER_TEXT;
                    break;
                case SCENE:
                    returnText = FG_RESOURCE_SCENE_TEXT;
                    break;
                case SCRIPT:
                    returnText = FG_RESOURCE_SCRIPT_TEXT;
                    break;
                case GROUP:
                    returnText = FG_RESOURCE_GROUP_TEXT;
                    break;
                case VARIA:
                    returnText = FG_RESOURCE_VARIA_TEXT;
                    break;
                case BINARY:
                    returnText = FG_RESOURCE_BINARY_TEXT;
                    break;
                case LIBRARY:
                    returnText = FG_RESOURCE_LIBRARY_TEXT;
                    break;
                case PLUGIN:
                    returnText = FG_RESOURCE_PLUGIN_TEXT;
                    break;
                case CUSTOM:
                    returnText = FG_RESOURCE_CUSTOM_TEXT;
                    break;
                case ZIP_PACK:
                    returnText = FG_RESOURCE_ZIP_PACK_TEXT;
                    break;
                case PARTICLE_EFFECT:
                    returnText = FG_RESOURCE_PARTICLE_EFFECT_TEXT;
                    break;
                default:
                    returnText = FG_RESOURCE_INVALID_TEXT;
                    break;
            }
            return returnText;
        }
        /**
         * 
         * @param text
         * @return 
         */
        inline ResourceType getResourceTypeFromText(const char* text) {

            if(!text)
                return fg::resource::INVALID;
            // # #FIXME !
            if(strncasecmp(text, FG_RESOURCE_INVALID_TEXT, strlen(FG_RESOURCE_INVALID_TEXT)) == 0) {
                return fg::resource::INVALID;
            } else if(strncasecmp(text, FG_RESOURCE_SOUND_TEXT, strlen(FG_RESOURCE_SOUND_TEXT)) == 0) {
                return fg::resource::SOUND;
            } else if(strncasecmp(text, FG_RESOURCE_MUSIC_TEXT, strlen(FG_RESOURCE_MUSIC_TEXT)) == 0) {
                return fg::resource::MUSIC;
            } else if(strncasecmp(text, FG_RESOURCE_3D_MODEL_TEXT, strlen(FG_RESOURCE_3D_MODEL_TEXT)) == 0) {
                return fg::resource::MODEL3D;
            } else if(strncasecmp(text, FG_RESOURCE_TEXTURE_TEXT, strlen(FG_RESOURCE_TEXTURE_TEXT)) == 0) {
                return fg::resource::TEXTURE;
            } else if(strncasecmp(text, FG_RESOURCE_FONT_TEXT, strlen(FG_RESOURCE_FONT_TEXT)) == 0) {
                return fg::resource::FONT;
            } else if(strncasecmp(text, FG_RESOURCE_SAVE_FILE_TEXT, strlen(FG_RESOURCE_SAVE_FILE_TEXT)) == 0) {
                return fg::resource::SAVE_FILE;
            } else if(strncasecmp(text, FG_RESOURCE_SCENE_TEXT, strlen(FG_RESOURCE_SCENE_TEXT)) == 0) {
                return fg::resource::SCENE;
            } else if(strncasecmp(text, FG_RESOURCE_SCRIPT_TEXT, strlen(FG_RESOURCE_SCRIPT_TEXT)) == 0) {
                return fg::resource::SCRIPT;
            } else if(strncasecmp(text, FG_RESOURCE_GROUP_TEXT, strlen(FG_RESOURCE_GROUP_TEXT)) == 0) {
                return fg::resource::GROUP;
            } else if(strncasecmp(text, FG_RESOURCE_VARIA_TEXT, strlen(FG_RESOURCE_VARIA_TEXT)) == 0) {
                return fg::resource::VARIA;
            } else if(strncasecmp(text, FG_RESOURCE_BINARY_TEXT, strlen(FG_RESOURCE_BINARY_TEXT)) == 0) {
                return fg::resource::BINARY;
            } else if(strncasecmp(text, FG_RESOURCE_LIBRARY_TEXT, strlen(FG_RESOURCE_LIBRARY_TEXT)) == 0) {
                return fg::resource::LIBRARY;
            } else if(strncasecmp(text, FG_RESOURCE_PLUGIN_TEXT, strlen(FG_RESOURCE_PLUGIN_TEXT)) == 0) {
                return fg::resource::PLUGIN;
            } else if(strncasecmp(text, FG_RESOURCE_CUSTOM_TEXT, strlen(FG_RESOURCE_CUSTOM_TEXT)) == 0) {
                return fg::resource::CUSTOM;
            } else if(strncasecmp(text, FG_RESOURCE_ZIP_PACK_TEXT, strlen(FG_RESOURCE_ZIP_PACK_TEXT)) == 0) {
                return fg::resource::ZIP_PACK;
            } else if(strncasecmp(text, FG_RESOURCE_PARTICLE_EFFECT_TEXT, strlen(FG_RESOURCE_PARTICLE_EFFECT_TEXT)) == 0) {
                return fg::resource::PARTICLE_EFFECT;
            }
            //FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_GUI_STRUCTURE_SHEET);   // #FIXME
            //FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_GUI_STYLE_SHEET);       // #FIXME
            //FG_RETURN_ENUM_IF_TEXT_EQ(FG_RESOURCE_SHADER);                // #FIXME
            return fg::resource::INVALID;
        }
        /**
         * 
         * @param text
         * @return 
         */
        inline ResourcePriority getResourcePriorityFromText(const char* text) {
            if(!text)
                return ResourcePriority::INVALID;

            if(strncasecmp(text, FG_RES_PRIORITY_INVALID_TEXT, strlen(FG_RES_PRIORITY_INVALID_TEXT)) == 0) {
                return ResourcePriority::INVALID;
            }
            if(strncasecmp(text, FG_RES_PRIORITY_LOW_TEXT, strlen(FG_RES_PRIORITY_LOW_TEXT)) == 0) {
                return ResourcePriority::LOW;
            }
            if(strncasecmp(text, FG_RES_PRIORITY_MEDIUM_TEXT, strlen(FG_RES_PRIORITY_MEDIUM_TEXT)) == 0) {
                return ResourcePriority::MEDIUM;
            }
            if(strncasecmp(text, FG_RES_PRIORITY_HIGH_TEXT, strlen(FG_RES_PRIORITY_HIGH_TEXT)) == 0) {
                return ResourcePriority::HIGH;
            }
            //FG_RETURN_ENUM_IF_TEXT_EQ(ResourcePriority::INVALID);
            //FG_RETURN_ENUM_IF_TEXT_EQ(ResourcePriority::LOW);
            //FG_RETURN_ENUM_IF_TEXT_EQ(ResourcePriority::MEDIUM);
            //FG_RETURN_ENUM_IF_TEXT_EQ(ResourcePriority::HIGH);
            return ResourcePriority::INVALID;
        }

        /**
         * Base class for resource
         */
        class CResource : public CManagedDataFile<ResourceHandle, Quality> {
            friend class CResourceManager;
            friend class CResourceGroup;

        public:
            ///
            typedef CManagedDataFile<ResourceHandle, Quality> base_type;
            ///
            typedef ResourceTag tag_type;
            ///
            typedef ResourceHandle handle_type;
            ///
            typedef Quality quality_type;

        public:
            /**
             *  Base constructor of the resource object
             */
            CResource();
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CResource(const char *path);
            /**
             * Constructor with additional parameter (path)
             * @param path
             */
            CResource(const std::string& path);
            /**
             * Destructor of the resource object
             */
            virtual ~CResource() { }

        protected:
            /**
             * Clears the class data, this actually does not free allocated memory,
             * just resets base class attributes
             */
            virtual void clear(void);

        public:
            /**
             * Create and destroy functions.  Note that the create() function of the
             * derived class does not have to exactly match the base class.  No assumptions
             * are made regarding parameters.
             * create() function should simply be overloaded to call any proper loading function,
             * which will load/interpret data from file in ROM and place it in RAM memory.
             * 
             * @return 
             */
            virtual fgBool create(void) = 0;
            /**
             * Destroy all loaded data including additional metadata (called with destructor)
             */
            virtual void destroy(void) {
                CResource::clear();
            };
            /**
             * Dispose and recreate must be able to discard and then completely recreate
             * the data contained in the class with no additional parameters
             * This functions should NOT be overloaded to have different number of parameters.
             * @return 
             */
            virtual fgBool recreate(void) = 0;
            /**
             * Dispose completely of the all loaded data, free all memory
             */
            virtual void dispose(void) = 0;
            /**
             * Return the size of the data actually loaded inside the class
             * @return 
             */
            virtual size_t getSize(void) const {
                return m_size;
            }
            /**
             * Return true if the data exists (it's loaded and ready)
             * @return 
             */
            virtual fgBool isDisposed(void) const = 0;
            /**
             * 
             * @param flags
             */
            inline virtual void setFlags(const char *flags) {
                setFlags(std::string(flags));
            }
            /**
             * 
             * @param flags
             */
            inline virtual void setFlags(const std::string& flags) { }

            // These functions set the parameters by which the sorting operator determines
            // in what order resources are discarded
            /**
             * Set the resource priority
             * @param priority
             */
            inline void setPriority(ResourcePriority priority) {
                m_priority = priority;
            }
            /**
             * Get the resource priority
             * @return 
             */
            inline ResourcePriority getPriority(void) const {
                return m_priority;
            }
            /**
             * Set the resource quality
             * @param quality
             */
            inline void setQuality(Quality quality) {
                m_quality = quality;
            }
            /**
             * Get the resource quality
             * @return 
             */
            inline Quality getQuality(void) const {
                return m_quality;
            }
            /**
             * Get the resource type id
             * @return 
             */
            inline ResourceType getResourceType(void) const {
                return m_resType;
            }
            /**
             * 
             * @return
             */
            inline const char* getCurrentFilePathStr(void) const {
                return base_type::getFilePathStr(this->m_quality);
            }
            /**
             *
             * @return
             */
            inline std::string& getCurrentFilePath(void) {
                return base_type::getFilePath(this->m_quality);
            }
            /**
             *
             * @return
             */
            inline std::string const& getCurrentFilePath(void) const {
                return base_type::getFilePath(this->m_quality);
            }

        protected:
            /**
             * Set the reference counter for the resource
             * @param nCount
             */
            inline void setReferenceCount(unsigned int nCount) {
                m_nRefCount = nCount;
            }

        public:
            /**
             * Return the current hit of the reference counter for the resource
             * @return 
             */
            inline unsigned int getReferenceCount(void) const {
                return m_nRefCount;
            }
            /**
             * Check if the resource is locked (reference counter is not zero)
             * @return 
             */
            inline fgBool isLocked(void) const {
                return (m_nRefCount > 0) ? FG_TRUE : FG_FALSE;
            }
            /**
             * Set the last access time
             * @param lastAccess
             */
            inline void setLastAccess(time_t lastAccess) {
                m_lastAccess = lastAccess;
            }
            /**
             * Return the current access time of the resource
             * @return 
             */
            inline time_t getLastAccess(void) const {
                return m_lastAccess;
            }

            /**
             * The less-than operator defines how resources get sorted for discarding.
             * @param container
             * @return 
             */
            virtual bool operator <(CResource& container);
            /**
             * The greater-than operator is used for comparison (eg. while sorting)
             * @param container
             * @return 
             */
            virtual bool operator >(CResource& container);

            // Well using reference count as simple as below is not recommended, it is more difficult
            // to handle in the end, dims the code etc., can cause many problems. Need to migrate to
            // smart pointers... using boost or some implementation #FIXME #P3 #TODO
        protected:
            /**
             * Increase the reference count
             * @return 
             */
            inline unsigned int upRef(void) {
                m_nRefCount++;
                return m_nRefCount;
            }
            /**
             * Decrease the reference count
             * @return 
             */
            inline unsigned int downRef(void) {
                if(m_nRefCount > 0) m_nRefCount--;
                return m_nRefCount;
            }
            /**
             * Lock the resource (reference counter +1)
             * @return 
             */
            virtual unsigned int Lock(void) {
                return upRef();
            }
            /**
             * Unlock the resource (reference counter -1)
             * @return 
             */
            virtual unsigned int Unlock(void) {
                return downRef();
            }
            /**
             * Unlock completely the resource (reference counter = 0) #NOTSAFE #FIXME
             */
            virtual void ZeroLock(void) {
                m_nRefCount = 0;
            }

        protected:
            /// Priority of this resource
            ResourcePriority m_priority;
            /// Quality of the resource
            Quality m_quality;
            /// Resource type
            ResourceType m_resType;
            /// Number of references to this resource
            unsigned int m_nRefCount;
            /// Time of last access, may become handy #TESTME
            time_t m_lastAccess;
            /// Size in bytes of the loaded data
            size_t m_size;
            /// Is the resource loaded and ready to be used in program?
            fgBool m_isReady;

        }; // class CResource

    } // namespace resource
} // namespace fg

    #undef FG_INC_RESOURCE_BLOCK
#endif /* FG_INC_RESOURCE */
