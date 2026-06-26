

#pragma once
#include <DX3D/All.h>
#include <memory>
#include <vector>
#include <unordered_map> // unordered map for the command registry
#include <DX3D/Input/commandHandler.h>


class SphereObj;
class CubeObj;

// main game loop 
class MainGame : public dx3d::Game
{
public:
	explicit MainGame(const dx3d::GameDesc& desc);
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);


//test
private:
	// stuff for command handler and command inputs
	commandHandler m_commandHandler;// the handler
	std::unordered_map<uint64_t, SphereObj*> m_sphereRegistry; // orbs registry in unordered map for easy track

	//testing 

	std::unordered_map<uint64_t, CubeObj*> m_CubeRegistry;

	uint64_t m_nextCommandId = 0; // id num

private:

	

	dx3d::GameObject* m_player{};
	dx3d::f32 m_rot{}, m_scale{};

};








