@echo off

rem This script should be in 'run' directory, or any other one level deep
set FG_CURDIR=%CD%
cd %~dp0..

echo ################## FLEXI GAME ########################
echo ## %date% %time%

set S3E_DIR=C:\Marmalade\7.4\s3e
set FG_BUILDDIR=build_infinium_vc11
set FG_PROJECTNAME=Infinium
set PYTHON=C:\Marmalade\7.4\python\Python.exe

echo ######################################################
echo ## S3E_DIR is '%S3E_DIR%'
echo ## FG_BUILDDIR is '%FG_BUILDDIR%'
echo ## PYTHON is '%PYTHON%'
echo ## Creating deploy package of %FG_PROJECTNAME% - RELEASE VERSION
echo ## Checking for %FG_PROJECTNAME%.mkb
IF NOT EXIST "%FG_PROJECTNAME%.mkb" (
  echo Missing %FG_PROJECTNAME%.mkb - Marmalade project file
  goto end
)

rem ====================== build if available
echo ######################################################
echo ## Checking for Python deploy config file: %FG_BUILDDIR%\deploy_config.py
IF NOT EXIST "%FG_BUILDDIR%\deploy_config.py" (
  echo ##ERROR## Missing %FG_BUILDDIR%\deploy_config.py
  goto end
) ELSE (
  echo ## %FG_BUILDDIR%\deploy_config.py is available
)

rem ===================== create deploy package for IOS Release
echo ######################################################
echo ## Creating deployment for IOS - RELEASE - %FG_PROJECTNAME%
call %S3E_DIR%\bin\s3e_deploy.bat -n -f --os=iphone --arch arm --gcc %FG_BUILDDIR%\deploy_config.py
if errorlevel 1 goto end

set FG_RELEASE=release
set FG_RELEASEDIR=deployments\default\iphone\release
set FG_RELEASE_CERTS_DIR=%FG_RELEASEDIR%\certificates
set FG_IPAFILE=%FG_RELEASEDIR%\%FG_PROJECTNAME%.ipa
set FG_IPAFILENAME=%FG_PROJECTNAME%.ipa
set FG_IPAFILEPATH=%FG_IPAFILE%
set FG_CERTS=certs

echo ######################################################
echo ## Release Deployment folder path: %FG_RELEASEDIR%
echo ## Release Deployment Certificates folder path: %FG_RELEASE_CERTS_DIR%
echo ## Release Deployment iOS package file: %FG_IPAFILE%

IF NOT EXIST "%FG_RELEASEDIR%" (
  echo ##ERROR## Missing %FG_RELEASEDIR% directory
  goto end
)

IF NOT EXIST "%FG_CERTS%" (
  echo ##ERROR## Missing %FG_CERTS% directory - could not locate main certificates
  goto skipcerts
)

IF NOT EXIST "%FG_RELEASE_CERTS_DIR%" (
  echo ##ERROR## Missing %FG_RELEASE_CERTS_DIR% directory, copying from project root
  call xcopy %FG_CERTS% %FG_RELEASE_CERTS_DIR% /F /E /I /Y
  rem goto end
) ELSE (
  echo ##INFO## Directory %FG_RELEASE_CERTS_DIR% already exists, overwriting files...
  call xcopy %FG_CERTS% %FG_RELEASE_CERTS_DIR% /F /E /I /Y
)

:skipcerts

:end

cd %FG_CURDIR%
@echo on
