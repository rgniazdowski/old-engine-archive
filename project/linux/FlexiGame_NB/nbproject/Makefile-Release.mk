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
include Makefile.nb

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1690346760/AbstractFunction.o \
	${OBJECTDIR}/_ext/1690346760/AbstractValue.o \
	${OBJECTDIR}/_ext/1690346760/Binding.o \
	${OBJECTDIR}/_ext/1690346760/Binding_objects.o \
	${OBJECTDIR}/_ext/1690346760/ContextHandle.o \
	${OBJECTDIR}/_ext/1690346760/ContextInfo.o \
	${OBJECTDIR}/_ext/1690346760/Meta.o \
	${OBJECTDIR}/_ext/1690346760/Meta_BitfieldsByString.o \
	${OBJECTDIR}/_ext/1690346760/Meta_BooleansByString.o \
	${OBJECTDIR}/_ext/1690346760/Meta_EnumsByString.o \
	${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByFunctionString.o \
	${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByString.o \
	${OBJECTDIR}/_ext/1690346760/Meta_FunctionStringsByExtension.o \
	${OBJECTDIR}/_ext/1690346760/Meta_ReqVersionsByExtension.o \
	${OBJECTDIR}/_ext/1690346760/Meta_StringsByBitfield.o \
	${OBJECTDIR}/_ext/1690346760/Meta_StringsByBoolean.o \
	${OBJECTDIR}/_ext/1690346760/Meta_StringsByEnum.o \
	${OBJECTDIR}/_ext/1690346760/Meta_StringsByExtension.o \
	${OBJECTDIR}/_ext/1690346760/ProcAddress.o \
	${OBJECTDIR}/_ext/1690346760/Value.o \
	${OBJECTDIR}/_ext/1690346760/Version.o \
	${OBJECTDIR}/_ext/1690346760/Version_ValidVersions.o \
	${OBJECTDIR}/_ext/1690346760/callbacks.o \
	${OBJECTDIR}/_ext/1371266908/types.o \
	${OBJECTDIR}/_ext/1279852618/fgTinyObj.o \
	${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o \
	${OBJECTDIR}/_ext/538025686/tinystr.o \
	${OBJECTDIR}/_ext/538025686/tinyxml.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlerror.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlparser.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXManager.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o \
	${OBJECTDIR}/_ext/1654483616/fgArgumentList.o \
	${OBJECTDIR}/_ext/1654483616/fgEventManager.o \
	${OBJECTDIR}/_ext/293675389/fgParticleSystem.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o \
	${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o \
	${OBJECTDIR}/_ext/960776194/fgGFXShader.o \
	${OBJECTDIR}/_ext/960776194/fgGFXShaderBase.o \
	${OBJECTDIR}/_ext/960776194/fgGFXShaderConfig.o \
	${OBJECTDIR}/_ext/960776194/fgGFXShaderManager.o \
	${OBJECTDIR}/_ext/960776194/fgGFXShaderProgram.o \
	${OBJECTDIR}/_ext/34731496/fgTextureLoader.o \
	${OBJECTDIR}/_ext/34731496/fgTextureManager.o \
	${OBJECTDIR}/_ext/34731496/fgTextureResource.o \
	${OBJECTDIR}/_ext/534590209/fgGFX2DScene.o \
	${OBJECTDIR}/_ext/534590209/fgGFX3DScene.o \
	${OBJECTDIR}/_ext/534590209/fgGFXCamera.o \
	${OBJECTDIR}/_ext/534590209/fgGFXCameraAnimation.o \
	${OBJECTDIR}/_ext/534590209/fgGFXContext.o \
	${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o \
	${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o \
	${OBJECTDIR}/_ext/534590209/fgGFXLight.o \
	${OBJECTDIR}/_ext/534590209/fgGFXMain.o \
	${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o \
	${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o \
	${OBJECTDIR}/_ext/534590209/fgGFXModelTypes.o \
	${OBJECTDIR}/_ext/534590209/fgGFXObject.o \
	${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o \
	${OBJECTDIR}/_ext/534590209/fgGFXPlatform.o \
	${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o \
	${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o \
	${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o \
	${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o \
	${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o \
	${OBJECTDIR}/_ext/534590209/fgGFXVertexData.o \
	${OBJECTDIR}/_ext/534590209/fgGFXWindow.o \
	${OBJECTDIR}/_ext/1216539907/fgFontBuiltIn.o \
	${OBJECTDIR}/_ext/1216539907/fgFontDrawer.o \
	${OBJECTDIR}/_ext/1216539907/fgFontResource.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbArial.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbArialBold.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbConsolas.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbConsolasBold.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbCourier.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbCourierBold.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbTimes.o \
	${OBJECTDIR}/_ext/1216539907/fgFontStbTimesBold.o \
	${OBJECTDIR}/_ext/534589759/fgGuiButton.o \
	${OBJECTDIR}/_ext/534589759/fgGuiCallback.o \
	${OBJECTDIR}/_ext/534589759/fgGuiConsole.o \
	${OBJECTDIR}/_ext/534589759/fgGuiContainer.o \
	${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o \
	${OBJECTDIR}/_ext/534589759/fgGuiEditableText.o \
	${OBJECTDIR}/_ext/534589759/fgGuiFrame.o \
	${OBJECTDIR}/_ext/534589759/fgGuiLabel.o \
	${OBJECTDIR}/_ext/534589759/fgGuiLoader.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMain.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMenu.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o \
	${OBJECTDIR}/_ext/534589759/fgGuiPopup.o \
	${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o \
	${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o \
	${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o \
	${OBJECTDIR}/_ext/534589759/fgGuiScrollArea.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyle.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetConfig.o \
	${OBJECTDIR}/_ext/534589759/fgGuiTable.o \
	${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o \
	${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidget.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidgetManager.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWindow.o \
	${OBJECTDIR}/_ext/477241454/fgGameLogic.o \
	${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o \
	${OBJECTDIR}/_ext/484399070/fgHardwareState.o \
	${OBJECTDIR}/_ext/484399070/fgQualityManager.o \
	${OBJECTDIR}/_ext/484399070/fgSensors.o \
	${OBJECTDIR}/_ext/1657950160/fgJoypadController.o \
	${OBJECTDIR}/_ext/1657950160/fgPointerInputReceiver.o \
	${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o \
	${OBJECTDIR}/_ext/942373304/fgResource.o \
	${OBJECTDIR}/_ext/942373304/fgResourceConfigParser.o \
	${OBJECTDIR}/_ext/942373304/fgResourceFactory.o \
	${OBJECTDIR}/_ext/942373304/fgResourceGroup.o \
	${OBJECTDIR}/_ext/942373304/fgResourceManager.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptCallback.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptMT.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptResource.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptSubsystem.o \
	${OBJECTDIR}/_ext/166270660/fgThread.o \
	${OBJECTDIR}/_ext/166270660/fgThreadSem.o \
	${OBJECTDIR}/_ext/608034620/fgConfig.o \
	${OBJECTDIR}/_ext/608034620/fgConfigParser.o \
	${OBJECTDIR}/_ext/608034620/fgConfigWriter.o \
	${OBJECTDIR}/_ext/608034620/fgDirent.o \
	${OBJECTDIR}/_ext/608034620/fgFile.o \
	${OBJECTDIR}/_ext/608034620/fgHashFunc.o \
	${OBJECTDIR}/_ext/608034620/fgPath.o \
	${OBJECTDIR}/_ext/608034620/fgProfiling.o \
	${OBJECTDIR}/_ext/608034620/fgSettings.o \
	${OBJECTDIR}/_ext/608034620/fgTime.o \
	${OBJECTDIR}/_ext/534573667/fgXMLParser.o \
	${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o \
	${OBJECTDIR}/_ext/1386528437/fgColors.o \
	${OBJECTDIR}/_ext/1386528437/fgCommon.o \
	${OBJECTDIR}/_ext/1386528437/fgErrno.o \
	${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o \
	${OBJECTDIR}/_ext/1386528437/fgGameMain.o \
	${OBJECTDIR}/_ext/1386528437/fgLog.o \
	${OBJECTDIR}/_ext/1386528437/fgMainModule.o \
	${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o \
	${OBJECTDIR}/_ext/1386528437/fgStatusReporter.o


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
LDLIBSOPTIONS=`pkg-config --libs libpng` -lm  -ljpeg `pkg-config --libs gl`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb ${OBJECTFILES} ${LDLIBSOPTIONS} -s

${OBJECTDIR}/_ext/1690346760/AbstractFunction.o: ../../../modules/glbinding/source/glbinding/source/AbstractFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/AbstractFunction.o ../../../modules/glbinding/source/glbinding/source/AbstractFunction.cpp

${OBJECTDIR}/_ext/1690346760/AbstractValue.o: ../../../modules/glbinding/source/glbinding/source/AbstractValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/AbstractValue.o ../../../modules/glbinding/source/glbinding/source/AbstractValue.cpp

${OBJECTDIR}/_ext/1690346760/Binding.o: ../../../modules/glbinding/source/glbinding/source/Binding.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Binding.o ../../../modules/glbinding/source/glbinding/source/Binding.cpp

${OBJECTDIR}/_ext/1690346760/Binding_objects.o: ../../../modules/glbinding/source/glbinding/source/Binding_objects.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Binding_objects.o ../../../modules/glbinding/source/glbinding/source/Binding_objects.cpp

${OBJECTDIR}/_ext/1690346760/ContextHandle.o: ../../../modules/glbinding/source/glbinding/source/ContextHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/ContextHandle.o ../../../modules/glbinding/source/glbinding/source/ContextHandle.cpp

${OBJECTDIR}/_ext/1690346760/ContextInfo.o: ../../../modules/glbinding/source/glbinding/source/ContextInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/ContextInfo.o ../../../modules/glbinding/source/glbinding/source/ContextInfo.cpp

${OBJECTDIR}/_ext/1690346760/Meta.o: ../../../modules/glbinding/source/glbinding/source/Meta.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta.o ../../../modules/glbinding/source/glbinding/source/Meta.cpp

${OBJECTDIR}/_ext/1690346760/Meta_BitfieldsByString.o: ../../../modules/glbinding/source/glbinding/source/Meta_BitfieldsByString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_BitfieldsByString.o ../../../modules/glbinding/source/glbinding/source/Meta_BitfieldsByString.cpp

${OBJECTDIR}/_ext/1690346760/Meta_BooleansByString.o: ../../../modules/glbinding/source/glbinding/source/Meta_BooleansByString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_BooleansByString.o ../../../modules/glbinding/source/glbinding/source/Meta_BooleansByString.cpp

${OBJECTDIR}/_ext/1690346760/Meta_EnumsByString.o: ../../../modules/glbinding/source/glbinding/source/Meta_EnumsByString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_EnumsByString.o ../../../modules/glbinding/source/glbinding/source/Meta_EnumsByString.cpp

${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByFunctionString.o: ../../../modules/glbinding/source/glbinding/source/Meta_ExtensionsByFunctionString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByFunctionString.o ../../../modules/glbinding/source/glbinding/source/Meta_ExtensionsByFunctionString.cpp

${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByString.o: ../../../modules/glbinding/source/glbinding/source/Meta_ExtensionsByString.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_ExtensionsByString.o ../../../modules/glbinding/source/glbinding/source/Meta_ExtensionsByString.cpp

${OBJECTDIR}/_ext/1690346760/Meta_FunctionStringsByExtension.o: ../../../modules/glbinding/source/glbinding/source/Meta_FunctionStringsByExtension.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_FunctionStringsByExtension.o ../../../modules/glbinding/source/glbinding/source/Meta_FunctionStringsByExtension.cpp

${OBJECTDIR}/_ext/1690346760/Meta_ReqVersionsByExtension.o: ../../../modules/glbinding/source/glbinding/source/Meta_ReqVersionsByExtension.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_ReqVersionsByExtension.o ../../../modules/glbinding/source/glbinding/source/Meta_ReqVersionsByExtension.cpp

${OBJECTDIR}/_ext/1690346760/Meta_StringsByBitfield.o: ../../../modules/glbinding/source/glbinding/source/Meta_StringsByBitfield.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_StringsByBitfield.o ../../../modules/glbinding/source/glbinding/source/Meta_StringsByBitfield.cpp

${OBJECTDIR}/_ext/1690346760/Meta_StringsByBoolean.o: ../../../modules/glbinding/source/glbinding/source/Meta_StringsByBoolean.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_StringsByBoolean.o ../../../modules/glbinding/source/glbinding/source/Meta_StringsByBoolean.cpp

${OBJECTDIR}/_ext/1690346760/Meta_StringsByEnum.o: ../../../modules/glbinding/source/glbinding/source/Meta_StringsByEnum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_StringsByEnum.o ../../../modules/glbinding/source/glbinding/source/Meta_StringsByEnum.cpp

${OBJECTDIR}/_ext/1690346760/Meta_StringsByExtension.o: ../../../modules/glbinding/source/glbinding/source/Meta_StringsByExtension.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Meta_StringsByExtension.o ../../../modules/glbinding/source/glbinding/source/Meta_StringsByExtension.cpp

${OBJECTDIR}/_ext/1690346760/ProcAddress.o: ../../../modules/glbinding/source/glbinding/source/ProcAddress.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/ProcAddress.o ../../../modules/glbinding/source/glbinding/source/ProcAddress.cpp

${OBJECTDIR}/_ext/1690346760/Value.o: ../../../modules/glbinding/source/glbinding/source/Value.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Value.o ../../../modules/glbinding/source/glbinding/source/Value.cpp

${OBJECTDIR}/_ext/1690346760/Version.o: ../../../modules/glbinding/source/glbinding/source/Version.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Version.o ../../../modules/glbinding/source/glbinding/source/Version.cpp

${OBJECTDIR}/_ext/1690346760/Version_ValidVersions.o: ../../../modules/glbinding/source/glbinding/source/Version_ValidVersions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/Version_ValidVersions.o ../../../modules/glbinding/source/glbinding/source/Version_ValidVersions.cpp

${OBJECTDIR}/_ext/1690346760/callbacks.o: ../../../modules/glbinding/source/glbinding/source/callbacks.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1690346760
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1690346760/callbacks.o ../../../modules/glbinding/source/glbinding/source/callbacks.cpp

${OBJECTDIR}/_ext/1371266908/types.o: ../../../modules/glbinding/source/glbinding/source/gl/types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1371266908
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1371266908/types.o ../../../modules/glbinding/source/glbinding/source/gl/types.cpp

${OBJECTDIR}/_ext/1279852618/fgTinyObj.o: ../../../modules/tinyobj/upstream/fgTinyObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1279852618
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1279852618/fgTinyObj.o ../../../modules/tinyobj/upstream/fgTinyObj.cpp

${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o: ../../../modules/tinyobj/upstream/tiny_obj_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1279852618
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o ../../../modules/tinyobj/upstream/tiny_obj_loader.cpp

${OBJECTDIR}/_ext/538025686/tinystr.o: ../../../modules/tinyxml/upstream/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinystr.o ../../../modules/tinyxml/upstream/tinystr.cpp

${OBJECTDIR}/_ext/538025686/tinyxml.o: ../../../modules/tinyxml/upstream/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxml.o ../../../modules/tinyxml/upstream/tinyxml.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlerror.o: ../../../modules/tinyxml/upstream/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlerror.o ../../../modules/tinyxml/upstream/tinyxmlerror.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlparser.o: ../../../modules/tinyxml/upstream/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlparser.o ../../../modules/tinyxml/upstream/tinyxmlparser.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXManager.o: ../../../src/Audio/fgSFXManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXManager.o ../../../src/Audio/fgSFXManager.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o: ../../../src/Audio/fgSFXMusicResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o ../../../src/Audio/fgSFXMusicResource.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o: ../../../src/Audio/fgSFXSoundResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o ../../../src/Audio/fgSFXSoundResource.cpp

${OBJECTDIR}/_ext/1654483616/fgArgumentList.o: ../../../src/Event/fgArgumentList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgArgumentList.o ../../../src/Event/fgArgumentList.cpp

${OBJECTDIR}/_ext/1654483616/fgEventManager.o: ../../../src/Event/fgEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgEventManager.o ../../../src/Event/fgEventManager.cpp

${OBJECTDIR}/_ext/293675389/fgParticleSystem.o: ../../../src/GFX/Particles/fgParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgParticleSystem.o ../../../src/GFX/Particles/fgParticleSystem.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o: ../../../src/GFX/Particles/fgPsParticleEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o ../../../src/GFX/Particles/fgPsParticleEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o: ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o: ../../../src/GFX/Particles/fgPsParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o ../../../src/GFX/Particles/fgPsParticleEmitter.cpp

${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o: ../../../src/GFX/Particles/fgPsSequentialEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o ../../../src/GFX/Particles/fgPsSequentialEffect.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShader.o: ../../../src/GFX/Shaders/fgGFXShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShader.o ../../../src/GFX/Shaders/fgGFXShader.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderBase.o: ../../../src/GFX/Shaders/fgGFXShaderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderBase.o ../../../src/GFX/Shaders/fgGFXShaderBase.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderConfig.o: ../../../src/GFX/Shaders/fgGFXShaderConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderConfig.o ../../../src/GFX/Shaders/fgGFXShaderConfig.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderManager.o: ../../../src/GFX/Shaders/fgGFXShaderManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderManager.o ../../../src/GFX/Shaders/fgGFXShaderManager.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderProgram.o: ../../../src/GFX/Shaders/fgGFXShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderProgram.o ../../../src/GFX/Shaders/fgGFXShaderProgram.cpp

${OBJECTDIR}/_ext/34731496/fgTextureLoader.o: ../../../src/GFX/Textures/fgTextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureLoader.o ../../../src/GFX/Textures/fgTextureLoader.cpp

${OBJECTDIR}/_ext/34731496/fgTextureManager.o: ../../../src/GFX/Textures/fgTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureManager.o ../../../src/GFX/Textures/fgTextureManager.cpp

${OBJECTDIR}/_ext/34731496/fgTextureResource.o: ../../../src/GFX/Textures/fgTextureResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureResource.o ../../../src/GFX/Textures/fgTextureResource.cpp

${OBJECTDIR}/_ext/534590209/fgGFX2DScene.o: ../../../src/GFX/fgGFX2DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFX2DScene.o ../../../src/GFX/fgGFX2DScene.cpp

${OBJECTDIR}/_ext/534590209/fgGFX3DScene.o: ../../../src/GFX/fgGFX3DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFX3DScene.o ../../../src/GFX/fgGFX3DScene.cpp

${OBJECTDIR}/_ext/534590209/fgGFXCamera.o: ../../../src/GFX/fgGFXCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXCamera.o ../../../src/GFX/fgGFXCamera.cpp

${OBJECTDIR}/_ext/534590209/fgGFXCameraAnimation.o: ../../../src/GFX/fgGFXCameraAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXCameraAnimation.o ../../../src/GFX/fgGFXCameraAnimation.cpp

${OBJECTDIR}/_ext/534590209/fgGFXContext.o: ../../../src/GFX/fgGFXContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXContext.o ../../../src/GFX/fgGFXContext.cpp

${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o: ../../../src/GFX/fgGFXDrawCall.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o ../../../src/GFX/fgGFXDrawCall.cpp

${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o: ../../../src/GFX/fgGFXDrawingBatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o ../../../src/GFX/fgGFXDrawingBatch.cpp

${OBJECTDIR}/_ext/534590209/fgGFXLight.o: ../../../src/GFX/fgGFXLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXLight.o ../../../src/GFX/fgGFXLight.cpp

${OBJECTDIR}/_ext/534590209/fgGFXMain.o: ../../../src/GFX/fgGFXMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXMain.o ../../../src/GFX/fgGFXMain.cpp

${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o: ../../../src/GFX/fgGFXMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o ../../../src/GFX/fgGFXMaterial.cpp

${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o: ../../../src/GFX/fgGFXModelResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o ../../../src/GFX/fgGFXModelResource.cpp

${OBJECTDIR}/_ext/534590209/fgGFXModelTypes.o: ../../../src/GFX/fgGFXModelTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXModelTypes.o ../../../src/GFX/fgGFXModelTypes.cpp

${OBJECTDIR}/_ext/534590209/fgGFXObject.o: ../../../src/GFX/fgGFXObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXObject.o ../../../src/GFX/fgGFXObject.cpp

${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o: ../../../src/GFX/fgGFXOctreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o ../../../src/GFX/fgGFXOctreeBase.cpp

${OBJECTDIR}/_ext/534590209/fgGFXPlatform.o: ../../../src/GFX/fgGFXPlatform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXPlatform.o ../../../src/GFX/fgGFXPlatform.cpp

${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o: ../../../src/GFX/fgGFXPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o ../../../src/GFX/fgGFXPrimitives.cpp

${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o: ../../../src/GFX/fgGFXQuadtreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o ../../../src/GFX/fgGFXQuadtreeBase.cpp

${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o: ../../../src/GFX/fgGFXSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o ../../../src/GFX/fgGFXSceneManager.cpp

${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o: ../../../src/GFX/fgGFXSimpleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o ../../../src/GFX/fgGFXSimpleDrawer.cpp

${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o: ../../../src/GFX/fgGFXTexturing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o ../../../src/GFX/fgGFXTexturing.cpp

${OBJECTDIR}/_ext/534590209/fgGFXVertexData.o: ../../../src/GFX/fgGFXVertexData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXVertexData.o ../../../src/GFX/fgGFXVertexData.cpp

${OBJECTDIR}/_ext/534590209/fgGFXWindow.o: ../../../src/GFX/fgGFXWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXWindow.o ../../../src/GFX/fgGFXWindow.cpp

${OBJECTDIR}/_ext/1216539907/fgFontBuiltIn.o: ../../../src/GUI/Font/fgFontBuiltIn.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontBuiltIn.o ../../../src/GUI/Font/fgFontBuiltIn.cpp

${OBJECTDIR}/_ext/1216539907/fgFontDrawer.o: ../../../src/GUI/Font/fgFontDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontDrawer.o ../../../src/GUI/Font/fgFontDrawer.cpp

${OBJECTDIR}/_ext/1216539907/fgFontResource.o: ../../../src/GUI/Font/fgFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontResource.o ../../../src/GUI/Font/fgFontResource.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbArial.o: ../../../src/GUI/Font/fgFontStbArial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbArial.o ../../../src/GUI/Font/fgFontStbArial.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbArialBold.o: ../../../src/GUI/Font/fgFontStbArialBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbArialBold.o ../../../src/GUI/Font/fgFontStbArialBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbConsolas.o: ../../../src/GUI/Font/fgFontStbConsolas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbConsolas.o ../../../src/GUI/Font/fgFontStbConsolas.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbConsolasBold.o: ../../../src/GUI/Font/fgFontStbConsolasBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbConsolasBold.o ../../../src/GUI/Font/fgFontStbConsolasBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbCourier.o: ../../../src/GUI/Font/fgFontStbCourier.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbCourier.o ../../../src/GUI/Font/fgFontStbCourier.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbCourierBold.o: ../../../src/GUI/Font/fgFontStbCourierBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbCourierBold.o ../../../src/GUI/Font/fgFontStbCourierBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbTimes.o: ../../../src/GUI/Font/fgFontStbTimes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbTimes.o ../../../src/GUI/Font/fgFontStbTimes.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbTimesBold.o: ../../../src/GUI/Font/fgFontStbTimesBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbTimesBold.o ../../../src/GUI/Font/fgFontStbTimesBold.cpp

${OBJECTDIR}/_ext/534589759/fgGuiButton.o: ../../../src/GUI/fgGuiButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiButton.o ../../../src/GUI/fgGuiButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiCallback.o: ../../../src/GUI/fgGuiCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiCallback.o ../../../src/GUI/fgGuiCallback.cpp

${OBJECTDIR}/_ext/534589759/fgGuiConsole.o: ../../../src/GUI/fgGuiConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiConsole.o ../../../src/GUI/fgGuiConsole.cpp

${OBJECTDIR}/_ext/534589759/fgGuiContainer.o: ../../../src/GUI/fgGuiContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiContainer.o ../../../src/GUI/fgGuiContainer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o: ../../../src/GUI/fgGuiDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o ../../../src/GUI/fgGuiDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiEditableText.o: ../../../src/GUI/fgGuiEditableText.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiEditableText.o ../../../src/GUI/fgGuiEditableText.cpp

${OBJECTDIR}/_ext/534589759/fgGuiFrame.o: ../../../src/GUI/fgGuiFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiFrame.o ../../../src/GUI/fgGuiFrame.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLabel.o: ../../../src/GUI/fgGuiLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLabel.o ../../../src/GUI/fgGuiLabel.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLoader.o: ../../../src/GUI/fgGuiLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLoader.o ../../../src/GUI/fgGuiLoader.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMain.o: ../../../src/GUI/fgGuiMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMain.o ../../../src/GUI/fgGuiMain.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMenu.o: ../../../src/GUI/fgGuiMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMenu.o ../../../src/GUI/fgGuiMenu.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o: ../../../src/GUI/fgGuiMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o ../../../src/GUI/fgGuiMessageBox.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPopup.o: ../../../src/GUI/fgGuiPopup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPopup.o ../../../src/GUI/fgGuiPopup.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o: ../../../src/GUI/fgGuiPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o ../../../src/GUI/fgGuiPrimitives.cpp

${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o: ../../../src/GUI/fgGuiProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o ../../../src/GUI/fgGuiProgressBar.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o: ../../../src/GUI/fgGuiScreenGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o ../../../src/GUI/fgGuiScreenGrid.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScrollArea.o: ../../../src/GUI/fgGuiScrollArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScrollArea.o ../../../src/GUI/fgGuiScrollArea.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o: ../../../src/GUI/fgGuiStructureSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o ../../../src/GUI/fgGuiStructureSheet.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o: ../../../src/GUI/fgGuiStructureSheetParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o ../../../src/GUI/fgGuiStructureSheetParser.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyle.o: ../../../src/GUI/fgGuiStyle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyle.o ../../../src/GUI/fgGuiStyle.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o: ../../../src/GUI/fgGuiStyleContent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o ../../../src/GUI/fgGuiStyleContent.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o: ../../../src/GUI/fgGuiStyleManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o ../../../src/GUI/fgGuiStyleManager.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetConfig.o: ../../../src/GUI/fgGuiStyleSheetConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetConfig.o ../../../src/GUI/fgGuiStyleSheetConfig.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTable.o: ../../../src/GUI/fgGuiTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTable.o ../../../src/GUI/fgGuiTable.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o: ../../../src/GUI/fgGuiTextArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o ../../../src/GUI/fgGuiTextArea.cpp

${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o: ../../../src/GUI/fgGuiToggleButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o ../../../src/GUI/fgGuiToggleButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidget.o: ../../../src/GUI/fgGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidget.o ../../../src/GUI/fgGuiWidget.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o: ../../../src/GUI/fgGuiWidgetFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o ../../../src/GUI/fgGuiWidgetFactory.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidgetManager.o: ../../../src/GUI/fgGuiWidgetManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidgetManager.o ../../../src/GUI/fgGuiWidgetManager.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWindow.o: ../../../src/GUI/fgGuiWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWindow.o ../../../src/GUI/fgGuiWindow.cpp

${OBJECTDIR}/_ext/477241454/fgGameLogic.o: ../../../src/GameLogic/fgGameLogic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/477241454
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/477241454/fgGameLogic.o ../../../src/GameLogic/fgGameLogic.cpp

${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o: ../../../src/Hardware/fgDeviceQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o ../../../src/Hardware/fgDeviceQuery.cpp

${OBJECTDIR}/_ext/484399070/fgHardwareState.o: ../../../src/Hardware/fgHardwareState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgHardwareState.o ../../../src/Hardware/fgHardwareState.cpp

${OBJECTDIR}/_ext/484399070/fgQualityManager.o: ../../../src/Hardware/fgQualityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgQualityManager.o ../../../src/Hardware/fgQualityManager.cpp

${OBJECTDIR}/_ext/484399070/fgSensors.o: ../../../src/Hardware/fgSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgSensors.o ../../../src/Hardware/fgSensors.cpp

${OBJECTDIR}/_ext/1657950160/fgJoypadController.o: ../../../src/Input/fgJoypadController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1657950160
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1657950160/fgJoypadController.o ../../../src/Input/fgJoypadController.cpp

${OBJECTDIR}/_ext/1657950160/fgPointerInputReceiver.o: ../../../src/Input/fgPointerInputReceiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1657950160
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1657950160/fgPointerInputReceiver.o ../../../src/Input/fgPointerInputReceiver.cpp

${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o: ../../../src/Math/fgKalmanFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607778370
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o ../../../src/Math/fgKalmanFilter.cpp

${OBJECTDIR}/_ext/942373304/fgResource.o: ../../../src/Resource/fgResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResource.o ../../../src/Resource/fgResource.cpp

${OBJECTDIR}/_ext/942373304/fgResourceConfigParser.o: ../../../src/Resource/fgResourceConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceConfigParser.o ../../../src/Resource/fgResourceConfigParser.cpp

${OBJECTDIR}/_ext/942373304/fgResourceFactory.o: ../../../src/Resource/fgResourceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceFactory.o ../../../src/Resource/fgResourceFactory.cpp

${OBJECTDIR}/_ext/942373304/fgResourceGroup.o: ../../../src/Resource/fgResourceGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceGroup.o ../../../src/Resource/fgResourceGroup.cpp

${OBJECTDIR}/_ext/942373304/fgResourceManager.o: ../../../src/Resource/fgResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceManager.o ../../../src/Resource/fgResourceManager.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptCallback.o: ../../../src/Scripting/fgScriptCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptCallback.o ../../../src/Scripting/fgScriptCallback.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptMT.o: ../../../src/Scripting/fgScriptMT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptMT.o ../../../src/Scripting/fgScriptMT.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptResource.o: ../../../src/Scripting/fgScriptResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptResource.o ../../../src/Scripting/fgScriptResource.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptSubsystem.o: ../../../src/Scripting/fgScriptSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptSubsystem.o ../../../src/Scripting/fgScriptSubsystem.cpp

${OBJECTDIR}/_ext/166270660/fgThread.o: ../../../src/Thread/fgThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/166270660
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/166270660/fgThread.o ../../../src/Thread/fgThread.cpp

${OBJECTDIR}/_ext/166270660/fgThreadSem.o: ../../../src/Thread/fgThreadSem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/166270660
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/166270660/fgThreadSem.o ../../../src/Thread/fgThreadSem.cpp

${OBJECTDIR}/_ext/608034620/fgConfig.o: ../../../src/Util/fgConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfig.o ../../../src/Util/fgConfig.cpp

${OBJECTDIR}/_ext/608034620/fgConfigParser.o: ../../../src/Util/fgConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigParser.o ../../../src/Util/fgConfigParser.cpp

${OBJECTDIR}/_ext/608034620/fgConfigWriter.o: ../../../src/Util/fgConfigWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigWriter.o ../../../src/Util/fgConfigWriter.cpp

${OBJECTDIR}/_ext/608034620/fgDirent.o: ../../../src/Util/fgDirent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgDirent.o ../../../src/Util/fgDirent.cpp

${OBJECTDIR}/_ext/608034620/fgFile.o: ../../../src/Util/fgFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgFile.o ../../../src/Util/fgFile.cpp

${OBJECTDIR}/_ext/608034620/fgHashFunc.o: ../../../src/Util/fgHashFunc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgHashFunc.o ../../../src/Util/fgHashFunc.cpp

${OBJECTDIR}/_ext/608034620/fgPath.o: ../../../src/Util/fgPath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgPath.o ../../../src/Util/fgPath.cpp

${OBJECTDIR}/_ext/608034620/fgProfiling.o: ../../../src/Util/fgProfiling.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgProfiling.o ../../../src/Util/fgProfiling.cpp

${OBJECTDIR}/_ext/608034620/fgSettings.o: ../../../src/Util/fgSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgSettings.o ../../../src/Util/fgSettings.cpp

${OBJECTDIR}/_ext/608034620/fgTime.o: ../../../src/Util/fgTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgTime.o ../../../src/Util/fgTime.cpp

${OBJECTDIR}/_ext/534573667/fgXMLParser.o: ../../../src/XML/fgXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534573667
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534573667/fgXMLParser.o ../../../src/XML/fgXMLParser.cpp

${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o: ../../../src/fgBuildConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o ../../../src/fgBuildConfig.cpp

${OBJECTDIR}/_ext/1386528437/fgColors.o: ../../../src/fgColors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgColors.o ../../../src/fgColors.cpp

${OBJECTDIR}/_ext/1386528437/fgCommon.o: ../../../src/fgCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgCommon.o ../../../src/fgCommon.cpp

${OBJECTDIR}/_ext/1386528437/fgErrno.o: ../../../src/fgErrno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrno.o ../../../src/fgErrno.cpp

${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o: ../../../src/fgErrorCodes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o ../../../src/fgErrorCodes.cpp

${OBJECTDIR}/_ext/1386528437/fgGameMain.o: ../../../src/fgGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgGameMain.o ../../../src/fgGameMain.cpp

${OBJECTDIR}/_ext/1386528437/fgLog.o: ../../../src/fgLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgLog.o ../../../src/fgLog.cpp

${OBJECTDIR}/_ext/1386528437/fgMainModule.o: ../../../src/fgMainModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMainModule.o ../../../src/fgMainModule.cpp

${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o: ../../../src/fgMessageSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o ../../../src/fgMessageSubsystem.cpp

${OBJECTDIR}/_ext/1386528437/fgStatusReporter.o: ../../../src/fgStatusReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgStatusReporter.o ../../../src/fgStatusReporter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
