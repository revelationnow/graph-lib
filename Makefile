all:	main

main.o:
	g++ -g -c main.cpp -std=c++11

main:   main.o
	g++ -g main.o -o main -std=c++11

clean: 
	rm main.o main
