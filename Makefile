
gxx := g++
flag := -W -I./
libr := -lopengl32 -lfreeglut -lglu32

all: main pys gra

run: all
	./main

main : main.cpp
	$(gxx) main.cpp $(flag) -o main $(libr)

gra : gra.o pys
	$(gxx) gra.cpp $(flag) -c

pys : pys.h.gch
	$(gxx) pys.h $(flag) -c