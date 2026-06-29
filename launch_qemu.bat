@echo off
setlocal enabledelayedexpansion

set "DISTRO_DIR=C:\Users\sethj\ArcadeOS-distro"

if not exist "%DISTRO_DIR%" (
    echo ERROR: Distro directory does not exist: %DISTRO_DIR%
    pause
    exit /b 1
)

:: Find the latest .iso file sorted by modification time
set "LATEST_ISO="
for /f "delims=" %%i in ('dir "%DISTRO_DIR%\*.iso" /b /a-d /o-d 2^>nul') do (
    set "LATEST_ISO=%%i"
    goto :found
)

:found
if "%LATEST_ISO%"=="" (
    echo ERROR: No .iso files found in %DISTRO_DIR%
    pause
    exit /b 1
)

echo Booting latest ISO: %LATEST_ISO%
"C:\Program Files\qemu\qemu-system-x86_64.exe" -m 4096 -accel whpx -cdrom "%DISTRO_DIR%\%LATEST_ISO%" -boot d
