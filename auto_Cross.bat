del bin\*.txt 
del demo.jpg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release --target=test_Cross
cd bin
.\test_Cross.exe
cd ..
python scripts\draw_Cross.py