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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CLevelDataHolder.o \
	${OBJECTDIR}/CLevelFile.o \
	${OBJECTDIR}/CLevelGenerator.o \
	${OBJECTDIR}/CLevelSolver.o \
	${OBJECTDIR}/CLevelVisualization.o \
	${OBJECTDIR}/ChainReaction.o \
	${OBJECTDIR}/SBlockData.o \
	${OBJECTDIR}/SHexData.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libChainReaction.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libChainReaction.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libChainReaction.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/CLevelDataHolder.o: CLevelDataHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelDataHolder.o CLevelDataHolder.cpp

${OBJECTDIR}/CLevelFile.o: CLevelFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelFile.o CLevelFile.cpp

${OBJECTDIR}/CLevelGenerator.o: CLevelGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelGenerator.o CLevelGenerator.cpp

${OBJECTDIR}/CLevelSolver.o: CLevelSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelSolver.o CLevelSolver.cpp

${OBJECTDIR}/CLevelVisualization.o: CLevelVisualization.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLevelVisualization.o CLevelVisualization.cpp

${OBJECTDIR}/ChainReaction.o: ChainReaction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ChainReaction.o ChainReaction.cpp

${OBJECTDIR}/SBlockData.o: SBlockData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SBlockData.o SBlockData.cpp

${OBJECTDIR}/SHexData.o: SHexData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SHexData.o SHexData.cpp

${OBJECTDIR}/SQuadData.o: SQuadData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_SDL2 -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SQuadData.o SQuadData.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libChainReaction.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
