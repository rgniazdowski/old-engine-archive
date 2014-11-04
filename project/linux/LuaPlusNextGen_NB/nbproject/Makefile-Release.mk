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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1575965373/LuaPlus.o \
	${OBJECTDIR}/_ext/1575965373/LuaPlusAddons.o \
	${OBJECTDIR}/_ext/1575965373/LuaState_DumpObject.o \
	${OBJECTDIR}/_ext/1617192163/lapi.o \
	${OBJECTDIR}/_ext/1617192163/lauxlib.o \
	${OBJECTDIR}/_ext/1617192163/lbaselib.o \
	${OBJECTDIR}/_ext/1617192163/lbitlib.o \
	${OBJECTDIR}/_ext/1617192163/lcode.o \
	${OBJECTDIR}/_ext/1617192163/lcorolib.o \
	${OBJECTDIR}/_ext/1617192163/lctype.o \
	${OBJECTDIR}/_ext/1617192163/ldblib.o \
	${OBJECTDIR}/_ext/1617192163/ldebug.o \
	${OBJECTDIR}/_ext/1617192163/ldo.o \
	${OBJECTDIR}/_ext/1617192163/ldump.o \
	${OBJECTDIR}/_ext/1617192163/lfunc.o \
	${OBJECTDIR}/_ext/1617192163/lgc.o \
	${OBJECTDIR}/_ext/1617192163/linit.o \
	${OBJECTDIR}/_ext/1617192163/liolib.o \
	${OBJECTDIR}/_ext/1617192163/llex.o \
	${OBJECTDIR}/_ext/1617192163/lmathlib.o \
	${OBJECTDIR}/_ext/1617192163/lmem.o \
	${OBJECTDIR}/_ext/1617192163/loadlib.o \
	${OBJECTDIR}/_ext/1617192163/lobject.o \
	${OBJECTDIR}/_ext/1617192163/lopcodes.o \
	${OBJECTDIR}/_ext/1617192163/loslib.o \
	${OBJECTDIR}/_ext/1617192163/lparser.o \
	${OBJECTDIR}/_ext/1617192163/lstate.o \
	${OBJECTDIR}/_ext/1617192163/lstring.o \
	${OBJECTDIR}/_ext/1617192163/lstrlib.o \
	${OBJECTDIR}/_ext/1617192163/ltable.o \
	${OBJECTDIR}/_ext/1617192163/ltablib.o \
	${OBJECTDIR}/_ext/1617192163/ltm.o \
	${OBJECTDIR}/_ext/1617192163/lundump.o \
	${OBJECTDIR}/_ext/1617192163/lvm.o \
	${OBJECTDIR}/_ext/1617192163/lzio.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a

${OBJECTDIR}/_ext/1575965373/LuaPlus.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlus.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1575965373
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1575965373/LuaPlus.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlus.cpp

${OBJECTDIR}/_ext/1575965373/LuaPlusAddons.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlusAddons.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1575965373
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1575965373/LuaPlusAddons.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaPlusAddons.c

${OBJECTDIR}/_ext/1575965373/LuaState_DumpObject.o: ../../../modules/luaplus51-all/Src/LuaPlus/LuaState_DumpObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1575965373
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1575965373/LuaState_DumpObject.o ../../../modules/luaplus51-all/Src/LuaPlus/LuaState_DumpObject.cpp

${OBJECTDIR}/_ext/1617192163/lapi.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lapi.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lapi.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lapi.c

${OBJECTDIR}/_ext/1617192163/lauxlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lauxlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lauxlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lauxlib.c

${OBJECTDIR}/_ext/1617192163/lbaselib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbaselib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lbaselib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbaselib.c

${OBJECTDIR}/_ext/1617192163/lbitlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbitlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lbitlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lbitlib.c

${OBJECTDIR}/_ext/1617192163/lcode.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcode.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lcode.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcode.c

${OBJECTDIR}/_ext/1617192163/lcorolib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcorolib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lcorolib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lcorolib.c

${OBJECTDIR}/_ext/1617192163/lctype.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lctype.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lctype.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lctype.c

${OBJECTDIR}/_ext/1617192163/ldblib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldblib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ldblib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldblib.c

${OBJECTDIR}/_ext/1617192163/ldebug.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldebug.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ldebug.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldebug.c

${OBJECTDIR}/_ext/1617192163/ldo.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldo.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ldo.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldo.c

${OBJECTDIR}/_ext/1617192163/ldump.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldump.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ldump.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ldump.c

${OBJECTDIR}/_ext/1617192163/lfunc.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lfunc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lfunc.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lfunc.c

${OBJECTDIR}/_ext/1617192163/lgc.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lgc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lgc.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lgc.c

${OBJECTDIR}/_ext/1617192163/linit.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/linit.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/linit.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/linit.c

${OBJECTDIR}/_ext/1617192163/liolib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/liolib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/liolib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/liolib.c

${OBJECTDIR}/_ext/1617192163/llex.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/llex.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/llex.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/llex.c

${OBJECTDIR}/_ext/1617192163/lmathlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmathlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lmathlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmathlib.c

${OBJECTDIR}/_ext/1617192163/lmem.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmem.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lmem.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lmem.c

${OBJECTDIR}/_ext/1617192163/loadlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loadlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/loadlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loadlib.c

${OBJECTDIR}/_ext/1617192163/lobject.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lobject.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lobject.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lobject.c

${OBJECTDIR}/_ext/1617192163/lopcodes.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lopcodes.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lopcodes.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lopcodes.c

${OBJECTDIR}/_ext/1617192163/loslib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loslib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/loslib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/loslib.c

${OBJECTDIR}/_ext/1617192163/lparser.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lparser.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lparser.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lparser.c

${OBJECTDIR}/_ext/1617192163/lstate.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lstate.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstate.c

${OBJECTDIR}/_ext/1617192163/lstring.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstring.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lstring.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstring.c

${OBJECTDIR}/_ext/1617192163/lstrlib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstrlib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lstrlib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lstrlib.c

${OBJECTDIR}/_ext/1617192163/ltable.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltable.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ltable.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltable.c

${OBJECTDIR}/_ext/1617192163/ltablib.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltablib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ltablib.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltablib.c

${OBJECTDIR}/_ext/1617192163/ltm.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltm.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/ltm.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/ltm.c

${OBJECTDIR}/_ext/1617192163/lundump.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lundump.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lundump.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lundump.c

${OBJECTDIR}/_ext/1617192163/lvm.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lvm.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lvm.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lvm.c

${OBJECTDIR}/_ext/1617192163/lzio.o: ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lzio.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1617192163
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Wall -s -DLUAPLUS_DUMPOBJECT -DLUA_OPNAMES -DLUA_USE_MKSTEMP -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1617192163/lzio.o ../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src/lzio.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libluaplusnextgen_nb.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
