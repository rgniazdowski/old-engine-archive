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
CND_CONF=Debug_STATIC
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AdditionalTypes.o \
	${OBJECTDIR}/CLevelDataHolder.o \
	${OBJECTDIR}/CLevelFile.o \
	${OBJECTDIR}/CLevelGenerator.o \
	${OBJECTDIR}/CLevelSolution.o \
	${OBJECTDIR}/CLevelSolutionFinder.o \
	${OBJECTDIR}/CLevelSolver.o \
	${OBJECTDIR}/CLevelVisualization.o \
	${OBJECTDIR}/ChainReaction.o \
	${OBJECTDIR}/SBlockData.o \
	${OBJECTDIR}/SHexData.o \
	${OBJECTDIR}/SOctData.o \
	${OBJECTDIR}/SQuadData.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a

${OBJECTDIR}/AdditionalTypes.o: AdditionalTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdditionalTypes.o AdditionalTypes.cpp

${OBJECTDIR}/CLevelDataHolder.o: CLevelDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelDataHolder.o CLevelDataHolder.cpp

${OBJECTDIR}/CLevelFile.o: CLevelFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelFile.o CLevelFile.cpp

${OBJECTDIR}/CLevelGenerator.o: CLevelGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelGenerator.o CLevelGenerator.cpp

${OBJECTDIR}/CLevelSolution.o: CLevelSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelSolution.o CLevelSolution.cpp

${OBJECTDIR}/CLevelSolutionFinder.o: CLevelSolutionFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelSolutionFinder.o CLevelSolutionFinder.cpp

${OBJECTDIR}/CLevelSolver.o: CLevelSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelSolver.o CLevelSolver.cpp

${OBJECTDIR}/CLevelVisualization.o: CLevelVisualization.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelVisualization.o CLevelVisualization.cpp

${OBJECTDIR}/ChainReaction.o: ChainReaction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ChainReaction.o ChainReaction.cpp

${OBJECTDIR}/SBlockData.o: SBlockData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SBlockData.o SBlockData.cpp

${OBJECTDIR}/SHexData.o: SHexData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SHexData.o SHexData.cpp

${OBJECTDIR}/SOctData.o: SOctData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SOctData.o SOctData.cpp

${OBJECTDIR}/SQuadData.o: SQuadData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -D_DEBUG -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_CR_PLUGIN_STATIC -DFG_DEFAULTS -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include -I../../../modules/bullet/bullet3/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SQuadData.o SQuadData.cpp

# Subprojects
.build-subprojects:
	cd ../FlexiGame_NB && ${MAKE} -j 20 -f Makefile.nb CONF=Debug_GLEW_SDL2

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libchainreaction.a

# Subprojects
.clean-subprojects:
	cd ../FlexiGame_NB && ${MAKE} -j 20 -f Makefile.nb CONF=Debug_GLEW_SDL2 clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
