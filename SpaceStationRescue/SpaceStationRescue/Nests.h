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

protected:

private:
	sf::Vector2f m_position;
	sf::CircleShape defendRad;
	bool shot;
	Grid *m_Grid;
	Player *m_player;
	void spawnNests();
	void Attack();
	float dist, dx, dy;
};