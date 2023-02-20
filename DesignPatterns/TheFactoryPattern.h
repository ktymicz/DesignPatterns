#pragma once
#include <string>
#include <iostream>
#include <list>

#include <algorithm>
#include <memory>

namespace TheFactoryPattern
{
	// Ingridients
	struct Dough
	{
		std::string d{ "dough" };
		/*friend std::ostream& operator<<(std::ostream& os, Dough& d);*/
	};

	struct ThinCrustDough : public Dough 
	{
		ThinCrustDough() { d = "thin crust dough"; };
	};

	struct ExtraThickCrustDough : public Dough 
	{
		ExtraThickCrustDough() { d = "extra thick crust dough"; }
	};

	struct Sauce 
	{ std::string s{"sauce" }; };

	struct MarinaraSauce : public Sauce
	{
		MarinaraSauce() { s = "marinara sauce"; }
	};

	struct PlumTomatoSauce : public Sauce
	{
		PlumTomatoSauce() { s = "plum tomato sauce"; }
	};

	struct Cheese 
	{ std::string ch{"cheese"}; };

	struct ReggianoCheese :public Cheese
	{
		ReggianoCheese() { ch = "reggiano cheese"; }
	};

	struct MozzarellaCheese : public Cheese 
	{
		MozzarellaCheese() { ch = "fresh real mozzarella cheese"; }
	};

	struct Veggies
	{std::string v{"garlic, onion, mushroom, redpepper, olive"}; };

	struct Pepperoni 
	{ std::string p{"pepperoni"}; };
	
	struct SlicedPepperoni :public Pepperoni
	{
		SlicedPepperoni() { p = "sliced pepperoni"; }
	};

	struct Clams 
	{ std::string cl{"clams"}; };
	
	struct FreshClams : public Clams
	{
		FreshClams() { cl = "fresh clams"; }
	};

	struct FrozenClams : public Clams
	{
		FrozenClams() { cl = "frozen clams"; }
	};

	class PizzaIngredientFactory
	{
	public:
		PizzaIngredientFactory() = default;
		PizzaIngredientFactory(const PizzaIngredientFactory& copy) = default;
		PizzaIngredientFactory(PizzaIngredientFactory&& move) = default;
		PizzaIngredientFactory& operator=(const PizzaIngredientFactory& copy) = default;
		PizzaIngredientFactory& operator=(PizzaIngredientFactory&& move) = default;
		virtual Dough createDough() { return Dough(); }
		virtual Sauce createSauce() { return Sauce(); }
		virtual Cheese createCheese() { return Cheese(); }
		virtual Veggies createVeggies() { return Veggies(); }
		virtual Pepperoni createPepperoni() { return Pepperoni(); }
		virtual Clams createClam() { return Clams(); }
	};

	class NYPizzaIngredientFactory : public PizzaIngredientFactory 
	{
	public:
		Dough createDough() override { return ThinCrustDough(); }
		Sauce createSauce()override { return MarinaraSauce(); };
		Cheese createCheese()override{ return ReggianoCheese(); };
		// Veggies createVeggies()override { return Veggies(); };
		Pepperoni createPepperoni()override { return SlicedPepperoni(); };
		Clams createClam()override { return FreshClams(); };

	};
	class CHPizzaIngredientFactory : public PizzaIngredientFactory
	{
	public:
		Dough createDough() override { return ExtraThickCrustDough(); }
		Sauce createSauce()override { return PlumTomatoSauce(); };
		Cheese createCheese()override { return MozzarellaCheese(); };
		// Veggies createVeggies()override { return Veggies(); };
		Pepperoni createPepperoni()override { return SlicedPepperoni(); };
		Clams createClam()override { return FrozenClams(); };
	};


	class Pizza
	{
	protected:
		std::string nameo;
		Sauce sauceo;
		Dough dougho;
		Veggies veggieso;
		Cheese cheeseo;
		Pepperoni pepperonio;
		Clams clamo;

		std::list<std::string> toppingso;

	public:
		Pizza(std::string name, std::string sauce, std::string dough, std::list<std::string> toppings);

		Pizza(std::string name);
		Pizza() = default;

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

		void bake() { std::cout << "Bake for 15 minutes at 250C, " << '\n'; };
		void cut() { std::cout << "Cutting the pizza into diagonal slices" << '\n'; }
		void box() { std::cout << "Place pizza in official PizzaStore box\n"; }
		std::string getName() { return nameo; }
		void setName(std::string name) { nameo = name; }
		virtual ~Pizza() { std::cout << "Pizza obj destroyed\n"; }
	};
	
	// The factory method is declered here, createPizza

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


	// Cheese Pizza
	class CheesePizza : public Pizza
	{
		 PizzaIngredientFactory* ingredientFactory;

	public:
		CheesePizza(PizzaIngredientFactory* pingredientFactory);
		void prepare() override;
		~CheesePizza() override {
			std::cout << "CheesePizza obj destroyed\n";
			delete ingredientFactory;
		}
	}; 

	class VeggiePizza : public Pizza
	{
		PizzaIngredientFactory* ingredientFactory;

	public:
		VeggiePizza(PizzaIngredientFactory* pingredientFactory)
			: Pizza(), ingredientFactory(pingredientFactory)
		{
			addTopping("Veggie3");
		}
		void prepare() override;
		~VeggiePizza() override {
			std::cout << "VeggiePizza obj destroyed\n";
			delete ingredientFactory;
		}
	};

	// old design NY and CH, used in NYPizzaStore and ChPizzaStore ::createPizza(std::string type)
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

