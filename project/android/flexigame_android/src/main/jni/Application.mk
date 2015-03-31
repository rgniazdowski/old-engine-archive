#
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
APP_STL := gnustl_static
APP_PLATFORM := android-16
APP_ABI := armeabi armeabi-v7a
APP_OPTIM := release
NDK_DEBUG := false

# For SDL_mixer
#
SUPPORT_MOD_MODPLUG := false
SUPPORT_MOD_MIKMOD := true
SUPPORT_MP3_SMPEG := true
SUPPORT_OGG := false

# For SDL_image
#
SUPPORT_PNG := true
SUPPORT_JPG := true
SUPPORT_WEBP := false

# For SDL_net
#

# For SDL_ttf
#

LIBCXX_FORCE_REBUILD := false

