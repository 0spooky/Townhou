env = Environment()

env.Append(LIBS = ["sfml-graphics","sfml-window","sfml-system"])
env.Append(CPPPATH = "include")

baseSources =  Glob('src/*.cpp')
graphicsSources = Glob('src/graphics/*.cpp')
worldSources = Glob('src/world/*.cpp')
utilSources = Glob('src/util/*.cpp')

env.Append(CCFLAGS = '-std=c++11')
env.Program(target = "bin/Townhou", source = baseSources + graphicsSources + worldSources + utilSources)
