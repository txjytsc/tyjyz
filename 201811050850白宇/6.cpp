#include<iostream>
#include <math.h>
using namespace std;

class vehicle
{
	protected:
	int wheels;
	int weight;
	public:
	vehicle(int wh, int we)
	{
		wheels = wh;
		weight = we;
	}
	void show()
	{
		cout << "轮子数=" << wheels << ",车重量=" << weight << endl;
	}


};
class car:private vehicle
{
	int passenger_load;
	public:
	car(int wh, int we, int pa) :vehicle(wh,we)
	{
		passenger_load = pa;
	}	
	void show()
	{
		vehicle::show();
		cout << "载客量=" << passenger_load << endl;
	}
};

class truck :private vehicle
{
	int passenger_load;
	int payload;
	public:
	truck(int wh, int we, int pa,int pay) :vehicle(wh, we)
	{
		passenger_load = pa;
		payload = pay;
	}
	void show()
	{
		vehicle::show();
		cout << "载客量=" << passenger_load << "载货量=" << payload << endl;
	}
};


void main()
{
	vehicle v(4, 24);
	v.show();


	car c(8, 20, 5);
	c.show();


	truck t(12, 5, 6, 8);
	t.show();

}