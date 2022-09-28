#include "CContactListener.h"

#include "box2d/b2_settings.h"

#include "CGameObject.h"

void CContactListener::BeginContact(b2Contact* contact)
{
	auto bodyuserdataA = (CGameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (CGameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->Getb2Body()->GetLinearVelocity();

		// TRY GET IMPACT FORCE USING POSTSOLVE OR PRESOLVE??

		bodyuserdataA->StartContact(bodyuserdataB);
		bodyuserdataB->StartContact(bodyuserdataA);

	}

	return;
}

void CContactListener::EndContact(b2Contact* contact)
{
	auto bodyuserdataA = (CGameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (CGameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->EndContact(bodyuserdataB);
		bodyuserdataB->EndContact(bodyuserdataA);
	}

	return;
}

void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	auto bodyuserdataA = (CGameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyuserdataB = (CGameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (bodyuserdataA && bodyuserdataB) // not null
	{
		bodyuserdataA->PostSolve(impulse);
		bodyuserdataB->PostSolve(impulse);
	}

	return;
}
