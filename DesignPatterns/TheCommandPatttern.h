#pragma once
#include <iostream>
#include <vector>

namespace CommandPattern {
	

	// --------- Abstract Classes --------- //

	class UseLambda
	{
	public:
		virtual void execute() = 0;
	};
	class Command
	{

	public:
		virtual void execute() = 0;
		virtual void undo() = 0;
	};

	class Invoker
	{
	public:
		void setCommand(Command* command);
		void buttonWasPressed(int indexSlot);
		//void undoButtonWasPressed(i)
	};

	// --------- Command classes  --------- //

	class NoCommand : public Command
	{
	public:
		void execute() {}
		void undo(){}
	};

	class Light
	{
	public:
		void on() { std::cout << "light on\n"; }
		void off() { std::cout << "light off\n"; }
	};

	class LightOnCommand : public Command
	{
		Light* light{ nullptr };
	public:
		LightOnCommand(Light* l)
			: light(l) {}
		void execute() override { light->on(); };
		void undo() override { light->off(); }
	};

	class LightOffCommand : public Command
	{
		Light* light;
	public:
		LightOffCommand(Light* l) : light(l) {}
		void execute() override { light->off(); }
		void undo() override { light->on(); }
	};

	class Stereo
	{
	public:
		void on() { std::cout << "Stereo on\n"; }
		void off() { std::cout << "Stereo off\n"; }
	};

	class StereoOnCommand : public Command
	{
		Stereo* stereo;
	public:
		StereoOnCommand(Stereo* st)
			: stereo(st) {}
		void execute() override { stereo->on(); }
		void undo() override { stereo->off(); }

	};

	class GarageDoor
	{
	public:
		void up() { std::cout << "The Garage Door up\n"; }
		void down() { std::cout << "The Garage Door down\n"; }
		void lightOn() { std::cout << "The Garage lights on\n"; }
		void lightOff() { std::cout << "The Garage lights off\n"; }
	};

	class GarageDoorOpenCommand : public Command
	{
		GarageDoor* garagedoor{ nullptr };
	public:
		GarageDoorOpenCommand(GarageDoor* gd) : garagedoor(gd) {}
		void execute() override { garagedoor->up(); };
		void undo() override { garagedoor->down(); }
	};


	class GarageDoorCloseCommand : public Command
	{
		GarageDoor* garagedoor{ nullptr };
	public:
		GarageDoorCloseCommand(GarageDoor* gd) : garagedoor(gd) {}
		void execute() override { garagedoor->down(); };
		void undo() override { garagedoor->up(); }
	};




	// --------- Control command --------- //

	class SimpleRemoteControl // Invoker
	{
		const int size = 7;
		std::vector<Command*> onCommands;
		std::vector<Command*> offCommands;
		Command* undoCommand;




	public:
		std::vector<void(*)()> onFp;
		std::vector<void(*)()> offFp;
		SimpleRemoteControl();
		void setCommand(int indexSlot, Command* onCommand, Command* offCommand);
		void setCommand(int indexSlot, void (*s)(), void (*s2)());
		void buttonOnWasPressed(int indexSlot);
		void buttonOffWasPressed(int indexSlot);
		void buttonUndoWasPressed();
	};


	class Reciver
	{
	public:
		void action1();
		void action2();
	};

	class Client
	{
	public:
		void createCommandObject();
	};


	class C : public UseLambda
	{

	};

	class RemoteControlTest
	{
	public:
		static void main(std::string args) {
			std::cout << args << '\n';
			SimpleRemoteControl* remote = new SimpleRemoteControl();
			Light* light = new Light();
			LightOnCommand* lightOn = new LightOnCommand(light);
			LightOffCommand* lightOff = new LightOffCommand(light);
			int slot = 0;
			remote->setCommand(slot, lightOn, lightOff);
			remote->buttonOnWasPressed(slot);
			remote->buttonUndoWasPressed();
			remote->buttonOffWasPressed(slot);
			remote->buttonUndoWasPressed();
			++slot;


			GarageDoor* garagedoor = new GarageDoor();
			GarageDoorOpenCommand* garageOpen = new GarageDoorOpenCommand(garagedoor);
			GarageDoorCloseCommand* garageClose = new GarageDoorCloseCommand(garagedoor);

			remote->setCommand(slot, garageOpen, garageClose);
			remote->buttonOnWasPressed(slot);
			remote->buttonUndoWasPressed();
			remote->buttonOffWasPressed(slot);
			remote->buttonUndoWasPressed();
			++slot;

			Stereo* stereo = new Stereo();
			StereoOnCommand* stereoOn = new StereoOnCommand(stereo);

			UseLambda* p;

			//remote->setCommand(slot, Stereo::on, Stereo::off);
//			remote->setCommand(slot, (*stereo.on), stereo->&off);


			/*remote->setCommand(stereoOn);
			remote->buttonWasPressed();*/


			delete stereoOn;
			delete stereo;
			
			delete garageOpen;
			delete garagedoor;

			delete lightOff;
			delete lightOn;
			delete light;

			delete remote;
		}
		//~RemoteControlTest() {  }
	};


}


