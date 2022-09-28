#include "CComet.h"

CComet::CComet()
{
	m_EGameObjectType = EGAMEOBJECTTYPE::COMET;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Asteroid.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);
}

CComet::~CComet()
{
}

void CComet::ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects)
{
	if (m_pBody != nullptr)
	{
		sf::Vector2i v2iMousePosition = sf::Mouse::getPosition(_window);

		sf::Vector2f v2fCometPosition = m_sprite.getPosition();

		sf::Vector2f v2fMouseToCometVector = sf::Vector2f(v2fCometPosition.x - v2iMousePosition.x, v2fCometPosition.y - v2iMousePosition.y);

		float fLength = sqrt(v2fMouseToCometVector.x * v2fMouseToCometVector.x + v2fMouseToCometVector.y * v2fMouseToCometVector.y);

		// Normalise the vector
		v2fMouseToCometVector = v2fMouseToCometVector / fLength;

		// Create and calculate the force
		b2Vec2 v2fForce = b2Vec2(v2fMouseToCometVector.x, v2fMouseToCometVector.y);
		v2fForce *= 500.0f;

		// Apply force
		m_pBody->ApplyLinearImpulseToCenter(v2fForce, true);

		//m_v2fFiringVector.x = mousePosition.x - m_v2fFiringOrigin.x;
		//m_v2fFiringVector.y = mousePosition.y - m_v2fFiringOrigin.y;

		////float length = sqrt(m_v2fFiringVector.x * m_v2fFiringVector.x + m_v2fFiringVector.y * m_v2fFiringVector.y);

		//if (length > 100.0f)
		//{
		//	m_v2fFiringVector = (m_v2fFiringVector / length) * 100.0f;
		//}

		//m_pLoadedLaunchable->GetSprite().setPosition(m_v2fFiringOrigin + m_v2fFiringVector);
	}

	return;
}
