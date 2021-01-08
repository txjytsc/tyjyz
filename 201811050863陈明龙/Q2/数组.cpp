#include<stdio.h>
int main()
{
	int m, n, number, count = 1;
	int houzi[1000]; //猴子编号最高值
	int t;						
	int i;
	printf("请输入猴子个数 m 和报数 n ：");
	scanf_s("%d%d", &m, &n);
	number = m;
	for (i = 0; i < m; i++) //生成猴子编号的数组
		houzi[i] = i + 1;
	t = 0;
	while (number > 1)
	{
		if (houzi[t] > 0)
		{
			if (count != n)
			{
				count++;
				t = (t + 1) % m;		//t=(t+1)%m实现数组下标加1
			}
			else
			{
				houzi[t] = 0;
				count = 1;
				number--;
				t = (t + 1) % m;
			}
		}
		else
		{
			t = (t + 1) % m;
		}
	}
	for (i = 0; i < m; i++)
	{
		if (houzi[i] > 0)
			printf("猴子大王编号是：%d\n", houzi[i]);
	}
	return 0;
}