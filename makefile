CXX = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -Werror -pedantic -c -std=c++11
LFLAGS = $(SDL)
SRC_DIR = src
SDL_DIR = sdl
OBJ_DIR = obj
BIN_DIR = bin
SOURCES = main.cpp config.cpp
SDL_SOURCES = sdl-manager.cpp sdl-utility.cpp sdl-widget.cpp sdl-text-display.cpp sdl-button.cpp sdl-slider.cpp sdl-triangle-slider.cpp sdl-entity.cpp sdl-map-view.cpp
MGR_SOURCES = game-manager.cpp resource-manager.cpp entity-manager.cpp
OBJECTS = main.o config.o village-ai.o managers.a sdl.a world-gen.o entity.o
EXECUTABLE = a.out

define compile
@mkdir -p $(OBJ_DIR)
$(CXX) $(CFLAGS) $< -o $@
endef

#vpath %.cpp $(SRC_DIR)
#vpath %.o $(OBJ_DIR)
#vpath %.a $(OBJ_DIR)
#vpath % $(OBJ_DIR)
#VPATH = $(SRC_DIR):$(OBJ_DIR)

all: $(EXECUTABLE)
	@echo "\033[33mDone\033[m"

$(EXECUTABLE): $(addprefix $(OBJ_DIR)/, $(OBJECTS))
	$(CXX) $(LFLAGS) $(addprefix , $^) -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(compile)

$(OBJ_DIR)/village-ai.o: $(SRC_DIR)/villager-ai.cpp
	$(compile)

$(OBJ_DIR)/managers.a: $(addprefix $(SRC_DIR)/, $(MGR_SOURCES))
	$(CXX) $(CFLAGS) $^
	ar cr $@ *manager.o
	rm -f *manager.o

$(OBJ_DIR)/sdl.a: $(addprefix $(SRC_DIR)/$(SDL_DIR)/, $(SDL_SOURCES))
	$(CXX) $(CFLAGS) $^
	ar cr $@ sdl*.o
	rm -f sdl*.o

astar:
	$(CXX) $(CFLAGS) -c test.cpp -o test.o
	$(CXX) $(CFLAGS) -c a-star.cpp -o a-star.o
	$(CXX) $(LFLAGS) test.o a-star.o -o test.out

run:
	cd $(BIN_DIR);./$(EXECUTABLE);cd -

clean:
	rm -f $(OBJ_DIR)/*
	rm -f $(BIN_DIR)/a.out
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f $(EXECUTABLE)
