//
//  main.cpp
//  hanshu_wenti(3)
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
using namespace std;
void fun(int *a,int *b,int *c)
{
    //int a_len=sizeof(a);
   // int b_len=strlen(b)-6;
    *c=*a/10*10+*a%10*1000+*b%10*100+*b/10;
}
int main()
{
    int a,b,c;
   // cout<<"请输入你所要输入的两个数:"<<endl;
    cin>>a>>b;
    fun(&a,&b,&c);
    cout<<c<<endl;
   // cout<<"两个数的合并值为:"<<c<<endl;
}
