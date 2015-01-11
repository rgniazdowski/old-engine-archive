@echo off

rem This script should be in 'run' directory, or any other one level deep
set FG_CURDIR=%CD%
cd %~dp0..

echo ****************** FLEXI GAME ************************
echo ** %date% %time%

IF "%S3E_DIR%" == "" (
GOTO sets3edir
) ELSE (
GOTO s3edirpresent
)

:sets3edir
echo ** Refreshing S3E_DIR variable value
set S3E_DIR=C:\Marmalade\7.4\s3e

:s3edirpresent
set FG_BUILDDIR=build_infinium_vc11
set FG_PROJECTNAME=Infinium
set FG_IPAFILENAME_SUBNAME=Infinium
set PYTHON=C:\Marmalade\7.4\python\Python.exe

rem first argument is the name of the config and the subdir
IF "%1"=="" (
	set FG_DEPLOY_CONFIG_NAME=Default
	set FG_DEPLOY_SUBDIR_NAME=default
	set FG_DEPLOY_CONFIG_NAME_PARAM=-v
	set FG_IPAFILENAME_SUBNAME=Infinium
	echo ** Going to create Default deploy package
) ELSE (
    set FG_DEPLOY_CONFIG_NAME=%1
    set FG_DEPLOY_SUBDIR_NAME=%1
    set FG_DEPLOY_CONFIG_NAME_PARAM=-v --config=%1
    set FG_IPAFILENAME_SUBNAME=%1
	echo ** Going to create '%1' deploy package
)

IF "%1"=="default" (
	set FG_DEPLOY_CONFIG_NAME=Default
	set FG_DEPLOY_SUBDIR_NAME=default
	set FG_DEPLOY_CONFIG_NAME_PARAM=-v
	set FG_IPAFILENAME_SUBNAME=Infinium
)

IF "%1"=="Default" (
	set FG_DEPLOY_SUBDIR_NAME=default
	set FG_IPAFILENAME_SUBNAME=Infinium
)

echo ******************************************************
echo ** S3E_DIR is '%S3E_DIR%'
echo ** FG_BUILDDIR is '%FG_BUILDDIR%'
echo ** PYTHON is '%PYTHON%'
echo ** Creating deploy package of %FG_PROJECTNAME% - RELEASE VERSION
echo ** Checking for %FG_PROJECTNAME%.mkb
IF NOT EXIST "%FG_PROJECTNAME%.mkb" (
  echo Missing %FG_PROJECTNAME%.mkb - Marmalade project file
  goto end
)

rem ====================== refresh the deploy config
echo ******************************************************
echo ** Refreshing the %FG_BUILDDIR%\deploy_config.py configuration file
call %S3E_DIR%\bin\mkb.bat --verbose=1 --buildenv=VC11 %FG_PROJECTNAME%.mkb --default-buildenv=vc11 --msvc-project --deploy-only
if errorlevel 1 goto end

rem ====================== Checking for deploy_config.py existence
echo ******************************************************
echo ** Checking for Python deploy config file: %FG_BUILDDIR%\deploy_config.py
IF NOT EXIST "%FG_BUILDDIR%\deploy_config.py" (
  echo **ERROR** Missing %FG_BUILDDIR%\deploy_config.py
  goto end
) ELSE (
  echo ** %FG_BUILDDIR%\deploy_config.py is available
)

rem ===================== create deploy package for IOS Release
echo ******************************************************
echo ** Creating deployment for IOS - RELEASE - %FG_PROJECTNAME% - Config %FG_DEPLOY_CONFIG_NAME%
call %S3E_DIR%\bin\s3e_deploy.bat -n -f %FG_DEPLOY_CONFIG_NAME_PARAM% --os=iphone --release-loader --arch arm --gcc %FG_BUILDDIR%\deploy_config.py
if errorlevel 1 goto end

set FG_RELEASE=release
set FG_RELEASEDIR=deployments\%FG_DEPLOY_SUBDIR_NAME%\iphone\release
set FG_RELEASE_CERTS_DIR=%FG_RELEASEDIR%\certificates
set FG_IPAFILENAME=%FG_IPAFILENAME_SUBNAME%.ipa
set FG_IPAFILE=%FG_RELEASEDIR%\%FG_IPAFILENAME%
set FG_IPAFILEPATH=%FG_IPAFILE%
set FG_CERTS=certs

echo ******************************************************
echo ** Release Deployment folder path: %FG_RELEASEDIR%
echo ** Release Deployment Certificates folder path: %FG_RELEASE_CERTS_DIR%
echo ** Release Deployment iOS package file: %FG_IPAFILE%

IF NOT EXIST "%FG_RELEASEDIR%" (
  echo **ERROR** Missing %FG_RELEASEDIR% directory
  goto end
)

IF NOT EXIST "%FG_CERTS%" (
  echo **ERROR** Missing %FG_CERTS% directory - could not locate main certificates
  goto skipcerts
)

IF NOT EXIST "%FG_RELEASE_CERTS_DIR%" (
  echo **ERROR** Missing %FG_RELEASE_CERTS_DIR% directory, copying from project root
  call xcopy %FG_CERTS% %FG_RELEASE_CERTS_DIR% /F /E /I /Y
  rem goto end
) ELSE (
  echo **INFO** Directory %FG_RELEASE_CERTS_DIR% already exists, overwriting files...
  call xcopy %FG_CERTS% %FG_RELEASE_CERTS_DIR% /F /E /I /Y
)

echo ** Calling resigning tool for iOS package
call tools\resign_run.bat development
if errorlevel 1 goto end

IF "%2" == "--skip-itunes" (
	goto skipitunes
)

echo ** Calling iTunes for package upload
start "C:\Program Files\iTunes\iTunes.exe" "%CD%\%FG_IPAFILE%"

:skipcerts

:skipitunes

:end

cd %FG_CURDIR%
