#include <iostream>
using namespace std;
struct houzi
{
    int num;  //���ӵı��
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
        //��������Χ�ɵ�ԲȦ
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
        p2->next = head;      //�����һָֻ���һֻ

        
        p1 = head;
        for (i = 1; i < m; i++)  //ѭ��m-1�Σ���̭m-1ֻ����
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