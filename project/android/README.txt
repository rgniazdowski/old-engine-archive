
This folder structure holds two types of projects:
- One is for Android Studio which is now the officially supported IDE for
  Android development (based on Intellij IDEA), it uses Gradle build system 
  instead of Ant. There are some downsides:
	-	NDK plugin supports only on library so this is disabled and hacks are
		in place to build the NDK libraries (main flexigame library, SDL,
		SDL_mixer, SDL_image, minizip/zlib 1.28, LuaPlus-5.2)
	-	On device debugging is supported only for Java - which in this case is
		only SDL Activity startup

- Second in flexigame_android/src/main is for Eclipse
	-	build structure is different - meaning different folders are used
	-	different APK is being built, different debug signing key is used,
		maybe this can be fixed
	-	it uses however already build NDK libs - need to build them separately
		but thankfully the paths match 
	-	symlink src -> java needs to be in place so the SDLActivity is compiled
	-	On device NDK code debugging (C++/C) is functional, however:
		-	For some reason while debugging on Eclipse the debug symbols are not
			being loaded - breakpoints can be set beforehand
		-	Using cgdb for separate debugging process works however may hang,
			disconnect (loads symbols, shows code, breakpoints work)
		-	Using gdb(arm,android) separately also works
		-	Using ddd is difficult, does not work, symbols are not loaded,
			cannot set a breakpoint - when activating ddd the application on 
			device hangs (pauses, is waiting for signal) and the gdb/ddd also
			pauses waiting for something - cannot debug - need to check this.
