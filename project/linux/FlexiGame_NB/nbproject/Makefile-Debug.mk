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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile.nb

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1279852618/fgTinyObj.o \
	${OBJECTDIR}/_ext/538025686/tinystr.o \
	${OBJECTDIR}/_ext/538025686/tinyxml.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlerror.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlparser.o \
	${OBJECTDIR}/_ext/1335969013/fgAndroid.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXManager.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o \
	${OBJECTDIR}/_ext/1654483616/fgArgumentList.o \
	${OBJECTDIR}/_ext/1654483616/fgEventManager.o \
	${OBJECTDIR}/_ext/1654483616/fgInputHandler.o \
	${OBJECTDIR}/_ext/1654483616/fgJoypadController.o \
	${OBJECTDIR}/_ext/293675389/fgParticleSystem.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o \
	${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o \
	${OBJECTDIR}/_ext/1008910172/fgGfx2DScene.o \
	${OBJECTDIR}/_ext/1008910172/fgGfx3DScene.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxBasetree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxBspCompiler.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxBspGeometry.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxBspTree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxBspTypes.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxLooseOctree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxLooseQuadtree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxOctree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxPortalProcessor.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxPvsProcessor.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxQuadtree.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneManager.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneNode.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeMesh.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeObject.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeTrigger.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxSceneSkyBox.o \
	${OBJECTDIR}/_ext/1008910172/fgGfxTreeNode.o \
	${OBJECTDIR}/_ext/960776194/fgGfxShader.o \
	${OBJECTDIR}/_ext/960776194/fgGfxShaderBase.o \
	${OBJECTDIR}/_ext/960776194/fgGfxShaderConfig.o \
	${OBJECTDIR}/_ext/960776194/fgGfxShaderManager.o \
	${OBJECTDIR}/_ext/960776194/fgGfxShaderProgram.o \
	${OBJECTDIR}/_ext/34731496/fgTextureLoader.o \
	${OBJECTDIR}/_ext/34731496/fgTextureManager.o \
	${OBJECTDIR}/_ext/34731496/fgTextureResource.o \
	${OBJECTDIR}/_ext/534590209/fgGfxCamera.o \
	${OBJECTDIR}/_ext/534590209/fgGfxCameraAnimation.o \
	${OBJECTDIR}/_ext/534590209/fgGfxContext.o \
	${OBJECTDIR}/_ext/534590209/fgGfxDrawCall.o \
	${OBJECTDIR}/_ext/534590209/fgGfxDrawingBatch.o \
	${OBJECTDIR}/_ext/534590209/fgGfxFrustum.o \
	${OBJECTDIR}/_ext/534590209/fgGfxLight.o \
	${OBJECTDIR}/_ext/534590209/fgGfxMain.o \
	${OBJECTDIR}/_ext/534590209/fgGfxMaterial.o \
	${OBJECTDIR}/_ext/534590209/fgGfxModelResource.o \
	${OBJECTDIR}/_ext/534590209/fgGfxModelTypes.o \
	${OBJECTDIR}/_ext/534590209/fgGfxPlatform.o \
	${OBJECTDIR}/_ext/534590209/fgGfxPrimitives.o \
	${OBJECTDIR}/_ext/534590209/fgGfxSimpleDrawer.o \
	${OBJECTDIR}/_ext/534590209/fgGfxVertexData.o \
	${OBJECTDIR}/_ext/534590209/fgGfxWindow.o \
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
	${OBJECTDIR}/_ext/534589759/fgGuiSlider.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyle.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o \
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
	${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o \
	${OBJECTDIR}/_ext/1611265229/fgCollisionBody.o \
	${OBJECTDIR}/_ext/1611265229/fgCollisionCoarse.o \
	${OBJECTDIR}/_ext/1611265229/fgCollisionFine.o \
	${OBJECTDIR}/_ext/1611265229/fgContact.o \
	${OBJECTDIR}/_ext/1611265229/fgContactResolver.o \
	${OBJECTDIR}/_ext/1611265229/fgCycloneCoreMath.o \
	${OBJECTDIR}/_ext/1611265229/fgForceGenerator.o \
	${OBJECTDIR}/_ext/1611265229/fgJoint.o \
	${OBJECTDIR}/_ext/1611265229/fgParticle.o \
	${OBJECTDIR}/_ext/1611265229/fgParticleContact.o \
	${OBJECTDIR}/_ext/1611265229/fgParticleContactResolver.o \
	${OBJECTDIR}/_ext/1611265229/fgParticleForceGenerator.o \
	${OBJECTDIR}/_ext/1611265229/fgParticleLink.o \
	${OBJECTDIR}/_ext/1611265229/fgParticleWorld.o \
	${OBJECTDIR}/_ext/1611265229/fgRandom.o \
	${OBJECTDIR}/_ext/1611265229/fgRigidBody.o \
	${OBJECTDIR}/_ext/1611265229/fgWorld.o \
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
	${OBJECTDIR}/_ext/608034620/fgFastCmp.o \
	${OBJECTDIR}/_ext/608034620/fgFile.o \
	${OBJECTDIR}/_ext/608034620/fgHashFunc.o \
	${OBJECTDIR}/_ext/608034620/fgPath.o \
	${OBJECTDIR}/_ext/608034620/fgProfiling.o \
	${OBJECTDIR}/_ext/608034620/fgRegularFile.o \
	${OBJECTDIR}/_ext/608034620/fgSettings.o \
	${OBJECTDIR}/_ext/608034620/fgStrings.o \
	${OBJECTDIR}/_ext/608034620/fgTime.o \
	${OBJECTDIR}/_ext/608034620/fgZipFile.o \
	${OBJECTDIR}/_ext/534573667/fgXMLParser.o \
	${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o \
	${OBJECTDIR}/_ext/1386528437/fgColors.o \
	${OBJECTDIR}/_ext/1386528437/fgCommon.o \
	${OBJECTDIR}/_ext/1386528437/fgDebugConfig.o \
	${OBJECTDIR}/_ext/1386528437/fgErrno.o \
	${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o \
	${OBJECTDIR}/_ext/1386528437/fgGameMain.o \
	${OBJECTDIR}/_ext/1386528437/fgLog.o \
	${OBJECTDIR}/_ext/1386528437/fgMainModule.o \
	${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o


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
LDLIBSOPTIONS=`pkg-config --libs gl` `pkg-config --libs sdl2` `pkg-config --libs SDL2_mixer` `pkg-config --libs libpng` -ljpeg -lm  `pkg-config --libs zlib`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1279852618/fgTinyObj.o: ../../../modules/tinyobj/upstream/fgTinyObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1279852618
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1279852618/fgTinyObj.o ../../../modules/tinyobj/upstream/fgTinyObj.cpp

${OBJECTDIR}/_ext/538025686/tinystr.o: ../../../modules/tinyxml/upstream/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinystr.o ../../../modules/tinyxml/upstream/tinystr.cpp

${OBJECTDIR}/_ext/538025686/tinyxml.o: ../../../modules/tinyxml/upstream/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxml.o ../../../modules/tinyxml/upstream/tinyxml.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlerror.o: ../../../modules/tinyxml/upstream/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlerror.o ../../../modules/tinyxml/upstream/tinyxmlerror.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlparser.o: ../../../modules/tinyxml/upstream/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlparser.o ../../../modules/tinyxml/upstream/tinyxmlparser.cpp

${OBJECTDIR}/_ext/1335969013/fgAndroid.o: ../../../src/Android/fgAndroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1335969013
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1335969013/fgAndroid.o ../../../src/Android/fgAndroid.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXManager.o: ../../../src/Audio/fgSFXManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXManager.o ../../../src/Audio/fgSFXManager.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o: ../../../src/Audio/fgSFXMusicResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o ../../../src/Audio/fgSFXMusicResource.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o: ../../../src/Audio/fgSFXSoundResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXSoundResource.o ../../../src/Audio/fgSFXSoundResource.cpp

${OBJECTDIR}/_ext/1654483616/fgArgumentList.o: ../../../src/Event/fgArgumentList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgArgumentList.o ../../../src/Event/fgArgumentList.cpp

${OBJECTDIR}/_ext/1654483616/fgEventManager.o: ../../../src/Event/fgEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgEventManager.o ../../../src/Event/fgEventManager.cpp

${OBJECTDIR}/_ext/1654483616/fgInputHandler.o: ../../../src/Event/fgInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgInputHandler.o ../../../src/Event/fgInputHandler.cpp

${OBJECTDIR}/_ext/1654483616/fgJoypadController.o: ../../../src/Event/fgJoypadController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgJoypadController.o ../../../src/Event/fgJoypadController.cpp

${OBJECTDIR}/_ext/293675389/fgParticleSystem.o: ../../../src/GFX/Particles/fgParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgParticleSystem.o ../../../src/GFX/Particles/fgParticleSystem.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o: ../../../src/GFX/Particles/fgPsParticleEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o ../../../src/GFX/Particles/fgPsParticleEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o: ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o: ../../../src/GFX/Particles/fgPsParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEmitter.o ../../../src/GFX/Particles/fgPsParticleEmitter.cpp

${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o: ../../../src/GFX/Particles/fgPsSequentialEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o ../../../src/GFX/Particles/fgPsSequentialEffect.cpp

${OBJECTDIR}/_ext/1008910172/fgGfx2DScene.o: ../../../src/GFX/Scene/fgGfx2DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfx2DScene.o ../../../src/GFX/Scene/fgGfx2DScene.cpp

${OBJECTDIR}/_ext/1008910172/fgGfx3DScene.o: ../../../src/GFX/Scene/fgGfx3DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfx3DScene.o ../../../src/GFX/Scene/fgGfx3DScene.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxBasetree.o: ../../../src/GFX/Scene/fgGfxBasetree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxBasetree.o ../../../src/GFX/Scene/fgGfxBasetree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxBspCompiler.o: ../../../src/GFX/Scene/fgGfxBspCompiler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxBspCompiler.o ../../../src/GFX/Scene/fgGfxBspCompiler.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxBspGeometry.o: ../../../src/GFX/Scene/fgGfxBspGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxBspGeometry.o ../../../src/GFX/Scene/fgGfxBspGeometry.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxBspTree.o: ../../../src/GFX/Scene/fgGfxBspTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxBspTree.o ../../../src/GFX/Scene/fgGfxBspTree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxBspTypes.o: ../../../src/GFX/Scene/fgGfxBspTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxBspTypes.o ../../../src/GFX/Scene/fgGfxBspTypes.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxLooseOctree.o: ../../../src/GFX/Scene/fgGfxLooseOctree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxLooseOctree.o ../../../src/GFX/Scene/fgGfxLooseOctree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxLooseQuadtree.o: ../../../src/GFX/Scene/fgGfxLooseQuadtree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxLooseQuadtree.o ../../../src/GFX/Scene/fgGfxLooseQuadtree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxOctree.o: ../../../src/GFX/Scene/fgGfxOctree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxOctree.o ../../../src/GFX/Scene/fgGfxOctree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxPortalProcessor.o: ../../../src/GFX/Scene/fgGfxPortalProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxPortalProcessor.o ../../../src/GFX/Scene/fgGfxPortalProcessor.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxPvsProcessor.o: ../../../src/GFX/Scene/fgGfxPvsProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxPvsProcessor.o ../../../src/GFX/Scene/fgGfxPvsProcessor.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxQuadtree.o: ../../../src/GFX/Scene/fgGfxQuadtree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxQuadtree.o ../../../src/GFX/Scene/fgGfxQuadtree.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneManager.o: ../../../src/GFX/Scene/fgGfxSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneManager.o ../../../src/GFX/Scene/fgGfxSceneManager.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneNode.o: ../../../src/GFX/Scene/fgGfxSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneNode.o ../../../src/GFX/Scene/fgGfxSceneNode.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeMesh.o: ../../../src/GFX/Scene/fgGfxSceneNodeMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeMesh.o ../../../src/GFX/Scene/fgGfxSceneNodeMesh.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeObject.o: ../../../src/GFX/Scene/fgGfxSceneNodeObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeObject.o ../../../src/GFX/Scene/fgGfxSceneNodeObject.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeTrigger.o: ../../../src/GFX/Scene/fgGfxSceneNodeTrigger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneNodeTrigger.o ../../../src/GFX/Scene/fgGfxSceneNodeTrigger.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxSceneSkyBox.o: ../../../src/GFX/Scene/fgGfxSceneSkyBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxSceneSkyBox.o ../../../src/GFX/Scene/fgGfxSceneSkyBox.cpp

${OBJECTDIR}/_ext/1008910172/fgGfxTreeNode.o: ../../../src/GFX/Scene/fgGfxTreeNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008910172
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1008910172/fgGfxTreeNode.o ../../../src/GFX/Scene/fgGfxTreeNode.cpp

${OBJECTDIR}/_ext/960776194/fgGfxShader.o: ../../../src/GFX/Shaders/fgGfxShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGfxShader.o ../../../src/GFX/Shaders/fgGfxShader.cpp

${OBJECTDIR}/_ext/960776194/fgGfxShaderBase.o: ../../../src/GFX/Shaders/fgGfxShaderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGfxShaderBase.o ../../../src/GFX/Shaders/fgGfxShaderBase.cpp

${OBJECTDIR}/_ext/960776194/fgGfxShaderConfig.o: ../../../src/GFX/Shaders/fgGfxShaderConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGfxShaderConfig.o ../../../src/GFX/Shaders/fgGfxShaderConfig.cpp

${OBJECTDIR}/_ext/960776194/fgGfxShaderManager.o: ../../../src/GFX/Shaders/fgGfxShaderManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGfxShaderManager.o ../../../src/GFX/Shaders/fgGfxShaderManager.cpp

${OBJECTDIR}/_ext/960776194/fgGfxShaderProgram.o: ../../../src/GFX/Shaders/fgGfxShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGfxShaderProgram.o ../../../src/GFX/Shaders/fgGfxShaderProgram.cpp

${OBJECTDIR}/_ext/34731496/fgTextureLoader.o: ../../../src/GFX/Textures/fgTextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureLoader.o ../../../src/GFX/Textures/fgTextureLoader.cpp

${OBJECTDIR}/_ext/34731496/fgTextureManager.o: ../../../src/GFX/Textures/fgTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureManager.o ../../../src/GFX/Textures/fgTextureManager.cpp

${OBJECTDIR}/_ext/34731496/fgTextureResource.o: ../../../src/GFX/Textures/fgTextureResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureResource.o ../../../src/GFX/Textures/fgTextureResource.cpp

${OBJECTDIR}/_ext/534590209/fgGfxCamera.o: ../../../src/GFX/fgGfxCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxCamera.o ../../../src/GFX/fgGfxCamera.cpp

${OBJECTDIR}/_ext/534590209/fgGfxCameraAnimation.o: ../../../src/GFX/fgGfxCameraAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxCameraAnimation.o ../../../src/GFX/fgGfxCameraAnimation.cpp

${OBJECTDIR}/_ext/534590209/fgGfxContext.o: ../../../src/GFX/fgGfxContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxContext.o ../../../src/GFX/fgGfxContext.cpp

${OBJECTDIR}/_ext/534590209/fgGfxDrawCall.o: ../../../src/GFX/fgGfxDrawCall.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxDrawCall.o ../../../src/GFX/fgGfxDrawCall.cpp

${OBJECTDIR}/_ext/534590209/fgGfxDrawingBatch.o: ../../../src/GFX/fgGfxDrawingBatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxDrawingBatch.o ../../../src/GFX/fgGfxDrawingBatch.cpp

${OBJECTDIR}/_ext/534590209/fgGfxFrustum.o: ../../../src/GFX/fgGfxFrustum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxFrustum.o ../../../src/GFX/fgGfxFrustum.cpp

${OBJECTDIR}/_ext/534590209/fgGfxLight.o: ../../../src/GFX/fgGfxLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxLight.o ../../../src/GFX/fgGfxLight.cpp

${OBJECTDIR}/_ext/534590209/fgGfxMain.o: ../../../src/GFX/fgGfxMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxMain.o ../../../src/GFX/fgGfxMain.cpp

${OBJECTDIR}/_ext/534590209/fgGfxMaterial.o: ../../../src/GFX/fgGfxMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxMaterial.o ../../../src/GFX/fgGfxMaterial.cpp

${OBJECTDIR}/_ext/534590209/fgGfxModelResource.o: ../../../src/GFX/fgGfxModelResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxModelResource.o ../../../src/GFX/fgGfxModelResource.cpp

${OBJECTDIR}/_ext/534590209/fgGfxModelTypes.o: ../../../src/GFX/fgGfxModelTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxModelTypes.o ../../../src/GFX/fgGfxModelTypes.cpp

${OBJECTDIR}/_ext/534590209/fgGfxPlatform.o: ../../../src/GFX/fgGfxPlatform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxPlatform.o ../../../src/GFX/fgGfxPlatform.cpp

${OBJECTDIR}/_ext/534590209/fgGfxPrimitives.o: ../../../src/GFX/fgGfxPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxPrimitives.o ../../../src/GFX/fgGfxPrimitives.cpp

${OBJECTDIR}/_ext/534590209/fgGfxSimpleDrawer.o: ../../../src/GFX/fgGfxSimpleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxSimpleDrawer.o ../../../src/GFX/fgGfxSimpleDrawer.cpp

${OBJECTDIR}/_ext/534590209/fgGfxVertexData.o: ../../../src/GFX/fgGfxVertexData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxVertexData.o ../../../src/GFX/fgGfxVertexData.cpp

${OBJECTDIR}/_ext/534590209/fgGfxWindow.o: ../../../src/GFX/fgGfxWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGfxWindow.o ../../../src/GFX/fgGfxWindow.cpp

${OBJECTDIR}/_ext/1216539907/fgFontBuiltIn.o: ../../../src/GUI/Font/fgFontBuiltIn.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontBuiltIn.o ../../../src/GUI/Font/fgFontBuiltIn.cpp

${OBJECTDIR}/_ext/1216539907/fgFontDrawer.o: ../../../src/GUI/Font/fgFontDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontDrawer.o ../../../src/GUI/Font/fgFontDrawer.cpp

${OBJECTDIR}/_ext/1216539907/fgFontResource.o: ../../../src/GUI/Font/fgFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontResource.o ../../../src/GUI/Font/fgFontResource.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbArial.o: ../../../src/GUI/Font/fgFontStbArial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbArial.o ../../../src/GUI/Font/fgFontStbArial.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbArialBold.o: ../../../src/GUI/Font/fgFontStbArialBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbArialBold.o ../../../src/GUI/Font/fgFontStbArialBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbConsolas.o: ../../../src/GUI/Font/fgFontStbConsolas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbConsolas.o ../../../src/GUI/Font/fgFontStbConsolas.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbConsolasBold.o: ../../../src/GUI/Font/fgFontStbConsolasBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbConsolasBold.o ../../../src/GUI/Font/fgFontStbConsolasBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbCourier.o: ../../../src/GUI/Font/fgFontStbCourier.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbCourier.o ../../../src/GUI/Font/fgFontStbCourier.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbCourierBold.o: ../../../src/GUI/Font/fgFontStbCourierBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbCourierBold.o ../../../src/GUI/Font/fgFontStbCourierBold.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbTimes.o: ../../../src/GUI/Font/fgFontStbTimes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbTimes.o ../../../src/GUI/Font/fgFontStbTimes.cpp

${OBJECTDIR}/_ext/1216539907/fgFontStbTimesBold.o: ../../../src/GUI/Font/fgFontStbTimesBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1216539907
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1216539907/fgFontStbTimesBold.o ../../../src/GUI/Font/fgFontStbTimesBold.cpp

${OBJECTDIR}/_ext/534589759/fgGuiButton.o: ../../../src/GUI/fgGuiButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiButton.o ../../../src/GUI/fgGuiButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiCallback.o: ../../../src/GUI/fgGuiCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiCallback.o ../../../src/GUI/fgGuiCallback.cpp

${OBJECTDIR}/_ext/534589759/fgGuiConsole.o: ../../../src/GUI/fgGuiConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiConsole.o ../../../src/GUI/fgGuiConsole.cpp

${OBJECTDIR}/_ext/534589759/fgGuiContainer.o: ../../../src/GUI/fgGuiContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiContainer.o ../../../src/GUI/fgGuiContainer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o: ../../../src/GUI/fgGuiDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o ../../../src/GUI/fgGuiDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiEditableText.o: ../../../src/GUI/fgGuiEditableText.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiEditableText.o ../../../src/GUI/fgGuiEditableText.cpp

${OBJECTDIR}/_ext/534589759/fgGuiFrame.o: ../../../src/GUI/fgGuiFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiFrame.o ../../../src/GUI/fgGuiFrame.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLabel.o: ../../../src/GUI/fgGuiLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLabel.o ../../../src/GUI/fgGuiLabel.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLoader.o: ../../../src/GUI/fgGuiLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLoader.o ../../../src/GUI/fgGuiLoader.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMain.o: ../../../src/GUI/fgGuiMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMain.o ../../../src/GUI/fgGuiMain.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMenu.o: ../../../src/GUI/fgGuiMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMenu.o ../../../src/GUI/fgGuiMenu.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o: ../../../src/GUI/fgGuiMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o ../../../src/GUI/fgGuiMessageBox.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPopup.o: ../../../src/GUI/fgGuiPopup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPopup.o ../../../src/GUI/fgGuiPopup.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o: ../../../src/GUI/fgGuiPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o ../../../src/GUI/fgGuiPrimitives.cpp

${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o: ../../../src/GUI/fgGuiProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o ../../../src/GUI/fgGuiProgressBar.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o: ../../../src/GUI/fgGuiScreenGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o ../../../src/GUI/fgGuiScreenGrid.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScrollArea.o: ../../../src/GUI/fgGuiScrollArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScrollArea.o ../../../src/GUI/fgGuiScrollArea.cpp

${OBJECTDIR}/_ext/534589759/fgGuiSlider.o: ../../../src/GUI/fgGuiSlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiSlider.o ../../../src/GUI/fgGuiSlider.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o: ../../../src/GUI/fgGuiStructureSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o ../../../src/GUI/fgGuiStructureSheet.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o: ../../../src/GUI/fgGuiStructureSheetParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o ../../../src/GUI/fgGuiStructureSheetParser.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyle.o: ../../../src/GUI/fgGuiStyle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyle.o ../../../src/GUI/fgGuiStyle.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o: ../../../src/GUI/fgGuiStyleContent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o ../../../src/GUI/fgGuiStyleContent.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o: ../../../src/GUI/fgGuiStyleManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleManager.o ../../../src/GUI/fgGuiStyleManager.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTable.o: ../../../src/GUI/fgGuiTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTable.o ../../../src/GUI/fgGuiTable.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o: ../../../src/GUI/fgGuiTextArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o ../../../src/GUI/fgGuiTextArea.cpp

${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o: ../../../src/GUI/fgGuiToggleButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o ../../../src/GUI/fgGuiToggleButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidget.o: ../../../src/GUI/fgGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidget.o ../../../src/GUI/fgGuiWidget.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o: ../../../src/GUI/fgGuiWidgetFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o ../../../src/GUI/fgGuiWidgetFactory.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidgetManager.o: ../../../src/GUI/fgGuiWidgetManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidgetManager.o ../../../src/GUI/fgGuiWidgetManager.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWindow.o: ../../../src/GUI/fgGuiWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWindow.o ../../../src/GUI/fgGuiWindow.cpp

${OBJECTDIR}/_ext/477241454/fgGameLogic.o: ../../../src/GameLogic/fgGameLogic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/477241454
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/477241454/fgGameLogic.o ../../../src/GameLogic/fgGameLogic.cpp

${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o: ../../../src/Hardware/fgDeviceQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o ../../../src/Hardware/fgDeviceQuery.cpp

${OBJECTDIR}/_ext/484399070/fgHardwareState.o: ../../../src/Hardware/fgHardwareState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgHardwareState.o ../../../src/Hardware/fgHardwareState.cpp

${OBJECTDIR}/_ext/484399070/fgQualityManager.o: ../../../src/Hardware/fgQualityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgQualityManager.o ../../../src/Hardware/fgQualityManager.cpp

${OBJECTDIR}/_ext/484399070/fgSensors.o: ../../../src/Hardware/fgSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgSensors.o ../../../src/Hardware/fgSensors.cpp

${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o: ../../../src/Math/fgKalmanFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607778370
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o ../../../src/Math/fgKalmanFilter.cpp

${OBJECTDIR}/_ext/1611265229/fgCollisionBody.o: ../../../src/Physics/fgCollisionBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgCollisionBody.o ../../../src/Physics/fgCollisionBody.cpp

${OBJECTDIR}/_ext/1611265229/fgCollisionCoarse.o: ../../../src/Physics/fgCollisionCoarse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgCollisionCoarse.o ../../../src/Physics/fgCollisionCoarse.cpp

${OBJECTDIR}/_ext/1611265229/fgCollisionFine.o: ../../../src/Physics/fgCollisionFine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgCollisionFine.o ../../../src/Physics/fgCollisionFine.cpp

${OBJECTDIR}/_ext/1611265229/fgContact.o: ../../../src/Physics/fgContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgContact.o ../../../src/Physics/fgContact.cpp

${OBJECTDIR}/_ext/1611265229/fgContactResolver.o: ../../../src/Physics/fgContactResolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgContactResolver.o ../../../src/Physics/fgContactResolver.cpp

${OBJECTDIR}/_ext/1611265229/fgCycloneCoreMath.o: ../../../src/Physics/fgCycloneCoreMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgCycloneCoreMath.o ../../../src/Physics/fgCycloneCoreMath.cpp

${OBJECTDIR}/_ext/1611265229/fgForceGenerator.o: ../../../src/Physics/fgForceGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgForceGenerator.o ../../../src/Physics/fgForceGenerator.cpp

${OBJECTDIR}/_ext/1611265229/fgJoint.o: ../../../src/Physics/fgJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgJoint.o ../../../src/Physics/fgJoint.cpp

${OBJECTDIR}/_ext/1611265229/fgParticle.o: ../../../src/Physics/fgParticle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticle.o ../../../src/Physics/fgParticle.cpp

${OBJECTDIR}/_ext/1611265229/fgParticleContact.o: ../../../src/Physics/fgParticleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticleContact.o ../../../src/Physics/fgParticleContact.cpp

${OBJECTDIR}/_ext/1611265229/fgParticleContactResolver.o: ../../../src/Physics/fgParticleContactResolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticleContactResolver.o ../../../src/Physics/fgParticleContactResolver.cpp

${OBJECTDIR}/_ext/1611265229/fgParticleForceGenerator.o: ../../../src/Physics/fgParticleForceGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticleForceGenerator.o ../../../src/Physics/fgParticleForceGenerator.cpp

${OBJECTDIR}/_ext/1611265229/fgParticleLink.o: ../../../src/Physics/fgParticleLink.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticleLink.o ../../../src/Physics/fgParticleLink.cpp

${OBJECTDIR}/_ext/1611265229/fgParticleWorld.o: ../../../src/Physics/fgParticleWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgParticleWorld.o ../../../src/Physics/fgParticleWorld.cpp

${OBJECTDIR}/_ext/1611265229/fgRandom.o: ../../../src/Physics/fgRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgRandom.o ../../../src/Physics/fgRandom.cpp

${OBJECTDIR}/_ext/1611265229/fgRigidBody.o: ../../../src/Physics/fgRigidBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgRigidBody.o ../../../src/Physics/fgRigidBody.cpp

${OBJECTDIR}/_ext/1611265229/fgWorld.o: ../../../src/Physics/fgWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1611265229
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1611265229/fgWorld.o ../../../src/Physics/fgWorld.cpp

${OBJECTDIR}/_ext/942373304/fgResource.o: ../../../src/Resource/fgResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResource.o ../../../src/Resource/fgResource.cpp

${OBJECTDIR}/_ext/942373304/fgResourceConfigParser.o: ../../../src/Resource/fgResourceConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceConfigParser.o ../../../src/Resource/fgResourceConfigParser.cpp

${OBJECTDIR}/_ext/942373304/fgResourceFactory.o: ../../../src/Resource/fgResourceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceFactory.o ../../../src/Resource/fgResourceFactory.cpp

${OBJECTDIR}/_ext/942373304/fgResourceGroup.o: ../../../src/Resource/fgResourceGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceGroup.o ../../../src/Resource/fgResourceGroup.cpp

${OBJECTDIR}/_ext/942373304/fgResourceManager.o: ../../../src/Resource/fgResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceManager.o ../../../src/Resource/fgResourceManager.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptCallback.o: ../../../src/Scripting/fgScriptCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptCallback.o ../../../src/Scripting/fgScriptCallback.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptMT.o: ../../../src/Scripting/fgScriptMT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptMT.o ../../../src/Scripting/fgScriptMT.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptResource.o: ../../../src/Scripting/fgScriptResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptResource.o ../../../src/Scripting/fgScriptResource.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptSubsystem.o: ../../../src/Scripting/fgScriptSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptSubsystem.o ../../../src/Scripting/fgScriptSubsystem.cpp

${OBJECTDIR}/_ext/166270660/fgThread.o: ../../../src/Thread/fgThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/166270660
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/166270660/fgThread.o ../../../src/Thread/fgThread.cpp

${OBJECTDIR}/_ext/166270660/fgThreadSem.o: ../../../src/Thread/fgThreadSem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/166270660
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/166270660/fgThreadSem.o ../../../src/Thread/fgThreadSem.cpp

${OBJECTDIR}/_ext/608034620/fgConfig.o: ../../../src/Util/fgConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfig.o ../../../src/Util/fgConfig.cpp

${OBJECTDIR}/_ext/608034620/fgConfigParser.o: ../../../src/Util/fgConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigParser.o ../../../src/Util/fgConfigParser.cpp

${OBJECTDIR}/_ext/608034620/fgConfigWriter.o: ../../../src/Util/fgConfigWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigWriter.o ../../../src/Util/fgConfigWriter.cpp

${OBJECTDIR}/_ext/608034620/fgDirent.o: ../../../src/Util/fgDirent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgDirent.o ../../../src/Util/fgDirent.cpp

${OBJECTDIR}/_ext/608034620/fgFastCmp.o: ../../../src/Util/fgFastCmp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgFastCmp.o ../../../src/Util/fgFastCmp.cpp

${OBJECTDIR}/_ext/608034620/fgFile.o: ../../../src/Util/fgFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgFile.o ../../../src/Util/fgFile.cpp

${OBJECTDIR}/_ext/608034620/fgHashFunc.o: ../../../src/Util/fgHashFunc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgHashFunc.o ../../../src/Util/fgHashFunc.cpp

${OBJECTDIR}/_ext/608034620/fgPath.o: ../../../src/Util/fgPath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgPath.o ../../../src/Util/fgPath.cpp

${OBJECTDIR}/_ext/608034620/fgProfiling.o: ../../../src/Util/fgProfiling.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgProfiling.o ../../../src/Util/fgProfiling.cpp

${OBJECTDIR}/_ext/608034620/fgRegularFile.o: ../../../src/Util/fgRegularFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgRegularFile.o ../../../src/Util/fgRegularFile.cpp

${OBJECTDIR}/_ext/608034620/fgSettings.o: ../../../src/Util/fgSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgSettings.o ../../../src/Util/fgSettings.cpp

${OBJECTDIR}/_ext/608034620/fgStrings.o: ../../../src/Util/fgStrings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgStrings.o ../../../src/Util/fgStrings.cpp

${OBJECTDIR}/_ext/608034620/fgTime.o: ../../../src/Util/fgTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgTime.o ../../../src/Util/fgTime.cpp

${OBJECTDIR}/_ext/608034620/fgZipFile.o: ../../../src/Util/fgZipFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgZipFile.o ../../../src/Util/fgZipFile.cpp

${OBJECTDIR}/_ext/534573667/fgXMLParser.o: ../../../src/XML/fgXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534573667
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534573667/fgXMLParser.o ../../../src/XML/fgXMLParser.cpp

${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o: ../../../src/fgBuildConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o ../../../src/fgBuildConfig.cpp

${OBJECTDIR}/_ext/1386528437/fgColors.o: ../../../src/fgColors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgColors.o ../../../src/fgColors.cpp

${OBJECTDIR}/_ext/1386528437/fgCommon.o: ../../../src/fgCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgCommon.o ../../../src/fgCommon.cpp

${OBJECTDIR}/_ext/1386528437/fgDebugConfig.o: ../../../src/fgDebugConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgDebugConfig.o ../../../src/fgDebugConfig.cpp

${OBJECTDIR}/_ext/1386528437/fgErrno.o: ../../../src/fgErrno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrno.o ../../../src/fgErrno.cpp

${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o: ../../../src/fgErrorCodes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o ../../../src/fgErrorCodes.cpp

${OBJECTDIR}/_ext/1386528437/fgGameMain.o: ../../../src/fgGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgGameMain.o ../../../src/fgGameMain.cpp

${OBJECTDIR}/_ext/1386528437/fgLog.o: ../../../src/fgLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgLog.o ../../../src/fgLog.cpp

${OBJECTDIR}/_ext/1386528437/fgMainModule.o: ../../../src/fgMainModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMainModule.o ../../../src/fgMainModule.cpp

${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o: ../../../src/fgMessageSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/cpp_btree `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o ../../../src/fgMessageSubsystem.cpp

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
