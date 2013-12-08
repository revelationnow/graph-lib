all:	main

node.o:
	g++ -c node.cpp

link.o:
	g++ -c link.cpp

graph.o:
	g++ -c graph.cpp

main.o:
	g++ -c main.cpp

main:   node.o link.o graph.o main.o
	g++ main.o node.o link.o graph.o -o main

clean: 
	rm main.o node.o link.o graph.o main
