#include<stdio.h>
int main()
{
	int m, n, number, count = 1;
	int houzi[1000]; //���ӱ�����ֵ
	int t;						
	int i;
	printf("��������Ӹ��� m �ͱ��� n ��");
	scanf_s("%d%d", &m, &n);
	number = m;
	for (i = 0; i < m; i++) //���ɺ��ӱ�ŵ�����
		houzi[i] = i + 1;
	t = 0;
	while (number > 1)
	{
		if (houzi[t] > 0)
		{
			if (count != n)
			{
				count++;
				t = (t + 1) % m;		//t=(t+1)%mʵ�������±��1
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
			printf("���Ӵ�������ǣ�%d\n", houzi[i]);
	}
	return 0;
}