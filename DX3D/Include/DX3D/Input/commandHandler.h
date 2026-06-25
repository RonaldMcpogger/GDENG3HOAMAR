#pragma once
#include <vector>
#include <memory>
#include <DX3D/Input/Command.h>


// the handlers and passers of undo and redo stacks from command using vectors
	class commandHandler
	{
	public:
		commandHandler() = default;
		~commandHandler() = default;

		void executeCommand(std::unique_ptr<dx3d::Command> command);
		void undo();
		void redo();
		void clearHistory();

	private:
		std::vector<std::unique_ptr<dx3d::Command>> m_undoStack;
		std::vector<std::unique_ptr<dx3d::Command>> m_redoStack;
	};
