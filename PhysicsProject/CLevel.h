#pragma once
#include <queue>

#include "CGameObject.h"
#include "CLauncher.h"
#include "CContactListener.h"
#include "CPlanet.h"
#include "CDestructable.h"
#include "CPlank.h"

// For testing
#include "Object.h"


class CLevel
{
public:
	CLevel(float _fScale);
	~CLevel();

	// Display all objects to window
	void Render(sf::RenderWindow& _window, float _fScale);

	// Advance world by a step
	// Planets exert gravity
	// Planks cleanup
	// Destructable cleanup
	// Returns true if the level is won
	bool Update();

	// Functions to be called in sf::Event checking
	// MouseButtonPressed returns true if no lauchables left in queue and player trys to launch one
	bool MouseButtonPressed(sf::RenderWindow& _window, float _fScale);
	void MouseButtonReleased(float _fScale);
	void MouseMoved(sf::RenderWindow& _window);

	// Call before Loading each level except initial load of level 1
	void UnloadLevel();

	// Used to load each scene
	void LoadLevel1(float _fScale);
	void LoadLevel2(float _fScale);
	void LoadLevel3(float _fScale);

	int GetCurrentLevel() { return m_iCurrentLevel; }
	void SetCurrentLevel(int _iLevel) { m_iCurrentLevel = _iLevel; return; }

private:
	b2World* m_pWorld;
	CContactListener* m_pContactListener = nullptr;

	CLauncher* m_pLauncher;

	std::vector<CGameObject*> m_vpGameObjects;
	std::vector<CPlanet*> m_vpPlanets;
	std::vector<CDestructable*> m_vpDestructableObjects;
	std::vector<CPlank*> m_vpPlanks;

	std::queue<EGAMEOBJECTTYPE> m_qEGOTToLaunch;

	//std::vector<Object*> m_vpObjects;

	// Properly destroys objects that are a certain distance from the origin
	//void ClearFarAndMarkedObjects();

	// If destructableobject is marked for destruction call DestroyDestructable on it
	// If destructableobject vector has a nullptr erase it and resize vector
	void DestroyObjectsMarkedForDestruction();

	// Destroys gameobject and remove it from gameobject vector
	// Sets element in destructableobjectsvector to nullptr
	void DestroyDestructable(CDestructable* _pDestructable);

	// Used to control if level is complete
	int m_iEnemyCount = 0;

	// Used to control what level is loaded and if game is won
	int m_iCurrentLevel = 1;
	
	// Used to control if most recent launchables special ability has been activated
	bool m_bSpecialAbilityActivated = true;
	CLaunchable* m_pMostRecentlyLaunchedLaunchable = nullptr;

	//std::vector<CLaunchable*> m_vpLaunchables;
	//std::vector<Bird*> birds;
};

