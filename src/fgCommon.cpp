/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

// #TODO #P2 - need to create some levels of logging verbosity
// #TODO #P3 - also maybe some files to write to
// #TODO #P4 - need to add some over the top logging subsystem and hook it to console or whatnot
// #TODO #P3 - this also should be linked directly to the error reporting subsystem/standard

#ifdef _MSC_VER
#if 0
#undef strtok_r

char *strtok_r(char *s, const char *delim, char **last) {
    char *spanp;
    int c, sc;
    char *tok;


    if(s == NULL && (s = *last) == NULL)
        return (NULL);

    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
cont:
    c = *s++;
    for(spanp = (char *)delim; (sc = *spanp++) != 0;) {
        if(c == sc)
            goto cont;
    }

    if(c == 0) { /* no non-delimiter characters */
        *last = NULL;
        return (NULL);
    }
    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for(;;) {
        c = *s++;
        spanp = (char *)delim;
        do {
            if((sc = *spanp++) == c) {
                if(c == 0)
                    s = NULL;
                else
                    s[-1] = 0;
                *last = s;
                return (tok);
            }
        } while(sc != 0);
    }
    /* NOTREACHED */
}
#endif
#endif

