LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: Townhou

Townhou: application.o basetile.o cameraview.o graphicsmodule.o main.o Noisegen.o world.o worldgen.o
	$(CXX) application.o basetile.o cameraview.o graphicsmodule.o main.o Noisegen.o world.o worldgen.o -o Townhou $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.hpp
	$(CXX) -c $< -o $@

clean:
	rm *o Townhou
