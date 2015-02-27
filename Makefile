LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
CXXFLAGS += -std=c++11

all: Townhou

release: CXXFLAGS += -O3
release: CCFLAGS += -O3
release: Townhou

Townhou: Application.o Basetile.o CameraView.o GraphicsModule.o Input.o main.o NoiseGenerator.o World.o WorldGenerator.o
	$(CXX) $(CXXFLAGS) Application.o Basetile.o CameraView.o GraphicsModule.o Input.o main.o NoiseGenerator.o World.o WorldGenerator.o -o Townhou $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.o: %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm *o Townhou
