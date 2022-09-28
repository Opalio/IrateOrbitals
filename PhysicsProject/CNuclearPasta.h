#pragma once
#include "CIndestructable.h"
class CNuclearPasta :
	public CIndestructable
{
public:
	CNuclearPasta(sf::Vector2f _v2fPosition, float _fScale, b2World* _pWorld);
	~CNuclearPasta();


private:

};

