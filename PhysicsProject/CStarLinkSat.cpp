#include "CStarLinkSat.h"

CStarLinkSat::CStarLinkSat()
{
	m_EGameObjectType = EGAMEOBJECTTYPE::STARLINKSAT;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Asteroid.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);
}

CStarLinkSat::~CStarLinkSat()
{
	// b2Joint's deletion is done by the world
	if (m_pDistanceJoint != nullptr)
	{
		m_pBody->GetWorld()->DestroyJoint(m_pDistanceJoint);

		m_pDistanceJoint = nullptr;
	}
}

void CStarLinkSat::ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects)
{
	if (m_pBody != nullptr)
	{
		for (int i = 0; i < 6; i++)
		{
			CStarLinkSat* newStarLinkSat = new CStarLinkSat();

			sf::Vector2f v2fNewPosition = m_sprite.getPosition();
			v2fNewPosition.x -= float(i * 20);
			v2fNewPosition.y += float(i * 20);

			newStarLinkSat->Launch(_fScale, v2fNewPosition, *m_pBody->GetWorld());

			b2Vec2 v2fForce = m_pBody->GetLinearVelocity();
			v2fForce.x *= m_pBody->GetMass();
			v2fForce.y *= m_pBody->GetMass();

			newStarLinkSat->Getb2Body()->ApplyLinearImpulseToCenter(v2fForce, true);

			_vpGameObjects.push_back(newStarLinkSat);

			// Create distance joint
			m_distanceJointDef.bodyA = _vpGameObjects[_vpGameObjects.size() - 2]->Getb2Body();
			m_distanceJointDef.bodyB = _vpGameObjects[_vpGameObjects.size() - 1]->Getb2Body();

			m_distanceJointDef.localAnchorA = b2Vec2(0, 0);
			m_distanceJointDef.localAnchorB = b2Vec2(0, 0);

			m_distanceJointDef.length = 0.75f;
			m_distanceJointDef.minLength = 0.5f;
			m_distanceJointDef.maxLength = 1.0f;
			m_distanceJointDef.stiffness = 1000.0f;
			m_distanceJointDef.collideConnected = false;
			m_distanceJointDef.damping = 500.0f;

			m_pDistanceJoint = (b2DistanceJoint*)m_pBody->GetWorld()->CreateJoint(&m_distanceJointDef);
		}
	}


	return;
}
