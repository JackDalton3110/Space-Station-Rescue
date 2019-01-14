#include "Nests.h"

Nests::Nests():
	defendRad(400)
{
	m_Grid = new Grid();
	m_healthSystem = new HealthSystem();
	defendRad.setFillColor(sf::Color(0,100,0,70));
	spawnNests();
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
	std::cout << dist << std::endl;
	if (dist<defendRad.getRadius()+m_Grid->m_tileSize/2)
	{
		defendRad.setFillColor(sf::Color(100,0,0,70));
		
		line[0].position = sf::Vector2f(m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize/2, m_Grid->m_nestPoints[spawnSpot]->m_position.y+m_Grid->m_tileSize/2);
		line[0].color = sf::Color::Red;
		line[1].position = sf::Vector2f(pos.x, pos.y);
		line[1].color = sf::Color::Red;
		attack = true;
	}
	else
	{
		defendRad.setFillColor(sf::Color(0, 100, 0, 70));
		attack = false;
	}
}

void Nests::update(sf::Vector2f pos)
{
	
	dx = pos.x - defendRad.getPosition().x+m_Grid->m_tileSize/2;
	dy = pos.y - defendRad.getPosition().y+m_Grid->m_tileSize/2;
	dist = sqrt((dx*dx) + (dy*dy));
	Attack(pos);
}

void Nests::render(sf::RenderWindow &m_window)
{
	m_window.draw(defendRad);
	if(attack)
	m_window.draw(line,2,sf::Lines);
}