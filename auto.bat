del bin\*.txt 
del demo.jpg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
cd bin
.\test_nonNewton.exe
cd ..
python draw.py