CXX = g++
CXXFLAGS = -Wall -g

all: fms_test

fms_test: test.cpp Flight/*.cpp Flight/*.hpp
	$(CXX) $(CXXFLAGS) -o fms_test $^

test: fms_test
	./fms_test

clean:
	rm -f fms_test
