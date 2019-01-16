#include "Sweeper.h"

Sweeper::Sweeper():
	m_velocity(0,0),
	maxSpeed(2.0f),
	maxRotation(360),
	rotation(0),
	m_heading(1,0),
	speed(2.0f)
{
	m_Grid = new Grid();

	if (!sweeperTxt.loadFromFile("./resources/sweeper.png"))
	{
		std::cout << "Cannot load sweeper image" << std::endl;
	}

	sweeperSprite.setTexture(sweeperTxt);
	sweeperSprite.setOrigin(sweeperSprite.getTextureRect().width / 2, sweeperSprite.getTextureRect().height / 2);
	sweeperSprite.setRotation(rotation);
	sweeperSprite.setScale(0.3, 0.3);
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

sf::Vector2f Sweeper::getPosition()
{
	return sweeperSprite.getPosition();
}

void Sweeper::collision()
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
}

void Sweeper::setBehaveState(behaveState S)
{
}

behaveState Sweeper::getCurrentState()
{
	return behaveState();
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

void Sweeper::update(double dt)
{
	pGridX = floor(sweeperSprite.getPosition().x / m_Grid->m_tileSize);
	pGridY = floor(sweeperSprite.getPosition().y / m_Grid->m_tileSize);
	collision();
	m_position.x += m_velocity.x ;
	m_position.y += m_velocity.y ;
	sweeperSprite.setPosition(m_position.x, m_position.y);
	rotateSweeper(m_velocity, rotation);
	cumulativeTime += dt / 1000;
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

void Sweeper::render(sf::RenderWindow &window)
{

	window.draw(sweeperSprite);

}
