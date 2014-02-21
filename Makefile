all:	main

main.o:
	g++ -g -c main.cpp

main:   main.o
	g++ -g main.o -o main

clean: 
	rm main.o main
