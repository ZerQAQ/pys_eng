gxx := g++
flag := -W -Iheaders -g
libr := -lopengl32 -lfreeglut -lglu32
object := main.o fpair.o body.o shape.o \
coll_inf.o collision.o world.o const.o render.o

VPATH := src:headers:o
o_dir = o

main.exe : $(object)
	$(gxx) -o main $(o_dir)/*.o $(libr)

main.o : main.cpp
	$(gxx) -c $< $(flag) -o $(o_dir)/$@ 

fpair.o : fpair.cpp
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

body.o : body.cpp fpair.h shape.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

shape.o : shape.cpp body.h fpair.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

coll_inf.o : coll_inf.cpp body.h shape.h collision.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

collision.o : collision.cpp body.h shape.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

world.o : world.cpp collision.h coll_inf.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

const.o : const.cpp fpair.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

render.o : render.cpp shape.h body.h
	$(gxx) -c $< $(flag) -o $(o_dir)/$@

clean :
	del $(o_dir)\*.o
	del main.exe

run : main.exe
	./main