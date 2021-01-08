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
		cout << "������=" << wheels << ",������=" << weight << endl;
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
		cout << "�ؿ���=" << passenger_load << endl;
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
		cout << "�ؿ���=" << passenger_load << "�ػ���=" << payload << endl;
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