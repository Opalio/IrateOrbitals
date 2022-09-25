#include "CAsteriod.h"

CAsteriod::CAsteriod()
{
	m_EGameObjectType = EGAMEOBJECTTYPE::ASTERIOD;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Asteroid.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);

	//// Box2d set up
	//m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);
	//// Body type set in CPhysicsObject constructor
	//// m_bodyDef.type = _bodyType;
	//m_pBody = _pWorld->CreateBody(&m_bodyDef);

	//m_shape.SetAsBox(fOriginX / _fScale, fOriginY / _fScale);
	//m_fixtureDef.density = 1.0f;
	//m_fixtureDef.restitution = 0.5f;
	//m_fixtureDef.shape = &m_shape;
	//m_pBody->CreateFixture(&m_fixtureDef);

	//m_pBody->GetUserData().pointer = (uintptr_t)this;
}

CAsteriod::~CAsteriod()
{
}
