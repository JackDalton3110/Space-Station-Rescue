#include "Game.h"

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(1280, 960), "AI LabCA1", sf::Style::Default)
{
	srand(time(NULL));

	m_Grid = new Grid();
/*
	for (int i = 0; i < 30; i++)
	{
		workers.push_back(new Worker(*m_Grid));
		
	}*/
	

	
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


	

	m_player = new Player(*m_Grid);

	if (!m_playerMMT.loadFromFile("./resources/PlayerMiniMap.png")) {
		//do something
	}

	if (!m_predatorMMT.loadFromFile("./resources/PredatorMiniMap.png")) {
		//do something
	}


	if (!m_MMT.loadFromFile("./resources/MiniMap.png")) {
		//do something
	}

	for (int i = 0; i < 3; i++)
	{


		spawnSpot = rand() % 5;


		while ((std::find(usedSpawns.begin(), usedSpawns.end(), spawnSpot) != usedSpawns.end()))
		{
			spawnSpot = rand() % 5;
		}
		nests.push_back(new Nests(spawnSpot, *m_Grid));
		
		/*m_predatorMM.setTexture(m_predatorMMT);
		m_predatorMM.setOrigin(m_predatorMM.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);*/
		//predSprite.push_back(m_predatorMM);

		usedSpawns.push_back(spawnSpot);
		




	}

	for (int i = 0; i < nests.size(); i++) {
		predators.push_back(new Predator(nests[i]->getPosition().x, nests[i]->getPosition().y, *m_Grid));
	}
	
	m_playerMM.setTexture(m_playerMMT);
	m_playerMM.setOrigin(m_playerMM.getTextureRect().width / 2, m_playerMM.getTextureRect().height / 2);

	/*m_predatorMM.setTexture(m_predatorMMT);
	m_predatorMM.setOrigin(m_predatorMM.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);

	m_predatorMM2.setTexture(m_predatorMMT);
	m_predatorMM2.setOrigin(m_predatorMM2.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);

	m_predatorMM3.setTexture(m_predatorMMT);
	m_predatorMM3.setOrigin(m_predatorMM3.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);*/
	
	m_MM.setTexture(m_MMT);


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

			//	m_Grid->initGrid(m_tilePosX, m_tilePosY);
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
	m_playerMM.setPosition(m_player->getPosition());
	m_playerMM.setRotation(m_player->getRotation());
	/*m_predatorMM.setPosition(predators[1]->getPosition());
	m_predatorMM.setRotation(predators[1]->getRotation());

	m_predatorMM2.setPosition(predators[2]->getPosition());
	m_predatorMM2.setRotation(predators[2]->getRotation());

	m_predatorMM3.setPosition(predators[3]->getPosition());
	m_predatorMM3.setRotation(predators[3]->getRotation());*/

	/*for (int i = 0; i < predSprite.size(); i++)
	{
		predSprite[i].setPosition(predators[i]->getPosition());
		predSprite[i].setRotation(predators[i]->getRotation());
	}*/
	m_player->update(dt);
	gameView.setCenter(m_player->getPosition());
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->update();
	}
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->update(*m_player, dt);
	}
	for (int i = 0; i < predators.size(); i++) 
	{
		predators[i]->update(dt);
	}
	if (m_player->pGridX != previousX || m_player->pGridY != previousY)
	{
		m_Grid->updateCost(m_player->pGridX, m_player->pGridY);
		previousX = m_player->pGridX;
		previousY = m_player->pGridY;
	}
	
	//m_predator->update(dt);
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
	
	m_window.clear(sf::Color(45, 45, 45));
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

	for (int i = 0; i < predators.size(); i++)
	{
		predators[i]->render(m_window);
	}

	m_window.setView(miniMapView);

	m_window.draw(m_MM);
	for (int i = 0; i < m_Grid->m_spawnPoints.size(); i++) {
		m_Grid->m_spawnPoints[i]->render(m_window);
	}

	//for (int i = 0; i < m_Grid->m_nestPoints.size(); i++) {
	//	m_Grid->m_nestPoints[i]->render(m_window);
	//}

	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->render(m_window);
	}
	/*for (int i = 0; i < predSprite.size(); i++)
	{
		m_window.draw(predSprite[i]);
	}*/
	/*m_window.draw(m_playerMM);
	m_window.draw(m_predatorMM);
	m_window.draw(m_predatorMM2);
	m_window.draw(m_predatorMM3);*/

	//for (int i = 0; i < workers.size(); i++)
	//{
		//workers[i]->render(m_window);
	//}
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