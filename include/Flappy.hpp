#pragma once

class Flappy
{
public:
	float posX, posY;
	float velocityX, velocityY;
	int width, height;

	Flappy(float p_x, float p_y, float p_w, float p_h);

	void flap();
	void update(float deltaTime);
};