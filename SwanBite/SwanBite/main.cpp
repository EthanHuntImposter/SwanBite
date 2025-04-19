#include <SDL3/SDL.h>
#include <SDL3/SDL_Main.h>

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_VIDEO & SDL_INIT_EVENTS);
	
	SDL_Window* window = SDL_CreateWindow("title", 800, 600, SDL_EVENT_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	return 0;
}