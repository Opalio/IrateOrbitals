#pragma once

#include "CGameObject.h"
#include "CLauncher.h"
#include "CContactListener.h"

// For testing
#include "Object.h"

class CLevel
{
public:
	CLevel(float _fScale);
	~CLevel();

	void Render(sf::RenderWindow& _window, float _fScale);
	void Update();

	void MouseButtonPressed(sf::RenderWindow& _window);
	void MouseButtonReleased(float _fScale);
	void MouseMoved(sf::RenderWindow& _window);

private:
	b2World* m_pWorld;
	CContactListener* m_pContactListener = nullptr;

	CLauncher* m_pLauncher;

	std::vector<CGameObject*> m_vpGameObjects;
	std::vector<Object*> m_vpObjects;

	//std::vector<CLaunchable*> m_vpLaunchables;
	//std::vector<Bird*> birds;
};

