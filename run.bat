@echo off

DEL /S /Q "build"
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && mingw32-make -C build

if %ERRORLEVEL% == 0 goto :next
	echo "ERROR: Failed to compile and build the application"

:next
	build\src\kivvss01.exe %1 %2 %3