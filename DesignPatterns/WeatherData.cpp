#include "WeatherData.h"

namespace Weather {


	// friends
	
	// ostream
	
	std::ostream& operator<<(std::ostream& os, Observer& ob)
	{
		os << "Current conditions\n"
			<< "humidity: " << ob.m.humidity
			<< " %, pressure: " << ob.m.pressure
			<< " Pa, temp: " << ob.m.temp << " C degrees" << '\n';
		return os;
	};

	
	std::ostream& operator<<(std::ostream& os, const Display& d)
	{
		os << "Current conditions\n"
			<< "avg. humidity: " << d.ob.get_Data().humidity
			<< " %, avg. pressure: " << d.ob.get_Data().pressure
			<< " Pa, avg. temp: " << d.ob.get_Data().temp << " C degrees" << '\n';
		return os;
	}

	// helper functions
	// 
	float computeHeatIndex(float t, float rh) {
		float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) +
			(0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) +
			(0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
			(0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
				(rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
			(0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
			0.000000000843296 * (t * t * rh * rh * rh)) -
			(0.0000000000481975 * (t * t * t * rh * rh * rh)));
		return index;
	}
}

