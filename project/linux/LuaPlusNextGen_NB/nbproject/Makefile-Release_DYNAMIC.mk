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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release_DYNAMIC
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/a210ad43/LuaPlus.o \
	${OBJECTDIR}/_ext/a210ad43/LuaPlusAddons.o \
	${OBJECTDIR}/_ext/a210ad43/LuaState_DumpObject.o \
	${OBJECTDIR}/_ext/606464e3/lapi.o \
	${OBJECTDIR}/_ext/606464e3/lauxlib.o \
	${OBJECTDIR}/_ext/606464e3/lbaselib.o \
	${OBJECTDIR}/_ext/606464e3/lbitlib.o \
	${OBJECTDIR}/_ext/606464e3/lcode.o \
	${OBJECTDIR}/_ext/606464e3/lcorolib.o \
	${OBJECTDIR}/_ext/606464e3/lctype.o \
	${OBJECTDIR}/_ext/606464e3/ldblib.o \
	${OBJECTDIR}/_ext/606464e3/ldebug.o \
	${OBJECTDIR}/_ext/606464e3/ldo.o \
	${OBJECTDIR}/_ext/606464e3/ldump.o \
	${OBJECTDIR}/_ext/606464e3/lfunc.o \
	${OBJECTDIR}/_ext/606464e3/lgc.o \
	${OBJECTDIR}/_ext/606464e3/linit.o \
	${OBJECTDIR}/_ext/606464e3/liolib.o \
	${OBJECTDIR}/_ext/606464e3/llex.o \
	${OBJECTDIR}/_ext/606464e3/lmathlib.o \
	${OBJECTDIR}/_ext/606464e3/lmem.o \
	${OBJECTDIR}/_ext/606464e3/loadlib.o \
	${OBJECTDIR}/_ext/606464e3/lobject.o \
	${OBJECTDIR}/_ext/606464e3/lopcodes.o \
	${OBJECTDIR}/_ext/606464e3/loslib.o \
	${OBJECTDIR}/_ext/606464e3/lparser.o \
	${OBJECTDIR}/_ext/606464e3/lstate.o \
	${OBJECTDIR}/_ext/606464e3/lstring.o \
	${OBJECTDIR}/_ext/606464e3/lstrlib.o \
	${OBJECTDIR}/_ext/606464e3/ltable.o \
	${OBJECTDIR}/_ext/606464e3/ltablib.o \
	${OBJECTDIR}/_ext/606464e3/ltm.o \
	${OBJECTDIR}/_ext/606464e3/lundump.o \
	${OBJECTDIR}/_ext/606464e3/lvm.o \
	${OBJECTDIR}/_ext/606464e3/lzio.o


# C Compiler Flags
CFLAGS=-ffunction-sections -fdata-sections -Os

# CC Compiler Flags
CCFLAGS=-ffunction-sections -fdata-sections -Os
CXXFLAGS=-ffunction-sections -fdata-sections -Os

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLuaPlusNextGen_NB.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLuaPlusNextGen_NB.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLuaPlusNextGen_NB.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -s -fPIC

${OBJECTDIR}/_ext/a210ad43/LuaPlus.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlus.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/a210ad43
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a210ad43/LuaPlus.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlus.cpp

${OBJECTDIR}/_ext/a210ad43/LuaPlusAddons.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlusAddons.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/a210ad43
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a210ad43/LuaPlusAddons.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlusAddons.c

${OBJECTDIR}/_ext/a210ad43/LuaState_DumpObject.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaState_DumpObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/a210ad43
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a210ad43/LuaState_DumpObject.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaState_DumpObject.cpp

${OBJECTDIR}/_ext/606464e3/lapi.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lapi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lapi.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lapi.c

${OBJECTDIR}/_ext/606464e3/lauxlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lauxlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lauxlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lauxlib.c

${OBJECTDIR}/_ext/606464e3/lbaselib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbaselib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lbaselib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbaselib.c

${OBJECTDIR}/_ext/606464e3/lbitlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbitlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lbitlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbitlib.c

${OBJECTDIR}/_ext/606464e3/lcode.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcode.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lcode.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcode.c

${OBJECTDIR}/_ext/606464e3/lcorolib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcorolib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lcorolib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcorolib.c

${OBJECTDIR}/_ext/606464e3/lctype.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lctype.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lctype.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lctype.c

${OBJECTDIR}/_ext/606464e3/ldblib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldblib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ldblib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldblib.c

${OBJECTDIR}/_ext/606464e3/ldebug.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldebug.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ldebug.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldebug.c

${OBJECTDIR}/_ext/606464e3/ldo.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldo.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ldo.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldo.c

${OBJECTDIR}/_ext/606464e3/ldump.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldump.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ldump.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldump.c

${OBJECTDIR}/_ext/606464e3/lfunc.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lfunc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lfunc.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lfunc.c

${OBJECTDIR}/_ext/606464e3/lgc.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lgc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lgc.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lgc.c

${OBJECTDIR}/_ext/606464e3/linit.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/linit.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/linit.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/linit.c

${OBJECTDIR}/_ext/606464e3/liolib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/liolib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/liolib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/liolib.c

${OBJECTDIR}/_ext/606464e3/llex.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/llex.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/llex.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/llex.c

${OBJECTDIR}/_ext/606464e3/lmathlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmathlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lmathlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmathlib.c

${OBJECTDIR}/_ext/606464e3/lmem.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmem.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lmem.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmem.c

${OBJECTDIR}/_ext/606464e3/loadlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loadlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/loadlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loadlib.c

${OBJECTDIR}/_ext/606464e3/lobject.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lobject.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lobject.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lobject.c

${OBJECTDIR}/_ext/606464e3/lopcodes.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lopcodes.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lopcodes.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lopcodes.c

${OBJECTDIR}/_ext/606464e3/loslib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loslib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/loslib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loslib.c

${OBJECTDIR}/_ext/606464e3/lparser.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lparser.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lparser.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lparser.c

${OBJECTDIR}/_ext/606464e3/lstate.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lstate.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstate.c

${OBJECTDIR}/_ext/606464e3/lstring.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstring.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lstring.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstring.c

${OBJECTDIR}/_ext/606464e3/lstrlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstrlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lstrlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstrlib.c

${OBJECTDIR}/_ext/606464e3/ltable.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltable.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ltable.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltable.c

${OBJECTDIR}/_ext/606464e3/ltablib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltablib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ltablib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltablib.c

${OBJECTDIR}/_ext/606464e3/ltm.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltm.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/ltm.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltm.c

${OBJECTDIR}/_ext/606464e3/lundump.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lundump.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lundump.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lundump.c

${OBJECTDIR}/_ext/606464e3/lvm.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lvm.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lvm.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lvm.c

${OBJECTDIR}/_ext/606464e3/lzio.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lzio.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/606464e3
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DFG_RELEASE -DLUA_BUILD_AS_DLL -DLUA_OPNAMES -DLUA_USE_MKSTEMP -DRELEASE -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/606464e3/lzio.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lzio.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLuaPlusNextGen_NB.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
