#pragma once

#include <string>
class Beverage
{

public:
	
	virtual float cost() = 0;
	virtual std::string descritpion();

};



class Decaf : public Beverage
{
	std::string s;
	float c;
public:
	float cost() override { return c; }
	std::string descritpion() override { return s; }

	Decaf(std::string str, float cost) 
		: c{cost}, s{str}
	{}
};


class CondimentDecorator :public Beverage
{
public:
	Beverage* pb;
	float cost() override;
	std::string descritpion() override;
};