#include "HealthSystem.h"
HealthSystem::HealthSystem() :
	m_position(700, 550),
	m_healthValue(3.0f)
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

	outerRect.setSize(sf::Vector2f(200, 30));
	outerRect.setOutlineColor(sf::Color::Red);
	outerRect.setOutlineThickness(5);
	outerRect.setFillColor(sf::Color::White);
	outerRect.setPosition(m_position);

	innerRect.setSize(sf::Vector2f(200, 30));
	innerRect.setOutlineColor(sf::Color::Red);
	outerRect.setFillColor(sf::Color::Red);
	innerRect.setOutlineThickness(5);
	innerRect.setPosition(m_position);


}

HealthSystem::~HealthSystem()
{

}
void HealthSystem::update()
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
	case 0:
		healthSprite.setTexture(health0_0Txt);
		break;
	default:
		break;
	}


}

void HealthSystem::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}


void HealthSystem::render(sf::RenderWindow &window)
{
	healthSprite.setPosition(m_position);
	window.draw(healthSprite);

}