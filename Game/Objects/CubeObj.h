#include <DX3D/All.h>

#pragma once
class CubeObj : public dx3d::GameObject
{
	dx3d_typeid(CubeObj)
public:
	explicit CubeObj(const dx3d::GameObjectDesc& desc);
	virtual ~CubeObj() override;
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);
	virtual void onDestroy();

private:
	bool rev=false;
};
