#pragma once
#include <math.h>
#include "Grid.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void respawn(float x, float y);
	void update(double dt);
	void render(sf::RenderWindow &window);
	void shoot(sf::Vector2f m_heading, sf::Vector2f m_position, float m_rotation);
	void collision();
	bool getState();

private:
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_orientation;

	float  DEG_TO_RAD;
	float m_maxSpeed;
	float m_rotation;
	sf::Vector2f m_heading;
	float m_speed;

	Grid *m_grid;
	int pGridX;
	int pGridY;

	bool active = false;

};