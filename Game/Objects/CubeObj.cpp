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
	 // no 7
	 // modify starting cube to card scale
	 getTransform().setScale({ 1,1.4,0.03 });

 }
 void CubeObj::onUpdate(dx3d::f32 deltaTime)
 {



	 /////  2 and 4 code
	 /*
	 auto rot = getTransform().getRotation();
	 auto sensitivity = 0.001f;
	 auto speed = 1.f;
	 rot += {.5f * sensitivity * speed, -.2f * sensitivity * speed, .07f * sensitivity * speed}; // for speed
	 getTransform().setRotation(rot);
	 */

	/* n0 3 code 
	 auto scale = getTransform().getScale(); // get scale

	 auto scalespeed = .5f*deltaTime; // scale speed to reach .25

	 auto scaletrack = scale.x; // to track the size of object when scaling

	

	 if (rev) // go left / go small
	 {
		 scale.x -= scalespeed;
		 scale.y -= scalespeed;
		 scale.z -= scalespeed;
		 if (scaletrack <= 0.25) rev = false;
	 }
	 else // go big
	 {
		 
		 scale.x += scalespeed;
		 scale.y += scalespeed;
		 scale.z += scalespeed;
		 if (scaletrack >=1) rev = true;
	 }



	 getTransform().setScale(scale);
	 */
	 


	 /* no 5

	 auto rot = getTransform().getRotation();
	 auto scale = getTransform().getScale();

	 auto speed = .5f *deltaTime; 

	 if (!rev)
	 {
		 
		 if (rot.x < 1.75) // almost exact point where it becomes horizontal
		 {
			 if (scale.z > 0) {
				 scale.z -= speed; // flatten it by its z axis, technically the smaller z means 
				 scale.x += speed*2;  // multiplied by 2 to become bigger than z axis and scale of cube
				 scale.y += speed*2;
				
			 }
			 rot.x += speed; // continue rotate until reach target value
			 
		 }
		 else if( rot.x >= 1.75)
		 {
		
			 rev = true; // switch bool
		 }
	 }
	 else // revert back
	 {
		 if (rot.x> 0)
		 {
			 if (scale.z < 1) {
				 scale.z += speed;
				 scale.x -= speed * 2;
				 scale.y -= speed * 2;
			 }
			 rot.x -=  speed;
			

		 }
		 else if (rot.x<=0)
		 {
			
			 
			 rev = false;

		 }
	 }

	 // set transforms here
	 getTransform().setScale(scale);
	 getTransform().setRotation(rot);
	 */

 }
 void CubeObj::onDestroy()
 {
 }