@echo off

rem This script should be in 'run' directory, or any other one level deep
set FG_CURDIR=%CD%
cd %~dp0..

echo ============== FLEXI GAME =================
echo %date% %time%

set S3E_DIR=C:\Marmalade\7.4\s3e
set BUILDDIR=build_infinium_vc11
set PROJECTNAME=Infinium
set PYTHON=C:\Marmalade\7.4\python\Python.exe

echo S3E_DIR is '%S3E_DIR%'
echo BUILDDIR is '%BUILDDIR%'
echo PYTHON is '%PYTHON%'

echo Building ARM version of %PROJECTNAME% - DEBUG VERSION
echo Checking for %PROJECTNAME%.mkb
IF NOT EXIST "%PROJECTNAME%.mkb" (
  echo Missing %PROJECTNAME%.mkb - Marmalade project file
  goto end
)

rem ===================== build project version debug ARM
echo call %S3E_DIR%\bin\mkb.bat -n --verbose=1 --debug --make --arm --compiler=gcc %PROJECTNAME%.mkb
if errorlevel 1 goto end

rem ====================== build if available
echo %BUILDDIR%\deploy_config.py
IF NOT EXIST "%BUILDDIR%\deploy_config.py" (
  echo Missing %BUILDDIR%\deploy_config.py
  goto end
)

:end

cd %FG_CURDIR%
@echo on
