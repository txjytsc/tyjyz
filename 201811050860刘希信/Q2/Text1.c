#include<stdio.h>
int main()
{
	int m,n,number,count=1;		//number�Ǻ���ʣ�������count�ǵ�ǰ����
	int monkey[100];
	int t;						//t�������±�
	int i;
	printf("��������Ӹ��� m �ͱ��� n ��");
	scanf("%d%d",&m,&n);
	number = m;   //����ʣ�������ں��Ӹ���
	for(i=0;i<m;i++)
		monkey[i]=i+1;//�����Ӹ�����������
	t=0;
	while(number>1)
	{
		if(monkey[t]>0)
		{
			if(count!=n)
			{
				count++;
				t=(t+1)%m;		//t=(t+1)%mʵ�������±��1
			}
			else
			{
				monkey[t]=0; //�������ĺ�������Ӧ��������0  �ж�Ϊ����
				count=1;   //���¼���
				number--;  //����ʣ������һ
				t=(t+1)%m; 
			}
		}
		else
		{
			t=(t+1)%m;
		}
	}
	for(i=0;i<m;i++)   //�������� �鿴δ���ֺ���
	{
		if(monkey[i]>0)
			printf("���Ӵ�����%d\n",monkey[i]);
	}
	return 0;
}
