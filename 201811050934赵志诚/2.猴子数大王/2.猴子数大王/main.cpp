//
//  main.cpp
//  2.猴子数大王
//
//  Created by 赵志诚 on 2020/12/21.
//  Copyright © 2020年 赵志诚. All rights reserved.
//

#include <iostream>
using namespace std;
struct Monkey
{
    int num;
    struct Monkey *next;
};
int main()
{
    int m,n,i,j,king;
    Monkey *head, *p1,*p2;
    cin>>m>>n;
    if(n==1)
    {
        king=m;
    }
    else
    {
        p1=p2=new Monkey;
        head = p1;
        p1->num=1;
        for(i=1; i<m; i++)
        {
            p1=new Monkey;
            p1->num=i+1;
            p2->next=p1;
            p2=p1;
        }
        p2->next=head;
        p1=head;
        for(i=1; i<m; i++)
        {
            for(j=1; j<n-1; j++)
                p1=p1->next;
            p2=p1->next;
            p1->next=p2->next;
            p1=p2->next;
            delete p2;  
        }
        king=p1->num;
        delete p1;
    }
    cout<<king<<endl;
    return 0;
}
