CXX = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -Werror -pedantic -c -std=c++11
LFLAGS = $(SDL)
SRC_DIR = src
SDL_DIR = sdl
OBJ_DIR = obj
EXE_DIR = build
SOURCES = main.cpp config.cpp
SDL_SOURCES = sdl-manager.cpp sdl-utility.cpp sdl-widget.cpp sdl-text-display.cpp sdl-button.cpp sdl-slider.cpp sdl-triangle-slider.cpp sdl-entity.cpp sdl-map-view.cpp
MGR_SOURCES = game-manager.cpp resource-manager.cpp
OBJECTS = main.o config.o village-ai.o sdl.a managers.a
EXECUTABLE = a.out

define compile
@mkdir -p $(OBJ_DIR)
$(CXX) $(CFLAGS) $< -o $(OBJ_DIR)/$@
endef

vpath %.cpp $(SRC_DIR)
vpath %.o $(OBJ_DIR)
VPATH = $(OBJ_DIR)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $^) -o $(EXE_DIR)/$@

main.o: main.cpp
	$(compile)

config.o: config.cpp
	$(compile)

village-ai.o: villager-ai.cpp
	$(compile)

managers.a: $(MGR_SOURCES)
	$(CXX) $(CFLAGS) $^
	ar cr $(OBJ_DIR)/$@ *manager.o
	rm -f *manager.o

sdl.a: $(addprefix $(SDL_DIR)/, $(SDL_SOURCES))
	$(CXX) $(CFLAGS) $^
	ar cr $(OBJ_DIR)/$@ sdl*.o
	rm -f sdl*.o

astar:
	$(CXX) $(CFLAGS) -c test.cpp -o test.o
	$(CXX) $(CFLAGS) -c a-star.cpp -o a-star.o
	$(CXX) $(LFLAGS) test.o a-star.o -o test.out

run:
	cd $(EXE_DIR);./$(EXECUTABLE);cd -

clean:
	rm -f obj/*
	rm -f build/a.out
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f $(EXECUTABLE)
