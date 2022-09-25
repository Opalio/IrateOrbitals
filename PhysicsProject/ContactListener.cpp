#include "ContactListener.h"

#include "box2d/b2_settings.h"
#include "Object.h"


void ContactListener::BeginContact(b2Contact* contact)
{
	auto bodyuserdataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->Getb2Body()->GetLinearVelocity();

		// TRY GET IMPACT FORCE USING POSTSOLVE OR PRESOLVE??

		bodyuserdataA->StartContact(bodyuserdataB);
		bodyuserdataB->StartContact(bodyuserdataA);

	}

	return;
}

void ContactListener::EndContact(b2Contact* contact)
{
	auto bodyuserdataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->EndContact(bodyuserdataB);
		bodyuserdataB->EndContact(bodyuserdataA);
	}

	return;
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	auto bodyuserdataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->PostSolve(impulse);
		bodyuserdataB->PostSolve(impulse);
	}

	return;
}
