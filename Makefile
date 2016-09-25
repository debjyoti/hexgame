CXX=g++
CXXFLAGS=-std=c++11

hex: *.cpp
	$(CXX) -DDEBUG $(CXXFLAGS) $^ -o $@
