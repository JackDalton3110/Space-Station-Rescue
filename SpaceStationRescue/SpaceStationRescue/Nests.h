#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include <SFML\Config.hpp>
#include <string>
#include "Bullet.h"
#include "Player.h"
#include "HealthSystem.h"

//enum State
//{
//	PLAYER,
//	ENEMY
//
//};

class Nests
{
public:
	Nests();
	~Nests();

	void update(sf::Vector2f pos);
	void render(sf::RenderWindow &m_window);
	int spawnSpot;
	sf::Vertex line[2];
	//State m_currentState = PLAYER;
protected:

private:
	sf::Vector2f m_position;
	sf::CircleShape defendRad;
	bool shot,attack;
	Grid *m_Grid;
	HealthSystem *m_healthSystem;
	void spawnNests();
	void Attack(sf::Vector2f pos);
	float dist, dx, dy;
};