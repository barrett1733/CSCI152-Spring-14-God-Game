CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -Werror -pedantic -c -std=c++11
LFLAGS = $(SDL)
SDL_SOURCES = sdl-manager.cpp sdl-utility.cpp sdl-widget.cpp sdl-text-display.cpp sdl-button.cpp sdl-slider.cpp sdl-triangle-slider.cpp sdl-entity.cpp sdl-map-view.cpp
EXECUTABLE = a.out

all: $(EXECUTABLE)

$(EXECUTABLE): main.o config.o sdl.a game-manager.o resource-manager.o village-ai.o
	$(CC) $(LFLAGS) $^ -o $@

main.o: main.cpp game-manager.o
	$(CC) $(CFLAGS) $< -o $@

config.o: config.cpp
	$(CC) $(CFLAGS) $< -o $@

game-manager.o: game-manager.cpp
	$(CC) $(CFLAGS) $< -o $@

resource-manager.o: resource-manager.cpp
	$(CC) $(CFLAGS) $< -o $@

village-ai.o: villager-ai.cpp
	$(CC) $(CFLAGS) $< -o $@

sdl.a: $(SDL_SOURCES)
	$(CC) $(CFLAGS) $^
	ar cr sdl.a sdl*.o

astar:
	$(CC) $(CFLAGS) -c test.cpp -o test.o
	$(CC) $(CFLAGS) -c a-star.cpp -o a-star.o
	$(CC) $(LFLAGS) test.o a-star.o -o test.out

run:
	./$(EXECUTABLE)

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f $(EXECUTABLE)
