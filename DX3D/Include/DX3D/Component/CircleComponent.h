#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Mat4x4.h>


namespace dx3d
{
	class CircleComponent : public Component
	{
	
		dx3d_typeid(CircleComponent)
	public:
		explicit CircleComponent(const ComponentDesc& data);


	};
}
