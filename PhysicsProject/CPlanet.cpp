#include "CPlanet.h"

CPlanet::CPlanet(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld)
{
	m_EGameObjectType = EGAMEOBJECTTYPE::PLANET;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/Ball.png");
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);

	// Box2d set up
	m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);

	// Nessessary to be dynamic so it has mass
	m_bodyDef.type = b2BodyType::b2_staticBody;
	m_pBody = _pWorld->CreateBody(&m_bodyDef);

	m_pShape = new b2CircleShape();

	float fRadius = (m_texture.getSize().x / 2);
	m_pShape->m_radius = (fRadius) / _fScale;

	m_fixtureDef.density = 5.0f;
	m_fixtureDef.shape = m_pShape;
	m_pBody->CreateFixture(&m_fixtureDef);

	m_pBody->GetUserData().pointer = (uintptr_t)this;
}

CPlanet::~CPlanet()
{
}

void CPlanet::ExertGravitationalForceOn(CGameObject* _pGameObject)
{
	if (_pGameObject->Getb2Body() != nullptr)
	{
		float fXDifference = m_pBody->GetTransform().p.x - _pGameObject->Getb2Body()->GetTransform().p.x;
		float fYDifference = m_pBody->GetTransform().p.y - _pGameObject->Getb2Body()->GetTransform().p.y;

		//|aShipToPlanet| = (G * mPlanet) / ((xShip- xPlanet)^2 + (yShip- yPlanet)^2)
		//G is gravitational constant
		float fAccelerationMagnitude = (m_fGravitationalConstant * m_fMass) / ((fXDifference * fXDifference) + (fYDifference * fYDifference));

		//std::cout << "mass: " << m_fMass << std::endl;
		//aShipToPlanet(unit vector) = <(xPlanet - xShip) / sqrt((xShip - xPlanet)^2 + (yShip - yPlanet)^2), (yPlanet - yShip) / sqrt((xShip - xPlanet)^2 + (yShip - yPlanet)^2)>
		sf::Vector2f v2fAccelerationDirection = sf::Vector2f(fXDifference / sqrtf((fXDifference * fXDifference) + (fYDifference * fYDifference)), fYDifference / sqrtf((fXDifference * fXDifference) + (fYDifference * fYDifference)));
		//v2fAccelerationDirection *= -1.0f;

		sf::Vector2f v2fAccelerationTowardsPlanet = fAccelerationMagnitude * v2fAccelerationDirection;

		// As force required - F = ma
		b2Vec2 v2fForce = _pGameObject->Getb2Body()->GetMass() * b2Vec2(v2fAccelerationTowardsPlanet.x, v2fAccelerationTowardsPlanet.y);

		//std::cout << v2fForce.x << ", " << v2fForce.y << std::endl;

		_pGameObject->Getb2Body()->ApplyLinearImpulseToCenter(v2fForce, true);
	}
	

	//*m_acceleration += v2fAccelerationTowardsEntity;
	return;




	//m_pLoadedLaunchable->Getb2Body()->ApplyLinearImpulseToCenter(b2LaunchVector, true);
}
