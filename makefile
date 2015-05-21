CXXFLAGS = -std=c++0x

OBJECTS = Driver.o Card.o

program1:	$(OBJECTS)
	g++ $(CXXFLAGS) $(OBJECTS) -o $@

Driver.o:	Driver.cpp
Card.o:	Card.h Card.cpp

clean:
	rm -f *.o program1

