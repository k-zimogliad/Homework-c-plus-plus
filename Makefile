CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: test

test: SparseVector.cpp
	$(CXX) $(CXXFLAGS) -o test SparseVector.cpp

clean:
	rm -f test

.PHONY: all clean
