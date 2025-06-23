@echo off

::
:: Clean build directory.
::

setlocal EnableDelayedExpansion

cd /D "%~dp0"..\..\

call scripts\windows\_setup_logger.bat

echo !log_info! Cleaning build directory... !log_end!
call rmdir /s /q build
if !errorlevel! neq 0 (
    echo !log_error! Failed to clean build directory. !log_end!
    goto exit_error
)
echo !log_success! Build directory cleaned successfully. !log_end!

:exit_success
endlocal
exit /b 0

:exit_error
endlocal
exit /b 1
