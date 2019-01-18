#include "Player.h"
#include <iostream>
Player::Player(Grid &m_Grid) :
	m_position(2000, 2000),
	m_velocity(0,0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(40.0),
	shieldcrc(60),
	m_speed(0),
	m_heading(0,0),
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

	shieldcrc.setFillColor(sf::Color(0, 0, 100, 60));
	shieldcrc.setPosition(m_sprite.getPosition().x-m_grid->m_tileSize/2, m_sprite.getPosition().y-m_grid->m_tileSize/2);
	shieldcrc.setOrigin(30, 30);

	pGridX = m_position.x / m_grid->m_tileSize;
	pGridY= m_position.y / m_grid->m_tileSize;

	m_healthSystem = new HealthSystem(0,0);
	m_healthSystem->setState(PLAYER);
	m_healthSystem->m_healthValue = 6;

	for (int i = 0; i < 3; i++)
	{
		m_bullet.push_back(new Bullet(*m_grid));
	}
	

}
Player::~Player()
{

}
/// <summary>
/// Returns the position of the player sprite
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}

/// <summary>
/// Returns the velocity of the player sprite
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}


/// <summary>
/// Returns the sprite rotation
/// </summary>
/// <returns></returns>
float Player::getRotation()
{
	return m_sprite.getRotation();
}

/// <summary>
/// Increases the player speed
/// </summary>
void Player::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 2;
	}
}

/// <summary>
/// Decreases the playe speed
/// </summary>
void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 2;
	}
}

/// <summary>
/// Increases the player rotation
/// </summary>
void Player::increaseRotation()
{

	m_rotation += 4.0f;
}

