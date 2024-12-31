@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"

for %%a in (%*) do set "%%a=1"

if not "%release%"=="1" set debug=1

if "%debug%"=="1"   set release=0 && echo [debug mode]
if "%release%"=="1" set debug=0 && echo [release mode]

set cl_common=     /I..\src\ /nologo /FC /Z7
set cl_debug=      call cl %cl_common% /Od /Ob1
set cl_release=    call cl %cl_common% /O2 
set cl_out=        /Fe:

set compile_debug=%cl_debug%
set compile_release=%cl_release%
set out=%cl_out%

if "%debug%"=="1"     set compile=%compile_debug%
if "%release%"=="1"   set compile=%compile_release%

if not exist build mkdir build
pushd build

set cpp_files=
for /R ..\src %%f in (*.cpp) do (
    set cpp_files=!cpp_files! "%%f"
)

%compile% !cpp_files! /EHsc %out%project.exe || exit /b 1

popd
