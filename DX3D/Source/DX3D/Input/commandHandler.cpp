#include <DX3D/Input/commandHandler.h>

void dx3d::commandHandler::executeCommand(std::unique_ptr<Command> command)
{
	if (!command) return;

	command->execute();
	m_undoStack.push_back(std::move(command));
	m_redoStack.clear(); // Executing a brand new key action clears forward redoes
}

void dx3d::commandHandler::undo()
{
	if (m_undoStack.empty()) return;

	auto command = std::move(m_undoStack.back());
	m_undoStack.pop_back();

	command->undo();
	m_redoStack.push_back(std::move(command));
}

void dx3d::commandHandler::redo()
{
	if (m_redoStack.empty()) return;

	auto command = std::move(m_redoStack.back());
	m_redoStack.pop_back();

	command->execute();
	m_undoStack.push_back(std::move(command));
}

void dx3d::commandHandler::clearHistory()
{
	m_undoStack.clear();
	m_redoStack.clear();
}