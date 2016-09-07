#include "std_lib_facilities.h"

class Mpg_log
{
private:
	double last_odometer;
	double current_odometer;
	double current_miles_traveled;
	double current_gas;

public:
	Mpg_log(double initial_odometer)
	{
		current_odometer = initial_odometer;
	}

	void buy_gas(double odometer, double gas)
	{
		last_odometer = current_odometer;
		current_odometer = odometer;
		current_miles_traveled = current_odometer - last_odometer;
		current_gas = gas;
	}

	double get_current_mpg()
	{
		double current_mpg = current_miles_traveled / current_gas;
		return current_mpg;
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

	while (true)
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