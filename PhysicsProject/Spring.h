#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Object.h"

class Spring
{
public:
	Spring(float _fStrength, float _fRestDist, Object* _objA, Object* _objB, b2World* world);
	~Spring();

	void Render(sf::RenderWindow& _renderWindow);


private:

	
	b2DistanceJointDef m_distanceJointDef;

	b2Joint* m_distanceJoint;

	Object* m_objA;
	Object* m_objB;

	sf::Vertex m_line[2];
};

