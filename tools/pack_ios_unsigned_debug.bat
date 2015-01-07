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
set PYTHON=C:\Marmalade\7.4\python\Python.exe

echo ******************************************************
echo ** S3E_DIR is '%S3E_DIR%'
echo ** FG_BUILDDIR is '%FG_BUILDDIR%'
echo ** PYTHON is '%PYTHON%'
echo ** Creating deploy package of %FG_PROJECTNAME% - DEBUG VERSION
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

rem ===================== create deploy package for IOS DEBUG
echo ******************************************************
echo ** Creating deployment for IOS - DEBUG - %FG_PROJECTNAME%
call %S3E_DIR%\bin\s3e_deploy.bat -n -f --os=iphone --debug --arch arm --gcc %FG_BUILDDIR%\deploy_config.py
if errorlevel 1 goto end

set FG_DEBUG=debug
set FG_DEBUGDIR=deployments\default\iphone\debug
set FG_DEBUG_CERTS_DIR=%FG_DEBUGDIR%\certificates
set FG_IPAFILE=%FG_DEBUGDIR%\%FG_PROJECTNAME%.ipa
set FG_IPAFILENAME=%FG_PROJECTNAME%.ipa
set FG_IPAFILEPATH=%FG_IPAFILE%
set FG_CERTS=certs

echo ******************************************************
echo ** Debug Deployment folder path: %FG_DEBUGDIR%
echo ** Debug Deployment Certificates folder path: %FG_DEBUG_CERTS_DIR%
echo ** Debug Deployment iOS package file: %FG_IPAFILE%

IF NOT EXIST "%FG_DEBUGDIR%" (
  echo **ERROR** Missing %FG_DEBUGDIR% directory
  goto end
)

IF NOT EXIST "%FG_CERTS%" (
  echo **ERROR** Missing %FG_CERTS% directory - could not locate main certificates
  goto skipcerts
)

IF NOT EXIST "%FG_DEBUG_CERTS_DIR%" (
  echo **ERROR** Missing %FG_DEBUG_CERTS_DIR% directory, copying from project root
  call xcopy %FG_CERTS% %FG_DEBUG_CERTS_DIR% /F /E /I /Y
  rem goto end
) ELSE (
  echo **INFO** Directory %FG_DEBUG_CERTS_DIR% already exists, overwriting files...
  call xcopy %FG_CERTS% %FG_DEBUG_CERTS_DIR% /F /E /I /Y
)

echo ** Calling resigning tool for iOS package
rem call tools\resign_run.bat development provisions\iOS_Distribution_FG_Infinium.mobileprovision
call tools\resign_run.bat development
if errorlevel 1 goto end
cd %~dp0..

echo ** Calling iTunes for package upload
start "C:\Program Files\iTunes\iTunes.exe" "%CD%\%FG_IPAFILE%"

:skipcerts

:end

cd %FG_CURDIR%
