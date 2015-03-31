#!/bin/bash

if ! [ -L SDL2 ]; then
	echo "Linking SDL2 library for JNI compilation"
	ln -s ../../../../../../modules/SDL2-2.0.3 SDL2
	unlink SDL2/SDL2
	ln -s include SDL2/SDL2
fi

unlink SDL2_image
if ! [ -L SDL2_image ]; then
	echo "Linking SDL2_image library for JNI compilation"
	ln -s ../../../../../../modules/SDL2_image-2.0.0 SDL2_image
	unlink SDL2/include/SDL_image.h
	ln -s ../../SDL2_image-2.0.0/SDL_image.h SDL2/include/SDL_image.h
	unlink smpeg2
	ln -s SDL2_mixer/external/smpeg2-2.0.0/ smpeg2
	unlink libmikmod
	ln -s SDL2_mixer/external/libmikmod-3.1.12/ libmikmod
fi

unlink SDL2_mixer
if ! [ -L SDL2_mixer ]; then
	echo "Linking SDL2_mixer library for JNI compilation"
	ln -s ../../../../../../modules/SDL2_mixer-2.0.0 SDL2_mixer
	unlink SDL2/include/SDL_mixer.h
	ln -s ../../SDL2_mixer-2.0.0/SDL_mixer.h SDL2/include/SDL_mixer.h
fi

if ! [ -L zlib_128 ]; then
	echo "Linking ZLib 1.28 + Contrib/MiniZip project for JNI compilation"
	ln -s ../../../../../../modules/zlib_128 zlib_128
fi

if ! [ -L LuaPlus ]; then
	echo "Linking NextGen branch of LuaPlus, latest revision + Lua 5.2 lib for JNI compilation"
	ln -s ../../../../../../modules/luaplus51-all/Src/LuaPlus LuaPlus
fi
