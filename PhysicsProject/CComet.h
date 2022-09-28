#pragma once
#include "CLaunchable.h"
class CComet :
	public CLaunchable
{
public:
	CComet();
	~CComet();

	// Applys large force away from mouse
	void ActivateSpecialAbility(sf::RenderWindow& _window, float _fScale, std::vector<CGameObject*>& _vpGameObjects) override;


private:
};

