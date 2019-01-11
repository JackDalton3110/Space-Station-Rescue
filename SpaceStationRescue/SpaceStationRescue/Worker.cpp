#include "Worker.h"

Worker::Worker():
	velocity(0,0),
	maxSpeed(2.0f),
	maxRotation(360),
	rotation(90)
{
	float x = rand() % 800 + 300;
	float y = rand() % 800 + 300;
	m_position.x = x;
	m_position.y = y;
	

	if (!workerTxt.loadFromFile("./resources/worker.png"))
	{
		std::cout << "Cannot load worker image" << std::endl;
	}

	workerSprite.setTexture(workerTxt);
	workerSprite.setPosition(m_position);
	workerSprite.setRotation(rotation);
	workerSprite.setScale(0.3, 0.3);
	workerSprite.setOrigin(workerSprite.getTextureRect().width / 2, workerSprite.getTextureRect().height / 2);
	velocity.x = getRandom(20, -10);
	velocity.y = getRandom(20, -10);
}

Worker::~Worker()
{

}

void Worker::update()
{

	/*if (enemy.getPosition().x < -100)
	{
		enemy.setPosition(1550, enemy.getPosition().y);
		velocity.x = rand() % 20 - 10;
		velocity.x = velocity.x / 100;
		velocity.y = rand() % 20 - 10;
		velocity.y = velocity.y / 100;

	}

	if (enemy.getPosition().x > 1600)
	{
		enemy.setPosition(-90, enemy.getPosition().y);
		velocity.x = rand() % 20 - 10;
		velocity.x = velocity.x / 100;
		velocity.y = rand() % 20 - 10;
		velocity.y = velocity.y / 100;

	}

	if (enemy.getPosition().y < -100)
	{
		enemy.setPosition(enemy.getPosition().x, 1550);

		velocity.x = rand() % 20 - 10;
		velocity.x = velocity.x / 100;
		velocity.y = rand() % 20 - 10;
		velocity.y = velocity.y / 100;
	}

	if (enemy.getPosition().y > 1600)
	{
		enemy.setPosition(enemy.getPosition().x, -90);

		velocity.x = rand() % 20 - 10;
		velocity.x = velocity.x / 100;
		velocity.y = rand() % 20 - 10;
		velocity.y = velocity.y / 100;
	}*/

	workerSprite.setPosition(enemy.getPosition().x, enemy.getPosition().y);
	m_position.x += velocity.x * 30 / 100;
	m_position.y += velocity.y * 30 / 100;
	enemy.setPosition(m_position.x, m_position.y);
	rotateWorker(velocity, rotation);

	workerSprite.setRotation(rotation);
	if (count >= 4)
	{
		velocity.x = rand() % 10 - 5;
		velocity.y = rand() % 10 - 5;
		count = 0;
	}

	count++;

}

float Worker::getRandom(int x, int y)
{
	//srand(time(NULL));
	float randVal = rand() % x + y;
	return randVal;
}

int Worker::rotateWorker(sf::Vector2f vel, int angle)
{
	if (vel.x > 0 && angle < 80)
	{
		rotation += 10;
	}
	else if (vel.x > 0 && angle > 100)
	{
		rotation -= 10;
	}

	if (vel.x > 0 && vel.y > 0 && angle<130)
	{
		rotation += 10;
	}
	else if (vel.x > 0 && vel.y>0 && angle > 140)
	{
		rotation -= 10;
	}

	if (vel.y > 0 && angle < 170)
	{
		rotation += 10;
	}
	else if (vel.y > 0 && angle > 190)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && vel.y > 0 && angle <215)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && vel.y>0 && angle > 235)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && angle <260)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && angle > 280)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && vel.y < 0 && angle <305)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && vel.y < 0 && angle > 325)
	{
		rotation -= 10;
	}

	if (vel.y < 0 && angle < 350)
	{
		rotation += 10;
	}
	else if (vel.y < 0 && angle > 10)
	{
		rotation -= 10;
	}

	if (vel.x > 0 && vel.y < 0  && angle < 35)
	{
			rotation += 10;
	}
	else if (vel.x > 0 && vel.y < 0  && angle > 55)
	{
		rotation -= 10;
	}
	std::cout << rotation << std::endl;
	return rotation;
	
}

void Worker::respawn(float x, float y)
{

}

void Worker::render(sf::RenderWindow &window)
{
	window.draw(workerSprite);
}

