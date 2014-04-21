CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -Werror -pedantic -c -std=c++11
LFLAGS = $(SDL)
SDL_SOURCES = sdl-manager.cpp sdl-utility.cpp sdl-widget.cpp sdl-text-display.cpp sdl-button.cpp sdl-slider.cpp sdl-triangle-slider.cpp sdl-entity.cpp sdl-map-view.cpp
MGR_SOURCES = game-manager.cpp resource-manager.cpp entity-manager.cpp
OBJECTS = main.o config.o village-ai.o sdl.a managers.a entity.o
EXECUTABLE = a.out

define compile
$(CXX) $(CFLAGS) $< -o $@
endef

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

main.o: main.cpp
	$(compile)

config.o: config.cpp
	$(compile)

entity.o: entity.cpp
	$(compile)

village-ai.o: villager-ai.cpp
	$(compile)

managers.a: $(MGR_SOURCES)
	$(CC) $(CFLAGS) $^
	ar cr $@ *manager.o
	rm -f *manager.o

sdl.a: $(addprefix sdl/, $(SDL_SOURCES))
	$(CC) $(CFLAGS) $^
	ar cr sdl.a sdl*.o
	rm -f sdl*.o



astar:
	$(CC) $(CFLAGS) -c test.cpp -o test.o
	$(CC) $(CFLAGS) -c a-star.cpp -o a-star.o
	$(CC) $(LFLAGS) test.o a-star.o -o test.out

run:
	cd ..;./src/$(EXECUTABLE); cd -

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f $(EXECUTABLE)
