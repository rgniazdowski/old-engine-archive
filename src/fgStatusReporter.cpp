/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgStatusReporter.h"
#include "fgMessageSubsystem.h"
#include "fgLog.h"

namespace FG_STATUS {

    void reportToMessageSubsystem(fgStatus *_status) {
        FG_MessageSubsystem->pushStatus(_status);
    }

    void printStatus(fgStatus *_status) {
        if(_status)
            FG_LOG::PrintStatus(_status);
    }
};
