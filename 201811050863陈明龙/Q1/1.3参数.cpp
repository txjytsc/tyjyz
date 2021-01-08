#include <iostream>
using namespace std;
void fun1(int& m, int& n)
{
    int a, b, c, d, e;
    a = m / 10;
    b = m % 10;
    c = n % 10;
    d = n / 10;
    e = a * 1000 + b + c * 10 + d * 100;
    cout << "合并后的数： " << e << endl;
}
int main()
{
    int a;
    int b;
    cout << "请输入两个两位数a,b:";
    	cin >> a;
    	cin >> b;
    fun1(a, b);
    return 0;
}