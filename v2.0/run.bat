IF NOT EXIST "googletest" (
    git clone https://github.com/google/googletest.git
)
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build --config Release

cd build\Release
Students_App_Tests.exe

pause

cd ..\..

build\Release\Students_App.exe
