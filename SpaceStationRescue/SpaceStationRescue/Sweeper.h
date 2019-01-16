#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include "Worker.h"
#include "Grid.h"
#include "Player.h"

enum behaveState {
	WANDER,
	FIND,
	FLEE
};

class Sweeper 
{
public:
	Sweeper(std::vector<Worker*> &m_worker);
	~Sweeper();

	void kinematicSeek(sf::Vector2f workerPos);
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicFlee(sf::Vector2f playerPos);
	void coneVision(std::vector<Worker*> workers);
	void update(sf::Vector2f pos, double dt);
	void render(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	void collision();
	void setBehaveState(sf::Vector2f pos, behaveState S);
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
	float m_velocityF;
	float m_orientation;
	float dist, dx, dy;

	double cumulativeTime;

	sf::Texture sweeperTxt;
	sf::Sprite sweeperSprite;
	sf::CircleShape radius;

	float rotateSweeper(sf::Vector2f vel, float rot);

	std::vector<Worker *>workers;
	Grid *m_Grid;
	int pGridX, pGridY;
};