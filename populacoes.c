#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#define WIDTH 1000
#define HEIGHT 600
#define BPP 4
#define DEPTH 32

#define N_DE_INDIVIDUOS 1000
#define N_DE_ESPECIES 2
#define ROUNDS 1000000000
#define PERIODO_MEDIA 1
#define RESOLUCAO 10000

struct individuo{
        float tipo;
        float pontos;
        int memoria;
};

void setpixel(SDL_Surface * screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if(x > WIDTH - 1 || x < 0 || y > HEIGHT - 1 || y < 0)
		return; 
	Uint32 *pixmem32;
	Uint32 colour;
	colour = SDL_MapRGB(screen->format, r, g, b);
	pixmem32 = (Uint32 *) screen->pixels + WIDTH * y + x;
	*pixmem32 = colour;
}

int main(void){
        int i, j, k, ind1, ind2, tipo1, tipo2, melhor = 0, pior = 0, vezes = 0;
        float media;
        srand(time(0));
        SDL_Surface *screen;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {
		SDL_Quit();
		return 1;
	}
        struct individuo * especimes = (struct individuo *) malloc(sizeof(struct individuo ) * N_DE_INDIVIDUOS);
        for(i = 0; i < N_DE_INDIVIDUOS; i++){
                especimes[i].tipo =  i / (float)N_DE_INDIVIDUOS ;
                especimes[i].pontos = 0;
        }
        for(i = 0; i < ROUNDS; i++){
                for(j = 0; j < 1; j++){
                        ind1 = rand() % N_DE_INDIVIDUOS;
                        ind2 = rand() % N_DE_INDIVIDUOS;
                        if(especimes[ind1].tipo < rand() % 100000 / 100000.0 * 0.5){
                                tipo1 = 0;
                        }else{
                                tipo1 = 1;
                        }
                        if(especimes[ind2].tipo < rand() % 100000 / 100000.0 * 0.5){
                                tipo2 = 0;
                        }else{
                                tipo2 = 1;
                        }
                        switch(tipo1 + tipo2){
                                case 0:
                                        if(rand() % 2){
                                                especimes[ind1].pontos += 10;
                                                especimes[ind2].pontos -= 10;
                                        }else{
                                                especimes[ind1].pontos -= 10;
                                                especimes[ind2].pontos += 10;
                                        }         
                                        break;               
                                case 1:
                                        if(especimes[ind1].tipo == 0){
                                                especimes[ind1].pontos -= 0;
                                                especimes[ind2].pontos += 30;
                                        }else{
                                                especimes[ind1].pontos += 30;
                                                especimes[ind2].pontos -= 0;
                                        }
                                        break;
                                case 2:
                                        if(rand() % 2){
                                                especimes[ind1].pontos -= 60;
                                                especimes[ind2].pontos += 40;
                                        }else{
                                                especimes[ind1].pontos += 40;
                                                especimes[ind2].pontos -= 60;
                                        }         
                                        break;     
                        }
                }
                ind1 = 0;
                ind2 = 0;
                for(j = 0; j < N_DE_INDIVIDUOS; j++){
                        if(especimes[j].pontos < especimes[pior].pontos) pior = j;
                        else if(especimes[j].pontos > especimes[melhor].pontos) melhor = j;    
                        especimes[j].pontos = 0;
                }
                if(i % RESOLUCAO == 0){
                        for(j = 0; j < N_DE_INDIVIDUOS; j++){
                                media += especimes[j].tipo;
                                filledCircleRGBA(screen, (i / RESOLUCAO) % WIDTH, (especimes[j].tipo / 2.0 + 0.25) * HEIGHT, 0.1, 255, 255, 255, 10);
                        }
                        media = media / N_DE_INDIVIDUOS;
                        printf("%f\n", media);
                        setpixel(screen,  (i / RESOLUCAO) % WIDTH, ( media / 2.0 + 0.25) * HEIGHT, 0, 255, 0);
                        SDL_Flip(screen);
                }
                if(rand() % 10000 < 9980){
                        especimes[pior].tipo = especimes[melhor].tipo + (rand() % 100000) / 100000000.0 - 0.0005 ;
                }else{
                        especimes[pior].tipo = (rand() % 1000000) / 1000000.0;
                }
 
                //printf("%f, %f\n", media / N_DE_INDIVIDUOS, ind1/(float)ind2);
                media = 0;
        }
        
        return(0);
}
