#include "CPlank.h"
#include "CBox.h"
#include "CNuclearPasta.h"

CPlank::CPlank(std::vector<CGameObject*>& _vpGameObjects, std::vector<CDestructable*>& _vpDestructables, EGAMEOBJECTTYPE _EGameObjectType, sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld)
{
	// Create the object elements and push to relevent vectors
	if (_EGameObjectType == EGAMEOBJECTTYPE::BOX)
	{
		for (int i = 0; i < 5; i++)
		{
			CBox* newBox = new CBox(_v2fPosition, _fScale, _pWorld);
			m_apPhysicsObjects[i] = newBox;

			_vpGameObjects.push_back(newBox);
			_vpDestructables.push_back(newBox);
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			CNuclearPasta* newPasta = new CNuclearPasta(_v2fPosition, _fScale, _pWorld);
			m_apPhysicsObjects[i] = newPasta;

			_vpGameObjects.push_back(newPasta);
		}
	}

	// Create Welds Defs
	for (int i = 0; i < 4; i++)
	{
		m_aWeldJointDefs[i].bodyA = m_apPhysicsObjects[i]->Getb2Body();
		m_aWeldJointDefs[i].bodyB = m_apPhysicsObjects[i + 1]->Getb2Body();

		m_aWeldJointDefs[i].collideConnected = false;

		m_aWeldJointDefs[i].localAnchorA = b2Vec2(0.0f, 0.0f);
	}
	
}
