@echo off

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_setup_logger.bat

call scripts\windows\setup_msvc_env.bat _standalone
if !errorlevel! neq 0 (
    goto exit_error
)

pushd examples\print_lib_info

echo !log_info! Copying bpm files... !log_end!
del bpm.* >nul 2>&1
copy ..\..\build\windows\debug\bpm.* . >nul 2>&1
if !errorlevel! neq 0 (
    echo !log_error! Failed to copy bpm files. !log_end!
    popd
    goto exit_error
)

echo !log_info! Building example: print_lib_info... !log_end!
call cl main.c bpm.lib /I ..\..\include /Fe:print_lib_info.exe /std:c11 /nologo /Od /Zi
if !errorlevel! neq 0 (
    echo !log_error! Failed to build print_lib_info example. !log_end!
    popd
    goto exit_error
)
echo !log_success! print_lib_info example built successfully. !log_end!

if "%1%" equ "run" (
    echo !log_info! Running print_lib_info example... !log_end!
    call print_lib_info.exe
    if !errorlevel! neq 0 (
        echo !log_error! print_lib_info example failed. !log_end!
        goto exit_error
    )
    echo !log_success! print_lib_info example ran successfully. !log_end!
)

popd

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
