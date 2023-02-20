#pragma once

#include <string>
#include <iostream>
class SimpleSingleton
{
protected:
	static SimpleSingleton* uniqueinstance;
	SimpleSingleton(const std::string s);
	SimpleSingleton();
public:
	
	SimpleSingleton(SimpleSingleton&) = delete;
	void operator=(const SimpleSingleton&) = delete;
	static SimpleSingleton* createSingleton();
	~SimpleSingleton() { if(uniqueinstance) delete uniqueinstance; }
};



