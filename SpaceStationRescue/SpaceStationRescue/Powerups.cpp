#include "Powerups.h"

Powerups::Powerups(int state):
	m_scale(0.3),
	collected(false)
{
	
	if (!PowerupTxt.loadFromFile("resources/bulletPowerup.png"))
	{
		std::cout << "error loading bullet Powerup image" << std::endl;
	}
	if (!PowerupTxt2.loadFromFile("resources/speedPowerup.png"));
	{
		std::cout << "error loading speed Powerup image" << std::endl;
	}
	if (!PowerupTxt3.loadFromFile("resources/shieldPowerup.png"));
	{
		std::cout << "error loading shield Powerup image" << std::endl;
	}
	if (!PowerupTxt4.loadFromFile("resources/healthPowerup.png"));
	{
		std::cout << "error loading health Powerup image" << std::endl;
	}
	//setImage(currentPowerup);
	setState(state);
	PowerupSprite.setScale(m_scale, m_scale);
	pGridX = m_position.x / m_Grid->m_tileSize;
	pGridY = m_position.y / m_Grid->m_tileSize;
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
		
	}
	else if (getState() == GOTTAGOFAST)
	{
		
	}
	else if (getState() == NODAMAGE)
	{
		PowerupSprite.setTexture(PowerupTxt3);
	}
	else if (getState() == REPLENISH)
	{
		PowerupSprite.setTexture(PowerupTxt4);
	}

}

void Powerups::setState(int i)
{
	if (i == 0)
	{
		currentPowerup = MORESHOTS;
		PowerupSprite.setTexture(PowerupTxt); 
		PowerupSprite.setOrigin(PowerupSprite.getTextureRect().width / 2, PowerupSprite.getTextureRect().height / 2);
		PowerupSprite.setPosition(2760, 3022);
	}
	else if (i == 1)
	{
		currentPowerup = GOTTAGOFAST;
		PowerupSprite.setTexture(PowerupTxt2);
		PowerupSprite.setOrigin(PowerupSprite.getTextureRect().width / 2, PowerupSprite.getTextureRect().height / 2);
		PowerupSprite.setPosition(852, 1731);
	}
	else if (i == 2)
	{
		currentPowerup = NODAMAGE;
		PowerupSprite.setTexture(PowerupTxt3);
		PowerupSprite.setOrigin(PowerupSprite.getTextureRect().width / 2, PowerupSprite.getTextureRect().height / 2);
		PowerupSprite.setPosition(2071, 572);
	}
	else if (i == 3)
	{
		currentPowerup = REPLENISH;
		PowerupSprite.setTexture(PowerupTxt4);
		PowerupSprite.setOrigin(PowerupSprite.getTextureRect().width / 2, PowerupSprite.getTextureRect().height / 2);
		PowerupSprite.setPosition(304, 3158);
	}
}

sf::Vector2f Powerups::getPosition()
{
	return PowerupSprite.getPosition();
}

void Powerups::update()
{
	rotation += 1;
	if (rotation >= 358)
	{
		rotation = 0;
	}
	PowerupSprite.setRotation(rotation);
	pGridX = floor(PowerupSprite.getPosition().x / m_Grid->m_tileSize);
	pGridY = floor(PowerupSprite.getPosition().y / m_Grid->m_tileSize);
	//std::cout << m_position.x <<" , "<< m_position.y << std::endl;
}

void Powerups::render(sf::RenderWindow &m_window)
{
	if(!collected)
	m_window.draw(PowerupSprite);
}