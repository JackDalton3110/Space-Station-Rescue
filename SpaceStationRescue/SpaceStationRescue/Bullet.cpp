#include "Bullet.h"
#include <iostream>
Bullet::Bullet() :
	m_position(900, 500),
	m_velocity(0, 0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(20.0),
	m_speed(75),
	m_heading(0, 0)

{
	if (!m_texture.loadFromFile("./resources/bullet.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(1, 1);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	DEG_TO_RAD = 3.14 / 180;

	m_grid = new Grid();

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

	m_velocity = m_heading * m_speed;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);

	active = true;
}

void Bullet::update(double dt)
{
	if (active == true) {

		m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x * (dt / 100), m_sprite.getPosition().y + m_velocity.y * (dt / 100));

	}
	pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
	pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);


	//std::cout << pGrid.x << std::endl;
	//std::cout << pGrid.y << std::endl;

	collision();
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

void Bullet::collision()
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			active = false;
		}

	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			active = false;
		}

	}
	if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		{
			active = false;
		}

	}

	if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		{
			active = false;
		}

	}

}

void Bullet::render(sf::RenderWindow &window)
{

	window.draw(m_sprite);
}