

#include "MainGame.h"
#include "Objects/Player.h"
#include "Objects/SphereObj.h"
#include "Objects/CubeObj.h"

MainGame::MainGame(const dx3d::GameDesc& desc) : dx3d::Game(desc)
{
}

void MainGame::onCreate() // crewate world 
{
	srand((unsigned int)time(NULL));
	Game::onCreate();
	auto& world = getWorld();
	
	
	auto floor = world.createGameObject<dx3d::GameObject>();
	floor->createOrGetComponent<dx3d::PlaneComponent>();
	floor->getTransform().setScale({ 6.8f, 1.0f, 6.8f });
	floor->getTransform().setPosition({ 0, 0, 0 });





	// player object
	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2});

	auto testCube = world.createGameObject<CubeObj>();
	
	

	//set reference

	getInputSystem().setCursorLocked(true);
	getInputSystem().setCursorVisible(false);
}


void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();
	auto& world = getWorld();

	// inputs for the command/ kill

	if (input.isKeyPressed(dx3d::KeyCode::Z)&&input.isKeyDown(dx3d::KeyCode::Shift))
	{
		m_commandHandler.undo();
	}

	if (input.isKeyPressed(dx3d::KeyCode::R) && input.isKeyDown(dx3d::KeyCode::Shift))
	{
		m_commandHandler.redo();
	}




	


}

