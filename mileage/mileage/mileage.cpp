#include "std_lib_facilities.h"

class Mpg_log
{
private:
	double last_odometer;
	double this_odometer;
	double this_gas;

public:
	Mpg_log(double initial_odometer)
	{
		this_odometer = initial_odometer;
	}

	void buy_gas(double odometer, double gas)
	{
		last_odometer = this_odometer;
		this_odometer = odometer;
		this_gas = gas;
	}

	double get_current_mpg()
	{
		double miles_traveled = this_odometer - last_odometer;
		double mpg = miles_traveled / this_gas;
		return mpg;
	}
};

int main()
{
	cout << "Initial odometer reading: ";
	double initial_odometer;
	cin >> initial_odometer;

	Mpg_log logger(initial_odometer);
	double odometer;
	double gas;

	while(true)
	{
		cout << "\nCurrent odometer reading: ";
		cin >> odometer;
		cout << "Gallons of gas purchased: ";
		cin >> gas;

		logger.buy_gas(odometer, gas);
		cout << "This mpg: " << logger.get_current_mpg() << endl;
	} 
	return 0;
}