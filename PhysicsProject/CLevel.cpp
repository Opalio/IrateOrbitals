#include "CLevel.h"
#include "CAsteriod.h"
#include "CNuclearPasta.h"
#include "CEnemy.h"
#include "CComet.h"
#include "CMeteor.h"
#include "CStarLinkSat.h"
#include "CBox.h"

CLevel::CLevel(float _fScale)
{
	LoadLevel1(_fScale);
	//b2Vec2 b2v2Gravity(0.0f, 0.0f);
	//m_pWorld = new b2World(b2v2Gravity);

	//// Create and bind the contact listener
	//m_pContactListener = new CContactListener();
	//m_pWorld->SetContactListener(m_pContactListener);

	//// Static Floor
	////m_vpObjects.push_back(new Object(sf::Vector2f(480, 500), _fScale, b2BodyType::b2_staticBody, "Ground.png", m_pWorld));

	////// 3 dynamic 'balls'
	////for (int i = 0; i < 1; i++)
	////{
	////	m_vpObjects.push_back(new Object(sf::Vector2f(550 + i * 100, 100), _fScale, b2BodyType::b2_dynamicBody, "Ball.png", m_pWorld));
	////}

	//// Planet

	//

	//CPlanet* newPlanet = new CPlanet(sf::Vector2f(1000, 500), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_staticBody, 1.0f);
	//m_vpPlanets.push_back(newPlanet);
	//m_vpGameObjects.push_back(newPlanet);

	//CPlanet* newPlanet2 = new CPlanet(sf::Vector2f(750, 250), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_dynamicBody, 0.5f);
	//m_vpPlanets.push_back(newPlanet2);
	//m_vpGameObjects.push_back(newPlanet2);

	//CPlanet* newPlanet3 = new CPlanet(sf::Vector2f(100, 100), _fScale, m_pWorld, "Ball.png", b2BodyType::b2_dynamicBody, 1.0f);
	//m_vpPlanets.push_back(newPlanet3);
	//m_vpGameObjects.push_back(newPlanet3);

	//

	//newPlanet->GiveAsOrbital(newPlanet2->Getb2Body(), 25, 20);
	//newPlanet2->GiveAsOrbital(newPlanet3->Getb2Body(), 90, 10);

	//for (int i = 0; i < 10; i++)
	//{
	//	m_vpGameObjects.push_back(new CNuclearPasta(sf::Vector2f(500 - i * 2, 500 - i * 2), _fScale, m_pWorld));
	//}

	//for (int i = 0; i < 15; i++)
	//{
	//	CDestructable* newBox = new CBox(sf::Vector2f(500 + i * 2, 500 + i * 2), _fScale, m_pWorld);
	//	m_vpGameObjects.push_back(newBox);
	//	m_vpDestructableObjects.push_back(newBox);
	//}

	//for (int i = 0; i < 20; i++)
	//{
	//	CDestructable* newEnemy = new CEnemy(sf::Vector2f(500 + i * 2, 300 + i * 2), _fScale, m_pWorld);

	//	m_vpGameObjects.push_back(newEnemy);
	//	m_vpDestructableObjects.push_back(newEnemy);

	//	m_iEnemyCount++;

	//}

	//m_vpPlanks.push_back(new CPlank(m_vpGameObjects, m_vpDestructableObjects, EGAMEOBJECTTYPE::BOX, sf::Vector2f(100.0f, 100.0f), _fScale, m_pWorld));
	//

	//m_pLauncher = new CLauncher(sf::Vector2f(250, 410));
}

CLevel::~CLevel()
{
	// Delete all objects
	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		delete m_vpGameObjects[i];
		m_vpGameObjects[i] = nullptr;
	}

	m_vpGameObjects.clear();
	m_vpDestructableObjects.clear();
	m_vpPlanets.clear();

	for (size_t i = 0; i < m_vpPlanks.size(); i++)
	{
		delete m_vpPlanks[i];
		m_vpPlanks[i] = nullptr;
	}
	m_vpPlanks.clear();

	// Delete launcher
	if (m_pLauncher != nullptr)
	{
		delete m_pLauncher;
		m_pLauncher = nullptr;
	}

	// Delete contact listener
	if (m_pContactListener != nullptr)
	{
		delete m_pContactListener;
		m_pContactListener = nullptr;
	}

	// Delete the world
	if (m_pWorld != nullptr)
	{
		delete m_pWorld;
		m_pWorld = nullptr;
	}
}

