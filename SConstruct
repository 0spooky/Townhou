env = Environment()

env.Append(LIBS = ["sfml-graphics","sfml-window","sfml-system"])
env.Append(CPPPATH = "include")

graphicsSources = Glob('src/graphics/*.cpp')
baseSources =  Glob('src/*.cpp')

env.Append(CCFLAGS = '-std=c++11')
env.Program(target = "bin/Townhou", source = graphicsSources + baseSources)
