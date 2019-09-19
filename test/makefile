
OBJECT := main.o A.o var.o

main.exe : $(OBJECT)
	g++ -o main.exe $(OBJECT)

main.o : main.cpp
	g++ -c -o $@ $<

A.o : A.cpp
	g++ -c -o $@ $<

var.o : var.cpp
	g++ -c -o $@ $<

clean :
	del $(OBJECT)