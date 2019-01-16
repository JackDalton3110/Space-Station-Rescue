#include "Sweeper.h"

Sweeper::Sweeper(std::vector<Worker*> &m_worker):
	m_velocity(0,0),
	maxSpeed(3.0f),
	maxRotation(360),
	rotation(0),
	speed(2.0f),
	radius(250),
	alive(true)
{
	m_Grid = new Grid();
	workers = m_worker;
	if (!sweeperTxt.loadFromFile("./resources/sweeper.png"))
	{
		std::cout << "Cannot load sweeper image" << std::endl;
	}

	sweeperSprite.setTexture(sweeperTxt);
	sweeperSprite.setOrigin(sweeperSprite.getTextureRect().width / 2, sweeperSprite.getTextureRect().height / 2);
	sweeperSprite.setRotation(rotation);
	sweeperSprite.setScale(0.3, 0.3);
	radius.setPosition(m_position);
	radius.setFillColor(sf::Color(0, 100, 0, 70));
	radius.setOrigin(250,250);
	rotation = rand() % 360;
	m_heading.x = cos(rotation*(3.14 / 180));
	m_heading.y = sin(rotation*(3.14 / 180));
	if (m_heading.x >= 0 && m_heading.y >= 0)
	{
		m_velocity = m_heading * speed;
	}
	else
		m_velocity = m_heading * -speed;
	m_velocity = m_heading * speed;
	m_position.x = m_Grid->m_sweeperSpawn->m_position.x;
	m_position.y = m_Grid->m_sweeperSpawn->m_position.y;
	
	sweeperSprite.setPosition(m_position);
	pGridX = m_position.x / m_Grid->m_tileSize;
	pGridY = m_position.y / m_Grid->m_tileSize;
}

Sweeper::~Sweeper()
{

}

float Sweeper::getNewOrientation(float currentOrientation, float vel)
{
	if (vel > 0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else
		return currentOrientation;
}

void Sweeper::kinematicSeek(sf::Vector2f workerPos)
{
	if (currentState == FIND)
	{
		m_velocity = workerPos - m_position;
		//Get magnitude of vector
		m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
		//Normalize vector
		m_velocity.x = m_velocity.x / m_velocityF;
		m_velocity.y = m_velocity.y / m_velocityF;

		m_velocity.x = m_velocity.x * maxSpeed;
		m_velocity.y = m_velocity.y * maxSpeed;

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}
}

sf::Vector2f Sweeper::getPosition()
{
	return sweeperSprite.getPosition();
}

void Sweeper::collision(Player &m_player)
{
	if (m_Grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		
		m_velocity.y *= -1;
		m_position.y += 10;

	}
	if (m_Grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		
		m_velocity.y *= -1;
		m_position.y -= 10;
	}
	if (m_Grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		m_velocity.x *= -1;
		m_position.x -= 10;
	}

	if (m_Grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		m_velocity.x *= -1;
		m_position.x += 10;
	}

	for (int i = 0; i < workers.size(); i++)
	{
		if (sweeperSprite.getPosition().x - m_Grid->m_tileSize / 2 < workers[i]->getPosition().x + m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().x + m_Grid->m_tileSize / 2 > workers[i]->getPosition().x - m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().y - m_Grid->m_tileSize / 2 < workers[i]->getPosition().y + m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().y + m_Grid->m_tileSize / 2 > workers[i]->getPosition().y - m_Grid->m_tileSize / 2)
		{
			if (workers[i]->alive && getCurrentState()!=FLEE)
			{
				workers[i]->alive = false;
				scoreCount += 10;
			}
		}
	}

	for (int i = 0; i < m_player.m_bullet.size(); i++) {

		if (sweeperSprite.getPosition().x - m_Grid->m_tileSize / 2 < m_player.m_bullet[i]->getPosition().x + m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().x + m_Grid->m_tileSize / 2 > m_player.m_bullet[i]->getPosition().x - m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().y - m_Grid->m_tileSize / 2 < m_player.m_bullet[i]->getPosition().y + m_Grid->m_tileSize / 2 &&
			sweeperSprite.getPosition().y + m_Grid->m_tileSize / 2 > m_player.m_bullet[i]->getPosition().y - m_Grid->m_tileSize / 2) {

			if (m_player.m_bullet[i]->active == true && alive)
			{
				m_player.m_bullet[i]->active = false;
				std::cout << "HIT" << std::endl;
				alive = false;
				m_player.score += scoreCount;
			}

		}
	}
}

void Sweeper::kinematicFlee(sf::Vector2f pos)
{
	m_velocity = m_position - pos;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * maxSpeed;
	m_velocity.y = m_velocity.y * maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);
}

