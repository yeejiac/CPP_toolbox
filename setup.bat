@echo off
REM compile .o file
mingw32-make initParser
mingw32-make logwriter
mingw32-make server
mingw32-make connection 
REM compile to .a(static library)
mingw32-make static_package.a
REM compile main.cpp
mingw32-make main
REM delete .o file
del "%~dp0\bin\*.o"
REM run file
test.exe

