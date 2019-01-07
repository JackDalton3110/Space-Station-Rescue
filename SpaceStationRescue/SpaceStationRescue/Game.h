#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
//#include "Player.h"
//#include "Enemy.h"
//#include "Pursue.h"
//#include "Arrive.h"
//#include "Flee.h"
//#include "Seek.h"
//#include "Wander.h"
#include "Grid.h"


class Game
{
public:
	Game();
	void run();

private:
	void update(double dt);
	void render();

protected:
	sf::RenderWindow m_window;
	/*Player* m_player;*/

	//Enemy* m_pursue;

	//std::vector<Enemy*> enemies;
	Grid *m_Grid;
	sf::View gameView;
	sf::View miniMapView;
	sf::View follow;

};
#endif // !GAME