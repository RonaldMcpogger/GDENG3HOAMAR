// main controls for the player to use


#include "Player.h"
#include <Windows.h>
Player::Player(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
}

Player::~Player()
{
}

void Player::onCreate()
{
	createOrGetComponent<dx3d::CameraComponent>();
}

void Player::onUpdate(dx3d::f32 deltaTime)
{
	auto& input = getInputSystem();

	// move and look sensitivity
	auto sensitivity = 0.001f;

	auto rot = getTransform().getRotation();
	rot.x += getInputSystem().getMouseDelta().y * sensitivity;
	rot.y += getInputSystem().getMouseDelta().x * sensitivity;
	if (rot.x > 1.57f) rot.x = 1.57f;
	else if (rot.x < -1.57f) rot.x = -1.57f;
	getTransform().setRotation(rot);


	auto pos = getTransform().getPosition();
	auto forward = 0.0f;
	auto right = 0.0f;
	auto speed = 3.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::W)) forward = 1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::S)) forward = -1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::D)) right = 1.0f;
	if (getInputSystem().isKeyDown(dx3d::KeyCode::A)) right = -1.0f;
	// end game

	if (getInputSystem().isKeyDown(dx3d::KeyCode::Escape))
	{
		PostQuitMessage(0);

	}

	// insert command line heres






	auto forwardDir = getTransform().forward() * forward;
	auto rightDir = getTransform().right() * right;
	auto direction = dx3d::Vec3::normalize(forwardDir + rightDir);
	pos = pos + direction * speed * deltaTime;
	getTransform().setPosition(pos);
}
