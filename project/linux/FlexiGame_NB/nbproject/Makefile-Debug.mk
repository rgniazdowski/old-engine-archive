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
CC=/usr/lib/distcc/bin/gcc-4.8.1
CCC=/usr/lib/distcc/bin/g++-4.8.1
CXX=/usr/lib/distcc/bin/g++-4.8.1
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/_ext/4c49004a/fgTinyObj.o \
	${OBJECTDIR}/_ext/dfee612a/tinystr.o \
	${OBJECTDIR}/_ext/dfee612a/tinyxml.o \
	${OBJECTDIR}/_ext/dfee612a/tinyxmlerror.o \
	${OBJECTDIR}/_ext/dfee612a/tinyxmlparser.o \
	${OBJECTDIR}/_ext/4fa144f5/fgAndroid.o \
	${OBJECTDIR}/_ext/626493dc/fgSFXManager.o \
	${OBJECTDIR}/_ext/626493dc/fgSFXMusicResource.o \
	${OBJECTDIR}/_ext/626493dc/fgSFXSoundResource.o \
	${OBJECTDIR}/_ext/629d6aa0/fgArgumentList.o \
	${OBJECTDIR}/_ext/629d6aa0/fgEventManager.o \
	${OBJECTDIR}/_ext/629d6aa0/fgInputHandler.o \
	${OBJECTDIR}/_ext/629d6aa0/fgJoypadController.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimation.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationChannel.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationInfo.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxArmature.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxBlending.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxBlendingInfo.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxBone.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxBoneAnimation.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxObjectAnimation.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxRagdollBoneAnimation.o \
	${OBJECTDIR}/_ext/bf7ada54/fgGfxSkinningInfo.o \
	${OBJECTDIR}/_ext/1181217d/fgParticleSystem.o \
	${OBJECTDIR}/_ext/1181217d/fgPsParticleEffect.o \
	${OBJECTDIR}/_ext/1181217d/fgPsParticleEffectCircular.o \
	${OBJECTDIR}/_ext/1181217d/fgPsParticleEmitter.o \
	${OBJECTDIR}/_ext/1181217d/fgPsSequentialEffect.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfx2DScene.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfx3DScene.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxAnimated.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBasetree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspCompiler.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspFile.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspNode.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspResource.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTypes.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxDrawable.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseOctree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseQuadtree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxNodeFactory.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxOctree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortal.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortalProcessor.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxPvsProcessor.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxQuadtree.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneEvent.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneManager.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNode.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeMesh.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeObject.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeTrigger.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneSkyBox.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxTreeNode.o \
	${OBJECTDIR}/_ext/3c22bf5c/fgGfxTriggerable.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShader.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderBase.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderConfig.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderDefs.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderManager.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderProgram.o \
	${OBJECTDIR}/_ext/c6bbb7fe/fgGfxUniformUpdater.o \
	${OBJECTDIR}/_ext/211f5e8/fgTextureLoader.o \
	${OBJECTDIR}/_ext/211f5e8/fgTextureManager.o \
	${OBJECTDIR}/_ext/211f5e8/fgTextureResource.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxAssimpHelper.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxAttributeData.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxCamera.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxCameraAnimation.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxContext.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxDrawCall.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxDrawingBatch.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxFrustum.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxLight.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxMVPMatrix.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxMain.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxMaterial.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxMesh.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxModelResource.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxPlaneGrid.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxPolygon.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxPrimitives.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxProjection.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxShape.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxSimpleDrawer.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxSkinnedMesh.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxVertexData.o \
	${OBJECTDIR}/_ext/e022ccff/fgGfxWindow.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontBuiltIn.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontDrawer.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontResource.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbArial.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbArialBold.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolas.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolasBold.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourier.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourierBold.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimes.o \
	${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimesBold.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiButton.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiCallback.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiConsole.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiContainer.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiDrawer.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiEditableText.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiFrame.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiLabel.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiLoader.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiMain.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiMenu.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiMessageBox.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiPopup.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiPrimitives.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiProgressBar.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiScreenGrid.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiScrollArea.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiSlider.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheet.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheetParser.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiStyle.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiStyleContent.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiStyleManager.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiTable.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiTextArea.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiToggleButton.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiWidget.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetFactory.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetManager.o \
	${OBJECTDIR}/_ext/e022cec1/fgGuiWindow.o \
	${OBJECTDIR}/_ext/24373b2c/fg2DGameWorld.o \
	${OBJECTDIR}/_ext/24373b2c/fg3DGameWorld.o \
	${OBJECTDIR}/_ext/24373b2c/fgGameEntity.o \
	${OBJECTDIR}/_ext/24373b2c/fgGameEntityActor.o \
	${OBJECTDIR}/_ext/24373b2c/fgGameEntityMesh.o \
	${OBJECTDIR}/_ext/24373b2c/fgGameMain.o \
	${OBJECTDIR}/_ext/24373b2c/fgGameWorld.o \
	${OBJECTDIR}/_ext/24373b2c/fgGrid.o \
	${OBJECTDIR}/_ext/24373b2c/fgIntelligent.o \
	${OBJECTDIR}/_ext/24373b2c/fgIntelligentWorld.o \
	${OBJECTDIR}/_ext/e320a822/fgDeviceQuery.o \
	${OBJECTDIR}/_ext/e320a822/fgHardwareState.o \
	${OBJECTDIR}/_ext/e320a822/fgQualityManager.o \
	${OBJECTDIR}/_ext/e320a822/fgSensors.o \
	${OBJECTDIR}/_ext/2439f642/fgKalmanFilter.o \
	${OBJECTDIR}/_ext/6009f4cd/fgAbstractCollisionBody.o \
	${OBJECTDIR}/_ext/6009f4cd/fgBulletHelper.o \
	${OBJECTDIR}/_ext/6009f4cd/fgCollisionBody.o \
	${OBJECTDIR}/_ext/6009f4cd/fgPhysical.o \
	${OBJECTDIR}/_ext/6009f4cd/fgPhysicalWorld.o \
	${OBJECTDIR}/_ext/6009f4cd/fgRagdollCollisionBody.o \
	${OBJECTDIR}/_ext/c7d48648/fgResource.o \
	${OBJECTDIR}/_ext/c7d48648/fgResourceConfigParser.o \
	${OBJECTDIR}/_ext/c7d48648/fgResourceFactory.o \
	${OBJECTDIR}/_ext/c7d48648/fgResourceGroup.o \
	${OBJECTDIR}/_ext/c7d48648/fgResourceManager.o \
	${OBJECTDIR}/_ext/b7d5943d/fgScriptCallback.o \
	${OBJECTDIR}/_ext/b7d5943d/fgScriptMT.o \
	${OBJECTDIR}/_ext/b7d5943d/fgScriptSubsystem.o \
	${OBJECTDIR}/_ext/9e916c4/fgThread.o \
	${OBJECTDIR}/_ext/9e916c4/fgThreadSem.o \
	${OBJECTDIR}/_ext/243ddf3c/fgConfig.o \
	${OBJECTDIR}/_ext/243ddf3c/fgConfigParser.o \
	${OBJECTDIR}/_ext/243ddf3c/fgConfigWriter.o \
	${OBJECTDIR}/_ext/243ddf3c/fgDirent.o \
	${OBJECTDIR}/_ext/243ddf3c/fgFastCmp.o \
	${OBJECTDIR}/_ext/243ddf3c/fgFile.o \
	${OBJECTDIR}/_ext/243ddf3c/fgHashFunc.o \
	${OBJECTDIR}/_ext/243ddf3c/fgPath.o \
	${OBJECTDIR}/_ext/243ddf3c/fgProfiling.o \
	${OBJECTDIR}/_ext/243ddf3c/fgRegularFile.o \
	${OBJECTDIR}/_ext/243ddf3c/fgSettings.o \
	${OBJECTDIR}/_ext/243ddf3c/fgStrings.o \
	${OBJECTDIR}/_ext/243ddf3c/fgTime.o \
	${OBJECTDIR}/_ext/243ddf3c/fgZipFile.o \
	${OBJECTDIR}/_ext/e0230d9d/fgXMLParser.o \
	${OBJECTDIR}/_ext/52a4beb5/fgApplication.o \
	${OBJECTDIR}/_ext/52a4beb5/fgBuildConfig.o \
	${OBJECTDIR}/_ext/52a4beb5/fgColors.o \
	${OBJECTDIR}/_ext/52a4beb5/fgCommon.o \
	${OBJECTDIR}/_ext/52a4beb5/fgDebugConfig.o \
	${OBJECTDIR}/_ext/52a4beb5/fgEngineMain.o \
	${OBJECTDIR}/_ext/52a4beb5/fgErrno.o \
	${OBJECTDIR}/_ext/52a4beb5/fgErrorCodes.o \
	${OBJECTDIR}/_ext/52a4beb5/fgLog.o \
	${OBJECTDIR}/_ext/52a4beb5/fgMessageSubsystem.o \
	${OBJECTDIR}/_ext/52a4beb5/fgPluginResource.o \
	${OBJECTDIR}/_ext/52a4beb5/fgSDLApplication.o \
	${OBJECTDIR}/_ext/52a4beb5/main.o


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
LDLIBSOPTIONS=`pkg-config --libs gl` `pkg-config --libs sdl2` `pkg-config --libs SDL2_mixer` `pkg-config --libs libpng` -ljpeg -lm  `pkg-config --libs zlib`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4c49004a/fgTinyObj.o: ../../../modules/tinyobj/upstream/fgTinyObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/4c49004a
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4c49004a/fgTinyObj.o ../../../modules/tinyobj/upstream/fgTinyObj.cpp

${OBJECTDIR}/_ext/dfee612a/tinystr.o: ../../../modules/tinyxml/upstream/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/dfee612a
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/dfee612a/tinystr.o ../../../modules/tinyxml/upstream/tinystr.cpp

${OBJECTDIR}/_ext/dfee612a/tinyxml.o: ../../../modules/tinyxml/upstream/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/dfee612a
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/dfee612a/tinyxml.o ../../../modules/tinyxml/upstream/tinyxml.cpp

${OBJECTDIR}/_ext/dfee612a/tinyxmlerror.o: ../../../modules/tinyxml/upstream/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/dfee612a
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/dfee612a/tinyxmlerror.o ../../../modules/tinyxml/upstream/tinyxmlerror.cpp

${OBJECTDIR}/_ext/dfee612a/tinyxmlparser.o: ../../../modules/tinyxml/upstream/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/dfee612a
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/dfee612a/tinyxmlparser.o ../../../modules/tinyxml/upstream/tinyxmlparser.cpp

${OBJECTDIR}/_ext/4fa144f5/fgAndroid.o: ../../../src/Android/fgAndroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/4fa144f5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4fa144f5/fgAndroid.o ../../../src/Android/fgAndroid.cpp

${OBJECTDIR}/_ext/626493dc/fgSFXManager.o: ../../../src/Audio/fgSFXManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/626493dc
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/626493dc/fgSFXManager.o ../../../src/Audio/fgSFXManager.cpp

${OBJECTDIR}/_ext/626493dc/fgSFXMusicResource.o: ../../../src/Audio/fgSFXMusicResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/626493dc
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/626493dc/fgSFXMusicResource.o ../../../src/Audio/fgSFXMusicResource.cpp

${OBJECTDIR}/_ext/626493dc/fgSFXSoundResource.o: ../../../src/Audio/fgSFXSoundResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/626493dc
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/626493dc/fgSFXSoundResource.o ../../../src/Audio/fgSFXSoundResource.cpp

${OBJECTDIR}/_ext/629d6aa0/fgArgumentList.o: ../../../src/Event/fgArgumentList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/629d6aa0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/629d6aa0/fgArgumentList.o ../../../src/Event/fgArgumentList.cpp

${OBJECTDIR}/_ext/629d6aa0/fgEventManager.o: ../../../src/Event/fgEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/629d6aa0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/629d6aa0/fgEventManager.o ../../../src/Event/fgEventManager.cpp

${OBJECTDIR}/_ext/629d6aa0/fgInputHandler.o: ../../../src/Event/fgInputHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/629d6aa0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/629d6aa0/fgInputHandler.o ../../../src/Event/fgInputHandler.cpp

${OBJECTDIR}/_ext/629d6aa0/fgJoypadController.o: ../../../src/Event/fgJoypadController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/629d6aa0
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/629d6aa0/fgJoypadController.o ../../../src/Event/fgJoypadController.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimation.o: ../../../src/GFX/Animation/fgGfxAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimation.o ../../../src/GFX/Animation/fgGfxAnimation.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationChannel.o: ../../../src/GFX/Animation/fgGfxAnimationChannel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationChannel.o ../../../src/GFX/Animation/fgGfxAnimationChannel.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationInfo.o: ../../../src/GFX/Animation/fgGfxAnimationInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxAnimationInfo.o ../../../src/GFX/Animation/fgGfxAnimationInfo.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxArmature.o: ../../../src/GFX/Animation/fgGfxArmature.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxArmature.o ../../../src/GFX/Animation/fgGfxArmature.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxBlending.o: ../../../src/GFX/Animation/fgGfxBlending.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxBlending.o ../../../src/GFX/Animation/fgGfxBlending.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxBlendingInfo.o: ../../../src/GFX/Animation/fgGfxBlendingInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxBlendingInfo.o ../../../src/GFX/Animation/fgGfxBlendingInfo.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxBone.o: ../../../src/GFX/Animation/fgGfxBone.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxBone.o ../../../src/GFX/Animation/fgGfxBone.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxBoneAnimation.o: ../../../src/GFX/Animation/fgGfxBoneAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxBoneAnimation.o ../../../src/GFX/Animation/fgGfxBoneAnimation.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxObjectAnimation.o: ../../../src/GFX/Animation/fgGfxObjectAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxObjectAnimation.o ../../../src/GFX/Animation/fgGfxObjectAnimation.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxRagdollBoneAnimation.o: ../../../src/GFX/Animation/fgGfxRagdollBoneAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxRagdollBoneAnimation.o ../../../src/GFX/Animation/fgGfxRagdollBoneAnimation.cpp

${OBJECTDIR}/_ext/bf7ada54/fgGfxSkinningInfo.o: ../../../src/GFX/Animation/fgGfxSkinningInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/bf7ada54
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf7ada54/fgGfxSkinningInfo.o ../../../src/GFX/Animation/fgGfxSkinningInfo.cpp

${OBJECTDIR}/_ext/1181217d/fgParticleSystem.o: ../../../src/GFX/Particles/fgParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1181217d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1181217d/fgParticleSystem.o ../../../src/GFX/Particles/fgParticleSystem.cpp

${OBJECTDIR}/_ext/1181217d/fgPsParticleEffect.o: ../../../src/GFX/Particles/fgPsParticleEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1181217d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1181217d/fgPsParticleEffect.o ../../../src/GFX/Particles/fgPsParticleEffect.cpp

${OBJECTDIR}/_ext/1181217d/fgPsParticleEffectCircular.o: ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1181217d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1181217d/fgPsParticleEffectCircular.o ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp

${OBJECTDIR}/_ext/1181217d/fgPsParticleEmitter.o: ../../../src/GFX/Particles/fgPsParticleEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1181217d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1181217d/fgPsParticleEmitter.o ../../../src/GFX/Particles/fgPsParticleEmitter.cpp

${OBJECTDIR}/_ext/1181217d/fgPsSequentialEffect.o: ../../../src/GFX/Particles/fgPsSequentialEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1181217d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1181217d/fgPsSequentialEffect.o ../../../src/GFX/Particles/fgPsSequentialEffect.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfx2DScene.o: ../../../src/GFX/Scene/fgGfx2DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfx2DScene.o ../../../src/GFX/Scene/fgGfx2DScene.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfx3DScene.o: ../../../src/GFX/Scene/fgGfx3DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfx3DScene.o ../../../src/GFX/Scene/fgGfx3DScene.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxAnimated.o: ../../../src/GFX/Scene/fgGfxAnimated.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxAnimated.o ../../../src/GFX/Scene/fgGfxAnimated.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBasetree.o: ../../../src/GFX/Scene/fgGfxBasetree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBasetree.o ../../../src/GFX/Scene/fgGfxBasetree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspCompiler.o: ../../../src/GFX/Scene/fgGfxBspCompiler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspCompiler.o ../../../src/GFX/Scene/fgGfxBspCompiler.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspFile.o: ../../../src/GFX/Scene/fgGfxBspFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspFile.o ../../../src/GFX/Scene/fgGfxBspFile.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspNode.o: ../../../src/GFX/Scene/fgGfxBspNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspNode.o ../../../src/GFX/Scene/fgGfxBspNode.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspResource.o: ../../../src/GFX/Scene/fgGfxBspResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspResource.o ../../../src/GFX/Scene/fgGfxBspResource.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTree.o: ../../../src/GFX/Scene/fgGfxBspTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTree.o ../../../src/GFX/Scene/fgGfxBspTree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTypes.o: ../../../src/GFX/Scene/fgGfxBspTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxBspTypes.o ../../../src/GFX/Scene/fgGfxBspTypes.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxDrawable.o: ../../../src/GFX/Scene/fgGfxDrawable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxDrawable.o ../../../src/GFX/Scene/fgGfxDrawable.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseOctree.o: ../../../src/GFX/Scene/fgGfxLooseOctree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseOctree.o ../../../src/GFX/Scene/fgGfxLooseOctree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseQuadtree.o: ../../../src/GFX/Scene/fgGfxLooseQuadtree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxLooseQuadtree.o ../../../src/GFX/Scene/fgGfxLooseQuadtree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxNodeFactory.o: ../../../src/GFX/Scene/fgGfxNodeFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxNodeFactory.o ../../../src/GFX/Scene/fgGfxNodeFactory.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxOctree.o: ../../../src/GFX/Scene/fgGfxOctree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxOctree.o ../../../src/GFX/Scene/fgGfxOctree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortal.o: ../../../src/GFX/Scene/fgGfxPortal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortal.o ../../../src/GFX/Scene/fgGfxPortal.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortalProcessor.o: ../../../src/GFX/Scene/fgGfxPortalProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxPortalProcessor.o ../../../src/GFX/Scene/fgGfxPortalProcessor.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxPvsProcessor.o: ../../../src/GFX/Scene/fgGfxPvsProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxPvsProcessor.o ../../../src/GFX/Scene/fgGfxPvsProcessor.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxQuadtree.o: ../../../src/GFX/Scene/fgGfxQuadtree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxQuadtree.o ../../../src/GFX/Scene/fgGfxQuadtree.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneEvent.o: ../../../src/GFX/Scene/fgGfxSceneEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneEvent.o ../../../src/GFX/Scene/fgGfxSceneEvent.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneManager.o: ../../../src/GFX/Scene/fgGfxSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneManager.o ../../../src/GFX/Scene/fgGfxSceneManager.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNode.o: ../../../src/GFX/Scene/fgGfxSceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNode.o ../../../src/GFX/Scene/fgGfxSceneNode.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeMesh.o: ../../../src/GFX/Scene/fgGfxSceneNodeMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeMesh.o ../../../src/GFX/Scene/fgGfxSceneNodeMesh.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeObject.o: ../../../src/GFX/Scene/fgGfxSceneNodeObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeObject.o ../../../src/GFX/Scene/fgGfxSceneNodeObject.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeTrigger.o: ../../../src/GFX/Scene/fgGfxSceneNodeTrigger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneNodeTrigger.o ../../../src/GFX/Scene/fgGfxSceneNodeTrigger.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneSkyBox.o: ../../../src/GFX/Scene/fgGfxSceneSkyBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxSceneSkyBox.o ../../../src/GFX/Scene/fgGfxSceneSkyBox.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxTreeNode.o: ../../../src/GFX/Scene/fgGfxTreeNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxTreeNode.o ../../../src/GFX/Scene/fgGfxTreeNode.cpp

${OBJECTDIR}/_ext/3c22bf5c/fgGfxTriggerable.o: ../../../src/GFX/Scene/fgGfxTriggerable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/3c22bf5c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3c22bf5c/fgGfxTriggerable.o ../../../src/GFX/Scene/fgGfxTriggerable.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShader.o: ../../../src/GFX/Shaders/fgGfxShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShader.o ../../../src/GFX/Shaders/fgGfxShader.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderBase.o: ../../../src/GFX/Shaders/fgGfxShaderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderBase.o ../../../src/GFX/Shaders/fgGfxShaderBase.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderConfig.o: ../../../src/GFX/Shaders/fgGfxShaderConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderConfig.o ../../../src/GFX/Shaders/fgGfxShaderConfig.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderDefs.o: ../../../src/GFX/Shaders/fgGfxShaderDefs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderDefs.o ../../../src/GFX/Shaders/fgGfxShaderDefs.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderManager.o: ../../../src/GFX/Shaders/fgGfxShaderManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderManager.o ../../../src/GFX/Shaders/fgGfxShaderManager.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderProgram.o: ../../../src/GFX/Shaders/fgGfxShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxShaderProgram.o ../../../src/GFX/Shaders/fgGfxShaderProgram.cpp

${OBJECTDIR}/_ext/c6bbb7fe/fgGfxUniformUpdater.o: ../../../src/GFX/Shaders/fgGfxUniformUpdater.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c6bbb7fe
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c6bbb7fe/fgGfxUniformUpdater.o ../../../src/GFX/Shaders/fgGfxUniformUpdater.cpp

${OBJECTDIR}/_ext/211f5e8/fgTextureLoader.o: ../../../src/GFX/Textures/fgTextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/211f5e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/211f5e8/fgTextureLoader.o ../../../src/GFX/Textures/fgTextureLoader.cpp

${OBJECTDIR}/_ext/211f5e8/fgTextureManager.o: ../../../src/GFX/Textures/fgTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/211f5e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/211f5e8/fgTextureManager.o ../../../src/GFX/Textures/fgTextureManager.cpp

${OBJECTDIR}/_ext/211f5e8/fgTextureResource.o: ../../../src/GFX/Textures/fgTextureResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/211f5e8
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/211f5e8/fgTextureResource.o ../../../src/GFX/Textures/fgTextureResource.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxAssimpHelper.o: ../../../src/GFX/fgGfxAssimpHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxAssimpHelper.o ../../../src/GFX/fgGfxAssimpHelper.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxAttributeData.o: ../../../src/GFX/fgGfxAttributeData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxAttributeData.o ../../../src/GFX/fgGfxAttributeData.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxCamera.o: ../../../src/GFX/fgGfxCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxCamera.o ../../../src/GFX/fgGfxCamera.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxCameraAnimation.o: ../../../src/GFX/fgGfxCameraAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxCameraAnimation.o ../../../src/GFX/fgGfxCameraAnimation.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxContext.o: ../../../src/GFX/fgGfxContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxContext.o ../../../src/GFX/fgGfxContext.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxDrawCall.o: ../../../src/GFX/fgGfxDrawCall.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxDrawCall.o ../../../src/GFX/fgGfxDrawCall.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxDrawingBatch.o: ../../../src/GFX/fgGfxDrawingBatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxDrawingBatch.o ../../../src/GFX/fgGfxDrawingBatch.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxFrustum.o: ../../../src/GFX/fgGfxFrustum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxFrustum.o ../../../src/GFX/fgGfxFrustum.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxLight.o: ../../../src/GFX/fgGfxLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxLight.o ../../../src/GFX/fgGfxLight.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxMVPMatrix.o: ../../../src/GFX/fgGfxMVPMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxMVPMatrix.o ../../../src/GFX/fgGfxMVPMatrix.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxMain.o: ../../../src/GFX/fgGfxMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxMain.o ../../../src/GFX/fgGfxMain.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxMaterial.o: ../../../src/GFX/fgGfxMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxMaterial.o ../../../src/GFX/fgGfxMaterial.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxMesh.o: ../../../src/GFX/fgGfxMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxMesh.o ../../../src/GFX/fgGfxMesh.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxModelResource.o: ../../../src/GFX/fgGfxModelResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxModelResource.o ../../../src/GFX/fgGfxModelResource.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxPlaneGrid.o: ../../../src/GFX/fgGfxPlaneGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxPlaneGrid.o ../../../src/GFX/fgGfxPlaneGrid.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxPolygon.o: ../../../src/GFX/fgGfxPolygon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxPolygon.o ../../../src/GFX/fgGfxPolygon.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxPrimitives.o: ../../../src/GFX/fgGfxPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxPrimitives.o ../../../src/GFX/fgGfxPrimitives.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxProjection.o: ../../../src/GFX/fgGfxProjection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxProjection.o ../../../src/GFX/fgGfxProjection.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxShape.o: ../../../src/GFX/fgGfxShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxShape.o ../../../src/GFX/fgGfxShape.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxSimpleDrawer.o: ../../../src/GFX/fgGfxSimpleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxSimpleDrawer.o ../../../src/GFX/fgGfxSimpleDrawer.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxSkinnedMesh.o: ../../../src/GFX/fgGfxSkinnedMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxSkinnedMesh.o ../../../src/GFX/fgGfxSkinnedMesh.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxVertexData.o: ../../../src/GFX/fgGfxVertexData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxVertexData.o ../../../src/GFX/fgGfxVertexData.cpp

${OBJECTDIR}/_ext/e022ccff/fgGfxWindow.o: ../../../src/GFX/fgGfxWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022ccff
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022ccff/fgGfxWindow.o ../../../src/GFX/fgGfxWindow.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontBuiltIn.o: ../../../src/GUI/Font/fgFontBuiltIn.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontBuiltIn.o ../../../src/GUI/Font/fgFontBuiltIn.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontDrawer.o: ../../../src/GUI/Font/fgFontDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontDrawer.o ../../../src/GUI/Font/fgFontDrawer.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontResource.o: ../../../src/GUI/Font/fgFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontResource.o ../../../src/GUI/Font/fgFontResource.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbArial.o: ../../../src/GUI/Font/fgFontStbArial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbArial.o ../../../src/GUI/Font/fgFontStbArial.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbArialBold.o: ../../../src/GUI/Font/fgFontStbArialBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbArialBold.o ../../../src/GUI/Font/fgFontStbArialBold.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolas.o: ../../../src/GUI/Font/fgFontStbConsolas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolas.o ../../../src/GUI/Font/fgFontStbConsolas.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolasBold.o: ../../../src/GUI/Font/fgFontStbConsolasBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbConsolasBold.o ../../../src/GUI/Font/fgFontStbConsolasBold.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourier.o: ../../../src/GUI/Font/fgFontStbCourier.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourier.o ../../../src/GUI/Font/fgFontStbCourier.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourierBold.o: ../../../src/GUI/Font/fgFontStbCourierBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbCourierBold.o ../../../src/GUI/Font/fgFontStbCourierBold.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimes.o: ../../../src/GUI/Font/fgFontStbTimes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimes.o ../../../src/GUI/Font/fgFontStbTimes.cpp

${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimesBold.o: ../../../src/GUI/Font/fgFontStbTimesBold.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b77d12fd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b77d12fd/fgFontStbTimesBold.o ../../../src/GUI/Font/fgFontStbTimesBold.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiButton.o: ../../../src/GUI/fgGuiButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiButton.o ../../../src/GUI/fgGuiButton.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiCallback.o: ../../../src/GUI/fgGuiCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiCallback.o ../../../src/GUI/fgGuiCallback.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiConsole.o: ../../../src/GUI/fgGuiConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiConsole.o ../../../src/GUI/fgGuiConsole.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiContainer.o: ../../../src/GUI/fgGuiContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiContainer.o ../../../src/GUI/fgGuiContainer.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiDrawer.o: ../../../src/GUI/fgGuiDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiDrawer.o ../../../src/GUI/fgGuiDrawer.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiEditableText.o: ../../../src/GUI/fgGuiEditableText.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiEditableText.o ../../../src/GUI/fgGuiEditableText.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiFrame.o: ../../../src/GUI/fgGuiFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiFrame.o ../../../src/GUI/fgGuiFrame.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiLabel.o: ../../../src/GUI/fgGuiLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiLabel.o ../../../src/GUI/fgGuiLabel.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiLoader.o: ../../../src/GUI/fgGuiLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiLoader.o ../../../src/GUI/fgGuiLoader.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiMain.o: ../../../src/GUI/fgGuiMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiMain.o ../../../src/GUI/fgGuiMain.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiMenu.o: ../../../src/GUI/fgGuiMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiMenu.o ../../../src/GUI/fgGuiMenu.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiMessageBox.o: ../../../src/GUI/fgGuiMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiMessageBox.o ../../../src/GUI/fgGuiMessageBox.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiPopup.o: ../../../src/GUI/fgGuiPopup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiPopup.o ../../../src/GUI/fgGuiPopup.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiPrimitives.o: ../../../src/GUI/fgGuiPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiPrimitives.o ../../../src/GUI/fgGuiPrimitives.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiProgressBar.o: ../../../src/GUI/fgGuiProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiProgressBar.o ../../../src/GUI/fgGuiProgressBar.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiScreenGrid.o: ../../../src/GUI/fgGuiScreenGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiScreenGrid.o ../../../src/GUI/fgGuiScreenGrid.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiScrollArea.o: ../../../src/GUI/fgGuiScrollArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiScrollArea.o ../../../src/GUI/fgGuiScrollArea.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiSlider.o: ../../../src/GUI/fgGuiSlider.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiSlider.o ../../../src/GUI/fgGuiSlider.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheet.o: ../../../src/GUI/fgGuiStructureSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheet.o ../../../src/GUI/fgGuiStructureSheet.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheetParser.o: ../../../src/GUI/fgGuiStructureSheetParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiStructureSheetParser.o ../../../src/GUI/fgGuiStructureSheetParser.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiStyle.o: ../../../src/GUI/fgGuiStyle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiStyle.o ../../../src/GUI/fgGuiStyle.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiStyleContent.o: ../../../src/GUI/fgGuiStyleContent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiStyleContent.o ../../../src/GUI/fgGuiStyleContent.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiStyleManager.o: ../../../src/GUI/fgGuiStyleManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiStyleManager.o ../../../src/GUI/fgGuiStyleManager.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiTable.o: ../../../src/GUI/fgGuiTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiTable.o ../../../src/GUI/fgGuiTable.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiTextArea.o: ../../../src/GUI/fgGuiTextArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiTextArea.o ../../../src/GUI/fgGuiTextArea.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiToggleButton.o: ../../../src/GUI/fgGuiToggleButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiToggleButton.o ../../../src/GUI/fgGuiToggleButton.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiWidget.o: ../../../src/GUI/fgGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiWidget.o ../../../src/GUI/fgGuiWidget.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetFactory.o: ../../../src/GUI/fgGuiWidgetFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetFactory.o ../../../src/GUI/fgGuiWidgetFactory.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetManager.o: ../../../src/GUI/fgGuiWidgetManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiWidgetManager.o ../../../src/GUI/fgGuiWidgetManager.cpp

${OBJECTDIR}/_ext/e022cec1/fgGuiWindow.o: ../../../src/GUI/fgGuiWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e022cec1
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e022cec1/fgGuiWindow.o ../../../src/GUI/fgGuiWindow.cpp

${OBJECTDIR}/_ext/24373b2c/fg2DGameWorld.o: ../../../src/Game/fg2DGameWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fg2DGameWorld.o ../../../src/Game/fg2DGameWorld.cpp

${OBJECTDIR}/_ext/24373b2c/fg3DGameWorld.o: ../../../src/Game/fg3DGameWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fg3DGameWorld.o ../../../src/Game/fg3DGameWorld.cpp

${OBJECTDIR}/_ext/24373b2c/fgGameEntity.o: ../../../src/Game/fgGameEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGameEntity.o ../../../src/Game/fgGameEntity.cpp

${OBJECTDIR}/_ext/24373b2c/fgGameEntityActor.o: ../../../src/Game/fgGameEntityActor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGameEntityActor.o ../../../src/Game/fgGameEntityActor.cpp

${OBJECTDIR}/_ext/24373b2c/fgGameEntityMesh.o: ../../../src/Game/fgGameEntityMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGameEntityMesh.o ../../../src/Game/fgGameEntityMesh.cpp

${OBJECTDIR}/_ext/24373b2c/fgGameMain.o: ../../../src/Game/fgGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGameMain.o ../../../src/Game/fgGameMain.cpp

${OBJECTDIR}/_ext/24373b2c/fgGameWorld.o: ../../../src/Game/fgGameWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGameWorld.o ../../../src/Game/fgGameWorld.cpp

${OBJECTDIR}/_ext/24373b2c/fgGrid.o: ../../../src/Game/fgGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgGrid.o ../../../src/Game/fgGrid.cpp

${OBJECTDIR}/_ext/24373b2c/fgIntelligent.o: ../../../src/Game/fgIntelligent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgIntelligent.o ../../../src/Game/fgIntelligent.cpp

${OBJECTDIR}/_ext/24373b2c/fgIntelligentWorld.o: ../../../src/Game/fgIntelligentWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/24373b2c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/24373b2c/fgIntelligentWorld.o ../../../src/Game/fgIntelligentWorld.cpp

${OBJECTDIR}/_ext/e320a822/fgDeviceQuery.o: ../../../src/Hardware/fgDeviceQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e320a822
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e320a822/fgDeviceQuery.o ../../../src/Hardware/fgDeviceQuery.cpp

${OBJECTDIR}/_ext/e320a822/fgHardwareState.o: ../../../src/Hardware/fgHardwareState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e320a822
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e320a822/fgHardwareState.o ../../../src/Hardware/fgHardwareState.cpp

${OBJECTDIR}/_ext/e320a822/fgQualityManager.o: ../../../src/Hardware/fgQualityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e320a822
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e320a822/fgQualityManager.o ../../../src/Hardware/fgQualityManager.cpp

${OBJECTDIR}/_ext/e320a822/fgSensors.o: ../../../src/Hardware/fgSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e320a822
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e320a822/fgSensors.o ../../../src/Hardware/fgSensors.cpp

${OBJECTDIR}/_ext/2439f642/fgKalmanFilter.o: ../../../src/Math/fgKalmanFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2439f642
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2439f642/fgKalmanFilter.o ../../../src/Math/fgKalmanFilter.cpp

${OBJECTDIR}/_ext/6009f4cd/fgAbstractCollisionBody.o: ../../../src/Physics/fgAbstractCollisionBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgAbstractCollisionBody.o ../../../src/Physics/fgAbstractCollisionBody.cpp

${OBJECTDIR}/_ext/6009f4cd/fgBulletHelper.o: ../../../src/Physics/fgBulletHelper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgBulletHelper.o ../../../src/Physics/fgBulletHelper.cpp

${OBJECTDIR}/_ext/6009f4cd/fgCollisionBody.o: ../../../src/Physics/fgCollisionBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgCollisionBody.o ../../../src/Physics/fgCollisionBody.cpp

${OBJECTDIR}/_ext/6009f4cd/fgPhysical.o: ../../../src/Physics/fgPhysical.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgPhysical.o ../../../src/Physics/fgPhysical.cpp

${OBJECTDIR}/_ext/6009f4cd/fgPhysicalWorld.o: ../../../src/Physics/fgPhysicalWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgPhysicalWorld.o ../../../src/Physics/fgPhysicalWorld.cpp

${OBJECTDIR}/_ext/6009f4cd/fgRagdollCollisionBody.o: ../../../src/Physics/fgRagdollCollisionBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/6009f4cd
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6009f4cd/fgRagdollCollisionBody.o ../../../src/Physics/fgRagdollCollisionBody.cpp

${OBJECTDIR}/_ext/c7d48648/fgResource.o: ../../../src/Resource/fgResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c7d48648
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7d48648/fgResource.o ../../../src/Resource/fgResource.cpp

${OBJECTDIR}/_ext/c7d48648/fgResourceConfigParser.o: ../../../src/Resource/fgResourceConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c7d48648
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7d48648/fgResourceConfigParser.o ../../../src/Resource/fgResourceConfigParser.cpp

${OBJECTDIR}/_ext/c7d48648/fgResourceFactory.o: ../../../src/Resource/fgResourceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c7d48648
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7d48648/fgResourceFactory.o ../../../src/Resource/fgResourceFactory.cpp

${OBJECTDIR}/_ext/c7d48648/fgResourceGroup.o: ../../../src/Resource/fgResourceGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c7d48648
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7d48648/fgResourceGroup.o ../../../src/Resource/fgResourceGroup.cpp

${OBJECTDIR}/_ext/c7d48648/fgResourceManager.o: ../../../src/Resource/fgResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c7d48648
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c7d48648/fgResourceManager.o ../../../src/Resource/fgResourceManager.cpp

${OBJECTDIR}/_ext/b7d5943d/fgScriptCallback.o: ../../../src/Scripting/fgScriptCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7d5943d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7d5943d/fgScriptCallback.o ../../../src/Scripting/fgScriptCallback.cpp

${OBJECTDIR}/_ext/b7d5943d/fgScriptMT.o: ../../../src/Scripting/fgScriptMT.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7d5943d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7d5943d/fgScriptMT.o ../../../src/Scripting/fgScriptMT.cpp

${OBJECTDIR}/_ext/b7d5943d/fgScriptSubsystem.o: ../../../src/Scripting/fgScriptSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7d5943d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7d5943d/fgScriptSubsystem.o ../../../src/Scripting/fgScriptSubsystem.cpp

${OBJECTDIR}/_ext/9e916c4/fgThread.o: ../../../src/Thread/fgThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/9e916c4
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9e916c4/fgThread.o ../../../src/Thread/fgThread.cpp

${OBJECTDIR}/_ext/9e916c4/fgThreadSem.o: ../../../src/Thread/fgThreadSem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/9e916c4
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9e916c4/fgThreadSem.o ../../../src/Thread/fgThreadSem.cpp

${OBJECTDIR}/_ext/243ddf3c/fgConfig.o: ../../../src/Util/fgConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgConfig.o ../../../src/Util/fgConfig.cpp

${OBJECTDIR}/_ext/243ddf3c/fgConfigParser.o: ../../../src/Util/fgConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgConfigParser.o ../../../src/Util/fgConfigParser.cpp

${OBJECTDIR}/_ext/243ddf3c/fgConfigWriter.o: ../../../src/Util/fgConfigWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgConfigWriter.o ../../../src/Util/fgConfigWriter.cpp

${OBJECTDIR}/_ext/243ddf3c/fgDirent.o: ../../../src/Util/fgDirent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgDirent.o ../../../src/Util/fgDirent.cpp

${OBJECTDIR}/_ext/243ddf3c/fgFastCmp.o: ../../../src/Util/fgFastCmp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgFastCmp.o ../../../src/Util/fgFastCmp.cpp

${OBJECTDIR}/_ext/243ddf3c/fgFile.o: ../../../src/Util/fgFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgFile.o ../../../src/Util/fgFile.cpp

${OBJECTDIR}/_ext/243ddf3c/fgHashFunc.o: ../../../src/Util/fgHashFunc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgHashFunc.o ../../../src/Util/fgHashFunc.cpp

${OBJECTDIR}/_ext/243ddf3c/fgPath.o: ../../../src/Util/fgPath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgPath.o ../../../src/Util/fgPath.cpp

${OBJECTDIR}/_ext/243ddf3c/fgProfiling.o: ../../../src/Util/fgProfiling.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgProfiling.o ../../../src/Util/fgProfiling.cpp

${OBJECTDIR}/_ext/243ddf3c/fgRegularFile.o: ../../../src/Util/fgRegularFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgRegularFile.o ../../../src/Util/fgRegularFile.cpp

${OBJECTDIR}/_ext/243ddf3c/fgSettings.o: ../../../src/Util/fgSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgSettings.o ../../../src/Util/fgSettings.cpp

${OBJECTDIR}/_ext/243ddf3c/fgStrings.o: ../../../src/Util/fgStrings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgStrings.o ../../../src/Util/fgStrings.cpp

${OBJECTDIR}/_ext/243ddf3c/fgTime.o: ../../../src/Util/fgTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgTime.o ../../../src/Util/fgTime.cpp

${OBJECTDIR}/_ext/243ddf3c/fgZipFile.o: ../../../src/Util/fgZipFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/243ddf3c
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/243ddf3c/fgZipFile.o ../../../src/Util/fgZipFile.cpp

${OBJECTDIR}/_ext/e0230d9d/fgXMLParser.o: ../../../src/XML/fgXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/e0230d9d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e0230d9d/fgXMLParser.o ../../../src/XML/fgXMLParser.cpp

${OBJECTDIR}/_ext/52a4beb5/fgApplication.o: ../../../src/fgApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgApplication.o ../../../src/fgApplication.cpp

${OBJECTDIR}/_ext/52a4beb5/fgBuildConfig.o: ../../../src/fgBuildConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgBuildConfig.o ../../../src/fgBuildConfig.cpp

${OBJECTDIR}/_ext/52a4beb5/fgColors.o: ../../../src/fgColors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgColors.o ../../../src/fgColors.cpp

${OBJECTDIR}/_ext/52a4beb5/fgCommon.o: ../../../src/fgCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgCommon.o ../../../src/fgCommon.cpp

${OBJECTDIR}/_ext/52a4beb5/fgDebugConfig.o: ../../../src/fgDebugConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgDebugConfig.o ../../../src/fgDebugConfig.cpp

${OBJECTDIR}/_ext/52a4beb5/fgEngineMain.o: ../../../src/fgEngineMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgEngineMain.o ../../../src/fgEngineMain.cpp

${OBJECTDIR}/_ext/52a4beb5/fgErrno.o: ../../../src/fgErrno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgErrno.o ../../../src/fgErrno.cpp

${OBJECTDIR}/_ext/52a4beb5/fgErrorCodes.o: ../../../src/fgErrorCodes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgErrorCodes.o ../../../src/fgErrorCodes.cpp

${OBJECTDIR}/_ext/52a4beb5/fgLog.o: ../../../src/fgLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgLog.o ../../../src/fgLog.cpp

${OBJECTDIR}/_ext/52a4beb5/fgMessageSubsystem.o: ../../../src/fgMessageSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgMessageSubsystem.o ../../../src/fgMessageSubsystem.cpp

${OBJECTDIR}/_ext/52a4beb5/fgPluginResource.o: ../../../src/fgPluginResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgPluginResource.o ../../../src/fgPluginResource.cpp

${OBJECTDIR}/_ext/52a4beb5/fgSDLApplication.o: ../../../src/fgSDLApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/fgSDLApplication.o ../../../src/fgSDLApplication.cpp

${OBJECTDIR}/_ext/52a4beb5/main.o: ../../../src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/52a4beb5
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -DFG_DEBUG -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_GL_BINDING -DFG_USING_OPENGL -DFG_USING_SDL2 -DFG_USING_TINYXML -DTIXML_USE_STL -D_DEBUG -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream -I../../../modules/stbfont/usascii -I../../../modules/stbfont -I../../../modules/luaplus51-all/Src -I../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src -I../../../modules/zlib_128/contrib/minizip -I../../../modules/simpleopt -I../../../modules/cpp_btree -I../../../modules/assimp/include `pkg-config --cflags gl` `pkg-config --cflags sdl2` `pkg-config --cflags SDL2_mixer` `pkg-config --cflags libpng` `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/52a4beb5/main.o ../../../src/main.cpp

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
