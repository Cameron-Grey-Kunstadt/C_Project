@echo off

gcc  ..\code\win32_platform.c C:\mingw64\x86_64-w64-mingw32\lib\libuser32.a C:\mingw64\x86_64-w64-mingw32\lib\libgdi32.a -o win32_platform

popd