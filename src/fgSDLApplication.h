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
 * File:   fgSDLApplication.h
 * Author: vigilant
 *
 * Created on January 3, 2016, 1:32 AM
 */

#ifndef FG_INC_SDL_APPLICATION
    #define FG_INC_SDL_APPLICATION
    #define FG_INC_SDL_APPLICATION_BLOCK

    #include "fgBuildConfig.h"
    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
        #include "fgApplication.h"
        #include "Event/fgKeyboard.h"

namespace fg {

    /**
     * 
     */
    class CSDLApplication : public CApplication {
    public:
        typedef CApplication base_type;
        typedef CSDLApplication self_type;
        typedef CSDLApplication type;

    public:
        CSDLApplication(int argc, char* argv[]);
        virtual ~CSDLApplication();

        static int SDLCALL filterSDLEvents(void* userdata, SDL_Event* event);

    private:
        CSDLApplication(const CSDLApplication& orig);
        static event::KeyVirtualCode translateKeyboardCode(const SDL_KeyboardEvent& event);
        SDL_EventType checkSDLEvents(void);

    protected:
        virtual fgBool customPreInitStep(void);
        virtual void customPostInitStep(void);

        virtual void customPreLoopStep(void);
        virtual void customPostLoopStep(void);

        virtual void customPreQuitStep(void);
        virtual void customPostQuitStep(void);

    private:

    }; // class CSDLApplication

} // namespace fg

    #endif /* FG_USING_SDL2 */

    #undef FG_INC_SDL_APPLICATION_BLOCK
#endif /* FG_INC_SDL_APPLICATION_BLOCK */
