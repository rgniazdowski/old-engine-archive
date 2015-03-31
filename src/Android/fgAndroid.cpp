/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************************************/

#include "fgAndroid.h"
#include "fgLog.h"

using namespace fg;
#if defined(FG_USING_PLATFORM_ANDROID)

/**
 * 
 * @return 
 */
AAssetManager* android::getAssetManager(void) {
#if defined(FG_USING_SDL2)
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jclass sdlClass = env->FindClass("org/libsdl/app/SDLActivity");

    if(sdlClass == 0) {
        FG_LOG_ERROR("org/libsdl/app/SDLActivity not found.");
        return NULL;
    }

    jfieldID mAssetMgr = env->GetStaticFieldID(sdlClass,
                                               "mAssetMgr",
                                               "Landroid/content/res/AssetManager;");

    if(mAssetMgr == 0) {
        FG_LOG_ERROR("Could not find mAssetMgr.");
        return NULL;
    }

    jobject assets = env->GetStaticObjectField(sdlClass, mAssetMgr);
    if(assets == 0) {
        FG_LOG_ERROR("Could not get mAssetMgr.");
        return NULL;
    }

    env->DeleteLocalRef(sdlClass);

    return AAssetManager_fromJava(env, assets);
#else
    return NULL;
#endif /* FG_USING_SDL2 */
}

/**
 * 
 * @return 
 */
JNIEnv* android::getEnv(void) {
#if defined(FG_USING_SDL2)
    return (JNIEnv*)SDL_AndroidGetJNIEnv();
#else
    return NULL;
#endif
}

/**
 * 
 * @return 
 */
const char* android::getInternalDataStorage(void) {
#if defined(FG_USING_SDL2)
    return SDL_AndroidGetInternalStoragePath();
#else
    return NULL;
#endif
}

/**
 * 
 * @return 
 */
const char* android::getExternalDataStorage(void) {
#if defined(FG_USING_SDL2)
    return SDL_AndroidGetExternalStoragePath();
#else
    return NULL;
#endif
}

/**
 *
 * @return 
 */
jobject android::getActivityObject(void) {
#if defined(FG_USING_SDL2)
    return (jobject)SDL_AndroidGetActivity();
#else
    return jobject();
#endif /* FG_USING_SDL2 */
}

/**
 *
 * @return
 */
jclass android::getActivityClass(void) {
#if defined(FG_USING_SDL2)
    // retrieve the JNI environment.
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();

    // retrieve the Java instance of the SDLActivity
    jobject activity = (jobject)SDL_AndroidGetActivity();

    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz(env->GetObjectClass(activity));
    return clazz;
#else
    return jclass();
#endif
}

#endif /* FG_USING_PLATFORM_ANDROID */
