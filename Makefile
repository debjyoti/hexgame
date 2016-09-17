CXX=g++
CXXFLAGS=-std=c++11

hex: *.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@   #automatic variables
