#include<stdio.h>
int main()
{
	int m,n,number,count=1;		//number记猴子剩余个数，count记当前报数
	int monkey[100];
	int t;						//t记数组下标
	int i;
	printf("请输入猴子个数 m 和报数 n ：");
	scanf("%d%d",&m,&n);
	number = m;   //猴子剩余数等于猴子个数
	for(i=0;i<m;i++)
		monkey[i]=i+1;//将猴子个数存入数组
	t=0;
	while(number>1)
	{
		if(monkey[t]>0)
		{
			if(count!=n)
			{
				count++;
				t=(t+1)%m;		//t=(t+1)%m实现数组下标加1
			}
			else
			{
				monkey[t]=0; //将数到的猴子所对应的数组置0  判断为出局
				count=1;   //重新计数
				number--;  //猴子剩余数减一
				t=(t+1)%m; 
			}
		}
		else
		{
			t=(t+1)%m;
		}
	}
	for(i=0;i<m;i++)   //遍历数组 查看未出局猴子
	{
		if(monkey[i]>0)
			printf("猴子大王：%d\n",monkey[i]);
	}
	return 0;
}
