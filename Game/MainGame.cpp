

#include "MainGame.h"
#include "Objects/Player.h"
#include "Objects/SphereObj.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate() // crewate world 
{
	srand((unsigned int)time(NULL));
	Game::onCreate();
	auto& world = getWorld();

	auto floor = world.createGameObject<dx3d::GameObject>();
	floor->createOrGetComponent<dx3d::CubeComponent>();
	floor->getTransform().setScale({ 6.8f, 0.0f, 6.8f });
	floor->getTransform().setPosition({ 0, -1, 0 });






	// player object
	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2});

	
	


	//set reference

	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}


void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();
	auto& world = getWorld();

	// inputs for the command/ kill



	if (input.isKeyPressed(dx3d::KeyCode::Space))
	{
		m_commandHandler.executeCommand(
			std::make_unique<dx3d::SpawnSphereCommand>(world, m_sphereRegistry, m_nextCommandId++)
		);
	}

	
	if (input.isKeyPressed(dx3d::KeyCode::Backspace))
	{
		m_commandHandler.executeCommand(std::make_unique<dx3d::DestroyRecentSphereCommand>(world, m_sphereRegistry, m_nextCommandId--)
		);
	}
	if (input.isKeyPressed(dx3d::KeyCode::Z))
	{
		m_commandHandler.undo();
	}

	if (input.isKeyPressed(dx3d::KeyCode::P))
	{
		m_commandHandler.redo();
	}

	
	if (input.isKeyPressed(dx3d::KeyCode::Delete))
	{
		
		m_commandHandler.executeCommand(
			std::make_unique<dx3d::DeleteAllSpheresCommand>(world, m_sphereRegistry)
		);

		 
	

	
	}
	
}


