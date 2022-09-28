#pragma once

#include "CPhysicsObject.h"

class CDestructable :
    public CPhysicsObject
{
public:
    CDestructable();
    virtual ~CDestructable();

    void PostSolve(const b2ContactImpulse* _impulse);
};

