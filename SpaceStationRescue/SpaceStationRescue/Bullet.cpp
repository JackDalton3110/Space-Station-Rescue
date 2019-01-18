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

sf::Vector2f Bullet::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Bullet::getVelocity()
{
	return m_velocity;
}



void Bullet::shoot(sf::Vector2f m_heading, sf::Vector2f m_position, float m_rotation)
{
	if (active == false)
	{
		/*if (m_heading.x >= 0 && m_heading.y >= 0)
		{*/
			m_velocity = m_heading * m_speed;
	/*	}
		else {
			m_velocity = m_heading * -m_speed;
		}*/
		

		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_rotation);

		active = true;
	}
}

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

void Bullet::seekShoot(sf::Vector2f playerPosition)
{
	
		m_velocity = playerPosition - m_position;
		//Get magnitude of vector
		m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
		//m_velocityF = m_velocityF * m_maxSpeed;
		//Normalize vector
		m_velocity.x = m_velocity.x / m_velocityF;
		m_velocity.y = m_velocity.y / m_velocityF;

		m_velocity.x = m_velocity.x * m_speed/40;
		m_velocity.y = m_velocity.y * m_speed/40;

		m_rotation = getNewOrientation(m_rotation, m_velocityF) + 90;

		//pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
		//pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);


		//collision();
	
}

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
	pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
	pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);
	

	//std::cout << pGrid.x << std::endl;
	//std::cout << pGrid.y << std::endl;

	collisionWall();
}

bool Bullet::getState() {

	return active;
}

void Bullet::respawn(float x, float y)
{
	if (y >= 1000 + 100)
	{
		//m_sprite.setPosition(m_sprite.getPosition().x, -200);
	}

	else if (y < -200)
	{
		//m_sprite.setPosition(m_sprite.getPosition().x,1100);
	}
	else if (x < -200)
	{
		//m_sprite.setPosition(2100, m_sprite.getPosition().y);
	}
	else if (x >= 2100)
	{
		//m_sprite.setPosition(200, m_sprite.getPosition().y);
	}
}

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

void Bullet::collisionNest(int xPos, int yPos)
{
	

	
}

void Bullet::render(sf::RenderWindow &window)
{

	window.draw(m_sprite);
}