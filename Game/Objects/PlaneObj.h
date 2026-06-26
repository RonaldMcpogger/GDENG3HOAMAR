#include <DX3D/All.h>

#pragma once
class PlaneObj : public dx3d::GameObject
{
	dx3d_typeid(PlaneObj)
public:
	explicit PlaneObj(const dx3d::GameObjectDesc& desc);
	virtual ~PlaneObj() override;
protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);
	virtual void onDestroy();

private:

};
