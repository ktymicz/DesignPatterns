#pragma once
#include <string>
#include <iostream>
#include <list>
namespace TheFactoryPattern
{
	class Pizza
	{
	private:
		std::string nameo;
		std::string sauceo;
		std::string dougho;
		std::list<std::string> toppingso;

	public:
		Pizza(std::string name, std::string sauce, std::string dough, std::list<std::string> toppings);

		virtual void prepare() 
		{ 
			std::cout << "Preparing " << nameo << '\n'
				<< "Tossing dough...\n"
				<< "Adding sauce...\n"
				<< "Adding toppings: ";
			for (auto& t : toppingso)
				std::cout << t << ',';
			std::cout << '\n';
		}
		void addTopping(std::string t) { toppingso.push_back(t); };
		virtual void bake() { std::cout << "Bake for 15 minutes at 250C, " << '\n'; };
		virtual void cut() { std::cout << "Cutting the pizza into diagonal slices" << '\n'; }
		void box() { std::cout << "Place pizza in official PizzaStore box\n"; }
		std::string getName() { return nameo; }
		virtual ~Pizza() { std::cout << "Pizza obj destroyed\n"; }
	};

	class PizzaStore
	{
	private:
		std::list<Pizza*> own;
	protected:
		void removePizza(Pizza* ppz);
		void addPizza(Pizza* ppz);
	public:
		Pizza* orderPizza(std::string type);
		virtual Pizza* createPizza(std::string type) = 0; // The Factory Method
		virtual ~PizzaStore() {
			for (auto& o : own)
			{
				delete o;
			}
			own.clear();
		};
	};

	
	// New York Pizza Store 
	
	class NYPizzaStore : public PizzaStore
	{
	public:
		Pizza* createPizza(std::string type) override; 
	};


	// Chicago Pizza Store
	class ChPizzaStore : public PizzaStore
	{
	public:
		Pizza* createPizza(std::string type) override;
	};

// New York Pizza
	class NYCheesePizza : public Pizza
	{
	public:
		NYCheesePizza()
			: Pizza( "NY Style Sauce and Cheese Pizza", 
				"Marinara Sauce", "Thin Crust Dough", 
				{ "t1", "t2" } )
		{
			addTopping("t3");
		}
		void bake() { std::cout << "Bake for 15 minutes at 250C, " << Pizza::getName() << '\n'; };			
		~NYCheesePizza() override { std::cout << "NYCheesePizza obj destroyed\n"; }
	}; 


	class NYVeggiePizza : public Pizza
	{
	public:
		NYVeggiePizza()
			: Pizza("NY Style Sauce and Cheese Pizza",
				"Marinara Sauce", "Thin Crust Dough",
				{ "Veggie1", "Veggie2" })
		{
			addTopping("Veggie3");
		}
		~NYVeggiePizza() override { std::cout << "NYVeggiePizza obj destroyed\n"; }
	};

	
	class NYClamPizza : public Pizza
	{
	public:
		NYClamPizza()
			: Pizza("NY Style Sauce and Cheese Pizza",
				"Marinara Sauce", "Thin Crust Dough",
				{ "Clam1", "Clam2" })
		{
			addTopping("Clam3");
		}
		~NYClamPizza() override { std::cout << "NYClamPizza obj destroyed\n"; }
	};

	// Chicago Style Pizza

	class ChicagoCheesePizza : public Pizza
	{
	public:
		ChicagoCheesePizza()
			: Pizza("Chicago Style Deep Dish Cheese Pizza",
				"Plum Tomato Sauce", "Extra Thick Crust Dough",
				{ "c1", "c2" })
		{
			addTopping("c3");
		}
		~ChicagoCheesePizza() override { std::cout <<"ChicagoCheesePizza obj destroyed\n";}
	};

	class ChicagoVeggiePizza : public Pizza
	{
	public:
		ChicagoVeggiePizza()
			: Pizza("Chicago Style Deep Dish Veggie Pizza",
				"Plum Tomato Sauce", "Extra Thick Crust Dough",
				{ "v1", "v2" })
		{
			addTopping("v3");
		}
		~ChicagoVeggiePizza() override { std::cout << "ChicagoVeggiePizza obj destroyed\n"; }
	};

}

