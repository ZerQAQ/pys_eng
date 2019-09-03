
gxx := g++
flag := -W
libr := -lopengl32 -lfreeglut -lglu32

all: main pys gra

run: all
	./main

main : main.cpp
	$(gxx) main.cpp $(flag) -o main $(libr)

gra : gra.o pys
	$(gxx) gra.cpp $(flag) -c

pys : pys.o
	$(gxx) pys.cpp $(flag) -c