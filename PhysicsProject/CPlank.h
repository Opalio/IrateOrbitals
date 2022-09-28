#pragma once
#include "CDestructable.h"
class CPlank
{
public:
    CPlank(std::vector<CGameObject*>& _vpGameObjects, std::vector<CDestructable*>& _vpDestructables, EGAMEOBJECTTYPE _EGameObjectType, sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld);
    ~CPlank();
private:

    // Deletion of these objects is not handled in this class
    // Update needs to keep track of if bodies have been destroyed so joints can be destroyed
    CPhysicsObject* m_apPhysicsObjects[5];

    b2WeldJointDef m_aWeldJointDefs[4];

    b2WeldJoint* m_pWeldJoint1 = nullptr;
    b2WeldJoint* m_pWeldJoint2 = nullptr;
    b2WeldJoint* m_pWeldJoint3 = nullptr;
    b2WeldJoint* m_pWeldJoint4 = nullptr;
};

