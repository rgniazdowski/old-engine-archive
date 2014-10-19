/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_ERROR_CODES_H_
    #define _FG_ERROR_CODES_H_

    #ifdef _FG_ERRNO_ERROR_CODES_BLOCK__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include ErrorCodes inside of fgErrno header."
    #endif

    #ifdef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include fgErrorCodes.h inside of other error codes definition header."
    #endif 

    #include "fgErrno.h"

    #include "Audio/fgSFXErrorCodes.h"
    #include "Event/fgEventErrorCodes.h"
    #include "GFX/fgGFXErrorCodes.h"
    #include "GFX/Textures/fgTextureErrorCodes.h"
    #include "GUI/fgGuiErrorCodes.h"
    #include "Resource/fgResourceErrorCodes.h"
    #include "Scripting/fgScriptErrorCodes.h"
    #include "Util/fgFileErrorCodes.h"
    #include "Util/fgMemoryErrorCodes.h"
    #include "XML/fgXMLErrorCodes.h"
    #include "fgGameErrorCodes.h"

class fgErrorCodes {
protected:
    fgErrorCodes() { }
    ~fgErrorCodes() { }
public:
    static void registerAll(void);
    static void unregisterAll(void);
};

#endif /* _FG_ERROR_CODES_H_ */
