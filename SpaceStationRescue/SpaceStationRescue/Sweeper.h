#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include "Worker.h"
#include "Grid.h"

enum behaveState {
	WANDER,
	FIND,
	FLEE
};

class Sweeper 
{
public:
	Sweeper();
	~Sweeper();

	void update(double dt);
	void render(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	void collision();
	void setBehaveState(behaveState S);
	behaveState getCurrentState();
	behaveState currentState = WANDER;

protected:


private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_heading;

	float maxSpeed;
	float rotation;
	float maxRotation;
	float speed;

	double cumulativeTime;

	sf::Texture sweeperTxt;
	sf::Sprite sweeperSprite;

	float rotateSweeper(sf::Vector2f vel, float rot);

	Grid *m_Grid;
	int pGridX, pGridY;
};