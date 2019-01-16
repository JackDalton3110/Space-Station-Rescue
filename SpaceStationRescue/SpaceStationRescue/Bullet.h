#pragma once
#include <math.h>
#include "Grid.h"

enum BulletType
{
	SEEK,
	STANDARD
};

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
	void collisionWall();
	void collisionNest(int xPos, int yPos);
	bool getState();
	BulletType bulletState = STANDARD;
	void seekShoot(sf::Vector2f playerPosition);
	bool nestShot = false;
	sf::Vector2f m_position;
	int pGridX;
	int pGridY;
	bool active = false;

private:
	float getNewOrientation(float currentOrientation, float velocity);

	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	
	float m_orientation;
	float m_velocityF;
	float  DEG_TO_RAD;
	float m_maxSpeed;
	float m_rotation;
	sf::Vector2f m_heading;
	float m_speed;

	Grid *m_grid;

	
};