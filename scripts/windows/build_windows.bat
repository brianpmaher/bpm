@echo off

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_log.bat

if not exist build (
    echo !log_info! Build directory does not exist, creating it... !log_end!
    mkdir build
)

echo !log_info! Building application... !log_end!
pushd build
call cl ..\src\main.c /options:strict /nologo /Fe:app.exe /Wall /WX
if !errorlevel! neq 0 (
    echo !log_error! Failed to build application !log_end!
    popd
    goto exit_error
)
popd
echo !log_success! Application built successfully !log_end!

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
