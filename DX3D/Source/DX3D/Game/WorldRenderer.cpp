
//CLASS FOR RENDERING ALL OBJECTS AND CAMERA IN THE GAME
#include <DX3D/Game/WorldRenderer.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>

#include <DX3D/Game/World.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Game/GameObject.h>

//components

#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Component/CameraComponent.h>

#include <DX3D/Component/CircleComponent.h>
#include <DX3D/Component/PlaneComponent.h>
// math utils

#include <DX3D/Math/MathUtils.h>
#include <DX3D/Math/Vec4.h>

#include <DX3D/Math/Vec3.h>
#include <fstream>
#include <ranges>


dx3d::WorldRenderer::WorldRenderer(const WorldRendererDesc& desc): Base(desc.base), m_graphicsDevice(desc.engine)
{
	auto& device = m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("Failed to open shader file.");
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();


	// render and compile shaders

	auto vs = device.compileShader({shaderFilePath, shaderSourceCode, shaderSourceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize,
		"PSMain", ShaderType::PixelShader });
	auto vsSig = device.createVertexShaderSignature({ vs });

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	// vertex list
	const Vertex vertexList[] =
	{
		{{-0.5f,-0.5f,-0.5f}, {1,0,0,1}},
		{{-0.5f,0.5f,-0.5f}, {0,1,0,1} },
		{{0.5f,0.5f,-0.5f},  {0,0,1,1}},
		{{0.5f,-0.5f,-0.5f}, {1,0,1,1}},

		{{0.5f,-0.5f,0.5f}, {1,0,1,1}},
		{{0.5f,0.5f,0.5f}, {0,0,1,1}},
		{{-0.5f,0.5f,0.5f}, {0,1,0,1}},
		{{-0.5f,-0.5f,0.5f}, {1,0,0,1}}
	};

	const ui32 indexList[] =
	{
		0,1,2,  
		2,3,0,  

		4,5,6,
		6,7,4,

		1,6,5,
		5,2,1,

		7,0,3,
		3,4,7,

		3,2,5,
		5,4,3,

		7,6,1,
		1,0,7
	};
	// bind and create here
	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vertex)});
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_ib = device.createIndexBuffer({indexList, std::size(indexList)});


// creating spheres

	std::vector<Vertex> speVerts;
	std::vector<ui32> speIndices;

	createSphereForm(&speVerts, &speIndices);
	
	m_speVb =
		device.createVertexBuffer({ speVerts.data(),static_cast<ui32>(speVerts.size()),sizeof(Vertex) });

	m_speIb= device.createIndexBuffer({ speIndices.data(), static_cast<ui32>(speIndices.size())});

	const Vertex planeVertexList[] =
	{
		{{-0.5f, 0.0f, -0.5f}, {1, 1, 1, 1.0f}},
		{{-0.5f, 0.0f,  0.5f}, {1, 1, 1, 1.0f}},
		{{ 0.5f, 0.0f,  0.5f}, {1, 1, 1, 1.0f}},
		{{ 0.5f, 0.0f, -0.5f}, {1, 1, 1, 1.0f}}
	};

	const ui32 planeIndexList[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_planeVb = device.createVertexBuffer({ planeVertexList, std::size(planeVertexList), sizeof(Vertex) });
	m_planeIb = device.createIndexBuffer({ planeIndexList, std::size(planeIndexList) });



}

dx3d::WorldRenderer::~WorldRenderer()
{
}


void dx3d::WorldRenderer::render(const World& world, SwapChain& swapChain, f32 deltaTime)
{
	auto size = swapChain.getSize();

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0, 0, 0, 1.0f }); // render taget color
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(size);

	auto numComponents = 0u;
	ConstantData data{};// empty constant data


	{// get the compnents existing in game
		auto components = world.getComponents<CameraComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			data.view = component->getViewMatrix();
			component->setViewportSize(size);
			data.proj = component->getProjectionMatrix();
			break;
		}
	}


	{
		/// try to refactor this in a  seperate class or method of refactoring these primitives as to not constantly copy and paste this same for loop for every primitive component
		auto components = world.getComponents<CubeComponent>(numComponents);

		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_vb;
			auto& ib = *m_ib;
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);
			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		}
	}

	{
		auto components = world.getComponents<CircleComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_speVb;
			auto& ib = *m_speIb;
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);
			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		}
	}


	{
		auto components = world.getComponents<PlaneComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();

			data.world = transform.getAffineWorldMatrix();

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *m_planeVb;
			auto& ib = *m_planeIb;
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);
			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		}
	}


	m_graphicsDevice.executeCommandList(context);


	swapChain.present();
}
//testing Circlefunction helper
void dx3d::WorldRenderer::createSphereForm(std::vector<Vertex>* vertices, std::vector<ui32>* indices)
{
	constexpr int latSegments = 16; // stacks
	constexpr int lonSegments = 16; // sectors 
	
	vertices->reserve((latSegments + 1) * (lonSegments + 1));
	indices->reserve(latSegments * lonSegments * 6);
	//create vertices for the mapping of vertice points of a sphere
	for (int l = 0; l <= latSegments; l++)
	{
		const float v = static_cast<float>(l) / static_cast<float>(latSegments);
		const float phi = v * MathUtils::PI;

		//for the longs

		for (int ln = 0; ln <= lonSegments; ln++)
		{
			const float u = static_cast<float>(ln) / static_cast<float>(lonSegments);
			const float thet = u * static_cast<float>(2 * MathUtils::PI);

			const float x = sinf(phi) * cosf(thet);
			const float y = cosf(phi);
			const float z = sinf(phi) * sinf(thet);
			constexpr float r = 0.5f;

			Vec3 SphPos{ x * r, y * r, z * r };
				
			Vec4 Color{ (x * 0.5f) + 0.3f,(y * 0.5f) + 0.3f,(z * 0.5f) + 0.3f,1.f };
			vertices->push_back({ SphPos,Color }); 


		}
	}
	for (int l = 0; l < latSegments; l++)
	{
		for (int ln = 0; ln < lonSegments; ln++)
		{
			const ui32 first = static_cast<ui32>(l * (lonSegments + 1) + ln);
			const ui32 sec = first + static_cast<ui32>(lonSegments) + 1u;
			
			indices->push_back(first);
			indices->push_back(sec);
			indices->push_back(first + 1u);

			indices->push_back(first + 1u);
			indices->push_back(sec);
			indices->push_back(sec + 1u);
		
		
		}
	}

}
