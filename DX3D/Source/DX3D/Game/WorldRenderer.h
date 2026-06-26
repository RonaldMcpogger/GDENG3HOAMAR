

#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>
#include <vector>
namespace dx3d
{
	class WorldRenderer final: public Base
	{
	public:
		explicit WorldRenderer(const WorldRendererDesc& desc);
		virtual ~WorldRenderer() override;

		void render(const World& world, SwapChain& swapChain, f32 deltaTime);
	private:
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
		};
		struct alignas(16) ConstantData // the usual constant data for viewing objects in world, then projection, then view
		{
			Mat4x4 world{};
			Mat4x4 view{};
			Mat4x4 proj{};
		};

		//testing circlecomponent function
		void createSphereForm(std::vector<Vertex>* vertices, std::vector<ui32>* indices);

	private:
		GraphicsDevice& m_graphicsDevice;
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
	
		/// <summary>
		///  buffers of each object need to find way to refactor where each rendercompnent has its own vb to pass through later
		/// 
		/// 
		/// </summary>
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<ConstantBuffer> m_cb{};
		RefPtr<IndexBuffer> m_ib{};

		//testing of spheres

		RefPtr<VertexBuffer> m_speVb{};
		RefPtr<IndexBuffer> m_speIb{};

		RefPtr<VertexBuffer> m_planeVb{};
		RefPtr<IndexBuffer> m_planeIb{};
	};
}
