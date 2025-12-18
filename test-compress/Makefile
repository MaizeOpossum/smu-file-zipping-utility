# -*- Makefile -*-
CXX := g++
CXXFLAGS := -std=c++20
LDLIBS := -lm

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o a $(LDLIBS)
	./a