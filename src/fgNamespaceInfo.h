/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_NAMESPACE_INFO
    #define FG_INC_NAMESPACE_INFO

/**
 * Main FlexiGame Engine namespace. Contains every FlexiGame class, structure,
 * enum, function.
 */
namespace fg {

    /**
     * Special namespace for android specific functions used with or without NDK/Java
     */
    namespace android {
    }
    /**
     * Namespace holding base abstract classes for the whole engine.
     */
    namespace base {
    }
    /**
     * Contains special helper functions and arrays for builtin color definitions.
     * Those colors are standard with standard HTML names. Useful mainly in the GUI subsystem.
     */
    namespace colors {
    }
    /**
     * Event management, callbacks, argument lists
     */
    namespace event {
    }
    /**
     * Game logic management
     */
    namespace game {
    }
    /**
     * GFX namespace contains 2D/3D graphics related objects and classes.
     * Designed mostly for OpenGL and OpenGL ES.
     */
    namespace gfx {
        /**
         * Definitions for base abstract classes needed for the GFX subsystem.
         */
        namespace base {
        }
        /**
         * Special namespace for holding information about current GFX context.
         * Works as a special kind of cache for client and server side.
         */
        namespace context {
        }
        /**
         * Platform/system dependent initialization functions.
         */
        namespace platform {
        }        
        /**
         * Animations and mesh skinning.
         */
        namespace anim {
            
        }
        /**
         * Holds additional functions for easier conversion between FG and
         * Assimp various data types.
         */
        namespace assimp_helper {

        }

    }
    /**
     * GUI namespace contains every class related to the graphical interface.
     */
    namespace gui {
        /**
         * Helper namespace holding builtin fonts - they're compiled into the engine as fallback.
         */
        namespace font {
        }
    }
    /**
     * Log namespace contains functions used for writing detailed output - used mainly for debugging and info.
     */
    namespace log {
    }
    /**
     * Namespace holding math specific structures and functions. When using GLM
     * (OpenGL Mathematics Library) this namespace is a wrapper for ::glm.
     */
    namespace math {
        /**
         * Namespace which contains more detailed functions/templates - based on GLM.
         */
        namespace detail {
        }
    }
    /**
     * Message namespace - message/status related structures.
     */
    namespace msg {
    }
    /**
     * Path namespace - contains path manipulation specific functions (global)
     */
    namespace path {
    }
    /**
     * The physics namespace includes all bullet specific classes functions.
     * It is defined as a namespace to allow function and class names to be
     * simple without causing conflicts.
     */
    namespace physics {

        /**
         * Holds dditional functions for easier conversion between FG and
         * Bullet various data types.
         */
        namespace bullet_helper {

        }
    }
    /**
     * Namespace holds classes for engine profiling
     */
    namespace profile {
    }
    /**
     * Resource namespace - everything related with resource management is in here.
     */
    namespace resource {
    }
    /**
     * Script namespace - everything related with script loading and object binding 
     */
    namespace script {
    }
    /**
     * SFX namespace - sound effects, sound/music management - audio subsystem.
     */
    namespace sfx {
        /**
         * Base namespace contains base abstract classes needed in the audio subsystem.
         */
        namespace base {
        }
    }
    /**
     * Strings namespace is for functions related to string manipulation.
     */
    namespace strings {
    }
    /**
     * Namespace containing functions designed for precise time measurement.
     */
    namespace timesys {
    }
    /**
     * Utilities namespace - classes for config and file loading, tags, handles, zip archives.
     */
    namespace util {
        /**
         * Base namespace for the Util namespace
         */
        namespace base {
        }
        /**
         * Config namespace - helper namespace holding typedefs for config specific vectors.
         */
        namespace config {
        }
        /**
         * Tag helper namespace - additional functions hidden in here for Tag structures.
         */
        namespace tag_helper {
        }
        /**
         * Contains ready to use various hash functions.
         */
        namespace hash {
        }
    }
    /**
     * XML namespace holds every class needed in XML manipulations (requires tinyxml)
     */
    namespace xml {
    }
}

#endif	/* FG_INC_NAMESPACE_INFO */
