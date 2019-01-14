#include "Nests.h"

Nests::Nests():
	defendRad(400)
{
	m_Grid = new Grid();
	m_player = new Player();
	defendRad.setFillColor(sf::Color(0,100,0,70));
	spawnNests();
}

Nests::~Nests()
{

}

void Nests::spawnNests()
{
	int spawnSpot = rand() % 5;
	defendRad.setOrigin(defendRad.getRadius()-m_Grid->m_tileSize/2,defendRad.getRadius()-m_Grid->m_tileSize/2);
	defendRad.setPosition(m_Grid->m_nestPoints[spawnSpot]->m_position.x, m_Grid->m_nestPoints[spawnSpot]->m_position.y);
}

void Nests::Attack()
{
	std::cout << dist << std::endl;
	if (dist<defendRad.getRadius())
	{
		defendRad.setFillColor(sf::Color(100,0,0,70));
	}
}

void Nests::update(sf::Vector2f pos)
{
	
	dx = pos.x - defendRad.getPosition().x;
	dy = pos.y - defendRad.getPosition().y;
	std::cout << pos.x << std::endl;
	std::cout << pos.y << std::endl;
	dist = sqrt((dx*dx) + (dy*dy));
	Attack();
}

void Nests::render(sf::RenderWindow &m_window)
{
	m_window.draw(defendRad);
}