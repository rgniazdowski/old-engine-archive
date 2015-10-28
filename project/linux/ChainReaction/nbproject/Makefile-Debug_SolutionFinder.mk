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
CC=/usr/bin/gcc-4.8.1
CCC=/usr/bin/g++-4.8.1
CXX=/usr/bin/g++-4.8.1
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug_SolutionFinder
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main_SolutionFinder.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lm /home/vigilant/develop/flexigame/project/linux/ChainReaction/dist/Debug_STATIC/GNU-Linux-x86/libchainreaction.a /home/vigilant/develop/flexigame/project/linux/FlexiGame_NB/dist/Debug_GLEW_StaticLib/GNU-Linux-x86/libflexigame_nb.a /home/vigilant/develop/flexigame/project/linux/LuaPlusNextGen_NB/dist/Debug/GNU-Linux-x86/libluaplusnextgen_nb.a /home/vigilant/develop/flexigame/project/linux/MiniZipMaster_NB/dist/Debug/GNU-Linux-x86/libminizipmaster_nb.a `pkg-config --libs glew` `pkg-config --libs gl` `pkg-config --libs zlib` `pkg-config --libs libpng` -ljpeg -ldl -lpthread   

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/ChainReaction/dist/Debug_STATIC/GNU-Linux-x86/libchainreaction.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/FlexiGame_NB/dist/Debug_GLEW_StaticLib/GNU-Linux-x86/libflexigame_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/LuaPlusNextGen_NB/dist/Debug/GNU-Linux-x86/libluaplusnextgen_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/MiniZipMaster_NB/dist/Debug/GNU-Linux-x86/libminizipmaster_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction ${OBJECTFILES} ${LDLIBSOPTIONS} -rdynamic -Wl,--export-dynamic

${OBJECTDIR}/main_SolutionFinder.o: main_SolutionFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -DFG_NO_UNDEF -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_SolutionFinder.o main_SolutionFinder.cpp

# Subprojects
.build-subprojects:
	cd /home/vigilant/develop/flexigame/project/linux/ChainReaction && ${MAKE} -j 20 -f Makefile CONF=Debug_STATIC

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction

# Subprojects
.clean-subprojects:
	cd /home/vigilant/develop/flexigame/project/linux/ChainReaction && ${MAKE} -j 20 -f Makefile CONF=Debug_STATIC clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
