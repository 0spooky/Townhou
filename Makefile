LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
CXXFLAGS += -std=c++11

PROJECT := Townhou
OBJECTS := Application.o Basetile.o CameraView.o Input.o GraphicsModule.o main.o NoiseGenerator.o Tilemap.o World.o WorldGenerator.o

all: $(PROJECT)

release: CXXFLAGS += -O3
release: CCFLAGS += -O3
release: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(PROJECT) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.o: %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm *o $(PROJECT)
