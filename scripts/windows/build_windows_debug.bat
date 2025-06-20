@echo off

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_setup_logger.bat

if not exist build\windows\debug (
    echo !log_info! Creating build directory... !log_end!
    mkdir build\windows\debug
)

echo !log_info! Building application... !log_end!
pushd build\windows\debug
call cl ..\..\..\src\main.c /Fe:app.exe /std:c11 /options:strict /nologo /Wall /WX /Od /Zi
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