void CLevel::Render(sf::RenderWindow& _window, float _fScale)
{
	m_pLauncher->Render(_window);

	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		m_vpGameObjects[i]->Render(_window, _fScale);
	}

	/*for (size_t i = 0; i < m_vpLaunchables.size(); i++)
	{
		m_vpLaunchables[i]->Render(_window, _fScale);
	}*/

	

	return;
}

bool CLevel::Update()
{
	m_pWorld->Step(1 / 60.f, 8, 3);

	/*for (size_t i = 0; i < m_vpObjects.size(); i++)
	{
		std::cout << m_vpObjects[i]->Getb2Body()->GetTransform().p.x << ", " << m_vpObjects[i]->Getb2Body()->GetTransform().p.y << std::endl;
	}*/

	for (size_t i = 0; i < m_vpPlanets.size(); i++)
	{
		for (size_t j = 0; j < m_vpGameObjects.size(); j++)
		{
			if (m_vpGameObjects[j]->GetObjectType() != EGAMEOBJECTTYPE::PLANET)
			{
				m_vpPlanets[i]->ExertGravitationalForceOn(m_vpGameObjects[j]);
			}
		}
	}

	//for (size_t i = 0; i < m_vpPlanks.size(); i++)
	//{
	//	m_vpPlanks[i]->Update();
	//}

	//ClearFarAndMarkedObjects();

	DestroyObjectsMarkedForDestruction();

	if (m_iEnemyCount <= 0)
	{
		m_iCurrentLevel++;
		return true;
	}
	else
	{
		return false;
	}
}

bool CLevel::MouseButtonPressed(sf::RenderWindow& _window, float _fScale)
{
	if (m_bSpecialAbilityActivated) // If true then new lauchable should be created
	{
		CLaunchable* pNewLauchable = nullptr;

		if (m_qEGOTToLaunch.size() > 0)
		{
			pNewLauchable = CLaunchable::CreateLaunchable(m_qEGOTToLaunch.front());
			m_qEGOTToLaunch.pop();
		}
		else
		{
			return true;
		}
		

		m_vpGameObjects.push_back(pNewLauchable);

		m_pLauncher->LoadLaunchable(pNewLauchable);
		m_pLauncher->MoveLaunchable(_window);

		m_bSpecialAbilityActivated = false;

		m_pMostRecentlyLaunchedLaunchable = pNewLauchable;

		// Asteriod has no special ability
		if (m_pMostRecentlyLaunchedLaunchable->GetObjectType() == EGAMEOBJECTTYPE::ASTERIOD)
		{
			m_bSpecialAbilityActivated = true;
		}
	}
	else // Activate Special Ability
	{
		m_pMostRecentlyLaunchedLaunchable->ActivateSpecialAbility(_window, _fScale, m_vpGameObjects);

		m_bSpecialAbilityActivated = true;
	}

	

	return false;
}

void CLevel::MouseButtonReleased(float _fScale)
{
	m_pLauncher->LaunchLoaded(_fScale, *m_pWorld);

	return;
}

void CLevel::MouseMoved(sf::RenderWindow& _window)
{
	m_pLauncher->MoveLaunchable(_window);

	return;
}

void CLevel::UnloadLevel()
{
	// Delete all objects
	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		delete m_vpGameObjects[i];
		m_vpGameObjects[i] = nullptr;
	}

	m_vpGameObjects.clear();
	m_vpDestructableObjects.clear();
	m_vpPlanets.clear();

	for (size_t i = 0; i < m_vpPlanks.size(); i++)
	{
		delete m_vpPlanks[i];
		m_vpPlanks[i] = nullptr;
	}
	m_vpPlanks.clear();

	// Delete launcher
	if (m_pLauncher != nullptr)
	{
		delete m_pLauncher;
		m_pLauncher = nullptr;
	}

	// Delete contact listener
	if (m_pContactListener != nullptr)
	{
		delete m_pContactListener;
		m_pContactListener = nullptr;
	}

	// Delete the world
	if (m_pWorld != nullptr)
	{
		delete m_pWorld;
		m_pWorld = nullptr;
	}

	m_bSpecialAbilityActivated = true;
	m_iEnemyCount = 0;
	m_pMostRecentlyLaunchedLaunchable = nullptr;

	while (m_qEGOTToLaunch.size() > 0)
	{
		m_qEGOTToLaunch.pop();
	}

	return;
}

