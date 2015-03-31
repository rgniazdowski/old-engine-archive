LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := zlib_128

LOCAL_C_INCLUDES := $(LOCAL_PATH)/contrib/minizip \
	$(LOCAL_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(LOCAL_PATH)/contrib/minizip/ioapi.c \
	$(LOCAL_PATH)/contrib/minizip/ioapi_mem.c \
	$(LOCAL_PATH)/contrib/minizip/ioapi_buf.c \
	$(LOCAL_PATH)/contrib/minizip/unzip.c \
	$(LOCAL_PATH)/contrib/minizip/zip.c \
	$(wildcard $(LOCAL_PATH)/contrib/minizip/aes/*.c) \
	$(wildcard $(LOCAL_PATH)/*.c)

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_CFLAGS += -DFG_NO_UNDEF -DHAVE_AES -DHAVE_MEMCPY -DZ_PREFIX -DHAS_STDINT_H -DUSE_FILE32API
LOCAL_CXXFLAGS += -std=c++11 -Wall -DFG_NO_UNDEF -DHAVE_AES -DHAVE_MEMCPY -DZ_PREFIX -DHAS_STDINT_H -DUSE_FILE32API
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)


