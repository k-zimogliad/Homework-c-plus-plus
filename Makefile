CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

test: main.cpp
	$(CXX) $(CXXFLAGS) -o test main.cpp

clean:
	rm -f test

.PHONY: test clean
