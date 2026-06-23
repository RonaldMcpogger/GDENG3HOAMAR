#pragma once

#include <DX3D/All.h>


class SphereObj : public dx3d::GameObject
	{
	dx3d_typeid(SphereObj)
	public:
		explicit SphereObj(const dx3d::GameObjectDesc& desc);
		virtual ~SphereObj() override;
	protected:
		virtual void onCreate();
		virtual void onUpdate(dx3d::f32 deltaTime);
		virtual void onDestroy();

	private:
		bool xRev=false;
		bool yRev = false;
		bool zRev = false;
		float speed = 1;
	};

