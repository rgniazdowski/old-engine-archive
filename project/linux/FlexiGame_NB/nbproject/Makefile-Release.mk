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
	${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o \
	${OBJECTDIR}/_ext/538025686/tinystr.o \
	${OBJECTDIR}/_ext/538025686/tinyxml.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlerror.o \
	${OBJECTDIR}/_ext/538025686/tinyxmlparser.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXAudioResource.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXManager.o \
	${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o \
	${OBJECTDIR}/_ext/1654483616/fgArgumentList.o \
	${OBJECTDIR}/_ext/1654483616/fgEventManager.o \
	${OBJECTDIR}/_ext/293675389/fgParticleSystem.o \
	${OBJECTDIR}/_ext/293675389/fgPsExplosionEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsFlashEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsFlyingDebrisEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsObjectPulseEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleDrawer.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o \
	${OBJECTDIR}/_ext/293675389/fgPsParticleEffectLimited.o \
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
	${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o \
	${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o \
	${OBJECTDIR}/_ext/534590209/fgGFXLight.o \
	${OBJECTDIR}/_ext/534590209/fgGFXMain.o \
	${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o \
	${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o \
	${OBJECTDIR}/_ext/534590209/fgGFXObject.o \
	${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o \
	${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o \
	${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o \
	${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o \
	${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o \
	${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o \
	${OBJECTDIR}/_ext/534589759/fgFontDrawer.o \
	${OBJECTDIR}/_ext/534589759/fgFontResource.o \
	${OBJECTDIR}/_ext/534589759/fgGuiButton.o \
	${OBJECTDIR}/_ext/534589759/fgGuiCallback.o \
	${OBJECTDIR}/_ext/534589759/fgGuiConsole.o \
	${OBJECTDIR}/_ext/534589759/fgGuiContainer.o \
	${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o \
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
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyle.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetParser.o \
	${OBJECTDIR}/_ext/534589759/fgGuiTable.o \
	${OBJECTDIR}/_ext/534589759/fgGuiText.o \
	${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o \
	${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidget.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o \
	${OBJECTDIR}/_ext/477241454/fgGameLogic.o \
	${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o \
	${OBJECTDIR}/_ext/484399070/fgHardwareState.o \
	${OBJECTDIR}/_ext/484399070/fgQualityManager.o \
	${OBJECTDIR}/_ext/484399070/fgSensors.o \
	${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o \
	${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o \
	${OBJECTDIR}/_ext/942373304/fgResource.o \
	${OBJECTDIR}/_ext/942373304/fgResourceFactory.o \
	${OBJECTDIR}/_ext/942373304/fgResourceGroup.o \
	${OBJECTDIR}/_ext/942373304/fgResourceManager.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptManager.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptResource.o \
	${OBJECTDIR}/_ext/608034620/fgConfig.o \
	${OBJECTDIR}/_ext/608034620/fgConfigParser.o \
	${OBJECTDIR}/_ext/608034620/fgConfigWriter.o \
	${OBJECTDIR}/_ext/608034620/fgDirent.o \
	${OBJECTDIR}/_ext/608034620/fgFile.o \
	${OBJECTDIR}/_ext/608034620/fgPath.o \
	${OBJECTDIR}/_ext/608034620/fgProfiling.o \
	${OBJECTDIR}/_ext/608034620/fgSettings.o \
	${OBJECTDIR}/_ext/608034620/fgTime.o \
	${OBJECTDIR}/_ext/534573667/fgXMLParser.o \
	${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o \
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
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flexigame_nb ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o: ../../../modules/tinyobj/upstream/tiny_obj_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1279852618
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o ../../../modules/tinyobj/upstream/tiny_obj_loader.cpp

${OBJECTDIR}/_ext/538025686/tinystr.o: ../../../modules/tinyxml/upstream/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinystr.o ../../../modules/tinyxml/upstream/tinystr.cpp

${OBJECTDIR}/_ext/538025686/tinyxml.o: ../../../modules/tinyxml/upstream/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxml.o ../../../modules/tinyxml/upstream/tinyxml.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlerror.o: ../../../modules/tinyxml/upstream/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlerror.o ../../../modules/tinyxml/upstream/tinyxmlerror.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlparser.o: ../../../modules/tinyxml/upstream/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlparser.o ../../../modules/tinyxml/upstream/tinyxmlparser.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXAudioResource.o: ../../../src/Audio/fgSFXAudioResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXAudioResource.o ../../../src/Audio/fgSFXAudioResource.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXManager.o: ../../../src/Audio/fgSFXManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXManager.o ../../../src/Audio/fgSFXManager.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o: ../../../src/Audio/fgSFXMusicResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o ../../../src/Audio/fgSFXMusicResource.cpp

${OBJECTDIR}/_ext/1654483616/fgArgumentList.o: ../../../src/Event/fgArgumentList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgArgumentList.o ../../../src/Event/fgArgumentList.cpp

${OBJECTDIR}/_ext/1654483616/fgEventManager.o: ../../../src/Event/fgEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgEventManager.o ../../../src/Event/fgEventManager.cpp

${OBJECTDIR}/_ext/293675389/fgParticleSystem.o: ../../../src/GFX/Particles/fgParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgParticleSystem.o ../../../src/GFX/Particles/fgParticleSystem.cpp

${OBJECTDIR}/_ext/293675389/fgPsExplosionEffect.o: ../../../src/GFX/Particles/fgPsExplosionEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsExplosionEffect.o ../../../src/GFX/Particles/fgPsExplosionEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsFlashEffect.o: ../../../src/GFX/Particles/fgPsFlashEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsFlashEffect.o ../../../src/GFX/Particles/fgPsFlashEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsFlyingDebrisEffect.o: ../../../src/GFX/Particles/fgPsFlyingDebrisEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsFlyingDebrisEffect.o ../../../src/GFX/Particles/fgPsFlyingDebrisEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsObjectPulseEffect.o: ../../../src/GFX/Particles/fgPsObjectPulseEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsObjectPulseEffect.o ../../../src/GFX/Particles/fgPsObjectPulseEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleDrawer.o: ../../../src/GFX/Particles/fgPsParticleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleDrawer.o ../../../src/GFX/Particles/fgPsParticleDrawer.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o: ../../../src/GFX/Particles/fgPsParticleEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffect.o ../../../src/GFX/Particles/fgPsParticleEffect.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o: ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffectCircular.o ../../../src/GFX/Particles/fgPsParticleEffectCircular.cpp

${OBJECTDIR}/_ext/293675389/fgPsParticleEffectLimited.o: ../../../src/GFX/Particles/fgPsParticleEffectLimited.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsParticleEffectLimited.o ../../../src/GFX/Particles/fgPsParticleEffectLimited.cpp

${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o: ../../../src/GFX/Particles/fgPsSequentialEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/293675389
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/293675389/fgPsSequentialEffect.o ../../../src/GFX/Particles/fgPsSequentialEffect.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShader.o: ../../../src/GFX/Shaders/fgGFXShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShader.o ../../../src/GFX/Shaders/fgGFXShader.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderBase.o: ../../../src/GFX/Shaders/fgGFXShaderBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderBase.o ../../../src/GFX/Shaders/fgGFXShaderBase.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderConfig.o: ../../../src/GFX/Shaders/fgGFXShaderConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderConfig.o ../../../src/GFX/Shaders/fgGFXShaderConfig.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderManager.o: ../../../src/GFX/Shaders/fgGFXShaderManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderManager.o ../../../src/GFX/Shaders/fgGFXShaderManager.cpp

${OBJECTDIR}/_ext/960776194/fgGFXShaderProgram.o: ../../../src/GFX/Shaders/fgGFXShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/960776194
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/960776194/fgGFXShaderProgram.o ../../../src/GFX/Shaders/fgGFXShaderProgram.cpp

${OBJECTDIR}/_ext/34731496/fgTextureLoader.o: ../../../src/GFX/Textures/fgTextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureLoader.o ../../../src/GFX/Textures/fgTextureLoader.cpp

${OBJECTDIR}/_ext/34731496/fgTextureManager.o: ../../../src/GFX/Textures/fgTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureManager.o ../../../src/GFX/Textures/fgTextureManager.cpp

${OBJECTDIR}/_ext/34731496/fgTextureResource.o: ../../../src/GFX/Textures/fgTextureResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/34731496
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34731496/fgTextureResource.o ../../../src/GFX/Textures/fgTextureResource.cpp

${OBJECTDIR}/_ext/534590209/fgGFX2DScene.o: ../../../src/GFX/fgGFX2DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFX2DScene.o ../../../src/GFX/fgGFX2DScene.cpp

${OBJECTDIR}/_ext/534590209/fgGFX3DScene.o: ../../../src/GFX/fgGFX3DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFX3DScene.o ../../../src/GFX/fgGFX3DScene.cpp

${OBJECTDIR}/_ext/534590209/fgGFXCamera.o: ../../../src/GFX/fgGFXCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXCamera.o ../../../src/GFX/fgGFXCamera.cpp

${OBJECTDIR}/_ext/534590209/fgGFXCameraAnimation.o: ../../../src/GFX/fgGFXCameraAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXCameraAnimation.o ../../../src/GFX/fgGFXCameraAnimation.cpp

${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o: ../../../src/GFX/fgGFXDrawCall.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXDrawCall.o ../../../src/GFX/fgGFXDrawCall.cpp

${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o: ../../../src/GFX/fgGFXDrawingBatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXDrawingBatch.o ../../../src/GFX/fgGFXDrawingBatch.cpp

${OBJECTDIR}/_ext/534590209/fgGFXLight.o: ../../../src/GFX/fgGFXLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXLight.o ../../../src/GFX/fgGFXLight.cpp

${OBJECTDIR}/_ext/534590209/fgGFXMain.o: ../../../src/GFX/fgGFXMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXMain.o ../../../src/GFX/fgGFXMain.cpp

${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o: ../../../src/GFX/fgGFXMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXMaterial.o ../../../src/GFX/fgGFXMaterial.cpp

${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o: ../../../src/GFX/fgGFXModelResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXModelResource.o ../../../src/GFX/fgGFXModelResource.cpp

${OBJECTDIR}/_ext/534590209/fgGFXObject.o: ../../../src/GFX/fgGFXObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXObject.o ../../../src/GFX/fgGFXObject.cpp

${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o: ../../../src/GFX/fgGFXOctreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXOctreeBase.o ../../../src/GFX/fgGFXOctreeBase.cpp

${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o: ../../../src/GFX/fgGFXPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXPrimitives.o ../../../src/GFX/fgGFXPrimitives.cpp

${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o: ../../../src/GFX/fgGFXQuadtreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXQuadtreeBase.o ../../../src/GFX/fgGFXQuadtreeBase.cpp

${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o: ../../../src/GFX/fgGFXSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXSceneManager.o ../../../src/GFX/fgGFXSceneManager.cpp

${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o: ../../../src/GFX/fgGFXSimpleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXSimpleDrawer.o ../../../src/GFX/fgGFXSimpleDrawer.cpp

${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o: ../../../src/GFX/fgGFXTexturing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534590209
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534590209/fgGFXTexturing.o ../../../src/GFX/fgGFXTexturing.cpp

${OBJECTDIR}/_ext/534589759/fgFontDrawer.o: ../../../src/GUI/fgFontDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgFontDrawer.o ../../../src/GUI/fgFontDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgFontResource.o: ../../../src/GUI/fgFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgFontResource.o ../../../src/GUI/fgFontResource.cpp

${OBJECTDIR}/_ext/534589759/fgGuiButton.o: ../../../src/GUI/fgGuiButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiButton.o ../../../src/GUI/fgGuiButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiCallback.o: ../../../src/GUI/fgGuiCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiCallback.o ../../../src/GUI/fgGuiCallback.cpp

${OBJECTDIR}/_ext/534589759/fgGuiConsole.o: ../../../src/GUI/fgGuiConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiConsole.o ../../../src/GUI/fgGuiConsole.cpp

${OBJECTDIR}/_ext/534589759/fgGuiContainer.o: ../../../src/GUI/fgGuiContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiContainer.o ../../../src/GUI/fgGuiContainer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o: ../../../src/GUI/fgGuiDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o ../../../src/GUI/fgGuiDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiFrame.o: ../../../src/GUI/fgGuiFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiFrame.o ../../../src/GUI/fgGuiFrame.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLabel.o: ../../../src/GUI/fgGuiLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLabel.o ../../../src/GUI/fgGuiLabel.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLoader.o: ../../../src/GUI/fgGuiLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLoader.o ../../../src/GUI/fgGuiLoader.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMain.o: ../../../src/GUI/fgGuiMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMain.o ../../../src/GUI/fgGuiMain.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMenu.o: ../../../src/GUI/fgGuiMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMenu.o ../../../src/GUI/fgGuiMenu.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o: ../../../src/GUI/fgGuiMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o ../../../src/GUI/fgGuiMessageBox.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPopup.o: ../../../src/GUI/fgGuiPopup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPopup.o ../../../src/GUI/fgGuiPopup.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o: ../../../src/GUI/fgGuiPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o ../../../src/GUI/fgGuiPrimitives.cpp

${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o: ../../../src/GUI/fgGuiProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o ../../../src/GUI/fgGuiProgressBar.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o: ../../../src/GUI/fgGuiScreenGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o ../../../src/GUI/fgGuiScreenGrid.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o: ../../../src/GUI/fgGuiStructureSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o ../../../src/GUI/fgGuiStructureSheet.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o: ../../../src/GUI/fgGuiStructureSheetParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetParser.o ../../../src/GUI/fgGuiStructureSheetParser.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyle.o: ../../../src/GUI/fgGuiStyle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyle.o ../../../src/GUI/fgGuiStyle.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o: ../../../src/GUI/fgGuiStyleContent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleContent.o ../../../src/GUI/fgGuiStyleContent.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetParser.o: ../../../src/GUI/fgGuiStyleSheetParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetParser.o ../../../src/GUI/fgGuiStyleSheetParser.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTable.o: ../../../src/GUI/fgGuiTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTable.o ../../../src/GUI/fgGuiTable.cpp

${OBJECTDIR}/_ext/534589759/fgGuiText.o: ../../../src/GUI/fgGuiText.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiText.o ../../../src/GUI/fgGuiText.cpp

${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o: ../../../src/GUI/fgGuiTextArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiTextArea.o ../../../src/GUI/fgGuiTextArea.cpp

${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o: ../../../src/GUI/fgGuiToggleButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiToggleButton.o ../../../src/GUI/fgGuiToggleButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidget.o: ../../../src/GUI/fgGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidget.o ../../../src/GUI/fgGuiWidget.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o: ../../../src/GUI/fgGuiWidgetFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidgetFactory.o ../../../src/GUI/fgGuiWidgetFactory.cpp

${OBJECTDIR}/_ext/477241454/fgGameLogic.o: ../../../src/GameLogic/fgGameLogic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/477241454
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/477241454/fgGameLogic.o ../../../src/GameLogic/fgGameLogic.cpp

${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o: ../../../src/Hardware/fgDeviceQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o ../../../src/Hardware/fgDeviceQuery.cpp

${OBJECTDIR}/_ext/484399070/fgHardwareState.o: ../../../src/Hardware/fgHardwareState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgHardwareState.o ../../../src/Hardware/fgHardwareState.cpp

${OBJECTDIR}/_ext/484399070/fgQualityManager.o: ../../../src/Hardware/fgQualityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgQualityManager.o ../../../src/Hardware/fgQualityManager.cpp

${OBJECTDIR}/_ext/484399070/fgSensors.o: ../../../src/Hardware/fgSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgSensors.o ../../../src/Hardware/fgSensors.cpp

${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o: ../../../src/Input/fgTouchReceiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1657950160
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o ../../../src/Input/fgTouchReceiver.cpp

${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o: ../../../src/Math/fgKalmanFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607778370
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o ../../../src/Math/fgKalmanFilter.cpp

${OBJECTDIR}/_ext/942373304/fgResource.o: ../../../src/Resource/fgResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResource.o ../../../src/Resource/fgResource.cpp

${OBJECTDIR}/_ext/942373304/fgResourceFactory.o: ../../../src/Resource/fgResourceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceFactory.o ../../../src/Resource/fgResourceFactory.cpp

${OBJECTDIR}/_ext/942373304/fgResourceGroup.o: ../../../src/Resource/fgResourceGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceGroup.o ../../../src/Resource/fgResourceGroup.cpp

${OBJECTDIR}/_ext/942373304/fgResourceManager.o: ../../../src/Resource/fgResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/942373304
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/942373304/fgResourceManager.o ../../../src/Resource/fgResourceManager.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptManager.o: ../../../src/Scripting/fgScriptManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptManager.o ../../../src/Scripting/fgScriptManager.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptResource.o: ../../../src/Scripting/fgScriptResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptResource.o ../../../src/Scripting/fgScriptResource.cpp

${OBJECTDIR}/_ext/608034620/fgConfig.o: ../../../src/Util/fgConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfig.o ../../../src/Util/fgConfig.cpp

${OBJECTDIR}/_ext/608034620/fgConfigParser.o: ../../../src/Util/fgConfigParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigParser.o ../../../src/Util/fgConfigParser.cpp

${OBJECTDIR}/_ext/608034620/fgConfigWriter.o: ../../../src/Util/fgConfigWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgConfigWriter.o ../../../src/Util/fgConfigWriter.cpp

${OBJECTDIR}/_ext/608034620/fgDirent.o: ../../../src/Util/fgDirent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgDirent.o ../../../src/Util/fgDirent.cpp

${OBJECTDIR}/_ext/608034620/fgFile.o: ../../../src/Util/fgFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgFile.o ../../../src/Util/fgFile.cpp

${OBJECTDIR}/_ext/608034620/fgPath.o: ../../../src/Util/fgPath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgPath.o ../../../src/Util/fgPath.cpp

${OBJECTDIR}/_ext/608034620/fgProfiling.o: ../../../src/Util/fgProfiling.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgProfiling.o ../../../src/Util/fgProfiling.cpp

${OBJECTDIR}/_ext/608034620/fgSettings.o: ../../../src/Util/fgSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgSettings.o ../../../src/Util/fgSettings.cpp

${OBJECTDIR}/_ext/608034620/fgTime.o: ../../../src/Util/fgTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/608034620
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/608034620/fgTime.o ../../../src/Util/fgTime.cpp

${OBJECTDIR}/_ext/534573667/fgXMLParser.o: ../../../src/XML/fgXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534573667
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534573667/fgXMLParser.o ../../../src/XML/fgXMLParser.cpp

${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o: ../../../src/fgBuildConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o ../../../src/fgBuildConfig.cpp

${OBJECTDIR}/_ext/1386528437/fgCommon.o: ../../../src/fgCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgCommon.o ../../../src/fgCommon.cpp

${OBJECTDIR}/_ext/1386528437/fgErrno.o: ../../../src/fgErrno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrno.o ../../../src/fgErrno.cpp

${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o: ../../../src/fgErrorCodes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgErrorCodes.o ../../../src/fgErrorCodes.cpp

${OBJECTDIR}/_ext/1386528437/fgGameMain.o: ../../../src/fgGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgGameMain.o ../../../src/fgGameMain.cpp

${OBJECTDIR}/_ext/1386528437/fgLog.o: ../../../src/fgLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgLog.o ../../../src/fgLog.cpp

${OBJECTDIR}/_ext/1386528437/fgMainModule.o: ../../../src/fgMainModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMainModule.o ../../../src/fgMainModule.cpp

${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o: ../../../src/fgMessageSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o ../../../src/fgMessageSubsystem.cpp

${OBJECTDIR}/_ext/1386528437/fgStatusReporter.o: ../../../src/fgStatusReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DTIXML_USE_STL -DFG_USING_SDL2 -DFG_USING_OPENGL -DFG_NO_UNDEF -DFG_USING_GLM -DFG_USING_TINYXML -I../../../src -I../../../modules/glm -I../../../modules/tinyobj/upstream -I../../../modules/tinyxml/upstream `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgStatusReporter.o ../../../src/fgStatusReporter.cpp

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
