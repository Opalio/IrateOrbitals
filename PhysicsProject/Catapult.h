#pragma once

#include "SFML/Graphics.hpp"
//#include "box2d/box2d.h"

class Bird;
class b2World;
class Sling;

class Catapult
{
public:
	Catapult(sf::Vector2f position, float _scale, b2World* _world);

	void Render(sf::RenderWindow& window);

	void LoadBird(Bird* bird);
	void MoveBird(sf::RenderWindow& window);
	void LaunchBird(float scale, b2World& world);

	//void UpdateSling(sf::Vector2i _v2iMousePosition);

private:

	Bird* m_loadedBird;

	// Firing Variables
	sf::Vector2f firingOrigin;
	sf::Vector2f firingVector;

	// SFML Stuff
	sf::Sprite m_sprite;
	sf::Texture m_texture;


	//Sling* m_sling;
};

