roomba : main.o
	g++ -Wall -g -std=c++11 main.o -o roomba
main.o : main.cpp
	g++ -Wall -g  -std=c++11 main.cpp -c
run : roomba
	./roomba
workspace :
	atom Makefile main.cpp
clean :
	rm *.o roomba
