

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
	
	
	





	// player object
	auto player = world.createGameObject<Player>();
	player->getTransform().setPosition({ 0, 1, -2});

	
	


	///1 

	/*
	auto Cube1 = world.createGameObject<dx3d::GameObject>();
	Cube1->createOrGetComponent<dx3d::CubeComponent>();
	*/






	
	///2 & 3


	//auto Cube2 = world.createGameObject<CubeObj>(); // call cubeObj update function for animation is in cubeObj.cpp


	//4
	/*
	for (int i = 0; i < 50; i++) // for loop to render all 50 cubes
	{
		auto Cube = world.createGameObject<CubeObj>();
		auto pos = Cube->getTransform().getPosition();
		auto x = pos.x;
		auto y = pos.y;
		auto z = pos.z;
		 x = (rand() % 10) + 1;
		 y = (rand() % 10) + 1;
		 z = (rand() % 10) + 1;
		Cube->getTransform().setPosition({x,y,z});
	}

	*/

	//5 render warping animation // update transformation function in CubeObj.cpp under no 5 comment line

	//	auto Cube5 = world.createGameObject<CubeObj>();

	/*6 copy layout and position of cube

	// set cube
	auto Cube1 = world.createGameObject<dx3d::GameObject>();
	Cube1->createOrGetComponent<dx3d::CubeComponent>();
	auto Cube2 = world.createGameObject<dx3d::GameObject>();
	Cube2->createOrGetComponent<dx3d::CubeComponent>();
	auto Cube3 = world.createGameObject<dx3d::GameObject>();
	Cube3->createOrGetComponent<dx3d::CubeComponent>();

	//set floor
	auto floor = world.createGameObject<dx3d::GameObject>();
	floor->createOrGetComponent<dx3d::PlaneComponent>();

	//set position

	Cube1->getTransform().setPosition({ 0,.9f,0 });
	Cube2->getTransform().setPosition({ -1.5f,2.0,0 });
	Cube3->getTransform().setPosition({ -1.5f,3.0f,-2.0 });

	floor->getTransform().setScale({ 20,20,20 });


	*/

	/* No 7 Cards*/

	// set Cards
	std::vector<CubeObj*> cards;

	for (int i = 0; i < 15; i++)
	{
		auto Cube = world.createGameObject<CubeObj>();
		cards.push_back(Cube);
	}
	// bottom layer
	//leftmost left leg
	cards[0]->getTransform().setRotation({ 0,1.57f,-0.31f });
	cards[0]->getTransform().setPosition({ -1.616,.666,0 });

	//leftmost right leg
	cards[1]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[1]->getTransform().setPosition({ -1.184,.666,0 });

	//middlemost left leg
	cards[2]->getTransform().setRotation({ 0,1.57f,-0.31f });
	cards[2]->getTransform().setPosition({ -.75,.666,0 });

	//middlemost right leg
	cards[3]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[3]->getTransform().setPosition({-.30,.666,0 });

	//rightmost left leg
	cards[4]->getTransform().setRotation({ 0,1.57f,-0.31f });
	cards[4]->getTransform().setPosition({ .15,.666,0 });

	//rightmost right leg
	cards[5]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[5]->getTransform().setPosition({ .6,.666,0 });

	//middle base
	cards[6]->getTransform().setRotation({ 0.f,1.57f,1.6 });
	cards[6]->getTransform().setPosition({ -1.2,1.34,0 });
	cards[7]->getTransform().setRotation({ 0.f,1.57f,1.6 });
	cards[7]->getTransform().setPosition({ 0.2,1.34,0 });

	//middle layer leg

	cards[8]->getTransform().setRotation({ 0,1.57f,-0.31f });
	cards[8]->getTransform().setPosition({ -1.22,1.966,0 });

	//rightmost right leg
	cards[9]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[9]->getTransform().setPosition({ -.77,1.966,0 });
	
	cards[10]->getTransform().setRotation({ 0,1.57f,-0.31f });
	cards[10]->getTransform().setPosition({ -.35,1.966,0 });

	//rightmost right leg
	cards[11]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[11]->getTransform().setPosition({ .15,1.966,0 });

	// top base
	cards[12]->getTransform().setRotation({ 0.f,1.57f,1.6 });
	cards[12]->getTransform().setPosition({ -.5,2.60,0 });

	cards[13]->getTransform().setRotation({ 0.f,1.57f,-0.31f });
	cards[13]->getTransform().setPosition({ -.65,3.34,0 });

	cards[14]->getTransform().setRotation({ 0.f,1.57f,0.31f });
	cards[14]->getTransform().setPosition({ -.1,3.34,0 });


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

