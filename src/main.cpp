/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgBuildConfig.h"
#if defined(FG_USING_SDL2)
#include "fgSDLApplication.h"
#endif
#if defined(FG_USING_PLATFORM_ANDROID)
#include "Android/fgAndroid.h"
#endif

#include "fgEngineMain.h"
#include "fgLog.h"
#include "Util/fgStrings.h"

using namespace fg;
//------------------------------------------------------------------------------

#if !defined(FG_STATIC_LIBRARY)

/**
 * Main function that is called when the program starts.
 */
#if defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)

extern "C" int SDL_main(int argc, char **argv) {
#else

/**
 * Main function that is called when the program starts.
 * @param argc Number of the arguments passed to the executable
 * @param argv Array containing the arguments
 * @return
 */
extern "C" int main(int argc, char *argv[]) {
#endif /* FG_USING_PLATFORM_ANDROID */

    timesys::init();
    FG_LOG_DEBUG("%s: Starting up!", FG_PACKAGE_FULL_TEXT);
    FG_LOG_DEBUG("%s: build %s %s DEBUG", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#if defined(FG_RELEASE)
    FG_LOG_INFO("%s: build %s %s RELEASE", FG_PACKAGE_NAME, FG_BUILD_TIME, FG_BUILD_DATE);
#endif

#if defined(FG_DEBUG)
    FG_LOG_DEBUG("%s: Number of arguments: %d", FG_PACKAGE_NAME, argc);
    if(argc) {
        for(int i = 0; i < argc; i++) {
            FG_LOG_DEBUG("%s: ARGV[%d] = '%s'", FG_PACKAGE_NAME, i, argv[i]);
        }
    }

#if defined(FG_USING_PLATFORM_ANDROID)
    FG_LOG_DEBUG("DATA INTERNAL STORAGE PATH: %s", android::getInternalDataStorage());
    FG_LOG_DEBUG("DATA EXTERNAL STORAGE PATH: %s", android::getExternalDataStorage());
    util::CRegularFile defaultProfile;
    std::string path;
    path.append(android::getInternalDataStorage());
    path.append("/defaultProfile.log");
    char *profileData = defaultProfile.load(path.c_str());
    FG_LOG_DEBUG("DATA PROFILE: %s", profileData);
    fgFree(profileData);
    defaultProfile.close();
#endif /* FG_USING_PLATFORM_ANDROID */

#endif /* FG_DEBUG */
    CApplication *mainModule = NULL;

#if defined(FG_USING_SDL2)
    mainModule = new CSDLApplication(argc, argv);
#else
    FG_LOG_ERROR("EMPTY APPLICATION!\n");
    return FG_FALSE;
#endif

    if(!mainModule->initProgram()) {
        mainModule->closeProgram();
        FG_LOG_DEBUG("Deleting main module...");
        delete mainModule;
        FG_LOG_ERROR("Initialization failed, closing program with error");
        return 1;
    }
    // DEVICE YIELD FUNCTION IN HERE

    while(FG_TRUE) {
        fgBool status = mainModule->mainLoopStep();
        // DEVICE YIELD FUNCTION IN HERE
        if(status == FG_FALSE || mainModule->isExit()) {
            FG_LOG_DEBUG("Main loop break...");
            break;
        }
    }
    mainModule->closeProgram();
    FG_LOG_DEBUG("Deleting main module...");
    delete mainModule;

    FG_LOG_INFO("Successfully closed program");
    return 0;
}
#endif /* !defined(FG_STATIC_LIBRARY) */