void Sweeper::setBehaveState(sf::Vector2f pos, behaveState S)
{
	dx = pos.x - radius.getPosition().x + m_Grid->m_tileSize / 2;
	dy = pos.y - radius.getPosition().y + m_Grid->m_tileSize / 2;
	dist = sqrt((dx*dx) + (dy*dy));
	if (dist < radius.getRadius())
	{
		currentState = FLEE;
		kinematicFlee(pos);
		//std::cout << "FLEE" << std::endl;
		radius.setFillColor(sf::Color(100, 0, 0, 70));
	}
	else if (currentState != FLEE)
	{
		for (int i = 0; i < workers.size(); i++)
		{
			dx = workers[i]->getPosition().x - radius.getPosition().x + m_Grid->m_tileSize / 2;
			dy = workers[i]->getPosition().y - radius.getPosition().y + m_Grid->m_tileSize / 2;
			dist = sqrt((dx*dx) + (dy*dy));
			if (dist < radius.getRadius())
			{
				if (workers[i]->alive)
				{
					currentState = FIND;

					kinematicSeek(workers[i]->getPosition());
					//std::cout << "SEEK" << std::endl;
					radius.setFillColor(sf::Color(0, 0, 100, 70));
				}
				else
				{
					currentState = WANDER;
					//std::cout << "WANDER" << std::endl;
					radius.setFillColor(sf::Color(0, 100, 0, 70));
				}
			}
			
		}
	}
	else
	{
		currentState = WANDER;
		//std::cout << "WANDER" << std::endl;
		radius.setFillColor(sf::Color(0, 100, 0, 70));
	}
}

behaveState Sweeper::getCurrentState()
{
	return currentState;
}

float Sweeper::rotateSweeper(sf::Vector2f vel, float rot)
{
	if (vel.x > 0.0 && rot < 80)
	{
		rotation += 10;
	}
	else if (vel.x > 0.0 && rot > 100)
	{
		rotation -= 10;
	}

	if (vel.x > 0.0 && vel.y > 0.0 && rot<130)
	{
		rotation += 10;
	}
	else if (vel.x > 0.0 && vel.y>0.0 && rot > 140)
	{
		rotation -= 10;
	}

	if (vel.y > 0.0 && rot < 170)
	{
		rotation += 10;
	}
	else if (vel.y > 0.0 && rot > 190)
	{
		rotation -= 10;
	}

	if (vel.x < 0.0 && vel.y > 0.0 && rot <215)
	{
		rotation += 10;
	}
	else if (vel.x < 0.0 && vel.y>0.0 && rot > 235)
	{
		rotation -= 10;
	}

	
	else if (vel.x < 0.0 && rot > 280)
	{
		rotation = 270;
	}

	if (vel.x < 0.0 && vel.y < 0.0 && rot <305)
	{
		rotation += 10;
	}
	else if (vel.x < 0.0 && vel.y < 0.0 && rot > 325)
	{
		rotation -= 10;
	}

	if (vel.y < 0.0 && rot < maxRotation)
	{
		rotation += 10;
	}

	if (vel.x > 0.0 && vel.y < 0.0 && rot >0)
	{
		rotation = 45;
	}

	if (rotation > 340)
	{
		rotation = 0;
	}
	return rotation;
}

void Sweeper::update(sf::Vector2f pos, double dt, Player &m_player)
{
	if (alive)
	{
		pGridX = floor(sweeperSprite.getPosition().x / m_Grid->m_tileSize);
		pGridY = floor(sweeperSprite.getPosition().y / m_Grid->m_tileSize);
		collision(m_player);
		radius.setPosition(m_position);
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;
		sweeperSprite.setPosition(m_position.x, m_position.y);
		rotateSweeper(m_velocity, rotation);
		cumulativeTime += dt / 1000;
		setBehaveState(pos, currentState);
		sweeperSprite.setRotation(rotation);
		if (cumulativeTime >= 5)
		{
			rotation = rand() % 360;
			m_heading.x = cos(rotation*(3.14 / 180));
			m_heading.y = sin(rotation*(3.14 / 180));
			if (m_heading.x >= 0 && m_heading.y >= 0)
			{
				m_velocity = m_heading * speed;
			}
			else
				m_velocity = m_heading * -speed;
			cumulativeTime = 0;
		}
	}
	
	
}

void Sweeper::render(sf::RenderWindow &window)
{
	if (alive)
	{
		window.draw(radius);
		window.draw(sweeperSprite);
	}

}
