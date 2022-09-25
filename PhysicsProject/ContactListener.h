#pragma once

//#include "box2d/box2d.h"
#include "box2d/b2_world_callbacks.h"

class ContactListener : public b2ContactListener
{

public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:

};

