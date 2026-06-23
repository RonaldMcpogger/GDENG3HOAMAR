

#include "MainGame.h"
#include "Objects/Player.h"
#include "Objects/SphereObj.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate() // crewate world 
{
	Game::onCreate();
	auto& world = getWorld();

	auto floor = world.createGameObject<dx3d::GameObject>();
	floor->createOrGetComponent<dx3d::CubeComponent>();
	floor->getTransform().setScale({ 6.8f, 0.0f, 6.8f });
	floor->getTransform().setPosition({ 0, -1, 0 });






	// player object
	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2});

	//sphere object
	 auto sphere = world.createGameObject<SphereObj>();


	//set reference

	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}


void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();
	auto& world = getWorld();

	// 1. SPACEBAR INPUT -> Fire Spawn Command
	if (input.isKeyPressed(dx3d::KeyCode::Space))
	{
		m_commandHandler.executeCommand(
			std::make_unique<dx3d::SpawnSphereCommand>(world, m_sphereRegistry, m_nextCommandId++)
		);
	}

	// 2. BACKSPACE INPUT -> Fire Undo Transaction 
	if (input.isKeyPressed(dx3d::KeyCode::Backspace))
	{
		m_commandHandler.undo();
	}

	// 3. DELETE INPUT -> Wipe active layout safely
	if (input.isKeyPressed(dx3d::KeyCode::Delete))
	{
		// Safely clear objects that are currently tracked as alive
		for (auto& [id, spherePtr] : m_sphereRegistry)
		{
			if (spherePtr)
			{
				world.destroyGameObject(*spherePtr);
			}
		}

		// Flush our pointer maps completely 
		m_sphereRegistry.clear();

		// Clear history so old actions don't attempt to undo non-existent components
		m_commandHandler.clearHistory();
	}
	
}


