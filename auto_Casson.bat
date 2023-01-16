del bin\*.txt 
del demo.jpg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=e:/codes/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release --target=test_Casson
cd bin
.\test_Casson.exe
cd ..
python scripts\draw_Casson.py