//
//  main.cpp
//  hanshu_wenti(2)
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
void fun(int &x,int &y,int &c)
{
      c=x/10*10+x%10*1000+y%10*100+y/10;
}
int main()
{
    int a,b,c;
    //cout<<"请输入两个整数:"<<endl;
    cin>>a>>b;
    fun(a,b,c);
    //cout<<"两个整数问题的和为："<<c<<endl;
    cout<<c<<endl;
    return 0;
}
