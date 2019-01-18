#include "HealthSystem.h"
HealthSystem::HealthSystem(float width, float height) :
	m_position(700, 550),
	m_healthValue(3.0f),
	m_hbWidth(width),
	m_hbHeight(height)
{
	if (!health3_0Txt.loadFromFile("resources/health3_0.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health2_5Txt.loadFromFile("resources/health2_5.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health2_0Txt.loadFromFile("resources/health2_0.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health1_5Txt.loadFromFile("resources/health1_5.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health1_0Txt.loadFromFile("resources/health1_0.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health0_5Txt.loadFromFile("resources/health0_5.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}
	if (!health0_0Txt.loadFromFile("resources/health0_0.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}


	healthSprite.setTexture(health3_0Txt);
	healthSprite.setPosition(m_position);

	outerRect.setSize(sf::Vector2f(m_hbWidth, m_hbHeight));
	outerRect.setOutlineColor(sf::Color::Red);
	outerRect.setOutlineThickness(5);
	outerRect.setFillColor(sf::Color::White);
	outerRect.setPosition(m_position);

	innerRect.setSize(sf::Vector2f(m_hbWidth, m_hbHeight));
	innerRect.setOutlineColor(sf::Color::Red);
	outerRect.setFillColor(sf::Color::Red);
	innerRect.setOutlineThickness(5);
	innerRect.setPosition(m_position);


}

HealthSystem::~HealthSystem()
{

}

/// <summary>
/// Sets the state of the healthsystem
/// </summary>
/// <param name="state"></param>
void HealthSystem::setState(hsState state)
{
	m_currentState = state;
}


/// <summary>
/// Returns the state of the health system
/// </summary>
/// <returns></returns>
hsState HealthSystem::getState()
{
	return m_currentState;
}
/// <summary>
/// If the healthsystem state is set to player, the hearts png is chnaged depending on the helthvalue
/// If the healthsystem state is set to enemy, the percentage that the health bar is filled is changed depending on the health value
/// </summary>
void HealthSystem::update()
{

	if (getState() == PLAYER)
	{
		switch (m_healthValue)
		{
		case 6:
			healthSprite.setTexture(health3_0Txt);
			break;
		case 5:
			healthSprite.setTexture(health2_5Txt);
			break;
		case 4:
			healthSprite.setTexture(health2_0Txt);
			break;
		case 3:
			healthSprite.setTexture(health1_5Txt);
			break;
		case 2:
			healthSprite.setTexture(health1_0Txt);
			break;
		case 1:
			healthSprite.setTexture(health0_5Txt);
			break;
		default:
			break;
		}

		if (m_healthValue <= 0)
		{
			healthSprite.setTexture(health0_0Txt);
		}
	}
	else
	{
		switch (m_healthValue)
		{
		case 6:
		
			innerRect.setSize(sf::Vector2f(m_hbWidth * 1, m_hbHeight));
			
			break;
		case 5:
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0.83, m_hbHeight));
			
			break;
		case 4:
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0.66, m_hbHeight));
			
			break;
		case 3:
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0.5, m_hbHeight));
			
			break;
		case 2:
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0.33, m_hbHeight));
			break;
		case 1:
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0.166, m_hbHeight));
			break;
		default:
			break;
		}
		if (m_healthValue <= 0)
		{
			innerRect.setSize(sf::Vector2f(m_hbWidth * 0, m_hbHeight));
		}
	}
	


}

/// <summary>
/// Method that sets the position of the health bar / hearts 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void HealthSystem::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

/// <summary>
/// Renders and sets the position of the hearts if state is player
/// renders and sets the position of the healthbar if state is enemy
/// </summary>
/// <param name="window"></param>
void HealthSystem::render(sf::RenderWindow &window)
{
	if (getState() == PLAYER)
	{
		healthSprite.setPosition(m_position);
		window.draw(healthSprite);
	}
	else
	{
		innerRect.setPosition(m_position);
		outerRect.setPosition(m_position);
		window.draw(outerRect);
		window.draw(innerRect);
	}
	
	

}