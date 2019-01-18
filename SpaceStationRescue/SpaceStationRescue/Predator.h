#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <math.h>
#include "Grid.h"
#include "HealthSystem.h"
#include "Player.h"
#include "Nests.h"

class Predator
{
public:
	Predator(float x, float y, Grid &m_Grid);
	~Predator();

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void speedUp();
	void speedDown();
	void increaseRotation();
	void decreaseRotation();
	void shoot();
	void respawn(std::vector<Nests*> &nests);
	void update(Player &m_player, std::vector<Nests*> &nests, double dt);
	void render(sf::RenderWindow &window);
	void collision();
	void collisionPlayer(Player & m_player);
	void respawn();

	float getRotation();


	int bulletindex = 0;
	bool fired = false;
	HealthSystem *m_healthSystem;
	Bullet* m_bullet;
	int spawnSpot;

private:
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_headingBullet;
	float m_orientation;
	float dist, dx, dy;

	float  DEG_TO_RAD;
	float m_maxSpeed;
	float m_rotation;
	sf::Vector2f m_heading;
	float m_speed;
	Grid *m_grid;
	int pGridX;
	int pGridY;
	float m_shootDist;
	int bulletDelay;


};