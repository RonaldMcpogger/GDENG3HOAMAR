#include <DX3D/Input/commandHandler.h>

//run the command iand stor into the list
void commandHandler::executeCommand(std::unique_ptr<dx3d::Command> command)
{
	if (!command) return;

	command->execute();
	m_undoStack.push_back(std::move(command));
	m_redoStack.clear(); // Executing a brand new key action clears forward redo
}

void commandHandler::undo() // reset
{
	if (m_undoStack.empty()) return;

	auto command = std::move(m_undoStack.back());
	m_undoStack.pop_back();

	command->undo();
	m_redoStack.push_back(std::move(command));
}

void commandHandler::redo() // redo the undo and stuff
{
	if (m_redoStack.empty()) return;

	auto command = std::move(m_redoStack.back());
	m_redoStack.pop_back();

	command->execute();
	m_undoStack.push_back(std::move(command));
}

void commandHandler::clearHistory()
{ // used when making a new entry or execution so it overwrites similar to how undo works
	m_undoStack.clear();
	m_redoStack.clear();
}