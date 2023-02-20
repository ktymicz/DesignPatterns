#include "TheFactoryPattern.h"

namespace TheFactoryPattern
{

	//std::ostream& operator<<(std::ostream& os, Dough& d)
	//{
	//	os << "dough" << d << '\n';
	//	return os;
	//};

	Pizza::Pizza(std::string name, std::string sauce, std::string dough, std::list<std::string> toppings)
		:nameo{ name }
	{
		sauceo.s = { sauce };
		dougho.d = { dough };
		for (auto t : toppings)
			toppingso.push_back(t);
	}

	CheesePizza::CheesePizza(PizzaIngredientFactory* pingredientFactory)
		: ingredientFactory(pingredientFactory)
	{
		addTopping("t3");
	}
	void CheesePizza::prepare()
	{
		dougho = ingredientFactory->createDough();
		sauceo = ingredientFactory->createSauce();
		cheeseo = ingredientFactory->createCheese();
		clamo = ingredientFactory->createClam();
		veggieso = ingredientFactory->createVeggies();
		std::cout << "Preparing " << getName() << '\n'
			<< "Tossing " << dougho.d << '\n'
			<< "Adding " << sauceo.s << '\n'
			<< "Adding " << cheeseo.ch << '\n'
			<< "Adding Veggies " << veggieso.v << '\n'
			<< "Adding toppings: ";
		for (auto& t : toppingso)
			std::cout << t << ',';
		std::cout << '\n';
	}
	void VeggiePizza::prepare()
	{
		dougho = ingredientFactory->createDough();
		sauceo = ingredientFactory->createSauce();
		cheeseo = ingredientFactory->createCheese();
		clamo = ingredientFactory->createClam();
		veggieso = ingredientFactory->createVeggies();
		std::cout << "Preparing " << getName() << '\n'
			<< "Tossing " << dougho.d << '\n'
			<< "Adding " << sauceo.s << '\n'
			<< "Adding " << cheeseo.ch << '\n'
			<< "Adding Veggies " << veggieso.v << '\n'
			<< "Adding toppings: ";
		for (auto& t : toppingso)
			std::cout << t << ',';
		std::cout << '\n';
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
		//std::shared_ptr<PizzaIngredientFactory> ingredientFactory =  WTF
		// WTF std::make_shared<PizzaIngredientFactory>(NYPizzaIngredientFactory()); 
		PizzaIngredientFactory * ingredientFactory = new NYPizzaIngredientFactory();
		Pizza* ppizza = nullptr;
		if (type == "cheese")
		{
			ppizza = new CheesePizza(ingredientFactory);
			ppizza->setName(std::string("NY Style Sauce and Cheese Pizza"));
		}
		else if(type == "veggie")
		{
			ppizza = new VeggiePizza(ingredientFactory);
			ppizza->setName(std::string("NY Style Veggie Pizza"));
		}
		else if (type == "clam")
		{
			ppizza = new NYClamPizza();
			ppizza->setName(std::string("NY Style Old Clams Pizza"));
		}
		
		
		PizzaStore::addPizza(ppizza);		
		
		return ppizza;
	}

	Pizza* ChPizzaStore::createPizza(std::string type)
	{
		PizzaIngredientFactory* ingredientFactory = new CHPizzaIngredientFactory();
		Pizza* ppizza = nullptr;
		if (type == "cheese")
		{
			ppizza = new CheesePizza(ingredientFactory);
			ppizza->setName(std::string("Ch Style Sauce and Cheese Pizza"));
		}
		else if (type == "veggie")
		{
			ppizza = new VeggiePizza(ingredientFactory);
			ppizza->setName(std::string("Ch Style Veggie Pizza"));
		}
		PizzaStore::addPizza(ppizza);
		return ppizza;
	}
}