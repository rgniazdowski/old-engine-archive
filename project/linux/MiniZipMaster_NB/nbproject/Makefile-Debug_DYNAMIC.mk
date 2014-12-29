#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug_DYNAMIC
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/904282815/aescrypt.o \
	${OBJECTDIR}/_ext/904282815/aeskey.o \
	${OBJECTDIR}/_ext/904282815/aestab.o \
	${OBJECTDIR}/_ext/904282815/entropy.o \
	${OBJECTDIR}/_ext/904282815/fileenc.o \
	${OBJECTDIR}/_ext/904282815/hmac.o \
	${OBJECTDIR}/_ext/904282815/prng.o \
	${OBJECTDIR}/_ext/904282815/pwd2key.o \
	${OBJECTDIR}/_ext/904282815/sha1.o \
	${OBJECTDIR}/_ext/1455455233/ioapi.o \
	${OBJECTDIR}/_ext/1455455233/ioapi_buf.o \
	${OBJECTDIR}/_ext/1455455233/ioapi_mem.o \
	${OBJECTDIR}/_ext/1455455233/unzip.o \
	${OBJECTDIR}/_ext/1455455233/zip.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMiniZipMaster_NB.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMiniZipMaster_NB.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMiniZipMaster_NB.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/904282815/aescrypt.o: ../../../modules/zlib_128/contrib/minizip/aes/aescrypt.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/aescrypt.o ../../../modules/zlib_128/contrib/minizip/aes/aescrypt.c

${OBJECTDIR}/_ext/904282815/aeskey.o: ../../../modules/zlib_128/contrib/minizip/aes/aeskey.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/aeskey.o ../../../modules/zlib_128/contrib/minizip/aes/aeskey.c

${OBJECTDIR}/_ext/904282815/aestab.o: ../../../modules/zlib_128/contrib/minizip/aes/aestab.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/aestab.o ../../../modules/zlib_128/contrib/minizip/aes/aestab.c

${OBJECTDIR}/_ext/904282815/entropy.o: ../../../modules/zlib_128/contrib/minizip/aes/entropy.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/entropy.o ../../../modules/zlib_128/contrib/minizip/aes/entropy.c

${OBJECTDIR}/_ext/904282815/fileenc.o: ../../../modules/zlib_128/contrib/minizip/aes/fileenc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/fileenc.o ../../../modules/zlib_128/contrib/minizip/aes/fileenc.c

${OBJECTDIR}/_ext/904282815/hmac.o: ../../../modules/zlib_128/contrib/minizip/aes/hmac.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/hmac.o ../../../modules/zlib_128/contrib/minizip/aes/hmac.c

${OBJECTDIR}/_ext/904282815/prng.o: ../../../modules/zlib_128/contrib/minizip/aes/prng.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/prng.o ../../../modules/zlib_128/contrib/minizip/aes/prng.c

${OBJECTDIR}/_ext/904282815/pwd2key.o: ../../../modules/zlib_128/contrib/minizip/aes/pwd2key.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/pwd2key.o ../../../modules/zlib_128/contrib/minizip/aes/pwd2key.c

${OBJECTDIR}/_ext/904282815/sha1.o: ../../../modules/zlib_128/contrib/minizip/aes/sha1.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/904282815
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904282815/sha1.o ../../../modules/zlib_128/contrib/minizip/aes/sha1.c

${OBJECTDIR}/_ext/1455455233/ioapi.o: ../../../modules/zlib_128/contrib/minizip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1455455233
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1455455233/ioapi.o ../../../modules/zlib_128/contrib/minizip/ioapi.c

${OBJECTDIR}/_ext/1455455233/ioapi_buf.o: ../../../modules/zlib_128/contrib/minizip/ioapi_buf.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1455455233
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1455455233/ioapi_buf.o ../../../modules/zlib_128/contrib/minizip/ioapi_buf.c

${OBJECTDIR}/_ext/1455455233/ioapi_mem.o: ../../../modules/zlib_128/contrib/minizip/ioapi_mem.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1455455233
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1455455233/ioapi_mem.o ../../../modules/zlib_128/contrib/minizip/ioapi_mem.c

${OBJECTDIR}/_ext/1455455233/unzip.o: ../../../modules/zlib_128/contrib/minizip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1455455233
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1455455233/unzip.o ../../../modules/zlib_128/contrib/minizip/unzip.c

${OBJECTDIR}/_ext/1455455233/zip.o: ../../../modules/zlib_128/contrib/minizip/zip.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1455455233
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -DFG_DEBUG -DHAVE_AES -D_DEBUG -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1455455233/zip.o ../../../modules/zlib_128/contrib/minizip/zip.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libMiniZipMaster_NB.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
