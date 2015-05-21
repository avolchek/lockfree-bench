git pull origin
cd intel-threading-blocks
make
cd ..
cmake -G "Unix Makefiles" CMakeLists.txt
make
./lockfree_bench