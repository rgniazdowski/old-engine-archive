#!/bin/bash

echo "Multiple APK installation - android"

if test "$#" -ne 1; then
    echo "Illegal number of parameters"
	echo "please pass the build: release or debug"
	exit
fi

dirname $0                                                                      
cd `dirname $0`                                                                 
cd ../

for SERIAL in $(adb devices | tail -n +2 | cut -sf 1);
do
  for APKLIST in $(find deployments | grep apk | grep android | grep $1);
  do
  echo "Installing $APKLIST on $SERIAL device"
  export ANDROID_SERIAL=$SERIAL
  adb install -r $APKLIST
  done

done
