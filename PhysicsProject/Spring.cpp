#include "Spring.h"

Spring::Spring(float _fStrength, float _fRestDist, Object* _objA, Object* _objB, b2World* world)
{
	m_objA = _objA;
	m_objB = _objB;

	// Assign the two objects to be connected
	m_distanceJointDef.bodyA = _objA->Getb2Body();
	m_distanceJointDef.bodyB = _objB->Getb2Body();

	// Assign the two points on those bodies the joint runs between
	m_distanceJointDef.localAnchorA.Set(0.0, 0.0);
	m_distanceJointDef.localAnchorB.Set(0.0, 0.0);

	// Set the rest distance
	m_distanceJointDef.length = _fRestDist;

	// Bodies should have collision
	m_distanceJointDef.collideConnected = false; // set to false if making elastic rope

	// Strength should be relative to stiffness and dampening
	m_distanceJointDef.damping = 0.5;
	m_distanceJointDef.stiffness = _fStrength;
	

	m_distanceJoint = world->CreateJoint(&m_distanceJointDef);

	b2Vec2 v2Position = _objA->Getb2Body()->GetPosition();
	m_line[0].position = sf::Vector2f(v2Position.x, v2Position.y);
	m_line[0].color = sf::Color::Red;

	v2Position = _objB->Getb2Body()->GetPosition();
	m_line[1].position = sf::Vector2f(v2Position.x, v2Position.y);
	m_line[1].color = sf::Color::Red;
}

Spring::~Spring()
{
}

void Spring::Render(sf::RenderWindow& _renderWindow)
{
	// line positions are in render as movers still need to update positions
	b2Vec2 v2Position = m_objA->Getb2Body()->GetPosition();
	m_line[0].position = sf::Vector2f(v2Position.x, v2Position.y);

	v2Position = m_objB->Getb2Body()->GetPosition();
	m_line[1].position = sf::Vector2f(v2Position.x, v2Position.y);

	_renderWindow.draw(m_line, 4, sf::Lines);

	return;
}
