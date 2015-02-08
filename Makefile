all: Townhou

Townhou: main.o basetile.o Noisegen.o
	g++ main.o basetile.o Noisegen.o -o Townhou -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

basetile.o: basetile.cpp
	g++ -c basetile.cpp

Noisegen.o: Noisegen.cpp
	g++ -c Noisegen.cpp

clean:
	rm *o Townhou