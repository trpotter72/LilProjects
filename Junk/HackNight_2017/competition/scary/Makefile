scary : main.o
	g++ -Wall -g -std=c++11 main.o -o scary
main.o : main.cpp
	g++ -Wall -g  -std=c++11 main.cpp -c
run : scary
	./scary
workspace :
	atom Makefile main.cpp
clean :
	rm *.o scary
