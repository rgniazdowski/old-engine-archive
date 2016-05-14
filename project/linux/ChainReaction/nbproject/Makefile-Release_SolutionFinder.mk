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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release_SolutionFinder
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
LDLIBSOPTIONS=-lm /home/vigilant/develop/flexigame/project/linux/ChainReaction/dist/Release_STATIC/GNU-Linux/libchainreaction.a /home/vigilant/develop/flexigame/project/linux/FlexiGame_NB/dist/Release_GLEW_StaticLib/GNU-Linux/libflexigame_nb.a /home/vigilant/develop/flexigame/project/linux/LuaPlusNextGen_NB/dist/Release/GNU-Linux/libluaplusnextgen_nb.a /home/vigilant/develop/flexigame/project/linux/MiniZipMaster_NB/dist/Release/GNU-Linux/libminizipmaster_nb.a `pkg-config --libs glew` `pkg-config --libs libpng` `pkg-config --libs zlib` `pkg-config --libs gl` -ldl -ljpeg -lpthread   

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/ChainReaction/dist/Release_STATIC/GNU-Linux/libchainreaction.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/FlexiGame_NB/dist/Release_GLEW_StaticLib/GNU-Linux/libflexigame_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/LuaPlusNextGen_NB/dist/Release/GNU-Linux/libluaplusnextgen_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: /home/vigilant/develop/flexigame/project/linux/MiniZipMaster_NB/dist/Release/GNU-Linux/libminizipmaster_nb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction ${OBJECTFILES} ${LDLIBSOPTIONS} -s

${OBJECTDIR}/main_SolutionFinder.o: main_SolutionFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -s -DFG_DEFAULTS -DFG_RELEASE -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src `pkg-config --cflags glew` `pkg-config --cflags libpng` `pkg-config --cflags zlib` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_SolutionFinder.o main_SolutionFinder.cpp

# Subprojects
.build-subprojects:
	cd /home/vigilant/develop/flexigame/project/linux/ChainReaction && ${MAKE} -j 20 -f Makefile CONF=Release_STATIC

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/chainreaction

# Subprojects
.clean-subprojects:
	cd /home/vigilant/develop/flexigame/project/linux/ChainReaction && ${MAKE} -j 20 -f Makefile CONF=Release_STATIC clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
