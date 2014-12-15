#!/bin/bash

# No alpha for iOS
OPTS_REMOVE_ALPHA=( -background black -flatten +matte )

# Android app icon
FILES_AND=( and_36x36.png and_48x48.png and_72x72.png and_96x96.png and_144x144.png and_170x170.png and_192x192.png )
# iOS app icon
FILES_IOS=( ios_57x57.png ios_72x72.png ios_76x76.png ios_114x114.png ios_120x120.png ios_144x144.png ios_152x152.png ios_180x180.png )
# Settings icons
FILES_IOS=( "${FILES_IOS[@]}" ios_settings_29x29.png ios_settings_58x58.png ios_settings_87x87.png )
# Search icon
FILES_IOS=( "${FILES_IOS[@]}" ios_search_40x40.png ios_search_80x80.png ios_search_50x50.png ios_search_100x100.png ios_search_120x120.png )

# WTF, depth is for bits per COLOR, not per PIXEL?
DEPTH_AND=( -depth 8 )
DEPTH_IOS=( -depth 8 )

#TEMPLATE=editable/huggable_template.svg
#TEMPLATE=Fractal-1-Icon.jpg
TEMPLATE=missile-swarm.tga

#######################################
# Android
for fname in "${FILES_AND[@]}"; do
		echo $fname...
		rm -f $fname

		# Extract image size
		size=${fname#and_}
		size=${size%.png}

		width=${size%x*}
		height=${size#*x}

		convert "$TEMPLATE" "${DEPTH_AND[@]}" -resize $size "$fname"

		#inkscape -z -e "$fname" -w "$width" -h "$height" -D "$TEMPLATE"
		#mogrify -background black -flatten +matte "$fname"
done

######################################
# iOS
for fname in "${FILES_IOS[@]}"; do
		echo $fname...
		rm -f $fname

		# Extract image size
		size=${fname#ios_}
		size=${size#spot_}
		size=${size#settings_}
		size=${size#search_}
		size=${size#webclip_}
		size=${size#toolbar_}
		size=${size#tabbar_}
		size=${size%.png}

		width=${size%x*}
		height=${size#*x}

		echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"

		if (( $width == 57 )) ; then
			# App icon iPhone 2G/3G/3GS (iOS 6.1 and earlier)
			fname="Icon.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 72 )) ; then
			# App icon iPad/iPad2/iPad Mini (iOS 6.1 and earlier)
			fname="Icon-72.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 76 )) ; then
			# App icon iPad2/iPad Mini (iOS 7 and later)
			fname="Icon-76.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 114 )) ; then
			# App icon iPhone 4/4S/5/5C/5S (iOS 6.1 and earlier)
			fname="Icon@2x.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 120 )) ; then
			# App icon iPhone 4/4S/5/5C/5S/6 (iOS 7 and later)
			fname="Icon-60@2x.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 144 )) ; then
			# App icon iPad3/iPad4 (iOS 6.1 and earlier)
			fname="Icon-72@2x.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 152 )) ; then
			# App icon iPad3/iPad4/Air/Mini (iOS 7 and later)
			fname="Icon-76@2x.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		elif (( $width == 180 )) ; then
			# App icon iPhone 6 Plus (iOS 8 and later)
			fname="Icon-60@3x.png"
			#echo convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
			#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize $size PNG24:"$fname"
		fi


		#inkscape -z -e "$fname" -w "$width" -h "$height" -D "$TEMPLATE"
		#mogrify -background black -flatten +matte "$fname"
done

######################################
# Large icons
#rm -vf LargeAppIcon_*
#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize 1024x1024 LargeAppIcon_1024.png
#convert "$TEMPLATE" "${DEPTH_IOS[@]}" "${OPTS_REMOVE_ALPHA[@]}" -resize 512x512 LargeAppIcon_512.png


#fname=LargeAppIcon_1024.png
#width=1024
#height=1024
#inkscape -z -e "$fname" -w "$width" -h "$height" -D "$TEMPLATE"
#mogrify -background black -flatten +matte "$fname"

#fname=LargeAppIcon_512.png
#width=512
#height=512
#inkscape -z -e "$fname" -w "$width" -h "$height" -D "$TEMPLATE"
#mogrify -background black -flatten +matte "$fname"

echo
identify *.png


#
# WEB
#

#inkscape -z -e web/web_logo_512.png -w 512 -h 512 -D editable/web_logo.svg
#inkscape -z -e web/web_logo_256.png -w 256 -h 256 -D editable/web_logo.svg
#inkscape -z -e web/web_logo_128.png -w 128 -h 128 -D editable/web_logo.svg
