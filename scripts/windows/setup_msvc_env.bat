@echo off

::
:: Setup MSVC environment
::

call "%~dp0_goto_project_root.bat"

call scripts\windows\_setup_logger.bat

if defined _msvc_env_initialized (
    if not "%1"=="_standalone" (
        echo %log_success% MSVC environment already initialized. %log_end%
    )
    goto exit_success
)

echo %log_info% Initializing MSVC environment... %log_end%
call vcvarsall.bat x64 >nul 2>&1
if %errorlevel% neq 0 (
    echo %log_error% MSVC environment setup script not found: %log_end%
    echo %log_error%  - If you have Visual Studio installed, make sure `vcvarsall.bat` is in your PATH. %log_end%
    echo %log_error%  - Otherwise install Visual Studio with C++ components ^(https://visualstudio.microsoft.com/downloads/^) and try again. %log_end%
    goto exit_error
)

if "%1"=="_standalone" (
    echo %log_info% MSVC environment initialized once. %log_end%
    echo %log_warn% Speed up your builds by calling `scripts\windows\setup_msvc_env.bat` in your terminal to setup the MSVC environment for the terminal session. %log_end%
    echo %log_warn% VSCode: Run this script in your terminal, launch `code` from the same terminal session to speed up builds in your editor. %log_end%
) else (
    echo %log_success% MSVC environment initialized in current terminal session. %log_end%
)

set _msvc_env_initialized=1

:exit_success
exit /b 0

:exit_error
exit /b 1
