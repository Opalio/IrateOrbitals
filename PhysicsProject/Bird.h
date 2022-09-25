#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Bird
{
public:
	Bird();

	void Render(sf::RenderWindow& window, float scale);

	void Launch(float scale, sf::Vector2f position, b2World& world);

	sf::Sprite m_sprite;
	b2Body* m_body;

private:
	// Box 2D Stuff
	b2BodyDef m_bodyDef;
	b2CircleShape m_shape;
	b2FixtureDef m_fixtureDef;

	// SFML Stuff

	sf::Texture m_texture;
};

