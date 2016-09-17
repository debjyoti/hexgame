CXX=g++
CXXFLAGS=-std=c++11 -DDEBUG

hex: *.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@   #automatic variables
