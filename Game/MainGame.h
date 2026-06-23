

#pragma once
#include <DX3D/All.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <DX3D/Input/commandHandler.h>

//add command and sphere obj hee
class SphereObj;


// main game loop i think
class MainGame : public dx3d::Game
{
public:
	explicit MainGame(const dx3d::GameDesc& desc);
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);


//test
private:
	// Command Architecture Systems
	dx3d::commandHandler m_commandHandler;
	std::unordered_map<uint64_t, SphereObj*> m_sphereRegistry;
	uint64_t m_nextCommandId = 0;

private:
	std::vector<SphereObj*> m_spawnedSpheres{};

	

	dx3d::GameObject* m_player{};
	dx3d::f32 m_rot{}, m_scale{};

};

/// all commands here






