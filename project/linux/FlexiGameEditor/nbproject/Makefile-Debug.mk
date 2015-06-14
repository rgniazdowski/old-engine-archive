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
CC=/usr/lib/distcc/bin/gcc
CCC=/usr/lib/distcc/bin/g++
CXX=/usr/lib/distcc/bin/g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile.nb

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CBspMaterialsEditDialog.o \
	${OBJECTDIR}/CEditorConfigPanel.o \
	${OBJECTDIR}/CEditorDrawingBatchFrame.o \
	${OBJECTDIR}/CEditorEventMgrPanel.o \
	${OBJECTDIR}/CEditorResMgrPanel.o \
	${OBJECTDIR}/CEditorScriptMgrPanel.o \
	${OBJECTDIR}/CEngineGfxCanvas.o \
	${OBJECTDIR}/CGfxHolderPanel.o \
	${OBJECTDIR}/CPreviewBspBuilder.o \
	${OBJECTDIR}/FlexiGameEditorApp.o \
	${OBJECTDIR}/FlexiGameEditorMain.o


# C Compiler Flags
CFLAGS=-m64 `wx-config --cflags` 

# CC Compiler Flags
CCFLAGS=-m64 `wx-config --cxxflags` -Wno-deprecated-declarations 
CXXFLAGS=-m64 `wx-config --cxxflags` -Wno-deprecated-declarations 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lm -ljpeg `pkg-config --libs glew` `pkg-config --libs gl` `pkg-config --libs zlib` `pkg-config --libs libpng` ../FlexiGame_NB/dist/Debug_GLEW_StaticLib/GNU-Linux-x86/libflexigame_nb.a ../LuaPlusNextGen_NB/dist/Debug/GNU-Linux-x86/libluaplusnextgen_nb.a ../MiniZipMaster_NB/dist/Debug/GNU-Linux-x86/libminizipmaster_nb.a -ldl  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/${CND_CONF}/FlexiGameEditor

bin/${CND_CONF}/FlexiGameEditor: ../FlexiGame_NB/dist/Debug_GLEW_StaticLib/GNU-Linux-x86/libflexigame_nb.a

bin/${CND_CONF}/FlexiGameEditor: ../LuaPlusNextGen_NB/dist/Debug/GNU-Linux-x86/libluaplusnextgen_nb.a

bin/${CND_CONF}/FlexiGameEditor: ../MiniZipMaster_NB/dist/Debug/GNU-Linux-x86/libminizipmaster_nb.a

bin/${CND_CONF}/FlexiGameEditor: ${OBJECTFILES}
	${MKDIR} -p bin/${CND_CONF}
	${LINK.cc} -o bin/${CND_CONF}/FlexiGameEditor ${OBJECTFILES} ${LDLIBSOPTIONS} `wx-config --libs` `wx-config --gl-libs`

${OBJECTDIR}/CBspMaterialsEditDialog.o: CBspMaterialsEditDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CBspMaterialsEditDialog.o CBspMaterialsEditDialog.cpp

${OBJECTDIR}/CEditorConfigPanel.o: CEditorConfigPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEditorConfigPanel.o CEditorConfigPanel.cpp

${OBJECTDIR}/CEditorDrawingBatchFrame.o: CEditorDrawingBatchFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEditorDrawingBatchFrame.o CEditorDrawingBatchFrame.cpp

${OBJECTDIR}/CEditorEventMgrPanel.o: CEditorEventMgrPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEditorEventMgrPanel.o CEditorEventMgrPanel.cpp

${OBJECTDIR}/CEditorResMgrPanel.o: CEditorResMgrPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEditorResMgrPanel.o CEditorResMgrPanel.cpp

${OBJECTDIR}/CEditorScriptMgrPanel.o: CEditorScriptMgrPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEditorScriptMgrPanel.o CEditorScriptMgrPanel.cpp

${OBJECTDIR}/CEngineGfxCanvas.o: CEngineGfxCanvas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CEngineGfxCanvas.o CEngineGfxCanvas.cpp

${OBJECTDIR}/CGfxHolderPanel.o: CGfxHolderPanel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CGfxHolderPanel.o CGfxHolderPanel.cpp

${OBJECTDIR}/CPreviewBspBuilder.o: CPreviewBspBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CPreviewBspBuilder.o CPreviewBspBuilder.cpp

${OBJECTDIR}/FlexiGameEditorApp.o: FlexiGameEditorApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FlexiGameEditorApp.o FlexiGameEditorApp.cpp

${OBJECTDIR}/FlexiGameEditorMain.o: FlexiGameEditorMain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLEW -DFG_USING_GLM -DFG_USING_LUA_PLUS -DFG_USING_OPENGL -DFG_USING_OPENGL_GLEW -DFG_USING_THREADS -DFG_USING_TINYXML -DTIXML_USE_STL -DWXUSINGDLL -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -I/usr/lib/wx/include/gtk2-unicode-3.0 -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree `pkg-config --cflags glew` `pkg-config --cflags gl` `pkg-config --cflags zlib` `pkg-config --cflags libpng` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FlexiGameEditorMain.o FlexiGameEditorMain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/${CND_CONF}/FlexiGameEditor

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
