//
//  main.cpp
//  6. 面向对象
//
//  Created by 赵志诚 on 2021/1/6.
//  Copyright © 2021年 赵志诚. All rights reserved.
//

#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
class vehicle
{
protected:
    int wheels;
    double weight;
public:
    vehicle(int wh,double we)
    {
        wheels=wh;
        weight=we;
    }
    vehicle(){}
    void cout_vehicle()
    {
        cout<<"wheels:"<<wheels<<endl;
        cout<<"weight: "<<weight<<endl;
    }
    
};

class car :private vehicle
{
public:
    int passenger_load;
    car(int p,int wh,double we)
    {
        passenger_load=p;
        wheels=wh;
        weight=we;
    }
    void cout_car()
    {
        this->cout_vehicle();
        cout<<"passenger: "<<this->passenger_load<<endl;
    }
};

class truck :private vehicle
{
public:
    int passenger_load;
    double payload;
    truck(int pa,double pay,int wh,double we)
    {
        passenger_load=pa;
        payload=pay;
        wheels=wh;
        weight=we;
    }
    void cout_truck()
    {
        this->cout_vehicle();
        cout<<"passenger:"<<this->passenger_load<<endl;
        cout<<"payload: "<<this->payload<<endl;
    }
};

int main()
{
    vehicle v1(4,199.2);
    v1.cout_vehicle();
    cout<<endl;
    
    car c1(5,150,12);
    c1.cout_car();
    cout<<endl;
    
    truck t1(12,120.2,6,42.2);
    t1.cout_truck();
    cout<<endl;
    
}





