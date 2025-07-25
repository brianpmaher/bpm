@echo off

::
:: Build bpm.dll for Windows in debug mode
::

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_setup_logger.bat

call scripts\windows\setup_msvc_env.bat _standalone
if !errorlevel! neq 0 (
    goto exit_error
)

if not exist build\windows\debug (
    echo !log_info! Creating build directory... !log_end!
    mkdir build\windows\debug
)

echo !log_info! Building bpm in debug mode... !log_end!
pushd build\windows\debug
call cl ..\..\..\src\*.c /I ..\..\..\include /D DLL_EXPORT /LD /Fe:bpm.dll /std:c11 /options:strict /nologo /Wall /WX /Od /Zi
if !errorlevel! neq 0 (
    echo !log_error! Failed to build bpm. !log_end!
    popd
    goto exit_error
)
popd
echo !log_success! bpm built successfully. !log_end!

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
