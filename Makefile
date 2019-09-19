gxx := g++
flag := -W -IF:/Github/phy_sim/headers -g
libr := -lopengl32 -lfreeglut -lglu32
object := main.o fpair.o line.o body.o rectangle.o \
polygon.o circle.o coll_inf.o collision.o world.o gra.o const.o

VPATH := src:headers:o

o_dir = o

main.exe : $(object)
	$(gxx) -o main $(o_dir)/*.o $(libr)

main.o : main.cpp
	$(gxx) -c $< $(flag) -o $(o_dir)/$@ 

fpair.o : fpair.cpp
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

line.o : line.cpp fpair.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

body.o : body.cpp fpair.o line.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

rectangle.o : rectangle.cpp body.h 
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

circle.o : circle.cpp body.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

polygon.o : polygon.cpp body.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

coll_inf.o : coll_inf.cpp fpair.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

collision.o : collision.cpp rectangle.h circle.h polygon.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

world.o : world.cpp collision.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

gra.o : gra.cpp world.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@ $(libr)

const.o : const.cpp fpair.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

clean :
	del $(o_dir)\*.o
	del main.exe

run : main.exe
	./main