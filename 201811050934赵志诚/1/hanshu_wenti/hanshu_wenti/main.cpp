//
//  main.cpp
//  hanshu_wenti
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
int fun(int a,int b)
{
    int c=a/10*10+a%10*1000+b%10*100+b/10;
    return c;
}
int main()
{
    int a,b,c;
    //cout<<"请输入你所要输入的两个数:"<<endl;
    cin>>a>>b;
    c=fun(a,b);
    //cout<<"两个数的合并值为:"<<c<<endl;
    cout<<c<<endl;
    return 0;
}
