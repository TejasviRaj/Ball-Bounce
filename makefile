ball: main.o HGL_init.o circle.o
	g++ -g -o ball main.o HGL_init.o circle.o -lSDL2

main.o: main.cpp
	g++ -g -c main.cpp

HGL_init.o: HGL_init.cpp HGL.h Color.h
	g++ -g -c HGL_init.cpp

circle.o:circle.cpp HGL.h Color.h
	g++ -g -c circle.cpp
