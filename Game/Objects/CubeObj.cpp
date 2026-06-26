#include "CubeObj.h"

CubeObj::CubeObj(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
}

CubeObj::~CubeObj()
{
}
 void CubeObj::onCreate()
 {
	 createOrGetComponent<dx3d::CubeComponent>();

 }
 void CubeObj::onUpdate(dx3d::f32 deltaTime)
 {
 }
 void CubeObj::onDestroy()
 {
 }