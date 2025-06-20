@echo off

setlocal EnableDelayedExpansion

cd /D "%~dp0"

call ..\..\scripts\windows\_setup_logger.bat

call copy ..\..\build\windows\debug\* . >nul
if !errorlevel! neq 0 (
    echo !log_error! Failed to copy build files. !log_end!
    goto exit_error
)

echo !log_info! Building example: `assert`... !log_end!
call cl main.c bpm.lib /I ..\..\include /Fe:assert.exe /nologo /Od /Zi
if !errorlevel! neq 0 (
    echo !log_error! Failed to build `assert` example. !log_end!
    goto exit_error
)
echo !log_success! `assert` example built successfully. !log_end!

if "%1%"=="run" (
    echo !log_info! Running `assert` example... !log_end!
    call assert.exe
    if !errorlevel! neq 0 (
        echo !log_error! `assert` example failed. !log_end!
        goto exit_error
    )
    echo !log_success! `assert` example ran successfully. !log_end!
)

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
