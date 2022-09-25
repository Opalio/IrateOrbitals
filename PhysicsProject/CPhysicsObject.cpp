#include "CPhysicsObject.h"

CPhysicsObject::CPhysicsObject()
{
	m_bodyDef.type = b2BodyType::b2_dynamicBody;
}

CPhysicsObject::~CPhysicsObject()
{
}
