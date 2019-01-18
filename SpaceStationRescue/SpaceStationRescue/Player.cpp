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
	m_font.loadFromFile("./resources/OCRAEXT.TTF");
	
	playerText.setFont(m_font);
	playerText.setCharacterSize(58);
	playerText.setFillColor(sf::Color::Green);
	enemyText.setFont(m_font);
	playerText.setString("Score: " + std::to_string(score) + " /200");
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

sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

float Player::getRotation()
{
	return m_sprite.getRotation();
}

void Player::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 2;
	}
}
void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 2;
	}
}
void Player::increaseRotation()
{

	m_rotation += 4.0f;
}
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

		respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);
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



		m_healthSystem->setPosition(m_sprite.getPosition().x - 600, m_sprite.getPosition().y - 450);
		m_healthSystem->update();
		playerText.setPosition(m_sprite.getPosition().x - 300, m_sprite.getPosition().y - 470);
		playerText.setString("Score: " + std::to_string(score) + " /200");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false && fired == true)
		{
			fired = false;


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false && fired == true)
			{
				fired = false;
			}
		}

		m_healthSystem->setPosition(m_sprite.getPosition().x - 600, m_sprite.getPosition().y - 450);
		m_healthSystem->update();

	}
}

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


void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(playerText);

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