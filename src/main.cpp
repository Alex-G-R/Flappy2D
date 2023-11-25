#include <SDL2/SDL.h>
#include <iostream>

const int window_width = 1280;
const int window_height = 720;

int main(int argc, char const *argv[])
{
	// Setup SDL, SDL_Event and window
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);





	// Game loop
	bool running = true;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				running = false;
		}

		// Set background color
		SDL_SetRenderDrawColor(renderer, 25, 24, 23, 255);
		SDL_RenderClear(renderer);
	}

	// Free up the memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}