#!/bin/bash

echo "Multiple APK installation - android"

if test "$#" -eq 0; then
    echo "** Illegal number of parameters!"
	echo "Please pass the build: release or debug"
	echo "Additional second parameter is a deployment name"
	exit
fi

FG_BUILD_NAME=$1
FG_DEPLOYMENT_NAME=default

if test "$#" -eq 2; then
	echo "Passed additional parameter: deployment name $2"
	FG_DEPLOYMENT_NAME=$2
fi


#dirname $0
cd `dirname $0`
cd ../

adb devices

for SERIAL in $(adb devices | tail -n +2 | cut -sf 1);
do
  for APKLIST in $(find deployments | grep apk | grep android | grep $FG_BUILD_NAME | grep $FG_DEPLOYMENT_NAME);
  do
  echo "Installing $APKLIST on $SERIAL device"
  export ANDROID_SERIAL=$SERIAL
  adb install -r $APKLIST
  done

done
