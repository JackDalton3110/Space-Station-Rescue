#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include <SFML\Config.hpp>
#include <string>
#include "Bullet.h"
#include "Player.h"

class Nests
{
public:
	Nests();
	~Nests();

	void update(sf::Vector2f pos, double dt);
	void render(sf::RenderWindow &m_window);
	int spawnSpot;
	sf::Vertex line[2];
protected:

private:
	sf::Vector2f m_position;
	sf::CircleShape defendRad;
	bool shot,attack,time;
	Grid *m_Grid;
	Player *m_player;
	Bullet *m_bullet;
	void spawnNests();
	void Attack(sf::Vector2f pos);
	float dist, dx, dy;
	sf::Clock bulletTime;
	double cumulativeTime;
	float t2 = 0.0f;
	sf::Time deltaTime = sf::seconds(5);
	int count = 0;
	int seconds = 0;
};