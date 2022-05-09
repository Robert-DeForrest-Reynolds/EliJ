@echo off
if not exist "%~dp0bin\gcc.exe" goto epicfail
if "%X_DISTRO%" == "nuwen" goto :eof
set X_DISTRO=nuwen
if exist "%~dp0git\cmd\git.exe" set PATH=%~dp0git\cmd;%PATH%
set PATH=%~dp0bin;%PATH%
set X_MEOW=%~dp0include;%~dp0include\freetype2
if defined C_INCLUDE_PATH (set C_INCLUDE_PATH=%X_MEOW%;%C_INCLUDE_PATH%) else (set C_INCLUDE_PATH=%X_MEOW%)
if defined CPLUS_INCLUDE_PATH (set CPLUS_INCLUDE_PATH=%X_MEOW%;%CPLUS_INCLUDE_PATH%) else (set CPLUS_INCLUDE_PATH=%X_MEOW%)
set X_MEOW=
if not defined GREP_COLORS (set GREP_COLORS=mt=01;32:fn=36:ln=33:bn=31:se=35)
doskey grep=grep --color=auto $*
goto :eof

:epicfail
color 4f
echo ERROR: You must run %~nx0 from the root of the distro.
echo        Don't copy or move this batch file.
title ERROR
goto :eof
