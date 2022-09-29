#include "CDestructable.h"

CDestructable::CDestructable()
{
}

CDestructable::~CDestructable()
{
}

void CDestructable::PostSolve(const b2ContactImpulse* _impulse)
{
	/*std::cout << "count: " << _impulse->count << std::endl;
	std::cout << "normalImpulse: " << *_impulse->normalImpulses << std::endl;
	std::cout << "tangentImpulse: " << *_impulse->tangentImpulses << std::endl;*/

	if (*_impulse->normalImpulses >= 80.0f)
	{
		m_bShouldDestroy = true;
		//std::cout << m_bShouldDestroy << std::endl;
	}

	return;
}
