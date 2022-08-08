#pragma once
#include <iostream>
#include <typeinfo>
namespace Bird {

	class FlyBehavior
	{
	public:
		virtual void fly() = 0;
		virtual FlyBehavior* clone() const = 0;
		
		
	};

	class FlyWithWings : public FlyBehavior
	{
	public:
		virtual void fly() override { std::cout << "I'm flying!!!\n"; } ;
		FlyWithWings* clone() const override 
		{ 
			return new FlyWithWings(*this);
			//FlyBehavior* ret =  new FlyWithWings(*this); 
			//return ret;
		}
	};

	class FlyNoWay : public FlyBehavior
	{
	public:
		virtual void fly() override { std::cout << "I can't fly\n"; }
		FlyNoWay* clone() const override { return new FlyNoWay(*this); }
	};


	class QuackBehavior
	{
	public:
		virtual void quack() = 0;
		virtual QuackBehavior* clone() const = 0;
	};

	class Quack : public QuackBehavior
	{
	public:
		
		void quack() override
		{
			std::cout << "quack\n";
		}
		Quack* clone() const override { return new Quack(*this); }


	};

	class Squeak : public QuackBehavior
	{
	public:
		void quack() override
		{
			std::cout << "rubber duckie squeak\n";
		}
		Squeak* clone() const override { return new Squeak(*this); }

	};

	class MuteQuack : public QuackBehavior
	{
	public:
		void quack() override
		{
			std::cout << "do nothing - can't quack!\n";
		}
		MuteQuack* clone() const override { return new MuteQuack(*this); }
	};



	class Duck
	{
	public:
		Duck():
			flybehavior(new FlyWithWings()),
			quackbehavior(new Quack())
		{}
		Duck(FlyBehavior* pflyB, QuackBehavior* pquckB) :
			flybehavior(pflyB), 
			quackbehavior(pquckB)
		{}
		Duck(const Duck& other)// copy constructor
			: flybehavior(other.flybehavior->clone()), quackbehavior(other.quackbehavior->clone())
		{}
		//Duck(Duck&& other) /// move constructor
		//{

		//}

		//Duck& operator=(const Duck& other) // assignment operator
		//{

		//}
		//Duck& operator=(Duck&& other) // move assigment operator
		//{

		//}
		
		void swim() { std::cout << "All ducks float, even decoys!"; };
		void display() { performFly(); performQuack(); };
		void performFly()
		{
			flybehavior->fly();
		}
		void performQuack()
		{
			quackbehavior->quack();
		}
		~Duck() 
		{
			//~FlyBehavior();
			//~QuackBehavior();
			delete flybehavior;
			delete quackbehavior;
		}
	private:
		FlyBehavior* flybehavior;  // p to one
		QuackBehavior* quackbehavior; // p to one 		
	};
}
