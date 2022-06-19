// TODO: IMPLEMENT ACTUALLY GENERATING THE PASSWORD

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#define CONSOLE_IMPLEMENTATION
#include "include/console.h"

#include "include/closeIcon.bmp.h"
#include "include/pswrdc.bmp.h"
#include "include/genPassword.bmp.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 485

int main(int argc, char **argv) {
	(void) argc; (void) argv;
	
	SDL_Window*  window 		= NULL;
	SDL_Surface* screensurface 	= NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		console(RED);
		printf("[Error] ");
		console(RESET);
		printf("SDL Could not be initialized! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("PSWRDC - A password manager made in c",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);

	if (window == NULL) {
		console(RED);
		printf("[Error] ");
		console(RESET);
		printf("SDL Window Could not be Created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	screensurface = SDL_GetWindowSurface(window);

	SDL_FillRect( screensurface, NULL, SDL_MapRGB(screensurface->format, 0x24, 0x24, 0x1f));
	SDL_UpdateWindowSurface(window);

	SDL_Rect br; br.x = 0; br.y = 0; br.w = 640; br.h = 25;	
	SDL_FillRect( screensurface, &br, SDL_MapRGB(screensurface->format, 0xd6, 0x45, 0x7c));
	SDL_UpdateWindowSurface(window);

	SDL_Rect r; r.x = SCREEN_WIDTH/2-140; r.y = SCREEN_HEIGHT/2-25; r.w = 280; r.h = 50;	
	SDL_FillRect( screensurface, &r, SDL_MapRGB(screensurface->format, 0xd6, 0x45, 0x7c));
	SDL_UpdateWindowSurface(window);

	SDL_RWops *z = SDL_RWFromMem(closeIcon,closeIconSize);
	SDL_Surface *closeicon = SDL_LoadBMP_RW(z,1);
	SDL_Rect closeiconRect; closeiconRect.x = 615; closeiconRect.y = 0; closeiconRect.w = 25; closeiconRect.h = 25;

	SDL_BlitSurface(closeicon, NULL, screensurface, &closeiconRect);

	SDL_RWops *ztitletext = SDL_RWFromMem(pswrdc,pswrdcSize);
	SDL_Surface *titletext = SDL_LoadBMP_RW(ztitletext,1);
	SDL_Rect titletextRect; titletextRect.x = 10; titletextRect.y = 2;

	SDL_BlitSurface(titletext, NULL, screensurface, &titletextRect);

	SDL_RWops *zgenpswd = SDL_RWFromMem(genPassword,genPasswordSize);
	SDL_Surface *genpswd = SDL_LoadBMP_RW(zgenpswd,1);
	SDL_Rect genpswdRect; genpswdRect.x = SCREEN_WIDTH/2-95; genpswdRect.y = SCREEN_HEIGHT/2-(int)35/2; genpswdRect.w = 180; genpswdRect.h = 35; 

	SDL_BlitSurface(genpswd, NULL, screensurface, &genpswdRect);


	int quit = 0;
	while (!quit) {
		SDL_Event event;
		if (SDL_WaitEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT: {
					quit = 1;
				} break;
				case SDL_WINDOWEVENT: {
					SDL_UpdateWindowSurface(window);
				} break;
				case SDL_MOUSEBUTTONDOWN: {
					if (event.button.button == SDL_BUTTON_LEFT) {
						printf("x: %i | y: %i\n",event.button.x, event.button.y);
						fflush(stdout);
						if (event.button.x > r.x && event.button.x < r.x+r.w && event.button.y > r.y && event.button.y < r.y+r.h) {
							printf("HIT!\n");
							fflush(stdout);
						}

						if (event.button.x > closeiconRect.x && event.button.x < closeiconRect.x+br.w && event.button.y > closeiconRect.y && event.button.y < closeiconRect.y+br.h) {
							quit=1;
						}
					}
				}
			}
		}
	}

	SDL_FreeSurface(closeicon); SDL_FreeSurface(titletext); SDL_FreeSurface(genpswd); SDL_FreeSurface(screensurface);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
