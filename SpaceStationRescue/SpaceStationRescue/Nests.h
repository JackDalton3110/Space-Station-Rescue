#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include <SFML\Config.hpp>
#include <string>

class Nests
{
public:
	Nests();
	~Nests();

	void update();
	void render(sf::RenderWindow &m_window);

protected:

private:
	sf::Vector2f m_position;
	sf::CircleShape defendRad;
	bool shot;
	Grid *m_Grid;
	void spawnNests();

};