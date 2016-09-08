#include "std_lib_facilities.h"
#include <deque>
#include <sstream>
#include <fstream>

class Mpg_log
{
private:
	double last_odometer;
	double current_odometer;
	double current_miles_traveled;
	double current_gas;
	double total_miles_traveled;
	double total_gas;
	deque<double> recent_miles_traveled;
	deque<double> recent_gas;

	double initial_odometer;
	vector<string> file_content;
	vector<double> file_odometer;
	vector<double> file_gas;
	vector<double> file_this_mpg;
	vector<double> file_total_mpg;
	vector<double> file_roll_avg_mpg;

public:
	void buy_gas(double odometer, double gas)
	{
		last_odometer = current_odometer;
		current_odometer = odometer;
		current_miles_traveled = current_odometer - last_odometer;

		current_gas = gas;

		total_miles_traveled += current_miles_traveled;
		total_gas += current_gas;

		recent_miles_traveled.push_back(current_miles_traveled);
		recent_gas.push_back(current_gas);

		if (recent_gas.size() == 6)
		{
			recent_gas.pop_front();
			recent_miles_traveled.pop_front();
		}
	}

	double get_current_mpg()
	{
		double current_mpg = current_miles_traveled / current_gas;
		return current_mpg;
	}

	double get_total_mpg()
	{
		double total_mpg = total_miles_traveled / total_gas;
		return total_mpg;
	}

	double get_rolling_average_mpg()
	{
		if (recent_gas.size() < 5)
		{
			return get_total_mpg();
		}

		else
		{
			double miles_traveled_sum = 0, gas_sum = 0;
			for (int i = 0; i < recent_gas.size(); ++i)
			{
				miles_traveled_sum += recent_miles_traveled[i];
				gas_sum += recent_gas[i];
			}

			double rolling_average_mpg = miles_traveled_sum / gas_sum;
			return rolling_average_mpg;
		}
	}

	void read_file(string file_name)
	{
		ifstream file_data(file_name);
		string file_line;
		int row = 0, column;
		while (getline(file_data, file_line))
		{
			column = 0;

			file_content.push_back(file_line);

			stringstream line_data(file_line);
			string file_cell;
			while (getline(line_data, file_cell, ','))
			{
				if (row == 1 && column == 1)
				{
					double temp_odometer = atof(file_cell.c_str());
					initial_odometer = temp_odometer;
				}

				else if (row > 1 && column == 1)
				{
					double temp_odometer = atof(file_cell.c_str());
					file_odometer.push_back(temp_odometer);
				}

				else if (row > 1 && column == 2)
				{
					double temp_gas = atof(file_cell.c_str());
					file_gas.push_back(temp_gas);
				}
				++column;
			}
			++row;
		}
	}

	void set_initial_values()
	{
		current_odometer = initial_odometer;
		total_miles_traveled = 0;
		total_gas = 0;
	}

	void do_calculations_on_input()
	{
		for (int i = 0; i < file_gas.size(); ++i)
		{
			buy_gas(file_odometer[i], file_gas[i]);
			file_this_mpg.push_back(get_current_mpg());
			file_total_mpg.push_back(get_total_mpg());
			file_roll_avg_mpg.push_back(get_rolling_average_mpg());
		}
	}

	void write_file(string file_name)
	{
		ofstream file_output;
		file_output.open(file_name);

		file_output << file_content[0] << ",This MPG,Total MPG,Rolling Average MPG" << endl;
		file_output << file_content[1] << endl;
		for (int i = 0; i < file_gas.size(); ++i)
		{
			file_output << file_content[i + 2] << ',' << file_this_mpg[i] << ',' << file_total_mpg[i] << ',' << file_roll_avg_mpg[i] << endl;
		}

		file_output.close();
	}
};

int main()
{
	Mpg_log logger;
	string file_output_name;
	cout << "Please enter your desired name for the ouput file [exclude .csv]: ";
	getline(cin, file_output_name);
	file_output_name += ".csv";

	cout << "Reading file ..." << endl;
	logger.read_file("Mileage_Log_for_Extreme_Bonus.csv");
	logger.set_initial_values();

	cout << "Performing calculations ..." << endl;
	logger.do_calculations_on_input();

	cout << "Writing to " << file_output_name << " ..." << endl;
	logger.write_file(file_output_name);

	cout << "Program complete ..." << endl << endl;

	keep_window_open();
	return 0;
}