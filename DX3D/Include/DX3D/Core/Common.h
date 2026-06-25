
//handlers of descriptors
#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>

namespace dx3d
{
	//base
	struct BaseDesc
	{
		Logger& logger;
	};
	// windows and display
	struct WindowDesc
	{
		BaseDesc base;
		Rect size{};
	};

	struct DisplayDesc
	{
		WindowDesc window;
		GraphicsDevice& graphicsDevice;
	};
	//graphics and its core functions
	struct GraphicsDeviceDesc
	{
		BaseDesc base;
	};

	struct SwapChainDesc
	{
		void* winHandle{};
		Rect winSize{};
	};
	//shader type
	enum class ShaderType
	{
		VertexShader = 0,
		PixelShader
	};
	//shader compiler
	struct ShaderCompileDesc
	{
		const char* shaderSourceName{};
		const void* shaderSourceCode{};
		size_t shaderSourceCodeSize{};
		const char* shaderEntryPoint{};
		ShaderType shaderType{};
	};

	struct VertexShaderSignatureDesc
	{
		const RefPtr<ShaderBinary>& vsBinary;
	};

	struct BinaryData
	{
		const void* data{};
		size_t dataSize{};
	};

	struct GraphicsPipelineStateDesc
	{
		const VertexShaderSignature& vs;
		const ShaderBinary& ps;
	};

	struct VertexBufferDesc
	{
		const void* vertexList{};
		ui32 vertexListSize{};
		ui32 vertexSize{};
	};
	// for animation
	struct ConstantBufferDesc
	{
		const void* buffer{};
		ui32 bufferSize{};
	};

	struct IndexBufferDesc
	{
		const ui32* indexList{};
		ui32 indexListSize{};
	};


	// for inputs
	struct GameContext
	{
		InputSystem& input;
	};
	// game settings
	struct GameDesc
	{
		Rect windowSize{ 1024,768 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};


	//game world and game context
	struct WorldDesc 
	{
		BaseDesc base;
		GameContext gameContext;
	};


	// a game object
	struct GameObjectDesc
	{
		BaseDesc base;
		GameContext gameContext;
		World& world;
	};
	
	//components
	struct ComponentDesc
	{
		BaseDesc base;
		GameObject& object;
		World& world;
	};

	// rendering objects
	struct WorldRendererDesc
	{
		BaseDesc base;
		GraphicsDevice& engine;
	};

	//keys fml
	enum class KeyCode
	{
		Unknown = 0,
		// Letters
		A, B, C, D, E, F, G,
		H, I, J, K, L, M, N,
		O, P, Q, R, S, T, U,
		V, W, X, Y, Z,

		// Numbers
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,


		Escape,
		Shift,
		Space,
		Enter,
		Delete,
		Backspace,

		// Mouse buttons (optional inclusion)
		MouseLeft,
		MouseRight,
		MouseMiddle,

		// Arrows
		Up,
		Down,
		Left,
		Right,

		Count
	};
	//the input for the keys

	struct InputSystemDesc
	{
		BaseDesc base;
	};

}