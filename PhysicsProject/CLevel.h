#pragma once

#include "CGameObject.h"
#include "CLauncher.h"
#include "CContactListener.h"
#include "CPlanet.h"
#include "CDestructable.h"

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
	std::vector<CPlanet*> m_vpPlanets;
	std::vector<CDestructable*> m_vpDestructableObjects;

	std::vector<Object*> m_vpObjects;

	// If destructableobject is marked for destruction call DestroyDestructable on it
	// If destructableobject vector has a nullptr erase it and resize vector
	void DestroyObjectsMarkedForDestruction();

	// Destroys gameobject and remove it from gameobject vector
	// Sets element in destructableobjectsvector to nullptr
	void DestroyDestructable(CDestructable* _pDestructable);

	//std::vector<CLaunchable*> m_vpLaunchables;
	//std::vector<Bird*> birds;
};

