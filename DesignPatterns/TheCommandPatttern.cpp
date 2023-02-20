#include "TheCommandPatttern.h"

namespace CommandPattern
{
	
	static NoCommand noCommand = NoCommand();
	SimpleRemoteControl::SimpleRemoteControl()
		:onCommands(size), offCommands(size)
	{
		for (auto c : onCommands)
			c = &noCommand;
		for (auto c : offCommands)
			c = &noCommand;
	}

	void SimpleRemoteControl::setCommand(int indexSlot, Command* onCommand, Command* offCommand)
	{
		onCommands[indexSlot] = onCommand;
		offCommands[indexSlot] = offCommand;
	}


	void SimpleRemoteControl::buttonOnWasPressed(int indexSlot)
	{
		onCommands[indexSlot]->execute();
		undoCommand = onCommands[indexSlot];
	}

	void SimpleRemoteControl::buttonOffWasPressed(int indexSlot)
	{
		offCommands[indexSlot]->execute();
		undoCommand = offCommands[indexSlot];
	}


	void SimpleRemoteControl::buttonUndoWasPressed()
	{
		undoCommand->undo();
	}

	void SimpleRemoteControl::setCommand(int indexSlot, void (*on)(), void (*off)())
	{
		onFp.push_back(on);
		offFp.push_back(off);
	}


}
