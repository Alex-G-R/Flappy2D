#include "Flappy.hpp"

Flappy::Flappy(float p_x, float p_y, float p_w, float p_h)
:posX(p_x), posY(p_y), width(p_w), height(p_h){ velocityX = 0.0f; velocityY = 0.0f; };

void Flappy::flap(){
	velocityY = -35.0f;
}

void Flappy::update(float deltaTime){
	// Update the position based on velocity
	posX += velocityX * deltaTime;
	posY += velocityY * deltaTime;
}

SDL_Rect Flappy::getBoundingBox() {
    return {static_cast<int>(posX),
     		static_cast<int>(posY),
            static_cast<int>(width),
            static_cast<int>(height)};
}