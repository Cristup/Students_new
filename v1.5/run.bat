cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build --config Release
cmake --install build --prefix install
cd build\Release
Students_App.exe
pause
