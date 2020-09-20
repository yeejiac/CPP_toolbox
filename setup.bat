@echo off
REM compile .o file
mingw32-make initParser
mingw32-make logwriter
REM mingw32-make server
mingw32-make connection 
mingw32-make dataQueue 
mingw32-make client 
REM compile to .a(static library)
mingw32-make static_package.a
REM compile main.cpp
mingw32-make main
REM delete .o file
del "%~dp0\bin\*.o"
REM run file
REM test.exe

