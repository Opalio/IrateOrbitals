#pragma once

#include "CGameObject.h"

class CPhysicsObject :
	public CGameObject
{
public:
	// BodyDef type set to dynamic
	CPhysicsObject();
	virtual ~CPhysicsObject();
};

