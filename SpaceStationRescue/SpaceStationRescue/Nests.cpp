#include "Nests.h"
#include <cstdlib>

Nests::Nests(int m_spawnSpot):
	defendRad(400),
	spawnSpot(m_spawnSpot)
{
	m_Grid = new Grid();
	m_bullet = new Bullet();
	
	defendRad.setFillColor(sf::Color(0,100,0,70));
	spawnNests();
	
}

Nests::~Nests()
{

}

void Nests::spawnNests()
{
	m_gridX = m_Grid->m_nestPoints[spawnSpot]->m_position.x;
	m_gridY = m_Grid->m_nestPoints[spawnSpot]->m_position.y;
	defendRad.setPosition(m_Grid->m_nestPoints[spawnSpot]->m_position.x + (m_Grid->m_tileSize / 2), m_Grid->m_nestPoints[spawnSpot]->m_position.y + (m_Grid->m_tileSize / 2));
	defendRad.setOrigin(400, 400);
	
	m_healthSystem = new HealthSystem(200, 10);
	m_healthSystem->setPosition(m_Grid->m_nestPoints[spawnSpot]->m_position.x - 67, m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize * 1.5 );
	m_healthSystem->setState(ENEMY);
	m_healthSystem->m_healthValue = 5;
	m_bullet->m_position.x = m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize;
	m_bullet->m_position.y = m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize;
}

void Nests::Attack(sf::Vector2f pos)
{
	//std::cout << dist << std::endl;
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


void Nests::update(Player &m_player, double dt)
{
	
	dx = m_player.getPosition().x - defendRad.getPosition().x+m_Grid->m_tileSize/2;
	dy = m_player.getPosition().y - defendRad.getPosition().y+m_Grid->m_tileSize/2;
	dist = sqrt((dx*dx) + (dy*dy));

	if (m_bullet->nestShot)
	{
		m_bullet->seekShoot(m_player.getPosition());
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

	std::cout << cumulativeTime << std::endl;

	if (cumulativeTime >= 5)
	{
		m_bullet->nestShot = false;
		shot = false;
		m_bullet->m_position.x = m_Grid->m_nestPoints[spawnSpot]->m_position.x + m_Grid->m_tileSize;
		m_bullet->m_position.y = m_Grid->m_nestPoints[spawnSpot]->m_position.y + m_Grid->m_tileSize;
		cumulativeTime = 0;
	}


	Attack(m_player.getPosition());
	m_bullet->update(dt);
	

	collision(m_player);
	m_healthSystem->update();

}


void Nests::collision(Player & m_player)
{
	for (int i = 0; i < m_player.m_bullet.size(); i++) {

		if (m_player.m_bullet[i]->pGridX == m_Grid->m_nestPoints[spawnSpot]->m_xPos && m_player.m_bullet[i]->pGridY == m_Grid->m_nestPoints[spawnSpot]->m_yPos) {

			if (m_player.m_bullet[i]->active == true)
			{
				m_healthSystem->m_healthValue--;
				
				m_player.m_bullet[i]->active = false;
			}
	
		}
	}

	/*for (int i = 0; i < nests.size(); i++) {

		if (getPosition().x - m_grid->m_tileSize / 2 < nests[i].m_bullet->getPosition().x + m_grid->m_tileSize / 2 &&
			getPosition().x + m_grid->m_tileSize / 2 > nests[i].m_bullet->getPosition().x - m_grid->m_tileSize / 2 &&
			getPosition().y - m_grid->m_tileSize / 2 < nests[i].m_bullet->getPosition().y + m_grid->m_tileSize / 2 &&
			getPosition().y + m_grid->m_tileSize / 2 > nests[i].m_bullet->getPosition().y - m_grid->m_tileSize / 2) {
			if (nests[i].m_bullet->nestShot == true)
			{
				m_healthSystem->m_healthValue--;

				nests[i].m_bullet->nestShot = false;
			}

		}
	}*/

	if (m_bullet->getPosition().x - m_Grid->m_tileSize / 2 < m_player.getPosition().x + m_Grid->m_tileSize / 2 &&
		m_bullet->getPosition().x + m_Grid->m_tileSize / 2 > m_player.getPosition().x - m_Grid->m_tileSize / 2 &&
		m_bullet->getPosition().y - m_Grid->m_tileSize / 2 < m_player.getPosition().y + m_Grid->m_tileSize / 2 &&
		m_bullet->getPosition().y + m_Grid->m_tileSize / 2 > m_player.getPosition().y - m_Grid->m_tileSize / 2) {
		if (m_bullet->nestShot == true)
		{
			m_player.m_healthSystem->m_healthValue--;

			m_bullet->nestShot = false;
		}
	}
}

void Nests::render(sf::RenderWindow &m_window)
{
	m_window.draw(defendRad);
	m_healthSystem->render(m_window);
	if (m_bullet->nestShot)
	{
		m_window.draw(line, 2, sf::Lines);
		m_bullet->render(m_window);
	}
}