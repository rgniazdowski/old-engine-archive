LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(SDL_PATH) \
	$(LOCAL_PATH)/source_engine \
	$(LOCAL_PATH)/../../../../../../../modules/glm \
	$(LOCAL_PATH)/../../../../../../../modules/tinyxml/upstream \
	$(LOCAL_PATH)/../../../../../../../modules/tinyobj/upstream \
	$(LOCAL_PATH)/../../../../../../../modules/stbfont/usascii \
	$(LOCAL_PATH)/../../../../../../../modules/simpleopt \
	$(LOCAL_PATH)/../../../../../../../modules/luaplus51-all/Src \
	$(LOCAL_PATH)/../../../../../../../modules/luaplus51-all/Src/LuaPlus \
	$(LOCAL_PATH)/../../../../../../../modules/luaplus51-all/Src/LuaPlus/lua52-luaplus/src \
	$(LOCAL_PATH)/../../../../../../../modules/zlib_128/contrib/minizip \
	$(LOCAL_PATH)/../../../../../../../modules/zlib_128 \
	$(LOCAL_PATH)/../../../../../../../modules/cpp_btree \
	$(LOCAL_PATH)/../SDL2_image/external/libpng-1.6.2 \
	$(LOCAL_PATH)/../SDL2_image/external/jpeg-9

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.c \
	$(wildcard $(LOCAL_PATH)/source_engine/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Android/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/XML/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Math/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Physics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Scripting/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Util/*.cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GameLogic/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GFX/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GFX/Particles/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GFX/Scene/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GFX/Shaders/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GFX/Textures/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Audio/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GUI/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/GUI/Font/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Thread/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Resource/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Hardware/*cpp) \
	$(wildcard $(LOCAL_PATH)/source_engine/Event/*cpp) \
	$(wildcard $(LOCAL_PATH)/../../../../../../../modules/tinyobj/upstream/*cpp) \
	$(wildcard $(LOCAL_PATH)/../../../../../../../modules/tinyxml/upstream/*cpp)


LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image zlib_128 ng_luaplus

LOCAL_CFLAGS += -DFG_NO_UNDEF -DFG_USING_SDL2 -DFG_USING_THREADS
LOCAL_CXXFLAGS += -std=c++11 -DFG_NO_UNDEF
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -landroid

ifeq ($(APP_OPTIM),debug)
  LOCAL_CXXFLAGS := -DFG_DEBUG $(LOCAL_CXXFLAGS)
  LOCAL_CFLAGS := -DFG_DEBUG $(LOCAL_CFLAGS)
else
  LOCAL_CXXFLAGS := -DFG_RELEASE $(LOCAL_CXXFLAGS)
  LOCAL_CFLAGS := -DFG_RELEASE $(LOCAL_CFLAGS)
endif

include $(BUILD_SHARED_LIBRARY)


