all:
	g++ -I src/include -L src/lib -o main main.cpp list.cpp window.cpp ship.cpp asteroid.cpp DrawFunc.cpp projectile.cpp inandout.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer