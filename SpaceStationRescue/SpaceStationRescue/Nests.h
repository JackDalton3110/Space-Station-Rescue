#pragma once
#include <iostream>
#include <vector>
#include <SFML\Config.hpp>
#include <string>
#include "Player.h"

//enum State
//{
//	PLAYER,
//	ENEMY
//
//};

class Nests
{
public:
	Nests(int m_spawnSpot, Grid &m_grid);
	~Nests();

	void update(Player & m_player, double dt);
	void render(sf::RenderWindow &m_window);
	void collision(Player & m_player);
	void spawnNests();
	sf::Vector2f getPosition();
	int spawnSpot;

	sf::Vertex line[2];
	//State m_currentState = PLAYER;
	HealthSystem *m_healthSystem;
	int m_gridX;
	int m_gridY;
	Bullet *m_bullet;
	sf::Vector2f m_position;

private:
	
	std::vector<int> usedSpawns;
	sf::CircleShape defendRad;
	bool shot,attack,time;
	Grid *m_Grid;

	
	void Attack(sf::Vector2f pos);
	float dist, dx, dy;
	sf::Clock bulletTime;
	double cumulativeTime;
	float t2 = 0.0f;
	sf::Time deltaTime = sf::seconds(5);
	int count = 0;
	int seconds = 0;
};