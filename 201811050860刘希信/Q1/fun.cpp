#include <iostream>
using namespace std;
int fun(int x,int y)
{
	int c=1000*(x%10)+(y/10)+10*(x/10)+100*(y%10);
	return c;
}
void fun1(int x,int y,int &c)
{
	c=1000*(x%10)+(y/10)+10*(x/10)+100*(y%10);
}
void fun2(int x,int y,int *c)
{
	*c=1000*(x%10)+(y/10)+10*(x/10)+100*(y%10);
}
int main()
{
	int a;
	int b;
	int c;
	int c1;
	int c2;
	cout<<"������������λ��a,b:";
	cin>>a;
	cin>>b;
    c=fun(a,b);
    fun1(a,b,c1);
	fun2(a,b,&c2);
	cout<<"(1)���Ϊ:"<<c<<endl;
	cout<<"(2)���Ϊ:"<<c1<<endl;
	cout<<"(3)���Ϊ:"<<c2<<endl;
	return 0;
}