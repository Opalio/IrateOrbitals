#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Object
{
public:

	Object(sf::Vector2f position, float scale, b2BodyType bodyType, std::string spriteName, b2World* world);

	void Render(sf::RenderWindow& window, float scale);

	b2Body* Getb2Body() { if (m_body != nullptr) { return m_body; } }

	virtual void StartContact(Object* other);
	virtual void EndContact(Object* other);
	virtual void PostSolve(const b2ContactImpulse* impulse);


private:
	// Box 2D Stuff
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;

	// SFML Stuff
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

