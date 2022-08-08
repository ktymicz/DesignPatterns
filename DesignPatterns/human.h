#pragma once
#include <string>
#include <iostream>
namespace people 
{
	//struct Data, Information, basicData, bornData{}
	struct Body
	{
		double hight{-1};
		double weight{-1};
	};
	struct State
	{
		double exist_since{0.0}; // date is double in the spirit of simplicity, for now
		std::string name{"state"};
	};

	class Base
	{
	public:
		virtual void info() const = 0;
	};

	class Base1 : public Base
	{
		Body b;
	public:
		virtual void info() const override
		{
			std::cout << "hight: " << b.hight << ", weight: " << b.weight << '\n';
		}

	};

	class Base2 : public Base1
	{
		State s;
	public:
		virtual void info() const override
		{
			Base1::info();
			std::cout << "born: " << s.exist_since << ", name: " << s.name << '\n';
		}

	};


	template <class Derived>
	class DerivationHelper
	{
		friend Derived;
		DerivationHelper(){}
	public:
		virtual Derived* clone() const
		{
			return new Derived(static_cast<const Derived&>(*this)); // call copy ctor
		}

	};





	class Human1 : public DerivationHelper<Human1>, public Base1
	{
	
		// Base* clone(); is inherited from DerivationHelper
	};

	class Human2 : public DerivationHelper<Human2>, public Base2
	{
		// Base* clone(); is inherited from DerivationHelper
	};



}


