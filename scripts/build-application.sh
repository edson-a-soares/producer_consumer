mkdir cmake-build
cd cmake-build
cmake .. -DENABLE_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cd ..
cmake --build cmake-build
