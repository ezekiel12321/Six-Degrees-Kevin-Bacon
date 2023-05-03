CXX = g++
CXXFLAGS = -Wall -g

OBJECTS = sixdegrees.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees sixdegrees.o

sixdegrees.o: sixdegrees.cpp sixdegrees.h
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp

clean:
	rm -f *.o
	rm sixdegrees