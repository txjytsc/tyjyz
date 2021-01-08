#include <iostream>
using namespace std;
struct houzi
{
    int num;  //猴子的编号
    struct houzi* next; 
};

int main()
{
    int m, n, i, j, king;
    houzi* head, * p1, * p2;
    cin >> m >> n;
    if (n == 1)
    {
        king = m;
    }
    else
    {
        //建立猴子围成的圆圈
        p1 = p2 = new houzi;
        head = p1;
        p1->num = 1;
        for (i = 1; i < m; i++)  
        {
            p1 = new houzi;  
            p1->num = i + 1;
            p2->next = p1;
            p2 = p1;          
        }
        p2->next = head;      //将最后一只指向第一只

        
        p1 = head;
        for (i = 1; i < m; i++)  //循环m-1次，淘汰m-1只猴子
        {
            
            for (j = 1; j < n - 1; j++)  
                p1 = p1->next;    

            
            p2 = p1->next;  
            
            p1->next = p2->next;  
            p1 = p2->next;  
            delete p2;  
        }
        king = p1->num;
        delete p1;
    }
    cout << king << endl;
    return 0;
}