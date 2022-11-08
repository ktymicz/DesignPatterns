#pragma once
#include <vector>

namespace Pattern{
	
	
	struct Data
	{
		int i;
	};
	class Observeable;
	class Observer
	{
		Data d;
		Observeable* p;
	public:
		void set_data();
		void get_data();
		void update();
		
	};


	class Observeable
	{
		std::vector<Observer*> ob;
	public:
		void register_Observer();
		void notify_Observers();
		void remove_Observer(Observer* ob);

		void set_data();
		void get_data();
	};
}


