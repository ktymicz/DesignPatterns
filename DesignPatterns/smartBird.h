#pragma once
#pragma once
#include <iostream>
#include <typeinfo>
#include <memory>
namespace SmartBird {

	class FlyBehavior
	{
	public:
		virtual void fly() = 0;
		virtual std::unique_ptr<FlyBehavior> clone() const = 0;


	};

	class FlyWithWings : public FlyBehavior
	{
	public:
		virtual void fly() override { std::cout << "I'm flying!!!\n"; };
		std::unique_ptr<FlyBehavior> clone() const override
		{
			return std::make_unique<FlyWithWings>(*this);
			//FlyBehavior* ret =  new FlyWithWings(*this); 
			//return ret;
		}
	};

	class FlyNoWay : public FlyBehavior
	{
	public:
		virtual void fly() override { std::cout << "I can't fly\n"; }
		std::unique_ptr<FlyBehavior> clone() const override 
		{
			return std::make_unique<FlyNoWay>(*this); 
		}
	};


	class QuackBehavior
	{
	public:
		virtual void quack() = 0;
		virtual std::unique_ptr<QuackBehavior> clone() const = 0;
	};

	class Quack : public QuackBehavior
	{
	public:

		void quack() override
		{
			std::cout << "quack\n";
		}
		std::unique_ptr<QuackBehavior> clone() const override 
		{
			return std::make_unique<Quack>(*this); 
		}


	};

	class Squeak : public QuackBehavior
	{
	public:
		void quack() override
		{
			std::cout << "rubber duckie squeak\n";
		}
		std::unique_ptr<QuackBehavior> clone() const override 
		{
			return std::make_unique<Squeak>(*this); 
		}
	};

	class MuteQuack : public QuackBehavior
	{
	public:
		void quack() override
		{
			std::cout << "do nothing - can't quack!\n";
		}
		std::unique_ptr<QuackBehavior> clone() const override 
		{
			return std::make_unique<MuteQuack>(*this); 
		}
	};

	//Duck(FlyBehavior* pflyB, QuackBehavior* pquckB) :
	//	flybehavior(std::move(pflyB)),
	//	quackbehavior(std::move(pquckB))
	//{}

	class Duck
	{
	public:
		Duck() :
			flybehavior(std::make_unique<FlyWithWings>()),
			quackbehavior(std::make_unique<Quack>())
		{}
		Duck(std::unique_ptr<FlyBehavior>pflyB, std::unique_ptr<QuackBehavior>pquckB) :
			flybehavior(std::move(pflyB)),
			quackbehavior(std::move(pquckB))
		{}
		Duck(const Duck& other)// copy constructor
			: flybehavior(other.flybehavior->clone()), quackbehavior(other.quackbehavior->clone())
		{}
		Duck(Duck&& other) /// move constructor
			: flybehavior(std::move(other.flybehavior)), quackbehavior(std::move(other.quackbehavior))
		{

		}

		Duck& operator=(const Duck& other) // assignment operator
		{
			flybehavior = other.flybehavior->clone();
			quackbehavior = other.quackbehavior->clone();
			return (*this);
		}
		Duck& operator=(Duck&& other) // move assigment operator
		{
			flybehavior = std::move(other.flybehavior);
			quackbehavior = std::move(other.quackbehavior);
			return (*this);
		}

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
		}
	private:
		std::unique_ptr<FlyBehavior> flybehavior;  // p to one
		std::unique_ptr<QuackBehavior> quackbehavior; // p to one 		
	};
}


