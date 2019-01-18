#include "Predator.h"
#include <iostream>
Predator::Predator(float x, float y, Grid &m_Grid) :
	m_position(x,y),
	m_velocity(0, 0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(3.0),
	m_speed(10),
	m_heading(0, 0),
	m_grid(&m_Grid),
	m_shootDist(400)

{
	if (!m_texture.loadFromFile("./resources/Predator.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.17, 0.17);
	m_sprite.setRotation(90);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	DEG_TO_RAD = 3.14 / 180;

	//m_position.x = m_grid->m_tileGrid[45][45]->m_position.x + m_grid->m_tileSize;
	//m_position.y = m_grid->m_tileGrid[45][45]->m_position.y + m_grid->m_tileSize;
	

	m_healthSystem = new HealthSystem(0, 0);
	m_healthSystem->setState(ENEMY);
	m_healthSystem->m_healthValue = 6;

	m_bullet = new Bullet(*m_grid);
	m_bullet->m_speed = 30;
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


void Predator::respawn(std::vector<Nests*> &nests)
{


		int val = rand() % 3;
		int deathVal = 0;

		while (nests[val]->m_healthSystem->m_healthValue <= 0)
		{
			int val = rand() % 3;
			deathVal++;
		}

		if (deathVal < 3)
		{
			m_sprite.setPosition(nests[val]->getPosition());
			m_healthSystem->m_healthValue = 6;
		}
		


}

void Predator::update(Player &m_player, std::vector<Nests*> &nests, double dt)
{
	if (m_healthSystem->m_healthValue > 0 )
	{
		dx = m_player.getPosition().x - m_sprite.getPosition().x + m_grid->m_tileSize / 2;
		dy = m_player.getPosition().y - m_sprite.getPosition().y + m_grid->m_tileSize / 2;
		dist = sqrt((dx*dx) + (dy*dy));
		shoot();

		pGridX = floor((m_sprite.getPosition().x) / m_grid->m_tileSize);
		pGridY = floor((m_sprite.getPosition().y) / m_grid->m_tileSize);

		m_velocity = m_grid->m_tileGrid[pGridX][pGridY]->getVelocity();
		m_rotation = m_grid->m_tileGrid[pGridX][pGridY]->m_rotation;
		m_velocity.x *= m_maxSpeed;
		m_velocity.y *= m_maxSpeed;

		collision();
		if (m_healthSystem->m_healthValue != 0)
		{
			collisionPlayer(m_player);
		}
		if(m_healthSystem->m_healthValue == 0)
		{
			respawn(nests);
		}

	



		m_bullet->update(dt);



		
		
			m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x,
				m_sprite.getPosition().y + m_velocity.y);
			m_sprite.setRotation(m_rotation);
		
		


	}
	
	m_healthSystem->setPosition(m_sprite.getPosition().x - 600, m_sprite.getPosition().y - 450);
	m_healthSystem->update();



}


void Predator::shoot()
{
	if (dist<m_shootDist + m_grid->m_tileSize / 2)
	{


			m_headingBullet.x = cos(m_rotation * (3.14 / 180));
			m_headingBullet.y = sin(m_rotation * (3.14 / 180));

			m_bullet->shoot(m_headingBullet, m_sprite.getPosition(), m_rotation);
			
		
		
		//m_bullet->shoot(test, m_Grid->m_nestPoints[spawnSpot]->m_position, 0);
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


void Predator::collisionPlayer(Player & m_player)
{
	if (m_bullet->getPosition().x - m_grid->m_tileSize / 2 < m_player.getPosition().x + m_grid->m_tileSize / 2 &&
		m_bullet->getPosition().x + m_grid->m_tileSize / 2 > m_player.getPosition().x - m_grid->m_tileSize / 2 &&
		m_bullet->getPosition().y - m_grid->m_tileSize / 2 < m_player.getPosition().y + m_grid->m_tileSize / 2 &&
		m_bullet->getPosition().y + m_grid->m_tileSize / 2 > m_player.getPosition().y - m_grid->m_tileSize / 2) {
		if (m_bullet->active == true && !m_player.shield)
		{
			m_player.m_healthSystem->m_healthValue--;

			m_bullet->active = false;
		}
		if (m_bullet->active == true && m_player.shield)
		{
			m_bullet->active = false;
		}
	}
	
	for (int i = 0; i < m_player.m_bullet.size(); i++) {

		if (m_player.m_bullet[i]->pGridX == pGridX && m_player.m_bullet[i]->pGridY == pGridY) {

			if (m_player.m_bullet[i]->active == true && !m_player.firepower)
			{
				m_healthSystem->m_healthValue -=2;

				m_player.m_bullet[i]->active = false;
			}
			else if (m_player.m_bullet[i]->active == true && m_player.firepower)
			{
				m_healthSystem->m_healthValue -= 3;

				m_player.m_bullet[i]->active = false;
			}

		}
	}
	
}

void Predator::render(sf::RenderWindow &window)
{
	if (m_healthSystem->m_healthValue > 0) {

		window.draw(m_sprite);
		if (m_bullet->getState() == true) {
			m_bullet->render(window);
		}
	}
	



		
	

}