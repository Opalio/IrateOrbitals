#include "CGameObject.h"

// Includes for Factory Method
#include "CAsteriod.h"

CGameObject::CGameObject() //(sf::Vector2f _v2fPosition, float _fScale, b2BodyType _bodyType, std::string _sSpriteName, b2World* _pWorld)
{
	//// Set the sprite
	//m_texture.loadFromFile("Resources/Sprites/" + _sSpriteName);
	//m_sprite.setTexture(m_texture);
	//float fOriginX = (m_texture.getSize().x / 2);
	//float fOriginY = (m_texture.getSize().y / 2);
	//m_sprite.setOrigin(fOriginX, fOriginY);

	//// Box2d set up
	//m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);
	//m_bodyDef.type = _bodyType;
	//m_pBody = _pWorld->CreateBody(&m_bodyDef);

	//m_shape.SetAsBox(fOriginX / _fScale, fOriginY / _fScale);
	//m_fixtureDef.density = 1.0f;
	//m_fixtureDef.restitution = 0.5f;
	//m_fixtureDef.shape = &m_shape;
	//m_pBody->CreateFixture(&m_fixtureDef);

	//m_pBody->GetUserData().pointer = (uintptr_t)this;
}

CGameObject::~CGameObject()
{
	// b2Body's deletion is done by the world
	if (m_pBody != nullptr)
	{
		m_pBody->GetWorld()->DestroyBody(m_pBody);
	}
}

CGameObject* CGameObject::CreateGameObject(EGAMEOBJECTTYPE _EGameObjectType, b2World* _pWorld, sf::Vector2f _v2fPosition, float _fScale)
{
	switch (_EGameObjectType)
	{
	case EGAMEOBJECTTYPE::ASTERIOD:
		return new CAsteriod();
		break;
	case EGAMEOBJECTTYPE::LAUNCHABLE2:
		break;
	case EGAMEOBJECTTYPE::LAUNCHABLE3:
		break;
	case EGAMEOBJECTTYPE::ENEMY1:
		break;
	case EGAMEOBJECTTYPE::ENEMY2:
		break;
	case EGAMEOBJECTTYPE::ENEMY3:
		break;
	case EGAMEOBJECTTYPE::DESTRUCTABLE1:
		break;
	case EGAMEOBJECTTYPE::DESTRUCTABLE2:
		break;
	case EGAMEOBJECTTYPE::DESTRUCTABLE3:
		break;
	case EGAMEOBJECTTYPE::NUCLEARPASTA:
		break;
	case EGAMEOBJECTTYPE::PLANET:
		break;
	default:
		break;
	}
	return nullptr;
}

void CGameObject::Render(sf::RenderWindow& _window, float _fScale)
{
	m_sprite.setPosition(m_pBody->GetPosition().x * _fScale, m_pBody->GetPosition().y * _fScale);
	m_sprite.setRotation(m_pBody->GetAngle() * 180 / b2_pi);

	_window.draw(m_sprite);

	return;
}

void CGameObject::StartContact(CGameObject* _goOther)
{
	if (m_bodyDef.type == b2BodyType::b2_staticBody)
	{
		std::cout << "Floor Hit \n";
	}

	return;
}

void CGameObject::EndContact(CGameObject* _goOther)
{
	std::cout << "Stop Hit \n";
	return;
}

void CGameObject::PostSolve(const b2ContactImpulse* _impulse)
{
	// Check force of collision here
	std::cout << "Post solve Hit \n";

	return;
}
