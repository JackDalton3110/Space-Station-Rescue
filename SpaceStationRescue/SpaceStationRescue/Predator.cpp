#include "Predator.h"
#include <iostream>
Predator::Predator(float x, float y, Grid &m_Grid) :
	m_position(x,y),
	m_velocity(0, 0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(2.0),
	m_speed(10),
	m_heading(0, 0),
	m_grid(&m_Grid)

{
	if (!m_texture.loadFromFile("./resources/Player.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.1, 0.1);
	m_sprite.setRotation(90);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	DEG_TO_RAD = 3.14 / 180;

	//m_position.x = m_grid->m_tileGrid[45][45]->m_position.x + m_grid->m_tileSize;
	//m_position.y = m_grid->m_tileGrid[45][45]->m_position.y + m_grid->m_tileSize;
	

	m_healthSystem = new HealthSystem(0, 0);
	m_healthSystem->setState(ENEMY);
	m_healthSystem->m_healthValue = 6;

	/*for (int i = 0; i < 3; i++)
	{
		m_bullet.push_back(new Bullet(*m_grid));
	}*/

	//m_grid->updateCost(pGridX, pGridY);


	pGridX = m_position.x / m_grid->m_tileSize;
	pGridY = m_position.y / m_grid->m_tileSize;

}
Predator::~Predator()
{

}

sf::Vector2f Predator::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Predator::getVelocity()
{
	return m_velocity;
}

float Predator::getRotation()
{
	return m_sprite.getRotation();
}

void Predator::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 2;
	}
}
void Predator::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 2;
	}
}
void Predator::increaseRotation()
{

	m_rotation += 4.0f;
}
void Predator::decreaseRotation()
{

	if (m_rotation != 0.00f)
	{
		m_rotation -= 4.0f;
	}
	else
	{
		m_rotation = 359.0f;
	}


}

void Predator::update(double dt)
{

	pGridX = floor((m_sprite.getPosition().x )/ m_grid->m_tileSize);
	pGridY = floor((m_sprite.getPosition().y)/ m_grid->m_tileSize);

	//

	//m_velocity = m_grid->m_tileGrid[pGridX][pGridY]->

	//if (m_velocity.x < m_maxSpeed) {
	//	m_velocity.x = m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().x * 3;
	//}
	//if (m_velocity.y < m_maxSpeed)
	//{
	//	m_velocity.y = m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().y * 3;
	//}
	
	std::cout << m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().x << ", " << m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().y << ", " << m_grid->m_tileGrid[pGridX][pGridY]->m_rotation << std::endl;


	//m_heading.x = cos(m_rotation * (3.14 / 180));
	//m_heading.y = sin(m_rotation * (3.14 / 180));
	/*if (m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().x == 0 && m_velocity.x > 0)
	{
		if (m_velocity.x != 0)
		{
			m_velocity.x--;
		}
		
	}
	else if (m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().x == 0 && m_velocity.x < 0)
	{
		if (m_velocity.x != 0)
		{
			m_velocity.x++;
		}
	}

	if (m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().y == 0 && m_velocity.y > 0)
	{
		if (m_velocity.y != 0)
		{
			m_velocity.y--;
		}
	}
	else if (m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().y == 0 && m_velocity.y < 0)
	{
		if (m_velocity.y != 0)
		{
			m_velocity.y++;
		}
	}

	if (m_velocity.x < m_maxSpeed && m_velocity.x > -m_maxSpeed)
	{
		m_velocity.x += m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().x ;
	}

	if (m_velocity.y < m_maxSpeed && m_velocity.x > -m_maxSpeed)
	{
		m_velocity.y += m_grid->m_tileGrid[pGridX][pGridY]->getVelocity().y ;
	}*/
	
	/*if (getPosition().x >= m_grid->m_tileGrid[pGridX][pGridY]->m_position.x + (m_grid->m_tileSize / 5)*4 &&
		getPosition().x <= m_grid->m_tileGrid[pGridX][pGridY]->m_position.x - m_grid->m_tileSize / 5 &&
		getPosition().y >= m_grid->m_tileGrid[pGridX][pGridY]->m_position.y + (m_grid->m_tileSize / 5) *4 &&
		getPosition().y <= m_grid->m_tileGrid[pGridX][pGridY]->m_position.y - m_grid->m_tileSize / 5)
	{*/
		m_velocity = m_grid->m_tileGrid[pGridX][pGridY]->getVelocity();
		m_rotation = m_grid->m_tileGrid[pGridX][pGridY]->m_rotation;
		m_velocity.x *= 5;
		m_velocity.y *= 5;

		collision();
	/*}*/
	
	

	m_sprite.setPosition(m_sprite.getPosition().x +m_velocity.x, 
						m_sprite.getPosition().y +m_velocity.y);
	m_sprite.setRotation(m_rotation);
	//collision();
	

	m_healthSystem->setPosition(m_sprite.getPosition().x - 600, m_sprite.getPosition().y - 450);
	m_healthSystem->update();



}

void Predator::respawn(float x, float y)
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

void Predator::collision()
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			//m_velocity.y *= -1;
			m_position.y += 5;
		}

	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			//m_velocity.y *= -1;
			m_position.y -= 5;
		}

	}
	if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		{
			//m_velocity.x *= -1;
			m_position.x -= 5;
		}

	}

	if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		{
			//m_velocity.x *= -1;
			m_position.x += 5;
		}

	}


}


void Predator::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);

	m_healthSystem->render(window);

	/*for (int i = 0; i < m_bullet.size(); i++)
	{
		if (m_bullet[i]->getState() == true) {
			m_bullet[i]->render(window);
		}
	}*/

}