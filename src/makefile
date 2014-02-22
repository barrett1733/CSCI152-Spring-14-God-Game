CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SDL)
SOURCES = main.cpp sdl-manager.cpp sdl-widget.cpp sdl-text-display.cpp sdl-button.cpp sdl-slider.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = a.out

all: $(EXECUTABLE)

$(EXECUTABLE): main.o sdl-manager.o sdl-widget.o sdl-button.o sdl-slider.o sdl-text-display.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) $< -o $@

sdl-manager.o: sdl-manager.cpp sdl-widget.o sdl-button.o sdl-slider.o sdl-text-display.o
	$(CC) $(CFLAGS) $< -o $@

sdl-widget.o: sdl-widget.cpp
	$(CC) $(CFLAGS) $< -o $@

sdl-button.o: sdl-button.cpp
	$(CC) $(CFLAGS) $< -o $@

sdl-slider.o: sdl-slider.cpp
	$(CC) $(CFLAGS) $< -o $@

sdl-text-display.o: sdl-text-display.cpp
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE)

clean:
	rm *.o && rm $(EXECUTABLE)
