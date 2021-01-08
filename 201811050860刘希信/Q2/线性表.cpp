
#include <iostream>
using namespace std;
struct Monkey
{
    int num;  //猴子的编号
    struct Monkey *next; //下一只猴子
};
 
int main()
{
    int m,n,i,j,king;
    Monkey *head, *p1,*p2;
	cout<<"输入猴子个数m和报数n"<<endl;
    cin>>m>>n;    //输入猴子总数及N
    if(n==1) //如果N=1则大王就是最后一只猴子
    {
        king=m;
    }
    else
    {
        //用线性表做
        p1=p2=new Monkey;
        head = p1;//设置头
        p1->num=1;//将p1的编号置1
        for(i=1; i<m; i++)  //剩下的m-1只猴子
        {
            p1=new Monkey;  //p1是新增加的
            p1->num=i+1;
            p2->next=p1;
            p2=p1;          //p2总是上一只
        }
        p2->next=head;      //最后一只指向第一只

        p1=head;
        for(i=1; i<m; i++)  //循环m-1次，淘汰m-1只猴子
        {
            for(j=1; j<n-1; j++)  //先找到第n-1只，下一只被淘汰
                p1=p1->next;    
            p2=p1->next;  //将p2设置为第n只猴子
            //cout<<"第"<<i<<"轮淘汰"<<p2->num<<endl; 
            p1->next=p2->next;
            p1=p2->next;  //下一轮数数的新起点
            delete p2;  //删除p2
        }
        king=p1->num;
        delete p1;
    }
    cout<<"猴子大王是:"<<king<<endl;
    return 0;
}
