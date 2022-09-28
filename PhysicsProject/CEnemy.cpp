#include "CEnemy.h"

CEnemy::CEnemy(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld)
{
	m_EGameObjectType = EGAMEOBJECTTYPE::ENEMY;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Enemy.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);

	// Box2d set up
	m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);

	// Set in Physics Object
	//m_bodyDef.type = b2BodyType::b2_dynamicBody;

	m_pBody = _pWorld->CreateBody(&m_bodyDef);

	// Because square

	// Nessesary to be able to call SetAsBox
	b2PolygonShape* pPolyShape = new b2PolygonShape();
	pPolyShape->SetAsBox(fOriginX / _fScale, fOriginY / _fScale);

	m_pShape = pPolyShape;
	m_fixtureDef.shape = m_pShape;

	m_fixtureDef.density = 5.0f;
	m_fixtureDef.restitution = 0.5f;
	m_fixtureDef.shape = m_pShape;
	m_pBody->CreateFixture(&m_fixtureDef);

	m_pBody->GetUserData().pointer = (uintptr_t)this;
}

CEnemy::~CEnemy()
{
}
