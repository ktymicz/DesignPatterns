#include "SimpleSingleton.h"


SimpleSingleton* SimpleSingleton::createSingleton()
{
	if(!uniqueinstance)
		uniqueinstance = new SimpleSingleton("work");
	return uniqueinstance;
}


SimpleSingleton::SimpleSingleton(const std::string s)
{
	std::cout << s << " is created.\n";
}

SimpleSingleton* SimpleSingleton::uniqueinstance = nullptr;