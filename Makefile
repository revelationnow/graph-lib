all:	main

node.o:
	g++ -g -c node.cpp

link.o:
	g++ -g -c link.cpp

graph.o:
	g++ -g -c graph.cpp

main.o:
	g++ -g -c main.cpp

main:   node.o link.o graph.o main.o
	g++ -g main.o node.o link.o graph.o -o main

clean: 
	rm main.o node.o link.o graph.o main
