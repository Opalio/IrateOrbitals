#include "CPlank.h"
#include "CBox.h"
#include "CNuclearPasta.h"

CPlank::CPlank(std::vector<CGameObject*>& _vpGameObjects, std::vector<CDestructable*>& _vpDestructables, EGAMEOBJECTTYPE _EGameObjectType, sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld)
{
	m_pWorld = _pWorld;
	// Create the object elements and push to relevent vectors
	if (_EGameObjectType == EGAMEOBJECTTYPE::BOX)
	{
		for (int i = 0; i < 5; i++)
		{
			//CBox* newBox = new CBox(sf::Vector2f(_v2fPosition.x + i * _fSpacing, _v2fPosition.y), _fScale, _pWorld);
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
			//CNuclearPasta* newPasta = new CNuclearPasta(sf::Vector2f(_v2fPosition.x + i * _fSpacing, _v2fPosition.y), _fScale, _pWorld);
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
		m_aWeldJointDefs[i].localAnchorB = b2Vec2(1.0f, 0.0f);
		m_aWeldJointDefs[i].referenceAngle = 0.0f;
		m_aWeldJointDefs[i].stiffness = b2_maxFloat;
		m_aWeldJointDefs[i].damping = 1000.0f;
	}
	
	// Create Weld Joints
	m_pWeldJoint1 = (b2WeldJoint*)m_apPhysicsObjects[0]->Getb2Body()->GetWorld()->CreateJoint(&m_aWeldJointDefs[0]);
	m_pWeldJoint2 = (b2WeldJoint*)m_apPhysicsObjects[0]->Getb2Body()->GetWorld()->CreateJoint(&m_aWeldJointDefs[1]);
	m_pWeldJoint3 = (b2WeldJoint*)m_apPhysicsObjects[0]->Getb2Body()->GetWorld()->CreateJoint(&m_aWeldJointDefs[2]);
	m_pWeldJoint4 = (b2WeldJoint*)m_apPhysicsObjects[0]->Getb2Body()->GetWorld()->CreateJoint(&m_aWeldJointDefs[3]);
}

CPlank::~CPlank()
{

	//if (m_pWeldJoint1 != nullptr)
	//{
	//	m_pWorld->DestroyJoint(m_pWeldJoint1);

	//	//m_pWeldJoint1 = nullptr;
	//}

	//if (m_pWeldJoint2 != nullptr)
	//{
	//	m_pWorld->DestroyJoint(m_pWeldJoint2);

	//	//m_pWeldJoint2 = nullptr;
	//}

	//if (m_pWeldJoint3 != nullptr)
	//{
	//	m_pWorld->DestroyJoint(m_pWeldJoint3);

	//	//m_pWeldJoint3 = nullptr;
	//}

	//if (m_pWeldJoint4 != nullptr)
	//{
	//	m_pWorld->DestroyJoint(m_pWeldJoint4);

	//	//m_pWeldJoint4 = nullptr;
	//}



	/*for (int i = 0; i < 4; i++)
	{
		if (m_apPhysicsObjects[i] != nullptr)
		{
			m_apPhysicsObjects[i]->SetShouldDestroy(true);
		}
	}*/

	//Update();

	//// If weld joint 1 exists then m_apPhysicsObjects exists
	//if (m_pWeldJoint1 != nullptr)
	//{
	//	m_apPhysicsObjects[0]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint1);

	//	m_pWeldJoint1 = nullptr;
	//}

	//if (m_pWeldJoint2 != nullptr)
	//{
	//	m_apPhysicsObjects[1]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint2);

	//	m_pWeldJoint2 = nullptr;
	//}

	//if (m_pWeldJoint3 != nullptr)
	//{
	//	m_apPhysicsObjects[2]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint3);

	//	m_pWeldJoint3 = nullptr;
	//}

	//if (m_pWeldJoint4 != nullptr)
	//{
	//	m_apPhysicsObjects[3]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint4);

	//	m_pWeldJoint4 = nullptr;
	//}
}

//void CPlank::Update()
//{
//	for (size_t i = 0; i < 5; i++)
//	{
//		if (m_apPhysicsObjects[i] != nullptr)
//		{
//			// Delete joint
//			if (m_apPhysicsObjects[i]->GetShouldDestroy())
//			{
//				if (i == 0)
//				{
//					if (m_pWeldJoint1 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint1);
//						m_pWeldJoint1 = nullptr;
//					}
//					
//					m_apPhysicsObjects[i] = nullptr;
//				}
//				else if (i == 1)
//				{
//					if (m_pWeldJoint1 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint1);
//						m_pWeldJoint1 = nullptr;
//					}
//					
//					if (m_pWeldJoint2 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint2);
//						m_pWeldJoint2 = nullptr;
//					}
//
//					m_apPhysicsObjects[i] = nullptr;
//				}
//				else if (i == 2)
//				{
//					if (m_pWeldJoint2 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint2);
//						m_pWeldJoint2 = nullptr;
//					}
//
//					if (m_pWeldJoint3 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint3);
//						m_pWeldJoint3 = nullptr;
//					}
//
//					m_apPhysicsObjects[i] = nullptr;
//				}
//				else if (i == 3)
//				{
//					if (m_pWeldJoint3 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint3);
//						m_pWeldJoint3 = nullptr;
//					}
//
//					if (m_pWeldJoint4 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint4);
//						m_pWeldJoint4 = nullptr;
//					}
//
//					m_apPhysicsObjects[i] = nullptr;
//				}
//				else if (i == 4)
//				{
//					if (m_pWeldJoint4 != nullptr)
//					{
//						m_apPhysicsObjects[i]->Getb2Body()->GetWorld()->DestroyJoint(m_pWeldJoint4);
//						m_pWeldJoint4 = nullptr;
//					}
//
//					m_apPhysicsObjects[i] = nullptr;
//				}
//			}
//		}
//	}
//
//	return;
//}