void CLevel::LoadLevel1(float _fScale)
{
	// Gravity is set to 0 as planets will generate impulse forces to simulate gravity
	b2Vec2 b2v2Gravity(0.0f, 0.0f);
	m_pWorld = new b2World(b2v2Gravity);

	// Create and bind the contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	// Create planet
	CPlanet* newPlanet = new CPlanet(sf::Vector2f(1000, 3000), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_staticBody, 20.0f);
	m_vpPlanets.push_back(newPlanet);
	m_vpGameObjects.push_back(newPlanet);

	// Create enemies
	for (int i = 0; i < 5; i++)
	{
		CDestructable* newEnemy = new CEnemy(sf::Vector2f(700 + i * 5, 550 + i * 5), _fScale, m_pWorld);

		m_vpGameObjects.push_back(newEnemy);
		m_vpDestructableObjects.push_back(newEnemy);

		m_iEnemyCount++;
	}

	// Create indestructables
	for (int i = 0; i < 10; i++)
	{
		m_vpGameObjects.push_back(new CNuclearPasta(sf::Vector2f(900 - i * 2, 500 - i * 5), _fScale, m_pWorld));
	}

	// Create the launcher and the queue of lauchables
	m_pLauncher = new CLauncher(sf::Vector2f(150, 410));

	for (int i = 0; i < 2; i++)
	{
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::ASTERIOD);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::COMET);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::METEOR);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::STARLINKSAT);
	}

	return;
}

void CLevel::LoadLevel2(float _fScale)
{
	// Gravity is set to 0 as planets will generate impulse forces to simulate gravity
	b2Vec2 b2v2Gravity(0.0f, 0.0f);
	m_pWorld = new b2World(b2v2Gravity);

	// Create and bind the contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	// Create planet
	CPlanet* newPlanet = new CPlanet(sf::Vector2f(900, 400), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_staticBody, 1.0f);
	m_vpPlanets.push_back(newPlanet);
	m_vpGameObjects.push_back(newPlanet);

	// Create enemies
	for (int i = 0; i < 5; i++)
	{
		CDestructable* newEnemy = new CEnemy(sf::Vector2f(800 + i * 5, 450 + i * 5), _fScale, m_pWorld);

		m_vpGameObjects.push_back(newEnemy);
		m_vpDestructableObjects.push_back(newEnemy);

		m_iEnemyCount++;
	}

	// Create Destructables
	for (int i = 0; i < 10; i++)
	{
		CDestructable* newBox = new CBox(sf::Vector2f(900 - i * 2, 450 - i * 2), _fScale, m_pWorld);
		m_vpGameObjects.push_back(newBox);
		m_vpDestructableObjects.push_back(newBox);
	}

	// Create indestructable plank
	m_vpPlanks.push_back(new CPlank(m_vpGameObjects, m_vpDestructableObjects, EGAMEOBJECTTYPE::NUCLEARPASTA, sf::Vector2f(800, 900), _fScale, m_pWorld));


	// Create indestructables
	/*for (int i = 0; i < 10; i++)
	{
		m_vpGameObjects.push_back(new CNuclearPasta(sf::Vector2f(900 - i * 2, 500 - i * 5), _fScale, m_pWorld));
	}*/

	// Create the launcher and the queue of lauchables
	m_pLauncher = new CLauncher(sf::Vector2f(150, 410));

	for (int i = 0; i < 2; i++)
	{
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::ASTERIOD);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::COMET);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::METEOR);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::STARLINKSAT);
	}

	return;
}

