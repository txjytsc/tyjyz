#include<stdio.h>
#include<algorithm>
using namespace std;
struct node
{
   int yuwen,shuxue,yingyu; 
   int num,sum;   
}student[3000];
int compare(node x,node y)//�ȽϹ���
{
    if(x.sum!=y.sum) return x.sum>y.sum;
    if(x.yuwen!=y.yuwen) return x.yuwen>y.yuwen;
    if(x.num!=y.num) return x.num<y.num;
	else return 0;
}
int main()
{
    int i,j,n,m;
	printf("������ѧ������:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
      scanf("%d%d%d",&student[i].yuwen,&student[i].shuxue,&student[i].yingyu);
      student[i].num=i+1;
      student[i].sum=student[i].yuwen+student[i].shuxue+student[i].yingyu;
    }
    sort(student,student+n,compare);//������   ��ʼ  ����  ����
    for(i=0;i<5;i++)//���ǰ����
    printf("%d %d\n",student[i].num,student[i].sum);
    while(1);
    return 0;
}
