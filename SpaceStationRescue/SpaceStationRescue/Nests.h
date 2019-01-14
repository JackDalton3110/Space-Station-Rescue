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

	void update(sf::Vector2f pos);
	void render(sf::RenderWindow &m_window);
	int spawnSpot;
	sf::Vertex line[2];
protected:

private:
	sf::Vector2f m_position;
	sf::CircleShape defendRad;
	bool shot,attack;
	Grid *m_Grid;
	Player *m_player;
	void spawnNests();
	void Attack(sf::Vector2f pos);
	float dist, dx, dy;
};