void CLevel::LoadLevel3(float _fScale)
{
	b2Vec2 b2v2Gravity(0.0f, 0.0f);
	m_pWorld = new b2World(b2v2Gravity);

	// Create and bind the contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	CPlanet* newPlanet = new CPlanet(sf::Vector2f(600, 300), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_staticBody, 1.0f);
	m_vpPlanets.push_back(newPlanet);
	m_vpGameObjects.push_back(newPlanet);

	CPlanet* newPlanet2 = new CPlanet(sf::Vector2f(750, 250), _fScale, m_pWorld, "Planet.png", b2BodyType::b2_dynamicBody, 0.5f);
	m_vpPlanets.push_back(newPlanet2);
	m_vpGameObjects.push_back(newPlanet2);

	CPlanet* newPlanet3 = new CPlanet(sf::Vector2f(800, 800), _fScale, m_pWorld, "Ball.png", b2BodyType::b2_dynamicBody, 1.0f);
	m_vpPlanets.push_back(newPlanet3);
	m_vpGameObjects.push_back(newPlanet3);



	newPlanet->GiveAsOrbital(newPlanet2->Getb2Body(), 25, 15);
	newPlanet2->GiveAsOrbital(newPlanet3->Getb2Body(), 50, 5);

	for (int i = 0; i < 5; i++)
	{
		m_vpGameObjects.push_back(new CNuclearPasta(sf::Vector2f(500 - i * 2, 500 - i * 2), _fScale, m_pWorld));
	}

	for (int i = 0; i < 15; i++)
	{
		CDestructable* newBox = new CBox(sf::Vector2f(600 + i * 2, 400 + i * 2), _fScale, m_pWorld);
		m_vpGameObjects.push_back(newBox);
		m_vpDestructableObjects.push_back(newBox);
	}

	for (int i = 0; i < 10; i++)
	{
		CDestructable* newEnemy = new CEnemy(sf::Vector2f(500 + i * 2, 300 + i * 2), _fScale, m_pWorld);

		m_vpGameObjects.push_back(newEnemy);
		m_vpDestructableObjects.push_back(newEnemy);

		m_iEnemyCount++;

	}

	m_vpPlanks.push_back(new CPlank(m_vpGameObjects, m_vpDestructableObjects, EGAMEOBJECTTYPE::BOX, sf::Vector2f(500.0f, 500.0f), _fScale, m_pWorld));
	m_vpPlanks.push_back(new CPlank(m_vpGameObjects, m_vpDestructableObjects, EGAMEOBJECTTYPE::NUCLEARPASTA, sf::Vector2f(600, 600), _fScale, m_pWorld));


	m_pLauncher = new CLauncher(sf::Vector2f(150, 410));

	for (int i = 0; i < 2; i++)
	{
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::ASTERIOD);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::COMET);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::METEOR);
		m_qEGOTToLaunch.push(EGAMEOBJECTTYPE::STARLINKSAT);
	}

	return;
}

//void CLevel::ClearFarAndMarkedObjects()
//{
//	for (size_t i = 0; i < m_vpDestructableObjects.size(); i++)
//	{
//		b2Vec2 v2fPosition = m_vpDestructableObjects[i]->Getb2Body()->GetTransform().p;
//		
//		if (v2fPosition.Length() > 1000)
//		{
//			m_vpDestructableObjects[i]->SetShouldDestroy(true);
//		}
//	}
//
//	DestroyObjectsMarkedForDestruction();
//
//	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
//	{
//		b2Vec2 v2fPosition = m_vpGameObjects[i]->Getb2Body()->GetTransform().p;
//
//		if (v2fPosition.Length() > 100)
//		{
//			// Dont need to check if planet as planets are always pinned to a staticbody planet
//			delete m_vpGameObjects[i];
//			m_vpGameObjects[i] = nullptr;
//			m_vpGameObjects.erase(m_vpGameObjects.begin() + i);
//		}
//	}
//
//	return;
//}

void CLevel::DestroyObjectsMarkedForDestruction()
{
	for (size_t i = 0; i < m_vpDestructableObjects.size(); i++)
	{
		if (m_vpDestructableObjects[i]->GetShouldDestroy())
		{
			// std::cout << "Destroying" << std::endl;
			DestroyDestructable(m_vpDestructableObjects[i]);
		}
		else // need to remove targets that have moved far off screen so game can still be won
		{
			b2Vec2 v2fPosition = m_vpDestructableObjects[i]->Getb2Body()->GetTransform().p;
			
			if (v2fPosition.Length() > 50)
			{
				DestroyDestructable(m_vpDestructableObjects[i]);
			}
		}
	}

	// Get rid of all nullptrs in the vector
	m_vpDestructableObjects.erase(std::remove(begin(m_vpDestructableObjects), end(m_vpDestructableObjects), nullptr), end(m_vpDestructableObjects));

	return;
}

void CLevel::DestroyDestructable(CDestructable* _pDestructable)
{
	// Erase it from the gameobject vector
	for (size_t i = 0; i < m_vpGameObjects.size(); i++)
	{
		if (m_vpGameObjects[i] == _pDestructable)
		{
			m_vpGameObjects.erase(m_vpGameObjects.begin() + i);

			// exit the loop
			i = m_vpGameObjects.size();
		}
	}

	// Nullify the pointer in the destructableobjects vector
	// Can not erase as it will mess up loop calling this function
	for (size_t i = 0; i < m_vpDestructableObjects.size(); i++)
	{
		if (m_vpDestructableObjects[i] == _pDestructable)
		{
			m_vpDestructableObjects[i] = nullptr;

			// exit the loop
			i = m_vpDestructableObjects.size();
		}
	}

	if (_pDestructable->GetObjectType() == EGAMEOBJECTTYPE::ENEMY)
	{
		m_iEnemyCount--;

		std::cout << "Targets Left: " << m_iEnemyCount << std::endl;
	}

	// Actually delete the object
	delete _pDestructable;

	return;
}
