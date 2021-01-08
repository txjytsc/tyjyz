//
//  main.cpp
//  3.奖学金
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
    int yuwen,shuxue,yingyu;
    int num,sum;
}student[100];
int cmp(node x,node y)
{
    if(x.sum!=y.sum) return x.sum>y.sum;
    if(x.yuwen!=y.yuwen) return x.yuwen>y.yuwen;
    if(x.num!=y.num) return x.num<y.num;
    return 0;
}
int main()
{
    int i,n;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>student[i].yuwen>>student[i].shuxue>>student[i].yingyu;
        student[i].num=i+1;
        student[i].sum=student[i].yuwen+student[i].shuxue+student[i].yingyu;
    }
    sort(student,student+n,cmp);
    for(i=0;i<5;i++)
        cout<<student[i].num<<" "<<student[i].sum<<endl;
    return 0;
}
