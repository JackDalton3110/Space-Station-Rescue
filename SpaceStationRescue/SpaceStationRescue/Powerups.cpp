#include "Powerups.h"

Powerups::Powerups(int state, sf::Vector2f pos):
	m_scale(0.3),
	p_shape(sf::Vector2f(20,20))
{
	setState(state);
	setImage(currentPowerup);
	
	m_position = pos;
	p_shape.setPosition(pos);
	p_shape.setFillColor(sf::Color::Yellow);
	PowerupSprite.setTexture(PowerupTxt);
	PowerupSprite.setPosition(m_position);
	PowerupSprite.setScale(m_scale, m_scale);
	
}

Powerups::~Powerups()
{

}

Powerup Powerups::getState()
{
	return currentPowerup;
}

void Powerups::setImage(Powerup s)
{
	if (getState() == MORESHOTS)
	{
		if (!PowerupTxt.loadFromFile("./resource/bulletPowerup.png"))
		{
			std::cout << "error loading bullet Powerup image" << std::endl;
		}
	}
	else if (getState() == GOTTAGOFAST)
	{
		if (!PowerupTxt.loadFromFile("./resources/speedPowerup.png"));
		{
			std::cout << "error loading speed Powerup image" << std::endl;
		}
	}
	else if (getState() == NODAMAGE)
	{
		if (!PowerupTxt.loadFromFile("./resources/shieldPowerup.png"));
		{
			std::cout << "error loading shield Powerup image" << std::endl;
		}
	}
	else if (getState() == REPLENISH)
	{
		if (!PowerupTxt.loadFromFile("./resources/healthPowerup.png"));
		{
			std::cout << "error loading health Powerup image" << std::endl;
		}
	}

}

void Powerups::setState(int i)
{
	if (i == 0)
	{
		currentPowerup = MORESHOTS;
	}
	else if (i == 1)
	{
		currentPowerup = GOTTAGOFAST;
	}
	else if (i == 2)
	{
		currentPowerup = NODAMAGE;
	}
	else if (i == 3)
	{
		currentPowerup = REPLENISH;
	}
}

sf::Vector2f Powerups::getPosition()
{
	return m_position;
}

void Powerups::update()
{
}

void Powerups::render(sf::RenderWindow &m_window)
{
	m_window.draw(PowerupSprite);
}