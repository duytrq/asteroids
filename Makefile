all:
	g++ -I src/include -L src/lib -o main main.cpp list.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image