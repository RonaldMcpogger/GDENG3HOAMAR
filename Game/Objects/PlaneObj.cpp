#include "PlaneObj.h"

PlaneObj::PlaneObj(const dx3d::GameObjectDesc& desc): dx3d::GameObject(desc)
{
}

PlaneObj::~PlaneObj()
{
}
void PlaneObj::onCreate()
{
	createOrGetComponent<dx3d::PlaneComponent>();

 }
void PlaneObj::onUpdate(dx3d::f32 deltaTime)
{

 }
void PlaneObj::onDestroy()
{

 }