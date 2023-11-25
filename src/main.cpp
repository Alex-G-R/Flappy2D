// Liblaries
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

// Mine files
#include "Flappy.hpp"

const int window_width = 1280;
const int window_height = 720;
const float deltaTime = 0.1;
const float gravity = 1.2f;

int main(int argc, char const *argv[])
{
	// Setup SDL, SDL_Event and window
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);


	Flappy player(150.0f, window_height/2 - 25, 50, 50);
	SDL_Rect playerR = {static_cast<int>(player.posX),
						static_cast<int>(player.posY),
						static_cast<int>(player.width),
						static_cast<int>(player.height)
					};

	std::vector<SDL_Rect> obstacles;

	SDL_Rect top1;
	top1.x = 250;
	top1.y = 0;
	top1.w = 100;
	top1.h = 200;
	obstacles.push_back(top1);

	SDL_Rect bottom1;
    bottom1.x = 250;
    bottom1.y = window_height - 200;
    bottom1.w = 100;
    bottom1.h = 200;
    obstacles.push_back(bottom1);

	// Game loop
	bool running = true;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				running = false;

			if(event.type == SDL_KEYUP)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_SPACE:
						std::cout << "Space bar released" << std::endl;
						player.flap();
						break;
				}
			}
		}

		// Set background color
		SDL_SetRenderDrawColor(renderer, 45, 44, 43, 255);
		SDL_RenderClear(renderer);


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &playerR);

		player.update(deltaTime);
		player.velocityY += gravity;

		playerR = {static_cast<int>(player.posX),
						static_cast<int>(player.posY),
						static_cast<int>(player.width),
						static_cast<int>(player.height)
					};

		for(auto& obstacle : obstacles) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &obstacle);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	// Free up the memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}