CC=g++
SDL_CFLAGS=$(shell sdl2-config --cflags)
SDL_LDFLAGS=$(shell sdl2-config --libs)
CFLAGS=-c -std=c++11 -Wall $(SDL_CFLAGS)
OFLAGS=-o -std=c++11 -Wall
SOURCES=src/main.cc
OBJECTS=obj/main.o obj/renderer.o obj/input.o obj/game.o obj/lbxopen.o obj/baseunit.o obj/unit.o obj/rendererror.o obj/button.o obj/xmlreader.o obj/helper.o obj/gameconstants.o

all: directories bin/rjak

directories: bin obj

bin:
	mkdir bin

obj:
	mkdir obj

bin/rjak: $(OBJECTS)
	$(CC) -Wall $(OBJECTS) $(SDL_LDFLAGS) -o bin/rjak

obj/main.o: src/main.cc obj/game.o
	$(CC) $(CFLAGS) src/main.cc -o obj/main.o

obj/renderer.o: src/renderer.cc src/renderer.h src/lbxopen.h src/rendererror.h
	$(CC) $(CFLAGS) src/renderer.cc -o obj/renderer.o

obj/rendererror.o: src/rendererror.cc src/rendererror.h
	$(CC) $(CFLAGS) src/rendererror.cc -o obj/rendererror.o

obj/input.o: src/input.cc src/input.h
	$(CC) $(CFLAGS) src/input.cc -o obj/input.o

obj/game.o: src/game.cc src/game.h src/resources.h obj/renderer.o obj/input.o obj/lbxopen.o obj/xmlreader.o obj/helper.o
	$(CC) $(CFLAGS) src/game.cc -o obj/game.o

obj/lbxopen.o: src/lbxopen.cc src/lbxopen.h
	$(CC) $(CFLAGS) src/lbxopen.cc -o obj/lbxopen.o

obj/baseunit.o: src/baseunit.cc src/baseunit.h
	$(CC) $(CFLAGS) src/baseunit.cc -o obj/baseunit.o

obj/unit.o: src/unit.cc src/unit.h src/baseunit.h src/gameconstants.h
	$(CC) $(CFLAGS) src/unit.cc -o obj/unit.o

obj/button.o: src/button.cc src/button.h
	$(CC) $(CFLAGS) src/button.cc -o obj/button.o

obj/xmlreader.o: src/xmlreader.cc src/xmlreader.h
	$(CC) $(CFLAGS) src/xmlreader.cc -o obj/xmlreader.o

obj/helper.o: src/helper.cc src/helper.h
	$(CC) $(CFLAGS) src/helper.cc -o obj/helper.o

obj/gameconstants.o : src/gameconstants.cc src/gameconstants.h
	$(CC) $(CFLAGS) src/gameconstants.cc -o obj/gameconstants.o

clean:
	rm -rf obj/*.o bin/rjak
