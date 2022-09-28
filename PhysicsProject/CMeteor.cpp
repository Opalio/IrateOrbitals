#include "CMeteor.h"

CMeteor::CMeteor()
{
	m_EGameObjectType = EGAMEOBJECTTYPE::METEOR;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Asteroid.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);
}

CMeteor::~CMeteor()
{
}

void CMeteor::ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects)
{
	if (m_pBody != nullptr)
	{
		for (int i = 0; i < 2; i++)
		{
			CMeteor* newMeteor = new CMeteor();

			sf::Vector2f v2fNewPosition = m_sprite.getPosition();
			v2fNewPosition.x += float(i * 20);
			v2fNewPosition.y += float(i * 20);

			newMeteor->Launch(_fScale, v2fNewPosition, *m_pBody->GetWorld());

			b2Vec2 v2fForce = m_pBody->GetLinearVelocity();
			v2fForce.x *= m_pBody->GetMass();
			v2fForce.y *= m_pBody->GetMass();

			newMeteor->Getb2Body()->ApplyLinearImpulseToCenter(v2fForce, true);

			_vpGameObjects.push_back(newMeteor);
		}
	}
	

	return;
}
