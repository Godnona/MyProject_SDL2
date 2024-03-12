all:
	g++ src/*.cpp -o bin/main.exe -I./SDL2 -I./SDL2/include -I./include -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
run:
	bin/main.exe
