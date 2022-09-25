#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include "CAsteriod.h"

class Object;
class Catapult;
class Bird;

class Level
{
public:
	Level(float scale);
	~Level();

	void Render(sf::RenderWindow& window, float scale);
	void Update();

	void MouseButtonPressed(sf::RenderWindow& window);
	void MouseButtonReleased(float scale);
	void MouseMoved(sf::RenderWindow& window);

private:
	b2World* world;
	class ContactListener* contactListener = nullptr;


	Catapult* catapult;

	std::vector<Object*> objects;
	std::vector<Bird*> birds;

	// TEST ASTEROID
	CGameObject* asteroid;
};

