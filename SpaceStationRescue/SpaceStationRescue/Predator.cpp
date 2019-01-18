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

	m_healthSystem = new HealthSystem(0, 0);
	m_healthSystem->setState(ENEMY);
	m_healthSystem->m_healthValue = 6;

	m_bullet = new Bullet(*m_grid);
	m_bullet->m_speed = 30;
	
	pGridX = m_position.x / m_grid->m_tileSize;
	pGridY = m_position.y / m_grid->m_tileSize;

}
Predator::~Predator()
{

}
/// <summary>
/// Returns the predator position
/// </summary>
/// <returns></returns>
sf::Vector2f Predator::getPosition()
{
	return m_sprite.getPosition();
}

/// <summary>
/// Returns the predators velocity
/// </summary>
/// <returns></returns>
sf::Vector2f Predator::getVelocity()
{
	return m_velocity;
}

/// <summary>
/// Returns the predators rotation
/// </summary>
/// <returns></returns>
float Predator::getRotation()
{
	return m_sprite.getRotation();
}

/// <summary>
/// Handles predator respawning when they die
/// Randomly picks one of the 3 nests to spawn at
/// If it picks a nest that is dead a random number is generated again 
/// If this nest is alive the predator will spawn here
/// If all 3 nests are dead the predator will not respawn
/// </summary>
/// <param name="nests"></param>
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
/// <summary>
/// Predator only updates when they are alive
/// calculates the distance from the predator to the player
/// calculates the predators grid position
/// respawns when health is 0
/// updates health system
/// 
/// Retrieves the vector from teh current tile the predator is on, within the flowfield
/// This vector is then multiplied by a speed allowing the predator to move along the flowfield to reach the player
/// The tile rotation is also set to the predator sprite making it face in the correct direction
/// </summary>
/// <param name="m_player"></param>
/// <param name="nests"></param>
/// <param name="dt"></param>
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

/// <summary>
/// IS called when the player is within the predators radius
/// Calculates the bullets heading and calls the shoot method for the normal bullet
/// </summary>
void Predator::shoot()
{
	if (dist<m_shootDist + m_grid->m_tileSize / 2)
	{


		m_headingBullet.x = cos(m_rotation * (3.14 / 180));
		m_headingBullet.y = sin(m_rotation * (3.14 / 180));

		m_bullet->shoot(m_headingBullet, m_sprite.getPosition(), m_rotation);
			
	}

}

/// <summary>
/// Checks collision with the world walls
/// Checks the ssquares that are nieghbouring the predator in the grid
/// If an obstacle is detected the predator will be bumped back from the wall
/// </summary>
void Predator::collision()
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			m_position.y += 5;
		}

	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			m_position.y -= 5;
		}

	}
	if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		{
			m_position.x -= 5;
		}

	}

	if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		{
			m_position.x += 5;
		}

	}


}

/// <summary>
/// Hnadles bullet collision related to the predator
/// Detects collision with the predator bullet and the player, minus the player health if hit
/// Checks if the predator is being hit by the predator bullet, if so the predators health gets deducted 
/// Bullets are destroyed when collision is detected 
/// </summary>
/// <param name="m_player"></param>
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
/// <summary>
/// Renders the predator and bullet when the predator is alive
/// </summary>
/// <param name="window"></param>
void Predator::render(sf::RenderWindow &window)
{
	if (m_healthSystem->m_healthValue > 0) {

		window.draw(m_sprite);
		if (m_bullet->getState() == true) {
			m_bullet->render(window);
		}
	}
	



		
	

}