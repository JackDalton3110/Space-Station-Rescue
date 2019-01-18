#include "Bullet.h"
#include <iostream>
Bullet::Bullet(Grid &m_Grid) :
	m_position(900, 500),
	m_velocity(0, 0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(20.0),
	m_speed(100),
	m_heading(0, 0),
	m_grid(&m_Grid)

{
	if (!m_texture.loadFromFile("./resources/bullet.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(1, 1);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	DEG_TO_RAD = 3.14 / 180;


	pGridX = m_position.x / m_grid->m_tileSize;
	pGridY = m_position.y / m_grid->m_tileSize;
	
}
Bullet::~Bullet()
{

}
/// <summary>
/// Returns the bullets position
/// </summary>
/// <returns></returns>
sf::Vector2f Bullet::getPosition()
{
	return m_sprite.getPosition();
}
/// <summary>
/// Returns the bullet velocity
/// </summary>
/// <returns></returns>
sf::Vector2f Bullet::getVelocity()
{
	return m_velocity;
}


/// <summary>
/// Function that controlls the shooting of the normal non heat seaking bullet
/// The ships heading, position and rotation is passed in
/// Position sets where the bullet is being fired from
/// The heading is used to calculate the velocity of the bullet
/// Rotation passed in is set to the rotation of the bullet sprite
/// </summary>
/// <param name="m_heading"></param>
/// <param name="m_position"></param>
/// <param name="m_rotation"></param>
void Bullet::shoot(sf::Vector2f m_heading, sf::Vector2f m_position, float m_rotation)
{
	if (active == false)
	{
		
	
		m_velocity = m_heading * m_speed;
	

		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_rotation);

		active = true;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="currentOrientation"></param>
/// <param name="velocity"></param>
/// <returns></returns>
float Bullet::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

/// <summary>
/// Controls the shooting of the heat seeking bullet
/// the vector passed in is where the bullet will try to go towards
/// the bullet adjusts its heading and velocity to get to this point
/// resulting in a seeking bullet
/// </summary>
/// <param name="playerPosition"></param>
void Bullet::seekShoot(sf::Vector2f playerPosition)
{
	
		m_velocity = playerPosition - m_position;
		//Get magnitude of vector
		m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
		//Normalize vector
		m_velocity.x = m_velocity.x / m_velocityF;
		m_velocity.y = m_velocity.y / m_velocityF;

		m_velocity.x = m_velocity.x * m_speed/35;
		m_velocity.y = m_velocity.y * m_speed/35;

		m_rotation = getNewOrientation(m_rotation, m_velocityF) + 90;

	
}
/// <summary>
/// Updates the position of both heatseeking and normal bullets 
/// when their bools are true
/// </summary>
/// <param name="dt"></param>
void Bullet::update(double dt)
{
	if (active == true) {

		m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x * (dt / 100), m_sprite.getPosition().y + m_velocity.y * (dt / 100));

	}

	if (nestShot)
	{
		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_rotation); 
		
		m_position = m_position + m_velocity;

	}

	//Calculates the bullet postiion within the grid
	pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
	pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);
	

	

	collisionWall();
}
/// <summary>
/// Returns the active bool for normal bullet type
/// </summary>
/// <returns></returns>
bool Bullet::getState() {

	return active;
}

/// <summary>
/// Handles gullet collision with the world walls in 4 directions
/// When the bullet hits a wall the active bools are set to false
/// Mening the bullet is no longer updated or drawn
/// </summary>
void Bullet::collisionWall()
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			active = false;
			nestShot = false;
		}

	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			active = false;
			nestShot = false;
		}

	}
	if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		{
			active = false;
			nestShot = false;
		}

	}

	if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		{
			active = false;
			nestShot = false;
		}

	}

}
/// <summary>
/// Renders the bullet sprite to the screen
/// </summary>
/// <param name="window"></param>
void Bullet::render(sf::RenderWindow &window)
{

	window.draw(m_sprite);
}