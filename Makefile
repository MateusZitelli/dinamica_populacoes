all:
	gcc populacoes.c -o pop.bin -O3 `sdl-config --cflags` `sdl-config --libs` -lSDL_gfx -g
