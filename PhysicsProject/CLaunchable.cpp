#include "CLaunchable.h"

CLaunchable::CLaunchable()
{
}

CLaunchable::~CLaunchable()
{
}

void CLaunchable::Launch(float _fScale, sf::Vector2f _v2fPosition, b2World& _world)
{
	// Box2d set up
	m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);
	//m_bodyDef.type = b2_dynamicBody;
	m_pBody = _world.CreateBody(&m_bodyDef);

	float fOriginX = (m_texture.getSize().x / 2);

	// Launchables are circles
	m_pShape = new b2CircleShape();
	m_pShape->m_radius = (fOriginX) / _fScale;
	m_fixtureDef.density = 5.0f;
	m_fixtureDef.shape = m_pShape;
	m_pBody->CreateFixture(&m_fixtureDef);

	m_pBody->GetUserData().pointer = (uintptr_t)this;

	return;
}

void CLaunchable::Render(sf::RenderWindow& _window, float _fScale)
{
	if (m_pBody != nullptr)
	{
		m_sprite.setPosition(m_pBody->GetPosition().x * _fScale, m_pBody->GetPosition().y * _fScale);
		m_sprite.setRotation(m_pBody->GetAngle() * 180 / b2_pi);
	}

	_window.draw(m_sprite);
}

void CLaunchable::ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects)
{
}
