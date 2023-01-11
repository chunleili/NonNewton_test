del bin\*.txt 
del demo.jpg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release --target=test_Casson
cd bin
.\test_Casson.exe
cd ..
python standalone_tests\Casson\draw_Casson.py