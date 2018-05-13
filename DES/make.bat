cls
g++ .\DES.cpp -c
g++ .\Analysis.cpp -c
g++ .\Application.cpp -c
g++ .\main.cpp -c
g++ .\main.o .\Application.o .\Analysis.o .\DES.o -o Application
