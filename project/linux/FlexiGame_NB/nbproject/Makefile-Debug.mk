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
	${OBJECTDIR}/_ext/534589759/fgFontDrawer.o \
	${OBJECTDIR}/_ext/534589759/fgFontResource.o \
	${OBJECTDIR}/_ext/534589759/fgGuiButton.o \
	${OBJECTDIR}/_ext/534589759/fgGuiCallback.o \
	${OBJECTDIR}/_ext/534589759/fgGuiConsole.o \
	${OBJECTDIR}/_ext/534589759/fgGuiContainer.o \
	${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o \
	${OBJECTDIR}/_ext/534589759/fgGuiLabel.o \
	${OBJECTDIR}/_ext/534589759/fgGuiLoader.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMain.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMenu.o \
	${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o \
	${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o \
	${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o \
	${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetInterpreter.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleSheet.o \
	${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetInterpreter.o \
	${OBJECTDIR}/_ext/534589759/fgGuiWidget.o \
	${OBJECTDIR}/_ext/477241454/fgGameLogic.o \
	${OBJECTDIR}/_ext/135315005/fgParticleSystem.o \
	${OBJECTDIR}/_ext/135315005/fgPsExplosionEffect.o \
	${OBJECTDIR}/_ext/135315005/fgPsFlashEffect.o \
	${OBJECTDIR}/_ext/135315005/fgPsFlyingDebrisEffect.o \
	${OBJECTDIR}/_ext/135315005/fgPsObjectPulseEffect.o \
	${OBJECTDIR}/_ext/135315005/fgPsParticleDrawer.o \
	${OBJECTDIR}/_ext/135315005/fgPsParticleEffect.o \
	${OBJECTDIR}/_ext/135315005/fgPsParticleEffectCircular.o \
	${OBJECTDIR}/_ext/135315005/fgPsParticleEffectLimited.o \
	${OBJECTDIR}/_ext/135315005/fgPsSequentialEffect.o \
	${OBJECTDIR}/_ext/1960555746/fgTextureLoader.o \
	${OBJECTDIR}/_ext/1960555746/fgTextureManager.o \
	${OBJECTDIR}/_ext/1960555746/fgTextureResource.o \
	${OBJECTDIR}/_ext/500601659/fgGFX2DScene.o \
	${OBJECTDIR}/_ext/500601659/fgGFX3DScene.o \
	${OBJECTDIR}/_ext/500601659/fgGFXCamera.o \
	${OBJECTDIR}/_ext/500601659/fgGFXCameraAnimation.o \
	${OBJECTDIR}/_ext/500601659/fgGFXDrawingBatch.o \
	${OBJECTDIR}/_ext/500601659/fgGFXLight.o \
	${OBJECTDIR}/_ext/500601659/fgGFXMain.o \
	${OBJECTDIR}/_ext/500601659/fgGFXMaterial.o \
	${OBJECTDIR}/_ext/500601659/fgGFXModelOBJResource.o \
	${OBJECTDIR}/_ext/500601659/fgGFXModelResource.o \
	${OBJECTDIR}/_ext/500601659/fgGFXObject.o \
	${OBJECTDIR}/_ext/500601659/fgGFXOctreeBase.o \
	${OBJECTDIR}/_ext/500601659/fgGFXPrimitives.o \
	${OBJECTDIR}/_ext/500601659/fgGFXQuadtreeBase.o \
	${OBJECTDIR}/_ext/500601659/fgGFXSceneManager.o \
	${OBJECTDIR}/_ext/500601659/fgGFXShader.o \
	${OBJECTDIR}/_ext/500601659/fgGFXShaderManager.o \
	${OBJECTDIR}/_ext/500601659/fgGFXShaderProgram.o \
	${OBJECTDIR}/_ext/500601659/fgGFXSimpleDrawer.o \
	${OBJECTDIR}/_ext/500601659/fgGFXTexturing.o \
	${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o \
	${OBJECTDIR}/_ext/484399070/fgHardwareState.o \
	${OBJECTDIR}/_ext/484399070/fgQualityManager.o \
	${OBJECTDIR}/_ext/484399070/fgSensors.o \
	${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o \
	${OBJECTDIR}/_ext/1386528437/MainModule.o \
	${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptManager.o \
	${OBJECTDIR}/_ext/1210739651/fgScriptResource.o \
	${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o \
	${OBJECTDIR}/_ext/1386528437/fgCommon.o \
	${OBJECTDIR}/_ext/1386528437/fgDirent.o \
	${OBJECTDIR}/_ext/1386528437/fgFile.o \
	${OBJECTDIR}/_ext/1386528437/fgGameMain.o \
	${OBJECTDIR}/_ext/1386528437/fgLog.o \
	${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o \
	${OBJECTDIR}/_ext/1386528437/fgPath.o \
	${OBJECTDIR}/_ext/1386528437/fgProfiling.o \
	${OBJECTDIR}/_ext/1386528437/fgResource.o \
	${OBJECTDIR}/_ext/1386528437/fgResourceFactory.o \
	${OBJECTDIR}/_ext/1386528437/fgResourceGroup.o \
	${OBJECTDIR}/_ext/1386528437/fgResourceManager.o \
	${OBJECTDIR}/_ext/1386528437/fgSettings.o \
	${OBJECTDIR}/_ext/1386528437/fgTime.o \
	${OBJECTDIR}/_ext/1386528437/fgXMLParser.o


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
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1279852618/tiny_obj_loader.o ../../../modules/tinyobj/upstream/tiny_obj_loader.cpp

${OBJECTDIR}/_ext/538025686/tinystr.o: ../../../modules/tinyxml/upstream/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinystr.o ../../../modules/tinyxml/upstream/tinystr.cpp

${OBJECTDIR}/_ext/538025686/tinyxml.o: ../../../modules/tinyxml/upstream/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxml.o ../../../modules/tinyxml/upstream/tinyxml.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlerror.o: ../../../modules/tinyxml/upstream/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlerror.o ../../../modules/tinyxml/upstream/tinyxmlerror.cpp

${OBJECTDIR}/_ext/538025686/tinyxmlparser.o: ../../../modules/tinyxml/upstream/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/538025686
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/538025686/tinyxmlparser.o ../../../modules/tinyxml/upstream/tinyxmlparser.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXAudioResource.o: ../../../src/Audio/fgSFXAudioResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXAudioResource.o ../../../src/Audio/fgSFXAudioResource.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXManager.o: ../../../src/Audio/fgSFXManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXManager.o ../../../src/Audio/fgSFXManager.cpp

${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o: ../../../src/Audio/fgSFXMusicResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1650758620
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1650758620/fgSFXMusicResource.o ../../../src/Audio/fgSFXMusicResource.cpp

${OBJECTDIR}/_ext/1654483616/fgArgumentList.o: ../../../src/Event/fgArgumentList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgArgumentList.o ../../../src/Event/fgArgumentList.cpp

${OBJECTDIR}/_ext/1654483616/fgEventManager.o: ../../../src/Event/fgEventManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1654483616
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1654483616/fgEventManager.o ../../../src/Event/fgEventManager.cpp

${OBJECTDIR}/_ext/534589759/fgFontDrawer.o: ../../../src/GUI/fgFontDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgFontDrawer.o ../../../src/GUI/fgFontDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgFontResource.o: ../../../src/GUI/fgFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgFontResource.o ../../../src/GUI/fgFontResource.cpp

${OBJECTDIR}/_ext/534589759/fgGuiButton.o: ../../../src/GUI/fgGuiButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiButton.o ../../../src/GUI/fgGuiButton.cpp

${OBJECTDIR}/_ext/534589759/fgGuiCallback.o: ../../../src/GUI/fgGuiCallback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiCallback.o ../../../src/GUI/fgGuiCallback.cpp

${OBJECTDIR}/_ext/534589759/fgGuiConsole.o: ../../../src/GUI/fgGuiConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiConsole.o ../../../src/GUI/fgGuiConsole.cpp

${OBJECTDIR}/_ext/534589759/fgGuiContainer.o: ../../../src/GUI/fgGuiContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiContainer.o ../../../src/GUI/fgGuiContainer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o: ../../../src/GUI/fgGuiDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiDrawer.o ../../../src/GUI/fgGuiDrawer.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLabel.o: ../../../src/GUI/fgGuiLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLabel.o ../../../src/GUI/fgGuiLabel.cpp

${OBJECTDIR}/_ext/534589759/fgGuiLoader.o: ../../../src/GUI/fgGuiLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiLoader.o ../../../src/GUI/fgGuiLoader.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMain.o: ../../../src/GUI/fgGuiMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMain.o ../../../src/GUI/fgGuiMain.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMenu.o: ../../../src/GUI/fgGuiMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMenu.o ../../../src/GUI/fgGuiMenu.cpp

${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o: ../../../src/GUI/fgGuiMessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiMessageBox.o ../../../src/GUI/fgGuiMessageBox.cpp

${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o: ../../../src/GUI/fgGuiPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiPrimitives.o ../../../src/GUI/fgGuiPrimitives.cpp

${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o: ../../../src/GUI/fgGuiProgressBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiProgressBar.o ../../../src/GUI/fgGuiProgressBar.cpp

${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o: ../../../src/GUI/fgGuiScreenGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiScreenGrid.o ../../../src/GUI/fgGuiScreenGrid.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o: ../../../src/GUI/fgGuiStructureSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheet.o ../../../src/GUI/fgGuiStructureSheet.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetInterpreter.o: ../../../src/GUI/fgGuiStructureSheetInterpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStructureSheetInterpreter.o ../../../src/GUI/fgGuiStructureSheetInterpreter.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleSheet.o: ../../../src/GUI/fgGuiStyleSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleSheet.o ../../../src/GUI/fgGuiStyleSheet.cpp

${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetInterpreter.o: ../../../src/GUI/fgGuiStyleSheetInterpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiStyleSheetInterpreter.o ../../../src/GUI/fgGuiStyleSheetInterpreter.cpp

${OBJECTDIR}/_ext/534589759/fgGuiWidget.o: ../../../src/GUI/fgGuiWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534589759
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534589759/fgGuiWidget.o ../../../src/GUI/fgGuiWidget.cpp

${OBJECTDIR}/_ext/477241454/fgGameLogic.o: ../../../src/GameLogic/fgGameLogic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/477241454
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/477241454/fgGameLogic.o ../../../src/GameLogic/fgGameLogic.cpp

${OBJECTDIR}/_ext/135315005/fgParticleSystem.o: ../../../src/Graphics/Particles/fgParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgParticleSystem.o ../../../src/Graphics/Particles/fgParticleSystem.cpp

${OBJECTDIR}/_ext/135315005/fgPsExplosionEffect.o: ../../../src/Graphics/Particles/fgPsExplosionEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsExplosionEffect.o ../../../src/Graphics/Particles/fgPsExplosionEffect.cpp

${OBJECTDIR}/_ext/135315005/fgPsFlashEffect.o: ../../../src/Graphics/Particles/fgPsFlashEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsFlashEffect.o ../../../src/Graphics/Particles/fgPsFlashEffect.cpp

${OBJECTDIR}/_ext/135315005/fgPsFlyingDebrisEffect.o: ../../../src/Graphics/Particles/fgPsFlyingDebrisEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsFlyingDebrisEffect.o ../../../src/Graphics/Particles/fgPsFlyingDebrisEffect.cpp

${OBJECTDIR}/_ext/135315005/fgPsObjectPulseEffect.o: ../../../src/Graphics/Particles/fgPsObjectPulseEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsObjectPulseEffect.o ../../../src/Graphics/Particles/fgPsObjectPulseEffect.cpp

${OBJECTDIR}/_ext/135315005/fgPsParticleDrawer.o: ../../../src/Graphics/Particles/fgPsParticleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsParticleDrawer.o ../../../src/Graphics/Particles/fgPsParticleDrawer.cpp

${OBJECTDIR}/_ext/135315005/fgPsParticleEffect.o: ../../../src/Graphics/Particles/fgPsParticleEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsParticleEffect.o ../../../src/Graphics/Particles/fgPsParticleEffect.cpp

${OBJECTDIR}/_ext/135315005/fgPsParticleEffectCircular.o: ../../../src/Graphics/Particles/fgPsParticleEffectCircular.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsParticleEffectCircular.o ../../../src/Graphics/Particles/fgPsParticleEffectCircular.cpp

${OBJECTDIR}/_ext/135315005/fgPsParticleEffectLimited.o: ../../../src/Graphics/Particles/fgPsParticleEffectLimited.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsParticleEffectLimited.o ../../../src/Graphics/Particles/fgPsParticleEffectLimited.cpp

${OBJECTDIR}/_ext/135315005/fgPsSequentialEffect.o: ../../../src/Graphics/Particles/fgPsSequentialEffect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/135315005
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/135315005/fgPsSequentialEffect.o ../../../src/Graphics/Particles/fgPsSequentialEffect.cpp

${OBJECTDIR}/_ext/1960555746/fgTextureLoader.o: ../../../src/Graphics/Textures/fgTextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1960555746
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1960555746/fgTextureLoader.o ../../../src/Graphics/Textures/fgTextureLoader.cpp

${OBJECTDIR}/_ext/1960555746/fgTextureManager.o: ../../../src/Graphics/Textures/fgTextureManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1960555746
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1960555746/fgTextureManager.o ../../../src/Graphics/Textures/fgTextureManager.cpp

${OBJECTDIR}/_ext/1960555746/fgTextureResource.o: ../../../src/Graphics/Textures/fgTextureResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1960555746
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1960555746/fgTextureResource.o ../../../src/Graphics/Textures/fgTextureResource.cpp

${OBJECTDIR}/_ext/500601659/fgGFX2DScene.o: ../../../src/Graphics/fgGFX2DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFX2DScene.o ../../../src/Graphics/fgGFX2DScene.cpp

${OBJECTDIR}/_ext/500601659/fgGFX3DScene.o: ../../../src/Graphics/fgGFX3DScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFX3DScene.o ../../../src/Graphics/fgGFX3DScene.cpp

${OBJECTDIR}/_ext/500601659/fgGFXCamera.o: ../../../src/Graphics/fgGFXCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXCamera.o ../../../src/Graphics/fgGFXCamera.cpp

${OBJECTDIR}/_ext/500601659/fgGFXCameraAnimation.o: ../../../src/Graphics/fgGFXCameraAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXCameraAnimation.o ../../../src/Graphics/fgGFXCameraAnimation.cpp

${OBJECTDIR}/_ext/500601659/fgGFXDrawingBatch.o: ../../../src/Graphics/fgGFXDrawingBatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXDrawingBatch.o ../../../src/Graphics/fgGFXDrawingBatch.cpp

${OBJECTDIR}/_ext/500601659/fgGFXLight.o: ../../../src/Graphics/fgGFXLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXLight.o ../../../src/Graphics/fgGFXLight.cpp

${OBJECTDIR}/_ext/500601659/fgGFXMain.o: ../../../src/Graphics/fgGFXMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXMain.o ../../../src/Graphics/fgGFXMain.cpp

${OBJECTDIR}/_ext/500601659/fgGFXMaterial.o: ../../../src/Graphics/fgGFXMaterial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXMaterial.o ../../../src/Graphics/fgGFXMaterial.cpp

${OBJECTDIR}/_ext/500601659/fgGFXModelOBJResource.o: ../../../src/Graphics/fgGFXModelOBJResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXModelOBJResource.o ../../../src/Graphics/fgGFXModelOBJResource.cpp

${OBJECTDIR}/_ext/500601659/fgGFXModelResource.o: ../../../src/Graphics/fgGFXModelResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXModelResource.o ../../../src/Graphics/fgGFXModelResource.cpp

${OBJECTDIR}/_ext/500601659/fgGFXObject.o: ../../../src/Graphics/fgGFXObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXObject.o ../../../src/Graphics/fgGFXObject.cpp

${OBJECTDIR}/_ext/500601659/fgGFXOctreeBase.o: ../../../src/Graphics/fgGFXOctreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXOctreeBase.o ../../../src/Graphics/fgGFXOctreeBase.cpp

${OBJECTDIR}/_ext/500601659/fgGFXPrimitives.o: ../../../src/Graphics/fgGFXPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXPrimitives.o ../../../src/Graphics/fgGFXPrimitives.cpp

${OBJECTDIR}/_ext/500601659/fgGFXQuadtreeBase.o: ../../../src/Graphics/fgGFXQuadtreeBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXQuadtreeBase.o ../../../src/Graphics/fgGFXQuadtreeBase.cpp

${OBJECTDIR}/_ext/500601659/fgGFXSceneManager.o: ../../../src/Graphics/fgGFXSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXSceneManager.o ../../../src/Graphics/fgGFXSceneManager.cpp

${OBJECTDIR}/_ext/500601659/fgGFXShader.o: ../../../src/Graphics/fgGFXShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXShader.o ../../../src/Graphics/fgGFXShader.cpp

${OBJECTDIR}/_ext/500601659/fgGFXShaderManager.o: ../../../src/Graphics/fgGFXShaderManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXShaderManager.o ../../../src/Graphics/fgGFXShaderManager.cpp

${OBJECTDIR}/_ext/500601659/fgGFXShaderProgram.o: ../../../src/Graphics/fgGFXShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXShaderProgram.o ../../../src/Graphics/fgGFXShaderProgram.cpp

${OBJECTDIR}/_ext/500601659/fgGFXSimpleDrawer.o: ../../../src/Graphics/fgGFXSimpleDrawer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXSimpleDrawer.o ../../../src/Graphics/fgGFXSimpleDrawer.cpp

${OBJECTDIR}/_ext/500601659/fgGFXTexturing.o: ../../../src/Graphics/fgGFXTexturing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/500601659
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/500601659/fgGFXTexturing.o ../../../src/Graphics/fgGFXTexturing.cpp

${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o: ../../../src/Hardware/fgDeviceQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgDeviceQuery.o ../../../src/Hardware/fgDeviceQuery.cpp

${OBJECTDIR}/_ext/484399070/fgHardwareState.o: ../../../src/Hardware/fgHardwareState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgHardwareState.o ../../../src/Hardware/fgHardwareState.cpp

${OBJECTDIR}/_ext/484399070/fgQualityManager.o: ../../../src/Hardware/fgQualityManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgQualityManager.o ../../../src/Hardware/fgQualityManager.cpp

${OBJECTDIR}/_ext/484399070/fgSensors.o: ../../../src/Hardware/fgSensors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/484399070
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/484399070/fgSensors.o ../../../src/Hardware/fgSensors.cpp

${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o: ../../../src/Input/fgTouchReceiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1657950160
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1657950160/fgTouchReceiver.o ../../../src/Input/fgTouchReceiver.cpp

${OBJECTDIR}/_ext/1386528437/MainModule.o: ../../../src/MainModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/MainModule.o ../../../src/MainModule.cpp

${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o: ../../../src/Math/fgKalmanFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607778370
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607778370/fgKalmanFilter.o ../../../src/Math/fgKalmanFilter.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptManager.o: ../../../src/Scripting/fgScriptManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptManager.o ../../../src/Scripting/fgScriptManager.cpp

${OBJECTDIR}/_ext/1210739651/fgScriptResource.o: ../../../src/Scripting/fgScriptResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1210739651
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1210739651/fgScriptResource.o ../../../src/Scripting/fgScriptResource.cpp

${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o: ../../../src/fgBuildConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgBuildConfig.o ../../../src/fgBuildConfig.cpp

${OBJECTDIR}/_ext/1386528437/fgCommon.o: ../../../src/fgCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgCommon.o ../../../src/fgCommon.cpp

${OBJECTDIR}/_ext/1386528437/fgDirent.o: ../../../src/fgDirent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgDirent.o ../../../src/fgDirent.cpp

${OBJECTDIR}/_ext/1386528437/fgFile.o: ../../../src/fgFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgFile.o ../../../src/fgFile.cpp

${OBJECTDIR}/_ext/1386528437/fgGameMain.o: ../../../src/fgGameMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgGameMain.o ../../../src/fgGameMain.cpp

${OBJECTDIR}/_ext/1386528437/fgLog.o: ../../../src/fgLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgLog.o ../../../src/fgLog.cpp

${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o: ../../../src/fgMessageSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgMessageSubsystem.o ../../../src/fgMessageSubsystem.cpp

${OBJECTDIR}/_ext/1386528437/fgPath.o: ../../../src/fgPath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgPath.o ../../../src/fgPath.cpp

${OBJECTDIR}/_ext/1386528437/fgProfiling.o: ../../../src/fgProfiling.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgProfiling.o ../../../src/fgProfiling.cpp

${OBJECTDIR}/_ext/1386528437/fgResource.o: ../../../src/fgResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgResource.o ../../../src/fgResource.cpp

${OBJECTDIR}/_ext/1386528437/fgResourceFactory.o: ../../../src/fgResourceFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgResourceFactory.o ../../../src/fgResourceFactory.cpp

${OBJECTDIR}/_ext/1386528437/fgResourceGroup.o: ../../../src/fgResourceGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgResourceGroup.o ../../../src/fgResourceGroup.cpp

${OBJECTDIR}/_ext/1386528437/fgResourceManager.o: ../../../src/fgResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgResourceManager.o ../../../src/fgResourceManager.cpp

${OBJECTDIR}/_ext/1386528437/fgSettings.o: ../../../src/fgSettings.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgSettings.o ../../../src/fgSettings.cpp

${OBJECTDIR}/_ext/1386528437/fgTime.o: ../../../src/fgTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgTime.o ../../../src/fgTime.cpp

${OBJECTDIR}/_ext/1386528437/fgXMLParser.o: ../../../src/fgXMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall `pkg-config --cflags libpng` `pkg-config --cflags gl` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/fgXMLParser.o ../../../src/fgXMLParser.cpp

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
