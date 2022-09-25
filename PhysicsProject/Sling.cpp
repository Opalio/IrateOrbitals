#include "Sling.h"

Sling::Sling(b2Vec2 _catapultPosition, float _scale, b2World* _world)
{
	m_v2StartPosition = b2Vec2(_catapultPosition.x - 10.0f, _catapultPosition.y + 20.0f);
	m_v2EndPosition = b2Vec2(_catapultPosition.x + 10.0f, _catapultPosition.y + 20.0f);

	for (int i = 0; i < 10; i++)
	{
		Object newSlingNode = Object(sf::Vector2f(m_v2StartPosition.x + i, m_v2StartPosition.y), _scale, b2BodyType::b2_staticBody, "SlingNode.png", _world);
		m_vSlingNodes.push_back(newSlingNode);
	}

	for (size_t i = 0; i < m_vSlingNodes.size() - 1; i++)
	{
		Spring newSpring = Spring(0.5, 10.0f, &m_vSlingNodes[i], &m_vSlingNodes[i + 1], _world);
		m_vSpringJoints.push_back(newSpring);
	}

	m_vSlingNodes[0].Getb2Body()->SetTransform(m_v2StartPosition, 0.0f);
	m_vSlingNodes[m_vSlingNodes.size() - 1].Getb2Body()->SetTransform(m_v2EndPosition, 0.0f);
}

Sling::~Sling()
{
}

void Sling::Update(sf::Vector2i _v2iMousePosition)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		m_vSlingNodes[int(m_vSlingNodes.size() / 2)].Getb2Body()->SetTransform(b2Vec2(_v2iMousePosition.x, _v2iMousePosition.y), 0.0f);
	}

	return;
}

void Sling::Render(sf::RenderWindow& _renderWindow)
{
	for (size_t i = 0; i < m_vSpringJoints.size(); i++)
	{
		m_vSpringJoints[i].Render(_renderWindow);
	}

	return;
}
