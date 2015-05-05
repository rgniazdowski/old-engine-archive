/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_ERRNO
    #define FG_INC_ERRNO
    #define FG_INC_ERRNO_ERROR_CODES_BLOCK__

    #include <cerrno>
    #include <map>
    #include <string>

    #define FG_ERRNO_INVALID_CODE_TEXT		"invalid error code"

    #define FG_ERRNO	errno

    #define FG_ERRNO_BASE_CODE_				20000
    #define FG_ERRNO_BASE_CODE(code)		(FG_ERRNO_BASE_CODE_+code)

    #define FG_ERRNO_WARNING_BASE_CODE_		63600
    #define FG_ERRNO_DEBUG_BASE_CODE_		616000
    #define FG_ERRNO_INFO_BASE_CODE_		100000

    #define FG_ERRNO_WARNING_BASE_CODE(code)	(FG_ERRNO_WARNING_BASE_CODE_+code)
    #define FG_ERRNO_DEBUG_BASE_CODE(code)		(FG_ERRNO_DEBUG_BASE_CODE_+code)
    #define FG_ERRNO_INFO_BASE_CODE(code)		(FG_ERRNO_INFO_BASE_CODE_+code)

/**********************************************************
 * FlexiGame specific error codes
 */

    #define FG_ERRNO_OK				FG_ERRNO_BASE_CODE(0)	/* No error */
    #define FG_ERRNO_NOCFG			FG_ERRNO_BASE_CODE(1)	/* No config file found */
    #define FG_ERRNO_EXCEPTION		FG_ERRNO_BASE_CODE(2)   /* Exception */
    #define FG_ERRNO_NOT_FOUND		FG_ERRNO_BASE_CODE(3)	/* Element was not found */
    #define FG_ERRNO_WRONG_PARAM	FG_ERRNO_BASE_CODE(4)	/* Wrong parameter */
    #define FG_ERRNO_WRONG_PATH		FG_ERRNO_BASE_CODE(5)	/* Wrong file path specified */

    #define FG_ERRNO_LAST_CODE		FG_ERRNO_BASE_CODE(4)	/* Last code */

    #define FG_ERRNO_OK_TEXT			"No error"
    #define FG_ERRNO_NOCFG_TEXT			"No config file found"
    #define FG_ERRNO_EXCEPTION_TEXT		"Exception"
    #define FG_ERRNO_NOT_FOUND_TEXT		"Element was not found"
    #define FG_ERRNO_WRONG_PARAM_TEXT	"Wrong parameter"
    #define FG_ERRNO_WRONG_PATH_TEXT	"Wrong file path specified"

