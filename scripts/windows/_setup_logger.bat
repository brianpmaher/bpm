::
:: Internal: Setup logger
::

@echo off

if defined _logger_initialized (
	goto :exit_success
)

for /F %%a in ('echo prompt $E ^| cmd') do (
	set "esc=%%a"
)
set "red=%esc%[31m"
set "green=%esc%[32m"
set "yellow=%esc%[33m"
set "blue=%esc%[34m"
set "magenta=%esc%[35m"
set "cyan=%esc%[36m"
set "white=%esc%[37m"
set "reset=%esc%[0m"

set "log_info=%white%[INFO]"
set "log_warn=%yellow%[WARNING]"
set "log_error=%red%[ERROR]"
set "log_success=%green%[SUCCESS]"
set "log_end=%reset%"

set _logger_initialized=1

echo %log_info% Logger initialized %log_end%

:exit_success
exit /b 0
