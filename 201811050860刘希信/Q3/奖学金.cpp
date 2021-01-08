#include<stdio.h>
#include<algorithm>
using namespace std;
struct node
{
   int yuwen,shuxue,yingyu; 
   int num,sum;   
}student[3000];
int compare(node x,node y)//比较规则
{
    if(x.sum!=y.sum) return x.sum>y.sum;
    if(x.yuwen!=y.yuwen) return x.yuwen>y.yuwen;
    if(x.num!=y.num) return x.num<y.num;
	else return 0;
}
int main()
{
    int i,j,n,m;
	printf("请输入学生人数:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
      scanf("%d%d%d",&student[i].yuwen,&student[i].shuxue,&student[i].yingyu);
      student[i].num=i+1;
      student[i].sum=student[i].yuwen+student[i].shuxue+student[i].yingyu;
    }
    sort(student,student+n,compare);//排序函数   起始  结束  方法
    for(i=0;i<5;i++)//输出前五名
    printf("%d %d\n",student[i].num,student[i].sum);
    while(1);
    return 0;
}
