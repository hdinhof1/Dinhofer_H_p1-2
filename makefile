# Specify the target
FLAGS = -Wall -std=c++11

all: program1

# Link one.o and two.o into an executable called

program1:	Driver.o Card.o
	g++ $(FLAGS) Driver.o Card.o -o program1
# g++ std=c++11 <etc>

Driver.o:	driver.cpp
	g++ $(FLAGS) -g -c driver.cpp -o Driver.o

Card.o:	Card.cpp
	g++ $(FLAGS) -g -c Card.cpp -o Card.o

clean:
	rm -f *.o program1

tar:
	tar cvzf Dinhofer_H_p1.tar.gz Dinhofer_H_p1