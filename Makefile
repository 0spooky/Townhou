LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: Townhou

Townhou: main.o basetile.o Noisegen.o
	$(CXX) main.o basetile.o Noisegen.o -o Townhou $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.hpp
	$(CXX) -c $< -o $@

clean:
	rm *o Townhou