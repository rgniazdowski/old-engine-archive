#!/bin/bash

tgafilelist=$(ls | sort | grep tga)

for FILE in $tgafilelist;
do
	name=${FILE%.tga}
	echo "Converting $FILE to formats: JPEG - no resize"
	echo convert $FILE -quality 92 ${name}.jpg
	convert $FILE -quality 92 ${name}.jpg
	echo
done
