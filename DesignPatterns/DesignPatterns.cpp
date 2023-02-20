// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include "bird.h"
#include "human.h"
#include "smartBird.h"
#include "FLTK_PPAP/Simple_window.h"


#include "TheFactoryPattern.h"
#include "SimpleSingleton.h"
#include "TheCommandPatttern.h"
#include "FLTK_PPAP/Simple_window.h"

// constants for a window, 
constexpr int width_window = 800;//1920/2;
constexpr int height_window = 800;///1080/2;
constexpr  int x_org = width_window / 2;
constexpr  int y_org = height_window / 2;
constexpr int dif_g = 100; // make axis smaller in graph
constexpr  int x_length = width_window - dif_g;
constexpr  int y_length = height_window - dif_g;
constexpr int xscale = 50;
constexpr int yscale = 10;
const Graph_lib::Point orig{ x_org, y_org };

const char* cbutton = "One Piece";
// functions
void bird();
void human();
void smartbird();

static void cb(Graph_lib::Address s, Graph_lib::Address addr);
void use_cb();

// Head first Design Patterns
void use_FactoryPattern();
void onlyOneInstance();
void use_CommandPattern();


int main()
{
    
    //bird();
    //human();
    //smartbird();
    //use_cb();
    //use_FactoryPattern();
    //onlyOneInstance();
    use_CommandPattern();
 }

void use_CommandPattern()
{
    using namespace CommandPattern;
    RemoteControlTest::main("Hello The Command Pattern");

}



void onlyOneInstance()
{
    std::string st("hello, SIngleton here");
    SimpleSingleton* b1 = SimpleSingleton::createSingleton();
    SimpleSingleton* b2 = SimpleSingleton::createSingleton();
    SimpleSingleton* b3 = SimpleSingleton::createSingleton();
}
void use_FactoryPattern()
{
    //TheFactoryPattern::NYCheesePizza s;
    //s.prepare();
    TheFactoryPattern::ChPizzaStore chstore;
    using namespace TheFactoryPattern;
    Pizza* s = chstore.orderPizza("cheese");
    Pizza* chveggie = chstore.orderPizza("veggie");

    NYPizzaStore nystore;
    Pizza* nycheese = nystore.orderPizza("cheese");
    
    Pizza* nyveggie = nystore.orderPizza("veggie");
}

void use_cb()
{
    std::string s = "The patterns";
    Graph_lib::Simple_window win(orig, width_window, height_window, s);
    Graph_lib::Box b(Graph_lib::Point(30, 30), 30, 30);
    win.attach(b);


    Graph_lib::Button but(Graph_lib::Point(60, 60), 100, 50, "wow", cb);
    win.attach(but);
    std::cout << "addr but: " << &but << '\n'
        << "addr simple_win: " << &win << '\n'
        << "win label:" << win.label() << '\n';
    win.wait_for_button();
}


static void cb(Graph_lib::Address w, Graph_lib::Address addr) // callback for next_button
//	{ reference_to<Simple_window>(addr).next(); }
{
    //static_cast<Graph_lib::Simple_window*>(addr);
    std::cout << static_cast<Fl_Widget*>(w)->label()<<":" << (static_cast<Fl_Widget*>(w)) << '\n'
        << static_cast<Graph_lib::Simple_window*>(addr)->label() << ":" << static_cast<Graph_lib::Simple_window*>(addr) << '\n';
    if (static_cast<Fl_Widget*>(w)->label() != cbutton)
    {
        std::cout << static_cast<Fl_Widget*>(w)->label() << " changed to " << cbutton << '\n';
        static_cast<Fl_Widget*>(w)->label(cbutton);
        
    }
        
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


