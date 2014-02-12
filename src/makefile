CXX = clang++
SDL = -framework SDL2 -framework SDL2_image
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SDL)
EXE = a.out

all: $(EXE)

$(EXE): main.o sdl-manager.o
	$(CXX) $(LDFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

sdl-manager.o: sdl-manager.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run:
	./$(EXE)

clean:
	rm *.o && rm $(EXE)
