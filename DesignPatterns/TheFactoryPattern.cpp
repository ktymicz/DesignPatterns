#include "TheFactoryPattern.h"


namespace TheFactoryPattern
{
	Pizza::Pizza(std::string name, std::string sauce, std::string dough, std::list<std::string> toppings)
		:nameo{ name }, sauceo{ sauce }, dougho{ dough }
	{
		for (auto t : toppings)
			toppingso.push_back(t);
	}


	Pizza* PizzaStore::orderPizza(std::string type)
	{
		Pizza *ppizza = createPizza(type);
		ppizza->prepare();
		ppizza->bake();
		ppizza->cut();
		ppizza->box();
		return ppizza;
	}

	void PizzaStore::removePizza(Pizza* ppz)
	{		
		own.remove(ppz);
	}
	void PizzaStore::addPizza(Pizza* ppz)
	{
		own.push_back(ppz);
	}

	Pizza* NYPizzaStore::createPizza(std::string type)
	{
		Pizza* ppizza = nullptr;
		if (type == "cheese")
		{
			ppizza = new NYCheesePizza();
		}
		else if(type == "veggie")
		{
			ppizza = new NYVeggiePizza();
		}
		else if (type == "clam")
		{
			ppizza = new NYClamPizza();
		}
		
		PizzaStore::addPizza(ppizza);
		return ppizza;
	}

	Pizza* ChPizzaStore::createPizza(std::string type)
	{
		Pizza* ppizza = nullptr;
		if (type == "cheese")
		{
			ppizza = new ChicagoCheesePizza();
		}
		else if (type == "veggie")
		{
			ppizza = new ChicagoVeggiePizza();
		}
		PizzaStore::addPizza(ppizza);
		return ppizza;
	}
}