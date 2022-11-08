// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include "bird.h"
#include "human.h"
#include "smartBird.h"

void bird();
void human();
void smartbird();
int main()
{
    //bird();
    //human();
    smartbird();
 }

void human()
{
    using namespace people;
    std::vector<Base*> s;
    Human1* h = Human1().clone();
    Human2* h1 = Human2().clone();
    h->info();
    s.push_back(Human1().clone());
    s.push_back(new Human1());
    s.push_back(new Human2());
    s.push_back(Human2().clone());

    for (auto v : s)
        (static_cast<const Base1*>(v)->info());
}


void smartbird()
{
    using namespace SmartBird;
    Duck s;
    s.display();

    //Duck s2(std::unique_ptr<FlyBehavior>(new FlyNoWay()), std::unique_ptr<QuackBehavior>(new MuteQuack()));
    Duck s2(std::make_unique<FlyNoWay>(), std::make_unique<MuteQuack>());
    s2.display();
    std::cout << "vector\n";
    std::vector<Duck> vDucks;
    vDucks.push_back(Duck(std::make_unique<FlyWithWings>(), std::make_unique<Squeak>()));
    vDucks.push_back(Duck(std::make_unique < FlyWithWings>(), std::make_unique < Quack>()));
    vDucks.push_back(Duck(std::make_unique < FlyWithWings>(), std::make_unique < MuteQuack>()));
    vDucks.push_back(s);
    vDucks.push_back(s2);
    vDucks.push_back(s2);
    vDucks.at(vDucks.size() - 1) = s;
    for (auto &v : vDucks)
        v.display();
    std::cout << &*vDucks.begin() << " " << &*vDucks.end();
}

void bird()
{
    Bird::Duck s;
    s.display();

    Bird::Duck s2(new Bird::FlyNoWay(), new Bird::MuteQuack());
    s2.display();

    std::vector<Bird::Duck> vDucks;
    vDucks.push_back(Bird::Duck(new Bird::FlyWithWings(), new Bird::Squeak()));
    vDucks.push_back(Bird::Duck(new Bird::FlyWithWings(), new Bird::Quack()));
    vDucks.push_back(Bird::Duck(new Bird::FlyWithWings(), new Bird::MuteQuack()));

    for (auto &v : vDucks)
        v.display();
}


