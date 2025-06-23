@echo off

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_setup_logger.bat

call scripts\windows\setup_msvc_env.bat _standalone
if !errorlevel! neq 0 (
    goto exit_error
)

pushd examples\assert

echo !log_info! Copying bpm files... !log_end!
copy ..\..\build\windows\debug\bpm.* . /Y >nul 2>&1
if !errorlevel! neq 0 (
    echo !log_error! Failed to copy bpm files. !log_end!
    popd
    goto exit_error
)

echo !log_info! Building example: assert... !log_end!
echo [TEMP] Current working directory: !cd!
echo [TEMP] Listing contents of ..\..\build\windows\debug:
dir ..\..\build\windows\debug
call cl main.c bpm.lib /I ..\..\include /Fe:assert.exe /nologo /Od /Zi
if !errorlevel! neq 0 (
    echo !log_error! Failed to build assert example. !log_end!
    popd
    goto exit_error
)
echo !log_success! assert example built successfully. !log_end!

if "%1%" equ "run" (
    echo !log_info! Running assert example... !log_end!
    call assert.exe
    if !errorlevel! neq 0 (
        echo !log_error! assert example failed. !log_end!
        goto exit_error
    )
    echo !log_success! assert example ran successfully. !log_end!
)

popd

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
