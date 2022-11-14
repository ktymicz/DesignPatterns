// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include "bird.h"
#include "human.h"
#include "smartBird.h"
#include "FLTK_PPAP/Simple_window.h"

// constants
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


void bird();
void human();
void smartbird();
static void cb(Graph_lib::Address s, Graph_lib::Address addr);
int main()
{
    std::string s = "The patterns";
    //bird();
    //human();
    //smartbird();
    Graph_lib::Simple_window win(orig, width_window, height_window, s);
    Graph_lib::Box b(Graph_lib::Point(30, 30), 30, 30);
    win.attach(b);


    Graph_lib::Button but(Graph_lib::Point(60, 60), 50, 50, "wow", cb);
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
    std::cout << (static_cast<Fl_Widget*>(w))->label() << '\n'
        << static_cast<Graph_lib::Simple_window*>(addr) << '\n';
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


