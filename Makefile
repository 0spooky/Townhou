LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: Townhou

Townhou: Application.o Basetile.o CameraView.o GraphicsModule.o main.o NoiseGenerator.o World.o WorldGenerator.o
	$(CXX) Application.o Basetile.o CameraView.o GraphicsModule.o main.o NoiseGenerator.o World.o WorldGenerator.o -o Townhou $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.hpp
	$(CXX) -c $< -o $@

clean:
	rm *o Townhou
