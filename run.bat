@echo off
REM Check if Node.js and PlatformIO are available
where node >nul 2>&1
if errorlevel 1 (
    echo Node.js is not installed or not in PATH.
    exit /b 1
)

where platformio >nul 2>&1
if errorlevel 1 (
    echo PlatformIO is not installed or not in PATH.
    exit /b 1
)

REM Run Node.js in cache mode
node index.js cache
if errorlevel 1 (
    echo Failed to run node index.js in cache mode. Aborting.
    exit /b 1
)

REM Run Node.js in sender mode
node index.js sender
if errorlevel 1 (
    echo Failed to run node index.js in sender mode. Aborting.
    exit /b 1
)

REM Upload to COM6
platformio run --target upload --upload-port COM6
if errorlevel 1 (
    echo Failed to upload to COM port 4. Aborting.
    exit /b 1
)

REM Run Node.js in receiver mode
node index.js receiver
if errorlevel 1 (
    echo Failed to run node index.js in receiver mode. Aborting.
    exit /b 1
)

REM Upload to COM5
platformio run --target upload --upload-port COM5
if errorlevel 1 (
    echo Failed to upload to COM port 7. Aborting.
    exit /b 1
)

REM Run Node.js in re-cache mode
node index.js re-cache
if errorlevel 1 (
    echo Failed to run node index.js in re-cache mode. Aborting.
    exit /b 1
)

REM All steps completed successfully
echo All steps completed successfully.
cls
exit /b 0