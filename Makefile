CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
GTEST_LIB = -lgtest -lgtest_main -lpthread

test_heap: test_heap.cpp
	$(CXX) $(CXXFLAGS) -o test_heap test_heap.cpp $(GTEST_LIB)

run: test_heap
	./test_heap

clean:
	rm -f test_heap

.PHONY: run clean
