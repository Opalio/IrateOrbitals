#include "Catapult.h"
#include "Bird.h"
#include "Sling.h"

Catapult::Catapult(sf::Vector2f position, float _scale, b2World* _world)
{
	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Catapult.png");
	m_sprite.setTexture(m_texture);
	float originX = (m_texture.getSize().x / 2);
	float originY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(originX, originY);

	m_sprite.setPosition(position);

	firingOrigin = position;
	firingOrigin.y -= m_texture.getSize().y / 2;

	m_loadedBird = nullptr;

	// Setup sling
	//m_sling = new Sling(b2Vec2(position.x, position.y), _scale, _world);
}

void Catapult::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	//m_sling->Render(window);
}

void Catapult::LoadBird(Bird* bird)
{
	m_loadedBird = bird;
}

void Catapult::MoveBird(sf::RenderWindow& window)
{
	if (m_loadedBird != nullptr)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		firingVector.x = mousePosition.x - firingOrigin.x;
		firingVector.y = mousePosition.y - firingOrigin.y;

		float length = sqrt(firingVector.x * firingVector.x + firingVector.y * firingVector.y);

		if (length > 100.0f)
		{
			firingVector = (firingVector / length) * 100.0f;
		}

		m_loadedBird->m_sprite.setPosition(firingOrigin + firingVector);
	}
}

void Catapult::LaunchBird(float scale, b2World& world)
{
	if (m_loadedBird != nullptr)
	{
		m_loadedBird->Launch(scale, m_loadedBird->m_sprite.getPosition(), world);
		

		float launchStrength = 5.0f;
		b2Vec2 b2LaunchVector;
		b2LaunchVector.x = firingVector.x * -1.0f * launchStrength;
		b2LaunchVector.y = firingVector.y * -1.0f * launchStrength;
		m_loadedBird->m_body->ApplyLinearImpulseToCenter(b2LaunchVector, true);
		m_loadedBird = nullptr;
	}
}

//void Catapult::UpdateSling(sf::Vector2i _v2iMousePosition)
//{
//	m_sling->Update(_v2iMousePosition);
//
//	return;
//}
