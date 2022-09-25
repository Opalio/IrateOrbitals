#include "Level.h"

#include "Object.h"
#include "Catapult.h"
#include "Bird.h"
#include "ContactListener.h"


Level::Level(float scale)
{
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);

	// Create and bind the contact listener
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);

	// Static Floor
	objects.push_back(new Object(sf::Vector2f(480, 500),
					  scale,
					  b2BodyType::b2_staticBody,
					  "Ground.png",
					  world));

	// 3 dynamic 'balls'
	for (int i = 0; i < 3; i++)
	{
		objects.push_back(new Object(sf::Vector2f(550 + i * 100, 100), 
						  scale,
						  b2BodyType::b2_dynamicBody,
						  "Ball.png",
						  world));
	}

	catapult = new Catapult(sf::Vector2f(250, 410), scale, world);

	// TEST ASTEROID
	asteroid = CGameObject::CreateGameObject(EGAMEOBJECTTYPE::ASTERIOD, world, sf::Vector2f(100.0f, 100.0f), scale);
}

Level::~Level()
{
	// Delete all objects here

	// Delete contact listener
	if (contactListener != nullptr)
	{
		delete contactListener;
		contactListener = nullptr;
	}

	// Delete the world
	if (world != nullptr)
	{
		delete world;
		world = nullptr;
	}
}

void Level::Render(sf::RenderWindow& window, float scale)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(window, scale);
	}

	catapult->Render(window);

	for (size_t i = 0; i < birds.size(); i++)
	{
		birds[i]->Render(window, scale);
	}

	
	asteroid->Render(window, scale);
}

void Level::Update()
{
	world->Step(1 /60.f, 8, 3);
}

void Level::MouseButtonPressed(sf::RenderWindow& window)
{
	birds.push_back(new Bird());

	catapult->LoadBird(birds[birds.size() - 1]);

	catapult->MoveBird(window);

	//catapult->UpdateSling(sf::Mouse::getPosition(window));
}

void Level::MouseButtonReleased(float scale)
{
	catapult->LaunchBird(scale, *world);
}

void Level::MouseMoved(sf::RenderWindow& window)
{
	catapult->MoveBird(window);
}
