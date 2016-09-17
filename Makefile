CXX=g++
CXXFLAGS=-std=c++11 -DDEBUG -g

hex: *.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@   #automatic variables
