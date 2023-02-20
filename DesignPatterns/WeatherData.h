#pragma once
#include <iostream>
#include <fstream>
#include <vector>

namespace Weather {
	// -----------------------------------------------------------------------
	// classes
	struct Measurement_Data
	{
		// measurement values
		float temp{ -100 };
		float humidity{ -100 };
		float pressure{ -100 }; // barometric pressure
		Measurement_Data() {}
		Measurement_Data(float t, float h, float p) : temp(t), humidity(h), pressure(p) {}
	};

	class Observer
	{
		Measurement_Data m;
	public:
		virtual void update(Measurement_Data& d) {
			m.temp = d.temp;
			m.humidity = d.humidity;
			m.pressure = d.pressure;
		}

		const Measurement_Data& get_Data() const { return m; };

		void display() { std::cout << *this; }
		friend std::ostream& operator<<(std::ostream& os, Observer& ob);

	};

	class WeatherData
	{
		Measurement_Data m;
		std::vector<Observer*> observers;

	public:
		void register_observer(Observer* ob) { observers.push_back(ob); };
		void remove_observer(Observer* ob)
		{ 
			for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end();)
			{
				if (*it == ob)
				{
					observers.erase(it);
					break;
				}
				else 
					++it;
			}
				
		};
		void notify_observers()
		{
			for (auto& ob : observers)
				ob->update(m);
		};

		void get_Data() 
		{
			m.temp = get_temperature();
			m.pressure = get_pressure();
			m.humidity = get_humidity();
		}

		float get_temperature() { return 20; };
		float get_humidity() { return 20; };
		float get_pressure() { return 20; };
		
		void measurements_changed() { notify_observers(); };
		
		void set_measurements(Measurement_Data& d)
		{
			m.humidity = d.humidity;
			m.pressure = d.pressure;
			m.temp = d.temp;
			measurements_changed();
		}

	};
	
	class Display_Average : public Observer
	{
		Measurement_Data total;
		int measurements_number;

	public:
		// calculates sth important
		void calculate()
		{
			total.humidity += get_Data().humidity;
			total.pressure += get_Data().pressure;
			total.temp += get_Data().temp;
			++measurements_number;
		};

		Display_Average() : Observer(Observer()), total(0, 0, 0), measurements_number{ 0 }
		{}
		Observer& get_Observer() { return *this; };
		friend std::ostream& operator<<(std::ostream& os, const Display_Average& d)
		{
			os << "Current conditions\n"
				<< "avg. humidity: " << d.total.humidity / d.measurements_number
				<< " %, avg. pressure: " << d.total.pressure / d.measurements_number
				<< " Pa, avg. temp: " << d.total.temp / d.measurements_number  << " C degrees" << '\n';
			return os;
		}
		virtual void update(Measurement_Data& d) override
		{
			Observer::update(d);
			calculate();
		}
	};

	class Display
	{
		Observer ob;
		Measurement_Data total;
		int measurements_number;

	public:
		// calculates sth important
		void calculate() 
		{
			total.humidity += ob.get_Data().humidity;
			total.pressure += ob.get_Data().pressure;
			total.temp += ob.get_Data().temp;
			++measurements_number;
		};

		Display() :ob(Observer()), total(0,0,0), measurements_number{0}
		{}
		Observer& get_Observer() { return ob; };

		friend std::ostream& operator<<(std::ostream& os, const Display& d);
	};
	// -----------------------------------------------------------------------
	// helper functions
	float computeHeatIndex(float t, float rh);


}
// WeatherData