@echo off
setlocal

set GCC_PATH=D:\mingw64

set CPPFLAGS=-O2 -std=c++14
set LDFLAGS=-static -lgcc -lpthread

set PATH=%PATH%;%GCC_PATH%\bin;%GCC_PATH%\libexec\gcc\x86_64-w64-mingw32\8.1.0;%GCC_PATH%\x86_64-w64-mingw32\bin

cd %~dp0src\util
g++ -c %CPPFLAGS% -o %~dp0cache\LinkedNode.o LinkedNode.cpp
g++ -c %CPPFLAGS% -o %~dp0cache\LinkedStack.o LinkedStack.cpp
g++ -c %CPPFLAGS% -o %~dp0cache\HashTable.o HashTable.cpp

cd %~dp0src\misc
g++ -c %CPPFLAGS% -o %~dp0cache\StringWrap.o StringWrap.cpp
g++ -c %CPPFLAGS% -o %~dp0cache\TFException.o TFException.cpp

cd %~dp0src
g++ -c %CPPFLAGS% -o %~dp0cache\Operators.o Operators.cpp
g++ -c %CPPFLAGS% -o %~dp0cache\TangentsMathFunc.o TangentsMathFunc.cpp

:: Test target.
set TARGET=test_main

cd %~dp0test\src
g++ %CPPFLAGS% -c -o %~dp0test\cache\%TARGET%.o %TARGET%.cpp -I%~dp0src

cd %~dp0
g++ -o %~dp0test\bin\%TARGET%.exe %~dp0test\cache\%TARGET%.o %~dp0cache\LinkedNode.o %~dp0cache\LinkedStack.o %~dp0cache\HashTable.o %~dp0cache\StringWrap.o %~dp0cache\TFException.o %~dp0cache\Operators.o %~dp0cache\TangentsMathFunc.o %LDFLAGS%
strip -s %~dp0test\bin\%TARGET%.exe

endlocal
pause
