#pragma once
#include <vector>
#include <memory>
#include <DX3D/Input/Command.h>

namespace dx3d
{
	class commandHandler
	{
	public:
		commandHandler() = default;
		~commandHandler() = default;

		void executeCommand(std::unique_ptr<Command> command);
		void undo();
		void redo();
		void clearHistory();

	private:
		std::vector<std::unique_ptr<Command>> m_undoStack;
		std::vector<std::unique_ptr<Command>> m_redoStack;
	};
}