/// <summary>
/// Decreases the player rotation
/// </summary>
void Player::decreaseRotation()
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
/// <summary>
/// only updates the player if the player is alive
/// calculates the players grid position
/// handles all keyboard input for the player
/// updates powerups
/// fires bullet when spacebar is clicked, allowing for 3 bullets to be fired at a time
/// updates healthsystem position and values
/// updates player sprite position
/// </summary>
/// <param name="dt"></param>
/// <param name="m_powerUps"></param>
void Player::update(double dt, std::vector<Powerups *>&m_powerUps)
{
	if (m_healthSystem->m_healthValue > 0)
	{
		pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
		pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);


	pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
	pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);
	collision(m_powerUps, dt);
	cumulativeTime += dt / 1000;
	shieldcrc.setPosition(m_sprite.getPosition().x - m_grid->m_tileSize / 2, m_sprite.getPosition().y - m_grid->m_tileSize / 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		speedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speedDown();
	}
	
	for (int i = 0; i < m_powerUps.size(); i++)
	{
		if (m_powerUps[i]->getState() == GOTTAGOFAST && m_powerUps[i]->collected)
		{
			if (cumulativeTime <= 10)
			{
				m_maxSpeed = 70.0;
			}
			else if (cumulativeTime >= 10 && m_speed >= m_maxSpeed)
			{
				m_maxSpeed = 50.0;
				speedDown();
			}
		}

		if (m_powerUps[i]->getState() == REPLENISH && m_powerUps[i]->collected)
		{
			m_healthSystem->m_healthValue = 6;
		}

		if (m_powerUps[i]->getState() == MORESHOTS && m_powerUps[i]->collected)
		{
			if (cumulativeTime <= 15)
			{
				firepower = true;
			}
			else
				firepower = false;
		}

		if (m_powerUps[i]->getState() == NODAMAGE && m_powerUps[i]->collected)
		{
			if (cumulativeTime <= 15)
			{
				shield = true;
			}
			else
				shield = false;
		}
		
	}


		m_heading.x = cos(m_rotation * (3.14 / 180));
		m_heading.y = sin(m_rotation * (3.14 / 180));

		m_velocity = m_heading * m_speed;

		m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x * (dt / 100), m_sprite.getPosition().y + m_velocity.y * (dt / 100));
		m_sprite.setRotation(m_rotation);
		if (bulletindex <= 2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_bullet[bulletindex]->getState() == false && fired == false)
			{
				m_bullet[bulletindex]->shoot(m_heading, m_sprite.getPosition(), m_rotation);
				bulletindex++;
				fired = true;

			}
		}
		else
			bulletindex = 0;


		for (int i = 0; i < m_bullet.size(); i++)
		{
			if (m_bullet[i]->getState() == true) {

				m_bullet[i]->update(dt);

			}
		}


	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false && fired == true)
		{
			fired = false;
		}
	}

	m_healthSystem->setPosition(m_sprite.getPosition().x - 600, m_sprite.getPosition().y - 450);
	m_healthSystem->update();
	
}
/// <summary>
/// Handles collision with world walls in all directions 
/// Checks the adjacent walls if they are of type obstacle and performs rectangle collision at these points 
/// 
/// Also checks collision with powerups, checking if its in the same grid position as the player,
/// Checks the typr of powerup and sets timer to 0 and picked up to false
/// </summary>
/// <param name="m_powerUps"></param>
/// <param name="dt"></param>
 void Player::collision(std::vector<Powerups*>&m_powerUps, double dt)
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			m_sprite.setPosition(m_sprite.getPosition().x, m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize + (m_grid->m_tileSize / 2));
		}
		
	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			m_sprite.setPosition(m_sprite.getPosition().x, m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y - (m_grid->m_tileSize / 2));
		}
	
	}
	  if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		 if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		 {
			 m_sprite.setPosition(m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x - (m_grid->m_tileSize / 2), m_sprite.getPosition().y);
		 }
		
	}
	
	  if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		 if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		 {
			 m_sprite.setPosition(m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize + (m_grid->m_tileSize / 2), m_sprite.getPosition().y);
		 }
	
	}

	  if (m_grid->m_tileGrid[pGridX - 1][pGridY - 1]->getCurrentState() == OBSTACLE)
	  {
		  if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		  {
			  m_sprite.setPosition(m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize + (m_grid->m_tileSize / 2), m_sprite.getPosition().y);
		  }

	  }

	  for (int i = 0; i < m_powerUps.size(); i++)
	  {
		  if (pGridX == m_powerUps[i]->pGridX  &&
			  pGridY == m_powerUps[i]->pGridY)
		  {
			  if (!m_powerUps[i]->collected && m_powerUps[i]->getState() == MORESHOTS)
			  {
				  cumulativeTime = 0;
				  m_powerUps[i]->collected = true;
				  
			  }
			  else if (!m_powerUps[i]->collected && m_powerUps[i]->getState() == GOTTAGOFAST)
			  {
				  m_powerUps[i]->collected = true;
				  cumulativeTime = 0;
			  }
			  else if (!m_powerUps[i]->collected && m_powerUps[i]->getState() == REPLENISH)
			  {
				  cumulativeTime = 0;
				  m_powerUps[i]->collected = true;
			  }
			  else if (!m_powerUps[i]->collected && m_powerUps[i]->getState() == NODAMAGE)
			  {
				  cumulativeTime = 0;
				  m_powerUps[i]->collected = true;
			  }
		  }
	  }


}

 /// <summary>
 /// Only draws player sprite if player is alive
 /// only draws the player shield if shield is active
 /// Renders healthsystem hearts to the screen as a HUD
 /// loops through the bullet vector and renders 
 /// </summary>
 /// <param name="window"></param>
void Player::render(sf::RenderWindow &window)
{

	if (m_healthSystem->m_healthValue > 0)
	{
		window.draw(m_sprite);
	}
	
	if (shield)
	{
		window.draw(shieldcrc);
	}

	m_healthSystem->render(window);

	for (int i = 0; i < m_bullet.size(); i++)
	{
		if (m_bullet[i]->getState() == true) {
			m_bullet[i]->render(window);
		}
	}
	
}