#include "SphereObj.h"

SphereObj::SphereObj(const dx3d::GameObjectDesc& desc): dx3d::GameObject(desc)
{
}

SphereObj::~SphereObj()
{
}

 void SphereObj::onCreate()
{
	 createOrGetComponent<dx3d::CircleComponent>();
	 srand((unsigned int)time(NULL));
	 auto pos = getTransform().getPosition();

	 auto x = pos.x;
	 auto y = pos.y;
	 auto z = pos.z;
	 speed = (rand() % 4) + 1;
	 x = (rand() % 4) + 1;
	 y = (rand() % 4) + 1;
	 getTransform().setScale({ 0.5f,0.5f,0.5f });
	 getTransform().setPosition({ x,y,z });
}
 void SphereObj::onUpdate(dx3d::f32 deltaTime)
{
	 auto pos = getTransform().getPosition();
	 auto x = pos.x;
	 auto y = pos.y;
	 auto z = pos.z;
	 if (xRev)
	 {	 
			 auto rightDir = getTransform().right() * -1;
			 auto direction = dx3d::Vec3::normalize(rightDir);

			 pos = pos + direction * 1.0f*deltaTime;
			
			 if (x < -3.5) xRev = false;		 
	 }
	 else
	 {
		 if (x > 3.5) { xRev = true; }
		 else
		 {
			 auto rightDir = getTransform().right() * 1;
			 auto direction = dx3d::Vec3::normalize(rightDir);
			 pos = pos + direction * speed * deltaTime;
		 }
	 }
	 if (yRev)
	 {
		 auto upDir = getTransform().up() * -1;
		 auto direction = dx3d::Vec3::normalize(upDir);

		 pos = pos + direction * speed * deltaTime;

		 if (y <= -1) yRev = false;
	 }
	 else
	 {
		 if (y > 5) { yRev = true; }
		 else
		 {
			 auto upDir = getTransform().up() * 1;
			 auto direction = dx3d::Vec3::normalize(upDir);
			 pos = pos + direction * speed * deltaTime;
		 }
	 }




	 getTransform().setPosition(pos);
}

 void SphereObj::onDestroy()
 {
 }

