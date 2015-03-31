/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_ANDROID_ANDROID_MAIN
    #define FG_INC_ANDROID_ANDROID_MAIN
    #define FG_INC_ANDROID_ANDROID_MAIN_BLOCK

    #include "fgBuildConfig.h"
    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
    #endif
    #if defined(FG_USING_PLATFORM_ANDROID)
        #include <jni.h>
        #include <android/asset_manager_jni.h>
        #include <android/asset_manager.h>

        #ifdef __cplusplus
extern "C" {
        #endif

    struct AAssetManager;

        #ifdef __cplusplus
};
        #endif
    #endif

namespace fg {
    namespace android {
    #if defined(FG_USING_PLATFORM_ANDROID)
        /**
         * 
         * @return 
         */
        AAssetManager* getAssetManager(void);
        /**
         * 
         * @return 
         */
        JNIEnv* getEnv(void);
        /**
         * 
         * @return 
         */
        const char* getInternalDataStorage(void);
        /**
         * 
         * @return 
         */
        const char* getExternalDataStorage(void);

        /**
         *
         */
        jobject getActivityObject(void);
        /**
         *
         */
        jclass getActivityClass(void);

    #endif
    }
}

    #undef FG_INC_ANDROID_ANDROID_MAIN_BLOCK
#endif /* FG_INC_ANDROID_ANDROID_MAIN */