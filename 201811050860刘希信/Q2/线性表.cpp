
#include <iostream>
using namespace std;
struct Monkey
{
    int num;  //���ӵı��
    struct Monkey *next; //��һֻ����
};
 
int main()
{
    int m,n,i,j,king;
    Monkey *head, *p1,*p2;
	cout<<"������Ӹ���m�ͱ���n"<<endl;
    cin>>m>>n;    //�������������N
    if(n==1) //���N=1������������һֻ����
    {
        king=m;
    }
    else
    {
        //�����Ա���
        p1=p2=new Monkey;
        head = p1;//����ͷ
        p1->num=1;//��p1�ı����1
        for(i=1; i<m; i++)  //ʣ�µ�m-1ֻ����
        {
            p1=new Monkey;  //p1�������ӵ�
            p1->num=i+1;
            p2->next=p1;
            p2=p1;          //p2������һֻ
        }
        p2->next=head;      //���һָֻ���һֻ

        p1=head;
        for(i=1; i<m; i++)  //ѭ��m-1�Σ���̭m-1ֻ����
        {
            for(j=1; j<n-1; j++)  //���ҵ���n-1ֻ����һֻ����̭
                p1=p1->next;    
            p2=p1->next;  //��p2����Ϊ��nֻ����
            //cout<<"��"<<i<<"����̭"<<p2->num<<endl; 
            p1->next=p2->next;
            p1=p2->next;  //��һ�������������
            delete p2;  //ɾ��p2
        }
        king=p1->num;
        delete p1;
    }
    cout<<"���Ӵ�����:"<<king<<endl;
    return 0;
}
