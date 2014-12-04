@echo off
echo ============== FLEXI GAME =================
echo %date% %time%

call python.exe deployments\default\iphone\debug\sign_app.py E:\Develop\Game.Dev.Engine\infinium\deployments\default\iphone\debug\Infinium.ipa "iPhone Developer" -f

pause
@echo on