/**********************************************************
 * STANDARD CODES
 */

    #define FG_ERRNO_EPERM		EPERM          /* Operation not permitted */
    #define FG_ERRNO_ENOENT		ENOENT         /* No such file or directory */
    #define FG_ERRNO_ESRCH		ESRCH          /* No such process */
    #define FG_ERRNO_EINTR		EINTR          /* Interrupted system call */
    #define FG_ERRNO_EIO		EIO            /* I/O error */
    #define FG_ERRNO_ENXIO		ENXIO          /* No such device or address */
    #define FG_ERRNO_E2BIG		E2BIG          /* Argument list too long */
    #define FG_ERRNO_ENOEXEC	ENOEXEC        /* Exec format error */
    #define FG_ERRNO_EBADF		EBADF          /* Bad file number */
    #define FG_ERRNO_ECHILD		ECHILD         /* No child processes */
    #define FG_ERRNO_EAGAIN		EAGAIN         /* Try again */
    #define FG_ERRNO_ENOMEM		ENOMEM         /* Out of memory */
    #define FG_ERRNO_EACCES		EACCES         /* Permission denied */
    #define FG_ERRNO_EFAULT		EFAULT         /* Bad address */
    #define FG_ERRNO_ENOTBLK	ENOTBLK        /* Block device required */
    #define FG_ERRNO_EBUSY		EBUSY          /* Device or resource busy */
    #define FG_ERRNO_EEXIST		EEXIST         /* File exists */
    #define FG_ERRNO_EXDEV		EXDEV          /* Cross-device link */
    #define FG_ERRNO_ENODEV		ENODEV         /* No such device */
    #define FG_ERRNO_ENOTDIR	ENOTDIR        /* Not a directory */
    #define FG_ERRNO_EISDIR		EISDIR         /* Is a directory */
    #define FG_ERRNO_EINVAL		EINVAL         /* Invalid argument */
    #define FG_ERRNO_ENFILE		ENFILE         /* File table overflow */
    #define FG_ERRNO_EMFILE		EMFILE         /* Too many open files */
    #define FG_ERRNO_ENOTTY		ENOTTY         /* Not a typewriter */
    #define FG_ERRNO_ETXTBSY	ETXTBSY        /* Text file busy */
    #define FG_ERRNO_EFBIG		EFBIG          /* File too large */
    #define FG_ERRNO_ENOSPC		ENOSPC         /* No space left on device */
    #define FG_ERRNO_ESPIPE		ESPIPE         /* Illegal seek */
    #define FG_ERRNO_EROFS		EROFS          /* Read-only file system */
    #define FG_ERRNO_EMLINK		EMLINK         /* Too many links */
    #define FG_ERRNO_EPIPE		EPIPE          /* Broken pipe */
    #define FG_ERRNO_EDOM		EDOM           /* Math argument out of domain of func */
    #define FG_ERRNO_ERANGE		ERANGE         /* Math result not representable */
    #define FG_ERRNO_EDEADLK		EDEADLK       
    #define FG_ERRNO_ENAMETOOLONG	ENAMETOOLONG 
    #define FG_ERRNO_ENOLCK			ENOLCK       
    #define FG_ERRNO_ENOSYS			ENOSYS       
    #define FG_ERRNO_ENOTEMPTY		ENOTEMPTY    
    #define FG_ERRNO_ELOOP			ELOOP          /* Too many symbolic links encountered */
    #define FG_ERRNO_EIDRM			EIDRM        



    #define FG_ERRNO_EWOULDBLOCK	EWOULDBLOCK     /* Operation would block */

    #define FG_ERRNO_EOVERFLOW		EOVERFLOW
    #define FG_ERRNO_EILSEQ			EILSEQ

    #define FG_ERRNO_ENOTSOCK		ENOTSOCK        /* Socket operation on non-socket */
    #define FG_ERRNO_EDESTADDRREQ	EDESTADDRREQ    /* Destination address required */
    #define FG_ERRNO_EMSGSIZE		EMSGSIZE        /* Message too long */
    #define FG_ERRNO_EPROTOTYPE		EPROTOTYPE      /* Protocol wrong type for socket */
    #define FG_ERRNO_ENOPROTOOPT		ENOPROTOOPT     /* Protocol not available */
    #define FG_ERRNO_EPROTONOSUPPORT	EPROTONOSUPPORT /* Protocol not supported */
    #define FG_ERRNO_ESOCKTNOSUPPORT	ESOCKTNOSUPPORT /* Socket type not supported */
    #define FG_ERRNO_EOPNOTSUPP		EOPNOTSUPP      /* Operation not supported on transport endpoint */
    #define FG_ERRNO_EPFNOSUPPORT	EPFNOSUPPORT    /* Protocol family not supported */
    #define FG_ERRNO_EAFNOSUPPORT	EAFNOSUPPORT    /* Address family not supported by protocol */
    #define FG_ERRNO_EADDRINUSE		EADDRINUSE      /* Address already in use */
    #define FG_ERRNO_EADDRNOTAVAIL	EADDRNOTAVAIL   /* Cannot assign requested address */
    #define FG_ERRNO_ENETDOWN		ENETDOWN        /* Network is down */
    #define FG_ERRNO_ENETUNREACH	ENETUNREACH     /* Network is unreachable */
    #define FG_ERRNO_ENETRESET		ENETRESET       /* Network dropped connection because of reset */
    #define FG_ERRNO_ECONNABORTED	ECONNABORTED    /* Software caused connection abort */
    #define FG_ERRNO_ECONNRESET		ECONNRESET      /* Connection reset by peer */
    #define FG_ERRNO_ENOBUFS		ENOBUFS         /* No buffer space available */
    #define FG_ERRNO_EISCONN		EISCONN         /* Transport endpoint is already connected */
    #define FG_ERRNO_ENOTCONN		ENOTCONN        /* Transport endpoint is not connected */
    #define FG_ERRNO_ESHUTDOWN		ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
    #define FG_ERRNO_ETOOMANYREFS	ETOOMANYREFS    /* Too many references: cannot splice */
    #define FG_ERRNO_ETIMEDOUT		ETIMEDOUT       /* Connection timed out */
    #define FG_ERRNO_ECONNREFUSED	ECONNREFUSED    /* Connection refused */
    #define FG_ERRNO_EHOSTDOWN		EHOSTDOWN       /* Host is down */
    #define FG_ERRNO_EHOSTUNREACH	EHOSTUNREACH    /* No route to host */
    #define FG_ERRNO_EALREADY		EALREADY        /* Operation already in progress */
    #define FG_ERRNO_EINPROGRESS	EINPROGRESS     /* Operation now in progress */
    #define FG_ERRNO_ESTALE			ESTALE          /* Stale NFS file handle */
    #define FG_ERRNO_EUCLEAN		EUCLEAN         /* Structure needs cleaning */
    #define FG_ERRNO_ENOTNAM		ENOTNAM         /* Not a XENIX named type file */
    #define FG_ERRNO_ENAVAIL		ENAVAIL         /* No XENIX semaphores available */
    #define FG_ERRNO_EISNAM			EISNAM          /* Is a named type file */
    #define FG_ERRNO_EREMOTEIO		EREMOTEIO       /* Remote I/O error */
    #define FG_ERRNO_EDQUOT			EDQUOT          /* Quota exceeded */

