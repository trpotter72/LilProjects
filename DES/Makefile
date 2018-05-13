
HEADERS = Application.h Analysis.h DES.h Bitset-Help.h Bitset-Help.hpp

Application: main.o Application.o Analysis.o DES.o
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ $< -c

clean:
	rm *.o Application
