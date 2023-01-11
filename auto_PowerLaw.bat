del bin\*.txt 
del demo.jpg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release --target=test_PowerLaw
cd bin
.\test_PowerLaw.exe
cd ..
python standalone_tests\PowerLaw\draw_PowerLaw.py