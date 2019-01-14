#include "Game.h"

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(1280, 960), "AI LabCA1", sf::Style::Default)
{
	srand(time(NULL));
	for (int i = 0; i < 30; i++)
	{
		workers.push_back(new Worker());
		
	}
	for (int i = 0; i < 3; i++)
	{
		nests.push_back(new Nests());
	}

	m_player = new Player();
	//m_worker = new Worker();

	/*Enemy* m_pursue = new Pursue(*this);
	Enemy* m_arriveFast = new Arrive(60.0f, 100.0f, 100.0f);
	Enemy* m_arriveSlow = new Arrive(150.0f, 1720.0f, 1000.0f);
	Enemy* m_seek = new Seek();
	Enemy* m_wander = new Wander();*/

	//Factory* factory = new EnemyFactory;

	/*enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());*/

	//enemies.push_back(m_pursue);
	//enemies.push_back(m_arriveFast);
	//enemies.push_back(m_arriveSlow);
	//enemies.push_back(m_seek);
	////enemies.push_back(m_flee);
	//enemies.push_back(m_wander);
	miniMapView.setViewport(sf::FloatRect(0.64f, 0.02f, 0.3f, 0.3f));
	miniMapView.setSize(3750, 3750);
	miniMapView.setCenter(1875, 1875);

	gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
	gameView.setSize(1280, 960);
	gameView.setCenter(640, 480);
	//gameView.zoom(0.3f);

	m_Grid = new Grid();
	

}

/// <summary>
/// 
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

	while (m_window.isOpen())
	{
		ProcessEvents();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}

		render();
	}
}

void Game::ProcessEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(e);
	}
}

void Game::processGameEvents(sf::Event& event)
{
	//mouse.getPosition();
	m_mousePos = sf::Mouse::getPosition(m_window);

	//std::cout << "Current State :" << m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() << std::endl;
	if (m_mousePos.x > 0 && m_mousePos.x < m_window.getSize().x
		&& m_mousePos.y > 0 && m_mousePos.y < m_window.getSize().y)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_leftPress == false)
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_startTile != NULL)
			{
				m_startTile->setCurrentState(NONE);
			}

			if (m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() != OBSTACLE)
			{
				m_startTile = m_Grid->m_tileGrid[m_tilePosX][m_tilePosY];

				m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(START);

				//getPath(m_tilePosX, m_tilePosY);
				m_leftPress = true;
			}

		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_leftPress = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_rightPress == false && m_startTile != NULL)
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_goalTile != NULL)
			{
				m_goalTile->setCurrentState(NONE);
			}

			if (m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() != OBSTACLE)
			{
				m_goalTile = m_Grid->m_tileGrid[m_tilePosX][m_tilePosY];

				m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(GOAL);

				m_rightPress = true;

				m_Grid->initGrid(m_tilePosX, m_tilePosY);
			}

		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_rightPress = false;
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			m_tilePosX = static_cast<int>(m_mousePos.x / (m_tileSize * m_tileScale));
			m_tilePosY = static_cast<int>(m_mousePos.y / (m_tileSize * m_tileScale));


			if (m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->getCurrentState() == NONE)
			{
				m_Grid->m_tileGrid[m_tilePosX][m_tilePosY]->setCurrentState(OBSTACLE);
			}



		}


	}


}


/// <summary>
/// 
/// </summary>
void Game::update(double dt)
{
	m_player->update(dt);
	gameView.setCenter(m_player->getPosition());
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->update();
	}
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->update(m_player->getPosition());
	}

	//m_worker->update();

	//m_Grid->update(gameView);

	/*for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player->getVelocity());
		enemies[i]->collisionAvoidance(enemies);
	}*/
	//m_enemy->update(m_player->getPosition());
	//m_enemySeek->update(m_player->getPosition());

	//	m_enemyFlee->update(m_player->getPosition());
	//m_enemyPursue->update(m_player->getPosition(), m_player->getVelocity());

}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	//m_window.setView(follow);
	
	m_window.clear(sf::Color::White);
	m_window.setView(gameView);
	m_Grid->render(m_window, gameView, false);
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->render(m_window);
	}
	m_player->render(m_window);
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->render(m_window);
	}
	
	/*m_worker->render(m_window);*/

	m_window.setView(miniMapView);
	m_Grid->render(m_window, gameView, true);
	m_player->render(m_window);
	/*for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->render(m_window);
	}*/
	/*m_worker->render(m_window);*/
	//m_player->render(m_window);

	/*for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}*/
	//	m_enemyPursue->render(m_window);
	//m_enemy->render(m_window);
	//m_enemySeek->render(m_window);
	//m_enemyFlee->render(m_window);
	m_window.display();
}