#include "Nests.h"

Nests::Nests():
	defendRad(400)
{
	m_Grid = new Grid();
	m_player = new Player();
	m_bullet = new Bullet();
	defendRad.setFillColor(sf::Color(0,100,0,70));
	spawnNests();
	
	m_bullet->m_position.x = m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize; 
	m_bullet->m_position.y = m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize;
}

Nests::~Nests()
{

}

void Nests::spawnNests()
{
	spawnSpot = rand() % 5;
	defendRad.setPosition(m_Grid->m_nestPoints[spawnSpot]->m_position.x + (m_Grid->m_tileSize / 2), m_Grid->m_nestPoints[spawnSpot]->m_position.y + (m_Grid->m_tileSize / 2));
	defendRad.setOrigin(400, 400);
}

void Nests::Attack(sf::Vector2f pos)
{
	
	if (dist<defendRad.getRadius()+m_Grid->m_tileSize/2)
	{
		defendRad.setFillColor(sf::Color(100,0,0,70));
		
		line[0].position = sf::Vector2f(m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize/2, m_Grid->m_nestPoints[spawnSpot]->m_position.y+m_Grid->m_tileSize/2);
		line[0].color = sf::Color::Red;
		line[1].position = sf::Vector2f(pos.x, pos.y);
		line[1].color = sf::Color::Red;
		m_bullet->nestShot = true;
		shot = true;
		sf::Vector2f test = sf::Vector2f(1, 0);
		//m_bullet->shoot(test, m_Grid->m_nestPoints[spawnSpot]->m_position, 0);
	}
	else
	{
		defendRad.setFillColor(sf::Color(0, 100, 0, 70));
	}
}

void Nests::update(sf::Vector2f pos, double dt)
{
	
	dx = pos.x - defendRad.getPosition().x+m_Grid->m_tileSize/2;
	dy = pos.y - defendRad.getPosition().y+m_Grid->m_tileSize/2;
	dist = sqrt((dx*dx) + (dy*dy));
	if (m_bullet->nestShot)
	{
		m_bullet->seekShoot(pos);
	}
	else
	{
		m_bullet->m_position.x = m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize;
		m_bullet->m_position.y = m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize;
	}
	if (shot)
	{
		cumulativeTime += dt/1000;
	}

	if (cumulativeTime >= 5)
	{
		m_bullet->nestShot = false;
		shot = false;
		m_bullet->m_position.x = m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize;
		m_bullet->m_position.y = m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize;
		cumulativeTime = 0;
	}


	Attack(pos);
	m_bullet->update(dt);
}

void Nests::render(sf::RenderWindow &m_window)
{
	
		m_window.draw(defendRad);
		if (m_bullet->nestShot)
		{
			m_window.draw(line, 2, sf::Lines);
			m_bullet->render(m_window);
		}
	
}