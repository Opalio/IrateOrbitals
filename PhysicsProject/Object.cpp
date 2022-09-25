#include "Object.h"
#include <iostream> // for testing

Object::Object(sf::Vector2f position, float scale, b2BodyType bodyType, std::string spriteName, b2World* world)
{
	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/" + spriteName);
	m_sprite.setTexture(m_texture);
	float originX = (m_texture.getSize().x / 2);
	float originY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(originX, originY);

	// Box2d set up
	m_bodyDef.position = b2Vec2(position.x / scale, position.y / scale);
	m_bodyDef.type = bodyType;
	m_body = world->CreateBody(&m_bodyDef);

	m_shape.SetAsBox(originX / scale, originY / scale);
	m_fixtureDef.density = 1.0f;
	m_fixtureDef.restitution = 0.5f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);

	m_body->GetUserData().pointer = (uintptr_t)this;

}

void Object::Render(sf::RenderWindow& window, float scale)
{
	m_sprite.setPosition(m_body->GetPosition().x * scale, m_body->GetPosition().y * scale);
	m_sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);

	window.draw(m_sprite);
}

void Object::StartContact(Object* other)
{
	if (m_bodyDef.type == b2BodyType::b2_staticBody)
	{


		std::cout << "Floor Hit \n";
	}

	return;
}

void Object::EndContact(Object* other)
{
	std::cout << "Stop Hit \n";
	return;
}

void Object::PostSolve(const b2ContactImpulse* impulse)
{
	// Check force of collision
	std::cout << "Post solve Hit \n";

	return;
}
