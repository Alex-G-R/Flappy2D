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

struct Obstacle {
    SDL_Rect rect;
    bool repositioned;
    Obstacle(int x, int y, int w, int h) : rect{x, y, w, h}, repositioned(false) {}
};

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

	std::vector<Obstacle> obstacles;

	Obstacle top1(250, 0, 100, 200);
	Obstacle bottom1(250, window_height - 200, 100, 200);
	obstacles.push_back(top1);
	obstacles.push_back(bottom1);

	Obstacle top2(450, 0, 100, 200);
	Obstacle bottom2(450, window_height - 200, 100, 200);
	obstacles.push_back(top2);
	obstacles.push_back(bottom2);

	Obstacle top3(650, 0, 100, 200);
	Obstacle bottom3(650, window_height - 200, 100, 200);
	obstacles.push_back(top3);
	obstacles.push_back(bottom3);

	Obstacle top4(850, 0, 100, 200);
	Obstacle bottom4(850, window_height - 200, 100, 200);
	obstacles.push_back(top4);
	obstacles.push_back(bottom4);

	Obstacle top5(1050, 0, 100, 200);
	Obstacle bottom5(1050, window_height - 200, 100, 200);
	obstacles.push_back(top5);
	obstacles.push_back(bottom5);

	Obstacle top6(1250, 0, 100, 200);
	Obstacle bottom6(1250, window_height - 200, 100, 200);
	obstacles.push_back(top6);
	obstacles.push_back(bottom6);

	Obstacle top7(1450, 0, 100, 200);
	Obstacle bottom7(1450, window_height - 200, 100, 200);
	obstacles.push_back(top7);
	obstacles.push_back(bottom7);

	Obstacle top8(1650, 0, 100, 200);
	Obstacle bottom8(1650, window_height - 200, 100, 200);
	obstacles.push_back(top8);
	obstacles.push_back(bottom8);

	// Game loop
	bool running = true;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){
				running = false;
			}
			else if(event.type == SDL_KEYUP)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_SPACE:
						player.flap();
						break;
				}
			}
			else if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(event.button.button == SDL_BUTTON_LEFT){
					player.flap();
				}
			}
		}

		// Set background color
		SDL_SetRenderDrawColor(renderer, 45, 44, 43, 255);
		SDL_RenderClear(renderer);

	
		for (auto& obstacle : obstacles) {
		    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		    SDL_RenderFillRect(renderer, &obstacle.rect);


		    obstacle.rect.x -= 1;

		    if (obstacle.rect.x + obstacle.rect.w < 0 && !obstacle.repositioned) {

		        obstacles.erase(obstacles.begin());

		        Obstacle newT(1500, 0, 100, 200);
				Obstacle newB(1500, window_height - 200, 100, 200);
				obstacles.push_back(newT);
				obstacles.push_back(newB);
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &playerR);

		player.update(deltaTime);
		player.velocityY += gravity;

		playerR = {static_cast<int>(player.posX),
						static_cast<int>(player.posY),
						static_cast<int>(player.width),
						static_cast<int>(player.height)
					};

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	// Free up the memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}