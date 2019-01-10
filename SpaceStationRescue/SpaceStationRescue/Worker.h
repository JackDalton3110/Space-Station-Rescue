#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include <SFML\Config.hpp>
#include <string>


class Worker
{
public:
	Worker();
	~Worker();

	void update();
	void render(sf::RenderWindow &window);
	float getRandom(int x, int y);
	void respawn(float x, float y);
	int count = 0;

protected:

private:
	sf::Vector2f velocity;
	sf::Vector2f m_position;
	float radius;
	float speed;
	float maxSpeed;
	float rotation;
	float maxRotation;
	sf::CircleShape enemy;
	sf::Texture workerTxt;
	sf::Sprite workerSprite;
	int rotateWorker(sf::Vector2f vel, int rotate);
};