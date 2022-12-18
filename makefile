test: make_test_o make_test

make_test_o:
	g++ -c deps/test-lib/test-lib.cpp
	mkdir -p build/test-lib
	mv test-lib.o build/test-lib/
	g++ -c tests/*.cpp
	mv *.o build/
make_test:
	g++ build/*.o build/*/*.o -o test
	rm build/*.o