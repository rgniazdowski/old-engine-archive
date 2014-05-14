/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "fgCommon.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

#ifdef FG_USING_MARMALADE
#include "s3eDebug.h"
#include "s3eTimer.h"
#endif

unsigned long int FG_GetTicks(void)
{
#ifdef FG_USING_MARMALADE
	return s3eTimerGetMs();
#else
	return 32; // FIXME - here needs to be proper function getting the miliseconds
#endif
}

/**
 * Log info message
 * @param fmt
 */
void FG_InfoLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "INFO: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/**
 * Write log message
 * @param fmt
 */
void FG_WriteLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "LOG: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/**
 * Log error message
 * @param fmt
 */
void FG_ErrorLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "ERROR: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}

#ifdef _MSC_VER

#undef strtok_r

char *strtok_r(char *s, const char *delim, char **last)
{
	char *spanp;
	int c, sc;
	char *tok;


	if (s == NULL && (s = *last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

#endif
