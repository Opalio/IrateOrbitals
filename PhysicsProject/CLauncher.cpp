#include "CLauncher.h"
#include "CLaunchable.h"

CLauncher::CLauncher(sf::Vector2f _v2fPosition)
{
	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Catapult.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);

	m_sprite.setPosition(_v2fPosition);

	m_v2fFiringOrigin = _v2fPosition;
	m_v2fFiringVector.y -= m_texture.getSize().y / 2;

	m_pLoadedLaunchable = nullptr;
}

CLauncher::~CLauncher()
{
}

void CLauncher::Render(sf::RenderWindow& window)
{
	window.draw(m_sprite);

	return;
}

void CLauncher::LoadLaunchable(CLaunchable* _launchable)
{
	m_pLoadedLaunchable = _launchable;

	return;
}

void CLauncher::MoveLaunchable(sf::RenderWindow& _window)
{
	if (m_pLoadedLaunchable != nullptr)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
		m_v2fFiringVector.x = mousePosition.x - m_v2fFiringOrigin.x;
		m_v2fFiringVector.y = mousePosition.y - m_v2fFiringOrigin.y;

		float length = sqrt(m_v2fFiringVector.x * m_v2fFiringVector.x + m_v2fFiringVector.y * m_v2fFiringVector.y);

		if (length > 100.0f)
		{
			m_v2fFiringVector = (m_v2fFiringVector / length) * 100.0f;
		}

		m_pLoadedLaunchable->GetSprite().setPosition(m_v2fFiringOrigin + m_v2fFiringVector);
	}

	return;
}

void CLauncher::LaunchLoaded(float _fScale, b2World& _world)
{
	if (m_pLoadedLaunchable != nullptr)
	{
		m_pLoadedLaunchable->Launch(_fScale, m_pLoadedLaunchable->GetSprite().getPosition(), _world);

		float fLaunchStrength = 5.0f;
		b2Vec2 b2LaunchVector;
		b2LaunchVector.x = m_v2fFiringVector.x * -1.0f * fLaunchStrength;
		b2LaunchVector.y = m_v2fFiringVector.y * -1.0f * fLaunchStrength;
		m_pLoadedLaunchable->Getb2Body()->ApplyLinearImpulseToCenter(b2LaunchVector, true);
		m_pLoadedLaunchable = nullptr;
	}

	return;
}
