@echo off

rem This script should be in 'run' directory, or any other one level deep
set FG_CURDIR=%CD%
cd %~dp0..
echo %CD%
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

rem echo %0
rem echo %1
rem echo %2
rem echo %3

set FG_S3E_SIGN_CFG_FILE=C:\Marmalade\7.4\tools\IPhoneSigner\settings.ast

IF "%FG_IPAFILE%"=="" (
    echo **ERROR** Path to IPA package file not set
    GOTO end
)

rem first argument is "development" or "distribution"
IF "%1"=="development" (
	set FG_SIGN_ID="iPhone Developer"
	echo ** Going to sign IPA file for development
) ELSE (
    set FG_SIGN_ID="iPhone Distribution"
	echo ** Going to sign IPA file for distribution
)

rem second argument is optional
IF "%2"=="" (
	set FG_PROVISION_FILE=""
) ELSE (
	set FG_PROVISION_FILE="%CD%\%2"
)

rem dir "E:\Develop\Game.Dev.Engine\infinium\deployments\default\iphone\release\Infinium.ipa"
rem filename ""
rem host "!"
rem select "iPhone Developer"

echo ** Updating settings for IPhoneSigner
rem @echo on

echo dir "%CD%\%FG_IPAFILE%" > %FG_S3E_SIGN_CFG_FILE%
echo filename %FG_PROVISION_FILE% >> %FG_S3E_SIGN_CFG_FILE%
echo host "!" >> %FG_S3E_SIGN_CFG_FILE%
echo select %FG_SIGN_ID% >> %FG_S3E_SIGN_CFG_FILE%

echo ** Executing preconfigured IPhoneSigner (Marmalade)

C:\Marmalade\7.4\tools\IPhoneSigner\IPhoneSigner.exe

:end

cd %FG_CURDIR%
@echo on