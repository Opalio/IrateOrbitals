#pragma once
#include "Spring.h"
#include "Catapult.h"

class Sling
{
public:
	Sling(b2Vec2 _catapultPosition, float _scale, b2World* _world);
	~Sling();

	void Update(sf::Vector2i _v2iMousePosition);

	void Render(sf::RenderWindow& _renderWindow);

private:

	b2Vec2 m_v2StartPosition;
	b2Vec2 m_v2EndPosition;

	std::vector<Object> m_vSlingNodes;
	std::vector<Spring> m_vSpringJoints;
};

