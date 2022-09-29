#include "CPlanet.h"

CPlanet::CPlanet(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld, std::string _sPlanetName, b2BodyType _bodyType, float _fPlanetScale)
{
	m_EGameObjectType = EGAMEOBJECTTYPE::PLANET;

	// Set the sprite
	m_texture.loadFromFile("Resources/Sprites/" + _sPlanetName);
	m_sprite.setTexture(m_texture);
	float fOriginX = (m_texture.getSize().x / 2);
	float fOriginY = (m_texture.getSize().y / 2);
	m_sprite.setOrigin(fOriginX, fOriginY);
	m_sprite.setScale(sf::Vector2f(_fPlanetScale, _fPlanetScale));

	// Box2d set up
	m_bodyDef.position = b2Vec2(_v2fPosition.x / _fScale, _v2fPosition.y / _fScale);

	// Nessessary to be dynamic so it has mass
	m_bodyDef.type = _bodyType;
	m_pBody = _pWorld->CreateBody(&m_bodyDef);

	m_pShape = new b2CircleShape();

	float fRadius = (m_texture.getSize().x * _fPlanetScale / 2);
	m_pShape->m_radius = (fRadius) / _fScale;

	m_fixtureDef.density = 5.0f;
	m_fixtureDef.shape = m_pShape;
	m_pBody->CreateFixture(&m_fixtureDef);

	m_pBody->GetUserData().pointer = (uintptr_t)this;

	m_fMass = fRadius / 1.5f;

	m_pOrbitalJoint = nullptr;
}

CPlanet::~CPlanet()
{
	// b2Joint's deletion is done by the world
	if (m_pOrbitalJoint != nullptr)
	{
		m_pBody->GetWorld()->DestroyJoint(m_pOrbitalJoint);

		m_pOrbitalJoint = nullptr;
	}
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

void CPlanet::GiveAsOrbital(b2Body* _pBodyThatWillOrbit, float _fSpeed, int _iDistance)
{
	m_revoluteJointDef.bodyA = m_pBody;
	m_revoluteJointDef.bodyB = _pBodyThatWillOrbit;
	m_revoluteJointDef.collideConnected = false;
	m_revoluteJointDef.localAnchorA.Set(0, 0);
	m_revoluteJointDef.localAnchorB.Set(0, _iDistance);
	m_revoluteJointDef.enableMotor = true;
	m_revoluteJointDef.maxMotorTorque = INTMAX_MAX;
	m_revoluteJointDef.motorSpeed = _fSpeed * (b2_pi / 180);//90 degrees per second

	m_pOrbitalJoint = (b2RevoluteJoint*)m_pBody->GetWorld()->CreateJoint(&m_revoluteJointDef);


	return;
}
