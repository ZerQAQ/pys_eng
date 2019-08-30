
gxx := g++
flag := -W
libr := -lopengl32 -lfreeglut -lglu32
name := main

all: $(name)

run: all
	./$(name)

main : $(name).cpp phy.cpp
	$(gxx) $(name).cpp $(flag) -o $(name) $(libr)
	$(gxx) phy.cpp $(flag) -c

phy : phy.o
	$(gxx) phy.cpp $(flag) -c