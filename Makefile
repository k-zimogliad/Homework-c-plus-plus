CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
GTEST_LIB = -lgtest -lgtest_main -lpthread

test: test.cpp SparseVector.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp SparseVector.cpp $(GTEST_LIB)

run: test
	./test

clean:
	rm -f test

.PHONY: run clean