/*
 *
 **********************************************************/

/*
 * 
 */
class fgErrno {
public:
    // 
    static const char *strError(int _code);
    // 
    static void registerStrError(int _code, const char *_str);
    // 
    static void registerStrError(int _code, std::string& _str);
    // 
    static void setErrno(int _code);
    //
    static void setLocalErrno(int _code);
    // 
    static void reset(void);
    //
    static int code(void);
    //
    static int localCode(void);
    //
    static void clearError(void);

protected:
    // 
    static const char *_getStrError(int _fg_code);

private:
    typedef std::map<int, std::string> strErrMap;
    typedef std::pair<int, std::string> strErrMapPair;
    typedef strErrMap::iterator strErrMapItor;

    // 
    static strErrMap s_errorMap;
    // 
    static int s_errno;
};

    #define FG_ERRNO_STR(code)	fgErrno::strError(code)

    #define FG_ERRNO_SET(code)				fgErrno::setErrno(code)
    #define FG_ERRNO_REGISTER(code, str)	fgErrno::registerStrError(code, str)

    #define FG_ERRNO_CLEAR()				do { fgErrno::clearError(); } while(0)

namespace FG_ERRNO_MAIN {
    const char * const __allErrVec[] = {
                                        FG_ERRNO_OK_TEXT,
                                        FG_ERRNO_NOCFG_TEXT,
                                        FG_ERRNO_EXCEPTION_TEXT,
                                        FG_ERRNO_NOT_FOUND_TEXT,
                                        FG_ERRNO_WRONG_PARAM_TEXT,
                                        FG_ERRNO_WRONG_PATH_TEXT
    };
    inline void __registerAll(void) {
        for(int code = FG_ERRNO_BASE_CODE(0), i = 0; code <= FG_ERRNO_LAST_CODE; code++, i++) {
            FG_ERRNO_REGISTER(code, FG_ERRNO_MAIN::__allErrVec[i]);
        }
    }
};

    #undef FG_INC_ERRNO_ERROR_CODES_BLOCK__
#endif /* FG_INC_ERRNO */
