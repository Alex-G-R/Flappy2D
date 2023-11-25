// Liblaries
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Mine files
#include "Flappy.hpp"

const int window_width = 1280;
const int window_height = 720;
const float deltaTime = 0.1;
const float gravity = 1.2f;

bool isColliding(const SDL_Rect& player, const SDL_Rect& obstacle) {
    // Check if any of the conditions for non-collision are true
    if (player.x > obstacle.x + obstacle.w ||
        player.x + player.w < obstacle.x ||
        player.y > obstacle.y + obstacle.h ||
        player.y + player.h < obstacle.y) {
        // No collision
        return false;
    } else {
        // Collision
        return true;
    }
}


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

	// Seed for the random number generator
    std::random_device rd;
    std::mt19937 generator(rd());

    // Define the distribution for the range [150, 450]
    std::uniform_int_distribution<int> distribution(100, 350);

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

		// Check for collision with each obstacle
	    for (const auto& obstacle : obstacles) {
	        if (isColliding(player.getBoundingBox(), obstacle.rect)) {
	            // Collision detected, handle it here
	            std::cout << "Collision detected!" << std::endl;
	            running = false;  // For simplicity, exit the game on collision
	            // You can add more specific actions like game over or score decrement here
	        }
	    }

	
		for (auto& obstacle : obstacles) {
		    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		    SDL_RenderFillRect(renderer, &obstacle.rect);


		    obstacle.rect.x -= 1;

		    if (obstacle.rect.x + obstacle.rect.w <= 0 && obstacle.rect.y == 0) {
		    	obstacles.erase(obstacles.begin());
		    	obstacles.erase(obstacles.begin());

		        int tempY = distribution(generator);

		        Obstacle newT(1500, 0, 100, tempY);
				Obstacle newB(1500, window_height - tempY + 130, 100, 720);
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

		SDL_Delay(10);
	}

	// Free up the memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}